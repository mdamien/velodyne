#include "AlascaConverter.h"

#include <QDir>

#include <fstream>
#include <iostream>
#include <sstream>

#include "kernel/DbiteException.h"
#include "kernel/DbiteFile.h"
#include "kernel/Log.h"
#include "structure/structure_telemetre.h"

using namespace pacpus;
using namespace std;

DECLARE_STATIC_LOGGER("pacpus.base.dbt2txt.AlascaConverter");

////////////////////////////////////////////////////////////////////////////////
typedef int16_t IntegerDistanceType;
typedef float RealDistanceType;

RealDistanceType convertAlascaNtoDistance(IntegerDistanceType n);
IntegerDistanceType convertDistanceToAlascaN(RealDistanceType d);

//////////////////////////////////////////////////////////////////////////
// convert the Alasca data in text format
// 
// columns in AlascaXT.txt: timestamp PC, start Angle, end Angle, 
// number of points, scanner type, time Start (relative to ECU), 
// name of the scan file
//
// Columns in scan_alasca#.txt:
//      scannerId, layerNumber, echoNumber, pointStatus, x [cm], y [cm], z [cm], width
void AlascaConverter::convert(const string & inputFilePath) const
{
    const string inputDirectory = getDirname(inputFilePath);

    // create output directory
    if (!createPath(getOutputDirectory())) {
        LOG_FATAL("cannot create output directory '" << getOutputDirectory() << "'");
        throw DbiteException("cannot create output log file");
    }

    // create output log file
    ofstream outputLogFile;
    const string txtFilePath = getOutputDirectory() + getPathSeparator() + "AlascaXT.txt";
    outputLogFile.open(txtFilePath.c_str(), ios::out | ios::trunc);
    if (!outputLogFile) {
        LOG_FATAL("cannot create output log file");
        throw DbiteException("cannot create output log file");
    }

    // open input data file
    ifstream dataFile;
    const string dataFilePath = getDirname(inputFilePath) + getPathSeparator() + "alasca_data.utc";
    dataFile.open(dataFilePath.c_str(), ios_base::in | ios_base::binary);
    if (!dataFile) {
        LOG_FATAL("cannot open input data file '" << dataFilePath << "'");
        throw DbiteException("cannot create output log file");
    }

    // open input dbt file
    DbiteFile inputDbiteFile;
    inputDbiteFile.open(inputFilePath, ReadMode);
    if (!inputDbiteFile.isOpen()) {
        LOG_FATAL("cannot open input Dbite file '" << inputFilePath << "'");
        throw DbiteException("cannot open input Dbite file");
    }
    
    // declarations
    road_time_t time;
    road_timerange_t tr;
    AlascaXT dbtData;

    // process all scans
    const int recordCount = inputDbiteFile.getRecordCount();
    LOG_INFO("To process: " << recordCount << " Alasca scans");
    float lastShownPercentDone = -1;
    int counter = 0;
    for (;;) {
        float percentDone = static_cast<int>(counter * 100.0 / recordCount);
        if (percentDone > lastShownPercentDone) {
            lastShownPercentDone = percentDone;
            LOG_INFO(percentDone << "%");
        }

        // read record from Dbite file
        size_t dataSize = sizeof(dbtData);
        if (!inputDbiteFile.readRecord(time, tr, reinterpret_cast<char *>(&dbtData), dataSize)) {
            break;
        }

        // get output file path
        ostringstream oss;
        oss << "alasca_scan" << counter << ".txt";
        const string outputTextFileName = oss.str();
        const string outputTextFilePath = getOutputDirectory() + getPathSeparator() + outputTextFileName;
        
        // write to log file:
        //      timestamp, start angle, end angle, #points, scanner type, time start, scan name
        outputLogFile <<
            time << " " <<
            dbtData.startAngle << " " <<
            dbtData.endAngle << " " <<
            dbtData.nbPoint << " " <<
            (unsigned short)(dbtData.scannertype) << " " <<
            dbtData.timeStart << " " <<
            outputTextFilePath << "\n";

        // set the get pointer to the correct place
        dataFile.seekg(dbtData.dataPos);

        // then copy the data contained in the binary file
        ScanAlascaData alascaData_;
        for (unsigned i = 0; i < dbtData.nbPoint; ++i) {
            dataFile.read(reinterpret_cast<char*>(&(alascaData_.point[i].scannerId)), sizeof(uint8_t));
            dataFile.read(reinterpret_cast<char*>(&(alascaData_.point[i].layerNumber)), sizeof(uint8_t));
            dataFile.read(reinterpret_cast<char*>(&(alascaData_.point[i].echoNumber)), sizeof(uint8_t));
            dataFile.read(reinterpret_cast<char*>(&(alascaData_.point[i].pointStatus)), sizeof(uint8_t));
            dataFile.read(reinterpret_cast<char*>(&(alascaData_.point[i].x)), sizeof(int16_t));
            dataFile.read(reinterpret_cast<char*>(&(alascaData_.point[i].y)), sizeof(int16_t));
            dataFile.read(reinterpret_cast<char*>(&(alascaData_.point[i].z)), sizeof(int16_t));
            dataFile.read(reinterpret_cast<char*>(&(alascaData_.point[i].width)), sizeof(uint16_t));
        }

        // verify that the last value is the UTC magic word
        int32_t utcMagicWord = 0;
        dataFile.read(reinterpret_cast<char*>(&(utcMagicWord)), sizeof(utcMagicWord));
        if (utcMagicWord != UTC_MAGIC_WORD) {
            LOG_ERROR("corrupted data, skipping");
        } else {
            LOG_DEBUG("scan No. " << counter);
            // create output text file
            ofstream outputTextFile;
            outputTextFile.open(outputTextFilePath.c_str(), ios::out | ios::trunc);
            
            // write data to text file
            outputTextFile << dbtData.timeStart << " " << time << "\n";
            for (unsigned i = 0; i < dbtData.nbPoint; ++i) {
                outputTextFile <<
                    (unsigned short)(alascaData_.point[i].scannerId) << " " <<
                    (unsigned short)(alascaData_.point[i].layerNumber) << " " <<
                    (unsigned short)(alascaData_.point[i].echoNumber) << " " <<
                    (unsigned short)(alascaData_.point[i].pointStatus) << " " <<
                    alascaData_.point[i].x << " " <<
                    alascaData_.point[i].y << " " <<
                    alascaData_.point[i].z << " " <<
                    alascaData_.point[i].width << "\n";
            }
            outputTextFile.close();
        }
        ++counter;
    }

    outputLogFile.close();
    dataFile.close();
    inputDbiteFile.close();

    LOG_INFO("Converted " << counter << " Alasca scans");
}

static const RealDistanceType kMultiplier = 100;
static const int kOffset = 900;

RealDistanceType convertAlascaNtoDistance(IntegerDistanceType n)
{
    if (n < -10000) {
        return n / kMultiplier + kOffset;
    } else if (n > 10000) {
        return n / kMultiplier - kOffset;
    } else {
        return n / kMultiplier;
    }
}

IntegerDistanceType convertDistanceToAlascaN(RealDistanceType d)
{
    if (d < -kMultiplier) {
        return static_cast<IntegerDistanceType>(10 * (d - kOffset));
    } else if (d > kMultiplier) {
        return static_cast<IntegerDistanceType>(10 * (d + kOffset));
    } else {
        return static_cast<IntegerDistanceType>(kMultiplier * d);
    }
}

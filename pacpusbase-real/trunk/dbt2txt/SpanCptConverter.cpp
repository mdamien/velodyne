#include "SpanCptConverter.h"

#include <iomanip>
#include <string>

#include "kernel/DbiteException.h"
#include "kernel/DbiteFile.h"
#include "kernel/DbiteFileTypes.h"
#include "kernel/Log.h"
#include "structure/structure_gps.h"

//namespace bu = boost::units;
using namespace pacpus;
using namespace std;

DECLARE_STATIC_LOGGER("pacpus.base.dbt2txt.SpanCptConverter");

SpanCptConverter::SpanCptConverter()
{
}

SpanCptConverter::~SpanCptConverter()
{
}

string insStatusToString(const INSStatus & status)
{
    switch (status) {
    case INS_INACTIVE:
        return "INS_INACTIVE";
        break;

    case INS_ALIGNING:
        return "INS_ALIGNING";
        break;

    case INS_SOLUTION_NOT_GOOD:
        return "INS_SOLUTION_NOT_GOOD";
        break;

    case INS_SOLUTION_GOOD:
        return "INS_SOLUTION_GOOD";
        break;

    case INS_BAD_GPS_AGREEMENT:
        return "INS_BAD_GPS_AGREEMENT";
        break;

    case INS_ALIGNMENT_COMPLETE:
        return "INS_ALIGNMENT_COMPLETE";
        break;

    default:
        LOG_FATAL("unknown INS status");
        throw DbiteException("unknown INS status");
    }
}

string groundStatusToString(const SolStatus & status)
{
    switch (status) {
    case SOL_COMPUTED:
        return "SOL_COMPUTED";
        break;

    case INSUFFICIENT_OBS:
        return "INSUFFICIENT_OBS";
        break;

    case NO_CONVERGENCE:
        return "NO_CONVERGENCE";
        break;

    case SINGULARITY:
        return "SINGULARITY";
        break;

    case COV_TRACE:
        return "COV_TRACE";
        break;

    case TEST_DIST:
        return "TEST_DIST";
        break;
        
    case COLD_START:
        return "COLD_START";
        break;

    case V_H_LIMIT:
        return "V_H_LIMIT";
        break;

    case VARIANCE:
        return "VARIANCE";
        break;

    case RESIDUALS:
        return "RESIDUALS";
        break;

    case DELTA_POS:
        return "DELTA_POS";
        break;

    case NEGATIVE_VAR:
        return "NEGATIVE_VAR";
        break;
        
    case INTEGRITY_WARNING:
        return "INTEGRITY_WARNING";
        break;

    case IMU_UNPLUGGED:
        return "IMU_UNPLUGGED";
        break;

    case PENDING:
        return "PENDING";
        break;

    default:
        LOG_FATAL("unknown ground status");
        throw DbiteException("unknown ground status");
    }
}

string positionTypeToString(const PosType & type)
{
    switch (type) {
    case NONE:
        return "NONE";
        break;
        
    case FIXEDPOS:
        return "FIXEDPOS";
        break;
        
    case FIXEDHEIGHT:
        return "FIXEDHEIGHT";
        break;
        
    case FLOATCONV:
        return "FLOATCONV";
        break;
        
    case WIDELANE:
        return "WIDELANE";
        break;
        
    case NARROWLANE:
        return "NARROWLANE";
        break;
        
    case DOPPLER_VELOCITY:
        return "DOPPLER_VELOCITY";
        break;
        
    case SINGLE:
        return "SINGLE";
        break;
        
    case PSRDIFF:
        return "PSRDIFF";
        break;
        
    case WAAS:
        return "WAAS";
        break;
        
    case PROPAGATED:
        return "PROPAGATED";
        break;
        
    case OMNISTAR:
        return "OMNISTAR";
        break;
        
    case L1_FLOAT:
        return "L1_FLOAT";
        break;
        
    case IONOFREE_FLOAT:
        return "IONOFREE_FLOAT";
        break;
        
    case NARROW_FLOAT:
        return "NARROW_FLOAT";
        break;
        
    case L1_INT:
        return "L1_INT";
        break;
        
    case WIDE_INT:
        return "WIDE_INT";
        break;
        
    case NARROW_INT:
        return "NARROW_INT";
        break;
        
    case RTK_DIRECT_INS:
        return "RTK_DIRECT_INS";
        break;
        
    case INS:
        return "INS";
        break;
        
    case INS_PSRSP:
        return "INS_PSRSP";
        break;
        
    case INS_PSRDIFF:
        return "INS_PSRDIFF";
        break;
        
    case INS_RTKFLOAT:
        return "INS_RTKFLOAT";
        break;
        
    case INS_RTKFIXED:
        return "INS_RTKFIXED";
        break;
        
    case INS_OMNISTAR:
        return "INS_OMNISTAR";
        break;
        
    case INS_OMNISTAR_HP:
        return "INS_OMNISTAR_HP";
        break;
        
    case INS_OMNISTAR_XP:
        return "INS_OMNISTAR_XP";
        break;
        
    case OMNISTAR_HP:
        return "OMNISTAR_HP";
        break;
        
    case OMNISTAR_XP:
        return "OMNISTAR_XP";
        break;
        
    case CDGPS:
        return "CDGPS";
        break;

    default:
        LOG_FATAL("unknown position type");
        throw DbiteException("unknown position type");
    }
}

/// T = header and record outputter object, should have methods:
///     void outputHeader(ofstream & os);
///     void outputRecord(ofstream & os, road_time_t t, road_timerange_t tr, const record_type & record);
template <typename T>
void convertSpanCptRecord(ofstream & outputTextFile, DbiteFile & inputDbiteFile, T & headerRecordOutputter);

template <class T>
void convertSpanCptRecord(ofstream & outputTextFile, DbiteFile & inputDbiteFile, T & outputter)
{
    outputter.outputHeader(outputTextFile);
    
    // declarations
    road_time_t t;
    road_timerange_t tr;
    T::record_type record;

    // process all records
    for (;;) {
        // read record from Dbite file
        size_t dataSize = sizeof(record);
        if (!inputDbiteFile.readRecord(t, tr, reinterpret_cast<char *>(&record), dataSize)) {
            break;
        }
        outputter.outputRecord(outputTextFile, t, tr, record);
    }
}

void SpanCptConverter::convert(const string & inputFilePath) const
{
    const string inputDirectory = getDirname(inputFilePath);

    // create output directory
    if (!createPath(getOutputDirectory())) {
        LOG_FATAL("cannot create output directory '" << getOutputDirectory() << "'");
        throw DbiteException("cannot create output log file");
    }

    // create output log file
    ofstream outputTextFile;
    const string txtFilePath = getOutputDirectory() + getPathSeparator() + getBasename(inputFilePath) + ".txt";
    outputTextFile.open(txtFilePath.c_str(), ios::out | ios::trunc);
    if (!outputTextFile) {
        LOG_FATAL("cannot create output log file");
        throw DbiteException("cannot create output log file");
    }
    
    outputTextFile << setprecision(12);

    // open input dbt file
    DbiteFile inputDbiteFile;
    inputDbiteFile.open(inputFilePath, ReadMode);
    if (!inputDbiteFile.isOpen()) {
        LOG_FATAL("cannot open input Dbite file '" << inputFilePath << "'");
        throw DbiteException("cannot open input Dbite file");
    }
    
    // record count
    const int recordCount = inputDbiteFile.getRecordCount();
    LOG_INFO("To process: " << recordCount << " records");
    
    // process all scans
    switch (inputDbiteFile.getType()) {
    case TRAME_BESTGPSPOSA:
        convertBestgpsposa(outputTextFile, inputDbiteFile);
        break;

    case TRAME_RAWIMUSA:
        convertRawimusa(outputTextFile, inputDbiteFile);
        break;

    case TRAME_INSPVAA:
        convertInspvaa(outputTextFile, inputDbiteFile);
        break;

    case TRAME_INSCOV:
        convertInscov(outputTextFile, inputDbiteFile);
        break;

    default:
        throw DbiteException("unknown record type");
    }
}

/// Outputter for TRAME_BESTGPSPOSA
class BestgpsposaOutputter
{
public:
    typedef trame_bestgpsposa record_type;
    void outputHeader(ofstream & os);
    void outputRecord(ofstream & os, road_time_t t, road_timerange_t tr, const record_type & record);
};

void BestgpsposaOutputter::outputHeader(ofstream & os)
{
    os  << "# "
        << "Timestamp" << ", "
        << "Timerange" << ", "

        << "GroundStatus" << ", "
        << "PositionType" << ", "
        << "Latitude" << ", "
        << "Longitude" << ", "
        << "Altitude" << ", "
        << "Undulation" << ", "
        << "LatitudeStdDev" << ", "
        << "LongitudeStdDev" << ", "
        << "AltitudeStdDev" << ", "
        << "East" << ", "
        << "North" << ", "
        << "Up" << "\n"
        ;
}

void BestgpsposaOutputter::outputRecord(ofstream & os, road_time_t t, road_timerange_t tr, const record_type & record)
{
    os
        << t << " "
        << tr << " "
        
        << groundStatusToString(record.Status) << " "
        << positionTypeToString(record.posType) << " "
        << record.Lat << " "
        << record.Lon << " "
        << record.Hgt << " "
        << record.Undulation << " "
        << record.LatStd << " "
        << record.LonStd << " "
        << record.HgtStd << " "
        << record.e << " "
        << record.n << " "
        << record.u << "\n"
        ;
}

/// Outputter for TRAME_INSPVAA
class InspvaaOutputter
{
public:
    typedef trame_inspvaa record_type;
    void outputHeader(ofstream & os);
    void outputRecord(ofstream & os, road_time_t t, road_timerange_t tr, const record_type & record);
};

void InspvaaOutputter::outputHeader(ofstream & os)
{
    os  << "# "
        << "Timestamp" << ", "
        << "Timerange" << ", "

        << "GpsWeek" << ", "
        << "(reserved)" << ", "
        << "Seconds" << ", "
        << "Latitude" << ", "
        << "Longitude" << ", "
        << "Altitude" << ", "

        << "EastSpeed" << ", "
        << "NorthSpeed" << ", "
        << "UpSpeed" << ", "

        << "Roll" << ", "
        << "Pitch" << ", "
        << "Azimuth" << ", "
        << "Status" << ", "
        << "(reserved)" << ", "
        << "East" << ", "
        << "North" << ", "
        << "Up" << "\n"
        ;
}

void InspvaaOutputter::outputRecord(ofstream & os, road_time_t t, road_timerange_t tr, const record_type & record)
{
    os
        << t << " "
        << tr << " "

        << record.Week << " "
        << record.reserved << " "
        << record.Seconds << " "
        << record.Lat << " "
        << record.Lon << " "
        << record.Hgt << " "
        << record.EastVel << " "
        << record.NorthVel << " "
        << record.UpVel << " "
        << record.Roll << " "
        << record.Pitch << " "
        << record.Azimuth << " "
        << insStatusToString(record.Status) << " "
        << record.reserved1 << " "
        << record.e << " "
        << record.n << " "
        << record.u << "\n"
        ;
}

/// Outputter for TRAME_RAWIMUSA
class RawimusaOutputter
{
public:
    typedef trame_rawimusa record_type;
    void outputHeader(ofstream & os);
    void outputRecord(ofstream & os, road_time_t t, road_timerange_t tr, const record_type & record);
};

void RawimusaOutputter::outputHeader(ofstream & os)
{
    os  << "# "
        << "Timestamp" << ", "
        << "Timerange" << ", "

        << "Week" << ", "
        << "(reserved)" << ", "
        << "Seconds" << ", "
        << "XAccel" << ", "
        << "YAccel" << ", "
        << "ZAccel" << ", "
        << "XGyro" << ", "
        << "YGyro" << ", "
        << "ZGyro" << "\n"
        ;
}

void RawimusaOutputter::outputRecord(ofstream & os, road_time_t t, road_timerange_t tr, const record_type & record)
{
    os
        << t << " "
        << tr << " "
        << record.Week << " "
        << record.reserved << " "
        << record.Seconds << " "
        << record.XAccel << " "
        << record.YAccel << " "
        << record.ZAccel << " "
        << record.XGyro << " "
        << record.YGyro << " "
        << record.ZGyro << "\n"
        ;
}

/// Outputter for TRAME_INSCOV
class InscovOutputter
{
public:
    typedef trame_inscov record_type;
    void outputHeader(ofstream & os);
    void outputRecord(ofstream & os, road_time_t t, road_timerange_t tr, const record_type & record);
};

void InscovOutputter::outputHeader(ofstream & os)
{
    os  << "# "
        << "Timestamp" << ", "
        << "Timerange" << ", "

        << "Week" << ", "
        << "(reserved)" << ", "
        << "Seconds" << ", "
        << "PosCov[3][3]" << ", "
        << "AttCov[3][3]" << ", "
        << "VelCov[3][3]" << "\n"
        ;
    os  << "# "
        << "arrays written in left-to-right line-by-line order" << "\n"
        ;
}

void InscovOutputter::outputRecord(ofstream & os, road_time_t t, road_timerange_t tr, const record_type & record)
{
    os
        << t << " "
        << tr << " "

        << record.Week << " "
        << record.reserved << " "
        << record.Seconds << " "
        ;
    for (size_t r = 0; r < 3; ++r) {
        for (size_t c = 0; c < 3; ++c) {
            os << record.PosCov[r][c] << " ";
        }
    }
    for (size_t r = 0; r < 3; ++r) {
        for (size_t c = 0; c < 3; ++c) {
            os << record.AttCov[r][c] << " ";
        }
    }
    for (size_t r = 0; r < 3; ++r) {
        for (size_t c = 0; c < 3; ++c) {
            os << record.VelCov[r][c] << " ";
        }
    }
    os << "\n";
}

// Convert functions using outputters
void SpanCptConverter::convertBestgpsposa(ofstream & outputTextFile, DbiteFile & inputDbiteFile) const
{
    BestgpsposaOutputter outputter;
    convertSpanCptRecord(outputTextFile, inputDbiteFile, outputter);
}

void SpanCptConverter::convertRawimusa(ofstream & outputTextFile, DbiteFile & inputDbiteFile) const
{
    RawimusaOutputter outputter;
    convertSpanCptRecord(outputTextFile, inputDbiteFile, outputter);
}

void SpanCptConverter::convertInspvaa(ofstream & outputTextFile, DbiteFile & inputDbiteFile) const
{
    InspvaaOutputter outputter;
    convertSpanCptRecord(outputTextFile, inputDbiteFile, outputter);
}

void SpanCptConverter::convertInscov(ofstream & outputTextFile, DbiteFile & inputDbiteFile) const
{
    InscovOutputter outputter;
    convertSpanCptRecord(outputTextFile, inputDbiteFile, outputter);
}

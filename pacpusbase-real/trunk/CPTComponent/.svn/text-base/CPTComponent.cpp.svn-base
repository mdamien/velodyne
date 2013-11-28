// *********************************************************************
//  created:    20011/06/28 - 18:13
//  filename:   cptComponent.cpp
//
//  author:     Sergio Rodriguez
//
//  version:    $Id: $
//
//  purpose:     Acquires SPAN CPT data
//
// *********************************************************************

#include "CPTComponent.h"

#include <iostream>

#include "kernel/ComponentFactory.h"
#include "kernel/DbiteFileTypes.h"
#include "kernel/Log.h"
#include "PacpusTools/geodesie.h"
#include "PacpusTools/ShMem.h"

namespace pacpus {

using namespace std;

/// Construct the factory
static ComponentFactory<CPTComponent> sFactory("CPTComponent");

static const size_t AllFramesSize = sizeof(TimestampedBestgpsposaFrame)
+ sizeof(TimestampedRawimusaFrame)
+ sizeof(TimestampedInspvaaFrame)
+ sizeof(TimestampedInscovFrame)
;

DECLARE_STATIC_LOGGER("pacpus.base.CPTComponent");

//////////////////////////////////////////////////////////////////////////
/// Constructor of CPTComponent class
CPTComponent::CPTComponent(QString name)
    : ComponentBase(name)
{
    LOG_INFO("sizeof(TimestampedBestgpsposaFrame)=" << sizeof(TimestampedBestgpsposaFrame));
    LOG_INFO("sizeof(TimestampedRawimusaFrame)=" << sizeof(TimestampedRawimusaFrame));
    LOG_INFO("sizeof(TimestampedInspvaaFrame)=" << sizeof(TimestampedInspvaaFrame));
    LOG_INFO("sizeof(TimestampedInscovFrame)=" << sizeof(TimestampedInscovFrame));

    mVerbose = false;
    recording = false;
    enuRef_ = false;
    LAT_REF =0.0;
    LON_REF =0.0;
    HE_REF =0.0;

    currentRoadtime_ = 0;
    currentTimerange_ = 0;

    //decoding
    currentDataFrame ="";
    currentRoadtime = 0;
    currentTimerange = 0;

    frameToDecode = "";
    timeOfFrameToDecode = 0;
    timerangeOfFrameToDecode = 0;

    restOfFrame = "";

    newFrameToDecode = false;
    startOfFrame = false;
    sofIdx_ =0;
    endOfFrame = false;
    eofIdx_ =0;

    //ShMems allocation
    mShMem = new ShMem("SPAN_FRAMES", AllFramesSize);
    mAllFramesBuffer = new char[AllFramesSize];
}

/// Destructor of the CPTComponent class
CPTComponent::~CPTComponent()
{
    delete mShMem;
    delete[] mAllFramesBuffer;
}

ComponentBase::COMPONENT_CONFIGURATION CPTComponent::configureComponent(XmlComponentConfig /*config*/)
{
    setPortCOM( param.getProperty("port").toLatin1() );

    if (!param.getProperty("recording").isNull()) {
        recording = (param.getProperty("recording") == "true" ? true : false);
    }
    if (!param.getProperty("verbose").isNull()) {
        mVerbose =  (param.getProperty("verbose") == "true" ? true : false);
    }
    if (!param.getProperty("ENUref").isNull()) {
        enuRef_ = (param.getProperty("ENUref") == "true" ? true : false);
        if (enuRef_) {
            LAT_REF = param.getProperty("LatRef").toDouble();
            LON_REF = param.getProperty("LonRef").toDouble();
            HE_REF = param.getProperty("HeRef").toDouble();
            if (mVerbose) {
                LOG_DEBUG("Reference Saint Mande:: Lat: " << LAT_REF << ", Lon: " << LON_REF << " Height: " << HE_REF);
            }
        }
    }
    return ComponentBase::CONFIGURED_OK;
}

void CPTComponent::setPortCOM(const char * port)
{
    portName = port;
}

/// Log function
void CPTComponent::processing(int /*i*/)
{
    if (!serialPort) {
        LOG_WARN("no serial port");
        return;
    }

    //ShMem data variables
    TimestampedBestgpsposaFrame a;
    TimestampedRawimusaFrame b;
    TimestampedInspvaaFrame c;
    TimestampedInscovFrame d;

    //ShMem buffer allocation
    char * allFramesBuffer = new char[AllFramesSize];

    //ShMem buffer initialization
    initBuffer(&a, &b, &c, &d);
    memcpy(allFramesBuffer,
           &a, sizeof(TimestampedBestgpsposaFrame));
    memcpy(allFramesBuffer
           + sizeof(TimestampedBestgpsposaFrame),
           &b,sizeof(TimestampedRawimusaFrame));
    memcpy(allFramesBuffer
           + sizeof(TimestampedBestgpsposaFrame) + sizeof(TimestampedRawimusaFrame),
           &c, sizeof(TimestampedInspvaaFrame));
    memcpy(allFramesBuffer
           + sizeof(TimestampedBestgpsposaFrame)+sizeof(TimestampedRawimusaFrame)+sizeof(TimestampedInspvaaFrame),
           &d, sizeof(TimestampedInscovFrame));

    memcpy(allFramesBuffer, mAllFramesBuffer, AllFramesSize);

    // get the frame and remove it in the list
    FRAME * currentFrame = serialPort->firstFrame();

    char * currentDataFrame = new char[currentFrame->length];
    memcpy(currentDataFrame, currentFrame->data, currentFrame->length);
    currentDataFrameLength_ = currentFrame->length;
    currentRoadtime_ = currentFrame->t;

    serialPort->removeFirstFrame();

    setState(ComponentBase::MONITOR_OK);

    if (recording) {
        s8Data_.dataPos = dataFile_.tellp();
        s8Data_.length  = currentDataFrameLength_;
        if (mVerbose) {
            LOG_DEBUG("data:" << currentDataFrame << "addr:" << s8Data_.dataPos << "l:" << s8Data_.length);
        }
        size_t dataSize = sizeof(Stream8Position);
        raws8hdFile.writeRecord(currentRoadtime_, 0, reinterpret_cast<const char *>(&s8Data_), dataSize);
        dataFile_.write(reinterpret_cast<char*>(currentDataFrame), currentDataFrameLength_);
    }

    // Decoding
    char * buffer = new char[currentDataFrameLength_ + 1];
    memcpy(buffer, currentDataFrame, currentDataFrameLength_);
    buffer[currentDataFrameLength_] = '\0'; // add a \0 to convert for the conversion in QString

    currentDataFrame = buffer;
    currentRoadtime  = currentRoadtime_;
    currentTimerange = currentRoadtime_;

    analyzeFrame();

    if (newFrameToDecode) {
        LOG_DEBUG("got new frame to decode");

        type = frameType(frameToDecode);
        LOG_DEBUG("frame type=" << type);
        if (-1 != type) {
            if (-1 == decodeFrame(type)) {
                LOG_WARN("cannot decode the dataframe");
            } else {
                switch(type) {
                case TRAME_GGA_DBL:
                    if (mVerbose) {
                        cout << "[SPAN-GGA] Lat: " <<
                                ggaFrame_.lat<<
                                " Lon: " << ggaFrame_.lon<<
                                " Hgt: " << ggaFrame_.alt_msl <<
                                " Quality: " << ggaFrame_.ind_qualite << "\n";}
                    break;

                case TRAME_BESTGPSPOSA:
                    //ShMem buffer data copy
                    memcpy(&a.frame, &bestgpsposaFrame_, sizeof(trame_bestgpsposa));
                    a.time=timeOfFrameToDecode;
                    a.timerange=timerangeOfFrameToDecode;
                    memcpy(allFramesBuffer, &a, sizeof(TimestampedBestgpsposaFrame));

                    if (recording) {
                        size_t dataSize = sizeof(bestgpsposaFrame_);
                        bestgpsposaFile_.writeRecord(timeOfFrameToDecode, timerangeOfFrameToDecode,
                                                     reinterpret_cast<const char *>(&bestgpsposaFrame_), dataSize);
                    }
                    if (mVerbose) {
                        cout << "[SPAN-BESTGPSPOSA]" << "\t"
                             << "Lat=" << bestgpsposaFrame_.Lat << "\t"
                             << "Lon=" << bestgpsposaFrame_.Lon << "\t"
                             << "Hgt=" << bestgpsposaFrame_.Hgt << "\t"
                             << "E=" << bestgpsposaFrame_.e << "\t"
                             << "N=" << bestgpsposaFrame_.n << "\t"
                             << "U=" << bestgpsposaFrame_.u
                                ;
                    }
                    mShMem->write(allFramesBuffer, AllFramesSize);
                    break;

                case TRAME_RAWIMUSA:

                    //ShMem buffer data copy
                    memcpy(&b.frame, &rawimuFrame_, sizeof(trame_rawimusa));
                    b.time=timeOfFrameToDecode;
                    b.timerange=timerangeOfFrameToDecode;
                    memcpy(allFramesBuffer+
                           sizeof(TimestampedBestgpsposaFrame),&b,sizeof(TimestampedRawimusaFrame));

                    if (recording) {
                        size_t dataSize = sizeof(rawimuFrame_);
                        rawimuFile_.writeRecord(timeOfFrameToDecode, timerangeOfFrameToDecode,
                                                reinterpret_cast<const char *>(&rawimuFrame_), dataSize);
                    }
                    if (mVerbose) {
                        cout << "[SPAN-RAWIMUSA]"<< endl;
                    }

                    //ShMem refresh
                    mShMem->write(allFramesBuffer, sizeof(TimestampedBestgpsposaFrame)
                                  +sizeof(TimestampedRawimusaFrame)
                                  +sizeof(TimestampedInspvaaFrame)
                                  +sizeof(TimestampedInscovFrame));
                    break;
                case TRAME_INSPVAA:

                    //ShMem buffer data copy
                    memcpy(&c.frame, &inspvaFrame_, sizeof(trame_inspvaa));
                    c.time=timeOfFrameToDecode;
                    c.timerange=timerangeOfFrameToDecode;
                    memcpy(allFramesBuffer+
                           sizeof(TimestampedBestgpsposaFrame)+sizeof(TimestampedRawimusaFrame),
                           &c,sizeof(TimestampedInspvaaFrame));

                    if (recording) {
                        size_t dataSize = sizeof(inspvaFrame_);
                        inspvaFile_.writeRecord(timeOfFrameToDecode, timerangeOfFrameToDecode,
                                                reinterpret_cast<const char *>(&inspvaFrame_), dataSize);
                    }
                    if (mVerbose) {
                        cout << "[SPAN-INSPVAA]:" << "\t"
                             << "Lat: " << inspvaFrame_.Lat << "\t"
                             << "Lon: " << inspvaFrame_.Lon  << "\t"
                             << "Roll: "<< inspvaFrame_.Roll << "\t"
                             << "Pitch: " << inspvaFrame_.Azimuth << "\t"
                             << "E: " << inspvaFrame_.e << "\t"
                             << "N: " << inspvaFrame_.n << "\t"
                             << "U: " << inspvaFrame_.u << endl;
                    }

                    //ShMem refresh
                    mShMem->write(allFramesBuffer, sizeof(TimestampedBestgpsposaFrame)
                                  +sizeof(TimestampedRawimusaFrame)
                                  +sizeof(TimestampedInspvaaFrame)
                                  +sizeof(TimestampedInscovFrame));
                    break;
                case TRAME_INSCOV:

                    //ShMem data copy
                    memcpy(&d.frame, &inscovFrame_, sizeof(trame_inscov));
                    d.time=timeOfFrameToDecode;
                    d.timerange=timerangeOfFrameToDecode;
                    memcpy(allFramesBuffer+
                           sizeof(TimestampedBestgpsposaFrame)+sizeof(TimestampedRawimusaFrame)+sizeof(TimestampedInspvaaFrame),
                           &d,sizeof(TimestampedInscovFrame));

                    if (recording) {
                        size_t dataSize = sizeof(inscovFrame_);
                        inscovFile_.writeRecord(timeOfFrameToDecode, timerangeOfFrameToDecode,
                                                reinterpret_cast<const char *>(&inscovFrame_), dataSize);
                        // FIXED: was inscovFile_ instead of inscovFrame_ given as buffer
                    }
                    if (mVerbose) {
                        cout << "[SPAN-INSCOV] CovXX: " << inscovFrame_.PosCov[0][0] <<
                                " CovYY: " << inscovFrame_.PosCov[1][1] <<
                                " CovZZ: "<< inscovFrame_.PosCov[2][2] << endl;
                    }

                    //ShMem refresh
                    mShMem->write(allFramesBuffer, sizeof(TimestampedBestgpsposaFrame)
                                  +sizeof(TimestampedRawimusaFrame)
                                  +sizeof(TimestampedInspvaaFrame)
                                  +sizeof(TimestampedInscovFrame));
                    break;
                default:
                    break;
                }
            }
        }

        type = -1;
        newFrameToDecode = false;
        frameToDecode = "";
    }
    delete[] buffer;
    delete[] currentDataFrame;

    memcpy(mAllFramesBuffer, allFramesBuffer, AllFramesSize);

    delete[] allFramesBuffer;

}

/************************************************************************/
/* Method to stop the thread                                            */
/************************************************************************/
void CPTComponent::stopActivity()
{
    serialPort->THREAD_ALIVE = false;
    if (!serialPort->wait(2000)) {
        serialPort->terminate();
        qDebug("The Win32SerialPort thread blocks anormally, it has been killed !!");
    }
    if ( !serialPort->closePort() )
        qDebug("Failed to close the port");
    else
        qDebug("The port is closed");
    delete serialPort;
    serialPort = NULL;

    if (recording) {
        bestgpsposaFile_.close();
        rawimuFile_.close();
        inspvaFile_.close();
        inscovFile_.close();
        raws8hdFile.close();
        dataFile_.close();
    }
}

/************************************************************************/
/* Method to start the thread                                            */
/************************************************************************/
void CPTComponent::startActivity()
{
    type = -1;

#if WIN32
    serialPort = new Win32SerialPort(portName.toLatin1());
    // Asynchrone
    serialPort->setMode(FILE_FLAG_OVERLAPPED);
    // Synchrone
    //serialPort->setMode(0);
#else 
    serialPort = new PosixSerialPort(portName.toLatin1());
#endif

    if (!serialPort->openPort(portName.toLatin1())) {
        LOG_ERROR("cannot open the port " << portName);
        LOG_INFO("cannot start SPAN CPT Component '" << componentName << "'");
        return;
    }

    serialPort->configurePort(param.getProperty("baudrate").toLong(),
                              param.getProperty("bytesize").toUInt(),
                              param.getProperty("parity").toShort(),
                              param.getProperty("stopbits").toUInt() - 1);

    if (recording) {
        bestgpsposaFile_.open("SPAN_bestgpsposa.dbt", WriteMode, TRAME_BESTGPSPOSA, sizeof(trame_bestgpsposa));
        rawimuFile_.open("SPAN_rawimusa.dbt", WriteMode, TRAME_RAWIMUSA, sizeof(trame_rawimusa));
        inspvaFile_.open("SPAN_inspvaa.dbt", WriteMode, TRAME_INSPVAA, sizeof(trame_inspvaa));
        inscovFile_.open("SPAN_inscov.dbt", WriteMode, TRAME_INSCOV, sizeof(trame_inscov));

        // raw data file: Dbt header  + binary data stream
        raws8hdFile.open((ComponentBase::componentName + ".dbt").toStdString(), WriteMode, STREAM8POSITION, sizeof(Stream8Position));
        // FIXME: use ofstream
        // open the file with C function to be sure that it will exist
        FILE * stream = NULL;
        if ( ( stream = fopen((ComponentBase::componentName + ".utc").toLatin1().data(),"a+")  ) == NULL ) {
            LOG_FATAL("Error while opening the stream utc file\n press a ENTER to exit");
            getchar();
            ::exit(-1);
        } else {
            fclose(stream);
        }

        dataFile_.open((ComponentBase::componentName + ".utc").toLatin1().data(), ios_base::out|ios_base::binary|ios_base::app);
        if (!dataFile_)
        {
            printf("Error while opening the file alasca_data.utc\n press a ENTER to exit\n");
            getchar();
            ::exit(0);
        }
    }

    if (!connect(serialPort,SIGNAL(newDataAvailable(int)),this, SLOT(processing(int)))) {
        LOG_WARN("cannot connect SIGNAL(newDataAvailable(int)) with SLOT(unlockProcessing(int)");
    }
    LOG_INFO("started component '" << componentName << "'");

    serialPort->THREAD_ALIVE = true;
    serialPort->start();

}

int CPTComponent::analyzeFrame()
{
    // SOF = start of frame
    // EOF = end of frame

    // PPS case
    //if (currentDataFrame == "PPS")
    //{
    //    frameToDecode = currentDataFrame;
    //    newFrameToDecode = true;
    //    timeOfFrameToDecode = currentRoadtime;
    //    timerangeOfFrameToDecode = currentTimerange;
    //    return 1;
    //}

    currentDataFrame = restOfFrame + currentDataFrame;
    restOfFrame = "";

    if (currentDataFrame.indexOf(QRegExp("[$#%]"),0)!=-1) {
        sofIdx_ = currentDataFrame.indexOf(QRegExp("[$#%]"),0);
        startOfFrame = true;
        timeOfFrameToDecode = currentRoadtime;

        if (currentDataFrame.indexOf("\n",sofIdx_)!=-1) {
            eofIdx_ = currentDataFrame.indexOf("\n",sofIdx_);
            endOfFrame = true;
            timerangeOfFrameToDecode = currentTimerange;
        }
        else
            restOfFrame = currentDataFrame;
    }
    else
        restOfFrame = currentDataFrame;

    if ( (startOfFrame) && (endOfFrame) )
    {
        newFrameToDecode = true;
        for (int i=sofIdx_;i<eofIdx_;i++)
            frameToDecode +=currentDataFrame.at(i);
        for (int j=eofIdx_+1; j<currentDataFrame.size(); j++)
            restOfFrame +=currentDataFrame.at(j);
        if (mVerbose) {
            LOG_DEBUG("[Frame:] " << frameToDecode);
        }
    }
    startOfFrame = false;
    endOfFrame = false;
    sofIdx_ =0;
    eofIdx_ =0;

    return 1;
}

int CPTComponent::frameType(const QString frame)
{
    if (( frame[0] == 'P' )  && (frame[1] == 'P')&&( frame[2] == 'S' )) return SIGNAL_PPS ;
    if (( frame[1] == 'G' )  && (frame[2] == 'P')&&( frame[3] == 'G' ) && (frame[4] == 'G')&&(frame[5] == 'A')) return TRAME_GGA_DBL ;
    if (( frame[1] == 'G' )  && (frame[2] == 'P')&&( frame[3] == 'G' ) && (frame[4] == 'S')&&(frame[5] == 'A')) return TRAME_GSA ;
    if (( frame[1] == 'G' )  && (frame[2] == 'P')&&( frame[3] == 'H' ) && (frame[4] == 'D')&&(frame[5] == 'T')) return TRAME_HDT ;
    if (( frame[1] == 'G' )  && (frame[2] == 'P')&&( frame[3] == 'G' ) && (frame[4] == 'S')&&(frame[5] == 'T')) return TRAME_GST ;
    if (( frame[1] == 'G' )  && (frame[2] == 'P')&&( frame[3] == 'G' ) && (frame[4] == 'S')&&(frame[5] == 'V')) return TRAME_GSV ;
    if (( frame[1] == 'G' )  && (frame[2] == 'P')&&( frame[3] == 'R' ) && (frame[4] == 'M')&&(frame[5] == 'C')) return TRAME_RMC ;
    if (( frame[1] == 'G' )  && (frame[2] == 'P')&&( frame[3] == 'R' ) && (frame[4] == 'O')&&(frame[5] == 'T')) return TRAME_ROT ;
    if (( frame[1] == 'G' )  && (frame[2] == 'P')&&( frame[3] == 'V' ) && (frame[4] == 'T')&&(frame[5] == 'G')) return TRAME_VTG ;
    if (( frame[1] == 'G' )  && (frame[2] == 'P')&&( frame[3] == 'Z' ) && (frame[4] == 'D')&&(frame[5] == 'A')) return TRAME_ZDA ;
    if ((frame[0]== '#')||(frame[0]== '%')) { // Span CPT frames
        if ((frame.contains("BESTGPSPOSA", Qt::CaseSensitive)))
            return TRAME_BESTGPSPOSA;
        else if ((frame.contains("RAWIMUSA", Qt::CaseSensitive)))
            return TRAME_RAWIMUSA;
        else if ((frame.contains("INSPVAA", Qt::CaseSensitive))||(frame.contains("INSPVASA", Qt::CaseSensitive)))
            return TRAME_INSPVAA;
        else if ((frame.contains("INSCOVA", Qt::CaseSensitive))||(frame.contains("INSCOVSA", Qt::CaseSensitive)))
            return TRAME_INSCOV;
        else
            return UNKNOWN_NMEA_FRAME;
    }
    return UNKNOWN_NMEA_FRAME;
}

int CPTComponent::decodeFrame(int type)
{
    double lat_rad = 0, lon_rad = 0;
    int indexGSV = 0;
    int indexGSA = 0;
    //int pps = 1; // dummy value for pps recording

    SENTENCE sentence;
    sentence.Sentence = frameToDecode;

    QStringList stringList;
    QString header;
    QString data;

    switch(type) {
    case UNKNOWN_NMEA_FRAME:
        LOG_ERROR("received unknown frame");
        break;

    case SIGNAL_PPS:
        // TODO
        LOG_WARN("unimplemented");
                break;

    case TRAME_GGA_DBL:
        if (sentence.Sentence.contains("PPS", Qt::CaseSensitive)) {
            LOG_ERROR("Almanac error on SPAN CPT");
            return -1;
        } else {
            if (!nmea0183_.Gga.Parse(sentence)) {
                LOG_ERROR("cannot parse the frame " << nmea0183_.Gga.ErrorMessage);
            }
            lat_rad = Geodesie::Deg2Rad(nmea0183_.Gga.Position.Latitude.GetDecimalDegrees());
            lon_rad = Geodesie::Deg2Rad(nmea0183_.Gga.Position.Longitude.GetDecimalDegrees());
            ggaFrame_.H = nmea0183_.Gga.Time.time().hour();
            ggaFrame_.Mi = nmea0183_.Gga.Time.time().minute();
            ggaFrame_.S = nmea0183_.Gga.Time.time().second();
            ggaFrame_.Ms = nmea0183_.Gga.Time.time().msec();
            ggaFrame_.lon = lon_rad;
            ggaFrame_.lat = lat_rad;
            ggaFrame_.ind_qualite = nmea0183_.Gga.GPSQuality;
            ggaFrame_.nb_sat = nmea0183_.Gga.NumberOfSatellitesInUse;
            ggaFrame_.hdop = nmea0183_.Gga.HorizontalDilutionOfPrecision;
            ggaFrame_.alt_msl = nmea0183_.Gga.AntennaAltitudeMeters;
            ggaFrame_.d_geoidal = nmea0183_.Gga.GeoidalSeparationMeters;
            ggaFrame_.age = nmea0183_.Gga.AgeOfDifferentialGPSDataSeconds;
            ggaFrame_.dir_lat = ( (nmea0183_.Gga.Position.Latitude.Northing == North) ? 'N' : 'S' );
            ggaFrame_.dir_lon = ( (nmea0183_.Gga.Position.Longitude.Easting == East) ? 'E' : 'W' );
            ggaFrame_.ref_station_ID = nmea0183_.Gga.DifferentialReferenceStationID;
        }
        break;

    case TRAME_GSA:
        if (!nmea0183_.Gsa.Parse(sentence))
            qWarning("Failed to parse the frame %s\n", nmea0183_.Gsa.ErrorMessage.toLatin1().data());
        gsaFrame_.mode_select = ((nmea0183_.Gsa.OperatingMode == GSA::Manual) ? 'M' : 'A');
        gsaFrame_.mode_result = 0;
        if (nmea0183_.Gsa.FixMode == GSA::FixUnavailable)
            gsaFrame_.mode_result = 1;
        if (nmea0183_.Gsa.FixMode == GSA::TwoDimensional)
            gsaFrame_.mode_result = 2;
        if (nmea0183_.Gsa.FixMode == GSA::ThreeDimensional)
            gsaFrame_.mode_result = 3;
        for (indexGSA = 0 ; indexGSA<12 ; indexGSA++)
            gsaFrame_.SV_PRN[indexGSA] = nmea0183_.Gsa.SatelliteNumber[indexGSA];
        gsaFrame_.pdop = nmea0183_.Gsa.PDOP;
        gsaFrame_.hdop = nmea0183_.Gsa.HDOP;
        gsaFrame_.vdop = nmea0183_.Gsa.VDOP;

        break;

    case TRAME_GST:
        if (!nmea0183_.Gst.Parse( sentence ))
            qWarning("Failed to parse the frame %s\n",nmea0183_.Gst.ErrorMessage.toLatin1().data());
        gstFrame_.rms = nmea0183_.Gst.RMSvalue;
        gstFrame_.a = nmea0183_.Gst.ErrorEllipseMajor;
        gstFrame_.b = nmea0183_.Gst.ErrorEllipseMinor;
        gstFrame_.phi = nmea0183_.Gst.ErrorEllipseOrientation;
        gstFrame_.sigma_lat = nmea0183_.Gst.LatitudeError;
        gstFrame_.sigma_lon = nmea0183_.Gst.LongitudeError;
        gstFrame_.sigma_alt = nmea0183_.Gst.HeightError;
        gstFrame_.H = nmea0183_.Gst.Time.time().hour();
        gstFrame_.Mi = nmea0183_.Gst.Time.time().minute();
        gstFrame_.S = nmea0183_.Gst.Time.time().second();
        gstFrame_.Ms = nmea0183_.Gst.Time.time().msec();

        break;

    case TRAME_GSV:
        indexGSV = 0;
        if (!nmea0183_.Gsv.Parse( sentence ))
            qWarning("Failed to parse the frame %s\n",nmea0183_.Gsv.ErrorMessage.toLatin1().data());
        // it's a new frame, reset stored value in case of the number of satellites
        // in view has decreased
        if (nmea0183_.Gsv.message_number == 1)
        {
            while (indexGSV < 36)
            {
                gsvFrame_.SatellitesInView[ indexGSV ][ 0 ] = 0;
                gsvFrame_.SatellitesInView[ indexGSV ][ 1 ] = 0;
                gsvFrame_.SatellitesInView[ indexGSV ][ 2 ] = 0;
                gsvFrame_.SatellitesInView[ indexGSV ][ 3 ] = 0;
                indexGSV++;
            }
        }
        gsvFrame_.NumberOfSatellites = nmea0183_.Gsv.NumberOfSatellites;
        gsvFrame_.Totalmessages = nmea0183_.Gsv.Totalmessages;

        for  ( indexGSV=4*(nmea0183_.Gsv.message_number-1); indexGSV<=(4*nmea0183_.Gsv.message_number)-1; indexGSV++ )
        {
            gsvFrame_.SatellitesInView[ indexGSV ][ 0 ] = nmea0183_.Gsv.SatellitesInView[ indexGSV ].SatelliteNumber;
            gsvFrame_.SatellitesInView[ indexGSV ][ 1 ] = nmea0183_.Gsv.SatellitesInView[ indexGSV ].ElevationDegrees;
            gsvFrame_.SatellitesInView[ indexGSV ][ 2 ] = nmea0183_.Gsv.SatellitesInView[ indexGSV ].AzimuthDegreesTrue;
            gsvFrame_.SatellitesInView[ indexGSV ][ 3 ] = nmea0183_.Gsv.SatellitesInView[ indexGSV ].SignalToNoiseRatio;
        }

        break;

    case TRAME_HDT:
        if (!nmea0183_.Hdt.Parse( sentence ))
            qWarning("Failed to parse the frame %s\n",nmea0183_.Hdt.ErrorMessage.toLatin1().data());
        hdtFrame_.DegreesTrue = nmea0183_.Hdt.DegreesTrue;

        break;

    case TRAME_RMC:
        if (!nmea0183_.Rmc.Parse( sentence ))
            qWarning("Failed to parse the frame %s\n",nmea0183_.Rmc.ErrorMessage.toLatin1().data());
        rmcFrame_.H = nmea0183_.Rmc.Time.time().hour();
        rmcFrame_.Mi = nmea0183_.Rmc.Time.time().minute();
        rmcFrame_.S = nmea0183_.Rmc.Time.time().second();
        rmcFrame_.Ms = nmea0183_.Rmc.Time.time().msec();
        rmcFrame_.AA = nmea0183_.Rmc.Time.date().year();
        rmcFrame_.MM = nmea0183_.Rmc.Time.date().month();
        rmcFrame_.JJ = nmea0183_.Rmc.Time.date().day();
        rmcFrame_.lat = Geodesie::Deg2Rad(nmea0183_.Rmc.Position.Latitude.GetDecimalDegrees());
        rmcFrame_.dir_lat = ( (nmea0183_.Rmc.Position.Latitude.Northing == North) ? 'N' : 'S');
        rmcFrame_.lon = Geodesie::Deg2Rad(nmea0183_.Rmc.Position.Longitude.GetDecimalDegrees());
        rmcFrame_.dir_lon = ( (nmea0183_.Rmc.Position.Longitude.Easting == East) ? 'E' : 'W' );
        rmcFrame_.magnet_var = nmea0183_.Rmc.MagneticVariation;
        rmcFrame_.dir_magnet_var = ( (nmea0183_.Rmc.MagneticVariationDirection == East) ? 'E' : 'W');
        rmcFrame_.mode = -1;
        if (nmea0183_.Rmc.ModeIndication == "A")
            rmcFrame_.mode = 1;
        if (nmea0183_.Rmc.ModeIndication == "D")
            rmcFrame_.mode = 2;
        if (nmea0183_.Rmc.ModeIndication == "N")
            rmcFrame_.mode = 0;
        rmcFrame_.track_true_north = nmea0183_.Rmc.TrackMadeGoodDegreesTrue;
        rmcFrame_.valid_data = ( (nmea0183_.Rmc.IsDataValid == True) ? 1 : 0 );
        rmcFrame_.vitesse = nmea0183_.Rmc.SpeedOverGroundKnots * 1852.0 / 3600.0; // 1 knot = 1852 m/h

        break;

    case TRAME_ROT:
        if (!nmea0183_.Rot.Parse( sentence ))
            qWarning("Failed to parse the frame %s\n",nmea0183_.Rot.ErrorMessage.toLatin1().data());
        rotFrame_.RateOfTurn = nmea0183_.Rot.RateOfTurn;
        rotFrame_.valid_data = ( (nmea0183_.Rot.IsDataValid == True) ? 1 : 0 );

        break;

    case TRAME_VTG:
        if (!nmea0183_.Vtg.Parse( sentence ))
            qWarning("Failed to parse the frame %s\n",nmea0183_.Vtg.ErrorMessage.toLatin1().data());
        vtgFrame_.v = nmea0183_.Vtg.SpeedKilometersPerHour;
        vtgFrame_.track_true_north = nmea0183_.Vtg.TrackDegreesTrue;
        vtgFrame_.track_magnet_north = nmea0183_.Vtg.TrackDegreesMagnetic;

        break;

    case TRAME_ZDA:
        if (!nmea0183_.Zda.Parse( sentence ))
            qWarning("Failed to parse the frame %s\n",nmea0183_.Zda.ErrorMessage.toLatin1().data());
        zdaFrame_.H = nmea0183_.Zda.Time.time().hour();
        zdaFrame_.Mi = nmea0183_.Zda.Time.time().minute();
        zdaFrame_.S = nmea0183_.Zda.Time.time().second();
        zdaFrame_.Ms = nmea0183_.Zda.Time.time().msec();
        zdaFrame_.AA = nmea0183_.Zda.Time.date().year();
        zdaFrame_.MM = nmea0183_.Zda.Time.date().month();
        zdaFrame_.JJ = nmea0183_.Zda.Time.date().day();
        zdaFrame_.H_offset = nmea0183_.Zda.LocalHourDeviation;
        zdaFrame_.Mi_offset = nmea0183_.Zda.LocalMinutesDeviation;

        break;

    case TRAME_BESTGPSPOSA:
        stringList = sentence.Sentence.split(";");
        if (stringList.size()==2) {
            header = stringList.at(0);
            data = stringList.at(1);

            if (mVerbose) {
                LOG_DEBUG("Header " << stringList.at(0));
                LOG_DEBUG("Data " << stringList.at(1));
            }

            if (parseCPTbestgpsposa(data)) {
                if (mVerbose) {
                    LOG_DEBUG("parsed TRAME_BESTGPSPOSA");
                }
            }
        }
        break;

    case TRAME_RAWIMUSA:
        stringList = sentence.Sentence.split(";");
        LOG_DEBUG(sentence.Sentence);
        if (stringList.size()==2) {
            header = stringList.at(0);
            data = stringList.at(1);

            if (mVerbose) {
                LOG_DEBUG("Header " << stringList.at(0));
                LOG_DEBUG("Data " << stringList.at(1));
            }

            if (parseCPTrawimusa(data)) {
                if (mVerbose) {
                    LOG_DEBUG("parsed TRAME_RAWIMUSA");
                }
            }
        }
        break;
    case  TRAME_INSPVAA:
        stringList = sentence.Sentence.split(";");
        LOG_DEBUG(sentence.Sentence);
        if (stringList.size()==2) {
            header = stringList.at(0);
            data = stringList.at(1);
            if (mVerbose) {
                LOG_DEBUG("Header " << stringList.at(0));
                LOG_DEBUG("Data " << stringList.at(1));
            }
            if (parseCPTinspvaa(data)) {
                if (mVerbose) {
                    LOG_DEBUG("parsed TRAME_INSPVAA");
                }
            }
        }
        break;

    case TRAME_INSCOV:
        stringList = sentence.Sentence.split(";");
        LOG_DEBUG(sentence.Sentence);
        if (stringList.size()==2) {
            header = stringList.at(0);
            data = stringList.at(1);
            if (mVerbose) {
                LOG_DEBUG("Header " << stringList.at(0));
                LOG_DEBUG("Data " << stringList.at(1));
            }
            if (parseCPTinscov(data)) {
                LOG_DEBUG("parsed TRAME_INSCOV");
            }
        }
        break;

    default:
        LOG_ERROR("unknown frame type=" << type);
        return 0;
    }

    return 1;
}

int CPTComponent::parseCPTbestgpsposa(QString data)
{
    double x=0.0;
    double y=0.0;
    double z=0.0;

    QStringList stringList = data.split(",");
    if (21 == stringList.size()) {
        if (stringList.at(0).compare("SOL_COMPUTED")==0)
            bestgpsposaFrame_.Status = SOL_COMPUTED;
        else if (stringList.at(0).compare("INSUFFICIENT_OBS")==0)
            bestgpsposaFrame_.Status = INSUFFICIENT_OBS;
        else if (stringList.at(0).compare("NO_CONVERGENCE")==0)
            bestgpsposaFrame_.Status = INSUFFICIENT_OBS;
        else if (stringList.at(0).compare("SINGULARITY")==0)
            bestgpsposaFrame_.Status = SINGULARITY;
        else if (stringList.at(0).compare("COV_TRACE ")==0)
            bestgpsposaFrame_.Status = COV_TRACE;
        else if (stringList.at(0).compare("TEST_DIST")==0)
            bestgpsposaFrame_.Status = TEST_DIST;
        else if (stringList.at(0).compare("COLD_START")==0)
            bestgpsposaFrame_.Status = COLD_START;
        else if (stringList.at(0).compare("V_H_LIMIT")==0)
            bestgpsposaFrame_.Status = V_H_LIMIT;
        else if (stringList.at(0).compare("VARIANCE")==0)
            bestgpsposaFrame_.Status = VARIANCE;
        else if (stringList.at(0).compare("RESIDUALS")==0)
            bestgpsposaFrame_.Status = RESIDUALS;
        else if (stringList.at(0).compare("DELTA_POS")==0)
            bestgpsposaFrame_.Status = DELTA_POS;
        else if (stringList.at(0).compare("NEGATIVE_VAR")==0)
            bestgpsposaFrame_.Status = NEGATIVE_VAR;
        else if (stringList.at(0).compare("INTEGRITY_WARNING")==0)
            bestgpsposaFrame_.Status = INTEGRITY_WARNING;
        else if (stringList.at(0).compare("IMU_UNPLUGGED")==0)
            bestgpsposaFrame_.Status = IMU_UNPLUGGED;
        else if (stringList.at(0).compare("PENDING")==0)
            bestgpsposaFrame_.Status = PENDING;
        else {
            LOG_ERROR("cannot parse BESTGPSPOSA");
            return 0;
        }

        if (stringList.at(1).compare("NONE")==0) {
            bestgpsposaFrame_.posType = NONE;
        } else if (stringList.at(1).compare("FIXEDPOS")==0) {
            bestgpsposaFrame_.posType = FIXEDPOS;
        } else if (stringList.at(1).compare("FIXEDHEIGHT")==0) {
            bestgpsposaFrame_.posType = FIXEDHEIGHT;
        } else if (stringList.at(1).compare("FLOATCONV")==0) {
            bestgpsposaFrame_.posType = FLOATCONV;
        } else if (stringList.at(1).compare("WIDELANE")==0) {
            bestgpsposaFrame_.posType = WIDELANE;
        } else if (stringList.at(1).compare("NARROWLANE")==0) {
            bestgpsposaFrame_.posType = NARROWLANE;
        } else if (stringList.at(1).compare("DOPPLER_VELOCITY")==0) {
            bestgpsposaFrame_.posType = DOPPLER_VELOCITY;
        } else if (stringList.at(1).compare("SINGLE")==0) {
            bestgpsposaFrame_.posType = SINGLE;
        } else if (stringList.at(1).compare("PSRDIFF")==0) {
            bestgpsposaFrame_.posType = PSRDIFF;
        } else if (stringList.at(1).compare("WAAS")==0) {
            bestgpsposaFrame_.posType = WAAS;
        } else if (stringList.at(1).compare("PROPAGATED")==0) {
            bestgpsposaFrame_.posType = PROPAGATED;
        } else if (stringList.at(1).compare("OMNISTAR")==0) {
            bestgpsposaFrame_.posType = OMNISTAR;
        } else if (stringList.at(1).compare("L1_FLOAT")==0) {
            bestgpsposaFrame_.posType = L1_FLOAT;
        } else if (stringList.at(1).compare("IONOFREE_FLOAT")==0) {
            bestgpsposaFrame_.posType = IONOFREE_FLOAT;
        } else if (stringList.at(1).compare("NARROW_FLOAT")==0) {
            bestgpsposaFrame_.posType = NARROW_FLOAT;
        } else if (stringList.at(1).compare("L1_INT")==0) {
            bestgpsposaFrame_.posType = L1_INT;
        } else if (stringList.at(1).compare("WIDE_INT")==0) {
            bestgpsposaFrame_.posType = WIDE_INT;
        } else if (stringList.at(1).compare("NARROW_INT")==0) {
            bestgpsposaFrame_.posType = NARROW_INT;
        } else if (stringList.at(1).compare("RTK_DIRECT_INS")==0) {
            bestgpsposaFrame_.posType = RTK_DIRECT_INS;
        } else if (stringList.at(1).compare("INS")==0) {
            bestgpsposaFrame_.posType = INS;
        } else if (stringList.at(1).compare("INS_PSRSP")==0) {
            bestgpsposaFrame_.posType = INS_PSRSP;
        } else if (stringList.at(1).compare("INS_PSRDIFF")==0) {
            bestgpsposaFrame_.posType = INS_PSRDIFF;
        } else if (stringList.at(1).compare("INS_RTKFLOAT")==0) {
            bestgpsposaFrame_.posType = INS_RTKFLOAT;
        } else if (stringList.at(1).compare("INS_RTKFIXED")==0) {
            bestgpsposaFrame_.posType = INS_RTKFIXED;
        } else if (stringList.at(1).compare("INS_OMNISTAR")==0) {
            bestgpsposaFrame_.posType = INS_OMNISTAR;
        } else if (stringList.at(1).compare("INS_OMNISTAR_HP")==0) {
            bestgpsposaFrame_.posType = INS_OMNISTAR_HP;
        } else if (stringList.at(1).compare("INS_OMNISTAR_XP")==0) {
            bestgpsposaFrame_.posType = INS_OMNISTAR_XP;
        } else if (stringList.at(1).compare("OMNISTAR_HP")==0) {
            bestgpsposaFrame_.posType = OMNISTAR_HP;
        } else if (stringList.at(1).compare("OMNISTAR_XP")==0) {
            bestgpsposaFrame_.posType = OMNISTAR_XP;
        } else if (stringList.at(1).compare("CDGPS")==0) {
            bestgpsposaFrame_.posType = CDGPS;
        } else {
            LOG_ERROR("cannot parse BESTGPSPOSA");
            return 0;
        }

        bestgpsposaFrame_.Lat = stringList.at(2).toDouble();
        bestgpsposaFrame_.Lon = stringList.at(3).toDouble();
        bestgpsposaFrame_.Hgt = stringList.at(4).toDouble();
        bestgpsposaFrame_.Undulation = stringList.at(5).toFloat();
        bestgpsposaFrame_.LatStd = stringList.at(7).toFloat();
        bestgpsposaFrame_.LonStd = stringList.at(8).toFloat();
        bestgpsposaFrame_.HgtStd = stringList.at(9).toFloat();

        // Geo to ECEF
        Geodesie::Geographique_2_ECEF(
                    Geodesie::Deg2Rad(bestgpsposaFrame_.Lon), Geodesie::Deg2Rad(bestgpsposaFrame_.Lat), bestgpsposaFrame_.Hgt,
                    x, y, z);
        // ECEF to ENU
        Geodesie::ECEF_2_ENU(x, y, z,
                             bestgpsposaFrame_.e, bestgpsposaFrame_.n, bestgpsposaFrame_.u,
                             Geodesie::Deg2Rad(LON_REF), Geodesie::Deg2Rad(LAT_REF), HE_REF);
        return 1;
    }
    return 0;
}

int CPTComponent::parseCPTrawimusa(QString data)
{
    QStringList stringList = data.split(",");
    QStringList stringList2;
    if (9 == stringList.size()) {
        rawimuFrame_.Week = stringList.at(0).toULong();
        rawimuFrame_.Seconds = stringList.at(1).toDouble();

        rawimuFrame_.ZAccel =  stringList.at(3).toLong();
        rawimuFrame_.YAccel =  stringList.at(4).toLong();
        rawimuFrame_.XAccel =  stringList.at(5).toLong();

        rawimuFrame_.ZGyro = stringList.at(6).toLong();
        rawimuFrame_.YGyro = stringList.at(7).toLong();

        stringList2 = stringList.at(8).split("*");
        if (2 == stringList2.size()) {
            rawimuFrame_.XGyro = stringList2.at(0).toLong();
        }
        return 1;
    }
    return 0;
}

int CPTComponent::parseCPTinspvaa(QString data)
{
    QStringList stringList = data.split(",");
    QStringList stringList2;

    double x=0.0;
    double y=0.0;
    double z=0.0;

    if (12 == stringList.size()) {
        inspvaFrame_.Week = stringList.at(0).toULong();
        inspvaFrame_.Seconds = stringList.at(1).toDouble();
        inspvaFrame_.Lat = stringList.at(2).toDouble();
        inspvaFrame_.Lon = stringList.at(3).toDouble();
        inspvaFrame_.Hgt = stringList.at(4).toDouble();
        inspvaFrame_.NorthVel = stringList.at(5).toFloat();
        inspvaFrame_.EastVel = stringList.at(6).toFloat();
        inspvaFrame_.UpVel = stringList.at(7).toFloat();
        inspvaFrame_.Roll = stringList.at(8).toFloat();
        inspvaFrame_.Pitch = stringList.at(9).toFloat();
        inspvaFrame_.Azimuth = stringList.at(10).toFloat();

        // Geo to ECEF
        Geodesie::Geographique_2_ECEF(
                    Geodesie::Deg2Rad(inspvaFrame_.Lon), Geodesie::Deg2Rad(inspvaFrame_.Lat), inspvaFrame_.Hgt,
                    x, y, z);
        // ECEF to ENU
        Geodesie::ECEF_2_ENU(x, y, z,
                             inspvaFrame_.e, inspvaFrame_.n, inspvaFrame_.u,
                             Geodesie::Deg2Rad(LON_REF), Geodesie::Deg2Rad(LAT_REF), HE_REF);

        stringList2 = stringList.at(11).split("*");
        if (2 == stringList2.size()) {
            if (stringList2.at(0).compare("INS_INACTIVE")==0)
                inspvaFrame_.Status = INS_INACTIVE;
            else if (stringList2.at(0).compare("INS_ALIGNING")==0)
                inspvaFrame_.Status = INS_ALIGNING;
            else if (stringList2.at(0).compare("INS_SOLUTION_NOT_GOOD")==0)
                inspvaFrame_.Status = INS_SOLUTION_NOT_GOOD;
            else if (stringList2.at(0).compare("INS_SOLUTION_GOOD")==0)
                inspvaFrame_.Status = INS_SOLUTION_GOOD;
            else if (stringList2.at(0).compare("INS_BAD_GPS_AGREEMENT")==0)
                inspvaFrame_.Status = INS_BAD_GPS_AGREEMENT;
            else if (stringList2.at(0).compare("INS_ALIGNMENT_COMPLETE")==0)
                inspvaFrame_.Status = INS_ALIGNMENT_COMPLETE;

            return 1;
        }
    }
    return 0;
}

int CPTComponent::parseCPTinscov(QString data)
{
    QStringList stringList = data.split(",");
    QStringList stringList2;
    if (29 == stringList.size()) {
        inscovFrame_.Week = stringList.at(0).toULong();
        inscovFrame_.Seconds = stringList.at(1).toDouble();
        //PosCov
        inscovFrame_.PosCov[0][0]=stringList.at(2).toDouble();
        inscovFrame_.PosCov[0][1]=stringList.at(3).toDouble();
        inscovFrame_.PosCov[0][2]=stringList.at(4).toDouble();

        inscovFrame_.PosCov[1][0]=stringList.at(5).toDouble();
        inscovFrame_.PosCov[1][1]=stringList.at(6).toDouble();
        inscovFrame_.PosCov[1][2]=stringList.at(7).toDouble();

        inscovFrame_.PosCov[2][0]=stringList.at(8).toDouble();
        inscovFrame_.PosCov[2][1]=stringList.at(9).toDouble();
        inscovFrame_.PosCov[2][2]=stringList.at(10).toDouble();
        //AttCov
        inscovFrame_.AttCov[0][0]=stringList.at(11).toDouble();
        inscovFrame_.AttCov[0][1]=stringList.at(12).toDouble();
        inscovFrame_.AttCov[0][2]=stringList.at(13).toDouble();

        inscovFrame_.AttCov[1][0]=stringList.at(14).toDouble();
        inscovFrame_.AttCov[1][1]=stringList.at(15).toDouble();
        inscovFrame_.AttCov[1][2]=stringList.at(16).toDouble();

        inscovFrame_.AttCov[2][0]=stringList.at(17).toDouble();
        inscovFrame_.AttCov[2][1]=stringList.at(18).toDouble();
        inscovFrame_.AttCov[2][2]=stringList.at(19).toDouble();
        //VelCov
        inscovFrame_.VelCov[0][0]=stringList.at(20).toDouble();
        inscovFrame_.VelCov[0][1]=stringList.at(21).toDouble();
        inscovFrame_.VelCov[0][2]=stringList.at(22).toDouble();

        inscovFrame_.VelCov[1][0]=stringList.at(23).toDouble();
        inscovFrame_.VelCov[1][1]=stringList.at(24).toDouble();
        inscovFrame_.VelCov[1][2]=stringList.at(25).toDouble();

        inscovFrame_.VelCov[2][0]=stringList.at(26).toDouble();
        inscovFrame_.VelCov[2][1]=stringList.at(27).toDouble();

        stringList2 = stringList.at(11).split("*");
        if (2 == stringList2.size()) {
            inscovFrame_.VelCov[2][2]=stringList2.at(0).toDouble();
            return 1;
        }
    }
    return 0;
}

void CPTComponent::initBuffer(TimestampedBestgpsposaFrame* a,
                              TimestampedRawimusaFrame* b,
                              TimestampedInspvaaFrame* c,
                              TimestampedInscovFrame* d)
{
    a->time=0;
    a->timerange=0;
    a->frame.Status=INSUFFICIENT_OBS;
    a->frame.posType=NONE;
    a->frame.Lat=0.0;
    a->frame.Lon=0.0;
    a->frame.Hgt=0.0;
    a->frame.Undulation=0.0;
    a->frame.LatStd=0.0;
    a->frame.LonStd=0.0;
    a->frame.HgtStd=0.0;
    a->frame.e=0.0;
    a->frame.n=0.0;
    a->frame.u=0.0;

    b->time=0;
    b->timerange=0;
    b->frame.Week=0;
    b->frame.Seconds=0.0;
    b->frame.ZAccel=0.0;
    b->frame.YAccel=0.0;
    b->frame.XAccel=0.0;
    b->frame.ZGyro=0.0;
    b->frame.YGyro=0.0;
    b->frame.XGyro=0.0;

    c->time=0;
    c->timerange=0;
    c->frame.Week =0;
    c->frame.Seconds=0.0;
    c->frame.Lat=0.0;
    c->frame.Lon=0.0;
    c->frame.Hgt=0.0;
    c->frame.NorthVel=0.0;
    c->frame.EastVel=0.0;
    c->frame.UpVel=0.0;
    c->frame.Roll=0.0;
    c->frame.Pitch=0.0;
    c->frame.Azimuth=0.0;
    c->frame.Status=INS_INACTIVE;
    c->frame.e=0.0;
    c->frame.n=0.0;
    c->frame.u=0.0;

    d->time=0;
    d->timerange=0;
    d->frame.Week=0;
    d->frame.Seconds=0.0;
    for (register int i=0;i<3;i++) {
        for (register int j=0;j<3;j++) {
            d->frame.PosCov[i][j]=0.0;
            d->frame.AttCov[i][j]=0.0;
            d->frame.VelCov[i][j]=0.0;
        }
    }
}

} // namespace pacpus

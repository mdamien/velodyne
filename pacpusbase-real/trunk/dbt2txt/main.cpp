//  created:    2008/3/4 - 11:06
//  modified:	2011/3/22
//  filename:   main.cpp
//
//  author:     Gerald Dherbomez / Bin WANG
//              Copyright Heudiasyc UMR UTC/CNRS 6599
//
//  version:    $Id: $
//
//  purpose:    Conversion from LRC files to DBT files
//              Add the supported LRC types in the lrcTypes.itm file
//

#include "kernel/DbiteException.h"
#include "kernel/DbiteFile.h"
#include "kernel/DbiteFileTypes.h"
#include "kernel/err.h"
#include "kernel/Log.h"
#include "structure/structureXbow.h"
#include "structure/structure_gps.h"
#include "structure/structureCanCarmen.h"
#include "structure/structureCanFluenceZE.h"
#include "structure/structureCanMobileye.h"

#include "extlib/NMEA0183/nmea0183.h"

#include "AlascaConverter.h"
#include "VelodyneConverter.h"
#include "SpanCptConverter.h"

#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <QStringList>
#include <QString>

// FIXME : replace by LOG_DEBUG the std::cout call
#define __VERBOSE__ 1

#ifndef M_PI
#   define M_PI 3.14159265358979323846
#endif // M_PI

using namespace pacpus;
using namespace std;

DECLARE_STATIC_LOGGER("pacpus.base.dbt2txt");

#define ITEM(a) a,

typedef enum {
#   include "dbtTypes.itm"
    DbtTypeEnumSize
} DbtTypeEnum;

#undef ITEM

#define ITEM(a) #a,

const char * const dbtTypesDescription[] = {
#   include "dbtTypes.itm"
};

#undef ITEM

typedef struct
{
    // TODO: int16_t, int16_t ???
  long dataPos;
  int length;
} Stream8Position;

typedef struct
{
  road_time_t t;
  road_timerange_t tr;
  unsigned long length;
  char * data;
} FRAME;

#define UNKNOWN_NMEA_FRAME -1

//////////////////////////////////////////////////////////////////////////
void convert(DbiteConverter & converter, const string & filePath);
std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
std::vector<std::string> split(const std::string &s, char delim);

//////////////////////////////////////////////////////////////////////////
void convert(DbiteConverter & converter, const string & filePath)
{
    // TODO: if no output directory specified
    // result will be put in the subdirectory (named as basename of input file) of the directory where the input file is
    // TODO: parameter
    string outputDirectory = DbiteConverter::getDirname(filePath) + "/" + DbiteConverter::getCompleteBasename(filePath);
    converter.setOutputDirectory(outputDirectory);
    converter.convert(filePath);
}

// utilities
std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while(std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    return split(s, delim, elems);
}

class decodeurSerie
{
public:
  decodeurSerie(void);
  ~decodeurSerie(void) {}

  int analyzeFrame(void);
  int frameType(const QString);
  int decodeFrame(int type);

  QString currentDataFrame;
  road_time_t currentRoadtime;
  road_timerange_t currentTimerange;

  QString frameToDecode;
  road_time_t timeOfFrameToDecode;
  road_timerange_t timerangeOfFrameToDecode;

  QString restOfFrame;

  bool newFrameToDecode;

  bool startOfFrame;
  int  sofIdx_;
  bool endOfFrame;
  int  eofIdx_;

  inline const trame_gga_dbl ggaData(void) {return ggaFrame_;}
  inline const trame_bestgpsposa bestgpsposa(void) {return bestgpsposaFrame_;}
  inline const trame_rawimusa rawimusa(void) {return rawimuFrame_;}
  inline const trame_inspvaa inspvaa(void) {return inspvaFrame_;}
  inline const trame_inscov inscov(void) {return inscovFrame_;}

private:
  int parseCPTbestgpsposa(QString);
  int parseCPTrawimusa(QString);
  int parseCPTinspvaa(QString);
  int parseCPTinscov(QString);

  NMEA0183 nmea0183_;

  //output structures
  trame_gga_dbl ggaFrame_;
  trame_gsa gsaFrame_;
  trame_gst gstFrame_;
  trame_gsv gsvFrame_;
  trame_hdt hdtFrame_;
  trame_rmc rmcFrame_;
  trame_rot rotFrame_;
  trame_vtg vtgFrame_;
  trame_zda zdaFrame_;

  trame_bestgpsposa bestgpsposaFrame_;
  trame_rawimusa    rawimuFrame_;
  trame_inspvaa     inspvaFrame_;
  trame_inscov      inscovFrame_;
};

decodeurSerie::decodeurSerie()
{
  currentDataFrame = "";
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
}

int decodeurSerie::analyzeFrame()
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
    } else {
      restOfFrame = currentDataFrame;
    }
  } else {
    restOfFrame = currentDataFrame;
  }

  if ( (startOfFrame) && (endOfFrame) ) {
    newFrameToDecode = true;
    for (int i = sofIdx_; i < eofIdx_; ++i) {
      frameToDecode += currentDataFrame.at(i);
    }
    for (int j = eofIdx_ + 1; j < currentDataFrame.size(); ++j) {
      restOfFrame += currentDataFrame.at(j);
    }
    //qDebug() << "[Frame:] " << frameToDecode;
  }
  startOfFrame = false;
  endOfFrame = false;
  sofIdx_ =0;
  eofIdx_ =0;

  return 1;
}

int decodeurSerie::frameType(const QString frame)
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
    if ((frame.contains("BESTGPSPOSA", Qt::CaseSensitive))) {
      return TRAME_BESTGPSPOSA;
    } else if ((frame.contains("RAWIMUSA", Qt::CaseSensitive))) {
      return TRAME_RAWIMUSA;
    } else if ((frame.contains("INSPVAA", Qt::CaseSensitive))||(frame.contains("INSPVASA", Qt::CaseSensitive))) {
      return TRAME_INSPVAA;
    } else if ((frame.contains("INSCOVA", Qt::CaseSensitive))||(frame.contains("INSCOVSA", Qt::CaseSensitive))) {
      return TRAME_INSCOV;
    } else {
      return UNKNOWN_NMEA_FRAME;
    }
  }
  return UNKNOWN_NMEA_FRAME;
}

int decodeurSerie::decodeFrame(int type)
{
  double lat_rad = 0, lon_rad = 0;
  int indexGSV = 0;
  int indexGSA = 0;

  SENTENCE sentence;
  sentence.Sentence = frameToDecode;

  QStringList stringList;
  QString header;
  QString data;

    switch(type) {
    case UNKNOWN_NMEA_FRAME:
        LOG_ERROR("Unknown frame received !");
        break;

    case SIGNAL_PPS:
        break;

    case TRAME_GGA_DBL:
  if (sentence.Sentence.contains("PPS", Qt::CaseSensitive)) {
    LOG_WARN("Almanac error on SPAN CPT");
    return -1;
  } else {
    if (!nmea0183_.Gga.Parse(sentence)) {
      LOG_WARN("Failed to parse the frame " << nmea0183_.Gga.ErrorMessage);
    }
    lat_rad = nmea0183_.Gga.Position.Latitude.GetDecimalDegrees()*M_PI/180;
    lon_rad = nmea0183_.Gga.Position.Longitude.GetDecimalDegrees()*M_PI/180;
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

    LOG_INFO("lon=" <<ggaFrame_.lon << "\t" << "lat=" << ggaFrame_.lat);
  }
  break;

case TRAME_GSA:
  if (!nmea0183_.Gsa.Parse(sentence)) {
      LOG_WARN("Failed to parse the frame " << nmea0183_.Gsa.ErrorMessage);
  }
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
  if (!nmea0183_.Gsv.Parse( sentence )) {
    qWarning("Failed to parse the frame %s\n",nmea0183_.Gsv.ErrorMessage.toLatin1().data());
  }
  // it's a new frame, reset stored value in case of the number of satellites
  // in view has decreased
  if (nmea0183_.Gsv.message_number == 1) {
    while (indexGSV < 36) {
      gsvFrame_.SatellitesInView[ indexGSV ][ 0 ] = 0;
      gsvFrame_.SatellitesInView[ indexGSV ][ 1 ] = 0;
      gsvFrame_.SatellitesInView[ indexGSV ][ 2 ] = 0;
      gsvFrame_.SatellitesInView[ indexGSV ][ 3 ] = 0;
      indexGSV++;
    }
  }
  gsvFrame_.NumberOfSatellites = nmea0183_.Gsv.NumberOfSatellites;
  gsvFrame_.Totalmessages = nmea0183_.Gsv.Totalmessages;

  for (indexGSV = 4*(nmea0183_.Gsv.message_number-1); indexGSV <= (4*nmea0183_.Gsv.message_number)-1; ++indexGSV) {
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
  if (!nmea0183_.Rmc.Parse(sentence))
    qWarning("Failed to parse the frame %s\n",nmea0183_.Rmc.ErrorMessage.toLatin1().data());
  rmcFrame_.H = nmea0183_.Rmc.Time.time().hour();
  rmcFrame_.Mi = nmea0183_.Rmc.Time.time().minute();
  rmcFrame_.S = nmea0183_.Rmc.Time.time().second();
  rmcFrame_.Ms = nmea0183_.Rmc.Time.time().msec();
  rmcFrame_.AA = nmea0183_.Rmc.Time.date().year();
  rmcFrame_.MM = nmea0183_.Rmc.Time.date().month();
  rmcFrame_.JJ = nmea0183_.Rmc.Time.date().day();
  rmcFrame_.lat = nmea0183_.Rmc.Position.Latitude.GetDecimalDegrees()*M_PI/180;
  rmcFrame_.dir_lat = ( (nmea0183_.Rmc.Position.Latitude.Northing == North) ? 'N' : 'S');
  rmcFrame_.lon = nmea0183_.Rmc.Position.Longitude.GetDecimalDegrees()*M_PI/180;;
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
    if (parseCPTbestgpsposa(data)) {
      //std::cout << "TRAME_BESTGPSPOSA parsed with checksum: " <<
      //        checksum_xor((unsigned char*)sentence.Sentence.toLatin1().data(),sentence.Sentence.size()) << std::endl;
    }
  } else {
    std::cout << "TRAME_BESTGPSPOSA not complete" << std::endl;
  }
  break;

case TRAME_RAWIMUSA:
  stringList = sentence.Sentence.split(";");
  LOG_DEBUG(sentence.Sentence);
  if (stringList.size()==2) {
    header = stringList.at(0);
    LOG_DEBUG("Header " << stringList.at(0));
    data = stringList.at(1);
    LOG_DEBUG("Data " <<stringList.at(1));
    if (parseCPTrawimusa(data))
      LOG_DEBUG("TRAME_RAWIMUSA parsed");
  }
  break;
case  TRAME_INSPVAA:
  stringList = sentence.Sentence.split(";");
  LOG_DEBUG(sentence.Sentence);
  if (stringList.size()==2) {
    header = stringList.at(0);
    LOG_DEBUG("Header " << stringList.at(0));
    data = stringList.at(1);
    LOG_DEBUG("Data " <<stringList.at(1));
    if (parseCPTinspvaa(data))
      LOG_DEBUG("TRAME_INSPVAA parsed");
  }
  break;
case TRAME_INSCOV:
  stringList = sentence.Sentence.split(";");
  LOG_DEBUG(sentence.Sentence);
  if (stringList.size()==2) {
    header = stringList.at(0);
    LOG_DEBUG("Header " << stringList.at(0));
    data = stringList.at(1);
    LOG_DEBUG("Data " <<stringList.at(1));
    if (parseCPTinscov(data))
      LOG_DEBUG("TRAME_INSCOV parsed");
  }
  break;

default:
  return 0;
  }

  return 1;
}

int decodeurSerie::parseCPTbestgpsposa(QString data)
{
  QStringList stringList = data.split(",");
  if (stringList.size()==21) {
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
    else{
      qWarning("Error during BESTGPSPOSA parsing\n");
      return 0;
    }

    if (stringList.at(1).compare("NONE")==0)
      bestgpsposaFrame_.posType = NONE;
    else if (stringList.at(1).compare("FIXEDPOS")==0)
      bestgpsposaFrame_.posType = FIXEDPOS;
    else if (stringList.at(1).compare("FIXEDHEIGHT")==0)
      bestgpsposaFrame_.posType = FIXEDHEIGHT;
    else if (stringList.at(1).compare("FLOATCONV")==0)
      bestgpsposaFrame_.posType = FLOATCONV;
    else if (stringList.at(1).compare("WIDELANE")==0)
      bestgpsposaFrame_.posType = WIDELANE;
    else if (stringList.at(1).compare("NARROWLANE")==0)
      bestgpsposaFrame_.posType = NARROWLANE;
    else if (stringList.at(1).compare("DOPPLER_VELOCITY")==0)
      bestgpsposaFrame_.posType = DOPPLER_VELOCITY;
    else if (stringList.at(1).compare("SINGLE")==0)
      bestgpsposaFrame_.posType = SINGLE;
    else if (stringList.at(1).compare("PSRDIFF")==0)
      bestgpsposaFrame_.posType = PSRDIFF;
    else if (stringList.at(1).compare("WAAS")==0)
      bestgpsposaFrame_.posType = WAAS;
    else if (stringList.at(1).compare("PROPAGATED")==0)
      bestgpsposaFrame_.posType = PROPAGATED;
    else if (stringList.at(1).compare("OMNISTAR")==0)
      bestgpsposaFrame_.posType = OMNISTAR;
    else if (stringList.at(1).compare("L1_FLOAT")==0)
      bestgpsposaFrame_.posType = L1_FLOAT;
    else if (stringList.at(1).compare("IONOFREE_FLOAT")==0)
      bestgpsposaFrame_.posType = IONOFREE_FLOAT;
    else if (stringList.at(1).compare("NARROW_FLOAT")==0)
      bestgpsposaFrame_.posType = NARROW_FLOAT;
    else if (stringList.at(1).compare("L1_INT")==0)
      bestgpsposaFrame_.posType = L1_INT;
    else if (stringList.at(1).compare("WIDE_INT")==0)
      bestgpsposaFrame_.posType = WIDE_INT;
    else if (stringList.at(1).compare("NARROW_INT")==0)
      bestgpsposaFrame_.posType = NARROW_INT;
    else if (stringList.at(1).compare("RTK_DIRECT_INS")==0)
      bestgpsposaFrame_.posType = RTK_DIRECT_INS;
    else if (stringList.at(1).compare("INS")==0)
      bestgpsposaFrame_.posType = INS;
    else if (stringList.at(1).compare("INS_PSRSP")==0)
      bestgpsposaFrame_.posType = INS_PSRSP;
    else if (stringList.at(1).compare("INS_PSRDIFF")==0)
      bestgpsposaFrame_.posType = INS_PSRDIFF;
    else if (stringList.at(1).compare("INS_RTKFLOAT")==0)
      bestgpsposaFrame_.posType = INS_RTKFLOAT;
    else if (stringList.at(1).compare("INS_RTKFIXED")==0)
      bestgpsposaFrame_.posType = INS_RTKFIXED;
    else if (stringList.at(1).compare("INS_OMNISTAR")==0)
      bestgpsposaFrame_.posType = INS_OMNISTAR;
    else if (stringList.at(1).compare("INS_OMNISTAR_HP")==0)
      bestgpsposaFrame_.posType = INS_OMNISTAR_HP;
    else if (stringList.at(1).compare("INS_OMNISTAR_XP")==0)
      bestgpsposaFrame_.posType = INS_OMNISTAR_XP;
    else if (stringList.at(1).compare("OMNISTAR_HP")==0)
      bestgpsposaFrame_.posType = OMNISTAR_HP;
    else if (stringList.at(1).compare("OMNISTAR_XP")==0)
      bestgpsposaFrame_.posType = OMNISTAR_XP;
    else if (stringList.at(1).compare("CDGPS")==0)
      bestgpsposaFrame_.posType = CDGPS;
    else{
      qWarning("Error during BESTGPSPOSA parsing\n");
      return 0;
    }

    bestgpsposaFrame_.Lat = stringList.at(2).toDouble();
    bestgpsposaFrame_.Lon = stringList.at(3).toDouble();
    bestgpsposaFrame_.Hgt = stringList.at(4).toDouble();
    bestgpsposaFrame_.Undulation = stringList.at(5).toFloat();
    bestgpsposaFrame_.LatStd = stringList.at(7).toFloat();
    bestgpsposaFrame_.LonStd = stringList.at(8).toFloat();
    bestgpsposaFrame_.HgtStd = stringList.at(9).toFloat();
  }
  else
    return 0;
  return 1;

}

int decodeurSerie::parseCPTrawimusa(QString data)
{
  QStringList stringList = data.split(",");
  QStringList stringList2;
  if (stringList.size()==9) {
    rawimuFrame_.Week = stringList.at(0).toULong();
    rawimuFrame_.Seconds = stringList.at(1).toDouble();

    rawimuFrame_.ZAccel =  stringList.at(3).toLong();
    rawimuFrame_.YAccel =  stringList.at(4).toLong();
    rawimuFrame_.XAccel =  stringList.at(5).toLong();

    rawimuFrame_.ZGyro = stringList.at(6).toLong();
    rawimuFrame_.YGyro = stringList.at(7).toLong();

    stringList2 = stringList.at(8).split("*");
    if (stringList2.size()==2) {
      rawimuFrame_.XGyro = stringList2.at(0).toLong();
    }
  }
  else
    return 0;
  return 1;
}

int decodeurSerie::parseCPTinspvaa(QString data)
{
  QStringList stringList = data.split(",");
  QStringList stringList2;
  if (stringList.size()==12) {
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

    stringList2 = stringList.at(11).split("*");
    if (stringList2.size()==2) {
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
    }
    else
      return 0;
    return 1;
  }
  else
    return 0;
}

int decodeurSerie::parseCPTinscov(QString data)
{
  QStringList stringList = data.split(",");
  QStringList stringList2;
  if (stringList.size()==29) {
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
    if (stringList2.size()==2) {
        inscovFrame_.VelCov[2][2]=stringList2.at(0).toDouble();
        return 1;
    }
  }
  return 0;
}

//////////////////////////////////////////////////////////////////////////
/// convert the serial data in text format
void convertSerie(const string & filename)
{
    using namespace std;
  Stream8Position dbtData;

  ifstream dataFile_;
  char *buffer = NULL;

  ofstream txtFile;
  ofstream ggatxtFile;
  int count = 0;

  txtFile.open("Serie.txt", ios::out | ios::trunc);
  if (!txtFile) {
    throw DbiteException("Error while creating TXT file");
  }
  ggatxtFile.open("gga.txt", ios::out | ios::trunc);
  if (!ggatxtFile) {
    throw DbiteException("Error while creating TXT file");
  }

  // create the dbt and the binary files
  DbiteFile dbtFile;
  try {
    dbtFile.open(filename, ReadMode);
  } catch (DbiteException & e) {
    cerr << "Error when opening file: " << filename << endl;
    cerr << "Error: " << e.what() << endl;
    throw e;
  }

  string utcFilename = filename;
  utcFilename.erase(utcFilename.end() - 3, utcFilename.end());
  utcFilename.append("utc");
  cout << utcFilename << "\n";
  dataFile_.open(utcFilename.c_str(), std::ios_base::in | std::ios_base::binary);
  if (!dataFile_) {
    cout << "Error while opening binary file, please press a ENTER to exit\n";
    char c;
    cin >> c;
    ::exit(0);
  }

  txtFile.precision(10);
  ggatxtFile.precision(10);

  //Decoding variables and objects
  FRAME currentFrame;
  decodeurSerie Dec;
  int type = -1;

  road_time_t time;
  road_timerange_t tr;
  for (;;) {
    size_t dataSize = sizeof(dbtData);
    if (!dbtFile.readRecord(time, tr, (char *) &dbtData, dataSize)) {
      break;
    }

    dataFile_.seekg(dbtData.dataPos); // set the get pointer to the correct place
    buffer = new char[dbtData.length+1];
    dataFile_.read(reinterpret_cast<char*>(buffer), dbtData.length); // get the frame .
    buffer[dbtData.length] = '\0'; // add a \0 to convert for the conversion in QString

    currentFrame.length = dbtData.length+1;
    currentFrame.t = time;
    currentFrame.tr= tr;
    currentFrame.data = new char[dbtData.length+1];
    memcpy(currentFrame.data, buffer, dbtData.length+1);
    //std::cout << "[Frame] " << currentFrame.data << std::endl;

    Dec.currentDataFrame = currentFrame.data;
    Dec.currentRoadtime  = currentFrame.t;
    Dec.currentTimerange = currentFrame.tr;

    if (__VERBOSE__) {
      cout << count++ << " ";
    }
    //qDebug() << "[QString] "<< Dec.currentDataFrame << "[length]: " << Dec.currentDataFrame.length();

    Dec.analyzeFrame();

    if (Dec.newFrameToDecode) {
      // a new complete frame is arrived
      type = Dec.frameType(Dec.frameToDecode);

      txtFile <<
        Dec.timeOfFrameToDecode << " " <<
        Dec.timerangeOfFrameToDecode << " " <<
        Dec.frameToDecode.toLatin1().data();
      if (type != -1) {
        if (Dec.decodeFrame(type) == -1)
          qWarning("Failed to decode the dataframe\n");
        else{
          switch(type)
          {
          case TRAME_GGA_DBL:
            ggatxtFile <<
              Dec.ggaData().Ms << " " <<
              Dec.ggaData().lat<< " " <<
              Dec.ggaData().lon<< " " <<
              Dec.ggaData().ind_qualite << "\n";
            break;
          case TRAME_BESTGPSPOSA:
            std::cout << "[SPAN-BESTGPSPOSA] Lat: " << Dec.bestgpsposa().Lat <<
              " Lon: " << Dec.bestgpsposa().Lon <<
              " Hgt: " << Dec.bestgpsposa().Hgt << std::endl;
            break;
          case TRAME_RAWIMUSA:
            std::cout << "[SPAN-RAWIMUSA]"<< std::endl;
            break;
          case TRAME_INSPVAA:
            std::cout << "[SPAN-INSPVAA] Lat: " << Dec.inspvaa().Lat <<
              " Lon: " << Dec.inspvaa().Lon <<
              " Roll: "<< Dec.inspvaa().Roll <<
              " Pitch: " << Dec.inspvaa().Azimuth << std::endl;
            break;
          case TRAME_INSCOV:
            std::cout << "[SPAN-INSCOV] CovXX: " << Dec.inscov().PosCov[0][0] <<
              " CovYY: " << Dec.inscov().PosCov[1][1] <<
              " CovZZ: "<< Dec.inscov().PosCov[2][2] << std::endl;
            break;
          default:
            break;
          }
        }
      }

      type = -1;
      Dec.newFrameToDecode = false;
      Dec.frameToDecode = "";
    }

    delete[] buffer;
    delete[] currentFrame.data;
    cout << endl;

  } // END   WHILE (!EOF)

  dataFile_.close();
  txtFile.close();
  ggatxtFile.close();
  dbtFile.close();
}

//////////////////////////////////////////////////////////////////////////
// convert the NMEA GGA DBT data in text format
// columns; timestamp PC, H, Mi, S, Ms, nb_sat, ind_qualite, age, hdop, lon (rad), lat (rad), alt_msl, d_geoidal, dir_lat, dir_lon, ref_station_ID
//////////////////////////////////////////////////////////////////////////
void convertGGA(const string & filename)
{
  trame_gga_dbl dbtData;
  std::ofstream txtFile;
  road_time_t time;
  road_timerange_t tr;
  int count = 0;

  txtFile.open("GGA.txt",ios::out|ios::trunc);
  if (!txtFile) {
    cout << "Error while creating TXT file\n enter a key to exit\n";
    char c;
    cin >> c;
    ::exit(0);
  }

  // create the dbt and the binary files
  DbiteFile dbtFile;
  dbtFile.open(filename, ReadMode);
  if (!dbtFile.isOpen()) {
    cout << "Error while opening DBT file\n enter a key to exit\n";
    char c;
    cin >> c;
    ::exit(0);
  }

  txtFile.precision(10);

  for (;;) {
    size_t dataSize = sizeof(dbtData);
    if (!dbtFile.readRecord(time, tr, reinterpret_cast<char *>(&dbtData), dataSize)) {
      break;
    }

    if (__VERBOSE__)
      cout << count++ << " ";
    txtFile <<
      time << " " <<
      dbtData.H << " " <<
      dbtData.Mi <<  " " <<
      dbtData.S <<  " " <<
      dbtData.Ms <<  " " <<
      dbtData.nb_sat <<  " " <<
      dbtData.ind_qualite <<  " " <<
      dbtData.age <<  " " <<
      dbtData.hdop <<  " " <<
      dbtData.lon <<  " " <<
      dbtData.lat <<  " " <<
      dbtData.alt_msl <<  " " <<
      dbtData.d_geoidal <<  " " <<
      dbtData.dir_lat <<  " " <<
      dbtData.dir_lon <<  " " <<
      dbtData.ref_station_ID <<  " " <<
      endl;

    if (__VERBOSE__)
      cout << "lon = " << dbtData.lon << "\t" << "lat = " << dbtData.lat << "\n";
  }

  txtFile.close();
  dbtFile.close();
}

//////////////////////////////////////////////////////////////////////////
// convert the NMEA GST DBT data in text format
// columns; timestamp PC,a,b,rms,phi,sigma_lat,sigma_lon,sigma_alt,H,Mi,S,Ms
//////////////////////////////////////////////////////////////////////////
void convertGST(const string & filename)
{
  trame_gst dbtData;
  std::ofstream txtFile;
  road_time_t time;
  road_timerange_t tr;
  int count = 0;

  txtFile.open("GST.txt",ios::out|ios::trunc);
  if (!txtFile)
  {
    cout << "Error while creating TXT file\n enter a key to exit\n";
    char c;
    cin >> c;
    ::exit(0);
  }

  // create the dbt and the binary files
  DbiteFile dbtFile;
  dbtFile.open(filename, ReadMode);
  if (!dbtFile.isOpen()) {
    cout << "Error while opening DBT file\n enter a key to exit\n";
    char c;
    cin >> c;
    ::exit(0);
  }

  for (;;) {
    size_t dataSize = sizeof(dbtData);
    if (!dbtFile.readRecord(time, tr, reinterpret_cast<char *>(&dbtData), dataSize)) {
      break;
    }

    if (__VERBOSE__)
      cout << count++ << " ";
    txtFile <<
      time << " " <<
      dbtData.a << " " <<
      dbtData.b <<  " " <<
      dbtData.rms <<  " " <<
      dbtData.phi <<  " " <<
      dbtData.sigma_lat <<  " " <<
      dbtData.sigma_lon <<  " " <<
      dbtData.sigma_alt <<  " " <<
      dbtData.H <<    " " <<
      dbtData.Mi <<  " " <<
      dbtData.S <<  " " <<
      dbtData.Ms <<  " " <<
      endl;

  }

  txtFile.close();
  dbtFile.close();
}

//////////////////////////////////////////////////////////////////////////
// convert the NMEA VTG DBT data in text format
// columns; timestamp PC, v(m/s), track_true_north, track_magnet_north
//////////////////////////////////////////////////////////////////////////
void convertVTG(const string & filename)
{
  trame_vtg dbtData;
  road_time_t time;
  road_timerange_t tr;
  int count = 0;

  std::ofstream txtFile;
  txtFile.open("VTG.txt",ios::out|ios::trunc);
  if (!txtFile) {
    cout << "Error while creating TXT file\n enter a key to exit\n";
    char c;
    cin >> c;
    ::exit(0);
  }

  // create the dbt and the binary files
  DbiteFile dbtFile;
  dbtFile.open(filename, ReadMode);
  if (!dbtFile.isOpen()) {
    cout << "Error while opening DBT file\n enter a key to exit\n";
    char c;
    cin >> c;
    ::exit(0);
  }

  for (;;) {
    size_t dataSize = sizeof(dbtData);
    if (!dbtFile.readRecord(time, tr, reinterpret_cast<char *>(&dbtData), dataSize)) {
      break;
    }

    if (__VERBOSE__)
      cout << count++ << " ";
    txtFile <<
      time << " " <<
      dbtData.v << " " <<
      dbtData.track_true_north <<  " " <<
      dbtData.track_magnet_north <<  " " <<
      endl;

  } // END   WHILE (!EOF)

  txtFile.close();
  dbtFile.close();
}

//////////////////////////////////////////////////////////////////////////
// convert the NMEA GSV DBT data in text format
// columns; timestamp PC, NumberOfSatellites, Totalmessages, + 36 x (SatelliteNumber, ElevationDegrees, AzimuthDegreesTrue, SignalToNoiseRatio)
//////////////////////////////////////////////////////////////////////////
void convertGSV(const string & filename)
{
  trame_gsv dbtData;
  std::ofstream txtFile;
  road_time_t time;
  road_timerange_t tr;
  int count = 0;

  txtFile.open("GSV.txt",ios::out|ios::trunc);
  if (!txtFile) {
    cout << "Error while creating TXT file\n enter a key to exit\n";
    char c;
    cin >> c;
    ::exit(0);
  }

  // create the dbt and the binary files
  DbiteFile dbtFile;
  dbtFile.open(filename, ReadMode);
  if (!dbtFile.isOpen()) {
    cout << "Error while opening DBT file\n enter a key to exit\n";
    char c;
    cin >> c;
    ::exit(0);
  }

  for (;;) {
    size_t dataSize = sizeof(dbtData);
    if (!dbtFile.readRecord(time, tr, reinterpret_cast<char *>(&dbtData), dataSize)) {
      break;
    }

    if (__VERBOSE__)
      cout << count++ << " ";
    txtFile <<
      time << " " <<
      dbtData.NumberOfSatellites << " " <<
      dbtData.Totalmessages <<  " ";
    for (int i=0 ; i < 36 ; ++i) {
      txtFile <<
        dbtData.SatellitesInView[i][0] <<  " " <<
        dbtData.SatellitesInView[i][1] <<  " " <<
        dbtData.SatellitesInView[i][2] <<  " " <<
        dbtData.SatellitesInView[i][3] <<  " ";
    }
    txtFile << endl;
  }

  txtFile.close();
  dbtFile.close();
}

//////////////////////////////////////////////////////////////////////////
// convert the NMEA ZDA DBT data in text format
// columns; timestamp PC,H,Mi,S,Ms,JJ,MM,AA,H_offset,Mi_offset
//////////////////////////////////////////////////////////////////////////
void convertZDA(const string & filename)
{
  trame_zda dbtData;
  std::ofstream txtFile;
  road_time_t time;
  road_timerange_t tr;
  int count = 0;

  txtFile.open("ZDA.txt", ios::out | ios::trunc);
  if (!txtFile) {
    cout << "Error while creating TXT file\n enter a key to exit\n";
    char c;
    cin >> c;
    ::exit(0);
  }

  // create the dbt and the binary files
  DbiteFile dbtFile;
  dbtFile.open(filename, ReadMode);
  if (!dbtFile.isOpen()) {
    cout << "Error while opening DBT file\n enter a key to exit\n";
    char c;
    cin >> c;
    ::exit(0);
  }

  for (;;) {
    size_t dataSize = sizeof(dbtData);
    if (!dbtFile.readRecord(time, tr, reinterpret_cast<char *>(&dbtData), dataSize)) {
      break;
    }

    if (__VERBOSE__)
      cout << count++ << " ";
    txtFile <<
      time << " " <<
      dbtData.H << " " <<
      dbtData.Mi <<  " " <<
      dbtData.S <<  " " <<
      dbtData.Ms <<  " " <<
      dbtData.JJ <<  " " <<
      dbtData.MM <<  " " <<
      dbtData.AA <<  " " <<
      dbtData.H_offset <<  " " <<
      dbtData.Mi_offset <<  " " <<
      endl;
  }

  txtFile.close();
  dbtFile.close();
}

//////////////////////////////////////////////////////////////////////////
// convert the VG700 DBT data in text format
// columns; timestamp PC, acceleros (X, Y, Z), gyros (X, Y, Z), roulis, tangage
//////////////////////////////////////////////////////////////////////////
void convertVG700(const string & filename)
{
  VG700dataframe dbtData;
  std::ofstream txtFile;
  road_time_t time;
  road_timerange_t tr;
  int count = 0;

  txtFile.open("VG700.txt", ios::out | ios::trunc);
  if (!txtFile) {
    cout << "Error while creating TXT file\n enter a key to exit\n";
    char c;
    cin >> c;
    ::exit(0);
  }

  // create the dbt and the binary files
  DbiteFile dbtFile;
  dbtFile.open(filename, ReadMode);
  if (!dbtFile.isOpen()) {
    cout << "Error while opening DBT file\n enter a key to exit\n";
    char c;
    cin >> c;
    ::exit(0);
  }

  for (;;) {
    size_t dataSize = sizeof(dbtData);
    if (!dbtFile.readRecord(time, tr, reinterpret_cast<char *>(&dbtData), dataSize)) {
      break;
    }

    if (__VERBOSE__) {
      cout << count++ << " ";
    }
    txtFile <<
      dbtData.message_time << " " <<
      dbtData.accelX <<  " " <<
      dbtData.accelY <<  " " <<
      dbtData.accelZ <<  " " <<
      dbtData.rollRate <<  " " <<
      dbtData.pitchRate <<  " " <<
      dbtData.yawRate <<  " " <<
      dbtData.rollAngle <<    " " <<
      dbtData.pitchAngle <<  " " <<
      endl;

    // dataFile.write(reinterpret_cast<char*>(&(utcMagicWord)), sizeof(int32_t));
  }

  txtFile.close();
  dbtFile.close();
}

#define MAX_CHAR_PICTURE_NAME		  64
#define MAX_CHAR_DIRECTORY_NAME		64

//////////////////////////////////////////////////////////////////////////
/// convert the Image DBT data in text format
/// columns: timestamp PC, image name
void convertImage320x240_24bits(const string & filename)
{
    const string LineCommentCharacter = "#";
    const string PortableGraymapBinaryMagicCode = "P5";
    const string PortablePixmapBinaryMagicCode = "P6";
    const int widthInPixels = 320;
    const int heightInPixels = 240;
    const int maximumColorValue = 255;
    const int bitsPerPixel = 24;
    const int bytesPerPixel = bitsPerPixel / 8;
    char dbtData[widthInPixels * heightInPixels * bytesPerPixel];

  ofstream txtFile;
  
  string directory = filename.substr(0, filename.find_last_of( '.' ));

  txtFile.open("ImageIndex.txt",ios::out|ios::trunc);
  if (!txtFile) {
    throw DbiteException("Error while creating TXT file");
  }

  // create the dbt and the binary files
  DbiteFile dbtFile;
  dbtFile.open(filename, ReadMode);
  if (!dbtFile.isOpen()) {
    throw DbiteException("Error while opening DBT file");
  }
  
  // loop over all lines (image file paths)
  int imageCounter = 0;
  road_time_t time;
  road_timerange_t tr;
  for (;;) {
    size_t dataSize = sizeof(dbtData);
    if (!dbtFile.readRecord(time, tr, reinterpret_cast<char *>(&dbtData), dataSize)) {
      break;
    }

    if (__VERBOSE__) {
      cout << imageCounter++ << " ";
    }

    stringstream imageNameSs;
    imageNameSs << directory << "/" << "image" << imageCounter << ".ppm";
    string imageName = imageNameSs.str();
    txtFile <<
      time << " " <<
      imageName <<  " " <<
      "\n";

    ofstream imageFile(imageName.c_str(), ios::binary);
    // magic number, whitespace
    imageFile << PortablePixmapBinaryMagicCode << "\n";
    // line comment, title
    imageFile << LineCommentCharacter << " " << imageName << "\n";
    // width, whitespace, height, whitespace
    imageFile << widthInPixels << " " << heightInPixels << "\n";
    // maximum color value, whitespace
    imageFile << maximumColorValue << "\n";
    // write 320*240*3 bytes from data buffer to image file
    imageFile.write(dbtData, sizeof(int8_t) * widthInPixels * heightInPixels * bytesPerPixel);
    // data
    imageFile.close();

    //FILE * ptf = fopen(imageName,"wb");
    //fprintf(ptf,"P5\n");
    //fprintf(ptf,"%d %d\n",320,240);
    //fprintf(ptf,"255\n");
    //// write 320*240*3 bytes from dbtData to ptf
    //fwrite(dbtData, sizeof(int8_t), 320*240*3, ptf);
    //fclose(ptf);
  }

  txtFile.close();
  dbtFile.close();
}

//////////////////////////////////////////////////////////////////////////
// convert the Image DBT data in text format
// columns: timestamp PC, image name
//////////////////////////////////////////////////////////////////////////
void convertImageIndexFile(string filename)
{
    ofstream txtFile;
    road_time_t time;
    road_timerange_t tr;
    char imageName[MAX_CHAR_PICTURE_NAME+MAX_CHAR_DIRECTORY_NAME];
    int imageCounter = 0;

    txtFile.open("ImageIndex.txt", ios::out | ios::trunc);
    if (!txtFile) {
        cout << "Error while creating TXT file\n enter a key to exit\n";
        char c;
        cin >> c;
        ::exit(0);
    }

    // create the dbt and the binary files
    DbiteFile dbtFile;
    dbtFile.open(filename, ReadMode);
    if (!dbtFile.isOpen()) {
        cout << "Error while opening DBT file\n enter a key to exit\n";
        char c;
        cin >> c;
        ::exit(0);
    }

    for (;;) {
        size_t dataSize = sizeof(imageName);
        if (!dbtFile.readRecord(time, tr, reinterpret_cast<char *>(&imageName), dataSize)) {
            break;
        }

        if (__VERBOSE__) {
            cout << imageCounter++ << " ";
        }

        txtFile
            << time << " "
            << imageName << " "
            << "\n";
    }

    txtFile.close();
    dbtFile.close();
}

/************************** CAN frame**************************/

//////////////////////////////////////////////////////////////////////////
// convert the wheel speed data in text format
// columns; timestamp PC, frontWheelsSpeed, rearLeftWheelSpeed, rearRightWheelSpeed, rpmFrontWheels
//////////////////////////////////////////////////////////////////////////
void convertWheelspeed(string filename)
{
  StructWheelSpeed dbtData;
  std::ofstream txtFile;
  road_time_t time;
  road_timerange_t tr;
  int count = 0;

  txtFile.open("WheelSpeed.txt",ios::out|ios::trunc);
  if (!txtFile) {
    cout << "Error while creating TXT file\n enter a key to exit\n";
    char c;
    cin >> c;
    ::exit(0);
  }

  // create the dbt and the binary files
  DbiteFile dbtFile;
  dbtFile.open(filename, ReadMode);
  if (!dbtFile.isOpen()) {
    cout << "Error while opening DBT file\n enter a key to exit\n";
    char c;
    cin >> c;
    ::exit(0);
  }

  for (;;) {
    size_t dataSize = sizeof(dbtData);
    if (!dbtFile.readRecord(time, tr, reinterpret_cast<char *>(&dbtData), dataSize)) {
      break;
    }

    if (__VERBOSE__) {
      cout << count++ << " ";
    }
    txtFile <<
      time << " " <<
      dbtData.frontWheelsSpeed <<  " " <<			// mean speed of the front wheels (in km/h)
      dbtData.rearLeftWheelSpeed <<  " " <<	    // speed of the rear left wheel (in km/h)
      dbtData.rearRightWheelSpeed <<  " " <<		// speed of the rear right wheel (in km/h)
      dbtData.rpmFrontWheels <<  " " <<			// mean rpm of the front wheels (in tr/min)
      endl;
  }

  txtFile.close();
  dbtFile.close();
}

//////////////////////////////////////////////////////////////////////////
/// convert the Carmen_rawcan DBT data in text format
/// columns; tempstamp PC,
void convertCarmen_rawcan(string filename)
{
  CanFrame dbtData;
  std::ofstream txtFile;
  road_time_t time;
  road_timerange_t tr;

  txtFile.open("Carmen_rawcan.txt",ios::out|ios::trunc);
  if (!txtFile) {
    cout << "Error while creating TXT file\n enter a key to exit\n";
    char c;
    cin >> c;
    ::exit(-1);
  }

  // create the dbt and the binary files
  DbiteFile dbtFile;
  dbtFile.open(filename, ReadMode);
  if (!dbtFile.isOpen()) {
    cout << "Error while opening DBT file\n enter a key to exit\n";
    char c;
    cin >> c;
    ::exit(-1);
  }

  for (;;) {
    size_t dataSize = sizeof(dbtData);
    if (!dbtFile.readRecord(time, tr, reinterpret_cast<char *>(&dbtData), dataSize)) {
      break;
    }

    stringstream bufferIdSs;
    bufferIdSs << "0x" << hex << setfill('0') << setw(1) << dbtData.id;
    const char * bufferID = bufferIdSs.str().c_str();

    stringstream bufferDlcSs;
    bufferDlcSs << dbtData.dlc;
    const char * bufferDLC = bufferDlcSs.str().c_str();

    stringstream bufferDataSs;
    for (int i = 0; i < dbtData.dlc; i++) {
        bufferDataSs << "0x" << hex << setfill('0') << setw(1) << dbtData.data[i] << " ";
    }
    const char * bufferDATA = bufferDataSs.str().c_str();

    //if (dbtData.id == 0x739) {
    /*
    cout << "id = ";
    cout << bufferID;
    cout << ", len = ";
    cout << bufferDLC;
    cout << ", data = ";
    cout << bufferDATA;
    cout << ",flags = 0, timestamp = ";
    cout << time << endl;
    */
    if (__VERBOSE__) {
      cout << ".";
    }
    txtFile <<

      "id = " <<
      bufferID <<
      ", len = " <<
      bufferDLC <<
      ", data = " <<
      bufferDATA <<
      ",flags = 0, timestamp = " <<
      time <<
      endl;

  }

  txtFile.close();
  dbtFile.close();
}

//////////////////////////////////////////////////////////////////////////
// convert the Lateral Dynamics DBT data in text format
// columns; timestamp PC,yawRate, latAcc, brakePressure,braking,perfLatAccSens,perfYawRateSens,latAccUncert,yawRateUncert,
//          brakeContactHS,brakeContact,muSplitSituation,stopEmissionBicapReq
//////////////////////////////////////////////////////////////////////////
void convertLat_dyn(string filename)
{
  StructLateralDynamics dbtData;
  std::ofstream txtFile;
  road_time_t time;
  road_timerange_t tr;
  int count = 0;

  txtFile.open("Lat_dyn.txt",ios::out|ios::trunc);
  if (!txtFile) {
    cout << "Error while creating TXT file\n enter a key to exit\n";
    char c;
    cin >> c;
    ::exit(0);
  }

  // create the dbt and the binary files
  DbiteFile dbtFile;
  dbtFile.open(filename, ReadMode);
  if (!dbtFile.isOpen()) {
    cout << "Error while opening DBT file\n enter a key to exit\n";
    char c;
    cin >> c;
    ::exit(0);
  }

  for (;;) {
    size_t dataSize = sizeof(dbtData);
    if (!dbtFile.readRecord(time, tr, reinterpret_cast<char *>(&dbtData), dataSize)) {
      break;
    }

    if (__VERBOSE__) {
      cout << count++ << " ";
    }
    txtFile <<
      time << " " <<
      dbtData.yawRate << " " <<					// >0 in trigonometric direction in deg/s
      dbtData.latAcc <<  " " <<					// >0 to the right in m/s2
      dbtData.brakePressure <<  " " <<			// master cylinder pressure in bar
      dbtData.braking <<  " " <<					// 2 bits
      dbtData.perfLatAccSens <<  " " <<			// ?
      dbtData.perfYawRateSens <<  " " <<			// ?
      dbtData.latAccUncert <<  " " <<				// ?
      dbtData.yawRateUncert <<  " " <<			// ?
      dbtData.brakeContactHS <<  " " <<			// ?
      dbtData.brakeContact <<  " " <<				// ?
      dbtData.muSplitSituation <<  " " <<			// ?
      dbtData.stopEmissionBicapReq <<  " " <<		// ?
      endl;
  }

  txtFile.close();
  dbtFile.close();
}

//////////////////////////////////////////////////////////////////////////
// convert the Odometry DBT data in text format
// columns; timestamp PC,vehicleSpeed, distance, longitudinalAcc
//////////////////////////////////////////////////////////////////////////
void convertOdometry(string filename)
{
  StructVehicleSpeed dbtData;
  std::ofstream txtFile;
  road_time_t time;
  road_timerange_t tr;
  int count = 0;

  txtFile.open("Odometry.txt",ios::out|ios::trunc);
  if (!txtFile) {
    cout << "Error while creating TXT file\n enter a key to exit\n";
    char c;
    cin >> c;
    ::exit(0);
  }

  // create the dbt and the binary files
  DbiteFile dbtFile;
  dbtFile.open(filename, ReadMode);
  if (!dbtFile.isOpen()) {
    cout << "Error while opening DBT file\n enter a key to exit\n";
    char c;
    cin >> c;
    ::exit(0);
  }

  for (;;) {
    size_t dataSize = sizeof(dbtData);
    if (!dbtFile.readRecord(time, tr, reinterpret_cast<char *>(&dbtData), dataSize)) {
      break;
    }

    if (__VERBOSE__) {
      cout << count++ << " ";
    }
    txtFile <<
      time << " " <<
      dbtData.vehicleSpeed << " " <<		// vehicle speed in km/h (referenced to the wheels)
      dbtData.distance <<  " " <<			// odometer in m (referenced to the wheels). Internally coded as integer 16 bits.
      //Roll over to 0 when value reachs FFFFh (6553.5m to be verified experimentally).
      dbtData.longitudinalAcc <<  " " <<	// longitudinal acceleration in m/s2 (referenced to the wheels)
      endl;

  }

  txtFile.close();
  dbtFile.close();
}

//////////////////////////////////////////////////////////////////////////
// convert the Steering Wheel DBT data in text format
// columns; timestamp PC,angle,rate,optRate,errorCode,trim,calibration,sensorState,checksum
//////////////////////////////////////////////////////////////////////////
void convertSteering_wheel(string filename)
{
  StructSteeringWheel dbtData;
  std::ofstream txtFile;
  road_time_t time;
  road_timerange_t tr;
  int count = 0;

  txtFile.open("Steering_wheel.txt",ios::out|ios::trunc);
  if (!txtFile) {
    cout << "Error while creating TXT file\n enter a key to exit\n";
    char c;
    cin >> c;
    ::exit(0);
  }

  // create the dbt and the binary files
  DbiteFile dbtFile;
  dbtFile.open(filename, ReadMode);
  if (!dbtFile.isOpen()) {
    cout << "Error while opening DBT file\n enter a key to exit\n";
    char c;
    cin >> c;
    ::exit(0);
  }

  for (;;) {
    size_t dataSize = sizeof(dbtData);
    if (!dbtFile.readRecord(time, tr, reinterpret_cast<char *>(&dbtData), dataSize)) {
      break;
    }

    if (__VERBOSE__) {
      cout << count++ << " ";
    }
    txtFile <<
      time << " " <<
      dbtData.angle << " " <<			// in deg - >0 in trigonometric direction (to the left)
      dbtData.rate << " " <<			// in deg/s
      dbtData.optRate << " " <<		// in deg/s optimized rotation rate of the steering wheel
      dbtData.errorCode << " " <<		// error code - 4 bits
      dbtData.trim << " " <<			// trim must be at 1, if 0 don't use angle and rate
      dbtData.calibration << " " <<   // calibration
      dbtData.sensorState << " " <<	// sensor state
      dbtData.checksum << " " <<		// checksum - 4 bits
      endl;
  }

  txtFile.close();
  dbtFile.close();
}

//////////////////////////////////////////////////////////////////////////
// convert the synchro GPS from NMEA ZDA
// columns; timestamp PC,
//////////////////////////////////////////////////////////////////////////
void convertSynchroGps(string filename)
{
  GpsSynchroFrame dbtData;
  std::ofstream txtFile;
  road_time_t time;
  road_timerange_t tr;
  int count = 0;

  txtFile.open("synchro_gps.txt",ios::out|ios::trunc);
  if (!txtFile) {
    cout << "Error while creating TXT file\n enter a key to exit\n";
    char c;
    cin >> c;
    ::exit(0);
  }

  // create the dbt and the binary files
  DbiteFile dbtFile;
  dbtFile.open(filename, ReadMode);
  if (!dbtFile.isOpen()) {
    cout << "Error while opening DBT file\n enter a key to exit\n";
    char c;
    cin >> c;
    ::exit(0);
  }

  for (;;) {
    size_t dataSize = sizeof(dbtData);
    if (!dbtFile.readRecord(time, tr, reinterpret_cast<char *>(&dbtData), dataSize)) {
      break;
    }

    if (__VERBOSE__) {
      cout << count++ << " ";
    }

    txtFile <<
      //cout <<
      time << " " <<
      dbtData.ppsTime << " " <<
      dbtData.zdaTime << " " <<
      dbtData.timeOffset << " " <<
      dbtData.zda.H << " " <<
      dbtData.zda.Mi <<  " " <<
      dbtData.zda.S <<  " " <<
      dbtData.zda.Ms <<  " " <<
      dbtData.zda.JJ <<  " " <<
      dbtData.zda.MM <<  " " <<
      dbtData.zda.AA <<  " " <<
      dbtData.zda.H_offset <<  " " <<
      dbtData.zda.Mi_offset <<  " " <<
      endl;
  }

  txtFile.close();
  dbtFile.close();
}

//////////////////////////////////////////////////////////////////////////
// convert the PPS signal
// columns: timestamp PC,
//////////////////////////////////////////////////////////////////////////
void convertPPS(string filename)
{
  int dbtData;
  std::ofstream txtFile;
  road_time_t time;
  road_timerange_t tr;
  int count = 0;

  txtFile.open("gps_pps.txt",ios::out|ios::trunc);
  if (!txtFile) {
    cout << "Error while creating TXT file\n enter a key to exit\n";
    char c;
    cin >> c;
    ::exit(0);
  }

  // create the dbt and the binary files
  DbiteFile dbtFile;
  dbtFile.open(filename, ReadMode);
  if (!dbtFile.isOpen()) {
    cout << "Error while opening DBT file\n enter a key to exit\n";
    char c;
    cin >> c;
    ::exit(0);
  }

  for (;;) {
    size_t dataSize = sizeof(dbtData);
    if (!dbtFile.readRecord(time, tr, reinterpret_cast<char *>(&dbtData), dataSize)) {
      break;
    }

    if (__VERBOSE__) {
      cout << count++ << " ";
    }
    txtFile <<
      //cout <<
      time << " " <<
      dbtData <<
      endl;
  }

  txtFile.close();
  dbtFile.close();
}

//////////////////////////////////////////////////////////////////////////
// convert
// columns: timestamp PC,
//////////////////////////////////////////////////////////////////////////
void convertFluenceLowSpeed(string filename)
{
  StructFluenceZeLowSpeed dbtData;
  std::ofstream txtFile;
  road_time_t time;
  road_timerange_t tr;
  int count = 0;

  txtFile.open("fluence_lowspeed.txt",ios::out|ios::trunc);
  if (!txtFile) {
    cout << "Error while creating TXT file\n enter a key to exit\n";
    char c;
    cin >> c;
    ::exit(0);
  }

  // create the dbt and the binary files
  DbiteFile dbtFile;
  dbtFile.open(filename, ReadMode);
  if (!dbtFile.isOpen()) {
    cout << "Error while opening DBT file\n enter a key to exit\n";
    char c;
    cin >> c;
    ::exit(0);
  }

  for (;;) {
    size_t dataSize = sizeof(dbtData);
    if (!dbtFile.readRecord(time, tr, reinterpret_cast<char *>(&dbtData), dataSize)) {
      break;
    }

    if (__VERBOSE__) {
      cout << count++ << " ";
    }
    txtFile <<
      //cout <<
      time << " " <<
      dbtData.accurateOdometer << " " <<
      dbtData.vehicleSpeed << " " <<
      endl;
  }

  txtFile.close();
  dbtFile.close();
}

//////////////////////////////////////////////////////////////////////////
// convert
// columns: timestamp PC,
//////////////////////////////////////////////////////////////////////////
void convertFluenceFrontWheelspeed(string filename)
{
  StructFluenceZeFrontWheelSpeed dbtData;
  std::ofstream txtFile;
  road_time_t time;
  road_timerange_t tr;
  int count = 0;

  txtFile.open("fluence_front_wheelspeed.txt",ios::out|ios::trunc);
  if (!txtFile) {
    cout << "Error while creating TXT file\n enter a key to exit\n";
    char c;
    cin >> c;
    ::exit(0);
  }

  // create the dbt and the binary files
  DbiteFile dbtFile;
  dbtFile.open(filename, ReadMode);
  if (!dbtFile.isOpen()) {
    cout << "Error while opening DBT file\n enter a key to exit\n";
    char c;
    cin >> c;
    ::exit(0);
  }

  for (;;) {
    size_t dataSize = sizeof(dbtData);
    if (!dbtFile.readRecord(time, tr, reinterpret_cast<char *>(&dbtData), dataSize)) {
      break;
    }

    if (__VERBOSE__) {
      cout << count++ << " ";
    }
    txtFile <<
      //cout <<
      time << " " <<
      dbtData.averageFrontWheelSpeed << " " <<
      dbtData.frontLeftWheelSpeed << " " <<
      dbtData.frontRightWheelSpeed << " " <<
      endl;
  }

  txtFile.close();
  dbtFile.close();
}

//////////////////////////////////////////////////////////////////////////
// convert
// columns: timestamp PC,
//////////////////////////////////////////////////////////////////////////
void convertFluenceRearWheelspeed(string filename)
{
  StructFluenceZeRearWheelSpeed dbtData;
  std::ofstream txtFile;
  road_time_t time;
  road_timerange_t tr;
  int count = 0;

  txtFile.open("fluence_rear_wheelspeed.txt",ios::out|ios::trunc);
  if (!txtFile) {
    cout << "Error while creating TXT file\n enter a key to exit\n";
    char c;
    cin >> c;
    ::exit(0);
  }

  // create the dbt and the binary files
  DbiteFile dbtFile;
  dbtFile.open(filename, ReadMode);
  if (!dbtFile.isOpen()) {
    cout << "Error while opening DBT file\n enter a key to exit\n";
    char c;
    cin >> c;
    ::exit(0);
  }

  for (;;) {
    size_t dataSize = sizeof(dbtData);
    if (!dbtFile.readRecord(time, tr, reinterpret_cast<char *>(&dbtData), dataSize)) {
      break;
    }

    if (__VERBOSE__) {
      cout << count++ << " ";
    }
    txtFile <<
      //cout <<
      time << " " <<
      dbtData.fourWheelReferenceSpeed << " " <<
      dbtData.rearLeftWheelSpeed << " " <<
      dbtData.rearRightWheelSpeed << " " <<
      endl;
  }

  txtFile.close();
  dbtFile.close();
}


//////////////////////////////////////////////////////////////////////////
// convert
// columns: timestamp PC,
//////////////////////////////////////////////////////////////////////////
void convertFluenceGears(string filename)
{
  StructFluenceZeGears dbtData;
  std::ofstream txtFile;
  road_time_t time;
  road_timerange_t tr;
  int count = 0;

  txtFile.open("fluence_gears.txt",ios::out|ios::trunc);
  if (!txtFile) {
    cout << "Error while creating TXT file\n enter a key to exit\n";
    char c;
    cin >> c;
    ::exit(0);
  }

  // create the dbt and the binary files
  DbiteFile dbtFile;
  dbtFile.open(filename, ReadMode);
  if (!dbtFile.isOpen()) {
    cout << "Error while opening DBT file\n enter a key to exit\n";
    char c;
    cin >> c;
    ::exit(0);
  }

  for (;;) {
    size_t dataSize = sizeof(dbtData);
    if (!dbtFile.readRecord(time, tr, reinterpret_cast<char *>(&dbtData), dataSize)) {
      break;
    }

    if (__VERBOSE__) {
      cout << count++ << " ";
    }
    txtFile <<
      //cout <<
      time << " " <<
      (unsigned int)(dbtData.position) << " " <<
      endl;
  }

  txtFile.close();
  dbtFile.close();
}

//////////////////////////////////////////////////////////////////////////
// convert
// columns: timestamp PC,
//////////////////////////////////////////////////////////////////////////
void convertFluenceKinematics(string filename)
{
  StructFluenceZeKinematics dbtData;
  std::ofstream txtFile;
  road_time_t time;
  road_timerange_t tr;
  int count = 0;

  txtFile.open("fluence_kinematics.txt",ios::out|ios::trunc);
  if (!txtFile) {
    cout << "Error while creating TXT file\n enter a key to exit\n";
    char c;
    cin >> c;
    ::exit(0);
  }

  // create the dbt and the binary files
  DbiteFile dbtFile;
  dbtFile.open(filename, ReadMode);
  if (!dbtFile.isOpen()) {
    cout << "Error while opening DBT file\n enter a key to exit\n";
    char c;
    cin >> c;
    ::exit(0);
  }

  for (;;) {
    size_t dataSize = sizeof(dbtData);
    if (!dbtFile.readRecord(time, tr, reinterpret_cast<char *>(&dbtData), dataSize)) {
      break;
    }

    if (__VERBOSE__) {
      cout << count++ << " ";
    }
    txtFile <<
      //cout <<
      time << " " <<
      dbtData.longitudinalAccProc << " " <<
      dbtData.transversalAcc << " " <<
      dbtData.yawRate << " " <<
      endl;
  }

  txtFile.close();
  dbtFile.close();
}

//////////////////////////////////////////////////////////////////////////
// convert
// columns: timestamp PC,
//////////////////////////////////////////////////////////////////////////
void convertFluenceSteeringWheel(string filename)
{
  StructFluenceZeSteeringWheel dbtData;
  std::ofstream txtFile;
  road_time_t time;
  road_timerange_t tr;
  int count = 0;

  txtFile.open("fluence_steeringwheel.txt", ios::out | ios::trunc);
  if (!txtFile) {
    cout << "Error while creating TXT file\n enter a key to exit\n";
    char c;
    cin >> c;
    ::exit(0);
  }

  // create the dbt and the binary files
  DbiteFile dbtFile;
  dbtFile.open(filename, ReadMode);
  if (!dbtFile.isOpen()) {
    cout << "Error while opening DBT file\n enter a key to exit\n";
    char c;
    cin >> c;
    ::exit(0);
  }

  for (;;) {
    size_t dataSize = sizeof(dbtData);
    if (!dbtFile.readRecord(time, tr, reinterpret_cast<char *>(&dbtData), dataSize)) {
      break;
    }

    if (__VERBOSE__) {
      cout << count++ << " ";
    }

    txtFile <<
      //cout <<
      time << " " <<
      dbtData.angle << " " <<
      dbtData.angleOffset << " " <<
      dbtData.rotationSpeed << " " <<
      "\n";
  }

  txtFile.close();
  dbtFile.close();
}

//////////////////////////////////////////////////////////////////////////
// convert Mobileye obstacles
//
// description of the 82 columns:
// --------------------------------
//
// timestamp PC, obstacleCount,
// 10 x ( obstacle_id, obstacle_status, obstacle_type, obstacle_x, obstacle_y, obstacle_age, obstacle_width ),
// rightLane_Conf, rightLane_Curvature, rightLane_Heading, rightLane_Offset, rightLane_Valid,
// leftLane_Conf, leftLane_Curvature, leftLane_Heading, leftLane_Offset, leftLane_Valid
//
//////////////////////////////////////////////////////////////////////////
void convertMobileyeObstacles(string filename)
{
  MobileyeDatas dbtData;
  std::ofstream txtFile;
  road_time_t time;
  road_timerange_t tr;
  int count = 0;

  txtFile.open("mobileye_obstacles.txt", ios::out | ios::trunc);
  if (!txtFile) {
    cout << "Error while creating TXT file\n enter a key to exit\n";
    char c;
    cin >> c;
    ::exit(0);
  }

  // create the dbt and the binary files
  DbiteFile dbtFile;
  dbtFile.open(filename, ReadMode);
  if (!dbtFile.isOpen()) {
    cout << "Error while opening DBT file\n enter a key to exit\n";
    char c;
    cin >> c;
    ::exit(0);
  }

  // print header
  cout << (string)dbtFile;

  for (;;) {
    //size_t dataSize = sizeof(dbtData);
    if (!dbtFile.readRecord(time, tr, reinterpret_cast<char *>(&dbtData)/*, dataSize*/)) {
      break;
    }

    if (__VERBOSE__) {
      cout << count++ << " " << time << " " /*<< dataSize << " "*/;
    }

    txtFile <<
      time << " " <<
      dbtData.obstaclesHeader.obstacleCount << " ";
    if (__VERBOSE__)
      cout << "nb obstacles : " << dbtData.obstaclesHeader.obstacleCount << endl;
    for (int i = 0 ; i < MOBILEYE_MAX_OBSTACLE_COUNT ; ++i) {
      txtFile <<
        dbtData.obstacles1[i].id << " " <<
        dbtData.obstacles1[i].status << " " <<
        dbtData.obstacles1[i].type << " " <<
        dbtData.obstacles1[i].x << " " <<
        dbtData.obstacles1[i].y << " " <<
        dbtData.obstacles2[i].age << " " <<
        dbtData.obstacles2[i].width << " ";
    }
    txtFile <<
      dbtData.rightLane.LaneConf << " " <<
      dbtData.rightLane.LaneCurvature << " " <<
      dbtData.rightLane.LaneHeading << " " <<
      dbtData.rightLane.LaneOffset << " " <<
      dbtData.rightLane.LaneValid << " " <<
      dbtData.leftLane.LaneConf << " " <<
      dbtData.leftLane.LaneCurvature << " " <<
      dbtData.leftLane.LaneHeading << " " <<
      dbtData.leftLane.LaneOffset << " " <<
      dbtData.leftLane.LaneValid << " " <<
      endl;
  }

  txtFile.close();
  dbtFile.close();
}

//////////////////////////////////////////////////////////////////////////
// convert Mobileye lanes
//
// description of the columns:
// --------------------------------
//
// timestamp PC, LaneCurvatureC2, LaneCurvatureDerivC3, LaneDegree, LanePositionC0, LaneQuality, LaneType, TimeStamp (lane part1), LaneHeadingC1, TimeStamp (lane part 2)
//
//////////////////////////////////////////////////////////////////////////
void convertMobileyeLanes(string filename)
{
  MobileyeLaneData dbtData;
  ofstream txtFile;
  road_time_t time;
  road_timerange_t tr;
  int count = 0;

  // extract name of the dbt file
  string filenameOut;
  if ( (filename.find("\\")!=string::npos) && (filename.find("/")!=string::npos) ) {
    cout << "Please check the path entered as argument, it contains \\ and / characters! \n enter a key to exit\n";
    char c;
    cin >> c;
    ::exit(0);
  }
  std::vector<std::string> list;
  if ( filename.find("\\") != string::npos )
    list = split(filename, '\\');
  else
    list = split(filename, '/');

  filenameOut = split(list.back(), '.').front() + ".txt";


  // open TXT file to output
  txtFile.open(filenameOut.c_str(),ios::out|ios::trunc);
  if (!txtFile) {
    cout << "Error while creating TXT file\n enter a key to exit\n";
    char c;
    cin >> c;
    ::exit(0);
  }

  // create the dbt and the binary files
  DbiteFile dbtFile;
  dbtFile.open(filename, ReadMode);
  if (!dbtFile.isOpen()) {
    cout << "Error while opening DBT file\n enter a key to exit\n";
    char c;
    cin >> c;
    ::exit(0);
  }

  // print header
  cout << (string) dbtFile;

  for (;;) {
    //size_t dataSize = sizeof(dbtData);
    if (!dbtFile.readRecord(time, tr, reinterpret_cast<char *>(&dbtData)/*, dataSize*/)) {
      break;
    }

    if (__VERBOSE__)
      cout << count++ << " " << time << " " /*<< dataSize << " "*/;

    txtFile <<
      time << " " <<
      dbtData.LanePart1.LaneCurvatureC2 << " " <<
      dbtData.LanePart1.LaneCurvatureDerivC3 << " " <<
      dbtData.LanePart1.LaneDegree << " " <<
      dbtData.LanePart1.LanePositionC0 << " " <<
      dbtData.LanePart1.LaneQuality << " " <<
      dbtData.LanePart1.LaneType << " " <<
      dbtData.LanePart1.TimeStamp << " " <<
      dbtData.LanePart2.LaneHeadingC1 << " " <<
      dbtData.LanePart2.TimeStamp << " " <<
      endl;
  }

  txtFile.close();
  dbtFile.close();
}

#include "structure/structure_IGN.h"

//////////////////////////////////////////////////////////////////////////
/// Converts Applanix data
///
/// Converts Applanix data into text format.
///
/// Columns:
/// --------------------------------
/// timestamp, ---timerange, ---timestamp GPS,
/// distance,
/// latitude, longitude, height, roll, pitch, yaw (heading)
/// speed East, speed North, speed Up
/// stddev(speed East), stddev(speed North), stddev(speed Up)
/// stddev( roll), stddev(pitch), stddev(yaw (heading))
///
//////////////////////////////////////////////////////////////////////////
void convertApplanix(const string & filename)
{
    // open output TXT file
    ofstream txtFile;
    txtFile.open("applanix.txt", ios::out | ios::trunc);
    if (!txtFile) {
        cout << "Error while creating TXT file\n enter a key to exit\n";
        char c;
        cin >> c;
        ::exit(-1);
    }

    // open input DBT file
    DbiteFile dbtFile;
    dbtFile.open(filename, ReadMode);
    if (!dbtFile.isOpen()) {
        cout << "Error while opening DBT file\n enter a key to exit\n";
        char c;
        cin >> c;
        ::exit(-2);
    }

    // read all records
    assert(152 == sizeof(ApplanixPoint));
    ApplanixPoint dbtData;
    road_time_t time;
    road_timerange_t tr;
    for (;;) {
        if (!dbtFile.readRecord(time, tr, reinterpret_cast<char *>(&dbtData)/*, dataSize*/)) {
            break;
        }
        txtFile
            << setprecision(0)
            << dbtData.time << "\t"
            //<< dbtData.timerange << "\t"

            << fixed << setprecision(6)
            //<< dbtData.timeGPS << "\t"
            << dbtData.distance << "\t"

            << dbtData.lat << "\t"
            << dbtData.lon << "\t"
            << dbtData.hElipsoid << "\t"

            << dbtData.rouli << "\t"
            << dbtData.tangage << "\t"
            << dbtData.cap << "\t"

            << dbtData.vitesseXENU << "\t"
            << dbtData.vitesseYENU << "\t"
            << dbtData.vitesseZENU << "\t"

            << dbtData.SDVitesseXENU << "\t"
            << dbtData.SDVitesseYENU << "\t"
            << dbtData.SDVitesseZENU << "\t"
            << dbtData.SDrouli << "\t"
            << dbtData.SDtangage << "\t"
            << dbtData.SDcap << "\t"
            << "\n"
            ;
    }

    txtFile.close();
    dbtFile.close();
}

//////////////////////////////////////////////////////////////////////////
void usage()
{
    cout << "Usage: dbt2txt <Dbite file path> <data type>\n";
    cout << "Supported Dbite data types:\n";
    for (int dbtTypeItem = 0; dbtTypeItem < DbtTypeEnumSize; ++dbtTypeItem) {
        cout << "\t" << dbtTypeItem << "\t:\t" << dbtTypesDescription[dbtTypeItem] << "\n";
    }
}

//////////////////////////////////////////////////////////////////////////
int main(int argc, char * argv[])
{
    LOG_DEBUG("argc = " << argc);
    if (argc < 3) {
        LOG_ERROR("not enough input arguments");
        usage();
        return EXIT_FAILURE;
    }
    string dbtFilename = argv[1];
    LOG_INFO("input file: '" << dbtFilename << "'");
    int dbtType = atoi(argv[2]);
    LOG_INFO("data type: " << dbtType);
    
    //////////////////////////////////////////////////////////////////////////
    // Big switch
    switch (dbtType) {
    case DbtApplanix:
        convertApplanix(dbtFilename);
        break;

    case DbtVG700:
        convertVG700(dbtFilename);
        break;

    case DbtGGA:
        convertGGA(dbtFilename);
        break;

    case DbtGST:
        convertGST(dbtFilename);
        break;

    case DbtVTG:
        convertVTG(dbtFilename);
        break;

    case DbtGSV:
        convertGSV(dbtFilename);
        break;

    case DbtZDA:
        convertZDA(dbtFilename);
        break;

    case DbtImage320x240_24bits:
        convertImage320x240_24bits(dbtFilename);
        break;

    case DbtWheelspeed:
        convertWheelspeed(dbtFilename);
        break;

    case DbtCarmen_rawcan:
        convertCarmen_rawcan(dbtFilename);
        break;

    case DbtLat_dyn:
        convertLat_dyn(dbtFilename);
        break;

    case DbtOdometry:
        convertOdometry(dbtFilename);
        break;

    case DbtSteering_wheel:
        convertSteering_wheel(dbtFilename);
        break;

    case DbtSerie:
        convertSerie(dbtFilename);
        break;

    case DbtSpanCpt:
        {
            SpanCptConverter conv;
            convert(conv, dbtFilename);
        }
        break;

    ////////////////////////////////////////
    // LIDARs
    case DbtAlasca:
        {
            AlascaConverter conv;
            convert(conv, dbtFilename);
        }
        break;
    case DbtVelodyne:
        {
            VelodyneConverter conv;
            convert(conv, dbtFilename);
        }
        break;

    ////////////////////////////////////////
    case ImageIndex:
        convertImageIndexFile(dbtFilename);
        break;

    case SynchroGPS:
        convertSynchroGps(dbtFilename);
        break;

    case DbtPPS:
        convertPPS(dbtFilename);
        break;

    case DbtFluenceLowSpeed:
        convertFluenceLowSpeed(dbtFilename);
        break;

    case DbtFluenceFrontWheelspeed:
        convertFluenceFrontWheelspeed(dbtFilename);
        break;

    case DbtFluenceRearWheelspeed:
        convertFluenceRearWheelspeed(dbtFilename);
        break;

    case DbtFluenceGears:
        convertFluenceGears(dbtFilename);
        break;

    case DbtFluenceKinematics:
        convertFluenceKinematics(dbtFilename);
        break;

    case DbtFluenceSteeringWheel:
        convertFluenceSteeringWheel(dbtFilename);
        break;

    case DbtMobileyeObstacles:
        convertMobileyeObstacles(dbtFilename);
        break;

    case DbtMobileyeLanes:
        convertMobileyeLanes(dbtFilename);
        break;

    default:
        LOG_ERROR("unknown data type");
        usage();
        return EXIT_FAILURE;
    }

    LOG_INFO("end of conversion from DBT to TXT");
}

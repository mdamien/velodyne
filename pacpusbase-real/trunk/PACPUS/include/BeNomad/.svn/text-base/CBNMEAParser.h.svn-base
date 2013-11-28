/*==========================================================  (-*- C++ -*-)
 *
 * @file CBNMEAParser.h 
 * 
 * @version  $Id: CBNMEAParser.h,v 1.2 2004/10/31 15:09:20 wkunkel Exp $ 
 * 
 * @author  William Kunkel
 *
 * @copyright  (c) 2002-2004 BeNomad S.A.R.L., All Rights Reserved
 *
 * BeNomad confidential file protected by international copyright laws
 * UNAUTHORIZED ACCESS, USE, REPRODUCTION OR DISTRIBUTION IS PROHIBITED.
 *
 *========================================================================*/

#ifndef _CBNMEA_PARSER_H_
#define _CBNMEA_PARSER_H_

/*!
  @file CBNMEAParser.h
	CBNMEAParser class definition.
*/

#include "BTypes.h"
#include "CBDateTime.h"

// Forward declarations
class CBStream;
class CBSerialLink;
class CBNMEAParserImp;


/**
 * @enum EB_LINK_STATUS
 * Defines the possible status of the link to the serial device.
 */
typedef enum {
  EB_DEVICE_CONNECTED,      //!< Device not connected
  EB_DEVICE_DISCONNECTED,   //!< Device disconnected
  EB_DEVICE_NOT_RESPONDING  //!< Device is not responding
} EB_LINK_STATUS;


/**
 * @struct TB_GPS_POS_INFO
 * A structure that contains real-time information related to the 
 * geographical position sent by a GPS receiver.
 */
typedef struct {  
  TBuint8          mSatUsed;    //!< Number of satellites being tracked
  TB_3D_LONGPOINT  mPos;        //!< The long/lat coodinates in SVS units and altitude in meters.
  TBfloat          mSpeed;      //!< Ground speed in km/h
  TBfloat          mAngle;      //!< Track angle in degrees 
  TBfloat          mPDOP;       //!< Position dilution of precision
  TBfloat          mHDOP;       //!< Horizontal dilution of precision
  TBfloat          mVDOP;       //!< Vertical dilution of precision
  CBDateTime       mLastUpdate; //!< Date and time of the last update
  EB_LINK_STATUS   mLinkStatus; //!< The current status of the connection to the serial device.
} TB_GPS_POS_INFO;


#define KB_MAX_GPS_CHANNELS  12   //!< Maximum number of channels

/**
 * @struct TB_SATELLITES_INFO
 * A structure that contains real-time information related to
 * satellite positions and status.
 */
typedef struct {  
  TBuint8          mInView;                         //!< Number of satellites in view
  TBuint8          mPRN[KB_MAX_GPS_CHANNELS];       //!< PRN of satellite   
  TBuint8          mElevation[KB_MAX_GPS_CHANNELS]; //!< Elevation of satellite 
  TBuint16         mAzimuth[KB_MAX_GPS_CHANNELS];	  //!< Azimuth
  TBuint8          mSNR[KB_MAX_GPS_CHANNELS];		    //!< Signal strength 
  CBDateTime       mLastUpdate;  //!< Date and time of the last update
  EB_LINK_STATUS   mLinkStatus;  //!< The current status of the connection to the serial device.  
} TB_SATELLITES_INFO;

/**
 * @class CBNMEAParser
 * Defines a parser of generic NMEA 0183 sentences such as GGA, GLL, GSA, 
 * GSV, RMC and VTG.
 */
class BNAV_EXPORT CBNMEAParser
{
public:
  /**
   * @enum EB_NMEA_VER
   * Defines the supported NMEA 0183 versions.
   */
  enum EB_NMEA_VER { 
    NMEA_V2_2, //!< Specifies the NMEA 0183 v2.2 protocol.
    NMEA_V2_3  //!< Specifies the NMEA 0183 v2.3 protocol.
  };

  /**
   * Constructs a new CBNMEAParser for parsing NMEA 0183 sentences sent by
   * a serial communication device (a GPS receiver).
   * @param inLink Defines the link to the serial communication device from
   * which comes NMEA sentences (The given CBSerial instance will be deleted 
   * by the NMEA Parser).
   * @param inNMEAVersion The NMEA 0183 version compatibility.   
   * @param inGeoScale The scale of the geographical position.     
   */
  CBNMEAParser(CBSerialLink * inLink, 
               EB_NMEA_VER    inNMEAVersion = NMEA_V2_2,
               TBuint32       inGeoScale    = 100000);

  /**
   * Destructor.
   */
  ~CBNMEAParser(void);

  /**
   * Starts the parsing process of NMEA sentences within another thread of execution.
   * This method returns immediately if the NMEA Parser can not establish a serial
   * connection to GPS device (or simulator) caused by a hardware error or a bad 
   * configuration (device disconnected, invalid serial port, etc.).
   * @param inOutStream An optional output stream which may be used to record all 
   * NMEA sentences.
   * @return \c true if the method succeeds, \c false otherwise.
   */
  TBbool Start(CBStream * inOutStream = NULL);

  /**
   * Stops the NMEA Parser.
   */
  TBbool Stop(void);

  /**
   * Indicates whether this NMEA parser is running or not.
   */
  TBbool IsRunning(void) const;

  /**
   * Returns a Thread-safe copy of the TB_GPS_INFO data.
   */
  TB_GPS_POS_INFO GetGPSInfo(void);

  /**
   * Returns a Thread-safe copy of the TB_SATELLITES_INFO data.
   */
  TB_SATELLITES_INFO GetSatInfo(void);


private:
  // Disable copy
  CBNMEAParser(const CBNMEAParser&);
  CBNMEAParser & operator=(const CBNMEAParser&);

private:
  CBNMEAParserImp * mImp;
};

#endif /* _CBNMEA_PARSER_H_ */

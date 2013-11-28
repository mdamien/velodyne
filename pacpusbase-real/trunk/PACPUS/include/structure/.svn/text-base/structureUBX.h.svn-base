#ifndef _UBX_structures_Ublox_H
#define _UBX_structures_Ublox_H

#define MAX_SBAS_SV 24
#define NB_CHANNEL 16

namespace Ublox{

/*! \struct structRAW_SV
  * \brief Structure containing measurement from the GPS receiver for each satellite 
  *	\author "Olivier Le Marchand"
  *	\version 0.1
  *	\date February 2008
  *
  * Ublox receiver realize several measures for each satellite, and provide it
  * through the RXM-RAW message. All the measures for one satellite are grouped 
  * in this structure\n
 *	Protocols definitions are available in the following document : \n
 *	Title:     ANTARIS Positioning Engine  \n
 *	Subtitle:  NMEA and UBX Protocol Specification  \n
 *	Doc Type:  Specification  \n
 *	Doc ID:    GPS.G3-X-03002-D \n 
 *	Firmware:  Version 5.00
 */
struct structRAW_SV
{
	//! Carrier Phase measurement (L1 Cycles)
	double CPMes;

	//! Pseudorange measurement (m)
	double PRMes;

	//! Doppler Measurement (Hz)
	float DOMes;		

	//! Satellite number
	unsigned char SV;	

	//! Nav measurement Quality indicator
	char MesQI;			

	//! Signal Strength (dBHz)
	char CNO;	
	
	//! Loss of Lock indicator
	unsigned char LLI;	
};


/*! \struct structSBAS_SV
 *  \brief Structure containing the SBAS correction data for one satellite 
 *	\author "Olivier Le Marchand"
 *	\version 0.1
 *	\date February 2008
 *
 *	Protocols definitions are available in the following document : \n
 *	Title:     ANTARIS Positioning Engine  \n
 *	Subtitle:  NMEA and UBX Protocol Specification  \n
 *	Doc Type:  Specification  \n
 *	Doc ID:    GPS.G3-X-03002-D \n 
 *	Firmware:  Version 5.00
 */
struct structSBAS_SV
{
	//!SV Id
	unsigned char SVID;

	//!Flags for this SV 
	unsigned char flags;

	//!Monitoring status
	unsigned char UDRE;

	//!System (WAAS/EGNOS/...) same as sys
	unsigned char SYSn;

	//!Services available sames sevices
	unsigned char serviceN;

	//!reserved
	unsigned char res0;

	//!Pseudo Range correction in [cm] 
	signed short PRC;

	//!reserved
	signed short res1;

	//!Ionosphere correction in [cm] 
	signed short IC;

};



/*! \struct structRXM_RAW
  * \brief Structure containing all the measurement from the GPS receiver at one epoch 
  *	\author "Olivier Le Marchand"
  *	\version 0.1
  *	\date February 2008
  *
  * Ublox receiver realize several measures for each satellite, and provide it
  * through the RXM-RAW message. All the measures for all satellites are grouped 
  * in this structure in order to pass all throw a RTMaps wire\n
 *	Protocols definitions are available in the following document : \n
 *	Title:     ANTARIS Positioning Engine  \n
 *	Subtitle:  NMEA and UBX Protocol Specification  \n
 *	Doc Type:  Specification  \n
 *	Doc ID:    GPS.G3-X-03002-D
  */
struct structRXM_RAW
{
	//! Measurement in ms GPS time  of Week
	long ITOW;	

	//! Measurement GPS Week numbers
	short Week;		

	//! number of Satellite in the frame
	unsigned char NSV;	

	/*! \brief measurement for each satellite */
	/*! the size of the array is 16, because hte ublox receiver we have can't track 
	more than 16 satellites*/
	structRAW_SV tabRAW_SV[NB_CHANNEL]; 

};

/*! \struct structRXM_SFRB
 * \brief Structure containing of one single frame buffer
 *	\author "Olivier Le Marchand"
 *	\version 0.1
 *	\date February 2008
 *
 * \n
 *	Protocols definitions are available in the following document : \n
 *	Title:     ANTARIS Positioning Engine  \n
 *	Subtitle:  NMEA and UBX Protocol Specification  \n
 *	Doc Type:  Specification  \n
 *	Doc ID:    GPS.G3-X-03002-D
  */
struct structRXM_SFRB
{
	//! Channel number
	unsigned char CHN;

	//!ID of the satellite transmitting the subframe
	unsigned char SVID;

	//array of ten words of data
	unsigned long int DWRD[10];
};


/*! \struct structNAV_CLOCK
 * \brief Structure containing the estimation of the clock bias and the clock drift
 *	\author "Olivier Le Marchand"
 *	\version 0.1
 *	\date February 2008
 *
 * \n
 *	Protocols definitions are available in the following document : \n
 *	Title:     ANTARIS Positioning Engine  \n
 *	Subtitle:  NMEA and UBX Protocol Specification  \n
 *	Doc Type:  Specification  \n
 *	Doc ID:    GPS.G3-X-03002-D
  */
struct structNAV_CLOCK
{
	//!GPS Millisecond Time of week (ms)
	unsigned long ITOW;     
	
	//!clock bias in nanoseconds
	long CLKB;    
	
	//!clock drift in nanoseconds per second
	long CLKD;
	
	//!Time Accuracy Estimate
	unsigned long TAcc;
	
	//!Frequency Accuracy Estimate
	unsigned long FAcc;

};

/*! \struct structNAV_SBAS
 * \brief Structure containing the status of the SBAS system and corrections
 *	\author "Olivier Le Marchand"
 *	\version 0.1
 *	\date February 2008
 *
 * \n
 *	Protocols definitions are available in the following document : \n
 *	Title:     ANTARIS Positioning Engine  \n
 *	Subtitle:  NMEA and UBX Protocol Specification  \n
 *	Doc Type:  Specification  \n
 *	Doc ID:    GPS.G3-X-03002-D
  */
struct structNAV_SBAS
{
	//!GPS Millisecond time of week
	unsigned long ITOW;

	//!PRN Number of the GEO where correction and integrity data is used from 
	unsigned char GEO;

	//!SBAS Mode | 0 Disabled | 1 Enabled Integrity | 3 Enabled Testmode 
	unsigned char mode;

	//!SBAS System (WAAS/EGNOS/...)  | -1 Unknown | 0 WAAS | 1 EGNOS | 2 MSAS | 16 GPS 
	signed char sys;

	//!SBAS Services available  | bit0 Ranging | bit1 Corrections | bit2 Integrity | bit3 Testmode |
	unsigned char service;

	//!Number of SV data following 
	unsigned char CNT;

	//!Reserved
	unsigned char res[3];

	structSBAS_SV tabSBAS_SV[MAX_SBAS_SV];

};

/*! \struct structNAV_SOL
 * \brief Structure containing the position and velocity estimation in the ECEF reference frame
 *	\author "Olivier Le Marchand"
 *	\version 0.1
 *	\date February 2008
 *
 * \n
 *	Protocols definitions are available in the following document : \n
 *	Title:     ANTARIS Positioning Engine  \n
 *	Subtitle:  NMEA and UBX Protocol Specification  \n
 *	Doc Type:  Specification  \n
 *	Doc ID:    GPS.G3-X-03002-D
  */
struct structNAV_SOL
{
	//!GPS Millisecond Time of Week
	unsigned long ITOW;
	
	//!Nanoseconds remainder of rounded ms above, range -500000 .. 500000
	long Frac;
	
	//!GPS week (GPS time) 
	short week;
	
	//!GPSfix Type, range 0..4  | 0x00 = No Fix | 0x01 = Dead Reckoning only | 0x02 = 2D-Fix | 0x03 = 3D-Fix | 0x04 = GPS + dead reckoning combined | 0x05 = Time only fix | 0x06..0xff: reserved | 
	unsigned char GPSfi;
	
	//!0x01=GPSfixOK (i.e. within DOP & ACC Masks) | 0x02=DiffSoln (is DGPS used) | 0x04=WKNSET (is Week Number valid) | 0x08=TOWSET (is Time of Week valid) | 0x?0=reserved
	unsigned char Flags;
	
	//!ECEF X coordinate (cm)
	long ECEF_X;
	
	//!ECEF Y coordinate (cm)
	long ECEF_Y;
	
	//!ECEF Z coordinate (cm)
	long ECEF_Z;
	
	//!3D Position Accuracy Estimate (cm)
	unsigned long Pacc;
	
	//!ECEF X velocity (cm/s)
	long ECEFVX;
	
	//!ECEF Y velocity (cm/s)
	long ECEFVY;
	
	//!ECEF Z velocity (cm/s)
	long ECEFVZ;
	
	//!Speed Accuracy Estimate (cm/s)
	unsigned long SAcc;
	
	//!Position DOP
	unsigned short PDOP;
	
	//!reserved
	unsigned char res1;
	
	//!Number of SVs used in Nav Solution
	unsigned char numSV;
	
	//!reserved
	unsigned long res2;
};


/*! \struct structSVINFO_SV
 * \brief Structure containing the main information on one satellite
 *	\author "Olivier Le Marchand"
 *	\version 0.1
 *	\date February 2008
 *
 * \n
 *	Protocols definitions are available in the following document : \n
 *	Title:     ANTARIS Positioning Engine  \n
 *	Subtitle:  NMEA and UBX Protocol Specification  \n
 *	Doc Type:  Specification  \n
 *	Doc ID:    GPS.G3-X-03002-D
  */
struct structSVINFO_SV
{
	
	//!channel number, range 0..NCH-1
	unsigned char chn;  
	
	//!Satellite ID  
	unsigned char SVID;
	
	/*! \brief Bitmask, made up of the following bit values 
	 *  0x01 = SV is used for navigation 
	 *  0x02 = Differential correction data is available for this SV
	 *  0x04 = Orbit information is available for this SV (Ephemeris or Almanach) 
	 *  0x08 = Orbit information is Ephemeris 
	 *  0x10 = SV is unhealthy / shall not be used*/
	unsigned char Flags;

	/*! \brief Signal Quality indicator (range 0..7). The following list shows the meaning of the different QI values: 
	 * 0: This channel is idle
	 * 1, 2: Channel is searching
	 * 3: Signal detected but unusable
	 * 4: Code Lock on Signal
	 * 5, 6: Code and Carrier locked
	 * 7: Code and Carrier locked, receiving 50bps data  */
	char QI;
		
	
	//! Carrier to Noise Ratio (Signal Strength) (dbHz)
	unsigned char CNO;  
	
	//!Elevation in integer degrees  
	char Elev;
	
	//!Azimuth in integer degrees  
	short Azim;
	
	//!Pseudo range residual in centimetres  
	long PRRes;

};


/*! \struct structNAV_SVINFO
 * \brief Structure containing the main information on all the visible satellites
 *	\author "Olivier Le Marchand"
 *	\version 0.1
 *	\date February 2008
 *
 * \n
 *	Protocols definitions are available in the following document : \n
 *	Title:     ANTARIS Positioning Engine  \n
 *	Subtitle:  NMEA and UBX Protocol Specification  \n
 *	Doc Type:  Specification  \n
 *	Doc ID:    GPS.G3-X-03002-D
  */
struct structNAV_SVINFO
{
	//!GPS Millisecond time of week  
	unsigned long ITOW;
   
	//!Number of channels range 0..16
	unsigned char NCH;  
   
	//!Reserved  
	unsigned char RES1;
   
	//!Reserved  
	unsigned short RES2;

	//!information for each Satellite
	structSVINFO_SV infoSV[NB_CHANNEL];

};


/*! \struct structNAV_VELNED
 * \brief Structure containing the velocity and heading estimations in a local tangent reference frame
 *	\author "Olivier Le Marchand"
 *	\version 0.1
 *	\date February 2008
 *
 * \n
 *	Protocols definitions are available in the following document : \n
 *	Title:     ANTARIS Positioning Engine  \n
 *	Subtitle:  NMEA and UBX Protocol Specification  \n
 *	Doc Type:  Specification  \n
 *	Doc ID:    GPS.G3-X-03002-D
  */
struct structNAV_VELNED
{
	//!GPS Millisecond Time of Week
	unsigned long ITOW;    
	
	//!NED north velocity (cm/s)
	long VEL_N;
	
	//!NED east velocity (cm/s)
	long VEL_E;   
	
	//!NED down velocity (cm/s)
	long VEL_D;
	
	//!Speed (3-D) (cm/s)
	unsigned long Speed; 
	
	//!Ground Speed (2-D)(cm/s)
	unsigned long GSpeed; 
	
	//!Heading 2-D (deg)
	long Heading;
	
	//!Speed Accuracy Estimate (cm/s)
	unsigned long SAcc;
	
	//!Course / Heading Accuracy Estimate (deg)
	unsigned long CAcc;
};


/*! \struct structNAV_POSLLH
 * \brief Structure containing the position estimation in the WGS84 coordinate system
 *	\author "Olivier Le Marchand"
 *	\version 0.1
 *	\date February 2008
 *
 * \n
 *	Protocols definitions are available in the following document : \n
 *	Title:     ANTARIS Positioning Engine  \n
 *	Subtitle:  NMEA and UBX Protocol Specification  \n
 *	Doc Type:  Specification  \n
 *	Doc ID:    GPS.G3-X-03002-D
  */
struct structNAV_POSLLH
{
	//!GPS Millisecond Time of Week
	unsigned long ITOW;
	
	//!Longitude (deg)
	long LON;
	
	//!Latitude (deg)
	long LAT;
	
	//!Height above Ellipsoid (mm)
	long HEIGHT;
	
	//!Height above mean sea level (mm)
	long HMSL;
	
	//!Horizontal Accuracy Estimate (mm)
	unsigned long Hacc;
	
	//!Vertical Accuracy Estimate (mm)
	unsigned long Vacc;
};


/*! \struct structNAV_POSUTM
 * \brief Structure containing the position estimation in the UTM coordinate system
 *	\author "Olivier Le Marchand"
 *	\version 0.1
 *	\date February 2008
 *
 * \n
 *	Protocols definitions are available in the following document : \n
 *	Title:     ANTARIS Positioning Engine  \n
 *	Subtitle:  NMEA and UBX Protocol Specification  \n
 *	Doc Type:  Specification  \n
 *	Doc ID:    GPS.G3-X-03002-D
  */
struct structNAV_POSUTM
{
	//!GPS Millisecond Time of Week
	unsigned long ITOW;
	
	//!UTM Easting (cm)
	long EAST;
	
	//!UTM Northing (cm)
	long NORTH;
	
	//!Altitude (cm)
	long ALT;
	
	//!UTM Zone Number
	char ZONE;
	
	//!Hemisphere Indicator (0=North, 1=South)
	char HEM;
};


} // END namespace Ublox




#endif
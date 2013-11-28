/*! \file       structure_septentrio.h
    \brief      Structure for Septentrio Binary Format frames.
    \author     Clement Fouque - HDS
    \date       16/07/2008
    \bug        None
    \warning    None

    This file contains all structures corresponding to Septentrio Binary Format frames emit by a Septentrio GNSS Receiver.

    BLOCK HEADER

    MEASUREMENT BLOCKS:
        - MeasEpoch
        - ShortMeasEpoch
        - GenMeasEpoch
        - EndOfMeas

    GPS MESSAGE BLOCKS:
        - GPSNav
        - GPSAlm
        - GPSIon
        - GPSUtc
        - GPSRaw
        - CNAVRaw

    SBAS MESSAGES BLOCKS:
        - GEOMT00
        - GEOPRNMask
        - GEOFasCorr
        - GEOIntegrity
        - GEOFastCorrDegr
        - GEONav
        - GEODegrFactors
        - GEONetworkTime
        - GEOAlm
        - GEOIGPMask
        - GEOLongTermCorr
        - GEOIonoDelay
        - GEOServiceLevel
        - GEOClockEphCovMatrix
        - GEORaw

*/

#ifndef __STRUCTURE_SEPTENTRIO_H__
#define __STRUCTURE_SEPTENTRIO_H__

#include <vector>

////////////////////
//  BLOCK HEADER  //
////////////////////
/*! \typedef struct SbfDataBlocHeader
    \brief Structure for header of each frame
    SBF Bloc Header Description
*/
typedef struct {
    //! Magic Word For Frame sync
   char sync[2];
   //! Value for CRC check
   unsigned short crc;
   //! Frame Numeric id
   unsigned short id;
   //! Message Frame Length
   unsigned short length;
} SbfDataBlocHeader ;


//////////////////////
//  BLOCK RAW DATA  //
//////////////////////
/*! \typedef struct SbfDataRaw
    \brief Structure for raw data
*/
typedef struct {
  SbfDataBlocHeader header;
  unsigned char data[4096];
}SbfDataRaw;


/////////////////////////////
//  MEASUREMENT BLOCKS:    //
//       - MeasEpoch       //
//       - ShortMeasEpoch  //
//       - GenMeasEpoch    //
//       - EndOfMeas       //
/////////////////////////////

/*! \typedef    struct SbfDataMEChannelData
    \brief      Channel Data for Meas Epoch
*/
typedef struct
{
//! Range on C/A Code (m)
  double CACode;
  //! Diff between P1 and C/A code (m)
  float P1_CACode;
  //! Diff between P2 and C/A code (m)
  float P2_CACode;
  //! L1 Carrier Phase Meas (cycles)
  double L1Phase;
  //! L2 Carrier Phase Meas (cycles)
  double L2Phase;
  //! Doppler shift on L1 (Hz)
  double L1Doppler;
  //! Doppler shift on L2 (Hz)
  double L2Doppler;
  //! Code To Noise Ratio on C/A (dB-Hz)
  float CACN0;
  //! Code To Noise Ratio on P1 (dB-Hz)
  float P1CN0;
  //! Code To Noise Ratio on P2 (dB-Hz)
  float P2CN0;
  //! Satellite ID for Current Sub Block
  unsigned short SVID;
  //! Receiver Channel for tracked SV
  unsigned short RXChannel;
  //! Duration of continuous Tracking
  float LockTime;
  //! L1 Loss-ofLock Indicator
  bool L1_lli;                // L1 Loss-of-Lock Indicator
  //! L1 Loss-ofLock Indicator
  bool L2_lli;
  //! Smoothing of L1-Code
  bool L1_smooth;             // Smoothing of L1-code;
  //! Smoothing of L2-Code
  bool L2_smooth;
  //! MultipathMitigation on C/A code
  bool CA_MultipathMitigation;
  //! Antenna ID for the current Sub Block
  bool AntennaID[3];
} SbfDataMEChannelData ;

/*! \typedef    struct SbfDataMeasEpoch
    \brief      Measurement Epoch
    SBF Block for a measurement Epoch
*/
typedef struct{
   //! GPS Time Of Week (sec)
   float TOW;
   //! GPS Week Number
   unsigned short WNc;
   //! Number of Channel Data SubBlock given in the following
   unsigned int Nsb;
   //! Length of one sub-block in bytes
   unsigned int SBLength;
   //! Structure for Channel Data
   SbfDataMEChannelData ChannelData[16];
} SbfDataMeasEpoch ;

typedef struct {
   unsigned int   CACode ;
   int            L1PhaseMSB ;
   int            L2PhaseMSB ;
   short          L1PhaseLSB ;
   short          L2PhaseLSB ;
   short          P1_CACode ;
   short          P2_CACode ;
   unsigned short CN0s ;
   unsigned char  SVID ;
   unsigned char  flag ;
} SbfDataSMEChannelData ;

typedef struct {
   float TOW;
   unsigned short WNc;
   unsigned char N;
   unsigned char SBLength;
   SbfDataSMEChannelData ChannelData[16];
} SbfDataShortMeasEpoch ;

typedef struct {
   unsigned char Type;
   unsigned char LockTime ;
   unsigned char CN0;
   unsigned char OffsetMSB ;
   char CarrierMSB ;
   unsigned short CodeOffsetLSB ;
   unsigned short CarrierLSB ;
   unsigned short DopplerOffsetLSB ;
} SbfDataGMESubBlockType2 ;

typedef struct {
   unsigned char  RXChannel;
   unsigned char  Type ;
   unsigned char  SVID ;
   unsigned char  Misc ;
   unsigned int   CodeLSB ;
   int            Doppler ;
   unsigned short CarrierLSB;
   char           CarrierMSB ;
   unsigned char  CN0 ;
   unsigned short LockTime ;
   unsigned char  N_Type2 ;
   SbfDataGMESubBlockType2 SubBlocks[10] ;
//    std::vector<SbfDataGMESubBlockType2> SubBlocks ; // Tester pour voir combien sont nécessaires !
} SbfDataGMESubBlockType1 ;

typedef struct {
   float TOW;
   unsigned short WNc;
   unsigned char N ;
   unsigned char SB1Length ;
   unsigned char SB2Length ;
   unsigned char CommonFlag ;
   SbfDataGMESubBlockType1 ChannelData[16] ;
} SbfDataGenMeasEpoch ;

typedef struct{
   //! GPS Time Of Week (sec)
   float TOW;
   //! GPS Week Number
   unsigned short WNc ;
} SbfDataEndOfMeas ;


/////////////////////////////
// GPS MESSAGE BLOCKS:     //
//       - GPSNav          //
//       - GPSAlm          //
//       - GPSIon          //
//       - GPSUtc          //
//       - GPSRaw          //
//       - CNAVRaw         //
/////////////////////////////

/*! \typedef    struct SbfDataGPSNav
    \brief      Decoded Ephemeris for a given SV
*/
typedef struct {
    //! GPS Time of reception of the Navigation Data set (sec)
   float TOW;                 // GPS Time Of Week (sec)
   //! Week Number associated with TOW
   unsigned short WNc;        // GPS Week Number
   //! PRN number of SV
   unsigned short PRN;         // GPS Sat PRN code
//    unsigned char Reserved;   // For future release
   //! Week Number associated to navigation frame
   short WN;                  // Week Nummber from Nav message
   //! Code(s) on L2 Channel
   unsigned char CAorPonL2;   // Code on L2 channel
   //! User Range Accuracy index
   unsigned char URAidx;      // User Range Accuracy Index
   //! 6-bits health
   unsigned char health;
   //! Data Flag for L2 P-Code
   unsigned char L2DataFlag;  // Data flag for L2-P code
   //! Clock Issue of Data
   unsigned short IODC;       // Issue of CLock Data
   //! Issue of ephemeris data ( from subframe 2 )
   unsigned char IODE2;       // Issue of ephemeris data ( subframe 2 )
   //! Issue of ephemeris data ( from subframe 3 )
   unsigned char IODE3;       // Issue of ephemeris data ( subframe 3 )
   //! Curve Fit interval
   unsigned char FitIntFlg;   // Curve Fit interval
//    unsigned char NotUsed;     // Unuse, set to 0;
   //! Estimated Group Delay Differential (sec)
   float T_gd;                 // TIme Group Delay
   //! Clock Data Reference Time (sec)
   unsigned int t_oc;         // Clock Data Reference Time (int ou float ??  )
   //! SV clock parameters [ s/s^2 , s/s , s ]
   float a_f[3];              // SV Clock parameters (bias,drift,aging)
//    float a_f2;              // SV Clock parameters (bias,drift,aging)
//    float a_f1;
//    float a_f0;
   //! Amplitude of the sine harmonic correction term to the orbit radius (m)
   float C_rs;                // Amplitude of the sine harmonic correction trm to the orbit
   //! Mean Motion difference from computed value ( semi-circle / s )
   float DELTA_N;             // Mean motion difference
   //! Mean anomaly at reference time (semi-circle)
   double M_0;                // Mean Anomaly
   //! Amplitude of the cosine harmonic correction term to the argument of latitude (rad)
   float C_uc;                //
   //! Eccentricity (-)
   double e;                  // Excentricity
   //! Amplitude of the sine harmonic correction term to the argument of latitude (rad)
   float C_us;
   //! Square root of semi-major axis ( sqrt(m) )
   double SQRT_A;             // SQRT of semi-major axis
   //! Ephemeris reference time (sec)
   unsigned int t_oe;         // Ref time of ephemeris
   //! Amplitude of the cosine harmonic correction term to the angle of inclination (rad)
   float C_ic;
   //! Longitude of ascending node of orbit plane at weekly epoch (semi-circle)
   double OMEGA_0;
   //! Amplitude of the sine harmonic correction term to the angle of inclination (rad)
   float C_is;
   //! Inclination at reference time (semi-circle)
   double i_0;
   //! Amplitude of the cosine harmonic correction term to the orbit radius (rad)
   float C_rc;
   //! Argument of perigee (semi-circle)
   double omega;
   //! Rate of right Ascension (semi-circle/s)
   float OMEGADOT;
   //! Rate of inclination angle (semi-circle/s)
   float IDOT;
   //! Week number associated with t_oc - modulo 1024
   unsigned short WNt_oc;     // WN to be used with t_oc
   //! Week number associated with t_oe - modulo 1024
   unsigned short WNt_oe;     // WN to be used with t_oe
} SbfDataGPSNav ;

/*! \typedef    struct SbfDataGPSAlm
    \brief      decoded GPS Almanach
*/
typedef struct {
   //! GPS time of reception of almanach data set (sec)
   float TOW;                 // GPS Time Of Week (sec)
   //! GPS Week number associated with TPW
   unsigned short WNc;        // GPS Week Number
   //! PRN Number of GPS SV
   unsigned char PRN;         // GPS Sat PRN code
//    unsigned char Reserved;   // For future release
   //! Eccentricity (-)
   double e;                  // Excentricity
   //! Reference time of ephemeris
   unsigned int t_oa;         // Almanach ref time of week
   //! Inclination at ref time, relative to i0 = 0.3 semi-circles (semi-circle)
   float delta_i;
   //! Rate of right ascension (semi-circle/s)
   float OMEGADOT;
   //! Square root of semi-major axis ( sqrt(m))
   double SQRT_A;             // SQRT of semi-major axis
   //! Longitude of ascending node of orbit plane (semi-circle)
   double OMEGA_0;
   //! Argument of perigee (semi-circle)
   double omega;
   //! Mean Anomaly (semi-circle)
   double M_0;                // Mean Anomaly
   //! SV Clock parameters (drift,bias) [s/s,s]
   float a_f[2];              // SV Clock parameters (bias,drift,aging)
//    float a_f1;
//    float a_f0;
   //! Week Number associated with t_oa
   unsigned char WNa;     // WN to be used with t_oc
   //! Anti-spoofing and satelitte configuration
   unsigned char AS_config;
   //! Health from almanach page
   unsigned char health8;
   //! Health summary
   unsigned char health6;
} SbfDataGPSAlm ;

/*! \typedef    struct SbfDataGPSIon
    \brief      Ionospheric delay paramters
*/
typedef struct {
    //! GPS Time Of Week of iono param reception (sec)
   float TOW;
   //! GPS Week Number
   unsigned short WNc;
   //! GPS Sat PRN code
   unsigned char PRN;
//    unsigned char Reserved;   // For future release
   //! Vertical Delay parameters
   float alpha[4];
//    float alpha_0;
//    float alpha_1;
//    float alpha_2;
//    float alpha_3;
   //! Model period coef
   float beta[4];
//    float beta_0;
//    float beta_1;
//    float beta_2;
//    float beta_3;
}  SbfDataGPSIon ;

/*! \typedef struct SbfDataGPSUtc
    \brief GPS Time to UTC Time parameters
 */
typedef struct {
    //! GPS Time Of Week (sec) of iono param reception
   float TOW;
   //! GPS Week Number
   unsigned short WNc;
   //! GPS Sat PRN code
   unsigned char PRN;
//    unsigned char Reserved;
   //! First order term of the polynomial
   float A_1;
   //! Constant term
   double A_0;
   //! Ref time for UTC data
   unsigned int t_ot;
    //! UTC ref week Number
   unsigned char WN_t;
   //! Delta time due to leap second ( effectivity time *NOT* in the past )
   char DEL_t_LS;
   //! Effectivity time of leap second (week)
   unsigned char WN_LSF;
   //! Effectivity time of leap second (day)
   unsigned char DN;
   //! Delta time due to leap second ( effectivity time in the past )
   char DEL_t_LSF;
} SbfDataGPSUtc ;

/*! \typedef    struct SbfDataGPSRaw
    \brief      GPS raw navigation subframe
    contains the 300 bits of a GPS subframe ( ten 30-bits words )
 */
typedef struct {
   //! GPS time of reception of this subframe (sec)
   float TOW;                 // GPS Time Of Week (sec)
   //! GPS Week Number associated to ToW
   unsigned short WNc;        // GPS Week Number
   //! PRN number of the GPS SV
   unsigned short PRN;         // GPS Sat PRN code
   //    unsigned char Reserved;   // For future release
   //! 10 words of a GPS Subframe
   unsigned long GPSWords[10]; // Raw GPS words for a subframe.
} SbfDataGPSRaw ;

/*! \typedef    struct SbfDataGPSRaw
    \brief      GPS raw navigation subframe
    contains the 300 bits of a GPS subframe ( ten 30-bits words )
    demodulated on L2C
 */
typedef struct {
   //! GPS time of reception of this subframe (sec)
    float TOW;                 // GPS Time Of Week (sec)
   //! GPS Week Number associated to ToW
    unsigned short WNc;        // GPS Week Number
   //! PRN number of the GPS SV
    unsigned short PRN;         // GPS Sat PRN code
   //    unsigned char Reserved;   // For future release
   //! 10 words of a GPS Subframe
   unsigned int CNAVBits[10]; // Raw GPS words for a subframe.
}  SbfDataCNAVRaw ;

///////////////////////////////////
//  SBAS MESSAGES BLOCKS:        //
//       - GEOMT00               //
//       - GEOPRNMask            //
//       - GEOFasCorr            //
//       - GEOIntegrity          //
//       - GEOFastCorrDegr       //
//       - GEONav                //
//       - GEODegrFactors        //
//       - GEONetworkTime        //
//       - GEOAlm                //
//       - GEOIGPMask            //
//       - GEOLongTermCorr       //
//       - GEOIonoDelay          //
//       - GEOServiceLevel       //
//       - GEOClockEphCovMatrix  //
//       - GEORaw                //
///////////////////////////////////

typedef struct {
   float TOW;
   unsigned short WNc;
   unsigned char PRN;
} SbfDataGEOMT00 ;

typedef struct {
   float TOW;
   unsigned short WNc;
   unsigned char PRN;
   unsigned char IODP;
   unsigned char NbrPRNs;
   unsigned char PRNMask[32];
} SbfDataGEOPRNMask ;

/*! \typedef    struct SbfDataGEOFastCorrSubBlock
    \brief      Sub Blocks data for SbfDataGEOFastCorr
*/
typedef struct {
    //! Index number in the PRN Mask
    unsigned char PRNMaskNo ;
    //! User Range Differential Error Indicator for the PRN at index PRNMaskNo
    unsigned char UDREI;
    //! Pseudorange corrections for the PRN at index PRNMaskNo (m)
    float PRC;
} SbfDataGEOFastCorrSubBlock ;

/*! \typedef    struct SbfDataGEOFastCorr
    \brief      Decoded SBAS fast corrections
    contains the SBAS decoded fast corrections from message type 2,3,4,5,24
*/
typedef struct {
    //! Transmission time of the end of the message.
    float TOW;
    //! Week Number associated with TOW;
    unsigned short WNc;
    //! Issue of Data - PRN
    unsigned char PRN;
    //! FC corrections message type
    unsigned char MT;
    //! Issue of Data - PRN;
    unsigned char IODP;
    //! Issue of Data - Fast Corrections;
    unsigned char IODF;
    //! Number of FC sets in this message according to the block type
    unsigned char N;
    //! Length of the FastCorr Sub Block, (bytes)
    unsigned char SBLength;
    //! Fast Corrections Sub Blocks
    SbfDataGEOFastCorrSubBlock FastCorr[16];
} SbfDataGEOFastCorr ;

/*! \typedef    struct SbfDataGEOIntegrity
    \brief      Decoded SBAS integrity informations
    contains the SBAS decoded integrity information from message type 6
 */
typedef struct {
   //! Transmission time of the end of the message.
   float TOW;
    //! Week Number associated with TOW;
   unsigned short WNc;
    //! PRN of transmitting SBAS SV
   unsigned char PRN;
   //! Issue of Data - Fast Corrections for MT02, MT03, MT04 and MT05
   unsigned char IODF[4];
   //! User Differential Range Error Indicator.
   unsigned char UDREI[51] ;
} SbfDataGEOIntegrity ;

/*!
    \typedef    struct SbfDataGEOFastCorrDegr
    \brief      Decoded SBAS integrity informations
    contains the SBAS decoded fast correction degration factor from message type 7
 */
typedef struct {
      //! Transmission time of the end of the message.
   float TOW;
    //! Week Number associated with TOW;
   unsigned short WNc;
    //! PRN of transmitting SBAS SV
   unsigned char PRN;
   //! Issue of data - PRN
   unsigned char IODP ;
   //! System latency
   unsigned char t_lat ;
   //! Degradation factor for each 51 slot;
   unsigned char Ai[51] ;
} SbfDataGEOFastCorrDegr ;

/*!
    \typedef    struct SbfDataGEONav
    \brief      Decoded SBAS navigation data
    Decoded navigation data transmitted in SBAS message type 9.
 */
typedef struct {
      //! Transmission time of the end of the message.
   float TOW;
    //! Week Number associated with TOW;
   unsigned short WNc;
    //! PRN of transmitting SBAS SV
   unsigned char PRN;
   //! Issue of data - Navigation
   unsigned short IODN ;
   //! Accuracy Exponent
   unsigned short URA ;
   //! Time of applicability
   unsigned long t0 ;
   //! X Position at t0 ;
   double Xg ;
   //! Y Position at t0 ;
   double Yg ;
   //! Z Position at t0 ;
   double Zg ;
   //! X Velocity at t0 ;
   double Xgd ;
   //! Y Velocity at t0 ;
   double Ygd ;
   //! Z Velocity at t0 ;
   double Zgd ;
   //! X acceleration at t0 ;
   double Xgdd ;
   //! Y acceleration at t0 ;
   double Ygdd ;
   //! Z acceleration at t0 ;
   double Zgdd ;
   //! time offset with respect to WAAS NetWork
   float AGf[2] ;
} SbfDataGEONav ;

/*!
    \typedef    struct SbfDataGEODegrFactors
    \brief      Decoded SBAS degradation factors
    Decoded navigation data transmitted in SBAS message type 9.
 */
typedef struct {
   //! Transmission time of the end of the message.
   float TOW;
   //! Week Number associated with TOW;
   unsigned short WNc;
   //! PRN of transmitting SBAS SV
   unsigned char PRN;
   //! A parameter associated with the relative estimation noise and round-off error.
   double Brrc ;
   //! Maximum round-off error due to the LSB resolution of the orbit and clock information.
   double Cltc_lsb ;
   //!  Velocity error bound on the maximum range rate difference of missed messages due to clock and orbit rate differences.
   double Cltc_v1;
   //! Update interval for long term corrections when the velocity code is 1.
   unsigned long Iltc_v1 ;
   //! Bound on the update delta between successive long term corrections.
   double Cltc_v0 ;
   //! Minimum update interval for long term messages when the velocity code is 0.
   unsigned long Iltc_v0 ;
   //! Maximum round-off error due to the LSB resolution of the orbit and clock information.
   double Cgeo_lsb ;
   //! Velocity error bound on the maximum range rate difference of missed messages due to clock and orbit rate differences.
   double Cgeo_v ;
   //! Update interval for GEO navigation messages.
   unsigned long Igeo ;
   //! A degradation parameter.
   float Cer ;
   //! Bound on the difference between successive ionospheric grid delay values.
   double Ciono_step ;
   //! Minimum update interval for ionospheric correction messages.
   unsigned long Iiono;
   //! Rate of change of the ionospheric corrections.
   double Ciono_ramp ;
   //! Root-sum-square flag (UDRE)
   unsigned char RSSudre ;
   //! Root-sum-square flag (IONO)
   unsigned char RSSiono ;
   //! A parameter used to compensate for the errors introduced by quantization (introduced in DO 229-C). To be multiplied by the SF parameter from the GEOClockEphCovMatrix block.
   double Ccovariance ;
} SbfDataGEODegrFactors ;

/*!
    \typedef    struct SbfDataGEODegrFactors
    \brief      Decoded SBAS degradation factors
    Decoded navigation data transmitted in SBAS message type 9.
 */
typedef struct {
   //! Transmission time of the end of the message.
   float TOW;
   //! Week Number associated with TOW;
   unsigned short WNc;
   //! PRN of transmitting SBAS SV
   unsigned char PRN;
   //! first order term of polynomial
   float A1 ;
   //! constant term of polynomial
   double A0 ;
   //! reference time for UTC data (time of week)
   unsigned long t_ot ;
   //! UTC reference week number, to which t_ot is referenced
   unsigned char WNt ;
   //! Delta time due to leap seconds whenever the effectivity time is not in the past
   char DEL_t_1S ;
   //! Effectivity time of leap second (week)
   unsigned char WN_LSF ;
   //! Effectivity time of leap second (day)
   unsigned char DN ;
   //! Delta time due to leap seconds whenever the effectivity time is in the past
   char DEL_t_LSF ;
   //! UTC Standard Identifier
   unsigned char UTCStdId ;
   //! GPS week number (modulo 1024)
   unsigned short GPSWN ;
   //! GPS time-of-week
   unsigned long GPSTOW ;
   //! Glonass Indicator
   unsigned char GLONASSind ;
} SbfDataGEONetworkTime ;

/*!
    \typedef    struct SbfDataGEOAlm
    \brief      Decoded SBAS almanach data
    Decoded navigation data transmitted in SBAS message type 9.
 */
typedef struct {
      //! Transmission time of the end of the message.
   float TOW;
    //! Week Number associated with TOW;
   unsigned short WNc;
    //! PRN of transmitting SBAS SV
   unsigned char PRN;
   //! Data ID
   unsigned char DataID ;
   //! Health bits
   unsigned short Health ;
   //! Time of applicability
   unsigned long t0 ;
   //! X Position at t0 ;
   double Xg ;
   //! Y Position at t0 ;
   double Yg ;
   //! Z Position at t0 ;
   double Zg ;
   //! X Velocity at t0 ;
   double Xgd ;
   //! Y Velocity at t0 ;
   double Ygd ;
   //! Z Velocity at t0 ;
   double Zgd ;
} SbfDataGEOAlm ;

/*!
    \typedef    struct SbfDataGEOIGPMask
    \brief      Decoded SBAS ionospheric grid point mask
    Decoded ionospheric grid point mask transmitted in SBAS message type 18.
 */
typedef struct {
   //! Transmission time of the end of the message, in milliseconds from the beginning of the current GPS week (to go with WNc). TOW is always a multiple of 1000.
   float TOW;
   //! Week number associated with TOW (see D.1.5)
   unsigned short WNc;
   //! PRN number of the SBAS satellite from which the message has been received.
   unsigned char PRN;
   //! Number of bands being broadcast.
   unsigned char NbrBands ;
   //! Band number.
   unsigned char BandNbr ;
   //! Issue of data – ionosphere.
   unsigned char IODI ;
   //! Number of ionospheric grid points (IGP) designated in the mask.
   unsigned char NbrIGPs;
   //! List of the IGPs in the IGP mask.
   unsigned char IGPMask[201];
} SbfDataGEOIGPMask ;

/*!
   \typedef struct SbfDataLTCorr
   \brief Decoded long term corrections SubBlock definition
   Decoded long term corrections SubBlock definition transmitted in SBAS message types 24 and 25. To go with <b>SbfDataGEOLongTermCorr</b>
*/

typedef struct
{
    //! Velocity code (0 or 1)
   unsigned char VelocityCode ;
    //! Sequence in the PRN mask, from 1 to 51. Note that if the PRN mask No. from the original message is 0, the corresponding long term corrections are ignored, and hence not included in the GEOLongTermCorr block.
   unsigned char PRNMaskNo ;
    //! Issue of data – PRN.
   unsigned char IODP ;
    //! Issue of data – ephemeris.
   unsigned char IODE ;
    //! Satellite position offset (x).
   float dx ;
    //! Satellite position offset (y).
   float dy ;
    //! Satellite position offset (z).
   float dz ;
    //! Satellite velocity offset (x), or 0.0 if VelocityCode is 0.
   float dxrate ;
    //! Satellite velocity offset (y), or 0.0 if VelocityCode is 0.
   float dyrate ;
    //! Satellite velocity offset (z), or 0.0 if VelocityCode is 0.
   float dzrate ;
    //! Satellite clock offset.
   float da_f0 ;
    //! Satellite drift correction, or 0.0 if VelocityCode is 0.
   float da_f1 ;
    //! Time-of-day of applicability, or 0 if VelocityCode is 0.
   unsigned long t_oe;
} SbfDataLTCorr ;

/*!
    \typedef    struct SbfDataLongTermCorrection
    \brief      Decoded SBAS ionospheric grid point mask
    Decoded ionospheric grid point mask transmitted in SBAS message type 18.
 */
typedef struct {
   //! Transmission time of the end of the message, in milliseconds from the beginning of the current GPS week (to go with WNc). TOW is always a multiple of 1000.
   float TOW ;
   //! Week number associated with TOW (see D.1.5)
   unsigned short WNc ;
   //! PRN number of the SBAS satellite from which the message has been received.
   unsigned char PRN ;
   //! Number of long-term corrections in this message. This is the number of LTCorr sub-blocks. N can be 0, 1, 2, 3 or 4.
   unsigned char N ;
   //! Length of the LTCorr sub-blocks in bytes
   unsigned char SBLength ;
   //! See LTCorr definition below
   SbfDataLTCorr LTCorr[5] ;
} SbfDataGEOLongTermCorr ;

/*!
   \typedef struct SbfDataIDC
   \brief decoded ionospheric subblock
    decoded ionospheric delays transmitted in SBAS message type 26. To go With SbfDataGEOIonoDelay
*/

typedef struct
{
    //! Sequence number in the IGP mask (see GEOIGPMask block), from 1 to 201.
   unsigned char IGPMaskNo ;
    //! Grid Ionospheric Vertical Error Indicator, from 0 to 15
   unsigned char GIVEI ;
   //! IGP vertical delay estimate.
   float VerticalDelay ;
} SbfDataIDC ;

/*!
   \typedef struct SbfDataGEOIonoDelay
   \brief decoded ionospheric delays
    decoded ionospheric delays transmitted in SBAS message type 26.
 */
typedef struct
{
    //! Transmission time of the end of the message, in milliseconds from the beginning of the current GPS week (to go with WNc). TOW is always a multiple of 1000.
    float TOW ;
    //! Week number associated with TOW (see D.1.5)
    unsigned short WNc ;
    //! PRN number of the SBAS satellite from which the message has been received.
    unsigned char PRN ;
    //! Band number.
    unsigned char BandNbr ;
    //! Issue of data – ionosphere.
    unsigned char IODI ;
    //! Number of ionospheric delay corrections in this message. This is the number of IDC sub-blocks. <b>N is always 15.</b>
    unsigned char N ;
    //! Length of the IDC sub-blocks in bytes
    unsigned char SBLength ;
    //! See IDC definition below.
    SbfDataIDC IDC[15] ;
} SbfDataGEOIonoDelay ;

/*!
   \typedef struct SbfDataServiceRegion
   \brief decoded service level message for a geostationary SBAS satellite
    a decoded service level message for a geostationary SBAS satellite as sent in message type 27. To go with SbfDataGEOServiceLevel
 */
typedef struct
{
    //! Coordinate 1 latitude, from –90 to +90
    char Latitude1 ;
    //! Coordinate 2 latitude, from –90 to +90
    char Latitude2 ;
    //! Coordinate 1 longitude, from –180 to +180
    int Longitude1 ;
    //! Coordinate 2 longitude, from –180 to +180
    int Longitude2 ;
    //! Region Shape: 0=triangular, 1=square
    unsigned char RegionShape ;

} SbfDataServiceRegion ;

/*!
   \typedef struct SbfDataGEOServiceLevel
   \brief decoded service level message for a geostationary SBAS satellite
    a decoded service level message for a geostationary SBAS satellite as sent in message type 27.
 */
typedef struct
{
    //! Transmission time of the end of the message, in milliseconds from the beginning of the current GPS week (to go with WNc). TOW is always a multiple of 1000.
    float TOW ;
    //! Week number associated with TOW (see D.1.5)
    unsigned short WNc ;
    //! PRN number of the SBAS satellite from which the message has been received.
    unsigned char PRN ;
    //! Issue of Data Service level, ranging from 0 to 7
    unsigned char IODS ;
    //! Number of service messages (MT27), from 1 to 8
    unsigned char NrMessages ;
    //! Service message number, from 1 to 8
    unsigned char MessageNR ;
    //! Priority Code, from 0 to 3
    unsigned char PriorityCode ;
    //! δUDRE Indicator for users inside the service region, from 0 to 15
    unsigned char dUDREI_In ;
    //! δUDRE Indicator for users outside the service region, from 0 to 15
    unsigned char dUDREI_Out ;
    //! Number of Regions in this message. This is the number of ServiceRegion sub-blocks. Ranging from 0 to 7
    unsigned char N ;
    //! Length of the ServiceRegion sub-blocks in bytes
    unsigned char SBLength ;
    //! See ServiceRegion definition below
    SbfDataServiceRegion ServiceRegion[8];
} SbfDataGEOServiceLevel ;

/*!
   \typedef struct SbfDataCovMatrix
   \brief decoded clock-ephemeris covariance Cholesky factor matrix
    Decoded clock-ephemeris covariance Cholesky factor matrix transmitted in SBAS message type 28. To go with SbfDataGEOServiceLevel.
 */
typedef struct
{
    //! Sequence number in the PRN mask, from 1 to 51. Note that if the PRN mask No. from the original message is 0, the corresponding matrix is ignored, and hence not included in the GEOClockEphCovMatrix block.
   unsigned char PRNMaskNo ;
    //! Scale exponent; scale factor ( = 2^(scale exponent – 5))
   unsigned char ScaleExp ;
    //! E(1,1)
   unsigned short E11;
    //! E(2,2)
   unsigned short E22;
    //! E(3,3)
   unsigned short E33;
    //! E(4,4)
   unsigned short E44;
    //! E(1,2)
   int E12 ;
    //! E(1,3)
   int E13 ;
    //! E(1,4)
   int E14 ;
    //! E(2,3)
   int E23 ;
    //! E(2,4)
   int E24 ;
    //! E(3,4)
   int E34 ;

} SbfDataCovMatrix ;

/*!
   \typedef struct SbfDataGEOClockEphCovMatrix
   \brief decoded clock-ephemeris covariance Cholesky factor matrix
    Decoded clock-ephemeris covariance Cholesky factor matrix transmitted in SBAS message type 28
 */
typedef struct
{
    //! Transmission time of the end of the message, in milliseconds from the beginning of the current GPS week (to go with WNc). TOW is always a multiple of 1000.
    float TOW ;
    //! Week number associated with TOW (see D.1.5)
    unsigned short WNc ;
    //! PRN number of the SBAS satellite from which the message has been received.
    unsigned char PRN ;
    //! Issue of data – PRN.
    unsigned char IODP ;
    //! Number of covariance matrices in this message. This is the number of CovMatrix sub-blocks. N can be 1 or 2.
    unsigned char N ;
    //! Length of the CovMatrix sub-blocks in bytes
    unsigned char SBLength ;
    //! See CovMatrix definition below
    SbfDataCovMatrix CovMatrix[2] ;
} SbfDataGEOClockEphCovMatrix ;

/*!
   \typedef struct SbfDataGEORaw
   \brief raw 250 bits of a navigation message from a geostationary SBAS satellite
    This block contains the raw 250 bits of a navigation message from a geostationary SBAS satellite.
    The 250 bits are stored in 8 successive 32-bit integers. The 6 unused bits are set to 0.
 */
typedef struct
{
    //! Transmission time of the end of the message, in milliseconds from the beginning of the current GPS week (to go with WNc). TOW is always a multiple of 1000.
   float TOW ;
    //! Week number associated with TOW (see D.1.5)
   unsigned short WNc ;
    //! PRN number of the SBAS satellite from which the message has been received.
   unsigned char PRN ;
   //! Signal source flag: 0 = SIS; 1 = SISNeT
   unsigned char SignalSource ;
   //! Raw 250 bits of the message.
   //! The first received bit is stored as bit 31 (MSB) of RawMessageBits[0], the 250-th bit is stored at bit position 6 in RawMessageBits[7].
   //! The 6 LSBs of RawMessageBits[7] are not used, and set to 0.
   //! The 24-bit CRC contained in the last 24 bits of the 250-bit message is always valid and ought not be checked.
   unsigned long RawMessageBits[8] ;
} SbfDataGEORaw ;

/////////////////////////////////////////
//  POSITION, VELOCITY & TIME BLOCKS:  //
//       - PVTCartesian                //
//       - PVTGeodetic                 //
//       - PosCovCartesian             //
//       - PosCovGeodetic              //
//       - VelCovCartesian             //
//       - VelCovGeodetic              //
//       - XDOP                        //
//       - PVTResiduals                //
//       - RAIMStatistics              //
//       - GEOCorrections              //
//       - BaseLine                    //
//       - EndOfPVT                    //
/////////////////////////////////////////

typedef struct
{
  float TOW;            // in s of week
  unsigned short WNc;   // GPS week
  unsigned char nrSV;   // number of satellites used in the PVT computation
  unsigned char error;
  unsigned char mode;
  unsigned char system;
  bool gpsUsed;         // depends on system
  bool glonassUsed;     // depends on system
  bool galileoUsed;     // depends on system (N/A)
  bool otherGnssUsed;   // depends on system (N/A)
  unsigned char sbas;   // 0(no) 1(egnos) 2(waas) 3(msas) 15(unknown)
  unsigned char info;
  bool PVTFix3D;        // true = 3D PVT fix; false = 2D PVT Fix
  bool L1SignalUsed;
  bool L2SignalUsed;
  bool sbasLTC;         // Long Term Corerctions used
  bool sbasFC;          // Fast Corrections used
  bool sbasIono;        // Ionospheric Model used
  bool sbasPA;          // Precision Approach used
  unsigned char sbasPrn;
  double x;             // meter
  double y;
  double z;
  float vx;             // m/s
  float vy;
  float vz;
  double rxClockBias;   // sec
  float rxClockDrift;   // s/s
  unsigned short meanCorrAge;       // 1/100 sec
  unsigned short refBaseId;     // Base station for differential corrections
} SbfDataPVTCartesian ;

typedef struct
{
     float TOW;            // in s of week
  unsigned short WNc;   // GPS week
  unsigned char nrSV;   // number of satellites used in the PVT computation
  unsigned char error;
  unsigned char mode;
  unsigned char system;
  bool gpsUsed;         // depends on system
  bool glonassUsed;     // depends on system
  bool galileoUsed;     // depends on system (N/A)
  bool otherGnssUsed;   // depends on system (N/A)
  unsigned char sbas;   // 0(no) 1(egnos) 2(waas) 3(msas) 15(unknown)
  unsigned char info;
  bool PVTFix3D;        // true = 3D PVT fix; false = 2D PVT Fix
  bool L1SignalUsed;
  bool L2SignalUsed;
  bool sbasLTC;         // Long Term Corerctions used
  bool sbasFC;          // Fast Corrections used
  bool sbasIono;        // Ionospheric Model used
  bool sbasPA;          // Precision Approach used
  unsigned char sbasPrn;
  double lat;           // North Latitude: -pi/2 -> pi/2 (rad)
  double lon;           // East Longitude: -pi -> pi (rad)
  double h;             // WGS84 Ellipsoidal heigth
  float Vn;             // North Velocity
  float Ve;             // East Velocity
  float Vu;             // Up Velocity
  float GeoidUndulation;// Local Geoid Undulation
  double rxClockBias;   // sec
  float rxClockDrift;   // s/s
  unsigned short meanCorrAge;       // 1/100 sec
  unsigned short refBaseId;     // Base station for differential corrections
  float COG;            // Course Over Ground (degree true)
} SbfDataPVTGeodetic ;

typedef struct
{
   float TOW;            // in s of week
   unsigned short WNc;   // GPS week
//   unsigned char Reserved
   unsigned char error;
   float Cov_xx;
   float Cov_yy;
   float Cov_zz;
   float Cov_bb;
   float Cov_xy;
   float Cov_xz;
   float Cov_xb;
   float Cov_yz;
   float Cov_yb;
   float Cov_zb;
} SbfDataPosCovCartesian ;

typedef struct
{
   float TOW;            // in s of week
   unsigned short WNc;   // GPS week
//   unsigned char Reserved
   unsigned char error;
   float Cov_LL;     // variance de la latitude estimee
   float Cov_ll;     // variance de la longitude estimee.
   float Cov_hh;
   float Cov_bb;
   float Cov_Ll;
   float Cov_Lh;
   float Cov_Lb;
   float Cov_lh;
   float Cov_lb;
   float Cov_hb;
} SbfDataPosCovGeodetic ;

typedef struct
{
   float TOW;            // in s of week
   unsigned short WNc;   // GPS week
//   unsigned char Reserved
   unsigned char error;
   float Cov_VxVx;
   float Cov_VyVy;
   float Cov_VzVz;
   float Cov_dd;
   float Cov_VxVy;
   float Cov_VxVz;
   float Cov_Vxd;
   float Cov_VyVz;
   float Cov_Vyd;
   float Cov_Vzd;
} SbfDataVelCovCartesian ;

typedef struct
{
   float TOW;            // in s of week
   unsigned short WNc;   // GPS week
//   unsigned char Reserved
   unsigned char error;
   float Cov_VnVn;     // variance de la latitude estimee
   float Cov_VeVe;     // variance de la longitude estimee.
   float Cov_VuVu;
   float Cov_dd;
   float Cov_VnVe;
   float Cov_VnVu;
   float Cov_Vnd;
   float Cov_VeVu;
   float Cov_Ved;
   float Cov_Vud;
} SbfDataVelCovGeodetic ;

typedef struct
{
   float TOW;            // in s of week
   unsigned short WNc;   // GPS week
   unsigned char nrSV;   // number of satellites used in the Dop computation
   unsigned char error;
   unsigned short PDOP;
   unsigned short TDOP;
   unsigned short HDOP;
   unsigned short VDOP;
   float HPL;
   float VPL;
}  SbfDataXDOP ;

typedef struct
{
   float CACode_Res;
   float P1Code_Res;
   float P2Code_Res;
   float DopL1_Res;
   float DopL2_Res;
   unsigned char SVID;
} SbfDataPVTResidualsChannelData ;

typedef struct
{
   float TOW;            // in s of week
   unsigned short WNc;   // GPS week
   unsigned char N;      // Number of Subblock
   unsigned char SBLength; // Length of a Sub-Block
   SbfDataPVTResidualsChannelData ResidualsSatData[16];
} SbfDataPVTResiduals ;

typedef struct
{
   unsigned char SVID;
   unsigned char AntennaID;
   unsigned char TestResult;
//    unsigned char Reserved
   float Wtest_range;
   float Wtest_rangerate;
   float MDB_range;
   float MDB_rangerate;
} SbfDataRAIMStatisticsSatData ;

typedef struct
{
   float TOW;            // in s of week
   unsigned short WNc;   // GPS week
   unsigned char IntegrityFlag;
//    unsigned char Reserved;
   float HERL_position;
   float VERL_position;
   float HERL_velocity;
   float VERL_velocity;
   unsigned short OverallModelPosition;
   unsigned short OverallModelVelocity;
//    unsigned short Reserved;
   unsigned char N;      // Number of Subblock
   unsigned char SBLength; // Length of a Sub-Block
   SbfDataRAIMStatisticsSatData RAIMSatData[16];
} SbfDataRAIMStatistics ;

typedef struct
{
   unsigned char SVID;
   unsigned char IODE;
//    unsigned char Reserved[2];
   float PR_Corr;
   float CorrAgeFC;
   float DeltaX;
   float DeltaY;
   float DeltaZ;
   float DeltaClock;
   float CorrAgeLT;
   float IonoPPLat;
   float IonoPPLon;
   float SlantIono;
   float CorrAgeIono;
} SbfDataGEOCorrectionsSatCorr ;

typedef struct
{
   float TOW;            // in s of week
   unsigned short WNc;   // GPS week
   unsigned char N;      // Number of Subblock
   unsigned char SBLength; // Length of a Sub-Block
   SbfDataGEOCorrectionsSatCorr GEOSatCorr[16];
} SbfDataGEOCorrections ;

typedef struct
{
   float TOW;
   unsigned short WNc;
   unsigned short BaseStationID;
   double East;
   double North;
   double Up;
} SbfDataBaseLine ;

typedef struct
{
   float TOW;
   unsigned short WNc;
} SbfDataEndOfPVT ;

////////////////////////////////
//  ATTITUDE BLOCKS           //
//       - AttitudeEuler      //
//       - AttitudeCovEuler   //
//       - AttitudeQuat       //
//       - AttitudeCovQuat    //
//       - AuxAntPositions    //
//       - EndOfAttitude      //
////////////////////////////////



//////////////////////////
//  TIME BLOCKS         //
//       - ReceiverTime //
//       - XPPSOffset   //
//       - ExtEvent     //
//////////////////////////

typedef struct
{
   float TOW;           // GPS Time of Week (sec)
   unsigned short WNc;  // GPS Week Number
   char UTCyear;
   char UTCmonth;
   char UTCday;
   char UTChour;
   char UTCmin;
   char UTCsec;
   char DeltaGPS_UTC;  // T_GPS - T_UTc (sec)
   bool WNSet;          // Sync of receiver week nb with GPS Time
   bool TOWSet;         // Sync of receiver time-of-week nb with GPS Time
   bool FineTime;       // Receiver internal clock is within the limit specified
} SbfDataReceiverTime ;

/*!
   \typedef struct SbfDataxPPSOffset
   \brief offset between the true xPPS pulse and the actual pulse output.
*/
typedef struct
{
    //! Time of week of the xPPS pulse to which this block refers.
    float TOW ;
    //! Week number associated with TOW (see D.1.5)
    unsigned short WNc ;
    //! Age of the last synchronization to GPS time. The xPPS pulse is regularly resynchronised with GPS time. This field indicates the number of seconds elapsed since the last resynchronisation. SyncAge is constrained to the 0-255s range. If the age is higher than 255s, SyncAge is set to 255.
    unsigned char SyncAge ;
    //! Time reference to which the xPPS pulse is referenced. The following values are defined (see also the SetPPSParameters command):
    //! 1:       GPS system time;
    //! 2:       UTC;
    //! 3:       receiver time.
    unsigned char Timescale ;
    //! Offset of the xPPS output by the receiver with respect to its true position. Offset is negative when the xPPS pulse is in advance with respect to its true position.
    float Offset ;
} SbfDataxPPSOffset ;

/*!
   \typedef struct SbfDataExtEvent
   \brief  time tag of a voltage transition on one of the TIMERx input pins.
   time tag of a voltage transition on one of the TIMERx input pins.
*/
typedef struct
{
    //! Time of week of the external event, in the receiver time scale.
    float TOW ;
    //! Week number associated with TOW (see D.1.5)
    unsigned short WNc ;
    //! Input pin where this external event has been detected. The following values are defined:
    //! 1:          TIMERA;
    //! 2:          TIMERB.
    unsigned char Source ;
    //! Sub-millisecond part of the external event time tag. The time of week of the external event is given by:
    //! t_ext,rx [s] = TOW/1000 + Offset
    //! t_ext,rx refers to the GPS receiver scale, use the following field (RxClkBias) to convert this time to the GPS time scale.
    float Offset ;
    //! Receiver clock bias relative to GPS time. To get the time of week of
//! the external event in the GPS time scale, use: t_ext,GPS [s] = TOW/1000 + Offset – RxClkBias
    double RxClkBias ;
} SbfDataExtEvent ;


//////////////////////////////////////
//  DIFFERENTIAL CORRECTIONS BLOCK  //
//       - DiffCorrIn               //
//       - BaseStation              //
//       - BaseLink                 //
//////////////////////////////////////


/////////////////////////////
//  STATUS BLOCKS          //
//       - TrackingStatus  //
//       - ReceiverStatus  //
//       - ReceiverSetup   //
/////////////////////////////

/*!
   \typedef struct SbfDataTrackingStatusChannelData
   \brief  tracking status of the active receiver channels.
    tracking status of the active receiver channels. tog with SbfDataTrackingStatusChannelData ;
 */
typedef struct
{
    //! Receiver logical channel number.
    unsigned char RxChannel ;

    //! Satellite ID tracked by this channel: the following ranges are defined
    //! 1-37 : SVID is a PRN number for a GPS satellite
    //! 120-138: SVID is a PRN number for an SBAS satellite
    unsigned char SVID ;

    //! Tracking status on the auxiliary antennas, as follows.
    //! The lowest four bits (bits 0 to 3) indicate the tracking status on the Aux1 antenna.
    //! They can take any of the following values:
    //! •      0: antenna not used by this channel;
    //! •      1: channel searching a satellite signal;
    //! •      2: signal found, channel synchronization in progress;
    //! •      3: signal tracking ongoing, single frequency mode: the channel delivers CA-code and carrier phase data on L1 frequency;
    //! •      4: signal tracking ongoing, dual-frequency mode: the channel delivers CA and P-code an carrier phase data on both L1 and L2 frequencies.
    unsigned char aux1_tracking ;
    //! The highest four bits (bits 4 to 7) indicate the tracking status on the Aux2 antenna with the same definition as above.
    unsigned char aux2_tracking ;

    //! Tracking status on the main antenna.
    //! The lowest four bits indicate the tracking status. They can take any of the following values:
    //! •      1: channel searching a satellite signal;
    //! •      2: signal found, channel synchronization in progress;
    //! •      3: signal tracking in single frequency mode: C/A code only.
    //! •      4: signal tracking in dual-frequency mode: C/A + P(Y) codes.
    //! •      5: signal tracking in dual-frequency mode: C/A + L2C codes.
    //! •      6: signal tracking in dual-frequency mode: C/A + P(Y) + L2C codes.
    unsigned char main_tracking ;

    //! The highest four bits indicate the PVT usage of the channel:
    //! •      0: channel not used in the PVT;
    //! •      1: channel used in the PVT;
    //! •      2: channel rejected from the PVT;
    unsigned char PVT_usage ;

    //! satellite azimuth from 0 to 359 (0 is North, 90 East, 180 South and 270 West). If the azimuth is not known, Azimuth is set to –32768.
    int Azimuth ;
    //! satellite elevation above horizon (90 is for a satellite at zenith). If the elevation is not known, Elevation is set to –128.
    char Elevation ;


    //! Health code:
    //! •      0: satellite healthy;
    //! •      1: satellite not healthy;
    //! •      2: health currently unknown by the receiver.
    unsigned char Health ;

    //! Rise/Set indicator:
    //! •      +1: the satellite rises (the elevation increases);
    //! •      –1: the satellite sets (the elevation decreases);
    //! •      0: elevation change unknown.
    char ElevChange ;
} SbfDataTrackingStatusChannelData ;

/*!
   \typedef struct SbfDataTrackingStatus
   \brief  tracking status of the active receiver channels.
    tracking status of the active receiver channels.
*/
typedef struct
{
    //! Current GPS time of week.
    float TOW ;
    //! Week number associated with TOW (see D.1.5)
    unsigned short WNc ;
    //! number of active channels for which information is provided in this SBF block, i.e. number of ChannelData sub-blocks
    unsigned char N ;
    //! Length of one sub-block in bytes
    unsigned char SBLength ;
    //! See ChannelData definition below
    SbfDataTrackingStatusChannelData ChannelData[16] ;
} SbfDataTrackingStatus ;

/*!
   \typedef struct SbfDataReceiverStatus
   \brief The ReceiverStatus block provides general information on the status of the receiver.
*/
typedef struct
{
   //! Time of week, in milliseconds from the beginning of the current GPS week.
   float TOW ;
   //! Week number associated with TOW (see D.1.5)
   unsigned short WNc ;
   //! Load on the receiver’s CPU. The load should stay below 80% in normal operation. Higher loads might result in data loss.
   unsigned char CPULoad ;
   //! Number of seconds elapsed since the start-up of the receiver, or since the last reset.
   unsigned long UpTime ;
   //! Bit field indicating the status of key components of the receiver.
   unsigned long RxState ;
   //! Bit field containing the settings of the Automatic Gain Control (AGC).
   unsigned long AGCSettings ;
} SbfDataReceiverStatus ;

/*!
   \typedef struct SbfDataReceiverSetup
   \brief  parameters related to the receiver set-up.
*/
typedef struct
{
    //! Current time of week in milliseconds
    float TOW ;
    //! Week number associated with TOW (see D.1.5)
    unsigned short WNc ;
    //! Name of the marker, this is a 60-character string, padded with zeros.
    char MarkerName[60] ;
    //! Marker identification, this is a 20-character string, padded with zeros
    char MarkerNumber[20] ;
    //! Observer description, this is a 20-character string, padded with zeros.
    char Observer[20] ;
    //! Observer’s agency description, this is a 40-character string, padded with zeros
    char Agency[40] ;
    //! Receiver serial number, this is a 20-character string, padded with zeros.
    char RxSerialNumber[20] ;
    //! Receiver name, this is a 20-character string, padded with zeros.
    char RxName[20] ;
    //! Receiver version, this is a 20-character string, padded with zeros.
    char RxVersion[20] ;
    //! Serial number of the main antenna, this is a 20-character string, padded with zeros.
    char AntSerialNbr[20] ;
    //! Type of the main antenna, this is a 20-character string, padded with zeros
    char AntType[20] ;
    //! δH offset of the main antenna
    float DeltaH ;
    //! δE offset of the main antenna
    float DeltaE ;
    //! δN offset of the main antenna
    float DeltaN ;
} SbfDataReceiverSetup ;

///////////////////////
//  MISC BLOCKS      //
//       - comment   //
///////////////////////

typedef struct
{
   float TOW ;
   unsigned short WNc ;
   unsigned short CommentLn ;
   char Comment[480];
} SbfDataComment ;

#endif

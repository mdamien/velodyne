#pragma warning( once : 4290 )
#pragma warning( once : 4274 )

#ifndef _SBAS_H
#define _SBAS_H



/*! \class SBAS
 *	\brief Allows to handle SBAS messages 
 *	\author Olivier LE MARCHAND
 *	\version 1.0
 *	\date April 2008
 *	\bug None
 *	\warning None
 *	
 *
 */
namespace SBAS{

//4*4+2 premiers bits = message ID

/*---------------------------------------------------------------------
---------------------------------- MT1 --------------------------------
-----------------------------------------------------------------------*/
/*!\brief Message type 1 - mask*/
/*! Message type 1 is used to transmit PRN mask for all satellites monitored by EGNOS system.
 *  That includes 37 GPS satellites, 24 GLONASS satellites, 58 future GNSS satellites, 19 GEO
 *  satellites and 72 future GNSS/GEO/WAAS/Pseudolites.\n
 *  Time out interval: 600s\n
 *  Maximum update interval: 120s*/
struct structPRNMaskAssignement
{
//bits 15 à 51 :  mask pour le satellite GPS 1
unsigned char GPSSatMask[37];

//bits 52 à 75 :  mask pour le satellite GLONASS
unsigned char GLONASSSatMask[24];

//bits 76 à 133 :  mask pour les futures GNSS
unsigned char futGNSSSatMask[58];

//bits  134 à 152:  mask pour les satellites SBAS 120 à 138
unsigned char GEOWAASSatMask[19];

//bits  153 à 224:  mask pour les satellites SBAS 120 à 138
unsigned char futAllSatMask[72];

/*!\brief Issue Of Data PRN Mask*/
/*! IODP is changed each time the PRNMask is modified\n
 * from bits 225 to 226*/
unsigned char IODP;
};



/*---------------------------------------------------------------------
---------------------------------- MT2 --------------------------------
-----------------------------------------------------------------------*/
// MT2 : 1 - 13
// MT3 : idem 14 - 26
// MT4 : idem 27 - 39
// MT5 : idem 40 - 51
/*!\brief Message type 2 to 5 - Fast corrections*/
/*! Fast corrections are necessary to correct the fast changing errors such as satellite 
 *  clock error\n
 *  Time out interval: variable\n
 *  Maximum update interval: 60s*/

struct structFastCorrections
{
/*!\brief Issue Of Data Fast Corrections (IODFj)*/
/*! Identifies the current fast corrections, where j shows fast corrections message 
 *  type (2-5). This parameter is used to associate fast corrections with integrity 
 *  information from message type 6\n
 * from bits 15 to 16*/
unsigned char IODF;

/*!\brief Issue Of Data PRN Mask*/
/*! Refers to the IODP of the message of type one in order to associate PRN mask
 *  with Satellite ID\n
 * from bits 17 to 18*/
unsigned char IODP;

// bits 19 à 30 : 12 bits PR correction (m) satellite 1 in PRN Mask valeur à diviser par 32
// bits 31 à 42 : 12 bits PR correction (m) satellite 2 in PRN Mask
// bits 43 à 54 : 12 bits PR correction (m) satellite 3 in PRN Mask
// bits 55 à 66 : 12 bits PR correction (m) satellite 4 in PRN Mask
// bits 67 à 78 : 12 bits PR correction (m) satellite 5 in PRN Mask
// bits 79 à 90 : 12 bits PR correction (m) satellite 6 in PRN Mask
// bits 91 à 102 : 12 bits PR correction (m) satellite 7 in PRN Mask
// bits 103 à 114 : 12 bits PR correction (m) satellite 8 in PRN Mask
// bits 115 à 126 : 12 bits PR correction (m) satellite 9 in PRN Mask
// bits 127 à 138 : 12 bits PR correction (m) satellite 10 in PRN Mask
// bits 139 à 150 : 12 bits PR correction (m) satellite 11 in PRN Mask
// bits 151 à 162 : 12 bits PR correction (m) satellite 12 in PRN Mask
// bits 163 à 174 : 12 bits PR correction (m) satellite 13 in PRN Mask
double  PRCorrectionPRNMask[13];

//43*4+2 = 174
// bits 175 à 178 : 1 octet User differential range estimate (m) satellite 1 in PRN mask valeur correspondante à un tableau
// bits 179 à 182 : 1 octet User differential range estimate (m) satellite 1 in PRN mask
// bits 183 à 186 : 1 octet User differential range estimate (m) satellite 1 in PRN mask
// bits 187 à 190 : 1 octet User differential range estimate (m) satellite 1 in PRN mask
// bits 191 à 194 : 1 octet User differential range estimate (m) satellite 1 in PRN mask
// bits 195 à 198 : 1 octet User differential range estimate (m) satellite 1 in PRN mask
// bits 199 à 202 : 1 octet User differential range estimate (m) satellite 1 in PRN mask
// bits 203 à 206 : 1 octet User differential range estimate (m) satellite 1 in PRN mask
// bits 207 à 210 : 1 octet User differential range estimate (m) satellite 1 in PRN mask
// bits 211 à 214 : 1 octet User differential range estimate (m) satellite 1 in PRN mask
// bits 215 à 218 : 1 octet User differential range estimate (m) satellite 1 in PRN mask
// bits 219 à 222 : 1 octet User differential range estimate (m) satellite 1 in PRN mask
// bits 223 à 226 : 1 octet User differential range estimate (m) satellite 1 in PRN mask
unsigned short UDREI[13];
};

//structFastCorrections fastCorrectionsExtract(unsigned char decodedDataBlock[32]);



/*---------------------------------------------------------------------
---------------------------------- MT6 --------------------------------
-----------------------------------------------------------------------*/
/*!\brief Message type 6 - */
/*! \n
 *  Time out interval: 18s\n
 *  Maximum update interval: 12s*/
struct structIntegrityInformation
{
// bits 15 à 16
/*!\brief Issue of Data Fast correction corresponding to the one used in MT2*/
unsigned char IODF2;

// bits 17 à 18 : IODF3
/*!\brief Issue of Data Fast correction corresponding to the one used in MT3*/
unsigned char IODF3;

// bits 19 à 20 : IODF4
/*!\brief Issue of Data Fast correction corresponding to the one used in MT4*/
unsigned char IODF4;

// bits 21 à 22 : IDOF5
/*!\brief Issue of Data Fast correction corresponding to the one used in MT5*/
unsigned char IODF5;

// bits 23 à 27 : UDREI for sat 1 of mask
//et continue jusqu'au 51
/*!\brief User Data Differential Estimate Indicator*/
unsigned char UDREI[51];
};

//structIntegrityInformation IntegrityInformationExtract(unsigned char decodedDataBlock[32]);


/*---------------------------------------------------------------------
---------------------------------- MT7 --------------------------------
-----------------------------------------------------------------------*/
/*!\brief Message type 7 - Fast Correction Degradation Factor*/
/*! \n
 *  Time out interval: 360s\n
 *  Maximum update interval: 120s*/
struct structFastCorrectionDegradationFactor
{
// bits 15 à 18 : latency in second
unsigned char systemLatency;

// bits 19 à 20 : IODP
unsigned char IODP;

// bits 23 à 26 : fast correction degradation factor of sat1 of mask
//et continue jusqu'au 51
unsigned char ai[51];
};



/*---------------------------------------------------------------------
---------------------------------- MT8 --------------------------------
-----------------------------------------------------------------------*/
/*!\brief Message type 8 - */
/*! \n
 *  Time out interval: \n
 *  Maximum update interval: */
struct structGEONavigationMessage
{
// bits 15 à 22 : IOD
unsigned char IOD;

// bits 23 à 35 : t0
unsigned int t0;

// bits 36 à 37 : accuracy URA
unsigned short accuracyURA;

// bits 38 à 67 : Xg(ECEF)
double XgECEF;

// bits 68 à 97 : Yg(ECEF)
double YgECEF;

// bits 98 à 122 : Zg(ECEF)
double ZgECEF;

// bits 123 à 139 : Xg rate of change
double XgRateOfChange;

// bits 140 à 156 : Yg rateof change
double YgRateOfChange;

// bits 157 à 174 : Zg rate of change
double ZgRateOfChange;

// bits 175 à 184 : Xg acceleration
double XgAcceleration;

// bits 185 à 194 : Yg acceleration
double YgAcceleration;

// bits 195 à 204 : Zg acceleration
double ZgAcceleration;

// bits 205 à 216 : agf0
double agf0;

// bits 217 à 228 : agf1
double agf1;
};




/*---------------------------------------------------------------------
---------------------------------- MT10 -------------------------------
-----------------------------------------------------------------------*/
/*!\brief Message type 10 - */
/*! \n
 *  Time out interval: 360s\n
 *  Maximum update interval: 120s*/
struct structDegradationParameters
{
// bits 15 à 24 : Brrc
double Brrc;

// bits 25 à 34 : Cltc_lsb
double Cltc_lsb;

// bits 35 à 44 : Cltc_v1
double Cltc_v1;

// bits 45 à 53 : Lltc_v1
unsigned short Lltc_v1;

// bits 54 à 63 : Cltc_v0
double Cltc_v0;

// bits 64 à 72 : Lltc_v0
unsigned short Lltc_v0;

// bits 73 à 82 : Cgeo_lsb
double Cgeo_lsb;

// bits 83 à 92 : Cgeo_v
double Cgeo_v;

// bits 93 à 101 : Igeo
unsigned short Igeo;

// bits 102 à 107 : Cer
double Cer;

// bits 108 à 117 : Ciono_step
double Ciono_step;

// bits 118 à 126 : Iiono
unsigned short Iiono;

// bits 127 à 136 : Ciono_ramp
double Ciono_ramp;

// bits 137 : RSSudre
bool RSSudre;

// bits 138 : RSSiono
bool RSSiono;

// bits 139 à 145 : Ccovariance
double Ccovariance;
};


/*---------------------------------------------------------------------
---------------------------------- MT12 -------------------------------
-----------------------------------------------------------------------*/
/*!\brief Message type 12 - */
/*! \n
 *  Time out interval: 1 day, 86400s\n
 *  Maximum update interval: 300s*/
struct structWAASTime
{
// bits 13 à 36
double A1wnt;

// bits 37 à 68
double A0wnt;

// bits 69 à 78
unsigned int t0t;

// bits 79 à 86
unsigned char WNt;

// bits 87 à 94
short DeltaTLS;

// bits 95 à 103
short WNlsf;

// bits 108 à 110
unsigned char DN;

// bits 111 à 118
short DeltaTLsf;

// bits 119 à 121
unsigned char UTSstandardld;

// bits 122 à 141
unsigned int GPSTimeOfWeek;

// bits 142 à 149
unsigned short GPSWeekNumber;

// bits  150
bool GLONASSInd;
};




/*---------------------------------------------------------------------
---------------------------------- MT17 -------------------------------
-----------------------------------------------------------------------*/
/*!\brief Message type 17 - */
/*! \n
 *  Time out interval: none\n
 *  Maximum update interval: 300s*/
struct structGEOSatelliteAlmanacs
{
// bits 
unsigned char DataID[3];

// bits 
unsigned short SPRNNumber[3];

//bits
int XgECEF[3];

//bits
int YgECEF[3];

//bits
int ZgECEF[3];

//bits
char XgRateOfChange[3];

//bits
char YgRateOfChange[3];

//bits
char ZgRateOfChange[3];

//bits
bool ranging[3];

//bits
bool corrections[3];

//bits
bool broadcatsIntegrity[3];

//bits
bool reserved[3];

//bits
unsigned char ID[3];

//bits
unsigned int t0;
};




/*---------------------------------------------------------------------
---------------------------------- MT18 --------------------------------
-----------------------------------------------------------------------*/
/*!\brief Message type 18 - Ionospheric Grid Point Mask*/
/*! Message type 18 is used to ....\n
 *  Time out interval: 1200s\n
 *  Maximum update interval: 300s*/


struct structIonosphericGridPointMask
{
//bits
/* !\brief Ionosphere Issue of Data*/
/* ! between 0 and 3*/
unsigned char IODIonosphere;

//bits
/* !\brief Number of broadcasted bands*/
/* ! Value between 0 and 9. O means that no ionospheric will be provided*/
unsigned char numberOfBroadcastedBands;

//bits
/* !\brief Number of the current band*/
/* ! Value between 0 and 8. Only value between 3 and 5 are useful for EGNOS*/
unsigned char bandNumber;

bool IGPMask[201];
};




/*---------------------------------------------------------------------
---------------------------------- MT24 -------------------------------
-----------------------------------------------------------------------*/

/*!\brief Message type 24 - */
/*! \n
 *  Time out interval: \n
 *  Maximum update interval: */
struct structMixedFastCorrectionLongTermError
{
//bits
double PRCorrection[6];

//bits
unsigned char UDREI[6];

//bits
unsigned char blockID;

//bits
bool velocityCode;

//bits
unsigned char FCIODF;

//bits
unsigned char FCIODP;

//bits
unsigned char PRNMask[2];

//bits
unsigned char IODE[2];

//bits
double deltaXECEF[2];

//bits
double deltaYECEF[2];

//bits
double deltaZECEF[2];

//bits
double deltaXROC;

//bits
double deltaYROC;

//bits
double deltaZROC;

//bits
double deltaAf0[2];

//bits
double deltaAf1;

//bits
double t0;

//bits 
unsigned char LTIODP;
};



/*---------------------------------------------------------------------
---------------------------------- MT25 -------------------------------
-----------------------------------------------------------------------*/
/*!\brief Message type 25 - Long Term Corrections*/
/*! \n
 *  Time out interval: 360s\n
 *  Maximum update interval: 120s*/
struct structLongTermSatelliteErrorCorrections
{
//bits
bool velocityCode[2];

//bits
unsigned char IODP[2];

//bits
unsigned char PRNMask[4];

//bits
unsigned char IODE[4];

//bits
double deltaXECEF[4];

//bits
double deltaYECEF[4];

//bits
double deltaZECEF[4];

//bits
double deltaXROC[4];

//bits
double deltaYROC[4];

//bits
double deltaZROC[4];

//bits
double deltaAf0[4];

//bits
double deltaAf1[4];

//bits
double t0[2];
};



/*---------------------------------------------------------------------
---------------------------------- MT26 -------------------------------
-----------------------------------------------------------------------*/
/*!\brief Message type 26 - Ionospheric Delay Correction*/
/*! Message type 26 is used to ....\n
 *  Time out interval: 600s\n
 *  Maximum update interval: 300s*/
struct structIonosphericDelayCorrections
{
/* !\brief Ionosphere Issue of Data*/
/* ! between 0 and 3*/
unsigned char IODIonosphere;

//bits
/* !\brief Number of the Band*/
/* ! between 0 and 9*/
unsigned char bandNumber;

//bits
/* !\brief Block Identifier*/
/* ! between 0 and 13*/
unsigned char blockID;

//bits
/* !\brief Grid Ionospheric Vertical Error Indicator*/
/* ! between 0 and 15\n
 *   GIVEI = 15 means "not monitored"*/
unsigned char GIVEI[15];

//bits
/* !\brief Vertical delay estimation of the IGP*/
/* ! between 0 and 63.875
 *   vertical delay = 63.750m means not monitored*/
double IGPVerticalDelayEstimate[15];
};




/*---------------------------------------------------------------------
---------------------------------- MT27 -------------------------------
-----------------------------------------------------------------------*/
/*!\brief Message type 27- */
/*! \n
 *  Time out interval: none\n
 *  Maximum update interval: 300s*/
struct structWAASServiceMessage
{
//bits
unsigned char numberOfRegions;

//bits
char coordinate1Latitude[5];

//bits
char coordinate1Longitude[5];

//bits
char coordinate2Latitude[5];

//bits
char coordinate2Longitude[5];

//bits
bool regionShape[5];

//bits
unsigned char IODService;

//bits
unsigned char numberOfServiceMsgs;

//bits
bool serviceMessageNumber;

//bits
unsigned char priorityCode;

//bits
unsigned char UDREIndicatorInside;

//bits
unsigned char UDREIndicatorOutside;
};





/*---------------------------------------------------------------------
---------------------------------- MT28 -------------------------------
-----------------------------------------------------------------------*/
/*!\brief Message type 28 - */
/*! \n
 *  Time out interval: \n
 *  Maximum update interval: */
struct structClockEphCovMatrixMsg
{
//bits
unsigned char PRNMask[2];

//bits
unsigned char ScaleExp[2];

//bits
unsigned short E11[2];

//bits
unsigned short E22[2];

//bits
unsigned short E33[2];

//bits
unsigned short E44[2];

//bits
short E12[2];

//bits
short E13[2];

//bits
short E14[2];

//bits
short E23[2];

//bits
short E24[2];

//bits
short E34[2];
};

unsigned char typeIDExtract(unsigned char decodedDataBlock[32]);

unsigned char preambleExtract(unsigned char decodedDataBlock[32]);


inline unsigned short bytesSpread(unsigned short startBit, unsigned short length)
{
	unsigned short nbBytes;
	nbBytes = ((startBit+length-2)/8 - (startBit-1)/8 +1);
	return nbBytes;
}

char extractChar(unsigned char* dataBlock, unsigned short startBit, unsigned short length);

short extractShort(unsigned char* dataBlock, unsigned short startBit, unsigned short length);

long extractLong(unsigned char* dataBlock, unsigned short startBit, unsigned short length);

unsigned short extractUShort(unsigned char* dataBlock, unsigned short startBit, unsigned short length);

unsigned long extractULong(unsigned char* dataBlock, unsigned short startBit, unsigned short length);
}

#endif
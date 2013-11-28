#ifndef _structure_dataset_H
#define _structure_dataset_H

#define MAX_NB_SAT 12

/* \struct structSatENUMeasCorr
	\brief contains data related to the satellite (coordinates in ENU), measurements from it, and the corrections to apply
 */
struct structSatENUMeasCorr 
{		
	/*! satellite ID*/	
	unsigned int satId;

	//! position of the satellite along the East oriented axis (m)
	double satPosEast;

	//! position of the satellite along the North oriented axis (m)
	double satPosNorth;

	//! position of the satellite along the Up oriented axis (m)
	double satPosUp;

	//! velocity of the satellite along the East oriented axis (m)
	double satVelEast;

	//! velocity of the satellite along the North oriented axis (m)
	double satVelNorth;

	//! velocity of the satellite along the Up oriented axis (m)
	double satVelUp;
	
	//! measured pseudorange on L1 frequency(m)
	double C1;

	//! measured doppler on L1 frequency 
	double D1;

	/*! phase measurement on L1 frequency*/
	double L1;

	/*! signal noise ratio of the signal on L1 frequency*/
	double S1;
	
	//! extrpolated pseudorange on L2 frequency(m)
	double C2;

	//! measured doppler on L2 frequency 
	double D2;

	/*! phase measurement on L2 frequency*/
	double L2;

	/*! signal noise ratio of the signal on L2 frequency*/
	double S2;

	//! satellite clock correction from the broadcasted GPS data plus relative effect (m)
	double satClockOffsetAndRelative;

	//! satellite clock correction from the broadcasted GPS data plus relative effect (m)
	double satClockDrift;

	//! Ionospheric correction from the broadcasted GPS data
	double ionoCorr;

	//! Tropospheric correction from the standard RTCA
	double tropoCorr;

};


struct structEpochDataENU
{
	structSatENUMeasCorr data[MAX_NB_SAT];

	//! Number of satellites
	unsigned int nbSat;

	//* seconds of the week
	double secondsOfWeek;

	//! week number
	int weekNumber;
	
	//! latitude of the center of the ENU referential (deg)
	double ENURefCenterLat;

	//! longitude of the center of the ENU referential (deg)
	double ENURefCenterLong;

	//! Ellispoidal Height of the center of the ENU referential (m)
	double ENURefCenterElH;
};


struct structEpochGPSsolENU
{
	//* seconds of the week
	double secondsOfWeek;

	//! week number
	int weekNumber;
	
	//! latitude of the center of the ENU referential (deg)
	double ENURefCenterLat;

	//! longitude of the center of the ENU referential (deg)
	double ENURefCenterLong;

	//! Ellispoidal Height of the center of the ENU referential (m)
	double ENURefCenterElH;

	double ENUsolX;

	double ENUsolY;

	double ENUsolZ;
};


/* \struct structSatENUMeasCorr
	\brief contains data related to the satellite (coordinates in ENU), measurements from it, and the corrections to apply
 */
struct structSatECEFMeasCorr 
{		
	/*! satellite ID*/	
	unsigned int satId;

	//! position of the satellite along the X axis (m)
	double satPosX;

	//! position of the satellite along the Y axis (m)
	double satPosY;

	//! position of the satellite along the Z axis (m)
	double satPosZ;

	//! velocity of the satellite along the X axis (m)
	double satVelX;

	//! velocity of the satellite along the Y axis (m)
	double satVelY;

	//! velocity of the satellite along the Z axis (m)
	double satVelZ;
	
	//! measured pseudorange on L1 frequency(m)
	double C1;

	//! measured doppler on L1 frequency 
	double D1;

	/*! phase measurement on L1 frequency*/
	double L1;

	/*! signal noise ratio of the signal on L1 frequency*/
	double S1;
	
	//! extrpolated pseudorange on L2 frequency(m)
	double C2;

	//! measured doppler on L2 frequency 
	double D2;

	/*! phase measurement on L2 frequency*/
	double L2;

	/*! signal noise ratio of the signal on L2 frequency*/
	double S2;

	//! satellite clock correction from the broadcasted GPS data plus relative effect (m)
	double satClockOffsetAndRelative;

	//! satellite clock correction from the broadcasted GPS data plus relative effect (m)
	double satClockDrift;

	//! Ionospheric correction from the broadcasted GPS data
	double ionoCorr;

	//! Tropospheric correction from the standard RTCA
	double tropoCorr;

};


struct structEpochDataECEF
{
	structSatECEFMeasCorr data[MAX_NB_SAT];

	//! Number of satellites
	unsigned int nbSat;

	//* seconds of the week
	double secondsOfWeek;

	//! week number
	int weekNumber;
};

struct structSatSBASCorr
{
	/*! satellite ID*/	
	unsigned int satId;

	//! Fast Correction (m)
	double fastCorr;

	//! Slow Correction X ECEF(m)
	double slowCorrX;

	//! Slow Correction Y ECEF(m)
	double slowCorrY;

	//! Slow Correction Z ECEF(m)
	double slowCorrZ;

	//! Slow Correction for the satellite clock offset (s)
	double slowCorrdtime;

	//! Ionospheric correction (m)
	double ionoCorr;

	//! set if the corrections where applied or not
	bool corrApplied;
};

struct structEpochDataSBAS
{
	structSatSBASCorr data[MAX_NB_SAT];

	//! Number of satellites
	unsigned int nbSat;

	//* seconds of the week
	double secondsOfWeek;

	//! week number
	int weekNumber;
};


#endif



#ifndef _GPSTK_Obs_H
#define _GPSTK_Obs_H


#undef min  
#undef max 
#include "DataStructures.hpp"
#include "SourceID.hpp"
#include "DayTime.hpp"
#include "SatID.hpp"
#include "TypeID.hpp"
#include "RinexObsStream.hpp"
#include "RinexObsData.hpp"


/*! \class GPSTK_Obs
 *	\brief Store GPS measurements coming in the gpstk framework
 *	\author Olivier LE MARCHAND
 *	\version 1.0
 *	\date February 2008
 *	\bug None
 *	\warning None
 *
 */

class GPSTK_Obs
{
public : 

	//TODO : doit être capable de gérer l'écriture des RINEX

	
	//! Store the raw measurement for one epoch
	gpstk::gnssSatTypeValue measures;

	//! RINEX data object corresponding to current RAW measurements
	gpstk::RinexObsData RINEX_Data; 

	/*! \brief Constructor. Intitialise the member variables, no RINEX is stored*/
	GPSTK_Obs();

	/*! \brief Constructor. Intitialise the member variables woth a RINEX data container*/
	GPSTK_Obs(gpstk::RinexObsData& rData);

	/*! \brief Constructor. Intitialise the member variables, and open RINEX Stream*/
	GPSTK_Obs(bool storeObsRINEX,std::string RINEX_FilePath);

	/*! \brief Destructor. */
	~GPSTK_Obs();

	/*! \brief Return the satellite system regarding to the satellite PRN */
	static enum gpstk::SatID::SatelliteSystem satelliteSystemFromSatID(int svid);

protected:
	
	gpstk::SourceID SID_GPS;
	gpstk::SourceID SID_Geosync;
	gpstk::SourceID SID_unknown;
	gpstk::DayTime::TimeFrame TF_Receiver;


	//! pointer to stream for the RINEX Observation file
	gpstk::RinexObsStream *prostr;

	//!pointer to the Observation Header
	gpstk::RinexObsHeader *proh;

	//! 1 if we save the Navigation RINEX in a file, 0 elsewhere
	bool storeObsRINEX;

	//! path of the RINEX file
	std::string RINEX_FilePath;

	int firstObservation;

		
	/*! \brief Initialize the observation header of the RINEX file */
	virtual void Obsv_Header_Initialize(gpstk::RinexObsHeader *roh);

};


#endif
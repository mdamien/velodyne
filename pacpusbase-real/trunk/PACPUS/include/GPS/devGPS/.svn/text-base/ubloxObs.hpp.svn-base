#ifndef _ubloxObs_H
#define _ubloxObs_H

#include "GPSTK_Obs.hpp"
#include "structureUBX.h"

#undef min  
#undef max 
#include "DataStructures.hpp"
#include "SourceID.hpp"
#include "DayTime.hpp"
#include "SatID.hpp"
#include "TypeID.hpp"
#include "RinexObsStream.hpp"


/*! \class ubloxObs
 *	\brief Store GPS measurements coming from a Ublox Receiver in the gpstk framework
 *	\author Olivier LE MARCHAND
 *	\version 1.0
 *	\date July 2008
 *	\bug None
 *	\warning None
 *
 */

class ubloxObs : public GPSTK_Obs
{
public : 
	
	/*! \brief Constructor. Intitialise the member variables, no RINEX is stored*/
	ubloxObs();

	/*! \brief Constructor. Intitialise the member variables, and open RINEX Stream*/
	ubloxObs(bool storeObsRINEX,std::string RINEX_FilePath);

	/*! \brief Add RAW data from Ublox Receiver. */
	int newUBX_RAW(const Ublox::structRXM_RAW &inputData);

protected:
	
	/*! \brief Initialize the observation header of the RINEX file */
	virtual void Obsv_Header_Initialize(gpstk::RinexObsHeader *roh);

};


#endif

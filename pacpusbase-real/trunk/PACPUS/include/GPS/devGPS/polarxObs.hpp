#ifndef _polarxObs_H
#define _polarxObs_H

#include "GPSTK_Obs.hpp"
#include "structure/structure_septentrio.h"
#include "PacpusTools/BinaryDecoder.h"

#undef min
#undef max
#include "DataStructures.hpp"
#include "SourceID.hpp"
#include "DayTime.hpp"
#include "SatID.hpp"
#include "TypeID.hpp"
#include "RinexObsStream.hpp"
// #include "ModelObsExt.hpp"


/*! \class polarxObs
 *	\brief Store GPS measurements coming from a PolarX Receiver in the gpstk framework
 *	\author Olivier LE MARCHAND
 *	\version 1.0
 *	\date July 2008
 *	\bug None
 *	\warning None
 *
 */

class polarxObs : public GPSTK_Obs
{
public :

	/*! \brief Constructor. Intitialise the member variables, no RINEX is stored*/
	polarxObs() : GPSTK_Obs() {};

	/*! \brief Constructor. Intitialise the member variables, and open RINEX Stream*/
// 	polarxObs(bool storeObsRINEX,std::string RINEX_FilePath);

	/*! \brief Add RAW data from polarx Receiver. */
	int newMeasEpoch(const SbfDataMeasEpoch &inputData);
        int newMeasEpoch(const SbfDataShortMeasEpoch &inputData);
        int newMeasEpoch(const SbfDataGenMeasEpoch &inputData);


protected:

	/*! \brief Initialize the observation header of the RINEX file for polarX data*/
// 	virtual void Obsv_Header_Initialize(gpstk::RinexObsHeader *roh);
        
};


#endif

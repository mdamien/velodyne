/*!
\class SerialCOM_Msg_GEOFastCorr
\brief EGNOS Fast Correction Message
\author C. Fouque
\version 1.0
\date Dec. 2008
\bug None
\warning None

This block contains the decoded fast corrections transmitted in the SBAS message types 2, 3, 4, 5, 24 and possibly 0 in case the type 0 message contains the type 2 contents. Refer to section A.4.4.3 and A.4.4.8 of DO 229 [2] for further details.

<b>Output rate:</b> if enabled, this block is generated each time MT02, MT03, MT04, MT05, MT24 and possibly MT00 is received from an SBAS satellite.


*/

#pragma warning( once : 4290 )
#pragma warning( once : 4274 )

#ifndef _SerialCOM_Msg_GEOFastCorr_Plrx_H
#define _SerialCOM_Msg_GEOFastCorr_Plrx_H

#include <vector>
#include "SerialCOM_Msg.hpp"
#include "SerialCOM_Protocol.hpp"
#include "structure_septentrio.h"

namespace Plrx
{

   class SerialCOM_Msg_GEOFastCorr : public SerialCOM_Msg , public SbfDataGEOFastCorr
   {

      public :

         /*! \brief Constructor. Intitialise the member variables*/
         SerialCOM_Msg_GEOFastCorr();

         /*! \brief Copy constructor*/
	//SerialCOM_Msg_RXM_SBAS (const SerialCOM_Msg_RXM_SBAS &source);

	/*! \brief reset internal variables of the message after an error or the end of a
         *  message */
         /*! For more information see SerialCOM_Msg::reset*/
         void reset();

	/*! \brief Read the core of the message to check if the object is able to handle this
         *  message*/
         /*! For more information see SerialCOM_Msg::identify*/
         int identify(vector<unsigned char> *pbuffer);

         /*! \brief extracts the data of the message contained in the buffer vector*/
         /*! For more information see SerialCOM_Msg::formatData*/
         int formatData(vector<unsigned char> *pbuffer);

         int fromStructFile(void *buf);

	//! return the size of the structure SbfDataGEOFastCorr
         int getSizeOfStruct(){return sizeof(SbfDataGEOFastCorr);};

	//! write the Data of the message in the DByte file
         virtual int writeDByte(road_time_t currentRoadtime, road_timerange_t currentTimerange);

         //! Display Data to stdout;
         virtual void stdoutDisplay();

   };

};


#endif
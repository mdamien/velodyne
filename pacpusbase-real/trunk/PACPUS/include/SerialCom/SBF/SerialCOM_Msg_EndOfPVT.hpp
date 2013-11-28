/*!
\class SerialCOM_Msg_EndOfPVT
\brief End Of PVT Message
\author C.Fouque
\version 1.0
\date Dec. 2008
\bug None
\warning None

The EndOfPVT block is a synchronization block that is always the last PVT block to be sent at a given epoch.

When this block is sent, the user is ensured that there will be no further PVT blocks with the current time tag. This might be useful for decoding programs wanting to know when all the data from a given epoch have been received.

<b>Output rate:</b> if enabled, this block is sent after all other PVT blocks from the same epoch. For example if only the PVTCartesian block is enabled, this block will be sent after the PVTCartesian block. If both the PVTCartesian and the DOP blocks are enabled, the EndOfPVT block will be sent right after the DOP block. If there are no other PVT blocks enabled than EndOfPVT, the EndOfPVT block is not sent.

*/

#pragma warning( once : 4290 )
#pragma warning( once : 4274 )

#ifndef _SerialCOM_Msg_EndOfPVT_Plrx_H
#define _SerialCOM_Msg_EndOfPVT_Plrx_H

#include <vector>
#include "SerialCOM_Msg.hpp"
#include "SerialCOM_Protocol.hpp"
#include "structure_septentrio.h"

namespace Plrx
{

   class SerialCOM_Msg_EndOfPVT : public SerialCOM_Msg , public SbfDataEndOfPVT
   {

      public :

         /*! \brief Constructor. Intitialise the member variables*/
         SerialCOM_Msg_EndOfPVT();

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

	//! return the size of the structure SbfDataEndOfPVT
         int getSizeOfStruct(){return sizeof(SbfDataEndOfPVT);};

	//! write the Data of the message in the DByte file
         virtual int writeDByte(road_time_t currentRoadtime, road_timerange_t currentTimerange);

         //! Display Data to stdout;
         virtual void stdoutDisplay();

   };

};


#endif

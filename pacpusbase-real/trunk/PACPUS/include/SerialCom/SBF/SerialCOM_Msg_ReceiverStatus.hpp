/*! 
\class SerialCOM_Msg_ReceiverStatus
\brief Overall status information of the receiver
\author Vincent Drevelle
\version 1.0
\date Dec. 2008
\bug None
\warning None

The ReceiverStatus block provides general information on the status of the receiver.\n
<b>Output rate:</b> if enabled, this block is generated every 2 seconds, synchronously with the 2-second
boundaries of the receiver time

 */

#pragma warning( once : 4290 )
#pragma warning( once : 4274 )

#ifndef _SerialCOM_Msg_ReceiverStatus_Plrx_H
#define _SerialCOM_Msg_ReceiverStatus_Plrx_H

#include <vector>
#include "SerialCOM_Msg.hpp"
#include "SerialCOM_Protocol.hpp"
#include "structure_septentrio.h"

namespace Plrx
{

   class SerialCOM_Msg_ReceiverStatus : public SerialCOM_Msg , public SbfDataReceiverStatus
   {

      public : 

         /*! \brief Constructor. Intitialise the member variables*/
         SerialCOM_Msg_ReceiverStatus();

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

	//! return the size of the structure SbfDataReceiverStatus
         int getSizeOfStruct(){return sizeof(SbfDataReceiverStatus);};

	//! write the Data of the message in the DByte file
         virtual int writeDByte(road_time_t currentRoadtime, road_timerange_t currentTimerange);
        
         //! Display Data to stdout;
         virtual void stdoutDisplay();

   };

};


#endif
/*! 
\class SerialCOM_Msg_ReceiverSetup
\brief General information about the receiver set-up
\author Vincent Drevelle
\version 1.0
\date Déc. 2008
\bug None
\warning None

The ReceiverSetup block contains parameters related to the receiver set-up. This block provides
most of the information to be included in a RINEX header.\n
<b>Output rate:</b> if enabled, this block is generated on three events:\n
• each time one of the following commands is issued: SetAntennaParameters,
SetMarkerParameters or SetObserverParameters;\n
• every 10 minutes (synchronous with the 10-minute boundary in the receiver time scale);\n
• each time the ReceiverSetup block is specified in the SetSBFOutput command.

 */

#pragma warning( once : 4290 )
#pragma warning( once : 4274 )

#ifndef _SerialCOM_Msg_ReceiverSetup_Plrx_H
#define _SerialCOM_Msg_ReceiverSetup_Plrx_H

#include <vector>
#include "SerialCOM_Msg.hpp"
#include "SerialCOM_Protocol.hpp"
#include "structure_septentrio.h"

namespace Plrx
{

   class SerialCOM_Msg_ReceiverSetup : public SerialCOM_Msg , public SbfDataReceiverSetup
   {

      public : 

         /*! \brief Constructor. Intitialise the member variables*/
         SerialCOM_Msg_ReceiverSetup();

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

	//! return the size of the structure SbfDataReceiverSetup
         int getSizeOfStruct(){return sizeof(SbfDataReceiverSetup);};

	//! write the Data of the message in the DByte file
         virtual int writeDByte(road_time_t currentRoadtime, road_timerange_t currentTimerange);
        
         //! Display Data to stdout;
         virtual void stdoutDisplay();
	
   };

};


#endif
/*!
\class SerialCOM_Msg_ReceiverTime
\brief Current GPS and UTC time
\author Vincent Drevelle
\version 1.0
\date Nov. 2008
\bug None
\warning None

The ReceiverTime block provides the current time with a 1-second resolution in both the GPS and
the UTC time scale.\n
The accuracy of the time depends on the level of synchronization of the receiver with the GPS system
time, as provided in the SyncLevel field.\n
UTC time is provided if GPS-to-UTC correction parameters are available in the receiver. This is
normally the case except after a reset all, or when the receiver has been switched off for at least
20 weeks. In these cases, the receiver waits for the GPS-to-UTC corrections to be sent by the GPS
satellites, which may take up to 12.5 minutes. If the UTC time is not available, the corresponding
fields are set to a special Do-Not-Use value.

*/

#pragma warning( once : 4290 )
#pragma warning( once : 4274 )

#ifndef _SerialCOM_Msg_ReceiverTime_Plrx_H
#define _SerialCOM_Msg_ReceiverTime_Plrx_H

#include <vector>
#include "SerialCOM_Msg.hpp"
#include "SerialCOM_Protocol.hpp"
#include "structure_septentrio.h"

namespace Plrx
{

   class SerialCOM_Msg_ReceiverTime : public SerialCOM_Msg , public SbfDataReceiverTime
   {

      public :

         /*! \brief Constructor. Intitialise the member variables*/
         SerialCOM_Msg_ReceiverTime();

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

	//! return the size of the structure SbfDataReceiverTime
         int getSizeOfStruct(){return sizeof(SbfDataReceiverTime);};

	//! write the Data of the message in the DByte file
         virtual int writeDByte(road_time_t currentRoadtime, road_timerange_t currentTimerange);

         //! Display Data to stdout;
         virtual void stdoutDisplay();

   };

};


#endif

/*! 
\class SerialCOM_Msg_ExtEvent
\brief Time tag of an external event
\author Vincent Drevelle
\version 1.0
\date Dec. 2008
\bug None
\warning None

The ExtEvent block contains the time tag of a voltage transition on one of the TIMERx input pins.
Refer to section 2.17 for further details.\n
<b>Output rate:</b> if enabled, this block is output each time when a voltage transition is detected on one of
the TIMERx pins. This block is only output after the first position fix is available.

 */

#pragma warning( once : 4290 )
#pragma warning( once : 4274 )

#ifndef _SerialCOM_Msg_ExtEvent_Plrx_H
#define _SerialCOM_Msg_ExtEvent_Plrx_H

#include <vector>
#include "SerialCOM_Msg.hpp"
#include "SerialCOM_Protocol.hpp"
#include "structure_septentrio.h"

namespace Plrx
{

   class SerialCOM_Msg_ExtEvent : public SerialCOM_Msg , public SbfDataExtEvent
   {

      public : 

         /*! \brief Constructor. Intitialise the member variables*/
         SerialCOM_Msg_ExtEvent();

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

	//! return the size of the structure SbfDataExtEvent
         int getSizeOfStruct(){return sizeof(SbfDataExtEvent);};

	//! write the Data of the message in the DByte file
         virtual int writeDByte(road_time_t currentRoadtime, road_timerange_t currentTimerange);
        
         //! Display Data to stdout;
         virtual void stdoutDisplay();
	
   };

};


#endif
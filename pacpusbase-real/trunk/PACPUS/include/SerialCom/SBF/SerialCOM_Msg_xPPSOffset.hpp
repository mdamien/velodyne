/*!
\class SerialCOM_Msg_xPPSOffset
\brief Offset between true xPPS and actual pulse output
\author C. Fouque
\version 1.0
\date Dec. 2008
\bug None
\warning None

The xPPSOffset block contains the offset between the true xPPS pulse and the actual pulse output by the receiver. The rationale for this block is explained in section 3.4, on page 37.

<b>Output rate:<b> if enabled, this block is output after each xPPS pulse.

 */

#pragma warning( once : 4290 )
#pragma warning( once : 4274 )

#ifndef _SerialCOM_Msg_xPPSOffset_Plrx_H
#define _SerialCOM_Msg_xPPSOffset_Plrx_H

#include <vector>
#include "SerialCOM_Msg.hpp"
#include "SerialCOM_Protocol.hpp"
#include "structure_septentrio.h"

namespace Plrx
{

   class SerialCOM_Msg_xPPSOffset : public SerialCOM_Msg , public SbfDataxPPSOffset
   {

      public :

         /*! \brief Constructor. Intitialise the member variables*/
         SerialCOM_Msg_xPPSOffset();

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

	//! return the size of the structure SbfDataxPPSOffset
         int getSizeOfStruct(){return sizeof(SbfDataxPPSOffset);};

	//! write the Data of the message in the DByte file
         virtual int writeDByte(road_time_t currentRoadtime, road_timerange_t currentTimerange);

         //! Display Data to stdout;
         virtual void stdoutDisplay();

   };

};


#endif
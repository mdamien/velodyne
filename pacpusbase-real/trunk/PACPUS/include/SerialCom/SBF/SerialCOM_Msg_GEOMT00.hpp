/*!
\class SerialCOM_Msg_GEOMT00
\brief GEO MT00 frame
\author C. Fouque
\version 1.0
\date DeC. 2008
\bug None
\warning None

This block is sent to indicate that an empty SBAS message type 0 has been received.

In test phase, message type 0 can contain the contents of message type 2. Upon reception of a message type 0, the receiver checks whether the message is empty (it contains only 0’s) or whether it contains the message type 2 contents. If the former case, a GEOMT00 block will be generated. In the latter case, a GEOFastCorr block will be generated. Refer to section A.4.4.1 of DO 229 [2] for further details.
 */

#pragma warning( once : 4290 )
#pragma warning( once : 4274 )

#ifndef _SerialCOM_Msg_GEOMT00_Plrx_H
#define _SerialCOM_Msg_GEOMT00_Plrx_H

#include <vector>
#include "SerialCOM_Msg.hpp"
#include "SerialCOM_Protocol.hpp"
#include "structure_septentrio.h"

namespace Plrx
{

   class SerialCOM_Msg_GEOMT00 : public SerialCOM_Msg , public SbfDataGEOMT00
   {

      public :

         /*! \brief Constructor. Intitialise the member variables*/
         SerialCOM_Msg_GEOMT00();

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

	//! return the size of the structure SbfDataGEOMT00
         int getSizeOfStruct(){return sizeof(SbfDataGEOMT00);};

	//! write the Data of the message in the DByte file
         virtual int writeDByte(road_time_t currentRoadtime, road_timerange_t currentTimerange);

         //! Display Data to stdout;
         virtual void stdoutDisplay();

   };

};


#endif
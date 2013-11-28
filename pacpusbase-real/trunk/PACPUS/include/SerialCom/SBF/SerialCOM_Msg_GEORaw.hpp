/*!
\class SerialCOM_Msg_GEORaw
\brief raw 250 bits of a navigation message from a geostationary SBAS satellite
\author C. Fouque
\version 1.0
\date Dec. 2008
\bug None
\warning None

This block contains the raw 250 bits of a navigation message from a geostationary SBAS satellite. The 250 bits are stored in 8 successive 32-bit integers. The 6 unused bits are set to 0. Refer to section A.4.3 of DO 229 [2] for further details.

If the SISNeT is used as a source of SBAS data, the PolaRx will also generate GEORaw messages. In this case the binary data represent the raw bits of the original SBAS data (all the SISNeT-specific encoding is removed).

<b>Output rate:</b> If enabled, this block is generated each time a new message is received from an SBAS satellite, if its parity is valid. Typically, the receiver outputs a new GEORaw block every second for each of the SBAS satellites currently tracked.

 */

#pragma warning( once : 4290 )
#pragma warning( once : 4274 )

#ifndef _SerialCOM_Msg_GEORaw_Plrx_H
#define _SerialCOM_Msg_GEORaw_Plrx_H

#include <vector>
#include "SerialCOM_Msg.hpp"
#include "SerialCOM_Protocol.hpp"
#include "structure_septentrio.h"

namespace Plrx
{

   class SerialCOM_Msg_GEORaw : public SerialCOM_Msg , public SbfDataGEORaw
   {

      public :

         /*! \brief Constructor. Intitialise the member variables*/
         SerialCOM_Msg_GEORaw();

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

	//! return the size of the structure SbfDataGEORaw
         int getSizeOfStruct(){return sizeof(SbfDataGEORaw);};

	//! write the Data of the message in the DByte file
         virtual int writeDByte(road_time_t currentRoadtime, road_timerange_t currentTimerange);

         //! Display Data to stdout;
         virtual void stdoutDisplay();

   };

};


#endif
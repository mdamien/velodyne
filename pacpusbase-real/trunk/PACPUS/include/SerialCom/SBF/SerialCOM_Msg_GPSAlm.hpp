/*!
\class SerialCOM_Msg_GPSAlm
\brief Almanac data for a GPS satellite
\author Vincent Drevelle
\version 1.0
\date Dec. 2008
\bug None
\warning None

The GPSAlm block contains the decoded almanac data for one GPS satellite. These data are conveyed
in subframes 4 and 5 of the satellite navigation message. Refer to GPS ICD [3] for further details.

 */

#pragma warning( once : 4290 )
#pragma warning( once : 4274 )

#ifndef _SerialCOM_Msg_GPSAlm_Plrx_H
#define _SerialCOM_Msg_GPSAlm_Plrx_H

#include <vector>
#include "SerialCOM_Msg.hpp"
#include "SerialCOM_Protocol.hpp"
#include "structure_septentrio.h"

namespace Plrx
{

   class SerialCOM_Msg_GPSAlm : public SerialCOM_Msg , public SbfDataGPSAlm
   {

      public :

         /*! \brief Constructor. Intitialise the member variables*/
         SerialCOM_Msg_GPSAlm();

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

	//! return the size of the structure SbfDataGPSAlm
         int getSizeOfStruct(){return sizeof(SbfDataGPSAlm);};

	//! write the Data of the message in the DByte file
         virtual int writeDByte(road_time_t currentRoadtime, road_timerange_t currentTimerange);

         //! Display Data to stdout;
         virtual void stdoutDisplay();

   };

};


#endif

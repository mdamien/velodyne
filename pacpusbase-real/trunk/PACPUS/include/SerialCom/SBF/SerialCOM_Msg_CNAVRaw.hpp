/*!
\class SerialCOM_Msg_CNAVRaw
\brief Raw navigation bits from a GPS satellite (DC(t) data modulated on the L2C code)
\author Vincent Drevelle
\version 1.0
\date Dec. 2008
\bug None
\warning None

This block contains the raw 300 bits of a CNAV frame (the so-called “Dc(t)” data modulating the L2C
code). The 300 bits are stored in 10 successive 32-bit integers. The 20 unused bits are set to 0. Refer
to GPS-ICD-200 Rev.C for details on the CNAV frame structure.

 */

#pragma warning( once : 4290 )
#pragma warning( once : 4274 )

#ifndef _SerialCOM_Msg_CNAVRaw_Plrx_H
#define _SerialCOM_Msg_CNAVRaw_Plrx_H

#include <vector>
#include "SerialCOM_Msg.hpp"
#include "SerialCOM_Protocol.hpp"
#include "structure_septentrio.h"

namespace Plrx
{

   class SerialCOM_Msg_CNAVRaw : public SerialCOM_Msg , public SbfDataCNAVRaw
   {

      public :

         /*! \brief Constructor. Intitialise the member variables*/
         SerialCOM_Msg_CNAVRaw();

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

	//! return the size of the structure SbfDataCNAVRaw
         int getSizeOfStruct(){return sizeof(SbfDataCNAVRaw);};

	//! write the Data of the message in the DByte file
         virtual int writeDByte(road_time_t currentRoadtime, road_timerange_t currentTimerange);

         //! Display Data to stdout;
         virtual void stdoutDisplay();

   };

};


#endif

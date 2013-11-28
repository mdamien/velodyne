/*! 
\class SerialCOM_Msg_EndOfMeas
\brief This class allows the handle of the EndOfMeas frame 
\author C. FOUQUE
\version 1.0
\date Oct. 2008
\bug None
\warning None

The EndOfMeas block is a synchronization block, which is always the last measurement block to be sent. When this block is sent, the user is ensured that there will be no further 
measurement blocks with the current time tag (TOW and WNc). This might be useful for decoding programs wanting to know when all the measurement data from a given epoch have been 
received.\n

<b>Output rate:</b> if enabled, this block is sent after all the other measurement blocks for the same 
epoch. For example if only the MeasEpoch block is enabled, this block will be sent after the MeasEpoch block. If both the MeasEpoch and the ShortMeasEpoch blocks are enabled, the 
EndOfMeas block will be sent right after the ShortMeasEpoch block. If the EndOfMeas block is the only measurement block enabled, it will not be sent.

 */

#pragma warning( once : 4290 )
#pragma warning( once : 4274 )

#ifndef _SerialCOM_Msg_EndOfMeas_Plrx_H
#define _SerialCOM_Msg_EndOfMeas_Plrx_H

#include <vector>
#include "SerialCOM_Msg.hpp"
#include "SerialCOM_Protocol.hpp"
#include "structure_septentrio.h"

namespace Plrx
{

   class SerialCOM_Msg_EndOfMeas : public SerialCOM_Msg , public SbfDataEndOfMeas
   {

      public : 

         /*! \brief Constructor. Intitialise the member variables*/
         SerialCOM_Msg_EndOfMeas();

         /*! \brief Copy constructor*/
	//SerialCOM_Msg_RXM_SBAS (const SerialCOM_Msg_RXM_SBAS &source);

	/*! \brief reset internal variables of the message after an error or the end of a  message. For more information see SerialCOM_Msg::reset */
         void reset();

	/*! \brief Read the core of the message to check if the object is able to handle this  message. For more information see SerialCOM_Msg::identify */
         int identify(vector<unsigned char> *pbuffer);

         /*! \brief extracts the data of the message contained in the buffer vector. For more information see SerialCOM_Msg::formatData */
         int formatData(vector<unsigned char> *pbuffer);

         int fromStructFile(void *buf);

	//! return the size of the structure structMeasEpoch
         int getSizeOfStruct(){return sizeof( SbfDataEndOfMeas ); };

	//! write the Data of the message in the DByte file
         virtual int writeDByte(road_time_t currentRoadtime, road_timerange_t currentTimerange);
        
         //! Display Data to stdout;
         virtual void stdoutDisplay();
	
   };

};


#endif

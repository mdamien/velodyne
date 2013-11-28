/*! 
\class SerialCOM_Msg_<FRAME>
\brief TO BE EDITED
\author TO BE EDITED
\version 1.0
\date TO BE EDITED
\bug None
\warning None

COMMENT FROM POLARX DOCUMENTATION.

Search for :
 * <FRAME>               : to edit class name according to frame name
 * <SBFDATASTRUCTURE>    : to provide the name of the corresponding data structure.
 * <FRAME_ID>            : to provide SBF frame ID
 * <FRAME_NAME>"         : to provide SBF frame name
 * <DBT_FRAME_NAME>      : to provide DBT name given in "iohdfile.h"

 */

#pragma warning( once : 4290 )
#pragma warning( once : 4274 )

#ifndef _SerialCOM_Msg_<FRAME>_Plrx_H
#define _SerialCOM_Msg_<FRAME>_Plrx_H

#include <vector>
#include "SerialCOM_Msg.hpp"
#include "SerialCOM_Protocol.hpp"
#include "structure_septentrio.h"

namespace Plrx
{

   class SerialCOM_Msg_<FRAME> : public SerialCOM_Msg , public <SBFDATASTRUCTURE>
   {

      public : 

         /*! \brief Constructor. Intitialise the member variables*/
         SerialCOM_Msg_<FRAME>();

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

	//! return the size of the structure <SBFDATASTRUCTURE>
         int getSizeOfStruct(){return sizeof(<SBFDATASTRUCTURE>);};

	//! write the Data of the message in the DByte file
         virtual int writeDByte(road_time_t currentRoadtime, road_timerange_t currentTimerange);
        
         //! Display Data to stdout;
         virtual void stdoutDisplay();
	
   };

};


#endif
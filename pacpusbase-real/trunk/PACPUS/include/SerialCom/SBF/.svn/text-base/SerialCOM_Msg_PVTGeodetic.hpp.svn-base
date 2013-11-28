/*! 
\class SerialCOM_Msg_PVTGeodetic
\brief Geodetic position of the receiver
\author C. Fouque
\version 1.0
\date dec. 2008
\bug None
\warning None

This block contains position (φ, λ, h) and velocity (vn, ve, vu) at the time specified in the TOW and WNc fields. The computed position and velocity are expressed in the geodetic coordinates that make use of the WGS-84 ellipsoid. The velocity vector is expressed relative to the local-level Cartesian coordinate frame with north-, east-, up unit vectors. To transfer the time to the GPS time frame, the reported receiver clock bias (RxClkBias field) must be subtracted from the receiver time. An indication  of the quality of the reported position and velocity fix can be found in the PosCovGeodetic and VelCovGeodetic blocks to be described further in this section. 

Output rate: if enabled, this block is output at a nominal rate defined by the SetPVTInterval and
SetOutputDecimation commands.

 */

#pragma warning( once : 4290 )
#pragma warning( once : 4274 )

#ifndef _SerialCOM_Msg_PVTGeodetic_Plrx_H
#define _SerialCOM_Msg_PVTGeodetic_Plrx_H

#include <vector>
#include "SerialCOM_Msg.hpp"
#include "SerialCOM_Protocol.hpp"
#include "structure_septentrio.h"

namespace Plrx
{

   class SerialCOM_Msg_PVTGeodetic : public SerialCOM_Msg , public SbfDataPVTGeodetic
   {

      public : 

         /*! \brief Constructor. Intitialise the member variables*/
         SerialCOM_Msg_PVTGeodetic();

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

	//! return the size of the structure structMeasEpoch
         int getSizeOfStruct(){return sizeof(SbfDataPVTGeodetic);};

	//! write the Data of the message in the DByte file
         virtual int writeDByte(road_time_t currentRoadtime, road_timerange_t currentTimerange);
        
         //! Display Data to stdout;
         virtual void stdoutDisplay();
	
   };

};


#endif
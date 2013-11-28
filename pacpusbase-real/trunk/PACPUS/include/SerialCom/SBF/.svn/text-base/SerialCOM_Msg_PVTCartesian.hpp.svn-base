/*! 
   \class SerialCOM_Msg_PVTCartesian
   \brief Allows to handle PVTcartesian messages coming from a Polarx GPS receiver
   \author Clément Fouque
   \version 1.0
   \date Sept. 2008
   \bug None
   \warning None
   
This block contains computed position (x, y, z) and velocity (vx, vy, vz) at the time specified in the TOW and WNc fields.\n
The computed position and velocity are expressed in the Cartesian axes of the WGS-84 ellipsoid. Note that the time of applicability is specified in the receiver time frame. To transfer the time to the GPS time frame, the reported receiver clock bias (RxClkBias field) must be subtracted from the receiver time. An indication of the quality of the reported position and velocity fix can be found in the PosCovCartesian and VelCovCartesian blocks.

*/

#ifndef _SerialCOM_Msg_PVTCar_Plrx_H
#define _SerialCOM_Msg_PVTCar_Plrx_H

#include <vector>
#include "structure_septentrio.h"
#include "SerialCOM_Msg.hpp"
#include "SerialCOM_Protocol.hpp"

namespace Plrx {
   
   class SerialCOM_Msg_PVTCartesian : public SerialCOM_Msg , public SbfDataPVTCartesian
   {
      public:

         SerialCOM_Msg_PVTCartesian();

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

		//! return the size of the structure structNAV_SOL
         int getSizeOfStruct(){return sizeof(SbfDataPVTCartesian);};

         int fromStructFile(void *buf);
		
		//! write the Data of the message in the DByte file
         virtual int writeDByte(road_time_t currentRoadtime, road_timerange_t currentTimerange);
         
         //! Display Data to stdout;
         virtual void stdoutDisplay();
   };
   
};
#endif

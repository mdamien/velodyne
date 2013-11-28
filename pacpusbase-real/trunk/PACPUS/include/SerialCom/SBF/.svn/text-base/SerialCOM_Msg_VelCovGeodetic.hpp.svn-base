/*! 
\class SerialCOM_Msg_VelCovGeodetic
\brief Velocity Covariance in Geodetic frame
\author C. Fouque
\version 1.0
\date dec. 2008
\bug None
\warning None

This block contains the elements of the symmetric variance-covariance matrix of the velocity expressed in the geodetic coordinates of the WGS-84 ellipsoid: 
Please refer to the PosCovCartesian block description for a general explanation of the contents.

In case of a 2D velocity, all height related components of the variance-covariance matrix are undefined and set to their Do-Not-Use value.

Output rate: if enabled, this block is generated together with the corresponding PVTGeodetic block.


 */

#pragma warning( once : 4290 )
#pragma warning( once : 4274 )

#ifndef _SerialCOM_Msg_VelCovGeodetic_Plrx_H
#define _SerialCOM_Msg_VelCovGeodetic_Plrx_H

#include <vector>
#include "SerialCOM_Msg.hpp"
#include "SerialCOM_Protocol.hpp"
#include "structure_septentrio.h"

namespace Plrx
{

   class SerialCOM_Msg_VelCovGeodetic : public SerialCOM_Msg , public SbfDataVelCovGeodetic
   {

      public : 

         /*! \brief Constructor. Intitialise the member variables*/
         SerialCOM_Msg_VelCovGeodetic();

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

	//! return the size of the structure SbfDataVelCovGeodetic
         int getSizeOfStruct(){return sizeof(SbfDataVelCovGeodetic);};

	//! write the Data of the message in the DByte file
         virtual int writeDByte(road_time_t currentRoadtime, road_timerange_t currentTimerange);
        
         //! Display Data to stdout;
         virtual void stdoutDisplay();
	
   };

};


#endif

/*! 
\class SerialCOM_Msg_PosCovGeodetic
\brief Position Covariance matrix in Geodetic frame
\author C. Fouque
\version 1.0
\date dec. 2008
\bug None
\warning None

This block contains the elements of the symmetric variance-covariance matrix of the position expressed in the geodetic coordinates of the WGS-84 ellipsoid:

Please refer to the PosCovCartesian block description for a general explanation of the contents. 
Note that the units of measure for all the variances and covariances, for height as well as for latitude and longitude, are metres^2 for ease of interpretation.

In special cases all or some components of the variance-covariance matrix are undefined and set to their Do-Not-Use value:
    • 2D position fix: all height related components of the variance-covariance matrix are undefined and set to their Do-Not-Use value.
    • Base mode: all components, except the clock bias variance, of the variance-covariance matrix are undefined and set to their Do-Not-Use value
    • RTK mode (float or fix): all covariances between the position and clock bias are undefined and set to their Do-Not-Use value.

<b>Output rate:</b> if enabled, this block is generated together with the corresponding PVTGeodetic block.


 */

#pragma warning( once : 4290 )
#pragma warning( once : 4274 )

#ifndef _SerialCOM_Msg_PosCovGeodetic_Plrx_H
#define _SerialCOM_Msg_PosCovGeodetic_Plrx_H

#include <vector>
#include "SerialCOM_Msg.hpp"
#include "SerialCOM_Protocol.hpp"
#include "structure_septentrio.h"

namespace Plrx
{

   class SerialCOM_Msg_PosCovGeodetic : public SerialCOM_Msg , public SbfDataPosCovGeodetic
   {

      public : 

         /*! \brief Constructor. Intitialise the member variables*/
         SerialCOM_Msg_PosCovGeodetic();

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

	//! return the size of the structure SbfDataPosCovGeodetic
         int getSizeOfStruct(){return sizeof(SbfDataPosCovGeodetic);};

	//! write the Data of the message in the DByte file
         virtual int writeDByte(road_time_t currentRoadtime, road_timerange_t currentTimerange);
        
         //! Display Data to stdout;
         virtual void stdoutDisplay();
	
   };

};


#endif
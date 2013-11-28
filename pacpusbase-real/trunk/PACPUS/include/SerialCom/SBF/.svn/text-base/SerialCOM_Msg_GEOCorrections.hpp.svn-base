/*! 
   \class SerialCOM_Msg_GEOCorrections
   \brief Allows to handle GEOCorrections messages coming from a Polarx GPS receiver
   \author Clément Fouque
   \version 1.0
   \date Sept. 2008
   \bug None
   \warning None
   
This block contains the SBAS corrections that the receiver has applied to each pseudorange used in the
PVT computation. The corrections are based on the messages received from an SBAS satellite. They
compensate for the following errors:
•   Satellite orbit;
•   Satellite clock;
•   Ionospheric delay.

Output rate: if enabled, this block is generated at a nominal rate specified by the SetPVTInterval
and SetOutputDecimation commands.


 */

#ifndef _SerialCOM_Msg_GeoCorr_Plrx_H
#define _SerialCOM_Msg_GeoCorr_Plrx_H

#include <vector>
#include "structure_septentrio.h"
#include "SerialCOM_Msg.hpp"
#include "SerialCOM_Protocol.hpp"

namespace Plrx {
   
   class SerialCOM_Msg_GEOCorrections : public SerialCOM_Msg , public SbfDataGEOCorrections
   {
      public:

         SerialCOM_Msg_GEOCorrections();

	/*! \brief reset internal variables of the message after an error or the end of a message */
        /*! For more information see SerialCOM_Msg::reset*/
        void reset();
		
         /*! \brief Read the core of the message to check if the object is able to handle this message*/
         /*! For more information see SerialCOM_Msg::identify*/
         int identify(vector<unsigned char> *pbuffer);
		
         /*! \brief extracts the data of the message contained in the buffer vector*/
         /*! For more information see SerialCOM_Msg::formatData*/
         int formatData(vector<unsigned char> *pbuffer);

	//! return the size of the structure structNAV_SOL
         int getSizeOfStruct(){return sizeof(SbfDataGEOCorrections);};

         int fromStructFile(void *buf);
		
	//! write the Data of the message in the DByte file
         virtual int writeDByte(road_time_t currentRoadtime, road_timerange_t currentTimerange);
         
         //! Display Data to stdout;
         virtual void stdoutDisplay();
   };
   
};
#endif

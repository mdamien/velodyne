/*!
   \class SerialCOM_Msg_GPSRaw
   \author Clément Fouque
   \date Oct. 2008
   \version 1.0
   \bug none
   \warning none

   \brief Raw navigation bits from a GPS satellite (D(t) data modulated on the C/A code).

The GPSRaw block contains the 300 bits of a GPS subframe (the so-called “D(t)” data). The GPS subframe consists of ten 30-bit words, which are stored as ten 32-bit integers in the GPSRaw block. Refer to GPS ICD [3] for further details.\n
<b>Output rate:</b> if enabled, this block is generated each time a new subframe is received from a GPS satellite, if its parity is valid. Typically, the receiver outputs a new GPSRaw block every 6 seconds for each of the GPS satellites currently tracked.

*/

#ifndef __SERIALCOM_MSG_GPSRAW_HPP__
#define __SERIALCOM_MSG_GPSRAW_HPP__

#include <vector>
#include "structure_septentrio.h"
#include "SerialCOM_Msg.hpp"
#include "SerialCOM_Protocol.hpp"

namespace Plrx {

   class SerialCOM_Msg_GPSRaw : public SerialCOM_Msg , public SbfDataGPSRaw
   {
      public:

         SerialCOM_Msg_GPSRaw();

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
         int getSizeOfStruct(){return sizeof(SbfDataGPSRaw);};

         int fromStructFile(void *buf);

		//! write the Data of the message in the DByte file
         virtual int writeDByte(road_time_t currentRoadtime, road_timerange_t currentTimerange);

         //! Display Data to stdout;
         virtual void stdoutDisplay();
   };

};

#endif

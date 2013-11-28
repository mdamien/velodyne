/*!
\class SerialCOM_Msg_ShortMeasEpoch
\brief Measurement subset at a given epoch (CA/P1/P2/L1/L2)
\author C.Fouque
\version 1.0
\date Dec. 2008
\bug None
\warning None

This block contains a subset of observations for all tracked satellites for a particular epoch. This block minimizes log-file size and is an alternative to the MeasEpoch block for those users who intend to store code and carrier phase measurements for a long period of time. Compared to the MeasEpoch block, it contains code and carrier phase data in compressed form and the resolution of the C/N0 values is reduced. The ShortMeasEpoch block does not contain Doppler data, lock time, and channel number information. Please note that the Doppler data can be reconstructed by taking the time derivative of the carrier phase date.

This block also contains N ChannelData sub-blocks, each sub-block containing all the dual-frequency measurements for a given satellite and a given antenna.

For multi-antenna configurations, measurements from the different antennas are contained in successive sub-blocks. The AntennaID bits in the Flags field of each sub-block specifies the antenna to which this sub-block is referred.

<b>Output rate:</b> if enabled, this block is output at a rate defined by the SetMeasInterval and
SetOutputDecimation commands. If there are no measurements available for an epoch (due to
signal obstruction for example), the N field is set to 0.


 */

#pragma warning( once : 4290 )
#pragma warning( once : 4274 )

#ifndef _SerialCOM_Msg_ShortMeasEpoch_Plrx_H
#define _SerialCOM_Msg_ShortMeasEpoch_Plrx_H

#include <vector>
#include "SerialCOM_Msg.hpp"
#include "SerialCOM_Protocol.hpp"
#include "structure_septentrio.h"

namespace Plrx
{

   class SerialCOM_Msg_ShortMeasEpoch : public SerialCOM_Msg , public SbfDataShortMeasEpoch
   {

      public :

         /*! \brief Constructor. Intitialise the member variables*/
         SerialCOM_Msg_ShortMeasEpoch();

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

	//! return the size of the structure SbfDataShortMeasEpoch
         int getSizeOfStruct(){return sizeof(SbfDataShortMeasEpoch);};

	//! write the Data of the message in the DByte file
         virtual int writeDByte(road_time_t currentRoadtime, road_timerange_t currentTimerange);

         //! Display Data to stdout;
         virtual void stdoutDisplay();

   };

};


#endif
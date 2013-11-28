/*! 
\class SerialCOM_Msg_TrackingStatus
\brief Status of the tracking for all receiver channels
\author Vincent Drevelle
\version 1.0
\date Dec. 2008
\bug None
\warning None

This block describes the tracking status of the active receiver channels. Active channels are logical
channels to which a satellite has been allocated. This block contains as many sub-blocks as the
number of active channels. Each sub-block contains the following information:\n
• logical channel number,\n
• satellite ID allocated to that logical channel,\n
• current channel status,\n
• health information of the satellite,\n
• azimuth at which the satellite is observed,\n
• elevation at which the satellite is observed,\n
• direction of change of elevation (rise/set indicator)\n
The channel numbering in the PolaRx depends upon the channel configuration as set by the
SetChannelConfiguration command.\n
If one of the channels is inactive, i.e. no satellite is currently allocated to it, it will not be contained in
the TrackingStatus block. If for example all the satellites are disabled (using
SetSatelliteTracking all off), there will be no sub-blocks at all.\n
The health status of the satellite allocated to a certain channel is a condensed version of the health
status sent by the satellite. The GPSNav and GPSAlm blocks provide a more detailed health
information.\n
The azimuth and elevation at which satellites are observed by the receiver are defined in the local
horizontal plane: a satellite at the northern horizon will be observed at an elevation of zero degrees and
zero azimuth. As this information is based on both the orbit parameters transmitted by the satellite and
the computed position of the PolaRx it might be that the receiver will not be able to provide the
azimuth and elevation if one of the two data sources is not available.\n
<b>Output rate:</b> if enabled, this block is generated every 2 seconds, synchronously with the 2-second
boundaries of the receiver time.

 */

#pragma warning( once : 4290 )
#pragma warning( once : 4274 )

#ifndef _SerialCOM_Msg_TrackingStatus_Plrx_H
#define _SerialCOM_Msg_TrackingStatus_Plrx_H

#include <vector>
#include "SerialCOM_Msg.hpp"
#include "SerialCOM_Protocol.hpp"
#include "structure_septentrio.h"

namespace Plrx
{

   class SerialCOM_Msg_TrackingStatus : public SerialCOM_Msg , public SbfDataTrackingStatus
   {

      public : 

         /*! \brief Constructor. Intitialise the member variables*/
         SerialCOM_Msg_TrackingStatus();

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

	//! return the size of the structure SbfDataTrackingStatus
         int getSizeOfStruct(){return sizeof(SbfDataTrackingStatus);};

	//! write the Data of the message in the DByte file
         virtual int writeDByte(road_time_t currentRoadtime, road_timerange_t currentTimerange);
        
         //! Display Data to stdout;
         virtual void stdoutDisplay();
	
   };

};


#endif
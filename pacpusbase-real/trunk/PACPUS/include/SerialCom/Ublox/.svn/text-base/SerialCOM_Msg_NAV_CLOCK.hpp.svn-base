#ifndef _SerialCOM_Msg_NAV_CLOCK_Ublox_H
#define _SerialCOM_Msg_NAV_CLOCK_Ublox_H


#include <vector>
#include "structureUBX.h"
#include "SerialCOM_Msg.hpp"
#include "SerialCOM_Protocol.hpp"

namespace Ublox{

/*! \class SerialCOM_Msg_NAV_CLOCK
 *	\brief Allows to handle NAV-CLOCK messages coming from a Ublox GPS receiver
 *	\author Olivier LE MARCHAND
 *	\version 1.0
 *	\date February 2007
 *	\bug None
 *	\warning None
 *	
 *  Can identify an incoming message as a NAV-CLOCK message and extract information from\n
 *	Protocols definitions are available in the following document : \n
 *	Title:     ANTARIS Positioning Engine  \n
 *	Subtitle:  NMEA and UBX Protocol Specification  \n
 *	Doc Type:  Specification  \n
 *	Doc ID:    GPS.G3-X-03002-D \n 
 *	Firmware:  Version 5.00  
 *
 */

	class SerialCOM_Msg_NAV_CLOCK: public SerialCOM_Msg, public structNAV_CLOCK
	{
	public:

		SerialCOM_Msg_NAV_CLOCK(void);

		/*! \brief reset internal variables of the message after an error or the end of a 
		 *  message */
		/*! For more information see SerialCOM_Msg::reset*/
		void reset(void);
		
		/*! \brief Read the core of the message to check if the object is able to handle this
		 *  message*/
		/*! For more information see SerialCOM_Msg::identify*/
		int identify(vector<unsigned char> *pbuffer);
		
		/*! \brief extracts the data of the message contained in the buffer vector*/
		/*! For more information see SerialCOM_Msg::formatData*/
		int formatData(vector<unsigned char> *pbuffer);

		int fromStructFile(void *buf);

		//! return the size of the structure structNAV_CLOCK
		int getSizeOfStruct(){return sizeof(structNAV_CLOCK);};
		
		//! write the Data of the message in the DByte file
		virtual int writeDByte(road_time_t currentRoadtime, road_timerange_t currentTimerange);

	};

} // END namespace Ublox

#endif
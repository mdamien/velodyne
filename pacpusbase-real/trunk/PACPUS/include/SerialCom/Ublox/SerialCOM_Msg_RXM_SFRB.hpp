#ifndef _SerialCOM_Msg_RXM_SFRB_Ublox_H
#define _SerialCOM_Msg_RXM_SFRB_Ublox_H


#include <vector>
#include "structureUBX.h"
#include "SerialCOM_Msg.hpp"
#include "SerialCOM_Protocol.hpp"

namespace Ublox{

/*! \class SerialCOM_Msg_RXM_SFRB
 *	\brief Allows to handle RXM-SFRB messages coming from a Ublox GPS receiver
 *	\author "Olivier Le Marchand"
 *	\version 0.1
 *	\date February 2008
 *	\bug None 
 *	\warning None
 *	
 *  Can identify an incoming message as a RXM-SFRB message and extract information from\n
 *	Title:     ANTARIS Positioning Engine  \n
 *	Subtitle:  NMEA and UBX Protocol Specification  \n
 *	Doc Type:  Specification  \n
 *	Doc ID:    GPS.G3-X-03002-D \n 
 *	Firmware:  Version 5.00
 **/

	class SerialCOM_Msg_RXM_SFRB: public SerialCOM_Msg, public structRXM_SFRB
	{

	public:

		typedef struct
		{
			bool use120;
			bool use122;
			bool use124;
			bool use126;
			bool use129;
			bool use131;
			bool use134;
			bool use137;
		}structUsedSBASSV;

		SerialCOM_Msg_RXM_SFRB();

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

		//! return the size of the structure structRXM_SFRB
		int getSizeOfStruct(){return sizeof(structRXM_SFRB);};
		
		//! write the Data of the message in the DByte file
		virtual int writeDByte(road_time_t currentRoadtime, road_timerange_t currentTimerange);

		/*! \brief If the SFRB contains a message from a SBAS satellite, extract relevant data */
		std::vector<unsigned char> toSBASBuffer();

		int fromStructFile(void *buf);
		
		structUsedSBASSV usedSBASSV;

	};

} // END namespace Ublox{

#endif
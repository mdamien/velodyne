#ifndef _SerialCOM_Protocol_UBX_Ublox_H
#define _SerialCOM_Protocol_UBX_Ublox_H

#include <vector>
#include "SerialCOM_Protocol.hpp"

namespace Ublox{



/*! \class SerialCOM_Protocol_UBX
 *	\brief Allows to handle all messages coming from a ublox GPS
 *	\author Olivier LE MARCHAND
 *	\version 1.0
 *	\date july 2007
 *	\bug None
 *	\warning None
 *	
 *	UBX Protocol is define in the following documents : \n
 *	Title: ANTARIS Positioning Engine  \n
 *	Subtitle: NMEA and UBX Protocol Specification  \n
 *	Doc Type: Specification  \n
 *	Doc ID: GPS.G3-X-03002-D  \n
 *	Firmware Version: Version 5.00  \n
 *	This class applies this specification regarding to the SerialCOM_Protocol class
 *
 *
 */

class SerialCOM_Protocol_UBX : public SerialCOM_Protocol
{

public : 

	/*! \brief Constructor, Intitialise variables herited from the SerialCOM_Protocol class*/
	SerialCOM_Protocol_UBX();

	/*! \brief Check if the two first bytes of the buffer are respectively equal to 0xB5 
	 *	and 0x62, extract the length of the message from the header, and identified the 
	 *	message*/
	/*! For more information see SerialCOM_Protocol::verifiy_Header*/
	int verifiyHeader(vector<unsigned char> *pbuffer);

	/*! \brief Chek if the end of the message is reached, regarding to its size*/
	/*! For more information see SerialCOM_Protocol::msg_Complete*/
	int msgComplete(vector<unsigned char> *pbuffer);

	/*! \brief Apply the Check calculation algorithm and compare the results to the check 
	 *	bytes of the messge*/
	/*! For more information see SerialCOM_Protocol::check_Msg*/
	int checkMsg(vector<unsigned char> *pbuffer);

	/*! \brief If a message has been identified, call its format_data function, otherwise call the 
	 *	standar format_Data function of the SerialCOM_Protocol class*/
	/*! For more information see SerialCOM_Protocol::format_Data*/
	int formatData(vector<unsigned char> *pbuffer, long double msgTime = 0);

};

} // END namespace Ublox

#endif
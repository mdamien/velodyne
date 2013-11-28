#ifndef _SerialCOM_Protocol_SBAS_Ublox_H
#define _SerialCOM_Protocol_SBAS_Ublox_H

#include <vector>
#include "SerialCOM_Protocol.hpp"
#include "structureSBAS.h"
//#include "Crc32.h"

namespace SBAS{



/*! \class SerialCOM_Protocol_SBAS
 *	\brief Allows to handle all messages coming the SBAS protocol
 *	\author Olivier LE MARCHAND
 *	\version 1.0
 *	\date july 2007
 *	\bug None
 *	\warning None
 *	
 *	SBAS Protocol is define in the following documents : \n
 *	
 *	This class applies this specification regarding to the SerialCOM_Protocol class
 *
 *
 */

class SerialCOM_Protocol_SBAS : public SerialCOM_Protocol
{

public : 

	/*! \brief Constructor, Intitialise variables herited from the SerialCOM_Protocol class*/
	SerialCOM_Protocol_SBAS();

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
	 *	standard format_Data function of the SerialCOM_Protocol class*/
	/*! For more information see SerialCOM_Protocol::format_Data*/
	int formatData(vector<unsigned char> *pbuffer, long double msgTime = 0);

	
private:
	//Crc32 *pCrc32;

};


unsigned char typeIDExtract(vector<unsigned char> *pbuffer);

unsigned char preambleExtract(vector<unsigned char> *pbuffer);



/*inline unsigned short bytesSpread(unsigned short startBit, unsigned short length)
{
	unsigned short nbBytes;
	nbBytes = ((startBit+length-2)/8 - (startBit-1)/8 +1);
	return nbBytes;
};*/

} // END namespace SBAS

#endif
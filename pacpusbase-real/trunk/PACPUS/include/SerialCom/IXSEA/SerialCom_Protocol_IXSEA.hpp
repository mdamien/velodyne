#ifndef _SerialCOM_Protocol_IXSEA_H
#define _SerialCOM_Protocol_IXSEA_H

#include <vector>
#include "SerialCOM_Protocol.hpp"
using namespace std;


namespace ixsea{

/*! \class SerialCOM_Protocol_IXSEA
 *	\brief Allows to handle all IXSEA messages
 *	\author Olivier LE MARCHAND
 *	\version 1.0
 *	\date july 2007
 *	\bug None
 *	\warning None
 *	
 *	IXSEA messages begins with the 3 caracters $, G, P, and ends with the bytes 0x0D et 0x0A
 *	which are the back to line characters.
 *
 *
 */

class SerialCOM_Protocol_IXSEA : public SerialCOM_Protocol
{

public : 

	/*! \brief Constructor, Intitialise variables herited from the SerialCOM_Protocol class*/
	SerialCOM_Protocol_IXSEA();

	/*! \brief Same as SerialCOM_Protocol_IXSEA()*/
	SerialCOM_Protocol_IXSEA(unsigned char *outputPointer);

	/*! \brief Check if the three first bytes of the buffer are equal to '$GP'*/
	/*! For more information see SerialCOM_Protocol::verifiy_Header*/
	int verifiyHeader(vector<unsigned char> *pbuffer);

	/*! \brief Check if the two last bytes of the buffer are respectively equals to 
	 *	0x0D et 0x0A*/
	/*! For more information see SerialCOM_Protocol::msg_Complete*/
	int msgComplete(vector<unsigned char> *pbuffer);

	int formatData(vector<unsigned char> *pbuffer, long double msgTime);


};


} // END namespace Ublox{
#endif
#pragma warning( once : 4290 )
#pragma warning( once : 4274 )

#ifndef _SerialCOM_Msg_HEHDT_H
#define _SerialCOM_Msg_HEHDT_H

#include <vector>
#include "SerialCOM_Msg.hpp"
#include "SerialCOM_Protocol.hpp"
#include "HEHDT.hpp"



namespace ixsea{

/*! \class SerialCOM_Msg_HEHDT
 *	\brief Allows to handle HEHDT messages coming from a IXSEA sentence
 *	\author Olivier LE MARCHAND
 *	\version 1.0
 *	\date fehruary 2008
 *	\bug None
 *	\warning None
 *	
 *
 */

	class SerialCOM_Msg_HEHDT : public SerialCOM_Msg, public HEHDT
{

public : 

	/*! \brief Constructor. Intitialise the member variables*/
	SerialCOM_Msg_HEHDT();

	/*! \brief Copy constructor*/
	//SerialCOM_Msg_HEHDT (const SerialCOM_Msg_HEHDT &source);

	/*! \brief Set to 0 the member variables*/
	void reset();

	/*! \brief Check if the third and fourth byte of the vector are respectively equal to
	 *	0x02 and 0x10, which identifies a RXM-RAW message*/
	int identify(vector<unsigned char> *pbuffer);

	/*! \brief Extract the data from the message in the buffer to the member variable of 
	 *	object*/
	int formatData(vector<unsigned char> *pbuffer);

	//! return the size of the structure HEHDT
	int getSizeOfStruct(){return sizeof(HEHDT);};
};


} // END namespace ixsea{

#endif

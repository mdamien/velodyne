#pragma warning( once : 4290 )
#pragma warning( once : 4274 )

#ifndef _SerialCOM_Msg_POSITI_H
#define _SerialCOM_Msg_POSITI_H

#include <vector>
#include "SerialCOM_Msg.hpp"
#include "SerialCOM_Protocol.hpp"
#include "POSITI.hpp"



namespace ixsea{

/*! \class SerialCOM_Msg_POSITI
 *	\brief Allows to handle POSITI messages coming from a IXSEA sentence
 *	\author Olivier LE MARCHAND
 *	\version 1.0
 *	\date fehruary 2008
 *	\bug None
 *	\warning None
 *	
 *
 */

	class SerialCOM_Msg_POSITI : public SerialCOM_Msg, public POSITI
{

public : 

	/*! \brief Constructor. Intitialise the member variables*/
	SerialCOM_Msg_POSITI();

	/*! \brief Copy constructor*/
	//SerialCOM_Msg_POSITI (const SerialCOM_Msg_POSITI &source);

	/*! \brief Set to 0 the member variables*/
	void reset();

	/*! \brief Check if the third and fourth byte of the vector are respectively equal to
	 *	0x02 and 0x10, which identifies a RXM-RAW message*/
	int identify(vector<unsigned char> *pbuffer);

	/*! \brief Extract the data from the message in the buffer to the member variable of 
	 *	object*/
	int formatData(vector<unsigned char> *pbuffer);

	//! return the size of the structure POSITI
	int getSizeOfStruct(){return sizeof(POSITI);};
};


} // END namespace ixsea{

#endif

#pragma warning( once : 4290 )
#pragma warning( once : 4274 )

#ifndef _SerialCOM_Msg_HSPOS_H
#define _SerialCOM_Msg_HSPOS_H

#include <vector>
#include "SerialCOM_Msg.hpp"
#include "SerialCOM_Protocol.hpp"
#include "HSPOS.hpp"



namespace ixsea{

/*! \class SerialCOM_Msg_HSPOS
 *	\brief Allows to handle HSPOS messages coming from a IXSEA sentence
 *	\author Olivier LE MARCHAND
 *	\version 1.0
 *	\date fehruary 2008
 *	\bug None
 *	\warning None
 *	
 *
 */

	class SerialCOM_Msg_HSPOS : public SerialCOM_Msg, public HSPOS
{

public : 

	/*! \brief Constructor. Intitialise the member variables*/
	SerialCOM_Msg_HSPOS();

	/*! \brief Copy constructor*/
	//SerialCOM_Msg_HSPOS (const SerialCOM_Msg_HSPOS &source);

	/*! \brief Set to 0 the member variables*/
	void reset();

	/*! \brief Check if the third and fourth byte of the vector are respectively equal to
	 *	0x02 and 0x10, which identifies a RXM-RAW message*/
	int identify(vector<unsigned char> *pbuffer);

	/*! \brief Extract the data from the message in the buffer to the member variable of 
	 *	object*/
	int formatData(vector<unsigned char> *pbuffer);

	//! return the size of the structure HSPOS
	int getSizeOfStruct(){return sizeof(HSPOS);};
};


} // END namespace ixsea{

#endif

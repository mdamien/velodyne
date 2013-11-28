#pragma warning( once : 4290 )
#pragma warning( once : 4274 )

#ifndef _SerialCOM_Msg_STDSPD_H
#define _SerialCOM_Msg_STDSPD_H

#include <vector>
#include "SerialCOM_Msg.hpp"
#include "SerialCOM_Protocol.hpp"
#include "STDSPD.hpp"



namespace ixsea{

/*! \class SerialCOM_Msg_STDSPD
 *	\brief Allows to handle STDSPD messages coming from a IXSEA sentence
 *	\author Olivier LE MARCHAND
 *	\version 1.0
 *	\date fehruary 2008
 *	\bug None
 *	\warning None
 *	
 *
 */

	class SerialCOM_Msg_STDSPD : public SerialCOM_Msg, public STDSPD
{

public : 

	/*! \brief Constructor. Intitialise the member variables*/
	SerialCOM_Msg_STDSPD();

	/*! \brief Copy constructor*/
	//SerialCOM_Msg_STDSPD (const SerialCOM_Msg_STDSPD &source);

	/*! \brief Set to 0 the member variables*/
	void reset();

	/*! \brief Check if the third and fourth byte of the vector are respectively equal to
	 *	0x02 and 0x10, which identifies a RXM-RAW message*/
	int identify(vector<unsigned char> *pbuffer);

	/*! \brief Extract the data from the message in the buffer to the member variable of 
	 *	object*/
	int formatData(vector<unsigned char> *pbuffer);

	//! return the size of the structure STDSPD
	int getSizeOfStruct(){return sizeof(STDSPD);};
};


} // END namespace ixsea{

#endif

#pragma warning( once : 4290 )
#pragma warning( once : 4274 )

#ifndef _SerialCOM_Msg_GST_H
#define _SerialCOM_Msg_GST_H

#include <vector>
#include "SerialCOM_Msg.hpp"
#include "SerialCOM_Protocol.hpp"
#include "qstring.h"
#include "NMEA0183_slim.H"
#include "LATLONG.HPP"
#include "SENTENCE.HPP"
#include "RESPONSE.HPP"
#include "GST.HPP"
#include "structure_gps.h"



namespace NMEA{

/*! \class SerialCOM_Msg_GST
 *	\brief Allows to handle GST messages coming from a NMEA sentence
 *	\author Olivier LE MARCHAND
 *	\version 1.0
 *	\date fehruary 2008
 *	\bug None
 *	\warning None
 *	
 *
 */

	class SerialCOM_Msg_GST : public SerialCOM_Msg, public GST
	{

	public : 

		/*! \brief Constructor. Intitialise the member variables*/
		SerialCOM_Msg_GST();

		/*! \brief Copy constructor*/
		//SerialCOM_Msg_RXM_SBAS (const SerialCOM_Msg_RXM_SBAS &source);

		/*! \brief Set to 0 the member variables*/
		void reset();

		/*! \brief Check if the third and fourth byte of the vector are respectively equal to
		 *	0x02 and 0x10, which identifies a RXM-RAW message*/
		int identify(vector<unsigned char> *pbuffer);

		/*! \brief Extract the data from the message in the buffer to the member variable of 
		 *	object*/
		int formatData(vector<unsigned char> *pbuffer);

		//! return the size of the structure trame_gst
		int getSizeOfStruct(){return sizeof(trame_gst);};

		trame_gst toTrame_gst();

		//! write the Data of the message in the DByte file
		virtual int writeDByte(road_time_t currentRoadtime, road_timerange_t currentTimerange);
};


} // END namespace Ublox{

#endif

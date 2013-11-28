#ifndef _SerialCOM_Msg_MT1_Ublox_H
#define _SerialCOM_Msg_MT1_Ublox_H


#include <vector>
#include "structureSBAS.h"
#include "SerialCOM_Msg.hpp"
#include "SerialCOM_Protocol.hpp"
#include "SerialCOM_Protocol_SBAS.hpp"

namespace SBAS{

/*! \class SerialCOM_Msg_MT1
 *	\brief Allows to handle MT1 messages from SBAS
 *	\author "Olivier Le Marchand"
 *	\version 0.1
 *	\date July 2008
 *	\bug None 
 *	\warning None
 *	
 *  Can identify an incoming message as a MT1 message and extract information from\n
 **/

	class SerialCOM_Msg_MT1: public SerialCOM_Msg, public SBAS::structPRNMaskAssignement
	{

	public:

		SerialCOM_Msg_MT1(void);

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

		//! return the size of the structure structPRNMaskAssignement
		int getSizeOfStruct(){return sizeof(SBAS::structPRNMaskAssignement);};
		
		//! write the Data of the message in the DByte file
		virtual int writeDByte(road_time_t currentRoadtime, road_timerange_t currentTimerange);

	};

} // END namespace SBAS{

#endif
#ifndef _SerialCOM_Msg_MT2to5_Ublox_H
#define _SerialCOM_Msg_MT2to5_Ublox_H


#include <vector>
#include "structureSBAS.h"
#include "SerialCOM_Msg.hpp"
#include "SerialCOM_Protocol.hpp"
#include "SerialCOM_Protocol_SBAS.hpp"

namespace SBAS{

/*! \class SerialCOM_Msg_MT2to5
 *	\brief Allows to handle MT1 messages from SBAS
 *	\author "Olivier Le Marchand"
 *	\version 0.1
 *	\date July 2008
 *	\bug None 
 *	\warning None
 *	
 *  Can identify an incoming message as a MT1 message and extract information from\n
 **/

	class SerialCOM_Msg_MT2to5: public SerialCOM_Msg, public SBAS::structFastCorrections
	{

	public:

		inline unsigned char getMTid() {return MTid;};

		
		/*! \brief Constructor */
		/*! \param MT0enabled Define if MT0 message as to be considered as a MT2 message*/
		SerialCOM_Msg_MT2to5(bool MT0enabled = false);

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

		//! return the size of the structure structFastCorrections
		int getSizeOfStruct(){return sizeof(SBAS::structFastCorrections);};
		
		//! write the Data of the message in the DByte file
		virtual int writeDByte(road_time_t currentRoadtime, road_timerange_t currentTimerange);

	protected:

		//! identifiant du message
		unsigned char MTid;

		//! save if MT0 messages can be considered as MT2 messages or not
		bool MT0included;

	};

} // END namespace SBAS{

#endif
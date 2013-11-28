#ifndef _SerialCOM_Protocol_SBF_Ublox_H
#define _SerialCOM_Protocol_SBF_Ublox_H

#include <vector>
#include <math.h>
#include "SerialCom/SerialCOM_Protocol.hpp"

/*! 
   \class SerialCOM_Protocol_SBF
   \brief Allows to handle all messages coming from a PolarX GPS
   \author Olivier LE MARCHAND & Clément Fouque
   \version 1.0.2
   \date September 2008
   \bug None
   \warning None
   \todo Nothing

   <b>Last Update (14/10/2008) :</b> Adding CRC Check for SBF frame.

 */

namespace Plrx {

class SerialCOM_Protocol_SBF : public SerialCOM_Protocol
{

public : 

	/*! \brief Constructor, Intitialise variables herited from the SerialCOM_Protocol class*/
	SerialCOM_Protocol_SBF();

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
        
   private:
      /*! Look up table for fast computation of the CCITT 16-bit CRC. */
      unsigned short CRCLookUp[256] ;

};

}

#endif
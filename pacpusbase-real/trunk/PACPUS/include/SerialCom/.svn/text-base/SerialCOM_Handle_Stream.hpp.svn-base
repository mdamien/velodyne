#ifndef _SerialCOM_Handle_Stream_H
#define _SerialCOM_Handle_Stream_H
//#define max(a,b) (a>=b?a:b)

#include <vector>
#include <string>

#include "SerialCOM_Protocol.hpp"
#include "SerialCOM_Msg.hpp"

using namespace std;

#define MAX_PROTOCOL 10
#define MAX_PROTOCOL_SIZE 1000





/*! \class SerialCOM_Handle_Stream
 *	\brief Allows to handle all messages coming from a ublox GPS
 *	\author Olivier LE MARCHAND
 *	\version 1.0
 *	\date july 2007
 *	\bug None
 *	\warning None
 *	
 *	This class allows to manage all messages coming from a serial communication. A serial 
 *	communication can carry at the same time different protocols which contain themselfs
 *	various types of messages \n
 *	References to protocol objects are stored in the SerialCOM_Handle_Stream::tabProtocol
 *  and each time a new data from the serial communication buffer, the addData function is called.
 *	This function tries to identify the protocol used, to bufferize the whole message, and realizes 
 *  relevant treatments regarding to the identified protocol.\n
 *  
 */

class SerialCOM_Handle_Stream
{

public:
	
	/*! \brief Constructor function. Just initalise to 0 or NULL all member variables and 
	 * clear the buffer*/
	SerialCOM_Handle_Stream(int gnlVerbose);

	/*! \brief returns the protocol ID of the current identified protocol*/
	const int getCurProtocolID() const {return curProtocolID;};

	/*! \brief returns a pointer to the current identified protocol*/
	SerialCOM_Protocol *getCurProtocolPointer()
	{
		if (iProtocolFound==-1)
			return NULL;
		else
			return (*this).tabProtocol[iProtocolFound];
	};

	/*! \brief returns a pointer to the current identified Msg*/
	SerialCOM_Msg *getCurMsgPointer(){
		if (iProtocolFound==-1)
			return NULL;
		else
			return (*this).tabProtocol[iProtocolFound]->getCurMsgPointer();
	}

	/*! \brief returns the message ID of the current identified message*/
	const int getCurMsgID() const {return curMsgID;};

	/*! \brief integer value equal to 1 if the object has to generate more information messages*/
	int verbose;	

	/*! \brief transmit the informationText variable to be printed and clear it*/
	string getInformationText();

	/*! \brief Treats all the data coming from the serial buffer*/
    /*! The architecture of tis function is the following :\n
	 * It bufferizes a minimum of bytes to be able to extract the Header of any protocol.\n
	 * If no correct header is recognized, the function flush the actual serial buffer, and reset 
	 * the message data.\n
	 * If the header is linked to a protocol, the buffer is compiled until the message is full\n
	 * Check the validity of the whole message if possible\n
	 * Apply the formatData function.
      \param pserial_buffer a pointer to the partial message obtained on the serial COM port
      \param serial_Buffer_Size the size of the buffer pointed by pserial_buffer
	  \param start_Read_Pos the position at which we have to start reading the buffer
	  \param pnb_Read a pointer to an integer variable used to return the number of bytes read by the function before it's return
	  \param pmsg_Info pointer to a struct_Msg_Info structure used to inform about the properties of the message returned
	  \param frameTime time of reception of this data frame
      \return an integer, equal to 1 if a message is complete and 0 otherwise
    */ 
	int addData(unsigned char *pserial_buffer, int serial_Buffer_Size,int start_Read_Pos, int* pnb_Read,long double frameTime = 0);
	

	/*! \brief Add a the specifications of a protocol to handle during the communication*/
	/*! Add the protocol, which is an object herited from the SerialCOM_Protocol class
	 *  in the array tabProtocol, and increment the variable nbMsg.\n
	 *  A maximum of 10 messages can be attached to an object.
	  \param pProtocol a pointer on a SerialCOM_Protocol object
      \return 1 if the protocol specification has been correctly added, 0 otherwise
    */ 
	int addProtocol(SerialCOM_Protocol *pProtocol);

	/*! \brief reset internal variables of the handler after an error or the end of a 
	 *  message, and call the reset function of the current protocol*/
	void msgReset();

private: 

	/*! \brief Array where pointers to all the procols to handle is stored */
	SerialCOM_Protocol *tabProtocol[MAX_PROTOCOL];

	/*! \brief Used to transfers textual information when an error or something else happen */
	string informationText;

	/*! \brief bufferize the whole message coming from the RS232*/
	/*! RS232 communication doesn't allow to access in one time to the whole message. 
	 *	It is cut in many parts accessible by a buffer of a small size. This variable 
	 *	allows to concatenate all the small parts to retrieve the whole message*/
	vector<unsigned char> buffer;	

	/*! \brief Maximum header size of all the protocols adde to the handle_Msg object*/
	unsigned int headerMaxSize;

	/*! \brief Number of protocols added to the handle_Msg object*/
	unsigned int nbProtocol;

	/*! \brief Index of the currently identified protocol in the pointers array 
	 *	tabProtocol[MAX_PROTOCOL]. Initialized to -1*/
	int iProtocolFound;

	/*! \brief ID of the currently identified protocol. Equal to -1 if no protocol has 
	 *	been identified*/
	int curProtocolID;

	/*! \brief ID of the currently identified message. Equal to -1 if no message has 
	 *	been identified*/
	int curMsgID;

	/*! \brief Equals to 1 if a message has been formatted and can be reset*/
	int msg_Formatted;

	/*! \brief Call the formatData of the currentluy identified protocol and put 
	 *	msg_formatted to 1*/
	void formatData();

	/*! \brief time of the current message*/
	long double msgFirstFrameTime;

};


#endif
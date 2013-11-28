#ifndef _SerialCOM_Protocol_H
#define _SerialCOM_Protocol_H

#include <vector>
#include "SerialCOM_Msg.hpp"
#include <string>
#include <set>
using namespace std;

#define MAX_OUTPUT_BUFFER 10000
#define MAX_MSG 20



/*! \class SerialCOM_Protocol
 *	\brief Define the variables and functions of a protocol to be used by a
 * SerialCOM_Handle_Stream object
 *	\author Olivier LE MARCHAND
 *	\version 1.0
 *	\date july 2007
 *	\bug None
 *	\warning None
 *
 *	To identify a message transmitted by a serial comunication, the SerialCOM_Handle_Stream
 *  class has to know the specifications of the all the communication protocols. Those specifications
 *  are the length of the messages, their header, their end, and how to verifiy if they don't have
 *  been corrupted during the transmission.\n
 *  The fundamental specifications are translated in the functions SerialCOM_Protocol::verifiyHeader
 *  and SerialCOM_Protocol::msgComplete, which are pure virtual functions. Other functions and variables
 * are included to realize standard treatments with each protocol.
 */

class SerialCOM_Protocol
{

public:


	/*! \brief integer value equal to 1 if the object has to generate more information messages */
	int verbose;

	/*! \brief Constructor function. Just initalize all member variables*/
	 SerialCOM_Protocol();

	 /*! \Delete SerialCOM_Msg Objects whose pointers are contained in the setOfMsg */
	void clear();

	/*! \brief Constructor function. Just initalise members variables and
	 * assign output_Pointer to the member variable output_pProtocol */
	SerialCOM_Protocol(unsigned char *output_Pointer);

	/*! \brief transmit the informationText variable to be printed and clear it*/
	string getProtocolName();

	/*! \brief transmit the informationText variable to be printed and clear it*/
	string getInformationText();

	/*! \brief Accessor to the private member variable: headerSize */
	const unsigned int get_headerSize() const {return headerSize;};

	/*! \brief Accessor to the private member variable: ID */
	const int getProtocolID() const {return protocolID;};

	/*! \brief Accessor to the private member variable: size */
	const int getSize() const {return size;};

	/*! \brief If a message of the protocol has been identified, return its ID */
	virtual int getCurMsgID();

	SerialCOM_Msg *getCurMsgPointer()
	{
		if (msgFoundIt==setOfMsg.end())
			return NULL;
		else
			return (*msgFoundIt);
	};


	/*! \brief realizes a standard treatment on the message contained in the buffer vector*/
    /*! After that a whole message is buffered in the buffer vector, we call this function\n
	 * The default behavior is to copy the buffer in an appropriate variable, pointed by
	 * the member variable output_pProtocol\n
	 \param pbuffer pointer to the std::vector containing the part of the message
	   currently buffered
	 \param frameTime Time of arrival of the first frame of the message
     \return 1 if the expected treatment is done, 0 otherwise*/
	virtual int formatData(vector<unsigned char> *pbuffer, long double msgTime = 0);

	/*! \brief Verifiy is the message header corresponds to the protocol*/
	/*! Read the headerSize firsts bytes of the buffer and check if they are compliant
	 *  with the protocol specification.\n
	 *  pure virtual function, HAS TO BE OVERWRITTEN.
	  \param pbuffer pointer to the std::vector containing the part of the message
	   currently buffered
      \return 1 if the protocol has identified its header in the message, 0 otherwise
    */
	virtual int verifiyHeader(vector<unsigned char> *pbuffer) =0;

	/*! \brief Verifiy if  we have to continue to bufferize or if the message is complete*/
	/*! Read the buffer and check if the message is complete, according to the the
	 *  protocol specification.\n
	 *  pure virtual function, HAS TO BE OVERWRITTEN
	  \param pbuffer pointer to the std::vector containing the part of the message
	   currently buffered
	 \return 1 if the message is complete, 0 otherwise
	*/
	virtual int msgComplete(vector<unsigned char> *pbuffer) =0;


	/*! \brief Verify if the message has not been corrupted during the transmission*/
	/*! If the protocol contains check_funtions, they have to be implemented here.\n
	 *  Called when the message is complete
	  \param pbuffer pointer to the std::vector containing the message currently buffered
      \return 1 if the check is ok, 0 otherwise
    */
	virtual int checkMsg(vector<unsigned char> *pbuffer);


	/*! \brief reset internal variables of the protocol after an error or the end of a
	 *  message */
	virtual void msgReset();

	/*! \brief Add a message using the protocol*/
	/*! add the message, which is an object herited from the SerialCOM_Msg class
	 *  in the std::set setOfMsg.\n
	  \param newMsg  a pointer on a SerialCOM_Msg object
      \return 1 if the message specification has been correctly added, 0 otherwise
    */
	int addMsg(SerialCOM_Msg *newMsg);

	/*! \brief Remove a message using the protocol*/
	/*! Remove the message, which is an object herited from the SerialCOM_Msg class
	 *  in the std::set setOfMsg.\n
	  \param oldMsg  a pointer on a SerialCOM_Msg object
      \return 1 if the message specification has been correctly removed, 0 otherwise
    */
	int removeMsg(SerialCOM_Msg *oldMsg);

	/*! \brief returns the time of arrival of the last message identified and completed using this protocol*/
	const long double getLastMsgTime() const {return lastMsgTime;};



protected :

	/*! \brief protocol name, for debug purpose */
	string protocolName;

	/*! \brief Used to transfers textual information when an error or something else happen */
	string informationText;

	/*! \brief Search if we can identify a message for this protocol*/
	/*! Call the identify function for each message in the tabMsg array, and return
	 *  the index of the last message identified
	  \param pbuffer pointer to the std::vector containing the message currently buffered
      \return the index of the message identified. If no message has beeen identified, return -1.
    */
	virtual int searchMsg(vector<unsigned char> *pbuffer);


	/*! \brief pointer to an array of 1000 unsigned char*/
	/*! Initialized to NULL, used to copy the whole message identified by the protocol to
	 *  an external array*/
	unsigned char *output_pProtocol;


	/*! \brief set container of possible messages attached to this protocol*/
	/*! The function addMsg(SerialCOM_Msg *pprop_Msg) must be used to fill the set.*/
	std::set<SerialCOM_Msg*> setOfMsg;


	std::set<SerialCOM_Msg*>::iterator msgFoundIt;



	/*! \brief Define the number of bytes which is necessar to bufferize before being
	 *  able to read the Header*/
	int headerSize;

	/*! \brief identifier of the protocol. Two protocols shouldn't have the same ID*/
	/*! Currently, the ID of the implemented protocols are : \n
	 *  1 : NMEA\n
	 *  2 : UBX\n
	 *  The ID has to be initialized in the constructor of the protocol object
    */
	int protocolID;

	/*! \brief Number of bytes used for the current whole message*/
	int size;

	/*! \brief Time of the last message identified and completed using this protocol*/
	long double lastMsgTime;


};



#endif

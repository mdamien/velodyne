#ifndef _SerialCOM_Msg_H
#define _SerialCOM_Msg_H

#include <vector>
#include <string>
#include <iostream>
#include "io_hdfile.h"
#include "PacpusTools/BinaryDecoder.h"
using namespace std;


/*! \class SerialCOM_Msg
 *	\brief Define necessary functions and variables in order to identify a message 
 *  type and apply relevant treatments
 *	\author Olivier LE MARCHAND
 *	\version 1.0
 *	\date july 2007
 *	\bug None
 *	\warning None
 *	
 *	After a protocol has handle the start, the end, and the core of a message, it can 
 *	call SerialCOM_Msg objects to manage the core of the data. Each type of message
 *	has its own class, the ability to identify itself, and to treat its own data.
 *
 */
//class SerialCOM_Msg_Comp;

class SerialCOM_Msg 
{

//	friend SerialCOM_Msg_Comp;

public : 
   


	SerialCOM_Msg();

	/*! \brief Destructor. Close DByte files if their header are not equal to NULL*/
	~SerialCOM_Msg();

	/*! \brief transmit the informationText variable to be printed and clear it*/
	string getInformationText();

	/*! \brief extracts the data of the message contained in the buffer vector*/
    /*! After that a whole message is buffered in the buffer vector, the protocol object
	 *  can call this function of the SerialCOM_Msg object to extract the data of this 
	 *  particular message.\n
	 *  The default behavior is to do nothing and to return 0\n
	 *  pure virtual function, HAS TO BE OVERWRITTEN.
	 * \return 1 if the expected treatment is done, 0 otherwise.
    */ 
	virtual int formatData(vector<unsigned char> *pbuffer)=0;

	/*! \brief extracts the data of the message contained in the buffer vector*/
    /*! Same function as virtual int formatData(vector<unsigned char> *pbuffer)=0; but take
	 *  in account the time of arrival of the frame
    */ 
	int formatData(vector<unsigned char> *pbuffer, long double msgTime);


	/*! \brief Read the core of the message to check if the object is able to handle this
	 *  message*/
	/*! Read the necessary bytes to check if the object is able to handle this
	 *  message\n 
	 *  pure virtual function, HAS TO BE OVERWRITTEN.
	  \param pbuffer pointer to the std::vector containing the part of the message 
	   currently buffered
      \return 1 if the message is identified, 0 otherwise
    */ 
	virtual int identify(vector<unsigned char> *pbuffer)=0;

	/*! \brief reset internal variables of the message after an error or the end of a 
	 *  message */
	virtual void reset();

	/*! \brief returns the ID of the protocol */
	const int getID() const {return ID;};

	/*! \brief returns the time of arrival of the message */
	const long double getMsgTime() const {return msgTime;};

	//! return the name of the message
	const std::string getName() {return name;};

	//! return the identifier for the DByte files
	const int getDbtType(){return DbtType;};

	//! return the size of the structure containing data
	virtual int getSizeOfStruct(){return 0;};

	virtual int fromStructFile(void *buf)
		{return 0;};

	//! used in DByte 
	bool recording;

	//! used in DByte
	hdfile_t *DByteFileHeader;

	//! virtual function you have to overwrite for each message Type
	virtual int writeDByte(road_time_t currentRoadtime, road_timerange_t currentTimerange);
        
        //! Virtual fuction to display data. Empty by default
        virtual void stdoutDisplay() {} ;

		/*! \brief extracts four consecutive bytes of the buffer 
	 * and interpret it as a float IEEE 754
	 *
	  \param startByte for "start position", define the position of the first byte of the 
	  four bytes of the float in the vector buffer
      \return the corresponding float value
    */ 
	static const float bufferToFloat(int startByte, vector<unsigned char> *pbuffer); 


	/*! \brief extracts four consecutive bytes of the buffer 
	 * and interpret it as an long integer
	 *!
	  \param startByte for "start position", define the position of the first byte of the 
	  four bytes of the long integer in the vector buffer
      \return the corresponding long integer value
    */ 
	static const long bufferToLong(int startByte, vector<unsigned char> *pbuffer);

	/*! \brief extracts four consecutive bytes of the buffer 
	 * and interpret it as an unsigned long integer
	 *!
	  \param startByte for "start position", define the position of the first byte of the 
	  four bytes of the long integer in the vector buffer
      \return the corresponding long integer value
    */ 
	static const unsigned long bufferToULong(int startByte, vector<unsigned char> *pbuffer);


	/*! \brief extracts eight consecutive bytes of the buffer 
	 * and interpret it as a double IEEE 754
	 *!
	  \param startByte for "start position", define the position of the first byte of the 
	  eight bytes of the double in the vector buffer
      \return the corresponding double value
    */ 
	static const double bufferToDouble(int startByte, vector<unsigned char> *pbuffer);


	/*! \brief extracts two consecutive bytes of the buffer 
	 * and interpret it as a unsigned short
	 *!
	  \param startByte for "start position", define the position of the first byte of the 
	  two bytes of the unsigned short in the vector buffer
      \return the corresponding unsigned short value
    */ 
	static const unsigned short bufferToUShort(int startByte, vector<unsigned char> *pbuffer);


	/*! \brief extracts two consecutive bytes of the buffer 
	 * and interpret it as a signed short
	 *!
	  \param startByte for "start position", define the position of the first byte of the 
	  two bytes of the signed short in the vector buffer
      \return the corresponding signed short value
    */ 
	static const short bufferToShort(int startByte, vector<unsigned char> *pbuffer);

	static unsigned short bytesSpread(unsigned short startBit, unsigned short length)
	{
		unsigned short nbBytes;
		nbBytes = ((startBit+length-2)/8 - (startBit-1)/8 +1);
		return nbBytes;
	}

	static char extractChar(vector<unsigned char> *pbuffer, unsigned short startBit, unsigned short length);

	static short extractShort(vector<unsigned char> *pbuffer, unsigned short startBit, unsigned short length);

	static long extractLong(vector<unsigned char> *pbuffer, unsigned short startBit, unsigned short length);

	static unsigned short extractUShort(vector<unsigned char> *pbuffer, unsigned short startBit, unsigned short length);

	static unsigned long extractULong(vector<unsigned char> *pbuffer, unsigned short startBit, unsigned short length);

protected : 

	/*! \brief Time of arrival of the message*/
	long double msgTime;

	/*! \brief Used to transfers textual information when an error or something else happen */
	string informationText;

	//! name of the message
	string name;

	/*! \brief identifier of the message. Two protocols shouldn't have the same ID*/
	/*! This ID has to be defined, if not initialised to -1*/
	int ID;

	/*! \brief type identifier for DBT files*/
	int DbtType;

};


/*class SerialCOM_Msg_Comp{
	bool operator() (const SerialCOM_Msg **left, const SerialCOM_Msg **right) const
	{return (*left)->ID<(*right)->ID;}
};*/

#endif

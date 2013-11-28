/// @date created 2013/05/06 - 17:01
/// @author Pierre Hudelaine
/// @version $Id: EsdCanDriver.cpp 888 2010-11-16 07:59:53Z phudelai $

#include "EsdCanDriver.h"

#include <cassert>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <string>

#include "kernel/Log.h"

using namespace pacpus;
using namespace std;

DECLARE_STATIC_LOGGER("pacpus.base.EsdCanDriver");

#define WAIT_RECEIVING_FRAME_TIMEOUT 1000

#define RX_QUEUE_SIZE 4096
#define QUEUE_LEVEL 1


int EsdCanDriver::speedConverter(int baudrate)
{
	switch(baudrate)
	{
		case 1000:
		{
			return NTCAN_BAUD_1000;		
			break;
		}
		case 800:
		{
			return NTCAN_BAUD_800;
			break;
		}
		case 666:
		{
			return 1;
			break;
		}
		case 500:
		{
			return NTCAN_BAUD_500;
			break;
		}
		case 333:
		{
			return 3;
			break;
		}
		case 250:
		{
			return NTCAN_BAUD_250;
			break;
		}
		case 166:
		{
			return 5;
			break;
		}
		case 125:
		{
			return NTCAN_BAUD_125;
			break;
		}
		case 100:
		{
			return NTCAN_BAUD_100;
			break;
		}
		case 83:
		{
			return 10;
			break;
		}
		case 66:
		{
			return 8;
			break;
		}
		case 50:
		{
			return NTCAN_BAUD_50;
			break;
		}
		case 20:
		{
			return NTCAN_BAUD_20;
			break;
		}
		case 10:
		{
			return NTCAN_BAUD_10;
			break;
		}
		default:
		{
			return NTCAN_BAUD_125;
			break;
		}
	}		
}

/**
* Constructor which enables to initialize the different attributes of the class with default values.
*/

EsdCanDriver::EsdCanDriver(int channel, unsigned int bitRate)
{
	LOG_INFO("Notice : ESD CAN Driver used\n");

	#ifdef CANTEST_DYNLOAD
		DynLoad();
	#endif /* of CANTEST_DYNLOAD */

	printf("%x\n",canOpen( channel, 0, 4096, RX_QUEUE_SIZE, WAIT_RECEIVING_FRAME_TIMEOUT, WAIT_RECEIVING_FRAME_TIMEOUT, &esd_handle_ ) );

	canSetBaudrate( esd_handle_, speedConverter(bitRate) );

	// Ne lit que la trame 272 (visiblement la seule avec de l'info)
	canIdAdd( esd_handle_, 272);
	canIdAdd( esd_handle_, 288);
}


/**
* Constructor which enables to initialize the different attributes of the class with default values.
*/

EsdCanDriver::EsdCanDriver(void)
{
	LOG_INFO("Notice : ESD CAN Driver used\n");

	printf("%x\n",canOpen( 0, 0, 4096, RX_QUEUE_SIZE, WAIT_RECEIVING_FRAME_TIMEOUT, WAIT_RECEIVING_FRAME_TIMEOUT, &esd_handle_ ) );

	canSetBaudrate( esd_handle_, NTCAN_BAUD_125 );

	// Ne lit que la trame 272 (visiblement la seule avec de l'info)
	canIdAdd( esd_handle_, 272);
	canIdAdd( esd_handle_, 288);
}	


EsdCanDriver::EsdCanDriver( int channel )
{
	LOG_INFO("Notice : ESD CAN Driver used\n");

	printf("%x\n",canOpen( channel, 0, 4096, RX_QUEUE_SIZE, WAIT_RECEIVING_FRAME_TIMEOUT, WAIT_RECEIVING_FRAME_TIMEOUT, &esd_handle_ ) );

	canSetBaudrate( esd_handle_, NTCAN_BAUD_125 );

	// Ne lit que la trame 272 (visiblement la seule avec de l'info)
	canIdAdd( esd_handle_, 272);
	canIdAdd( esd_handle_, 288);
}

short EsdCanDriver::initPort (void)
{

	return 0;
}


/**
* Member used to clean up the configuration of the CAN Card.
* @see initPort (void)
* @return a Vstatus variable which contain the error code of the function. On success, it return VSUCCESS. On failure, it return Vstatus error code which is defined in VCanD.h
*/
short EsdCanDriver::cleanUpPort (void)
{
	
	return 0;
}


EsdCanDriver::~EsdCanDriver()
{
	// Fermeture
	canClose( esd_handle_ );
}


/**
* Member which permit to send a frame on the CAN bus and test if the frame is well acknowledged.
*/
short EsdCanDriver::sendFrame (struct CanFrame frame)
{
	CMSG cmsg;
	int32_t count = 1;

	cmsg.id = frame.id;
	cmsg.len = frame.dlc;
	memcpy( cmsg.data, frame.data, frame.dlc );
	canSend( esd_handle_, &cmsg, &count );

	return 1;
}


/**
* Member which permit to receive of a frame on the CAN bus.
*/
short EsdCanDriver::receiveFrame (struct CanFrame &frame)
{
	int32_t count = 1;
	CMSG cmsg;
	NTCAN_RESULT canReadRes;

	if ( ( canReadRes = canRead( esd_handle_, &cmsg, &count , NULL ) ) == NTCAN_SUCCESS ) 
	{
		frame.id = cmsg.id;
		frame.dlc = static_cast<uint8_t>( cmsg.len );
		memcpy( frame.data, cmsg.data, frame.dlc);

		printf("id : %d  dlc : %d  data : ", frame.id, frame.dlc );
		
		for (int i = 0; i < frame.dlc ; i++)
			printf("%x  ", frame.data[i]);

		printf("\n");
		
		return 0;

	} else {

		printf("%x\n", canReadRes );
		return 1;
	}

	return 0;
}


/**
* Member which wait the reception of a frame on the CAN bus.
*/
void EsdCanDriver::waitReceivingFrame(void)
{

}

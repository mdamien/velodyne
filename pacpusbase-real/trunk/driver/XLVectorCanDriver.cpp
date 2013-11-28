/// @date created 2006/08/07 - 14:14
/// @author Gerald Dherbomez
/// @version $Id: XLVectorCanDriver.cpp 888 2010-11-16 07:59:53Z gdherbom $

#include "XLVectorCanDriver.h"

#include <cassert>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <string>

#include "kernel/Log.h"

using namespace pacpus;
using namespace std;

DECLARE_STATIC_LOGGER("pacpus.base.XLVectorCanDriver");

#define WAIT_RECEIVING_FRAME_TIMEOUT 1000

#define RX_QUEUE_SIZE 4096
#define QUEUE_LEVEL 1

bool checkXlStatus(const XLstatus status) {
	if ( status != XL_SUCCESS ) {
		XLstringType error = xlGetErrorString(status);
		LOG_ERROR(error);
		return false;
	} else {
		return true;
	}

}

XLstatus traceXLCommand(char * cmd, XLstatus status)
{
	LOG_TRACE(cmd << " : " << xlGetErrorString(status));
	checkXlStatus(status);
	return status;
}

/**
* Constructor which enables to initialize the different attributes of the class with default values.
* @see ~XLVectorCanDriver (void)
* @see XLVectorCanDriver (unsigned int gHwTypeT, Vaccess gChannelMaskT, unsigned int gCanIdT, unsigned int gBitRateT,int gHwChannelT)
*/

XLVectorCanDriver::XLVectorCanDriver(int channel, unsigned int bitRate)
{
  LOG_INFO("Notice : VECTOR XL CAN Driver used\n");
  /*
  gPortHandle		= INVALID_PORTHANDLE;
  gChannelMask	= 0x3;
  gPermissionMask	= 0;
  gCanId			= 0x2A9;
  gBitRate		= bitRate;
  gHwType			= HWTYPE_CANAC2PCI;
  gHwChannel		= channel;
  gEventHandle	= 0;
  */
  traceXLCommand("xlOpenDriver", xlOpenDriver());
  //  initialize("canXL", XL_HWTYPE_CANBOARDXL, 0, channel, bitRate); // TODO - Fix this hardcoded hardware value
  initialize("canXL", -1, 0, channel, bitRate);
}


/**
* Constructor which enables to initialize the different attributes of the class with default values.
* @see ~XLVectorCanDriver (void)
* @see XLVectorCanDriver (unsigned int gHwTypeT, Vaccess gChannelMaskT, unsigned int gCanIdT, unsigned int gBitRateT,int gHwChannelT)
*/

XLVectorCanDriver::XLVectorCanDriver (void)
{
  LOG_INFO("Notice : VECTOR XL CAN Driver used\n");
  /*
  gPortHandle		= INVALID_PORTHANDLE;
  gChannelMask	= 0x3;
  gPermissionMask	= 0;
  gCanId			= 0x2A9;
  gBitRate		= 500000;
  gHwType			= HWTYPE_CANAC2PCI;
  gHwChannel		= 0;
  gEventHandle	= 0;*/

  initialize("canXL", -1, 0, 0, 500000);
}


void XLVectorCanDriver::displayHardware() {
	XLdriverConfig driverConfig;
	traceXLCommand("xlGetDriverConfig", xlGetDriverConfig(&driverConfig));

	LOG_INFO("----------------------------------------------------------");
	LOG_INFO("- " << setfill('0') << setw(2) << driverConfig.channelCount << " channels       Hardware Configuration               -");
	LOG_INFO("----------------------------------------------------------");

	char str[XL_MAX_LENGTH + 1] = "";

  for (unsigned int i = 0; i < driverConfig.channelCount; ++i) {
		XLchannelConfig channel = driverConfig.channel[i];
    LOG_INFO("- Ch:" << setfill('0') << setw(2) << channel.channelIndex << ", "
        << "CM:0x" << hex << setfill('0') << setw(3) << channel.channelMask << ", ");

    strncpy_s(str, channel.name, 23);
    printf(" %23s,", str);
    memset(str, 0, sizeof(str));

		if (channel.transceiverType != XL_TRANSCEIVER_TYPE_NONE) {
      strncpy_s(str, channel.transceiverName, 13);
      printf("%13s -\n", str);
		} else {
			printf("    no Cab!   -\n", str);
		}
  }

  LOG_INFO("----------------------------------------------------------");
}

/**
* Constructor which enables to initialize the different attributes of the class with values given in parameters.
* @see ~XLVectorCanDriver (void)
* @see XLVectorCanDriver (void)
*/
XLVectorCanDriver::XLVectorCanDriver(const std::string &name, const int hwType, const int hwIndex, const int hwChannel, unsigned long bitrate)
{
	initialize(name, hwType, hwIndex, hwChannel, bitrate);
}

void XLVectorCanDriver::initialize(const std::string &name, const int hwType, const int hwIndex, const int hwChannel, unsigned long bitrate)
{
  printf("Notice : VECTOR XL CAN Driver used\n");
  displayHardware();
  /*gPortHandle		= INVALID_PORTHANDLE;
  gChannelMask	= gChannelMaskT;
  gPermissionMask	= 0;
  gCanId			= gCanIdT;
  gBitRate		= gBitRateT;
  gHwType			= gHwTypeT;
  gHwChannel		= gHwChannelT;
  gEventHandle	= 0;*/

  this->accessMask = xlGetChannelMask(hwType, hwIndex, hwChannel);
	if(!this->accessMask) {
		traceXLCommand("xlGetChannelMask", XL_ERR_HW_NOT_PRESENT);
	} else {
		traceXLCommand("xlGetChannelMask", XL_SUCCESS);
	}
	XLaccess permissionMask = this->accessMask;

	traceXLCommand("xlOpenPort",
		xlOpenPort(&this->port, const_cast<char*>(name.c_str()), this->accessMask,
		&permissionMask, RX_QUEUE_SIZE, XL_INTERFACE_VERSION, XL_BUS_TYPE_CAN));
	if ( this->port == XL_INVALID_PORTHANDLE ) {
		checkXlStatus(XL_ERR_HW_NOT_PRESENT);
	}

	if (this->accessMask == permissionMask) {
		traceXLCommand("xlCanSetChannelBitrate",
			xlCanSetChannelBitrate(this->port, this->accessMask, bitrate));
	} else {
		LOG_DEBUG("No init access");
	}
	traceXLCommand("xlSetNotification",
		xlSetNotification(this->port, &this->msgEvent, QUEUE_LEVEL));
	traceXLCommand("xlCanSetReceiveMode",
		xlCanSetReceiveMode(this->port, 1, 1));
	traceXLCommand("xlActivateChannel",
		xlActivateChannel(this->port, this->accessMask, XL_BUS_TYPE_CAN,
		XL_ACTIVATE_RESET_CLOCK));
}


/**
* Constructor which enables to select the channel and to initialize the different attributes of the class with default values..
* @see ~XLVectorCanDriver (void)
* @see XLVectorCanDriver (void)
*/

XLVectorCanDriver::XLVectorCanDriver(int channel)
{
  printf("Notice : VECTOR XL CAN Driver used\n");

  /*
  gPortHandle		= INVALID_PORTHANDLE;
  gChannelMask	= 0x3;
  gPermissionMask	= 0;
  gCanId			= 0x2A9;
  gBitRate		= 1000000;
  gHwType			= HWTYPE_CANAC2PCI;
  gHwChannel		= channel;
  gEventHandle	= 0;
  */

    initialize("can", 0, 0, channel, 500);
}



/**
* Destructor which clean up the different attributs of the class.
* @see XLVectorCanDriver (void)
* @see XLVectorCanDriver (unsigned int gHwTypeT, Vaccess gChannelMaskT, unsigned int gCanIdT, unsigned int gBitRateT,int gHwChannelT)
*/
XLVectorCanDriver::~XLVectorCanDriver (void)
{
	traceXLCommand("xlDeactivateChannel",
		xlDeactivateChannel(this->port, this->accessMask));
	traceXLCommand("xlClosePort",
		xlClosePort(this->port));
	this->port = XL_INVALID_PORTHANDLE;
}


/**
* Member used to initialise the configuration of the CAN Card.
* @see cleanUpPort (void)
* @return a Vstatus variable which contain the error code of the function. On success, it return VSUCCESS. On failure, it return Vstatus error code which is defined in VCanD.h
*/
short XLVectorCanDriver::initPort (void)
{
	/*
  Vstatus vErr;
  VsetAcceptance acc;

  // Open the driver
  vErr = ncdOpenDriver ();
  if (vErr)
  {
    printf ("ERROR:initport %s!\n", ncdGetErrorString (vErr));
    return vErr;
  }

  // Select the channel 
  gChannelMask = ncdGetChannelMask (gHwType,0,gHwChannel);
  if (!gChannelMask) 
  {
    printf ("ERROR: (initport) Channel not present!\n");
    printf ("ERROR:(initport) %s!\n", ncdGetErrorString (VERROR));
    return vErr;
  }

  // Select the index 
  int gChannelIndex = ncdGetChannelIndex (gHwType,0,gHwChannel);
  if ( gChannelIndex == -1 ) 
  {
    printf ("ERROR: (initport) Channel not present!\n");
    printf ("ERROR:(initport) %s!\n", ncdGetErrorString (VERROR));
    return vErr;
  }

  // Open a port 
  vErr = ncdOpenPort (&gPortHandle,"PACPUS_CANDriver",gChannelMask,gChannelMask,&gPermissionMask,1024);
  if (vErr != VSUCCESS)
  {
    printf ("ERROR:(init port) %s!\n", ncdGetErrorString (vErr));
    return vErr;
  }

  // Only if permission to initialize the channel 
  if (gPermissionMask) 
  {
    // Set the bus timing 
    vErr = ncdSetChannelBitrate (gPortHandle,gPermissionMask,gBitRate);
    if (vErr)
    {
      printf ("ERROR: %s!\n", ncdGetErrorString (vErr));	
      if (gPortHandle!=INVALID_PORTHANDLE)
      {
        ncdClosePort (gPortHandle);
        gPortHandle = INVALID_PORTHANDLE;
      }
      return vErr;
    }
  }
  else if (gBitRate)
  {
    printf ("WARNING: No init access! Bitrate ignored.\n");
  }

  // Enable the TX and disable the TXRQ notifications 
  vErr = ncdSetChannelMode (gPortHandle,gChannelMask,1,0);
  if (vErr)
  {
    printf ("ERROR:(init port) %s!\n", ncdGetErrorString (vErr));
    if (gPortHandle!=INVALID_PORTHANDLE)
    {
      ncdClosePort (gPortHandle);
      gPortHandle = INVALID_PORTHANDLE;
    }
    return vErr;
  }

  // create a synchronisation object 
  gEventHandle = CreateEvent (NULL, FALSE, FALSE, NULL);
  vErr = ncdSetNotification (gPortHandle, (unsigned long*)&gEventHandle, 1);
  if (vErr)
  {
    printf ("ERROR(init port): %s!\n", ncdGetErrorString (vErr));
    ncdDeactivateChannel (gPortHandle, gChannelMask);
    cleanUpPort ();
    return vErr;
  }

  // Open the acceptance filter 
  acc.mask = 0x000; // relevant=1
  acc.code = 0x000;

  vErr = ncdSetChannelAcceptance (gPortHandle,gChannelMask,&acc);
  if (vErr)
  {
    printf ("ERROR: %s!\n", ncdGetErrorString (vErr));
    if (gPortHandle!=INVALID_PORTHANDLE)
    {
      ncdClosePort (gPortHandle);
      gPortHandle = INVALID_PORTHANDLE;
    }
    return vErr;
  }

  // Go on bus 
  vErr = ncdActivateChannel (gPortHandle,gChannelMask);
  if (vErr)
  {
    printf ("ERROR: %s!\n", ncdGetErrorString (vErr));
    ncdDeactivateChannel (gPortHandle, gChannelMask);
    cleanUpPort ();
    return vErr;
  }

  // Reset the clocks of all channels connected to the port 
  vErr = ncdResetClock(gPortHandle); 
  if (vErr)
  {
    printf ("ERROR: %s!\n", ncdGetErrorString (vErr));
    ncdDeactivateChannel (gPortHandle, gChannelMask);
    cleanUpPort ();
    return vErr;
  }

  return VSUCCESS;
  */
	traceXLCommand("xlOpenDriver", xlOpenDriver());
	return 0;
}


/**
* Member used to clean up the configuration of the CAN Card.
* @see initPort (void)
* @return a Vstatus variable which contain the error code of the function. On success, it return VSUCCESS. On failure, it return Vstatus error code which is defined in VCanD.h
*/
short XLVectorCanDriver::cleanUpPort (void)
{
	/*
  Vstatus vErr;
  vErr = ncdDeactivateChannel(gPortHandle, gChannelMask);
  if (vErr)
  {
    printf ("ERROR: (cleanUpPort) Channel not correctly deactivated!\n Driver not correctly closed!\n");
    printf ("ERROR: %s!\n", ncdGetErrorString (vErr));
    return vErr;
  }
  vErr = ncdClosePort (gPortHandle);
  if (vErr)
  {
    printf ("ERROR: (cleanUpPort) Port not correctly closed!\n Driver not correctly closed!\n");
    printf ("ERROR: %s!\n", ncdGetErrorString (vErr));
    return vErr;
  }
  gPortHandle = INVALID_PORTHANDLE;
  vErr = ncdCloseDriver ();
  if (vErr)
  {
    printf ("ERROR: (cleanUpPort) Driver not correctly closed!\n");
    printf ("ERROR: %s!\n", ncdGetErrorString (vErr));
    return vErr;
  }

  return VSUCCESS;
  */
	traceXLCommand("xlCloseDriver", xlCloseDriver());

	return 0;
}


/**
* Member which permit to send a frame on the CAN bus and test if the frame is well acknowledged.
* @param flags a character which contain the flags of the sent frame.
* @param dlc a character which defined the number of characters of the sent frame.
* @param data a table of characters with the data of the sent frame.
* @see receiveFrame (unsigned char * flags, unsigned char * dlc, unsigned char ** data)
* @return a Vstatus variable which contain the error code of the function. On success, it return VSUCCESS. On failure, it return Vstatus error code which is defined in VCanD.h
*/
//Vstatus XLVectorCanDriver::sendFrame (unsigned char flags, unsigned char dlc, unsigned char * data, int identifiant)
short XLVectorCanDriver::sendFrame (struct CanFrame frame)
{

		XLevent e;
	e.tag = XL_TRANSMIT_MSG;
	e.tagData.msg.id = frame.id;
	e.tagData.msg.flags = 0;
	e.tagData.msg.dlc = frame.dlc;
	memcpy(e.tagData.msg.data, frame.data, frame.dlc);

	unsigned int count = 1;
	LOG_DEBUG(xlGetEventString(&e));
	traceXLCommand("xlCanTransmit",
		xlCanTransmit(this->port, this->accessMask, &count, &e));

	/*
  Vstatus vErr;
  Vevent event;
  Vevent * pEvent = NULL;

  // Create frame to send 
  event.tag                 = V_TRANSMIT_MSG;
  event.tagData.msg.id      = frame.id;
  event.tagData.msg.flags   = 0;
  event.tagData.msg.dlc     = frame.dlc;

  for (int i = 0; i < frame.dlc; i++)
    event.tagData.msg.data[i] = frame.data[i];

  // Send the frame 
  vErr = ncdTransmit (gPortHandle, gChannelMask, &event);

  //printf("sendFrame ncdTransmit  --  vErr=%d, event=0x%x\n", vErr, event); 

  if (vErr==VERR_QUEUE_IS_FULL)
  {
    printf("!");
  }

  else if (vErr)
  {
    printf ("ERROR:(send frame) %s!\n", ncdGetErrorString (vErr));		
    //		ncdDeactivateChannel (gPortHandle, gChannelMask);
    //		cleanUpPort ();
    return vErr;
  }

  return VSUCCESS;

  // Wait the acknowledgement frame 
  waitReceivingFrame(); 

  // Read the acknowledgement frame in the buffer 
  vErr = ncdReceive1 (gPortHandle,&pEvent);
  //printf("sendFrame ncdReceive1  --  vErr=%d, pEvent=0x%x\n", vErr, pEvent); 

  if ( (pEvent==NULL) && (vErr==VERR_QUEUE_IS_EMPTY) )
  {
    printf ("%s\n",ncdGetErrorString (vErr));
    printf ("%s!\n",ncdGetErrorString (vErr));
    //		ncdDeactivateChannel (gPortHandle, gChannelMask);
    //		cleanUpPort ();
    return vErr;
  }

  // If frame is well acknoledged 
  if (pEvent->tagData.msg.flags & 0x40)  
    return VSUCCESS;
  else
  {
   //printf("%x ",pEvent->tagData.msg.flags);
   //printf (" no acknolegement of frame!\n");
   
    return VERROR;
  }*/

	return 1;
}


/**
* Member which permit to receive of a frame on the CAN bus.
* @param flags a character pointer which contain the flags of the received frame.
* @param dlc a character pointer which defined the number of characters of the received frame.
* @param data a pointer of table of characters with the data of the received frame.
* @see sendFrame (unsigned char flags, unsigned char dlc, unsigned char * data)
* @return a Vstatus variable which contain the error code of the function. On success, it return VSUCCESS. On failure, it return Vstatus error code which is defined in VCanD.h
*/
//Vstatus XLVectorCanDriver::receiveFrame (unsigned char * flags, unsigned char * dlc, unsigned char * data, int * identifiant)
short XLVectorCanDriver::receiveFrame (struct CanFrame &frame)
{

	
	XLhandle handle;
	traceXLCommand("xlSetNotification",
	xlSetNotification(this->port, &handle, 1));
	XLevent e;
	unsigned int count = 1;

	int queueSize;
	//bool found = false;
	//DWORD begin = timeGetTime();
	//while ( !found ) {
		/*DWORD now = timeGetTime();
		/DEBUG("begin: %ld, now: %ld", begin, now);
		if ( now - begin >= timeout ) {
			return NULL;
		}
*/
		traceXLCommand("xlGetReceiveQueueLevel",
			xlGetReceiveQueueLevel(this->port, &queueSize));
		if ( queueSize < 1 ) {
			 if (WaitForSingleObject(handle, WAIT_RECEIVING_FRAME_TIMEOUT) == WAIT_TIMEOUT)
				{
				LOG_TRACE("waitReceivingFrame : no frame receiving in the last " << WAIT_RECEIVING_FRAME_TIMEOUT/1000 << " seconds."); 
				return 1;
				}
		}

		if (xlReceive(this->port, &count, &e) == XL_SUCCESS) {
			LOG_TRACE(xlGetEventString(&e));
			//found = (e.tagData.msg.id & id) == id;
			frame.id = e.tagData.msg.id;
			frame.dlc = static_cast<uint8_t>(e.tagData.msg.dlc);
			memcpy(frame.data,e.tagData.msg.data, frame.dlc);
			return 0;
		} else {
			return 1;
		}
	//}

	//return new CanMessage(e);


	/*
  int L ;
  Vstatus vErr;
  Vevent * pEvent = NULL;

  do {
    // Read frame in the buffer 
    ncdGetReceiveQueueLevel( gPortHandle , &L );
    if( L <= 0 )
    {
      if (WaitForSingleObject (gEventHandle,WAIT_RECEIVING_FRAME_TIMEOUT) == WAIT_TIMEOUT)
      {
        //printf("no frame receiving in the %d last seconds\n", WAIT_RECEIVING_FRAME_TIMEOUT/1000); 
        return VERR_QUEUE_IS_EMPTY;
      }
    }

    vErr = ncdReceive1 (gPortHandle,&pEvent);
    if( vErr == VERROR )
    {
      printf ("receiveframe ERROR  - ERROR: %s\n", ncdGetErrorString (vErr));		
      //		ncdDeactivateChannel (gPortHandle, gChannelMask);
      //		cleanUpPort ();

      return vErr;
    }

  } while((( pEvent==NULL ) && ( vErr==VERR_QUEUE_IS_EMPTY )) || ( vErr == VERROR ));

  // Return the flags field, dlc field and data field of the sent frame 
  //frame.flags = pEvent->tagData.msg.flags;
  frame.dlc = pEvent->tagData.msg.dlc;
  frame.id =  pEvent->tagData.msg.id;
  if( ( frame.dlc > 8 ) || ( frame.dlc < 0 ))     
    frame.dlc = 8; 

  memcpy(frame.data,pEvent->tagData.msg.data, frame.dlc);

  return VSUCCESS;*/
	
}


/**
* Member which wait the reception of a frame on the CAN bus.
* @see sendFrame (unsigned char flags, unsigned char dlc, unsigned char * data)
* @see receiveFrame (unsigned char * flags, unsigned char * dlc, unsigned char ** data)
*/
void XLVectorCanDriver::waitReceivingFrame(void)
{

  if (WaitForSingleObject (msgEvent,WAIT_RECEIVING_FRAME_TIMEOUT) == WAIT_TIMEOUT)
  {
    LOG_TRACE("waitReceivingFrame - Error : no frame receiving in the " << WAIT_RECEIVING_FRAME_TIMEOUT/1000 << " %d last seconds"); 
  }
	/*
  if (WaitForSingleObject (gEventHandle,WAIT_RECEIVING_FRAME_TIMEOUT) == WAIT_TIMEOUT)
  {
    printf("waitReceivingFrame - Error : no frame receiving in the %d last seconds\n", WAIT_RECEIVING_FRAME_TIMEOUT/1000); 
  }
  */
}

/*
Vstatus XLVectorCanDriver::AcceptId(int id)
{
  if(ncdAddAcceptanceRange(gPortHandle,gChannelMask,id,id)!=VSUCCESS)
  {
    printf("erreur lors de la configuration du filtre");
    return VERROR;
  }
  else
    return VSUCCESS;
}
*/


/*
Vstatus XLVectorCanDriver::AcceptIdRange(int deb,int fin)
{
  if(ncdAddAcceptanceRange(gPortHandle,gChannelMask,deb,fin)!=VSUCCESS)
  {
    printf("erreur lors de la configuration du filtre");
    return VERROR;
  }
  else
    return VSUCCESS;
}
*/
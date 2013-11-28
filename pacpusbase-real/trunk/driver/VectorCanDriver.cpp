/********************************************************************
//  created:    2006/08/07 - 14:14
//  filename:   VectorCanDriver.cpp
//
//  author:     Gerald Dherbomez
//
//  version:    $Id: VectorCanDriver.cpp 1203 2012-08-02 11:58:15Z morasjul $
//
//  purpose:    Implementation of the VectorCanDriver class
//              This file is based on the work 2 UTC students (Maricot 
//              Benoit & Pham Eric) in the framework of their SY27 
//              project. 
//
*********************************************************************/


#include "VectorCanDriver.h"
#include <stdio.h>
#include <string>


#define WAIT_RECEIVING_FRAME_TIMEOUT 1000



/**
* Constructor which enables to initialize the different attributes of the class with default values.
* @see ~VectorCanDriver (void)
* @see VectorCanDriver (unsigned int gHwTypeT, Vaccess gChannelMaskT, unsigned int gCanIdT, unsigned int gBitRateT,int gHwChannelT)
*/
VectorCanDriver::VectorCanDriver (int channel, unsigned int bitRate)
{
  printf("Notice : VECTOR CAN Driver used\n");
  gPortHandle		= INVALID_PORTHANDLE;
  gChannelMask	= 0x3;
  gPermissionMask	= 0;
  gCanId			= 0x2A9;
  gBitRate		= bitRate;
  gHwType			= HWTYPE_CANAC2PCI;
  gHwChannel		= channel;
  gEventHandle	= 0;
}


/**
* Constructor which enables to initialize the different attributes of the class with default values.
* @see ~VectorCanDriver (void)
* @see VectorCanDriver (unsigned int gHwTypeT, Vaccess gChannelMaskT, unsigned int gCanIdT, unsigned int gBitRateT,int gHwChannelT)
*/
VectorCanDriver::VectorCanDriver (void)
{
  printf("Notice : VECTOR CAN Driver used\n");
  gPortHandle		= INVALID_PORTHANDLE;
  gChannelMask	= 0x3;
  gPermissionMask	= 0;
  gCanId			= 0x2A9;
  gBitRate		= 500000;
  gHwType			= HWTYPE_CANAC2PCI;
  gHwChannel		= 0;
  gEventHandle	= 0;
}


/**
* Constructor which enables to initialize the different attributes of the class with values given in parameters.
* @see ~VectorCanDriver (void)
* @see VectorCanDriver (void)
*/
VectorCanDriver::VectorCanDriver (unsigned int gHwTypeT, Vaccess gChannelMaskT, unsigned int gCanIdT, unsigned int gBitRateT,int gHwChannelT)
{
  printf("Notice : VECTOR CAN Driver used\n");
  gPortHandle		= INVALID_PORTHANDLE;
  gChannelMask	= gChannelMaskT;
  gPermissionMask	= 0;
  gCanId			= gCanIdT;
  gBitRate		= gBitRateT;
  gHwType			= gHwTypeT;
  gHwChannel		= gHwChannelT;
  gEventHandle	= 0;
}


/**
* Constructor which enables to select the channel and to initialize the different attributes of the class with default values..
* @see ~VectorCanDriver (void)
* @see VectorCanDriver (void)
*/
VectorCanDriver::VectorCanDriver(int channel)
{
  printf("Notice : VECTOR CAN Driver used\n");
  gPortHandle		= INVALID_PORTHANDLE;
  gChannelMask	= 0x3;
  gPermissionMask	= 0;
  gCanId			= 0x2A9;
  gBitRate		= 1000000;
  gHwType			= HWTYPE_CANAC2PCI;
  gHwChannel		= channel;
  gEventHandle	= 0;
}



/**
* Destructor which clean up the different attributs of the class.
* @see VectorCanDriver (void)
* @see VectorCanDriver (unsigned int gHwTypeT, Vaccess gChannelMaskT, unsigned int gCanIdT, unsigned int gBitRateT,int gHwChannelT)
*/
VectorCanDriver::~VectorCanDriver (void)
{
  gEventHandle	= NULL;
  gPortHandle		= INVALID_PORTHANDLE;
}


/**
* Member used to initialise the configuration of the CAN Card.
* @see cleanUpPort (void)
* @return a Vstatus variable which contain the error code of the function. On success, it return VSUCCESS. On failure, it return Vstatus error code which is defined in VCanD.h
*/
Vstatus VectorCanDriver::initPort (void)
{
  Vstatus vErr;
  VsetAcceptance acc;

  /* Open the driver */
  vErr = ncdOpenDriver ();
  if (vErr)
  {
    printf ("ERROR:initport %s!\n", ncdGetErrorString (vErr));
    return vErr;
  }

  /* Select the channel */
  gChannelMask = ncdGetChannelMask (gHwType,0,gHwChannel);
  if (!gChannelMask) 
  {
    printf ("ERROR: (initport) Channel not present!\n");
    printf ("ERROR:(initport) %s!\n", ncdGetErrorString (VERROR));
    return vErr;
  }

  /* Select the index */
  int gChannelIndex = ncdGetChannelIndex (gHwType,0,gHwChannel);
  if ( gChannelIndex == -1 ) 
  {
    printf ("ERROR: (initport) Channel not present!\n");
    printf ("ERROR:(initport) %s!\n", ncdGetErrorString (VERROR));
    return vErr;
  }

  /* Open a port */
  vErr = ncdOpenPort (&gPortHandle,"PACPUS_CANDriver",gChannelMask,gChannelMask,&gPermissionMask,1024);
  if (vErr != VSUCCESS)
  {
    printf ("ERROR:(init port) %s!\n", ncdGetErrorString (vErr));
    return vErr;
  }

  /* Only if permission to initialize the channel */
  if (gPermissionMask) 
  {
    /* Set the bus timing */
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

  /* Enable the TX and disable the TXRQ notifications */
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

  /* create a synchronisation object */
  gEventHandle = CreateEvent (NULL, FALSE, FALSE, NULL);
  vErr = ncdSetNotification (gPortHandle, (unsigned long*)&gEventHandle, 1);
  if (vErr)
  {
    printf ("ERROR(init port): %s!\n", ncdGetErrorString (vErr));
    ncdDeactivateChannel (gPortHandle, gChannelMask);
    cleanUpPort ();
    return vErr;
  }

  /* Open the acceptance filter */
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

  /* Go on bus */
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
}


/**
* Member used to clean up the configuration of the CAN Card.
* @see initPort (void)
* @return a Vstatus variable which contain the error code of the function. On success, it return VSUCCESS. On failure, it return Vstatus error code which is defined in VCanD.h
*/
Vstatus VectorCanDriver::cleanUpPort (void)
{
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
}


/**
* Member which permit to send a frame on the CAN bus and test if the frame is well acknowledged.
* @param flags a character which contain the flags of the sent frame.
* @param dlc a character which defined the number of characters of the sent frame.
* @param data a table of characters with the data of the sent frame.
* @see receiveFrame (unsigned char * flags, unsigned char * dlc, unsigned char ** data)
* @return a Vstatus variable which contain the error code of the function. On success, it return VSUCCESS. On failure, it return Vstatus error code which is defined in VCanD.h
*/
//Vstatus VectorCanDriver::sendFrame (unsigned char flags, unsigned char dlc, unsigned char * data, int identifiant)
Vstatus VectorCanDriver::sendFrame (struct CanFrame frame)
{
  Vstatus vErr;
  Vevent event;
  //Vevent * pEvent = NULL;

  /* Create frame to send */
  event.tag                 = V_TRANSMIT_MSG;
  event.tagData.msg.id      = frame.id;
  event.tagData.msg.flags   = 0;
  event.tagData.msg.dlc     = frame.dlc;

  for (int i = 0; i < frame.dlc; i++)
    event.tagData.msg.data[i] = frame.data[i];

  /* Send the frame */
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

  ///* Wait the acknowledgement frame */
  //waitReceivingFrame(); 

  ///* Read the acknowledgement frame in the buffer */
  //vErr = ncdReceive1 (gPortHandle,&pEvent);
  ////printf("sendFrame ncdReceive1  --  vErr=%d, pEvent=0x%x\n", vErr, pEvent); 

  //if ( (pEvent==NULL) && (vErr==VERR_QUEUE_IS_EMPTY) )
  //{
  //  printf ("%s\n",ncdGetErrorString (vErr));
  //  printf ("%s!\n",ncdGetErrorString (vErr));
  //  //		ncdDeactivateChannel (gPortHandle, gChannelMask);
  //  //		cleanUpPort ();
  //  return vErr;
  //}

  ///* If frame is well acknoledged */
  //if (pEvent->tagData.msg.flags & 0x40)  
  //  return VSUCCESS;
  //else
  //{/*
  // printf("%x ",pEvent->tagData.msg.flags);
  // printf (" no acknolegement of frame!\n");
  // */
  //  return VERROR;
  //}
}


/**
* Member which permit to receive of a frame on the CAN bus.
* @param flags a character pointer which contain the flags of the received frame.
* @param dlc a character pointer which defined the number of characters of the received frame.
* @param data a pointer of table of characters with the data of the received frame.
* @see sendFrame (unsigned char flags, unsigned char dlc, unsigned char * data)
* @return a Vstatus variable which contain the error code of the function. On success, it return VSUCCESS. On failure, it return Vstatus error code which is defined in VCanD.h
*/
//Vstatus VectorCanDriver::receiveFrame (unsigned char * flags, unsigned char * dlc, unsigned char * data, int * identifiant)
Vstatus VectorCanDriver::receiveFrame (struct CanFrame &frame)
{
  int L ;
  Vstatus vErr;
  Vevent * pEvent = NULL;

  do {
    /* Read frame in the buffer */
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

  /* Return the flags field, dlc field and data field of the sent frame */
  //frame.flags = pEvent->tagData.msg.flags;
  frame.dlc = pEvent->tagData.msg.dlc;
  frame.id =  pEvent->tagData.msg.id;
  if( ( frame.dlc > 8 ) || ( frame.dlc < 0 ))     
    frame.dlc = 8; 

  memcpy(frame.data,pEvent->tagData.msg.data, frame.dlc);

  return VSUCCESS;
}


/**
* Member which wait the reception of a frame on the CAN bus.
* @see sendFrame (unsigned char flags, unsigned char dlc, unsigned char * data)
* @see receiveFrame (unsigned char * flags, unsigned char * dlc, unsigned char ** data)
*/
void VectorCanDriver::waitReceivingFrame(void)
{
  if (WaitForSingleObject (gEventHandle,WAIT_RECEIVING_FRAME_TIMEOUT) == WAIT_TIMEOUT)
  {
    printf("waitReceivingFrame - Error : no frame receiving in the %d last seconds\n", WAIT_RECEIVING_FRAME_TIMEOUT/1000); 
  }
}


Vstatus VectorCanDriver::AcceptId(int id)
{
  if(ncdAddAcceptanceRange(gPortHandle,gChannelMask,id,id)!=VSUCCESS)
  {
    printf("erreur lors de la configuration du filtre");
    return VERROR;
  }
  else
    return VSUCCESS;
}


Vstatus VectorCanDriver::AcceptIdRange(int deb,int fin)
{
  if(ncdAddAcceptanceRange(gPortHandle,gChannelMask,deb,fin)!=VSUCCESS)
  {
    printf("erreur lors de la configuration du filtre");
    return VERROR;
  }
  else
    return VSUCCESS;
}

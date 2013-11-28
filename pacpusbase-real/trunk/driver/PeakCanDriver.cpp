/********************************************************************
//  created:    2011/02/21 - 10:46
//  filename:   PeakCanDriver.cpp
//
//  author:     Sergio Rodriguez
//
//  version:    $Id: PeakCanDriver.cpp srodrigu $
//
//  purpose:    Implementation of the PeakCanDriver class
//
*********************************************************************/


#include "PeakCanDriver.h"
#include <stdio.h>
#include <cstring>
#include <cstdlib>
#include <iostream>

#define DEFAULT_NODE "/dev/pcanusb0"
#define WAIT_RECEIVING_FRAME_TIMEOUT 1000

/**
* Constructor which enables to initialize the different attributes of the class with default values.
*/
PeakCanDriver::PeakCanDriver (void)
{
  printf("Notice : PEAK CAN Driver used\n");
  //szDevNode_ = DEFAULT_NODE;
  mode_ = ReadOnly;
}

/**
* Constructor which enables to initialize the different attributes of the class with default values.
*/
PeakCanDriver::PeakCanDriver (int channel)
{
  printf("Notice : PEAK CAN Driver used\n");
  //szDevNode_ = DEFAULT_NODE;
  mode_ = ReadOnly;
}

/**
* Constructor which enables to initialize the different attributes of the class with default values.
*/
PeakCanDriver::PeakCanDriver (int channel, unsigned int bitRate)
{
  printf("Notice : PEAK CAN Driver used\n");
  //szDevNode_ = DEFAULT_NODE;
  mode_ = ReadOnly;
}

/**
* Constructor which enables to initialize the different attributes of the class with default values.
*/
PeakCanDriver::PeakCanDriver(const char* port, const char* mode)
{
  szDevNode_ =(char*) malloc(14*sizeof(char));
  strcpy(szDevNode_,DEFAULT_NODE);
  
  printf("Notice : PEAK CAN Driver used\n");
  //strcpy(szDevNode_, port);
  printf("Driver to be connected at port: %s",szDevNode_);
  
  if (!strcmp(mode,"ReadOnly")){
        mode_ = ReadOnly; 
      printf(" in ReadOnly mode\n");
  }
  else if (!strcmp(mode,"WriteOnly")){
      mode_ = WriteOnly;
      printf(" in WriteOnly mode\n");
  }
  else if (!strcmp(mode,"ReadWrite")){
      mode_ = ReadWrite;
      printf(" in ReadWrite dual mode\n");
  }
  else{
      mode_= ReadOnly;
      printf(" in ReadOnly mode since mode was not identified.\n");
  } 
}

/**
* Destructor which clean up the different attributs of the class.
*/
PeakCanDriver::~PeakCanDriver (void)
{

}

/**
* Member used to initialise the configuration of the CAN Card.
* @see cleanUpPort (void)
* @return a Pstatus variable which contain the error code of the function. On success, it return PSUCCESS. On failure, it return Pstatus error code.
*/
short PeakCanDriver::initPort (void)
{
     
  switch(mode_)
  {
  case ReadOnly:
      canDeviceHandle_ = LINUX_CAN_Open(szDevNode_, O_RDONLY);
      break;
  case WriteOnly:
      canDeviceHandle_ = LINUX_CAN_Open(szDevNode_, O_WRONLY);
      break;
  case ReadWrite:
      canDeviceHandle_ = LINUX_CAN_Open(szDevNode_, O_RDWR);
      break;
  default:
      printf("Error on CAN port operation mode selection.\n");
      break;
  }
  
  return (!canDeviceHandle_)?1:PSUCCESS;
}

/**
* Member used to clean up the configuration of the CAN Card.
* @see initPort (void)
* @return a Pstatus variable which contain the error code of the function. On success, it return PSUCCESS. On failure, it return Pstatus error code.
*/
short PeakCanDriver::cleanUpPort (void)
{
    if(canDeviceHandle_)
    {
      printf("Closing CAN Driver..");
      CAN_Close(canDeviceHandle_);
      return PSUCCESS;
    }
    printf("CAN Driver finished.\n");
    return 1;
}


/**
* Member which permit to send a frame on the CAN bus and test if the frame is well acknowledged.
* @param flags a character which contain the flags of the sent frame.
* @param dlc a character which defined the number of characters of the sent frame.
* @param data a table of characters with the data of the sent frame.
* @see receiveFrame (unsigned char * flags, unsigned char * dlc, unsigned char ** data)
* @return a Pstatus variable which contain the error code of the function. On success, it return PSUCCESS. On failure, it return Pstatus error code.
*/
short PeakCanDriver::sendFrame (struct CanFrame frame)
{
    return PSUCCESS;
}


/**
* Member which permit to receive of a frame on the CAN bus.
* @param flags a character pointer which contain the flags of the received frame.
* @param dlc a character pointer which defined the number of characters of the received frame.
* @param data a pointer of table of characters with the data of the received frame.
* @see sendFrame (unsigned char flags, unsigned char dlc, unsigned char * data)
* @return a Pstatus variable which contain the error code of the function. On success, it return PSUCCESS. On failure, it return Pstatus error code.
*/
short PeakCanDriver::receiveFrame (struct CanFrame &frame)
{
    TPCANRdMsg message;
    __u32 status;

    //if ((errno = CAN_Read(canDeviceHandle_, &message)))
    if ((errno = LINUX_CAN_Read_Timeout(canDeviceHandle_, &message, READ_TIMEOUT)))
    {
      perror("application: CAN_Read()");
      return errno;
    }
    else
    {
      //print_message(&message.Msg);
      // check if a CAN status is pending
      if (message.Msg.MSGTYPE & MSGTYPE_STATUS)
      {
        status = CAN_Status(canDeviceHandle_);
        if ((int)status < 0)
        {
          errno = nGetLastError();
          perror("application: CAN_Status()");
          return errno;
        }
        else
          printf("application: pending CAN status 0x%04x read.\n", (__u16)status);
      }
    }

  /* Return the flags field, dlc field and data field of the sent frame */
  //frame.flags = pEvent->tagData.msg.flags;
  frame.dlc = message.Msg.LEN; //ok
  frame.id =  message.Msg.ID;

  if( ( frame.dlc > 8 ) || ( frame.dlc < 0 ))
      frame.dlc = 8;
  memcpy(frame.data,message.Msg.DATA, frame.dlc);

  return PSUCCESS;
}


/**
* Member which wait the reception of a frame on the CAN bus.
* @see sendFrame (unsigned char flags, unsigned char dlc, unsigned char * data)
* @see receiveFrame (unsigned char * flags, unsigned char * dlc, unsigned char ** data)
*/
void PeakCanDriver::waitReceivingFrame(void)
{

}
// print out the contents of a CAN message
void PeakCanDriver::print_message(TPCANMsg *m)
{
  int i;

  // print RTR, 11 or 29, CAN-Id and datalength
  printf("message: %c %c 0x%08x %1d  ",
      (m->MSGTYPE & MSGTYPE_RTR)      ? 'r' : 'm',
      (m->MSGTYPE & MSGTYPE_EXTENDED) ? 'e' : 's',
       m->ID,
       m->LEN);

  // don't print any telegram contents for remote frames
  if (!(m->MSGTYPE & MSGTYPE_RTR))
    for (i = 0; i < m->LEN; i++)
      printf("0x%02x ", m->DATA[i]);

  printf("\n");
}

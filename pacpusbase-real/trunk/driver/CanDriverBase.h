/********************************************************************
//  created:    2006/08/07 - 14:12
//  filename:   CanDriverBase.h
//
//  author:     Gerald Dherbomez
//
//  version:    $Id: CanDriverBase.h 1069 2012-03-07 15:57:30Z kurdejma $
//
//  purpose:    This is an abstract class that manages the CAN card. 
//              Use UPF frames to communicate with it. 
//              Contains basic decoding functions for CAN data.
//              
*********************************************************************/


#ifndef _CANDRIVERBASE_H_
#define _CANDRIVERBASE_H_

#include "kernel/road_time.h"
#include "PacpusTools/BinaryDecoder.h"
#include "structure/structureCanCarmen.h"

/*

#define MAX_CAN_MSG_LENGTH 8


// Basic structure of a CAN frame
struct CanFrame {
  unsigned long id;
  unsigned char dlc;
  unsigned char data [MAX_CAN_MSG_LENGTH];
};

// Can structure with timestamping
struct TimestampedCanFrame {
  CanFrame frame;
  road_time_t time;
  road_timerange_t timerange;
};

*/

class CanDriverBase
{
public:
  CanDriverBase(){}
  ~CanDriverBase(){}
  
  virtual short initPort (void) = 0;
  virtual short cleanUpPort (void) = 0;
  virtual short sendFrame (struct CanFrame frame) = 0 ;
  virtual short receiveFrame (struct CanFrame &frame) = 0;
  virtual void waitReceivingFrame (void) = 0;

protected:

private:
};




#endif

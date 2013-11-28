/// Purpose: Inherits from the CanDriver class
///          Reimplement all the virtual members of the CanDriverBase 
///          class in order to be used with the Vector driver.  
///          platform : Windows specific
///
/// @date created 2013/05/06 - 17:01
/// @author Pierre Hudelaine
/// @version $Id$

#ifndef ESDCANDRIVER_H
#define ESDCANDRIVER_H

#include <string>
#include <windows.h>

#include "CanDriverBase.h"
#include "ntcan.h"

class EsdCanDriver
    : public CanDriverBase
{
public:
  EsdCanDriver(void);
  EsdCanDriver(int channel);
  EsdCanDriver(int channel, unsigned int bitRate);
  EsdCanDriver(char * /*dummy1*/, char * /*dummy2*/) {} // DON'T USE
  ~EsdCanDriver(void);  
  
  short initPort (void);
  short cleanUpPort (void);
  short sendFrame (struct CanFrame frame);
  short receiveFrame (struct CanFrame &frame);
  void  waitReceivingFrame(void);

protected:
	
private:

	int speedConverter(int baudrate);

	NTCAN_HANDLE esd_handle_;
};

#endif // ESDCANDRIVER_H

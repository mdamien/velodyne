/// Purpose: Inherits from the CanDriver class
///          Reimplement all the virtual members of the CanDriverBase 
///          class in order to be used with the Vector driver.  
///          platform : Windows specific
///
/// @date created 2006/08/07 - 14:14
/// @author Gerald Dherbomez
/// @version $Id$

#ifndef XLVECTORCANDRIVER_H
#define XLVECTORCANDRIVER_H

#include <string>
#include <windows.h>

#include "CanDriverBase.h"
#include "vxlapi.h"

class XLVectorCanDriver
    : public CanDriverBase
{
public:
  XLVectorCanDriver(void);
  XLVectorCanDriver(const std::string &name, const int hwType, const int hwIndex, const int hwChannel, unsigned long bitrate);
  void initialize(const std::string &name, const int hwType, const int hwIndex, const int hwChannel, unsigned long bitrate);
  XLVectorCanDriver(int channel);
  XLVectorCanDriver(int channel, unsigned int bitRate);
  XLVectorCanDriver(char * /*dummy1*/, char * /*dummy2*/) {} // DON'T USE
  ~XLVectorCanDriver(void);

  short initPort (void);
  short cleanUpPort (void);

  void displayHardware(void);

  //Vstatus AcceptId(int id);
  //Vstatus AcceptIdRange(int deb,int fin);
  //Vstatus sendFrame (unsigned char, unsigned char, unsigned char *, int);
  //Vstatus receiveFrame (unsigned char *, unsigned char *, unsigned char *, int *);
  short sendFrame (struct CanFrame frame);
  short receiveFrame (struct CanFrame &frame);
  void waitReceivingFrame(void);

protected:
	
private:
	/*
  VportHandle		gPortHandle;		//!< Handle to the AC2PCI CAN Card 
  Vaccess			  gChannelMask;		//!< Mask to select the channel of the card (channel 0 or 1) 
  Vaccess			  gPermissionMask;	//!< Mask of the channel selected 
  unsigned int	gCanId;				//!< Identificator of the CAN frame send by the card 
  unsigned int	gBitRate;			//!< Variable which defined the bitrate of the card 
  unsigned int	gHwType;			//!< Defined the type of the hardware use for CAN communication. for the moment the only possible value is HWTYPE_CANAC2PCI for the AC2PCI CAN Card 
  int				    gHwChannel;			//!< Defined the channel of the card what we want used (channel 0 or 1) 
  HANDLE			  gEventHandle;		//!< Handle on a windows event for known if a CAN frame is present on the frame's buffer of the card 
*/
  		XLaccess accessMask;
		XLportHandle port;
		XLhandle msgEvent;

};

#endif // XLVECTORCANDRIVER_H

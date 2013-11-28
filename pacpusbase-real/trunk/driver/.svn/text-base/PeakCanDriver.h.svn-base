/********************************************************************
//  created:    2011/02/21 - 10:39
//  filename:   PeakCanDriver.h
//
//  author:     Sergio Rodriguez
//
//  version:    $Id: PeakCanDriver.h srodrigu $
//
//  purpose:    Inherits from the CanDriver class
//              Reimplement all the virtual members of the CanDriverBase
//              class in order to be used with the Peak driver.
//              platform : Linux specific
//
*********************************************************************/

#ifndef PEAKCANDRIVER_H
#define PEAKCANDRIVER_H

#include "CanDriverBase.h"
#include "libpcan.h"
#include <fcntl.h>    // O_RDWR
#include <errno.h>
#include <string>

#define PSUCCESS                     0
#define READ_TIMEOUT                100000 // 100 miliseconds timeout

class PeakCanDriver : public CanDriverBase
{
public:
  PeakCanDriver(void);
  PeakCanDriver(int);
  PeakCanDriver(const char* port, const char* mode);
  PeakCanDriver(int channel, unsigned int bitRate);
  ~PeakCanDriver(void);

  short initPort (void);
  short cleanUpPort (void);

  short sendFrame (struct CanFrame frame);
  short receiveFrame (struct CanFrame &frame);
  void waitReceivingFrame(void);

  enum OperationMode{ReadOnly, WriteOnly, ReadWrite};

protected:

private:
  char *  szDevNode_;
  OperationMode mode_;

  HANDLE        canDeviceHandle_;

  void print_message(TPCANMsg *m);

};

#endif // PEAKCANDRIVER_H

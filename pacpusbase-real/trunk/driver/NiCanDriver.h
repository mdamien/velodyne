/*********************************************************************
//  created:    2006/08/08 - 11:43
//  filename:   NiCanDriver.h
//
//  author:     Gerald Dherbomez
// 
//  version:    $Id: NiCanDriver.h 869 2010-07-23 09:44:33Z gdherbom $
//
//  purpose:    
*********************************************************************/


#ifndef _NICANDRIVER_H_
#define _NICANDRIVER_H_


#include "CanDriverBase.h"
#include <stdio.h>


class NiCanDriver : public CanDriverBase
{
public:
  NiCanDriver(){printf("NI Can Driver used");};
  ~NiCanDriver(){};


  short initPort (void){return 1;};
  short cleanUpPort (void){return 1;};

  short sendFrame (unsigned char, unsigned char, unsigned char *){return 1;};
  short receiveFrame (unsigned char *, unsigned char *, unsigned char **){return 1;};

  void waitReceivingFrame (void){};


protected:
	
private:
};



#endif
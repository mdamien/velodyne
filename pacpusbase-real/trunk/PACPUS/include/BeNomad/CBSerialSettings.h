/*==========================================================  (-*- C++ -*-)
 *
 * @file CBSerialSettings.h 
 * 
 * @version  $Id: CBSerialSettings.h,v 1.6 2005/05/03 14:28:54 wkunkel Exp $ 
 * 
 * @author  William Kunkel
 *
 * @copyright  (c) 2002-2004 BeNomad S.A.R.L., All Rights Reserved
 *
 * BeNomad confidential file protected by international copyright laws
 * UNAUTHORIZED ACCESS, USE, REPRODUCTION OR DISTRIBUTION IS PROHIBITED.
 *
 *========================================================================*/

#ifndef _CBSERIAL_SETTINGS_H_
#define _CBSERIAL_SETTINGS_H_

/*!
  @file CBSerialSettings.h
	CBSerial class definition.
*/

#include "BTypes.h"

/**
 * @class CBSerialSettings
 * Defines the general control setting for a serial communications device.
 */
class BNAV_EXPORT CBSerialSettings
{
public:
  
  /**
   * \enum EB_BAUD_RATE
   * Defines all possible baud rates at which the communications device operates.
   */
  enum EB_BAUD_RATE {      
#if defined(_WIN32)
    B110,    //!< deprecated (see BR110)
    B300,    //!< deprecated (see BR300)
    B600,    //!< deprecated (see BR600)
    B1200,   //!< deprecated (see BR1200)
    B2400,   //!< deprecated (see BR2400)
    B4800,   //!< deprecated (see BR4800)
    B9600,   //!< deprecated (see BR9600)
    B14400,  //!< deprecated (see BR14400)
    B19200,  //!< deprecated (see BR19200)
    B38400,  //!< deprecated (see BR28400)
    B56000,  //!< deprecated (see BR56000)
    B57600,  //!< deprecated (see BR57600)
    B115200, //!< deprecated (see BR115200)
    B128000, //!< deprecated (see BR128000)
    B256000, //!< deprecated (see BR256000)
    
    BR110,    //!<    110 bits/s  
    BR300,    //!<    300 bits/s
    BR600,    //!<    600 bits/s
    BR1200,   //!<   1200 bits/s
    BR2400,   //!<   2400 bits/s
    BR4800,   //!<   4800 bits/s
    BR9600,   //!<   9600 bits/s
    BR14400,  //!<  14400 bits/s
    BR19200,  //!<  19200 bits/s 
    BR38400,  //!<  38400 bits/s 
    BR56000,  //!<  56000 bits/s 
    BR57600,  //!<  57600 bits/s
    BR115200, //!< 115200 bits/s
    BR128000, //!< 128000 bits/s
    BR256000  //!< 256000 bits/s
#else
    BR110,   //!<    110 bits/s  
    BR300,   //!<    300 bits/s
    BR600,   //!<    600 bits/s
    BR1200,  //!<   1200 bits/s
    BR2400,  //!<   2400 bits/s
    BR4800,  //!<   4800 bits/s
    BR9600,  //!<   9600 bits/s
    BR19200, //!<  19200 bits/s 
    BR38400, //!<  38400 bits/s 
    BR57600, //!<  57600 bits/s 
    BR115200 //!< 115200 bits/s 
#endif
  };

  static TBuint32 GetBaudRateValue(EB_BAUD_RATE inBaudRate);

  /**
   * \enum EB_PARITY
   * Defines all possible parity scheme.
   */
  enum EB_PARITY {    
    NO_PARITY,   //!< No parity
    EVEN_PARITY, //!< Even parity
    MARK_PARITY, //!< Mark parity    
    ODD_PARITY,  //!< Odd parity
    SPACE_PARITY //!< Space parity
  };

  /**
   * \enum EB_DATA_SIZE
   * Defines all possible data size (The number of data bits encoding a character).
   */
  enum EB_DATA_SIZE {  
    DATA_5, //!< 5 bits
    DATA_6, //!< 6 bits
    DATA_7, //!< 7 bits
    DATA_8  //!< 8 bits
  };

  /**
   * \enum EB_STOP_BITS
   * Defines all possible number of stop bits.
   */
  enum EB_STOP_BITS {  
    ONE_STOP,  //!< 1 stop bit
    ONE5_STOP, //!< 1.5 stop bits
    TWO_STOP   //!< 2 stop bits
  };

  /**
   * \enum EB_FLOW_CONTROL
   * Defines all available flow control type.
   */
  enum EB_FLOW_CONTROL {
    NO_FLOW_CONTROL = 0, //!< No flow control
    CTS_RTS,             //!< CTS/RTS hardware flow control
    CTS_DTR,             //!< CTS/DTR hardware flow control
    DSR_RTS,             //!< DSR/RTS hardware flow control
    DSR_DTR,             //!< DSR/DTR hardware flow control
    XON_XOFF             //!< Software flow control
  };

  /**
   * Constructs a new CBSerialSettings with the following default parameters :
   * baud=9600 parity=N data=8 stop=1, no flow control, no read/write time-out
   */
  CBSerialSettings(void) 
    : mBRate(BR9600),
      mParity(NO_PARITY),
      mDSize(DATA_8),
      mStopBits(ONE_STOP),
      mFlowCtrl(NO_FLOW_CONTROL),
      mReadTimeOut(0),
      mWriteTimeOut(0)
    {}
  
  /**
   * Constructs a new CBSerialSettings
   * @param inBaudRate The baud rate
   * @param inParity The parity
   * @param inDataSize The number of bits data (character size)
   * @param inStopBits The number of stop bits
   * @param inFlowCtrl The type of flow control
   * @param inReadTimeOut The read time-out in milliseconds.
   * @param inWriteTimeOut The write time-out in milliseconds.
   */
  CBSerialSettings(EB_BAUD_RATE    inBaudRate,
                   EB_PARITY       inParity,
                   EB_DATA_SIZE    inDataSize,
                   EB_STOP_BITS    inStopBits,
                   EB_FLOW_CONTROL inFlowCtrl,
                   TBuint32        inReadTimeOut,
                   TBuint32        inWriteTimeOut) 
    : mBRate(inBaudRate),
      mParity(inParity),
      mDSize(inDataSize),
      mStopBits(inStopBits),
      mFlowCtrl(inFlowCtrl),
      mReadTimeOut(inReadTimeOut),
      mWriteTimeOut(inWriteTimeOut) {}

public:

  EB_BAUD_RATE    mBRate;  
  EB_PARITY       mParity;
  EB_DATA_SIZE    mDSize;
  EB_STOP_BITS    mStopBits;
  EB_FLOW_CONTROL mFlowCtrl;
  TBuint32        mReadTimeOut;
  TBuint32        mWriteTimeOut;
};

#endif /* _CBSERIAL_SETTINGS_H_ */ 

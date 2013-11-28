  /*==========================================================  (-*- C++ -*-)
 *
 * @file CBSerialCom.h 
 * 
 * @version  $Id: CBSerialCom.h,v 1.7 2005/05/03 14:28:54 wkunkel Exp $ 
 * 
 * @author  William Kunkel
 *
 * @copyright  (c) 2002-2004 BeNomad S.A.R.L., All Rights Reserved
 *
 * BeNomad confidential file protected by international copyright laws
 * UNAUTHORIZED ACCESS, USE, REPRODUCTION OR DISTRIBUTION IS PROHIBITED.
 *
 *========================================================================*/

#ifndef _CBSERIAL_COM_H_
#define _CBSERIAL_COM_H_

/*!
  @file CBSerialCom.h
	CBSerialCom class definition.
*/

#if defined(_WIN32)
#  include <windows.h>
#else
#  include <termios.h>
#endif


#include "CBSerialLink.h"
#include "CBSerialSettings.h"

/**
 * @class CBSerialCom
 * Defines a class for handling IO operations with a serial communications device.
 */
class BNAV_EXPORT CBSerialCom : public CBSerialLink
{
public:
  
  /**
   * Constructs a new CBSerialCom.
   * @param inPort Name of the serial port or device (i.e. /dev/ttyS0).
   * @param inSettings The serial settings used to configure the communications device.
   */
  CBSerialCom(const TBchar * inPort, const CBSerialSettings & inSettings);

  /**
   * Accessor to the internal serial settings.
   * @return The serial settings currently in use.
   */
  inline CBSerialSettings * GetSerialSettings(void) { return &mSettings; }

  /**
   * Destructor
   */ 
  ~CBSerialCom(void);

  /**
   * Attempts to open the serial port and set the parameter on the port.   
   * @return \c true if the operation succeeds, \c false otherwise.
   */
  TBbool Open(void);

  /**
   * Attempts to open the serial port with new parameters.
   * @param inPort Name of the serial port or device (i.e. /dev/ttyS0).
   * @param inSettings The serial settings used to configure the communications device.
   * @return \c true if the operation succeeds, \c false otherwise.
   */
  TBbool Open(const TBchar * inPort, const CBSerialSettings & inSettings);

  /**
   * Closes the serial port.
   * @return \c true if the operation succeeds, \c false otherwise.
   */
  TBbool Close(void);

  /**
   * Returns \c true if the serial port was successfully opened, \c false otherwise.
   * @return \c true if the serial port was successfully opened, \c false otherwise.
   */
  TBbool IsOpen(void) const { 
#if defined(_WIN32)
    return mHCom != INVALID_HANDLE_VALUE; 
#else
    return mFd != -1;
#endif
}


  /**
   * Reads \a inBytesToRead bytes from the serial port.
   * @param ioBuf Pointer to buffer that receives data.
   * @param inBytesToRead Number of bytes to read.
   * @return \c true if the function succeeds, \c false otherwise.
   */
  TBbool Read(TBuint8 * ioBuf, TBuint32 inBytesToRead = 1);
  
  /**
   * Writes \a inBytesToWrite bytes to the serial port.
   * @param inBuf Pointer to buffer that contains bytes to write.
   * @param inBytesToWrite Number of bytes to write.
   * @return \c true if the function succeeds, \c false otherwise.
   */
  TBbool Write(const TBuint8 * inBuf, TBuint32 inBytesToWrite = 1);

#if defined(_WIN32)
  /**
   * Returns the Windows Handle to the communications device.
   * @return The Windows Handle to the communications device.
   */
  inline HANDLE GetComHandle(void) const { return mHCom; }
#endif

private:
  CBSerialCom(void);
  // Disable copy
  CBSerialCom(const CBSerialCom&);
  CBSerialCom & operator=(const CBSerialCom&);
private:
#if defined(_WIN32)
  HANDLE           mHCom;
#else
  int              mFd;
  struct termios   mOldOptions;
  TBchar         * mLockFile;
#endif
  TBchar         * mPort;  
  CBSerialSettings mSettings;
};

#endif /* _CBSERIAL_COM_H_ */ 



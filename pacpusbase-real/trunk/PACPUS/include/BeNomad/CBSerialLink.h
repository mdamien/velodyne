/*==========================================================  (-*- C++ -*-)
 *
 * @file CBSerialLink.h 
 * 
 * @version  $Id: CBSerialLink.h,v 1.2 2004/10/31 15:09:20 wkunkel Exp $ 
 * 
 * @author  William Kunkel
 *
 * @copyright  (c) 2002-2004 BeNomad S.A.R.L., All Rights Reserved
 *
 * BeNomad confidential file protected by international copyright laws
 * UNAUTHORIZED ACCESS, USE, REPRODUCTION OR DISTRIBUTION IS PROHIBITED.
 *
 *========================================================================*/

#ifndef _CBSERIAL_LINK_H_
#define _CBSERIAL_LINK_H_

/*!
  @file CBSerialLink.h
	CBSerialLink class definition.
*/

#include "BTypes.h"

/**
 * @class CBSerialLink
 * Defines an abstract class for handling IO operations with a generic serial device.
 */
class BNAV_EXPORT CBSerialLink
{
public:
  
  /**
   * \enum EB_ERROR
   * 
   */
  enum EB_ERROR { 
    SUCCESS = 0,         //!< Operation completed successfully.    
    CANT_OPEN_LINK,      //!< 
    CANT_GET_SETTINGS,   //!< Current serial device settings can not be obtained.
    CANT_SET_SETTINGS,   //!< An invalid configuration was specified to the serial device (E.g. invalid baud rate).
    ALREADY_OPEN,
    READ_FAULT,          //!< Cannot read from the specified device. 
    READ_TIMEOUT,        //!< Operation returned because the read timeout period expired.
    WRITE_FAULT,         //!< Cannot write to the specified device. 
    WRITE_TIMEOUT,       //!< Operation returned because the write timeout period expired.
    INSUFFICIENT_BUFFER, //!< The buffer passed to the #Read or #Write method is too small.
    IO_OP_ABORTED        //!< An IO operation was aborted.
   };

  /**
   * Constructs a new CBSerialLink object.
   */
  CBSerialLink(void) : mLastError(SUCCESS) {}

  /**
   * Destructor
   */ 
  virtual ~CBSerialLink(void) {}

  /**
   * Returns \c true if the serial link was successfully opened, \c false otherwise.
   * @return \c true if the serial link was successfully opened, \c false otherwise.
   */
  virtual TBbool IsOpen(void) const = 0;

  /**
   * Attempts to open the serial.
   * @return \c true if the operation succeeds, \c false otherwise.
   */
  virtual TBbool Open(void) = 0;

  /**
   * Closes the serial link.
   * @return \c true if the operation succeeds, \c false otherwise.
   */
  virtual TBbool Close(void) = 0;

  /**
   * Reads \a inBytesToRead bytes from this serial link.
   * @param ioBuf Pointer to buffer that receives data.
   * @param inBytesToRead Number of bytes to read.
   * @return \c true if the function succeeds, \c false otherwise.
   */
  virtual TBbool Read(TBuint8 * ioBuf, TBuint32 inBytesToRead = 1) = 0;
  
  /**
   * Writes \a inBytesToWrite bytes of \a inBuf buffer to this serial link.
   * @param inBuf Pointer to buffer that contains bytes to write.
   * @param inBytesToWrite Number of bytes to write.
   * @return \c true if the function succeeds, \c false otherwise.
   */
  virtual TBbool Write(const TBuint8 * inBuf, TBuint32 inBytesToWrite = 1) = 0;

  /**
   * Returns the last error code.
   * @return The last error code (see CBSerialLink::EB_ERROR).
   */
  EB_ERROR GetLastError(void) const { return mLastError; }

protected:
  // Disable copy
  CBSerialLink(const CBSerialLink&) {}
  CBSerialLink & operator=(const CBSerialLink&);
protected:
  EB_ERROR mLastError;
};

#endif /* _CBSERIAL_LINK_H_ */ 

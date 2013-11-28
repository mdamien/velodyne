/*==========================================================  (-*- C++ -*-)
 *
 * @file CBSerialFile.h 
 * 
 * @version  $Id: CBSerialFile.h,v 1.3 2004/12/17 14:46:35 dlabrousse Exp $ 
 * 
 * @author  William Kunkel
 *
 * @copyright  (c) 2002-2004 BeNomad S.A.R.L., All Rights Reserved
 *
 * BeNomad confidential file protected by international copyright laws
 * UNAUTHORIZED ACCESS, USE, REPRODUCTION OR DISTRIBUTION IS PROHIBITED.
 *
 *========================================================================*/

#ifndef _CBSERIAL_FILE_H_
#define _CBSERIAL_FILE_H_

/*!
  @file CBSerialFile.h
	CBSerialFile class definition.
*/

#include "CBSerialLink.h"
#include "CBFile.h"


/**
 * \def BREAD_DELAY
 * This macro creates an unsigned 32-bit value which defines 
 * a read delay for the #CBSerialFile::Read method. A read delay is
 * the time \a t to wait (in milliseconds) after reading \a n bytes.
 */
#define BREAD_DELAY(t,n)  ((t << 8) | (n & 0xFF))

/**
 * @class CBSerialFile
 * Defines a class for simulating serial input operations from a file.
 */
class BNAV_EXPORT CBSerialFile : public CBSerialLink
{
public:
  
  /**
   * Constructs a new CBSerialFile.
   * @param inFileName Full path name of the file to open.
   * @param inReadDelay The time delay which will be applied after 
   * reading a certain number of bytes (See #BREAD_DELAY macro).
   */
  CBSerialFile(const TBchar * inFileName, TBuint32 inReadDelay = 0);

  /**
   * Destructor
   */ 
  ~CBSerialFile(void);

  /**
   * Returns the current time delay (in milliseconds) that is applied
   * between two successive read operations.
   * @return The current time delay (in milliseconds) that is applied
   * between two successive read operations.
   */
  inline TBuint32 GetReadDelay(void) const { return mReadDelay; }

  /**
   * Attempts to open the serial port and set the parameter on the port.   
   * @return \c true if the operation succeeds, \c false otherwise.
   */
  TBbool Open(void);

  /**
   * Attempts to open the serial port with new parameters.
   * @param inFileName Full path name of the file to open     
   * @return \c true if the operation succeeds, \c false otherwise.
   */
  TBbool Open(const TBchar * inFileName);

  /**
   * Closes the serial port.
   * @return \c true if the operation succeeds, \c false otherwise.
   */
  TBbool Close(void);

  /**
   * Returns \c true if the serial port was successfully opened, \c false otherwise.
   * @return \c true if the serial port was successfully opened, \c false otherwise.
   */
  TBbool IsOpen(void) const { return mFile.IsValid(); }

  /**
   * Reads \a inBytesToRead bytes from the serial file.
   * @param ioBuf Pointer to buffer that receives data.
   * @param inBytesToRead Number of bytes to read.
   * @return \c true if the function succeeds, \c false otherwise.
   */
  TBbool Read(TBuint8 * ioBuf, TBuint32 inBytesToRead = 1);
  
  /**
   * Does nothing 
   * @param inBuf Pointer to buffer that contains bytes to write.
   * @param inBytesToWrite Number of bytes to write.
   * @return \c true if the function succeeds, \c false otherwise.
   */
  TBbool Write(const TBuint8 * inBuf, TBuint32 inBytesToWrite = 1);

private:
  CBSerialFile(void);
  // Disable copy
  CBSerialFile(const CBSerialFile&);
  CBSerialFile & operator=(const CBSerialFile&);
private:
  CBFile   mFile;
  TBuint32 mReadDelay;
  TBuint8  mBytesRead;
};

#endif /* _CBSERIAL_FILE_H_ */ 

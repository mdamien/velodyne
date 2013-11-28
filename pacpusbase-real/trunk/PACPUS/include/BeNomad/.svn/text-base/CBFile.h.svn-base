/*==========================================================  (-*- C++ -*-)
 *
 * @file CBFile.h 
 * 
 * @version  $Id: CBFile.h,v 1.20 2005/10/18 08:24:55 wkunkel Exp $ 
 * 
 * @author  William Kunkel
 *
 * @copyright  (c) 2002-2003 BeNomad S.A.R.L., All Rights Reserved
 *
 * BeNomad confidential file protected by international copyright laws
 * UNAUTHORIZED ACCESS, USE, REPRODUCTION OR DISTRIBUTION IS PROHIBITED.
 *
 *========================================================================*/

#ifndef _CBFILE_H_
#define _CBFILE_H_

/*!
  @file CBFile.h
	CBFile class definition.
*/

#if defined(_WIN32_WCE)
#  include <winbase.h>
#else
#  include <stdio.h>
#endif

#include "BTypes.h"
#include "CBStream.h"
#include "CBDateTime.h"

/**
 * @class CBFile
 * @brief This class encapsulates file operations.
 */
class BSVS_EXPORT CBFile : public CBStream
{
public:

  static TBbool Exists(const TBchar * inName);
  static TBbool Delete(const TBchar * inName);
  static TBbool LastModTime(const TBchar * inName, CBDateTime & ioLastModTime);
  /**
   * Constructor.
   * Attempt to open the 'inName' file. You must call the #IsValid
   * method to check if this file has been successfully opened. 
   * @param inName The file name.
   * @param inMode The access mode.
   */
  CBFile(const TBchar * inName,
				 EB_STREAM_MODE inMode = CBStream::RDONLY);

  /**
   * Destructor.
   */
  ~CBFile (void);
  
  /**
   * Returns a copy of the stream.
   * @note According to the copy constructor of the base class, 
   * the internal data block cannot be written. 
   */
  CBStream * Copy(void * inPlacement = NULL) const;

  /**
   * Returns \c true if the stream is ready for IO operations.
   * @return \c true if the stream is ready for IO operations.
   * @note User MUST call this method just after a stream constructor to
   * determine if an error occured during ctor initialization.
   */
  TBbool IsValid(void) const
	{
#if defined(_WIN32_WCE)
    return (mHnd != INVALID_HANDLE_VALUE);
#else
    return (mFd != -1);
#endif
  }
  
  /**
   * Returns \c true if the file is empty.
   * @return \c true if the file is empty.
   */
  TBbool IsEmpty(void);

  /**
   * Closes the file.
	 */
  void Close(void);

  /**
   * Reopens the current file if it was previously closed. Otherwise, 
   * the current stream pointer is set to the beginning of the file.
   * @return \c true if the file has been successfully reopened, \c false otherwise.
   * @since 1.7.0 Creation.
   */
  TBbool ReOpen(void);

  /**
   * Returns the position of the current stream pointer.
   * @return The position of the current stream pointer.
   */
  TBoff GetPos(void) const;

  /**
   * Moves the current stream pointer to the specified location.
   * @param	inOffset Specifies the number of bytes to move.
   * @param	inFromWhere The seek method.
   */
  TBbool SetPos(TBoff inOffset,	EB_SEEK inFromWhere = CBStream::FROM_START) const;
  
  /**
   * Reads data from the stream and returns number of bytes read.
   * @param	outBuffer Storage location for data
   * @param	inByteCount The number of bytes to read.
   * @return The number of bytes read.
   */
  TBuint32 ReadData(void * outBuffer,	TBuint32 inByteCount) const;

  /**
   * Provides an optimized version of the #ReadData method for reading 
   * 4 bytes.
   * @param	outBuffer Storage location for data
   * @return The number of bytes read.
   * @since 1.5.1 Creation
   */
  TBuint32 Read4Bytes(void * outBuffer) const;

  /**
   * Provides an optimized version of the #ReadData method for reading 
   * 1 byte.
   * @param	outBuffer Storage location for data
   * @return The number of bytes read.
   * @since 1.5.1 Creation
   */
  TBuint32 Read1Byte(void * outBuffer) const;

  /**
   * Writes data to the stream and returns the number of bytes written.
   * @param	inBuffer Data to be written
   * @param	inByteCount The number of bytes to write.
   * @return The number of bytes written.
   */
  TBuint32 WriteData(const void * inBuffer, TBuint32 inByteCount);

  /**
	 * Is this stream a CBMemStream ? No !
   * @return \c false
   */
  TBbool IsMemStream(void) const { return false; }

private:

#if defined(_WIN32_WCE)
  HANDLE mHnd;
#else
  int   mFd;
#endif
  TBchar * mFileName;
  
private:

  TBbool Open(void);

  CBFile (void);
  CBFile (const CBFile&);
  CBFile& operator=(const CBFile&);
  
};

#endif /* _CBFILE_H_ */

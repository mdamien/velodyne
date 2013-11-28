/*==========================================================  (-*- C++ -*-)
 *
 * @file CBStream.h
 * 
 * @version  $Id: CBStream.h,v 1.22 2005/06/24 17:52:06 wkunkel Exp $ 
 * 
 * @author  William Kunkel
 *
 * @copyright  (c) 2002-2003 BeNomad S.A.R.L., All Rights Reserved
 *
 * BeNomad confidential file protected by international copyright laws
 * UNAUTHORIZED ACCESS, USE, REPRODUCTION OR DISTRIBUTION IS PROHIBITED.
 *
 *========================================================================*/

#ifndef	_CBSTREAM_H_
#define	_CBSTREAM_H_

/*!
  @file CBStream.h
	CBStream class definition.
*/

#include "BTypes.h"

/**
 * \typedef TBoff
 * Stream offset definition
 */ 
typedef TBint32 TBoff; 


#define KB_CR 0x0D //!< Carriage Return
#define KB_LF 0x0A //!< Line Feed 

#if defined(_WIN32)
#  define KB_PATH_SEPARATOR  __T('\\')
#  define KB_MAX_PATH        MAX_PATH
#else
#  include <limits.h>
#  define KB_PATH_SEPARATOR  __T('/')
#  define KB_MAX_PATH        PATH_MAX
#endif

/**
 * @class CBStream
 * A class that defines a stream abstraction for IO operations.
 */
class BSVS_EXPORT CBStream
{
public:  

  /**
   * \enum EB_SEEK
   * Defines the three seek methods you can use to move inside a CBStream (See #SetPos).
   */
  enum EB_SEEK { 
    FROM_START,   //!< Move from the beginning of stream.
    FROM_CURRENT, //!< Move from the current position.
    FROM_END      //!< Move form the end of the stream.
   };

  /**
   * \enum EB_STREAM_MODE
   * Defines all the possible access options for a stream.
   */
  enum EB_STREAM_MODE {  
    RDONLY,  //!< Open a stream for reading. The stream is positioned at the beginning of the file.

    RDWR,    /*!< Open a stream for reading and writing. 
                  The stream is positioned at the beginning of the file.
                  (In case of a stream file, the file is created if it does not exist,  
                  otherwise it is truncated).
             */
    UPDATE,  /*!< Open a stream for reading and writing. 
                  The stream is positioned at the beginning of the file.
                  (In case of a stream file, the file is not created if it does not exist,  
                  and the stream is invalid).
              */
    APPEND   /*!< Open a stream for reading and appending. 
                  The stream is positioned at the end of the file.
                  (In case of a stream file, the file is created if it does not exist,  
                  otherwise it is truncated).
              */
  };
	
  /**
   * Destructor
   */
  virtual ~CBStream() {}

  /**
   * Returns a shared copy of the stream. 
   * @return The copied stream.
   * @note According to the copy constructor, the internal data block cannot be written. 
   */
  virtual CBStream* Copy(void * inPlacement = NULL) const = 0;	

  /**
   * Returns the length of the stream in bytes.
   * @return The length if the stream in bytes.
   */
  inline TBoff GetLength(void) const { return mLength; }

  /**
   * Returns the access option for this stream.
   * @return The access option for this stream.
   */
  inline EB_STREAM_MODE GetMode (void) const { return mMode; }
					
  /**
   * Returns \c true if the stream is ready for IO operations.
   * @return \c true if the stream is ready for IO operations.
   * @note User MUST call this method just after a stream constructor to
   * determine if an error occured during ctor initialization.
   */
  virtual TBbool IsValid (void) const = 0;

  /**
   * Returns the position of the current stream pointer.
   * @return The position of the current stream pointer.
   */
  virtual TBoff GetPos() const = 0;

  /**
   * Moves the current stream pointer to the specified location.
   * @param	inOffset Specifies the number of bytes to move
   * @param	inFromWhere The seek method
   */
  virtual TBbool SetPos(TBoff inOffset, EB_SEEK inFromWhere = CBStream::FROM_START) const = 0;

  /**
   * Reads data from the stream.
   * @param	outBuffer Storage location for data
   * @param	inByteCount The number of bytes to read.
   * @return The number of bytes read.
   */
  virtual TBuint32 ReadData(void * outBuffer, TBuint32 inByteCount) const = 0;

  /**
   * Provides an optimized version of the #ReadData method for reading 
   * 4 bytes.
   * @param	outBuffer Storage location for data
   * @return The number of bytes read.
   * @since 1.5.1 Creation
   */
  virtual TBuint32 Read4Bytes(void * outBuffer) const = 0;

  /**
   * Provides an optimized version of the #ReadData method for reading 
   * 1 byte.
   * @param	outBuffer Storage location for data
   * @return The number of bytes read.
   * @since 1.5.1 Creation
   */
  virtual TBuint32 Read1Byte(void * outBuffer) const = 0;

  /**
   * Writes data to the stream. 
   * @param	inBuffer Data to be written
   * @param	inByteCount The number of bytes to write.
   * @return The number of bytes written.
   */
  virtual TBuint32 WriteData(const void * inBuffer, TBuint32 inByteCount) = 0;

  /**
   * Returns \c true if the stream is a CBMemStream.
   * @return \c true if the stream is a CBMemStream.
   */
  virtual TBbool IsMemStream(void) const = 0;

  /**
   * Writes one string of TBint8 characters into the stream
   * @param	inString The string to write.
   * @returns	A self reference.
   */
  CBStream& operator<< (const TBint8 *inString);

  /**
   * Writes one string of TBuint8 characters into the stream.
   * @param	inString The string to write.
   * @returns	A self reference.
   */
  CBStream& operator<< (const TBuint8 *inString);

  /**
   * Writes one byte into the stream.
   * @param	inByte The byte to write.
   * @returns	A self reference.
   */
  inline CBStream& operator<< (const TBuint8 inByte)
  {
    WriteData(&inByte, sizeof(TBuint8));
    return *this;
  }
  
  /**
   * @name Special read methods.
   * Methods for reading integer values from Little-endian format.
   */
  //@{
  TBbool ReadInt8   (TBint8   & outValue) const;
  TBbool ReadUInt8  (TBuint8  & outValue) const;
  TBbool ReadInt16  (TBint16  & outValue) const;
  TBbool ReadUInt16 (TBuint16 & outValue) const;
  TBbool ReadInt32  (TBint32  & outValue) const;
  TBbool ReadUInt32 (TBuint32 & outValue) const;
  //@}

  /**
   * @name Special write methods.
   * Methods for writing integer values to Little-endian format.
   */
  //@{
  TBbool WriteInt8   (const TBint8   & inValue);
  TBbool WriteUInt8  (const TBuint8  & inValue);
  TBbool WriteInt16  (const TBint16  & inValue);
  TBbool WriteUInt16 (const TBuint16 & inValue);
  TBbool WriteInt32  (const TBint32  & inValue);
  TBbool WriteUInt32 (const TBuint32 & inValue);
  //@}


  /**
   * Reads a line of text from a generic stream.
   * This method reads an entire line of text up to (but not including) 
   * the next newline character (CRLF or LF sequence). An ending null character 
   * is automatically appended after the data stored in \a ioBuf.
   * @param ioBuf A pointer to an array of characters.
   * @param inBufSize The maximum number of characters to store, including the ternimating null character.     
   * @return The number of characters read (excluding the newline and final null character) or 
   * -1 if the end of file has been reached or -2 if the given array of characters is not enough large.        
   * @since 1.5.1
   */
  TBint32 GetLine(TBuint8 * ioBuf, TBuint32 inBufSize);

protected: 

  /**
   * Default constructor.
   */
  CBStream (void);
  
  CBStream (EB_STREAM_MODE inMode);

  CBStream(TBuint32 inLength, EB_STREAM_MODE inMode = CBStream::RDONLY);

  CBStream(const CBStream&);
  CBStream& operator=(const CBStream&);
  
protected:

  TBoff          mLength;  // The length of the stream (in bytes).  
  EB_STREAM_MODE mMode;    // Access options for the stream
};

#endif // _CBSTREAM_H_

/*==========================================================  (-*- C++ -*-)
 *
 * @file CBMemStream.h
 * 
 * @version  $Id: CBMemStream.h,v 1.21 2005/06/24 17:52:06 wkunkel Exp $ 
 * 
 * @author  William Kunkel
 *
 * @copyright  (c) 2002-2003 BeNomad S.A.R.L., All Rights Reserved
 *
 * BeNomad confidential file protected by international copyright laws
 * UNAUTHORIZED ACCESS, USE, REPRODUCTION OR DISTRIBUTION IS PROHIBITED.
 *
 *========================================================================*/

#ifndef	_CBMEMSTREAM_H_
#define	_CBMEMSTREAM_H_

/*!
  @file CBMemStream.h
	CBMemStream class definition.
*/

#include "BMacros.h"
#include "CBStream.h"


#define	KB_MEMSTREAM_DEFAULT_GROW_BY	1024   


/**
 * @class CBMemStream
 * A class that defines a memory stream reading & writing.
 */
class BSVS_EXPORT CBMemStream : public CBStream
{
public:

	/**
	 * @enum EB_MEM_TYPE
	 * This enum defines the type of memory in which the file is mapped
	 */
  enum EB_MEM_TYPE {
		RAM,  //!< RAM memory
		VM    //!< Virtual memory
	};

  /**
   * Default constructor.
   * Creates an empty memory stream for reading & writing.
   */
  CBMemStream(void);

  /**
   * Destructor
   */
  ~CBMemStream();

  /**
   * Returns a copy of the stream.
   * @note According to the copy constructor of the base class, 
   * the internal data block cannot be written. 
   */
  CBStream * Copy(void * inPlacement = NULL) const; 

  /**
   * This method allows you to map the whole content of the given file into
   * RAM or Virtual Memory.
   * @note  Data into RAM memory can be reading and writing whereas VM memory is
   * limited to reading operations.
   * @param inFileName The file to map into memory
   * @param inMode     The access options for the stream
   * @param inMemType  The type of memory in which the file has to be mapped.
	 * @return \c true if mapping was succesful, \c false otherwise.
   */
  TBbool MapFromFile(const TBchar * inFileName,
                     EB_STREAM_MODE inMode    = CBStream::RDONLY,
                     EB_MEM_TYPE    inMemType = CBMemStream::RAM);

  /**
   * Unmap the allocated data from memory.
	 * @return \c true if unmapping was succesful, \c false otherwise.
   */
  TBbool UnMap(void);

  /**
   * Returns \c true if the stream is ready for IO operations.
   * @return \c true if the stream is ready for IO operations.
   * @note User MUST call this method just after a stream constructor to
   * determine if an error occured during ctor initialization.
   */
  TBbool IsValid(void) const
	{ 
    return B_BIT_ENABLED(mFlags, VALID); 
  }

  /**
   * Returns the position of the current stream pointer.
   * @return The position of the current stream pointer.
   */
  TBoff GetPos(void) const { return mOffset; }
  
  /**
   * Moves the current stream pointer to the specified location.
   * @param	inOffset Specifies the number of bytes to move.
   * @param	inFromWhere The seek method.
   */
  TBbool SetPos(TBoff   inOffset,
								EB_SEEK inFromWhere = CBStream::FROM_START) const;

  /**
   * Sets the amount of bytes which we grow the buffer everytime it is needed.
   * @param	inGrowBy Number of bytes.
   */
  inline void SetGrowBy(TBuint32 inGrowBy) { mGrowBy = inGrowBy; }

  /**
   * Reads data from the stream and returns number of bytes read.
   * @param	outBuffer Storage location for data
   * @param	inByteCount The number of bytes to read.
   * @return The number of bytes read.
   */
  TBuint32 ReadData(void * outBuffer, TBuint32 inByteCount) const;

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
	 * Is this stream is a CBMemStream ? Yes !
   * @return \c true
   */
  virtual TBbool IsMemStream(void) const
  {
    return true;
  }

  /**
	 * Returns \c true if this stream is mapped in virtual memory.
   * @return \c true if this stream is mapped in virtual memory.
   */
  inline TBbool IsVMStream(void) const
  {
    return B_BIT_ENABLED(mFlags, MAPPED); 
  }

  /**
   * Detach and return the data block (this CBMemStream is not owner anymore).
   * @return The detached data block.
   */
  void * Detach() ;

  /**
   * Returns a pointer to the stream's data buffer
   *
   */
  inline void * GetData(void) { return mData; }

  /**
   * Shrink the memory block so that there is no extra space in it
   *
   */
  void ShrinkAllocation(void);

  /**
   * Resizes the length of the stream (truncate this stream to a specified length)
   * @param	inLength The new length of the stream in bytes.
   * @return \c false if an error occurs, \c true otherwise.
   */
  TBbool Resize(TBuint32 inLength);

private:

  enum EB_FLAGS {
    OWNER  = 0x01, // frees the data block on delete
    VALID  = 0x02, // stream ready for io ops
    MAPPED = 0x04  // stream is a mapped file
  };


  /**
   * Copy constructor.
   * @note The internal data block is not copied and user 
   * can't write the stream.The data block is shared (for reading only).
   */
  CBMemStream(const CBMemStream&);


  /**
   * Assignment operator (not implemented !)
   */
  CBMemStream& operator= (const CBMemStream &); 	


  void *   	    mData;			    // Pointer to the data block we allocated
  mutable TBoff mOffset;        // Current position in the stream
  TBuint32	    mAllocatedSize;	// Size we allocated
  TBuint32	    mGrowBy;		    // Size to grow by the allocated size
  TBuint8       mFlags;         // Internal flags (i.e EB_FLAGS enumeration)
};

#endif // _CBMEMSTREAM_H_

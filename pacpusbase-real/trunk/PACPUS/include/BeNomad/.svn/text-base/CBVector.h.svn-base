/*==========================================================  (-*- C++ -*-)
 *
 * @file CBVector.h 
 * 
 * @version  $Id: CBVector.h,v 1.15 2003/11/05 20:01:58 wkunkel Exp $ 
 * 
 * @author  William Kunkel
 *
 * @copyright (c) 2002-2003 BeNomad S.A.R.L., All Rights Reserved
 *
 * BeNomad confidential file protected by international copyright laws
 * UNAUTHORIZED ACCESS, USE, REPRODUCTION OR DISTRIBUTION IS PROHIBITED.
 *
 *========================================================================*/

#ifndef _CBVECTOR_H_
#define _CBVECTOR_H_

/*!
  @file CBVector.h
	CBVector class definition.
*/

#include "BTypes.h"
#include "BMacros.h"


#define KB_VECTOR_GROWBY  16 //!< The default number of empty slots to add each time the vector need to grow.

/**
 * \typedef  BVectorCompareFunc
 * Prototype of the comparison function used by the #Sort method which
 * is called with two arguments that point to elements in the vector.
 * The comparison function must return an integer less than, equal to, 
 * or greater than zero if the first argument is considered to be respectively
 * less than, equal to, or greater than the second. If two members compare as equal, 
 * their order in the sorted array is undefined.
 */
typedef int (*BVectorCompareFunc )(const void * elem1, const void * elem2);


/**
 * @class CBVector
 *
 * @brief A generic vector implementation of fixed size elements.
 * This class provides a growable container optimized for elements insertion
 * with a minimal extra memory cost. These elements can be either 'C' structures
 * or pointer to 'C++' classes.
 * @note Insertion of C++ classes by value is not recommended (even prohibited) 
 * because the copy constructor will never be called. In the same way, class 
 * destructors will never be called at the time of the removal of elements or 
 * vector deletion.
 * @warning Do not maintain external reference to elements added by value.
 */
class BSVS_EXPORT CBVector
{
public:

  /**
   * Constructs an empty vector of elements whose size is \a inElemSize.
   * @param inElemSize The size of each element in bytes (i.e. sizeof).
   * @param inGrowBy The number of empty slots to add each time the vector need to grow.
   * @param inLowMark The number of slots that the vector must maintain in memory.
   * This optimizes vectors which support a high number of insertion and removal of elements.
   */
  CBVector (TBuint16 inElemSize,
            TBuint32 inGrowBy  = KB_VECTOR_GROWBY,
            TBuint32 inLowMark = 0);
  
  /**
   * Constructs an empty vector of elements whose size is \a inElemSize with an initial 
   * number of empty slots.
   * @param inElemSize The size of each element in bytes (i.e. sizeof).
   * @param inInitialCapacity The number of initial empty slots.
   * @param inGrowBy The number of empty slots to add each time the vector need to grow.
   * @param inLowMark The number of slots that the vector must maintain in memory.
   * This optimizes vectors which support a high number of insertion and removal of elements.
   */
  CBVector (TBuint16 inElemSize, 
            TBuint32 inInitialCapacity,
            TBuint32 inGrowBy,
            TBuint32 inLowMark = 0); 

  /**
   * Constructs a vector from an external binary buffer.
   * @param inBuffer The external binary buffer that contains elements.
   * @param inElemCount The number of elements stored in the binary buffer.
   * @param inElemSize The size of each element in bytes (i.e. sizeof).
   * @param inOwner Set this flag to \c true if you want to pass buffer ownership to the vector.
   * @param inGrowBy The number of empty slots to add each time the vector need to grow.
   * @param inLowMark The number of slots that the vector must maintain in memory.
   * This optimizes vectors which support a high number of insertion and removal of elements.
   * @warning Not Setting buffer ownership to the vector implies that you will not be able to 
   * #Insert, #Add and #Remove elements from the vector. In this case, only read operations are
   * allowed.
   */
  CBVector (TBuint8 *  inBuffer, 
            TBuint32   inElemCount, 
            TBuint16   inElemSize,
            TBbool     inOwner,
            TBuint32   inGrowBy  = KB_VECTOR_GROWBY,
            TBuint32   inLowMark = 0);
  
  /**
   * Copy constructor.
   */
  CBVector (const CBVector& inOther);

  /**
   * Assignment operator
   */
  CBVector& operator=(const CBVector& inOther);

  /**
   * Destructor
   */
  virtual ~CBVector (void);

  /**
   * @name Accessors
   */
  //@{
  
  /**
   * Returns the number of inserted elements.
   * @return The number of inserted elements.
   */
  inline TBuint32 GetCount (void) const { return mCount; }

  /**
   * Returns the current capacity of the vector.
   * @return The current capacity of the vector (number of elements + empty slots).
   */
  inline TBuint32 GetCapacity (void) const { return mCapacity; }
  
  /**
   * Returns the size of each element.
   * @return The size of each element.
   */
  inline TBuint16 GetElemSize (void) const { return mElemSize; }
  
  /**
   * Returns the number of empty slots to add each time the vector need to grow.
   * @return The number of empty slots to add each time the vector need to grow.
   */
  inline TBuint32 GetGrowBy (void) const { return (mGrowBy / mElemSize); }
  
  /**
   * Modifies the number of empty slots to add each time the vector need to grow.
   * @param inGrowBy The new number of empty slots to add each time the vector need to grow.
   */
  inline void SetGrowBy (TBuint32 inGrowBy) { mGrowBy = (inGrowBy * mElemSize); }
  //@}

  /**
   * Inserts a new element at the specified position.
   * @param inElem The address of the element.
   * @param inIndex The position where the element must be inserted.
   * @return \c false if the given index is out of bounds or if the vector does not 
   * have the buffer ownership, \c true otherwise.
   */
  TBbool Insert (const void * inElem, TBuint32 inIndex);

  /**
   * Adds an new element at the end of the vector.
   * @param inElem The address of the element.
   * @return \c false if the vector does not have the buffer ownership, \c true otherwise.
   */
  TBuint32 Add (const void * inElem);
  
  /**
   * Removes element(s) from the vector.
   * @param inIndex The position of the first element to remove.
   * @param inHowMany The number of elements to remove.
   * @return \c false if the given index is out of bounds or if the vector does not 
   * have the buffer ownership, \c true otherwise.
   */
  TBbool Remove (TBuint32 inIndex, TBuint32 inHowMany=1);
    
  /**
   * Removes all elements from the vector.
   * @note Elements are not destroyed.
   * @param inFreeAllMemory If \c true, all allocated memory will be freed. Otherwise,
   * the vector will keep a number of empty slots defined by the low marker (see \a inLowMark 
   * argument in constructors). If \a inLowMark is zero all memory will be freed too 
   * (same as \a inFreeAllMemory is \c true).
   * @return \c false if the vector does not have the buffer ownership, \c true otherwise.
   */
  TBbool Clear (TBbool inFreeAllMemory = true);

  /**
   * Adjusts the the underlying buffer such that there is no empty slot 
   * (memory space optimization).
   */
  void Shrink (void);

  /**
   * Sorts the vector according to the user comparison function. 
   * @param inCompareFunction The user comparison function (see #BVectorCompareFunc).
   */
  void Sort (BVectorCompareFunc inCompareFunction);

  /**
   * Returns the underlying binary buffer where elements are stored.
   * @return The underlying binary buffer where elements are stored.
   */
  const TBuint8 * GetData(void) const { return mBuf;}

  /**
   * Detaches the underlying binary buffer.
   * @return The underlying binary buffer.
   */
  TBuint8 * DetachBuffer (void);

  /**
   * @brief Reference operator. 
   * Returns a reference to the element located at the given position.
   * @param inIndex The position of the element to return.
   * @note The index \a inIndex must be between 0 and the size less one.
   * @return A reference to the specified element.
   */
  inline void*& operator[] (TBuint32 inIndex) 
  {
    B_ASSERT (inIndex < mCount);
    return * (void **) (mBuf + (inIndex * mElemSize));
  }

   /**
   * @brief Const reference operator. 
   * Returns a reference to the element located at the given position.
   * @param inIndex The position of the element to return.
   * @note The index \a inIndex must be between 0 and the size less one.
   * @return A reference to the specified element.
   */
  inline const void*& operator[] (TBuint32 inIndex) const
  {
    B_ASSERT (inIndex < mCount);
    return * (const void **) (mBuf + (inIndex * mElemSize));
  }

  /** @example vector_usage.cpp
   * This is an example of how to use the CBVector class.
   */

protected:

  CBVector (void);

  /**
   * @internal
   */
  TBbool Allocate (TBuint32 inNeededBytes);
  
private:
  
  enum EB_FLAGS {
    EB_OWNER  = 0x01, // frees the data block on delete
  };

  TBuint8 * mBuf;
  TBuint32  mCount;
  TBuint32  mCapacity;
  TBuint32  mGrowBy;  
  TBuint32  mLowMark;
  TBuint16  mElemSize;
  TBuint8   mFlags;  
};

#endif /* _CBVECTOR_H_ */

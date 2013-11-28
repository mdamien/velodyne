/*==========================================================  (-*- C++ -*-)
 *
 * @file CBHashMapIter.h
 * 
 * @version  $Id: CBHashMapIter.h,v 1.6 2003/06/11 19:51:45 wkunkel Exp $ 
 * 
 * @author  William Kunkel
 *
 * @copyright  (c) 2002-2003 BeNomad S.A.R.L., All Rights Reserved
 *
 * BeNomad confidential file protected by international copyright laws
 * UNAUTHORIZED ACCESS, USE, REPRODUCTION OR DISTRIBUTION IS PROHIBITED.
 *
 *========================================================================*/

#ifndef _CBHASH_MAP_ITER_H_
#define _CBHASH_MAP_ITER_H_

/*!
  @file CBHashMapIter.h
	CBHashMapIter class definition.
*/

#include "CBHashMap.h"


/**
 * @class CBHashMapIter
 * This class defines an iterator over all #CBHashMap's entries.
 * @warning While iterating over elements, you <b>DO NOT PERFORM ANY MODIFICATIONS</b>
 * on the associated hashmap !
 */
class BSVS_EXPORT CBHashMapIter
{
public:
  /**
   * Constructs a new iterator over entries stored in the given hashmap.
   * @param inHashMap The hashmap to iterate.
   */
  CBHashMapIter (const CBHashMap * inHashMap)
    : mHashMap   (inHashMap),
      mBucketIdx (0),
      mPairIdx   ((TBuint32)-1) {}

  /**
   * Copy constructor.
   */
  CBHashMapIter (const CBHashMapIter& inSource)
    : mHashMap   (inSource.mHashMap),
      mBucketIdx (inSource.mBucketIdx),
      mPairIdx   (inSource.mPairIdx) {}
  
  /**
   * Assignment operator.
   */
  CBHashMapIter & operator=(const CBHashMapIter& inOther)
  { 
    if (&inOther != this) {
      mHashMap   = inOther.mHashMap;
      mBucketIdx = inOther.mBucketIdx;
      mPairIdx   = inOther.mPairIdx;
    }
    return *this;
  }

  /**
   * Assigns a new hashmap.
   * @param inHashMap The new hashmap to iterate.
   */
  void SetHashMap (const CBHashMap * inHashMap) {
    mHashMap = inHashMap;
    Reset();
  }

  /**
   * Positions the iterator to the next hashmap's entry.
   * If this method returns \c true, key and value of the current entry 
   * might be retrieved via #GetKey and #GetValue methods.
   * @return \c true if the iteration has more elements, \c false otherwise.
   */
  TBbool Next (void);

  /**
   * Resets the iterator to the first hashmap's entry (if any).
   */
  void Reset(void);

  /**
   * @return the current entry's key.
   */
  inline TBany CBHashMapIter::GetKey(void)
  {
    return mHashMap->mBuckets[mBucketIdx]->GetKey(mPairIdx);
  }

	/**
   * @return the current entry's value.
   */
  inline TBany CBHashMapIter::GetValue(void)
  {
    return mHashMap->mBuckets[mBucketIdx]->GetValue(mPairIdx);
  }

private:

  const CBHashMap * mHashMap;
  TBuint32          mBucketIdx;
  TBuint32          mPairIdx;
};

#endif /* _CBHASH_MAP_ITER_H_ */

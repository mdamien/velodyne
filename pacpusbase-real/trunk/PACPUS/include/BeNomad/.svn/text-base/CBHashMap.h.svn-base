/*==========================================================  (-*- C++ -*-)
 *
 * @file CBHashMap.h
 * 
 * @version  $Id: CBHashMap.h,v 1.17 2003/09/05 12:38:11 wkunkel Exp $ 
 * 
 * @author  William Kunkel
 *
 * @copyright  (c) 2002-2003 BeNomad S.A.R.L., All Rights Reserved
 *
 * BeNomad confidential file protected by international copyright laws
 * UNAUTHORIZED ACCESS, USE, REPRODUCTION OR DISTRIBUTION IS PROHIBITED.
 *
 *========================================================================*/

#ifndef _CBHASH_MAP_H_
#define _CBHASH_MAP_H_

/*!
  @file CBHashMap.h
	CBHashMap class definition.
*/

#include "BTypes.h"
#include "CBVector.h"

/**
 * \typedef TBHashFunc  
 * Prototype of Hash Functions
 */
typedef TBuint32 (*TBHashFunc) (TBany key, const TBuint32 inBucketsNum);

/** 
 * \typedef TBHashMatchFunc
 * Prototype of Match Functions
 */
typedef TBbool (*TBHashMatchFunc) (TBany key, TBany value,  TBany userArg);


/**
 * @name Predefined Hash functions
 * A set of hash functions which provide an efficient distribution. 
 */
 //@{
/**
 * \relates CBHashMap
 * A function for hashing TBuint32 keys.
 */
TBuint32 BSVS_EXPORT Buint32HashFunc (TBany key, const TBuint32 inBucketsNum);
/**
 * \relates CBHashMap
 * A function for hashing pointer to TBuint32 keys.
 */
TBuint32 BSVS_EXPORT Buint32PtrHashFunc (TBany key, const TBuint32 inBucketsNum);
/**
 * \relates CBHashMap
 * A function for hashing ANSI string keys (case-sensitive).
 */
TBuint32 BSVS_EXPORT BStrCaseHashFunc (TBany key, const TBuint32 inBucketsNum);
/**
 * \relates CBHashMap
 * A function for hashing ANSI string keys (non case-sensitive).
 */
TBuint32 BSVS_EXPORT BStrNCaseHashFunc (TBany key, const TBuint32 inBucketsNum);

#if defined(_UNICODE)
/**
 * \relates CBHashMap
 * A function for hashing Unicode string keys (case-sensitive).
 */
TBuint32 BSVS_EXPORT BWCSCaseHashFunc (TBany key, const TBuint32 inBucketsNum);
/**
 * \relates CBHashMap
 * A function for hashing Unicode string keys (non case-sensitive).
 */
TBuint32 BSVS_EXPORT BWCSNCaseHashFunc (TBany key, const TBuint32 inBucketsNum);
#endif
//@}

#if defined(_UNICODE)
#  define BTSTRCASEHASHFUNC  BWCSCaseHashFunc
#  define BTSTRNCASEHASHFUNC BWCSNCaseHashFunc
#else
#  define BTSTRCASEHASHFUNC  BStrCaseHashFunc
#  define BTSTRNCASEHASHFUNC BStrNCaseHashFunc
#endif


/**
 * @name Predefined Match functions
 * 
 */
//@{
/**
 * \relates CBHashMap
 * A function to match ANSI string keys (case-sensitive).
 */
TBbool BSVS_EXPORT BStrCaseMatchFunc  (TBany key, TBany value, TBany userArg);

/**
 * \relates CBHashMap
 * A function to match ANSI string keys (non case-sensitive).
 */
TBbool BSVS_EXPORT BStrNCaseMatchFunc (TBany key, TBany value, TBany userArg);

#if defined(_UNICODE)
/**
 * \relates CBHashMap
 * A function to match Unicode string keys (case-sensitive).
 */
TBbool BSVS_EXPORT BWCSCaseMatchFunc  (TBany key, TBany value, TBany userArg);

/**
 * \relates CBHashMap
 * A function to match Unicode string keys (non case-sensitive).
 */
TBbool BSVS_EXPORT BWCSNCaseMatchFunc (TBany key, TBany value, TBany userArg);
#endif
//@}

#if defined(_UNICODE)
#  define BTSTRCASEMATCHFUNC  BWCSCaseMatchFunc
#  define BTSTRNCASEMATCHFUNC BWCSNCaseMatchFunc
#else
#  define BTSTRCASEMATCHFUNC  BStrCaseMatchFunc
#  define BTSTRNCASEMATCHFUNC BStrNCaseMatchFunc
#endif


/**
 * @class CBHashMap
 *
 * @brief CBHashMap : An Associative Container (AC).
 *
 * The CBHashMap class defines an unique associative container that supports  
 * efficient retrieval of elements (values) based on keys : According to the 
 * \a inUniqueness ctor argument, the CBHashMap implements either a multiple 
 * AC or a unique AC where each key is unique (no two elements have the same key).
 */
class BSVS_EXPORT CBHashMap
{
public:

  /**
   * Constructs a new empty CBHashMap.
   * @param inHashFunc  The hash function which depends on the key type. 
   * @param inBuckets   The initial number of buckets which determined the hashmap capacity.
   * In the case of "hash collision", a single bucket stores multiple entries, which must be searched sequentially.
   * @param inBucketsGrowBy The number of empty slots to add each time a bucket need to grow.
   * @param inUniqueness Indicates if the hashmap defines an unique associative container or not.
   */
  CBHashMap (TBHashFunc inHashFunc,
             TBuint32   inBuckets,
             TBuint32   inBucketsGrowBy,
             TBbool     inUniqueness=true);

  /**
   * Copy constructor
   */
  CBHashMap (const CBHashMap& inSource);

  /**
   * Destructor
   */
  ~CBHashMap (void);

  /**
   * Returns the number of inserted pairs (key/value). 
   * @return The number of inserted pairs (key/value). 
   */
  inline TBuint32 GetCount (void) const { return mCount; }

  /**
   * Returns the number of empty slots to add each time a bucket need to grow.
   * @return The number of empty slots to add each time a bucket need to grow.
   */
  inline TBuint32 GetBucketsGrowBy (void) const { return mBucketsGrowBy; }
  
  /**
   * Sets the number of empty slots to add each time a bucket need to grow.
   * @param inGrowBy The new number of empty slots to add each time a bucket need to grow.
   */
  void SetBucketsGrowBy(TBuint32 inGrowBy);

  /**
   * Returns \c true if this hashmap defines a unique associative container, \c false otherwise.
   * @return \c true if this hashmap defines a unique associative container, \c false otherwise.
   */
  inline TBbool GetUniqueness (void) const { return mUniqueness; }

  /**
   * @brief Inserts a new key/value pair in the HashMap.
   * 
   * If the HashMap defines an unique associative container, the \a inForceInsertion 
   * argument allows you to optimize elements insertion by bypassing all relative
   * checks to the uniqueness constraint. That assumes that uniqueness is guaranteed 
   * by the caller !
   * If the previous flag is set to \c false and depending on the \a inReplaceValue argument 
   * this method may replace or not an existing value, the key of which match the given 
   * key and an optional user matching function. 
   *
   * @param inKey The key.
   * @param inValue The Value to insert.
   * @param inForceInsertion Otimizes elements insertion (To use with care !)
   * @param inReplaceValue Indicates if an existing value must be replaced or not
   * (have no effect if \a inForceInsertion is defined).
   * @param inMatchFunc The user matching function.
   * @param inUserArg A user data to pass to the matching function.
   * @return The added or replaced value or NULL.
   */
  TBany Insert (TBany           inKey, 
                TBany           inValue,
                TBbool          inForceInsertion=false,
                TBbool          inReplaceValue=false,
                TBHashMatchFunc inMatchFunc=NULL,
                TBany           inUserArg=NULL);

  /**
   * Removes all entries from the hashmap that match the given key and 
   * an optional user matching function.
   * @param inKey The key of entries to remove.
   * @param inMatchFunc An optional matching function.
   * @param inUserArg A user data to pass to the matching function.
   */
  TBuint32 Remove (TBany           inKey, 
                   TBHashMatchFunc inMatchFunc=NULL, 
                   TBany           inUserArg=NULL);

  /**
   * Retrieves the value to which the specified key is mapped in this hashmap.
   * @note In case of multiple associative container, only the first value that matches
   * the specified key is returned !
   * @param inKey The key of the value to retrieve.
   * @param inMatchFunc An optional matching function.
   * @param inUserArg A user data to pass to the matching function.
   */
  TBany Find (TBany           inKey, 
              TBHashMatchFunc inMatchFunc=NULL, 
              TBany           inUserArg=NULL);

  /**
   * Applies a user fonction to all stored entries.
   * @param ApplyFunc The user function to apply
   * @param inUserArg A user data to pass to the user function.
   */
  void ApplyToAll (void (*ApplyFunc)(TBany key, TBany value, TBany userArg), 
                  TBany inUserArg=NULL) const;

  /**
   * Adjusts buckets allocations such that there is no empty slot. 
   */
  void ShrinkBucketsAllocation(void);
	
  /**
   * Removes all entries from the hashmap.
   */
	void Clear (void);

#ifdef _DEBUG
  void PrintStats (void);
#endif

protected:

  class CBBucket : public CBVector
  {
  public:

    CBBucket (TBuint32 inGrowBy);
    ~CBBucket (void) {}

    void AddPair (TBany inKey, TBany inVal);

    inline TBany GetKey (TBuint32 inIdx) const {
      return ((TB_PAIR &) (*this)[inIdx]).mKey;
    } 

    inline TBany GetValue (TBuint32 inIdx) const {
      return ((TB_PAIR &) (*this)[inIdx]).mValue;
    } 

    inline void SetValue (TBuint32 inIdx, TBany inVal) {
      ((TB_PAIR &) (*this)[inIdx]).mValue = inVal;
    }

  protected:
    struct TB_PAIR {
      TB_PAIR () 
        : mKey(NULL), mValue(NULL) {}
      
      TB_PAIR (TBany inKey, TBany inVal) 
        : mKey(inKey), mValue(inVal) {}
      
      TBany mKey;
      TBany mValue;
    };

    CBBucket (void);
  };

private:

  TBHashFunc mHashFunc;
  CBBucket** mBuckets;
  TBuint32   mBucketsCount;
  TBuint32   mBucketsGrowBy;
  TBuint32   mCount;
  TBbool     mUniqueness;

  CBHashMap (void);
  CBHashMap& operator=(const CBHashMap & inSource);

  friend class CBHashMapIter;
};

#endif /* _CBHASH_MAP_H_ */



/*==========================================================  (-*- C++ -*-)
 *
 * @file CBMutex.h
 * 
 * @version  $Id: CBMutex.h,v 1.22 2005/03/30 14:44:00 wkunkel Exp $ 
 * 
 * @author  William Kunkel
 *
 * @copyright  (c) 2002-2003 BeNomad S.A.R.L., All Rights Reserved
 *
 * BeNomad confidential file protected by international copyright laws
 * UNAUTHORIZED ACCESS, USE, REPRODUCTION OR DISTRIBUTION IS PROHIBITED.
 *
 *========================================================================*/

#ifndef _CBMUTEX_H_
#define _CBMUTEX_H_

#if defined(_BMT_SAFE) || defined(_BENABLE_MUTEX)

/*!
  @file CBMutex.h
	CBMutex class definition.
*/

#if defined(_WIN32)
#  if !defined(_WIN32_WCE)
#    define _WIN32_WINNT 0x0400 // For TryLock method
#  endif
#  include <windows.h> 
#else
#  include <pthread.h>
#endif

#include "BTypes.h"


/**
 * @class CBMutex
 *
 * The CBMutex class provides an implementation of a non-recursive or recursive
 * mutex for access serialization between threads. 
 *
 * @note You should compile this file with the macro _BMT_SAFE defined (eg. compile with -D_BMT_SAFE).
 */
class BSVS_EXPORT CBMutex
{
public:
  /**
   * Creates and initialize a new mutex.
   * @param inRecursive \c false for creating a non-recursive mutex (have no effect on WIN32 platforms)
   * @note WIN32 mutexes are always recursive !
   */
  CBMutex(TBbool inRecursive = true);

  /**
   * Destroy the mutex.
   */
  virtual ~CBMutex(void);

  /**
   * Attempts to lock the mutex. If another thread has locked the mutex 
   * then this call will block until that thread has unlocked it. 
   * @note If the mutex is of the "recursive" type, \c Lock succeeds and 
   * returns immediately, recording the number of times the calling thread 
   * has locked the mutex. An equal number of unLock operations 
   * must be performed before the mutex returns to the unlocked state.
   */
  void Lock(void);

  /** 
   * Try to lock the mutex and returns immediately.
   * @return true if the mutex was locked, false otherwise.
   * @warning Not supported on Windows 98.
   **/
  TBbool TryLock(void);
   
  /**
   * Unlocks the mutex.
   */
  void Unlock(void);

private:

  // Disable copy
  CBMutex (const CBMutex &);
  CBMutex &operator=( const CBMutex & );

#if defined(_WIN32)
  CRITICAL_SECTION     mMutex;
#else
  pthread_mutex_t      mMutex;
  pthread_mutexattr_t  mAtt;
#endif

};


/**
 * @class CBMutexGuard
 *
 * @brief This class implements the guard mechanism for mutex objects.
 * The Guard will lock the given mutex when it is created and automatically 
 * unlock it when it goes out of scope. 
 * This eliminates common mistakes like forgetting to unlock your mutex. 
 *
 */
class BSVS_EXPORT CBMutexGuard
{
public:
  /**
   * Creates a mutex Guard by locking the given mutex.
   * @param inMutex The mutex to lock
   */
  CBMutexGuard (CBMutex & inMutex) 
    : mMutex (inMutex) { mMutex.Lock();   }

  /**
   * Unlocks the associated mutex and destroys the Guard. 
   */
  ~CBMutexGuard (void) { mMutex.Unlock(); }

private:
  CBMutexGuard (void);
  CBMutexGuard (const CBMutexGuard&);
  CBMutexGuard & operator=(const CBMutexGuard&);
private:
  CBMutex & mMutex;
};

// A useful macro to define a mutex Guard
#  define B_GUARD(m)        CBMutexGuard guarded##m (m)
#  define B_MUTEX_LOCK(m)   (m).Lock()
#  define B_MUTEX_TRYLOCK(m)(m).TryLock()
#  define B_MUTEX_UNLOCK(m) (m).Unlock()
#else // !_BMT_SAFE && !_BENABLE_MUTEX
#  define B_GUARD(m)   
#  define B_MUTEX_LOCK(m) 
#  define B_MUTEX_TRYLOCK(m)
#  define B_MUTEX_UNLOCK(m)
#endif

#endif /* _CBMUTEX_H_ */

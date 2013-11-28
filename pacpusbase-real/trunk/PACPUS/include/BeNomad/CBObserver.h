/*==========================================================  (-*- C++ -*-)
 *
 * @file CBObserver.h 
 * 
 * @version  $Id: CBObserver.h,v 1.13 2005/03/30 14:44:07 wkunkel Exp $ 
 * 
 * @author  William Kunkel
 *
 * @copyright  (c) 2002-2003 BeNomad S.A.R.L., All Rights Reserved
 *
 * BeNomad confidential file protected by international copyright laws
 * UNAUTHORIZED ACCESS, USE, REPRODUCTION OR DISTRIBUTION IS PROHIBITED.
 *
 *========================================================================*/

#ifndef _CBOBSERVER_H_
#define _CBOBSERVER_H_

/*!
  @file CBObserver.h
	CBObserver class definition.
*/

#include "CBVector.h"
#include "CBMutex.h"


class CBSubject;

/**
 * @class CBObserver
 *
 * @brief A class that implements the Observer part of the MVC 
 * (Model View Controler) Design Pattern.
 * 
 */
class BSVS_EXPORT CBObserver
{
public:

  /**
   * Destructor (does nothing).
   */
  virtual ~CBObserver(void) {}

  /**
   * This method reflects a Subject notification. 
   * @param inChangedSubject The subject who sends the notification.
   * @param inEventType The type of notification.
   * @param inUserData  A user data.
   */
  virtual void Update(CBSubject * inChangedSubject, 
                      TBuint32    inEventType,
                      TBany       inUserData=NULL) = 0;

#if defined(_BMT_SAFE)  
 /**
   * If the multithreading support is active, all CBObserver specializations
   * should implement the Lock method in order to guarantee the thread safety
   * during the Subject's notification.   
   */
  virtual void Lock(void) = 0;
   
  /**
   * If the multithreading support is active, all CBObserver specializations
   * should implement the Unlock method in order to guarantee the thread safety
   * during the Subject's notification.   
   */
  virtual void Unlock(void) = 0;
#endif

protected:

  CBObserver(void) {}
};



/**
 * @class CBSubject
 *
 * @brief A class that implements the Subject part of the MVC 
 * (Model View Controler) Design Pattern.
 * A subject may have any number of dependent observers and 
 * observers are notified whenever the subject undergoes a change 
 * in state (#CBObserver).
 * 
 */
class BSVS_EXPORT CBSubject
{
public:
  
  /**
   * Destructor
   */
  virtual ~CBSubject(void) {}

  /**
   * Returns the number of currently attached Observers.
   * @return The number of currently attached Observers.
   */
  TBuint32 GetNbObservers(void) const ;

  /**
   * Attaches a new Observer.
   * @param inObserver The Observer to attach.
   */
  virtual void Attach(CBObserver * inObserver);

  /**
   * Detaches the given Observer.
   * @param inObserver The Observer to detach.
   */
  virtual void Detach(CBObserver * inObserver);

  /**
   * Sends a notification to all the attached Observers.
   * @param inEventType The type of notification
   * @param inUserData A user data.
   */
  virtual void Notify(TBuint32 inEventType, TBany inUserData=NULL);
  
protected:
  
  /**
   * Constructs a Subject with an empty list of Observer.
   */
  CBSubject (void)
    : mObservers (sizeof(CBObserver *), 4) {}

  CBSubject (const CBSubject& inSource)
    : mObservers (inSource.mObservers) {}

  CBSubject& operator=(const CBSubject& inOther) {
    if (this != &inOther) {
      mObservers = inOther.mObservers;
    }
    return *this;
  }
  
private:

  CBVector mObservers;
#if defined(_BMT_SAFE)
  mutable CBMutex  mMutex;
#endif
};

#endif /* _CBOBSERVER_H_ */

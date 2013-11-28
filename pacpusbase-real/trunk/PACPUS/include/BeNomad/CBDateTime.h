/*==========================================================  (-*- C++ -*-)
 *
 * @file CBDateTime.h
 * 
 * @version  $Id: CBDateTime.h,v 1.6 2004/10/31 13:35:55 wkunkel Exp $ 
 * 
 * @author  William Kunkel
 *
 * @copyright (c) 2002-2004 BeNomad S.A.R.L., All Rights Reserved
 *
 * BeNomad confidential file protected by international copyright laws
 * UNAUTHORIZED ACCESS, USE, REPRODUCTION OR DISTRIBUTION IS PROHIBITED.
 *
 *========================================================================*/

#ifndef _CBDATE_TIME_H_
#define _CBDATE_TIME_H_

/*!
  @file CBDateTime.h
	CBDateTime class definition.
*/
#if defined(_WIN32) // For SYSTEMTIME and FILETIME structures
#  include <windows.h>
#endif

#include "BConfig.h"

#if defined(HAVE_TIME_T)
#  include <time.h>
#elif !defined(_TIME_T_DEFINED)
  typedef long time_t;
#endif


  
#include "BTypes.h"

/**
 * @class CBDateTime
 * @brief A class that provides methods for manipulating and comparing a
 * calendar date and a clock time (a "datetime"). 
 */
class BSVS_EXPORT CBDateTime
{
public:

  /**
   * Constructs a new CBDateTime object with the current system time 
   * (ie. number of seconds elapsed since UTC 01/01/1970). 
   */
  CBDateTime (void);

  /**
   * Constructs a new CBDateTime object from the specified date and time
   * @param inTime The Date and time (ie. number of seconds elapsed since UTC 01/01/1970). 
   */
  CBDateTime (time_t inTime);

#if defined(_WIN32) 
  /**
   * Constructs a new CBDateTime object from the Windows SYSTEMTIME structure.
   * @param inSysTime The Windows SYSTEMTIME structure to convert.
   * @note SYSTEMTIME::wMilliseconds are ignored.
   */
  CBDateTime (const SYSTEMTIME & inSysTime);

  /**
   * Constructs a new CBDateTime object from the Windows FILETIME structure which
   * represents the number of 100-nanosecond intervals since January 1, 1601.
   * @param inFileTime The Windows FILETIME structure to convert.   
   */
  CBDateTime (const FILETIME & inFileTime);
#endif

  /**
   * Constructs a new CBDateTime from the specified date and time components.   
   * @note You should use #IsValid to check whether the conversion successed.
   */
  CBDateTime (TBint16 inYear, 
              TBint16 inMonth, 
              TBint16 inDay,
              TBint16 inHour=0, TBint16 inMin=0, TBint16 inSec=0);

  /**
   * Constructs a new CBDateTime from a string representation.
   * @param inDate A "DD/MM/YYYY" formatted string
   * @param intime A "hh:mm:ss" formatted string
   * @note You should use #IsValid to check whether the conversion successed.
   */
  CBDateTime (const TBchar * inDate, const TBchar * inTime=NULL);

  /**
   * Copy constructor
   */
  CBDateTime (const CBDateTime& inSource);

  /**
   * Assignment operator
   */
  CBDateTime& operator=(const CBDateTime& inOther);

  /**
   * Assignment operator.
   * @param inTime A time_t value (number of seconds elapsed since UTC 01/01/1970)   
   */
  CBDateTime& operator =(time_t inTime);

  /**
   * Destructor
   */
  ~CBDateTime (void) {}
  
  /**
   * Returns \c true if the current CBDateTime is a valid datetime, \c false otherwise.
   */
  inline TBbool IsValid (void) const { return mTime != -1; }

#if defined(HAVE_TIME_T)
  /**
   * Returns a broken-down time representation of the current CBDateTime for the local time zone.
   * <I>Broken-down time</I> is a binary representation of calendar time separated into year, 
   * month, day, and so on (ie. tm structure).
   */
  void GetBrokenDownTime (struct tm * inTm);
#endif

  /**
   * Formats this CBDateTime object according to the format specification \c inFormat 
   * and places the result in the character array \c ioStrs of size \c inMax.
   * @return the number of characters placed in the array \c ioStr, not including the 
   * terminating NULL character.
   * @note e.g strftime function
   **/
  TBint16 AsString (TBchar * ioStr, TBint16 inMax, const TBchar * inFormat);

  void AddRemoveYears    (TBint16  inHowMany);
  void AddRemoveMonths   (TBint16  inHowMany);
  void AddRemoveDays     (TBuint32 inHowMany);
  void AddRemoveHours    (TBuint32 inHowMany);
  void AddRemoveMinutes  (TBuint32 inHowMany);
  void AddRemoveSecondes (TBuint32 inHowMany);

  friend bool operator==(const CBDateTime& inD1, const CBDateTime& inD2);
  friend bool operator!=(const CBDateTime& inD1, const CBDateTime& inD2);
  friend bool operator>=(const CBDateTime& inD1, const CBDateTime& inD2);
  friend bool operator<=(const CBDateTime& inD1, const CBDateTime& inD2);
  friend bool operator> (const CBDateTime& inD1, const CBDateTime& inD2);
  friend bool operator< (const CBDateTime& inD1, const CBDateTime& inD2);

  /**
   * Returns the difference between two CBDateTime.
   * @return The elapsed time in seconds as a double-precision floating-point number.
   */
  TBdouble operator-(const CBDateTime& inDate);

    
  operator time_t(void) const { return mTime; }   

private:

#if !defined(HAVE_TIME_T)
  static TBint16 mMonthDays[2][13];
#endif

  // Represents the time in seconds since 00:00:00 UTC, January 1, 1970.
  time_t  mTime; 
};

#endif /* _CBDATE_TIME_H_ */

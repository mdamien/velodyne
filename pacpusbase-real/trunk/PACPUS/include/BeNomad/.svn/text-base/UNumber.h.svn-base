/*==========================================================  (-*- C++ -*-)
 *
 * @file UNumber.h 
 * 
 * @version  $Id: UNumber.h,v 1.4 2003/06/11 19:51:45 wkunkel Exp $ 
 * 
 * @author  William Kunkel
 *
 * @copyright  (c) 2002-2003 BeNomad S.A.R.L., All Rights Reserved
 *
 * BeNomad confidential file protected by international copyright laws
 * UNAUTHORIZED ACCESS, USE, REPRODUCTION OR DISTRIBUTION IS PROHIBITED.
 *
 *========================================================================*/

#ifndef _UNUMBER_H_
#define _UNUMBER_H_

/*!
  @file UNumber.h
	UNumber class definition.
*/

#include "BTypes.h"

/**
 * @class UNumber
 * A useful class which provides methods for dealing with string conversions.
 */
class BSVS_EXPORT UNumber
{
public:

  /**
   * @name String to numerical values
   * All the following methods return \c false if an error occurs.
   */
  //@{
  static TBbool ToInt16  (const TBint8 * inString, TBint16  & outValue);
  static TBbool ToUInt16 (const TBint8 * inString, TBuint16 & outValue);
  static TBbool ToInt32  (const TBint8 * inString, TBint32  & outValue);
  static TBbool ToUInt32 (const TBint8 * inString, TBuint32 & outValue);
  static TBbool ToFloat  (const TBint8 * inString, TBfloat  & outValue);
  static TBbool ToDouble (const TBint8 * inString, TBdouble & outValue);
  //@}
private:
  UNumber(void);
  UNumber (const UNumber&);
  UNumber & operator=(const UNumber&);
};
#endif /* _UNUMBER_H_ */

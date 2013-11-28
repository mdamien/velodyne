/*==========================================================  (-*- C++ -*-)
 *
 * @file CBFormFactory.h
 * 
 * @version  $Id: CBFormFactory.h,v 1.14 2005/02/10 10:05:11 wkunkel Exp $ 
 * 
 * @author  William Kunkel
 *
 * @copyright  (c) 2002-2005 BeNomad S.A.R.L., All Rights Reserved
 *
 * BeNomad confidential file protected by international copyright laws
 * UNAUTHORIZED ACCESS, USE, REPRODUCTION OR DISTRIBUTION IS PROHIBITED.
 *
 *========================================================================*/

#ifndef __CBFORM_FACTORY_H__
#define __CBFORM_FACTORY_H__

/*!
  @file CBFormFactory.h
	CBFormFactory class definition.
*/

#include "BTypes.h"

class CBForm;
class CBObjectMgr;
class CBCursor;
class CBBitStream;
class CBTreeParser;

/**
 * @class CBFormFactory
 *
 * @brief This static class provides factorization for calling any type of SVS forms contructors
 *
 */
class BSVS_EXPORT CBFormFactory
{
public:

  /**
   * Calls one of SVS form constructor according to geometric type defined in \a inObject,
	 * computes form's bounding rectangle and returns new form.
   * @param inObject Object to build from
   * @param in3D If \c true, calls a 3D form constructor, if \c false, calls a 2D constructor
   * @param outRect Form's bounding rectangle
   * @return New form
   */
  static CBForm * CreateForm(const TB_EXTERN_OBJECT& inObject,
                             TBbool                  in3D,
                             TB_LONGRECT           & outRect);

  /**
   * \internal
   */
  static CBForm * CreateForm(CBBitStream        * inBitStream,
                             const CBObjectMgr  * inObjectMgr,
                             const CBTreeParser * inTreeParser,
                             TBbool               in3D = false);

  /**
   * \internal
   */
  static CBForm * CreateForm(CBCursor          * inCursor,
                             const CBObjectMgr * inObjectMgr,
                             TBbool              in3D = false);

  /**
   * Returns name corresponding to \a inType.
	 * @param inType Geometric type
	 * @return One of "ABSTRACT", "POINT", "OPEN", "CLOSED", "RECTANGLE", "ARC", "CIRCLE",
	 * "ELLIPSE" or "COMPLEX"
	 */
  static const TBint8 * GetFormName(EB_GEOTYPE inType);

private:

  CBFormFactory(void);
  CBFormFactory(const CBFormFactory&);
  CBFormFactory& operator=(const CBFormFactory&);
};


#endif /* __CBFORM_FACTORY_H__ */

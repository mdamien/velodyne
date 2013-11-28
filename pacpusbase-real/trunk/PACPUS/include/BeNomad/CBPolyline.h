/*==========================================================  (-*- C++ -*-)
 *
 * @file CBPolyline.h
 * 
 * @version  $Id: CBPolyline.h,v 1.1 2005/02/10 10:14:06 wkunkel Exp $ 
 * 
 * @author  William Kunkel
 *
 * @copyright  (c) 2002-2005 BeNomad S.A.R.L., All Rights Reserved
 *
 * BeNomad confidential file protected by international copyright laws
 * UNAUTHORIZED ACCESS, USE, REPRODUCTION OR DISTRIBUTION IS PROHIBITED.
 *
 *========================================================================*/

#ifndef _CBPOLYLINE_H_
#define _CBPOLYLINE_H_


/*!
  @file CBPolyline.h
	CBPolyline class definition.
*/

#include "CBDynamicForm.h"
#include "BMacros.h"

// Forward declaration
class CBSVS;

/**
 * @class CBPolyline
 * The CBPolyline class defines a generic dynamic polyline. 
 * Its graphical parameters (color, width) must be defined
 * in the graphique chart according to its Class ID.
 * @since v1.5
 * @note See CBFleetMgr::CreatePolyline method for CBPolyline construction.
 */
class BFLT_EXPORT CBPolyline : public CBDynamicForm
{
protected:

  /**
   * Constructor
   */
  CBPolyline (CBSVS * inSvs, TBuint32 inClassID, const TB_EXTERN_OBJECT & inExtObj)
    : CBDynamicForm(inSvs, inClassID, inExtObj) {
    B_ASSERT (inExtObj.geo.type == EB_GEOTYPE_OPEN);
  }
    
  /**
   * Default Constructor (Not implemented)
   */
  CBPolyline(void);

  /**
   * Disable copy
   */
  CBPolyline(const CBPolyline&);
  CBPolyline& operator=(const CBPolyline&);

  /**
   * Destructor
   */
  virtual ~CBPolyline(void) {}

  friend class CBFleetMgr;
};

#endif /* _CBPOLYLINE_H_ */

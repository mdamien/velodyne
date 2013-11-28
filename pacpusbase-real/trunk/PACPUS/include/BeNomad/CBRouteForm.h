/*==========================================================  (-*- C++ -*-)
 *
 * @file CBRouteForm.h
 * 
 * @version  $Id: CBRouteForm.h,v 1.9 2005/02/10 10:14:19 wkunkel Exp $ 
 * 
 * @author  William Kunkel
 *
 * @copyright  (c) 2002-2003 BeNomad S.A.R.L., All Rights Reserved
 *
 * BeNomad confidential file protected by international copyright laws
 * UNAUTHORIZED ACCESS, USE, REPRODUCTION OR DISTRIBUTION IS PROHIBITED.
 *
 *========================================================================*/

#ifndef _CBROUTE_FORM_H_
#define _CBROUTE_FORM_H_

/*!
  @file CBRouteForm.h
	CBRouteForm class definition.
*/

#include "CBPolyline.h"

// Forward declaration
class CBSVS;

/**
 * @class CBRouteForm
 * The CBRouteForm class is composed of one polyline being used to 
 * define a graphical route. Its graphical parameters (color, width) must be defined
 * in the graphique chart according to its Class ID.
 * @note See CBFleetMgr::CreateRoute method for CBRouteForm construction.
 */
class BFLT_EXPORT CBRouteForm : public CBPolyline
{
protected:

  /**
   * Constructor
   */
  CBRouteForm (CBSVS * inSvs, TBuint32 inClassID, const TB_EXTERN_OBJECT & inExtObj)
    : CBPolyline(inSvs, inClassID, inExtObj) {}
    
  /**
   * Default Constructor (Not implemented)
   */
  CBRouteForm(void);

  /**
   * Disable copy
   */
  CBRouteForm(const CBRouteForm&);
  CBRouteForm& operator=(const CBRouteForm&);

  /**
   * Destructor
   */
  virtual ~CBRouteForm(void) {}

  friend class CBFleetMgr;
};

#endif /* _CBROUTE_FORM_H_ */

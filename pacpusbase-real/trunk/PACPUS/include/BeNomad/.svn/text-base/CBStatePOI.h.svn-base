/*==========================================================  (-*- C++ -*-)
 *
 * @file CBStatePOI.h
 * 
 * @version  $Id: CBStatePOI.h,v 1.3 2004/04/08 17:03:09 wkunkel Exp $ 
 * 
 * @author  William Kunkel
 *
 * @copyright  (c) 2002-2004 BeNomad S.A.R.L., All Rights Reserved
 *
 * BeNomad confidential file protected by international copyright laws
 * UNAUTHORIZED ACCESS, USE, REPRODUCTION OR DISTRIBUTION IS PROHIBITED.
 *
 *========================================================================*/

#ifndef _CBSTATE_POI_H_
#define _CBSTATE_POI_H_

/*!
  @file CBStatePOI.h
	CBStatePOI class definition.
*/

#include "CBDynamicPOI.h"

// Attribute associated to the state of the vehicle 
const TBuint16 KB_STATE_ATTCODE   = 3; 
const TBuint8  KB_UNDEFINED_STATE = 0;

/**
 * @class CBStatePOI
 * The CBStatePOI class is used to represent a state POI. Its representation depends on
 * its category (Class ID) and its current state. Before creating a series of state POIs,
 * you must define its category, its various states as well as the mapping between each
 * state and an image (see CBFleetMgr::AddCategory and CBFleetMgr::AddState).
 * @note Although the representation of the state POIs do not depend directly on the graphic chart
 * to establish the mapping seen previously, you must nevertheless define a default style for the 
 * corresponding Class ID in the graphic chart.
 */
class BFLT_EXPORT CBStatePOI : public CBDynamicPOI
{
public:
  
  /**
   * Returns the current POI's state.
   * @return the current POI's state.
   */
  TBuint8 GetState (void) const;

  /**
   * Sets the POI's state.
   * @param inState The new state.
   */
  void SetState (TBuint8 inState);

  /**
   * Sets or adds an attribute value.
   * @param inAtt The stucture that contains attribute data.
   * @return \c false, if there is already an attribute with the same code 
   * but with a different type.
   */
  TBbool SetAttribute (const TB_ATTRIBUTE & inAtt);

  /**
   * Returns \c true.
   */
  TBbool IsStatePOI(void) const { return true; }

protected:
  /**
   * Default Constructor (Not implemented)
   */
  CBStatePOI (void);

  /**
   * Constructor
   */
  CBStatePOI (CBSVS                  * inSvs,
              TBuint32                 inClassID,             
              const TB_EXTERN_OBJECT & inExtObj);
    
  /**
   * Destructor
   */
  virtual ~CBStatePOI (void) {}

  /**
   * Disable copy
   */
  CBStatePOI (const CBStatePOI&);
  CBStatePOI & operator=(const CBStatePOI&);

  friend class CBFleetMgr;
};

#endif /* _CBSTATE_POI_H_ */

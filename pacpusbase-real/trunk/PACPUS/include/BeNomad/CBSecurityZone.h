/*==========================================================  (-*- C++ -*-)
 *
 * @file CBSecurityZone.h
 * 
 * @version  $Id: CBSecurityZone.h,v 1.15 2005/04/12 14:01:36 wkunkel Exp $ 
 * 
 * @author  William Kunkel
 *
 * @copyright  (c) 2002-2003 BeNomad S.A.R.L., All Rights Reserved
 *
 * BeNomad confidential file protected by international copyright laws
 * UNAUTHORIZED ACCESS, USE, REPRODUCTION OR DISTRIBUTION IS PROHIBITED.
 *
 *========================================================================*/

#ifndef _CBSECURITY_ZONE_H_
#define _CBSECURITY_ZONE_H_

/*!
  @file CBSecurityZone.h
	CBSecurityZone class definition.
*/

#include "CBDynamicForm.h"

// Forward declaration
class CBSVS;
class CBForm2D;


/**
 * @class CBSecurityZone
 * The CBSecurityZone class is composed of one or more polygons being used to 
 * define a geographical area in which you can check if an arbitrary point is inside
 * this zone or not (see #Contains). It is a very useful class for the management of alarms 
 * relating to the position of vehicles or another POIs.
 * @note See CBFleetMgr::CreateSecurityZone method for CBSecurityZone construction.
 */
class BFLT_EXPORT CBSecurityZone : public CBDynamicForm
{
public:

  /**
   * Returns the associated transparent color.
   * @return The RGB transparent color.
   */
  inline TBuint32 GetTansparentColor(void) const { return mTansparentColor; }

  /**
   * Sets the transparent color of the security zone.
   * @param inColor The new transparent color.
   */
  inline void SetTransparentColor(TBuint32 inColor) { mTansparentColor = inColor; }

  /**
   * Check whether the given point is inside the security zone or not.
   * @return \c true, if the point is contained, \c false otherwise.
   */
  TBbool Contains (const TB_2D_LONGPOINT & inPt);

protected:

  /**
   * Constructor
   */
  CBSecurityZone (CBSVS                  * inSvs,
                  TBuint32                 inClassID,               
                  const TB_EXTERN_OBJECT & inExtObj,
                  TBuint32                 inTransparentClr = 0xC8C8C8);

  /**
   * Constructor
   * @since v1.5
   */
  CBSecurityZone (CBSVS     * inSvs,
                  TBuint32    inClassID,               
                  CBForm2D  * inForm,
                  TBuint32    inTransparentClr = 0xC8C8C8);


  /**
   * Default Constructor (Not implemented)
   */
  CBSecurityZone(void);

  /**
   * Disable copy
   */
  CBSecurityZone(const CBSecurityZone&);
  CBSecurityZone& operator=(const CBSecurityZone&);

   /**
   * Destructor
   */
  virtual ~CBSecurityZone(void) {}

private:

  TBuint32  mTansparentColor; // RGB color value

  friend class CBFleetMgr;
};

#endif /* _CBSECURITY_ZONE_H_ */


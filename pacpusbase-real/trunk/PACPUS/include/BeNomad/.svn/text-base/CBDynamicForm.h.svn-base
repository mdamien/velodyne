/*==========================================================  (-*- C++ -*-)
 *
 * @file CBDynamicForm.h
 * 
 * @version  $Id: CBDynamicForm.h,v 1.18 2005/04/12 14:01:36 wkunkel Exp $ 
 * 
 * @author  William Kunkel
 *
 * @copyright  (c) 2002-2003 BeNomad S.A.R.L., All Rights Reserved
 *
 * BeNomad confidential file protected by international copyright laws
 * UNAUTHORIZED ACCESS, USE, REPRODUCTION OR DISTRIBUTION IS PROHIBITED.
 *
 *========================================================================*/

#ifndef _CBDYNAMIC_FORM_H_
#define _CBDYNAMIC_FORM_H_

/*!
  @file CBDynamicForm.h
	CBDynamicForm class definition.
*/

#include "BTypes.h"

// Forward declarations
class CBForm;
class CBSVS;

/**
 * @class CBDynamicForm
 * This class represents the base class for all dynamic forms handled by
 * the #CBFleetMgr class.
 * Dynamic forms are in-memory geometric forms to which a set of attributes
 * may be attached.
 * @note Each dynamic form created by a CBFleetMgr contains a special attribute
 * that keeps a reference to itself (i.e. a pointer to a CBDynamicForm object)
 * (Attribute code : #KB_ATT_SELF_REF, type : #EB_ATTTYPE_USER_ANY)
 */
class BFLT_EXPORT CBDynamicForm
{
public:

  /**
   * \typedef BOnFormDeletionCbk
   * Defines the prototype of a callback that may be called on dynamic form deletion.
   * @param inDynForm The dynamic form which is about to be destroyed.
   */
  typedef void (*BOnFormDeletionCbk) (CBDynamicForm * inDynForm);

  /**
   * Constructs a new dynamic form from an external object description.
   * @param inSvs The #CBSVS object in which the form must be added.
   * @param inClassID The Class ID in which the form must be added.
   * @param inExtObj An external object representation.
   */
  CBDynamicForm (CBSVS                  * inSvs,
                 TBuint32                 inClassID,
                 const TB_EXTERN_OBJECT & inExtObj);
  /**
   * Destroys this form and its attributes.
   */
  virtual ~CBDynamicForm (void);

  /**
   * Returns the associated Class ID of which this dynamic form belongs to.
   * @return The associated Class ID of which this dynamic form belongs to.
   */
  TBuint32 GetClassID (void) const { return mClassID; }

  /**
   * Returns The number of associated attributes.
   * @return The number of associated attributes.
   */
  TBuint16 GetNbAtt (void) const;

  /***
   * Retrieves the attribute stored at the specified index.
   * @param inIndex The index of the attribute to retrieve.
   * @param outAtt Contains the attribute's data.
   * @return \c true if the given index is not out of bounds, false otherwise.
   */
  TBbool GetAttributeByIndex (TBuint16 inIndex, TB_ATTRIBUTE & outAtt) const;

  /**
   * Gets the attribute's value depending on its code (ioAtt.code).
   * @param ioAtt The stucture that contains attibute data.
   * @return \c false, if there is no attribute that matches the given code.
   */
  TBbool GetAttribute (TB_ATTRIBUTE & ioAtt) const;

  /**
   * Sets or adds a new attribute.
   * @param inAtt The stucture that contains attribute data.
   * @return \c false, if there is already an attribute with the same code 
   * but with a different type.
   */
  virtual TBbool SetAttribute (const TB_ATTRIBUTE & inAtt);

  /** 
   * Indicates whether this dynamic form is visible.
   * @return \c true if the this dynamic form is visible, \c false otherwise.
   */
  inline TBbool IsVisible (void) const { return (mFlags & VISIBLE) != 0; }

  /**
   * Changes the visibility state of this dynamic form.
   * @param inFlag The visibility flag.
   */
  inline void SetVisibility (TBbool inFlag) { inFlag ? mFlags |= VISIBLE : mFlags &= ~(VISIBLE); }

  /** 
   * Checks whether this dynamic form is marked as selected or not.
   * @return \c true if the this dynamic form is selected, \c false otherwise.
   */
  inline TBbool IsSelected (void) const { return (mFlags & SELECTED) != 0; }

  /**
   * Changes the selection state of this dynamic form.
   * @param inFlag The flag selection.
   */
  inline void Select (TBbool inFlag) { inFlag ? mFlags |= SELECTED : mFlags &= ~(SELECTED); }

  /**
   * Returns the color selection.
   * @return The RGB color of selection.
   */
  inline TBuint32 GetColorSelection (void) const { return mColorSelection; }

  /**
   * Sets the color selection.
   * @param inColor The RGB code of the new color selection.
   */
  inline void SetColorSection (TBuint32 inColor) { mColorSelection = inColor; }

  /**
   * Returns the internal dynamic form representation
   * @return The internal dynamic form representation
   */
  inline CBForm * GetForm (void) const { return mForm; }

  /**
   * Indicates if this form represents a state POI(see #CBStatePOI).
   * @return \c true if this form represents a state POI.
   */
  virtual TBbool IsStatePOI(void) const { return false; }

  /**
   * Sets a user-defined callback which will be applied on this form before deletion
   * (i.e usage : to release special attribute resources)
   * @param inFunc The callback to apply on this form.
   */
  inline void SetOnDeletionCbk (BOnFormDeletionCbk inFunc) { mOnDelCbk = inFunc; }

  /**
   * Returns an optional user defined data.
   */
  inline TBany GetUserData(void) { return mUserData; }

  /**
   * Sets an optional user defined data.
   */
  inline void SetUserData(TBany data) { mUserData = data; }

protected:

  /**
   * Default Constructor (Not implemented)
   */
  CBDynamicForm (void); 

  /**
   * Disable copy
   */
  CBDynamicForm (const CBDynamicForm&);
  CBDynamicForm & operator=(const CBDynamicForm&);

  /**
   * \internal
   */
  CBDynamicForm(CBSVS * inSvs, TBuint32 inClassID, CBForm * inForm);

protected:

  enum EB_FLAGS { 
    VISIBLE  = 1,  
    SELECTED = 2,
    LABEL_VISIBILITY = 4, // POIs only
  };

  TBuint8            mFlags;
  TBuint32           mClassID;
  TBuint32           mColorSelection;
  CBSVS            * mSvs;
  CBForm           * mForm;
  BOnFormDeletionCbk mOnDelCbk;
  TBany              mUserData;
};


#endif /* _CBDYNAMIC_FROM_H_ */



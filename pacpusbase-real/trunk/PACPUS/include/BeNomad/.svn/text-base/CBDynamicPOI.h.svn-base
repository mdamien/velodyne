/*==========================================================  (-*- C++ -*-)
 *
 * @file CBDynamicPOI.h
 * 
 * @version  $Id: CBDynamicPOI.h,v 1.13 2004/03/20 17:30:47 wkunkel Exp $ 
 * 
 * @author  William Kunkel
 *
 * @copyright  (c) 2002-2003 BeNomad S.A.R.L., All Rights Reserved
 *
 * BeNomad confidential file protected by international copyright laws
 * UNAUTHORIZED ACCESS, USE, REPRODUCTION OR DISTRIBUTION IS PROHIBITED.
 *
 *========================================================================*/

#ifndef _CBDYNAMIC_POI_H_
#define _CBDYNAMIC_POI_H_

/*!
  @file CBDynamicPOI.h
	CBDynamicPOI class definition.
*/

#include "CBDynamicForm.h"

// Forward declarations
class CBSVS;

/**
 * @class CBDynamicPOI
 * The CBDynamicPOI class allows you to create customisable Points Of Interest which 
 * can be displayed on a cartographic support according to an x and y coordinates. 
 * The graphique representation of a CBDynamicPOI object is generally a small image (bitmap) 
 * and depends on the following factors :
 *   - The Class ID to which this object belongs to
 *   - The style associated with this Class ID in a graphic chart (see #CBGraphicChart)
 *   - The graphic chart used to parameterize all rendering operations in a view (see #CBView).
 *
 * @note If you forget to define a style for the corresponding Class ID, 
 * all the POIs of this class will remain invisible.
 *
 * In addition, this class provides a tooltip mechanism for displaying additional informations
 * (i.e. name of the POI, ...).
 */
class BFLT_EXPORT CBDynamicPOI : public CBDynamicForm
{
public:

  /**
   * Returns the position of the POI.
   * @param outGeoPt The returned position.
   */
  void GetPosition (TB_2D_LONGPOINT & outGeoPt) const;

  /**
   * Modifies the position of the POI.
   * @param inGeoPt The new position of the POI.
   */
  void SetPosition (const TB_2D_LONGPOINT & inGeoPt);
  
  /** 
   * @name Tooltip related methods.
   * The following methods allow you to display a multiline label under the POI
   * as a tooltip. Tooltip's background and foreground colors are also customisable.
   * @note Caller is responsible for destroying the label. That can be done by setting 
   * a deletion callback (see CBDynamicForm::SetOnDeletionCbk).
   */
  //@{
  /**
   * Assigns a multiline label to this POI.
   * @note A carriage return-linefeed sequence breaks the line.
   * @note Set the \c null value to hide the tooltip.
   * @param inLabel The label to display.
   */
  inline void SetLabel (TBint8 * inLabel) { mLabel = inLabel; }

  /**
   * Sets the tooltip's foreground color (or text color).
   * (default is black)
   * @param inColor A RGB color value. 
   */
  inline void SetLabelForeground (TBuint32 inColor) { mLabelForeground = inColor; }

  /**
   * Sets the tooltip's background color (default is white)
   * @param inColor A RGB color value.
   * @note The 0xFF000000 value specifies a transparent tooltip.
   */
  inline void SetLabelBackground (TBuint32 inColor) { mLabelBackground = inColor; }

  /**
   * Returns the tooltip's label.
   * @return The tooltip's label or \c null.
   */
  inline TBint8 * GetLabel (void) const { return mLabel; }

  /**
   * Returns the tooltip's foreground color.
   * @return The tooltip's foreground color.
   */
  inline TBuint32 GetLabelForeground (void) const { return mLabelForeground; }

  /**
   * Returns the tooltip's background color.
   * @return The tooltip's background color.
   */
  inline TBuint32 GetLabelBackground (void) const { return mLabelBackground; }

  /**
   * Sets the visiblility of the tooltip's label.
   * @param inFlag The flag visibility.
   */
  inline void SetLabelVisibility (TBbool inFlag) { inFlag ? mFlags |= LABEL_VISIBILITY : mFlags &= ~(LABEL_VISIBILITY); }

   /** 
   * Checks whether the tooltip's label is visible.
   * @return \c true if the tooltip's label is visible, \c false otherwise.
   */
  inline TBbool GetLabelVisibility (void) const { return (mFlags & LABEL_VISIBILITY) != 0; }

  //@}
protected:

  /**
   * Constructor
   */
  CBDynamicPOI (CBSVS * inSvs, TBuint32 inClassID, const TB_EXTERN_OBJECT & inExtObj);

  /**
   * Default Constructor (Not implemented)
   */
  CBDynamicPOI (void); 

  /**
   * Disable copy
   */
  CBDynamicPOI (const CBDynamicPOI&);
  CBDynamicPOI & operator=(const CBDynamicPOI&);

  /**
   * Destructor
   */
  virtual ~CBDynamicPOI (void) {}

private:

  TBint8  * mLabel;           // An optional label
  TBuint32  mLabelBackground; //(RGB color value)
  TBuint32  mLabelForeground; //(RGB color value)

  friend class CBFleetMgr;
};

#endif /* _CBDYNAMIC_POI_H_ */

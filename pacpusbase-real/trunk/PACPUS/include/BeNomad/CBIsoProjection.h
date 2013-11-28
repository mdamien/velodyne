/*==========================================================  (-*- C++ -*-)
 *
 * @file CBIsoProjection.h
 *
 * @version  $Id: CBIsoProjection.h,v 1.22 2006/03/02 14:54:10 dlabrousse Exp $
 * 
 * @author  David Labrousse
 *
 * @copyright  (c) 2002-2003 BeNomad S.A.R.L., All Rights Reserved
 *
 * BeNomad confidential file protected by international copyright laws
 * UNAUTHORIZED ACCESS, USE, REPRODUCTION OR DISTRIBUTION IS PROHIBITED.
 *
 *========================================================================*/

#ifndef __CBISOPROJECTION_H__
#define __CBISOPROJECTION_H__

/*!
  @file CBIsoProjection.h
	CBIsoProjection class definition.
*/

#include "CBProjection.h"

/**
 * @class CBIsoProjection
 *
 * @brief This class defines projection of points in 'real' coordinates
 * into screen coordinates.
 *
 * CBIsoProjection is a class that defines \e homothetic projection of points in 
 * real coordinates (the coordinates used to define geometry of SVS objects) into 
 * screen coordinates. If you use this class for screen projection, you assume that
 * the SVS coordinate system is such that homothetic projection is suitable (which is
 * not the case when the SVS coordinate system is of type longitude/lattitude !).
 */
class BSVS_EXPORT CBIsoProjection : public CBProjection
{
public:

	/**
	 * Constructor.
	 * @param inDeltaX Screen size in x direction
	 * @param inDeltaY Screen size in y direction
	 */
  CBIsoProjection(TBint16 inDeltaX,
                  TBint16 inDeltaY);

	/**
	 * Destructor.
	 */
  ~CBIsoProjection();

	/**
	 * Is #CBIsoProjection a #CBGeoProjection ? No !
	 * @return \c false
	 */
	TBbool IsGeoProjection(void) const
  {
    return false;
  }

	/**
	 * Sets projection parameters so that #mScale = \a inScale.
	 * @note
	 * \arg #mFactor cannot be smaller than #mInitFactor. If this should happen, #mFactor
	 * is set to #mInitFactor and other projection parameters are changed in consequence.
	 * \arg #mScale cannot be smaller than 0.2. If this should happen, #mScale
	 * is set to 0.2 and other projection parameters are changed in consequence.
	 * @param inScale New value of #mScale
	 */
  void Zoom(TBfloat inScale);

	/**
	 * Sets projection parameters so that #mScale = \a inScale and #mRealRect is centered on \a inPoint.
	 * @note
	 * \arg #mFactor cannot be smaller than #mInitFactor. If this should happen, #mFactor
	 * is set to #mInitFactor and other projection parameters are changed in consequence.
	 * \arg #mScale cannot be smaller than 0.2. If this should happen, #mScale
	 * is set to 0.2 and other projection parameters are changed in consequence.
	 * @param inScale New value of #mScale
	 * @param inPoint Real (SVS coordinate system) coordinate point to center view on
	 */
  void Zoom(TBfloat                inScale,
            const TB_2D_LONGPOINT& inPoint);

	/**
	 * Sets projection parameters so that #mScale = \a inScale and #mRealRect is centered on \a inPoint.
	 * @note 
	 * \arg #mFactor cannot be smaller than #mInitFactor. If this should happen, #mFactor
	 * is set to #mInitFactor and other projection parameters are changed in consequence.
	 * \arg #mScale cannot be smaller than 0.2. If this should happen, #mScale
	 * is set to 0.2 and other projection parameters are changed in consequence.
	 * @param inScale New value of #mScale
	 * @param inPoint Real (SVS coordinate system) coordinate point (double precision) to center view on
   * @since v1.8.0 creation
	 */
  virtual void Zoom(TBfloat               inScale,
                    const TB_2D_DBLPOINT& inPoint);
	/**
	 * Sets projection parameters so that #mScale = \a inScale and view is centered on screen point \a inPoint.
	 * @note 
	 * \arg #mFactor cannot be smaller than #mInitFactor. If this should happen, #mFactor
	 * is set to #mInitFactor and other projection parameters are changed in consequence.
	 * \arg #mScale cannot be smaller than 0.2. If this should happen, #mScale
	 * is set to 0.2 and other projection parameters are changed in consequence.
	 * @param inScale New value of #mScale
	 * @param inPoint Screen coordinates point to center view on
	 * @return \c true
	 */
  TBbool Zoom(TBfloat            inScale,
									    const TB_2D_POINT& inPoint);

	/**
	 * Sets projection parameters so that \a inScreenRect, given in screen coordinates
	 * will become new limits of all visible SVS objects.
	 * @param inScreenRect Screen rectangular limits of SVS objects to project on screen
	 * @return \c true
	 */
  TBbool ZoomIn(const TB_2D_RECT& inScreenRect);

	/**
	 * Sets projection parameters so that \a inRealRect, given in real (SVS coordinate system) coordinates
	 * will be limits of visible SVS objects when projected.
	 * @param inRealRect SVS rectangular limits of SVS objects to project on screen
	 */
  void ZoomIn(const TB_2D_LONGRECT& inRealRect);

	/**
	 * Sets projection parameters so that #mScale (resp #mFactor) becomes twice 
	 * (resp half) its current value.
	 * @note #mFactor cannot be smaller than #mInitFactor. If this should happen, #mFactor
	 * is set to #mInitFactor and other projection parameters are changed in consequence.
	 */
  void ZoomOut(void);

	/**
	 * Sets projection parameters to initial parameters (set when #SetInitialRealRect is called).
	 */
  void ZoomInitial(void);

	/**
	 * Sets projection parameters so that view is translated by a vector defined by screen points \a inPt1 and \a inPt2.
	 * @param inPt1 First screen coordinate point
 	 * @param inPt2 Second screen coordinate point.
	 * @return \c true
	 */
  TBbool Move(const TB_2D_POINT& inPt1,
											const TB_2D_POINT& inPt2);

	/**
	 * Computes screen projection of a real (SVS coordinate system) 2D point.
	 * @param inRealPoint Real coordinate 2D point
	 * @param outPoint Screen point = projection of \a inRealPoint on screen
	 * @return \c true
	 */
  TBbool Project(const TB_2D_LONGPOINT& inRealPoint,
                         TB_2D_LONGPOINT&       outPoint) const;

	/**
	 * Computes real (SVS coordinate system) coordinates of a screen point.
	 * @param inScreenPoint Screen point
	 * @param outPoint Real (SVS coordinate system) point
	 * @return \c true
	 */
  TBbool DeProject(const TB_2D_POINT& inScreenPoint,
                   TB_2D_LONGPOINT&   outPoint) const;

	/**
	 * Computes real (SVS coordinate system) coordinates of a screen point.
	 * @param inScreenPoint Screen point
	 * @param outPoint Real (SVS coordinate system) point
	 * @return \c true
	 */
  TBbool DeProject(const TB_2D_POINT& inScreenPoint,
                   TB_2D_DBLPOINT&    outPoint) const;

	/**
	 * Returns euclidian real distance between screen points \a inPt1 and \a inPt2.
	 * @note Distance is given in SVS unit.
	 * @return Distance in SVS unit between screen points \a inPt1 and \a inPt2
	 */
  TBfloat GetDist(const TB_2D_POINT& inPt1,
                          const TB_2D_POINT& inPt2) const;

	/**
	 * Returns euclidian real distance between real (SVS coordinate system) points \a inPt1 and \a inPt2.
	 * @note Distance is given in SVS unit.
	 * @return Distance in SVS unit between real points \a inPt1 and \a inPt2
	 */
  TBfloat GetDist(const TB_2D_LONGPOINT& inPt1,
                          const TB_2D_LONGPOINT& inPt2) const;

	/**
	 * Returns clockwise oriented angle (in degrees) between line (\a inPt1, \a inPt2)
	 * and vertical.
	 * @return Angle in degrees
	 */
	TBint16 GetAngle(const TB_2D_LONGPOINT& inPt1,
													 const TB_2D_LONGPOINT& inPt2) const;

	/**
	 * Converts a "real" distance into a "view" distance. Useful for drawing scale information.
	 * @note \a inDist is assumed to be given in SVS units
   * Conversion is valid for view's center point
	 * @param inDist The "real" distance
   * @return "view" distance
	 */
  TBdouble DistToPixels(TBdouble inDist) const;

protected:

  void Init(void);

// private:

  void SetRealRect(void);
};

#endif // __CBISOPROJECTION_H__

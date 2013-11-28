/*==========================================================  (-*- C++ -*-)
 *
 * @file CBGeoProjection.h
 *
 * @version  $Id: CBGeoProjection.h,v 1.37 2006/03/02 14:54:10 dlabrousse Exp $ 
 * 
 * @author  David Labrousse
 *
 * @copyright  (c) 2002-2003 BeNomad S.A.R.L., All Rights Reserved
 *
 * BeNomad confidential file protected by international copyright laws
 * UNAUTHORIZED ACCESS, USE, REPRODUCTION OR DISTRIBUTION IS PROHIBITED.
 *
 *========================================================================*/

#ifndef __CBGEOPROJECTION_H__
#define __CBGEOPROJECTION_H__

/*!
  @file CBGeoProjection.h
	CBGeoProjection class definition and constants for orthographic projection.
*/

#include "CBProjection.h"

#if defined(_WIN32_WCE)
# if !defined(_BEMBEDDED_OPTIM)
#   define _BEMBEDDED_OPTIM
# endif
#endif

#if defined(_BEMBEDDED_OPTIM)
# define _BFORCE_SIMPLIFY_XY
#endif

#if !defined(_BFORCE_SIMPLIFY_XY)
# define GEO_DEFAULT_THRESHOLD_X 15  //!< Threshold on longitude for projection approximation in x (see #CBGeoProjection).
# define GEO_DEFAULT_THRESHOLD_Y 10  //!< Threshold on latitude for projection approximation in y (see #CBGeoProjection).
#endif

#define GEO_MAX_SCALE 10000000UL    //!< Max value for number of SVS units per degree

/**
 * @class CBGeoProjection
 *
 * This class defines projection of points in longitude/lattitude coordinates into screen coordinates.
 *
 * CBGeoProjection is a class that defines \e orthographic projection of points in 
 * longitude/lattitude coordinates into screen coordinates. If you use this class for screen projection,
 * you assume that the SVS coordinate system is of type longitude/lattitude. If it is not the case,
 * or if you are not sure, do not use this class !!
 *
 * @note For calculus simplification a threshold on x (resp y) size of #mRealRect can be
 * defined in CBGeoProjection's constructor. Default values are #GEO_DEFAULT_THRESHOLD_X (resp #GEO_DEFAULT_THRESHOLD_Y).
 */
class BSVS_EXPORT CBGeoProjection : public CBProjection
{
 private:

#if !defined(_BFORCE_SIMPLIFY_XY)
  TBbool          mOverlap;
  TBbool          mInitialSimplifyX;
  TBbool          mSimplifyX;
  TBbool          mSimplifyY;
  TBint8          mThresholdX;
  TBint8          mThresholdY;
  TBint32         mSimplifyThresoldX;
  TBint32         mSimplifyThresoldY;
#endif
	TBuint32        mCoordScale;
  TBfloat         mCosY0;
  TBfloat         mSinY0;
  TBfloat         mFactorX;
  TBfloat         mK;
  TBint32         m2PI;
  TBint32         mPI;
  TBint32         mPI2;
  TBdouble        mConversionFact;

 public:

	/**
	 * Constructor.
	 * @param inDeltaX Screen size in horizontal direction
	 * @param inDeltaY Screen size in vertical direction
	 * @param inCoordScale Number of SVS units per degree (default = 100000)
	 * @param inThresholdX Threshold on longitude size of #mRealRect underneath which projection approximation in x is allowed (default = #GEO_DEFAULT_THRESHOLD_X)
	 * @param inThresholdY Threshold on latitude size of #mRealRect underneath which projection approximation in y is allowed (default = #GEO_DEFAULT_THRESHOLD_Y)
	 * @note \a inCoordScale has to be in range [1, #GEO_MAX_SCALE]
	 */
  CBGeoProjection(TBint16  inDeltaX,
                  TBint16  inDeltaY,
                  TBuint32 inCoordScale = 100000
#if !defined(_BFORCE_SIMPLIFY_XY)
                  ,TBuint8  inThresholdX = GEO_DEFAULT_THRESHOLD_X,
                  TBuint8  inThresholdY = GEO_DEFAULT_THRESHOLD_Y
#endif
                  );

	/**
	 * Destructor.
	 */
  ~CBGeoProjection() {}

	/**
	 * Returns number of SVS units per degree
	 * @return Number of SVS units per degree
	 */
	inline TBuint32 GetCoordScale(void) const { return mCoordScale; }

	/**
	 * Is #CBGeoProjection a #CBGeoProjection ? Yes !
	 * @return \c true
	 */
	TBbool IsGeoProjection(void) const
  {
    return true;
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
	 * @return \c false if \a inPoint has no real coordinates, \c true otherwise
	 */
  TBbool Zoom(TBfloat            inScale,
											const TB_2D_POINT& inPoint);

	/**
	 * Sets projection parameters so that \a inScreenRect, given in screen coordinates
	 * will become new limits of all visible SVS objects.
	 * @param inScreenRect Screen rectangular limits of SVS objects to project on screen
	 * @return \c false if \a inScreenRect has no real coordinates, \c true otherwise
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
	 * @return \c false if either \a inPt1 or \a inPt2 have no equivalent in real (SVS) coordinate system,
	 * \c true otherwise
	 */
  TBbool Move(const TB_2D_POINT& inPt1,
              const TB_2D_POINT& inPt2);

	/**
	 * Computes screen projection of a real (SVS coordinate system) 2D point.
	 * @param inRealPoint Real coordinate 2D point
	 * @param outPoint Screen point = projection of \a inRealPoint on screen
	 * @return \c false if \a inRealPoint 's projection is not visible due to sphere overlapping, \c true otherwise
	 */
  TBbool Project(const TB_2D_LONGPOINT& inRealPoint,
                 TB_2D_LONGPOINT&       outPoint) const;

	/**
	 * Computes real (SVS coordinate system) coordinates of a screen point.
	 * @param inScreenPoint Screen point
	 * @param outPoint Real (SVS coordinate system) point
	 * @return \c false if \a inScreenPoint has no corresponding real coordinate (if projection
	 * scale is big enough, a screen point can be beyond Earth's projection bounds), \c true otherwise
	 */
  TBbool DeProject(const TB_2D_POINT&   inScreenPoint,
                   TB_2D_LONGPOINT&     outPoint) const;

	/**
	 * Computes real (SVS coordinate system) coordinates of a screen point.
	 * @param inScreenPoint Screen point
	 * @param outPoint Real (SVS coordinate system) point
	 * @return \c false if \a inScreenPoint has no corresponding real coordinate (if projection
	 * scale is big enough, a screen point can be beyond Earth's projection bounds), \c true otherwise
	 */
  TBbool DeProject(const TB_2D_POINT&   inScreenPoint,
                   TB_2D_DBLPOINT&      outPoint) const;

	/**
	 * Returns euclidian real distance between screen points \a inPt1 and \a inPt2.
	 * @note Distance is given in meters.
	 * @return Distance in meters between screen points \a inPt1 and \a inPt2
	 */
  TBfloat GetDist(const TB_2D_POINT&     inPt1,
                          const TB_2D_POINT&     inPt2) const;

	/**
	 * Returns euclidian real distance between real (SVS coordinate system) points \a inPt1 and \a inPt2.
	 * @note Distance is given meters.
	 * @return Distance in meters between real points \a inPt1 and \a inPt2
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
	 * @note \a inDist is assumed to be given in meters.
   * Conversion is valid for view's center point
	 * @param inDist The "real" distance
   * @return "view" distance
	 */
  TBdouble DistToPixels(TBdouble inDist) const;

protected:

  void Init(void);

  void SetRealRect(void);

private:

#if 0
  TBint8 GetCos(const TBint32 inAngle) const;

  TBfloat GetRealCos(const TBint32 inAngle) const;

  TBfloat GetRealSin(const TBint32 inAngle) const;
#endif

  inline TBbool IsNorthPoleVisible(void) const
  {
    return !(mP0.y < 0 || (mP0.y != mPI2 && mK > ((TBfloat) mPI2 / (mPI2 - mP0.y)) * (mDeltaY >> 1)));
  }

  inline TBbool IsSouthPoleVisible(void) const
  {
    return !(mP0.y > 0 || (mP0.y != mPI2 && mK > ((TBfloat) mPI2 / (mPI2 + mP0.y)) * (mDeltaY >> 1)));
  }

  inline TBbool IsAPoleVisible(void) const
  {
    return IsNorthPoleVisible() || IsSouthPoleVisible();
  }
};

#endif // __CBGEOPROJECTION_H__

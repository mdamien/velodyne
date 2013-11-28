/*==========================================================  (-*- C++ -*-)
 *
 * @file CBProjection.h
 * 
 * @version  $Id: CBProjection.h,v 1.41 2006/03/06 15:40:40 dlabrousse Exp $ 
 * 
 * @author  David Labrousse
 *
 * @copyright  (c) 2002-2003 BeNomad S.A.R.L., All Rights Reserved
 *
 * BeNomad confidential file protected by international copyright laws
 * UNAUTHORIZED ACCESS, USE, REPRODUCTION OR DISTRIBUTION IS PROHIBITED.
 *
 *========================================================================*/

#ifndef __CBPROJECTION_H__
#define __CBPROJECTION_H__

/*!
  @file CBProjection.h
	CBProjection class definition.
*/

#include "BTypes.h"
#include "BMacros.h"
#include "CBClipZone.h"



#define KB_EARTH_RADIUS 6378137     //!< Earth's radius in meters.

/**
 * @class CBProjection
 *
 * @brief This virtual class defines projection of points in real coordinates
 * (SVS coordinate system) into screen coordinates.
 *
 * CBProjection is an abstract class that defines projection of points in real 
 * coordinates into screen coordinates. Real coordinates are the coordinates 
 * used to define geometry of SVS objects (which can be of any kind of system or scale).
 * Screen coordinates are the coordinates of points on a screen.
 * 
 * Projection of SVS objects on screen is used by rendering module.
 *
 * The screen projection is based on several parameters such as
 * screen dimensions (#mDeltaX, #mDeltaY), projection scale (#mScale), rotation angle
 * around Z axis (#mZAngle) and rotation angle around X axis (#mXAngle).
 *
 * Each time a zoom or a move method is called, the extraction area, defining the geometric
 * limits of the visible area, is updated. The extraction area is defined by #mClipZone.
 * This area is normally a rectangle but it may be any convex quadrilateral if either #mZangle
 * or #mXangle is set to a non zero value.
 *
 * @note #SetInitialRealRect method should be called \e before starting any projection. This 
 * method initializes projection parameters. Before calling this method, #mInitialized is set to \c false
 * and projection parameters are not set.
 */
class BSVS_EXPORT CBProjection
{
protected:

	TBbool          mInitialized;     /**< Set to \c true when #SetInitialRealRect is called */
	TBint16         mMinY;            /**< Internal */
	TBint32         mTrueMinY;        /**< Internal */
	TBint32         mZAngle;          /**< Rotation angle around z axis in degrees */
	TBfloat         mZCos;            /**< Cosinus of #mZAngle */
	TBfloat         mZSin;            /**< Sinus of #mZAngle */
  TBint32         mXAngle;          /**< Rotation angle around x axis in degrees */
	TBfloat         mXCos;            /**< Cosinus of #mXAngle */
	TBfloat         mXCoef;           /**< Internal */
	TBfloat         mXCoefInv;        /**< Internal */
	TBfloat         mXFact;           /**< Internal */
  TBint16         mDeltaX;          /**< Screen size in \c x direction */
  TBint16         mDeltaY;          /**< Screen size in \c y direction */
  TBfloat         mScale;           /**< Projection scale = (#mRealRect .max.y - #mRealRect .min.y) / #mDeltaY */
  TBfloat         mFactor;          /**< Projection factor = 1 / #mScale */
  TBfloat         mInitFactor;      /**< Initial projection factor : Set when #SetInitialRealRect is called */
  TBuint32        mMinObjectSize;   /**< Minimum size of an SVS object under which an object is considered as not visible : #mMinObjectSize = #mScale / 2 */
  TBfloat       * mXFactArray;      /**< Internal */
	TB_2D_LONGPOINT mP0;              /**< Real coordinates of point in center of screen */
	TB_2D_DBLPOINT  mDblP0;           /**< Real coordinates of point in center of screen */
  TB_2D_LONGRECT  mRealRect;        /**< Current projection real rectangle : defines rectangular limits, in SVS coordinate system, of SVS objects to be projected on screen.\n
																	  		 If an object does not belong to #mRealRect, its projection will be out of screen bounds.*/
  TB_2D_LONGRECT  mInitialRealRect; /**< Initial #mRealRect : Set when #SetInitialRealRect is called */
	CBClipZone      mClipZone;        /**< Extraction area */

public:

  enum EB_TYPE { GEO, ISO };

	/**
	 * Constructor.
	 * @param inDeltaX Screen size in x direction
	 * @param inDeltaY Screen size in y direction
	 */
  CBProjection(TBint16 inDeltaX, TBint16 inDeltaY);

	/**
	 * Destructor.
	 */
  virtual ~CBProjection();

  /**
	 * Returns the rotation angle around z axis (#mZAngle).
	 * @return Rotation angle around z axis.
	 */
	inline TBint32 GetZAngle(void) const { return mZAngle; }

	/**
	 * Sets a rotation angle around z axis (#mZAngle).
	 * @param inAngle Rotation angle around z axis in degrees.
	 * @param internal Internal !
	 */
	void SetZAngle(TBint32 inAngle = 0,
								 TBbool  internal = true);

#if defined(_BSIV_LEVEL3)

  /**
	 * Returns the rotation angle around x axis (#mXAngle).
	 * @return Rotation angle around x axis.
	 */
	inline TBint32 GetXAngle(void) const { return mXAngle; }

	/**
	 * Sets a rotation angle around x axis (#mXAngle).
	 * @param inAngle Rotation angle around x axis in degrees.
	 * @param internal Internal !
	 * @note #mXangle is bounded by 0° and 70° which means that 
	 * if \c inAngle is < 0°, #mXAngle will be set to 0° 
	 * and if \c inAngle is > 70°, #mXAngle will be set to 70°
	 */
	void SetXAngle(TBint32 inAngle = 0, TBbool  internal = true);

  /**
   * @since v1.5
	 * Returns the y screen coordinate of the horizon ().
   * @note 0 means that the horizon is not visible which is the case if and only if #mXangle is < 60°
	 * @return The y screen coordinate of the horizon.
	 */
  TBint16 GetHorizonHight(void) const { return mMinY; }

#endif

	/**
	 * @internal
	 * Returns the current extraction area (clipping zone).
	 * @return Extraction area (clipping zone).
	 */
	inline const CBClipZone& GetClipZone(void) const { return mClipZone; }

	/**
	 * Returns \c true if object #CBProjection is a #CBGeoProjection,
	 * \c false otherwise (i.e. object is a #CBIsoProjection).
	 * @return \c true if object #CBProjection is a #CBGeoProjection, \c false otherwise
	 */
	virtual TBbool IsGeoProjection(void) const = 0;

	/**
	 * Resizes screen dimensions.
	 * @param inDeltaX New screen size in x direction
	 * @param inDeltaY New screen size in y direction
	 */
  void Resize(TBint16 inDeltaX, TBint16 inDeltaY);

	/**
	 * Returns size under which an SVS object is smaller than half a pixel when
	 * projected to screen (depends on current value of #mScale). If an SVS object
	 * is smaller than minimal size, it can be considered has not visible at current scale.
	 * @return Size under which an object is smaller than half a pixel
	 */
  inline TBuint32 GetMinObjectSize(void) const
  {
    return mMinObjectSize;
  }

	/**
	 * Returns \c true if object #CBProjection has been initialized,
	 * \c false otherwise (see #SetInitialRealRect).
	 * @return \c true if object #CBProjection has been initialized, \c false otherwise
	 */
	inline TBbool IsInitialized(void)
	{
		return mInitialized;
	}

	/**
	 * Returns current real 2D rectangle : rectangle in real coordinates in which SVS objects
	 * are to be displayed on screen.
	 * @param outRect Current real 2D rectangle
	 */
  inline void GetRealRect(TB_2D_LONGRECT& outRect) const
  {
    outRect = mRealRect;
  }

	/**
	 * Returns current real 3D rectangle : rectangle in real coordinates in which SVS objects
	 * are to be displayed on screen.
	 * @note z component are note taken into account.
	 * @param outRect Current real 3D rectangle
	 */
  inline void GetRealRect(TB_3D_LONGRECT& outRect) const
  {
    outRect.min.x = mRealRect.min.x;
    outRect.min.y = mRealRect.min.y;
    outRect.max.x = mRealRect.max.x;
    outRect.max.y = mRealRect.max.y;
  }

	/**
	 * Returns current real 2D center point of projection.
	 * @return Current real 2D center point of projection
	 */
  inline const TB_2D_LONGPOINT& GetCenterRealPoint(void) const { return mP0; }

	/**
	 * Returns current real 2D center point of projection (in \c double precision).
	 * @return Current real 2D center point of projection
	 */
  inline const TB_2D_DBLPOINT& GetCenterRealDblPoint(void) const { return mDblP0; }

	/**
	 * Sets initial real rectangle. Initial rectangle, given in real coordinates
	 * is used to initialize projection parameters and by #ZoomInitial.
	 * @note #mInitialized is set to \c true.
	 * @param inRect Initial 2D rectangle in real coordinates
	 */
  void SetInitialRealRect(const TB_2D_LONGRECT& inRect);

	/**
	 * Sets initial real rectangle. Initial rectangle, given in real coordinates
	 * is used to initialize projection parameters and by #ZoomInitial.
	 * @note
	 * @arg #mInitialized is set to \c true.
	 * @arg The z components of \a inRect are not taken into account.
	 * @param inRect Initial 3D rectangle in real coordinates
	 */
  void SetInitialRealRect(const TB_3D_LONGRECT& inRect);

	/**
	 * Returns initial real rectangle.
	 * @param outRect Initial real rectangle
	 */
  inline void GetInitialRealRect(TB_2D_LONGRECT& outRect) const
  {
    outRect = mInitialRealRect;
  }

	/**
	 * Returns initial projection factor (see #mInitFactor, #mFactor and #mScale).
	 * @return Initial projection factor
	 */
  inline TBfloat GetInitFactor(void) const
  {
    return mInitFactor;
  }

	/**
	 * Returns current projection factor (see #mInitFactor, #mFactor and #mScale).
	 * @return Current projection factor
	 */
  inline TBfloat GetFactor(void) const
  {
    return mFactor;
  }

	/**
	 * Returns current projection scale (see #mInitFactor, #mFactor and #mScale).
	 * @return Current projection scale
	 */
  inline TBfloat GetScale(void) const
  {
    return mScale;
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
  virtual void Zoom(TBfloat inScale) = 0;

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
  virtual void Zoom(TBfloat                inScale,
                    const TB_2D_LONGPOINT& inPoint) = 0;

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
                    const TB_2D_DBLPOINT& inPoint) = 0;

	/**
	 * Sets projection parameters so that #mScale = \a inScale and view is centered on screen point \a inPoint.
	 * @note 
	 * \arg #mFactor cannot be smaller than #mInitFactor. If this should happen, #mFactor
	 * is set to #mInitFactor and other projection parameters are changed in consequence.
	 * \arg #mScale cannot be smaller than 0.2. If this should happen, #mScale
	 * is set to 0.2 and other projection parameters are changed in consequence.
	 * @param inScale New value of #mScale
	 * @param inPoint Screen coordinates point to center view on
	 * @return \c false if \a inPoint has no real coordinates (only if #CBProjection is a #CBGeoProjection),
	 * \c true otherwise
	 */
  virtual TBbool Zoom(TBfloat            inScale,
									    const TB_2D_POINT& inPoint) = 0;

	/**
	 * Sets projection parameters so that \a inScreenRect, given in screen coordinates
	 * will become new limits of all visible SVS objects.
	 * @param inScreenRect Screen rectangular limits of SVS objects to project on screen
	 * @return \c false if \a inScreenRect has no real coordinates (only if #CBProjection is a #CBGeoProjection),
	 * \c true otherwise
	 */
  virtual TBbool ZoomIn(const TB_2D_RECT& inScreenRect) = 0;

	/**
	 * Sets projection parameters so that \a inRealRect, given in real (SVS coordinate system) coordinates
	 * will be limits of visible SVS objects when projected.
	 * @param inRealRect SVS rectangular limits of SVS objects to project on screen
	 */
  virtual void ZoomIn(const TB_2D_LONGRECT& inRealRect) = 0;

	/**
	 * Sets projection parameters so that #mScale (resp #mFactor) becomes twice 
	 * (resp half) its current value.
	 * @note #mFactor cannot be smaller than #mInitFactor. If this should happen, #mFactor
	 * is set to #mInitFactor and other projection parameters are changed in consequence.
	 */
  virtual void ZoomOut(void) = 0;

	/**
	 * Sets projection parameters to initial parameters (set when #SetInitialRealRect is called).
	 */
  virtual void ZoomInitial(void) = 0;

	/**
	 * Sets projection parameters so that view is translated by a vector defined by screen points \a inPt1 and \a inPt2.
	 * @param inPt1 First screen coordinate point
 	 * @param inPt2 Second screen coordinate point.
	 * @return \c false if either \a inPt1 or \a inPt2 have no equivalent in real (SVS) coordinate system (only if #CBProjection is a #CBGeoProjection),
	 * \c true otherwise
	 */
  virtual TBbool Move(const TB_2D_POINT& inPt1,
											const TB_2D_POINT& inPt2) = 0;

	/**
	 * Computes screen projection of a real (SVS coordinate system) 2D point.
	 * @param inRealPoint Real coordinate 2D point
	 * @param outPoint Screen point = projection of \a inRealPoint on screen
	 * @return \c false if \a inRealPoint 's projection is not visible (only if #CBProjection is a #CBGeoProjection),
	 * \c true otherwise
	 */
  virtual TBbool Project(const TB_2D_LONGPOINT& inRealPoint,
                         TB_2D_LONGPOINT&       outPoint) const = 0;

	/**
	 * Computes screen projection of a real (SVS coordinate system) 3D point.
	 * @note The z component of \a inRealPoint is not taken into account.
	 * @param inRealPoint Real coordinate 3D point
	 * @param outPoint Screen point = projection of \a inRealPoint on screen
	 * @return \c false if \a inRealPoint 's projection is not visible (only if #CBProjection is a #CBGeoProjection),
	 * \c true otherwise
	 */
  TBbool Project(const TB_3D_LONGPOINT& inRealPoint,
								 TB_2D_LONGPOINT&       outPoint) const;

	/**
	 * Computes screen projection of a real (SVS coordinate system) 2D rectangle.
	 * @param inRealRect Real coordinate 2D rectangle
	 * @param outRect Screen rectangle = projection of \a inRealRect on screen
	 * @return \c false if \a inRealRect 's projection is not visible (only if #CBProjection is a #CBGeoProjection),
	 * \c true otherwise
	 */
  TBbool Project(const TB_2D_LONGRECT& inRealRect,
								 TB_2D_LONGRECT&       outRect) const;

	/**
	 * Computes screen projection of a real (SVS coordinate system) 3D rectangle.
	 * @note The z components of \a inRealRect are not taken into account.
	 * @param inRealRect Real coordinate 3D rectangle
	 * @param outRect Screen rectangle = projection of \a inRealRect on screen
	 * @return \c false if \a inRealRect 's projection is not visible (only if #CBProjection is a #CBGeoProjection),
	 * \c true otherwise
	 */
  TBbool Project(const TB_3D_LONGRECT& inRealRect,
								 TB_2D_LONGRECT&       outRect) const;

	/**
	 * Computes real (SVS coordinate system) coordinates of a screen point.
	 * @param inScreenPoint Screen point
	 * @param outPoint Real (SVS coordinate system) point
	 * @return \c false if \a inScreenPoint has no real coordinates (only if #CBProjection is a #CBGeoProjection),
	 * \c true otherwise
	 */
  virtual TBbool DeProject(const TB_2D_POINT& inScreenPoint,
                           TB_2D_LONGPOINT&   outPoint) const = 0;

	/**
	 * Computes real (SVS coordinate system) coordinates of a screen point.
	 * @param inScreenPoint Screen point
	 * @param outPoint Real (SVS coordinate system) point
	 * @return \c true
	 */
  virtual TBbool DeProject(const TB_2D_POINT& inScreenPoint,
                           TB_2D_DBLPOINT&    outPoint) const = 0;
	/**
	 * Computes real (SVS coordinate system) coordinates of a screen rectangle.
	 * @param inScreenRect Screen rectangle
	 * @param outRect Real (SVS coordinate system) rectangle
	 * @return \c false if \a inScreenRect has no real coordinates (only if #CBProjection is a #CBGeoProjection),
	 * \c true otherwise
	 */
  TBbool DeProject(const TB_2D_RECT& inScreenRect,
									 TB_2D_LONGRECT&   outRect) const;

	/**
	 * Returns euclidian real distance between screen points \a inPt1 and \a inPt2.
	 * @note If #CBProjection is a #CBIsoProjection, distance is given in SVS unit.
	 * If #CBProjection is a #CBGeoProjection, distance is given in meters.
	 * @param inPt1 First point
	 * @param inPt2 Second point
	 * @return Distance between screen points \a inPt1 and \a inPt2
	 */
  virtual TBfloat GetDist(const TB_2D_POINT& inPt1,
                          const TB_2D_POINT& inPt2) const = 0;

	/**
	 * Returns euclidian real distance between real (SVS coordinate system) points \a inPt1 and \a inPt2.
	 * @note If #CBProjection is a #CBIsoProjection, distance is given in SVS unit.
	 * If #CBProjection is a #CBGeoProjection, distance is given in meters.
	 * @param inPt1 First point
	 * @param inPt2 Second point
	 * @return Distance between real points \a inPt1 and \a inPt2
	 */
  virtual TBfloat GetDist(const TB_2D_LONGPOINT& inPt1,
                          const TB_2D_LONGPOINT& inPt2) const = 0;

	/**
	 * Returns clockwise oriented angle (in degrees) between line (\a inPt1, \a inPt2) and vertical.
	 * @param inPt1 First point
	 * @param inPt2 Second point
	 * @return Angle in degrees
	 */
	virtual TBint16 GetAngle(const TB_2D_LONGPOINT& inPt1,
													 const TB_2D_LONGPOINT& inPt2) const = 0;

	/**
	 * Returns euclidian real distance between real (SVS coordinate system) points \a inPt1 and \a inPt2.
	 * @note If \a inGeoScale = 0, distance is given in SVS unit.
	 * If a inGeoScale != 0, distance is given in meters.
	 * @param inPt1 First point
	 * @param inPt2 Second point
	 * @param inGeoScale Scale for long/lat coordinate system : number of units per degree (set to 0 if not long/lat coordinates)
	 * @return Distance between real points \a inPt1 and \a inPt2
	 */
  static TBdouble GetDist(const TB_2D_LONGPOINT& inPt1,
                          const TB_2D_LONGPOINT& inPt2,
                          TBuint32               inGeoScale);

	/**
	 * Returns euclidian real distance between real (SVS coordinate system) points \a inPt1 and \a inPt2.
	 * @note If \a inGeoScale = 0, distance is given in SVS unit.
	 * If a inGeoScale != 0, distance is given in meters.
	 * @param inPt1 First point (\c double precision)
	 * @param inPt2 Second point
	 * @param inGeoScale Scale for long/lat coordinate system : number of units per degree (set to 0 if not long/lat coordinates)
	 * @return Distance between real points \a inPt1 and \a inPt2
	 */
  static TBdouble GetDist(const TB_2D_DBLPOINT&  inPt1,
                          const TB_2D_LONGPOINT& inPt2,
                          TBuint32               inGeoScale);

	/**
	 * Returns euclidian real distance between real (SVS coordinate system) points \a inPt1 and \a inPt2.
	 * @note If \a inGeoScale = 0, distance is given in SVS unit.
	 * If a inGeoScale != 0, distance is given in meters.
	 * @param inPt1 First point (\c double precision)
	 * @param inPt2 Second point (\c double precision)
	 * @param inGeoScale Scale for long/lat coordinate system : number of units per degree (set to 0 if not long/lat coordinates)
	 * @return Distance between real points \a inPt1 and \a inPt2
	 */
  static TBdouble GetDist(const TB_2D_DBLPOINT& inPt1,
                          const TB_2D_DBLPOINT& inPt2,
                          TBuint32              inGeoScale);

	/**
	 * Computes the result of the translation of \a inPt of vector \a inDx, \a inDy
	 * @note If \a inGeoScale = 0, translation is simply an addition of \a inDx and \a inDy
   * If \a inGeoScale != 0, \a inDx and \a inDy are values given in meters,
   * \a inPt and \a outPt are values in long/lat coordinates.
	 * @param inPt Point to be translated
	 * @param outPt Result of the translation
	 * @param inDx The x component of translation's vector
	 * @param inDy The y component of translation's vector
	 * @param inGeoScale Scale for long/lat coordinate system : number of units per degree (set to 0 if not long/lat coordinates)
   * @since 1.7.0
	 */
  static void Translate(const TB_2D_LONGPOINT& inPt,
                        TB_2D_LONGPOINT&       outPt,
                        TBdouble               inDx,
                        TBdouble               inDy,
                        TBuint32               inGeoScale);

	/**
	 * Converts a "real" distance into a "view" distance. Useful for drawing scale information.
	 * @note If #CBProjection is a #CBIsoProjection, \a inDist is assumed to be given in SVS units
   * If #CBProjection is a #CBGeoProjection, \a inDist is assumed to be given in meters.
   * Conversion is valid for view's center point
	 * @param inDist The "real" distance
   * @return "view" distance
   * @since 1.7.0
	 */
  virtual TBdouble DistToPixels(TBdouble inDist) const = 0;

	/**
	 * Returns clockwise oriented angle (in degrees) between line (\a inPt1, \a inPt2)
	 * and vertical.
	 * @param inPt1 First point
	 * @param inPt2 Second point
	 * @param inGeoScale Scale for long/lat coordinate system : number of units per degree (set to 0 if not long/lat coordinates)
	 * @return Angle in degrees
	 */
	static TBint16 GetAngle(const TB_2D_LONGPOINT& inPt1,
													const TB_2D_LONGPOINT& inPt2,
													TBuint32               inGeoScale);

protected:

  /**
   * @internal
   */
  virtual void Init(void) = 0;

  virtual void SetRealRect(void) = 0;

  /**
   * @internal
   */
	void RotateZ(TBdouble& ioX,
							 TBdouble& ioY) const;

  /**
   * @internal
   */
	void RevRotateZ(TBdouble& ioX,
									TBdouble& ioY) const;

  /**
   * @internal
   */
	void RevRotateZ(TB_2D_LONGPOINT& ioPt) const;

#if defined(_BSIV_LEVEL3)
  /**
   * @internal
   */
	void RotateX(TBdouble& ioX,
							 TBdouble& ioY) const;

  void RotateX(TBint32& ioX,
               TBint32& ioY) const;

  /**
   * @internal
   */
	void RevRotateX(TBdouble& ioX,
							 		TBdouble& ioY) const;

  /**
   * @internal
   */
	void RevRotateX(TB_2D_LONGPOINT& ioPt) const;

  void RevRotateX(TBint32& ioX, TBint32& ioY) const;

	/**
	 * Returns the cosinus of the rotation angle around X axis (#mXAngle).
	 * @return Cosinus of rotation angle around X axis.
	 */
	inline TBfloat GetXCos(void) const { return mXCos; }

	/**
	 * @internal
	 */
	inline TBfloat GetXFact(void) const { return mXFact; }

	/**
	 * @internal
	 */
  TBfloat GetXFact(TBint16 y) const;

	/**
	 * @internal
	 */
  void SetXFact(void);
#endif

	friend class CBPainter;
};

#endif // __CBPROJECTION_H__

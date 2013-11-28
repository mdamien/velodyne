/*==========================================================  (-*- C++ -*-)
 *
 * @file CBView.h
 * 
 * @version  $Id: CBView.h,v 1.38 2006/07/26 20:36:09 wkunkel Exp $ 
 * 
 * @author  William Kunkel
 *
 * @copyright  (c) 2002-2003 BeNomad S.A.R.L., All Rights Reserved
 *
 * BeNomad confidential file protected by international copyright laws
 * UNAUTHORIZED ACCESS, USE, REPRODUCTION OR DISTRIBUTION IS PROHIBITED.
 *
 *========================================================================*/

#ifndef _CBVIEW_H_
#define _CBVIEW_H_

/*!
  @file CBView.h
	CBView class definition.
*/

#if defined(_BWIN32_API_SUPPORT)
#  include <windows.h>
#elif defined(_BQT_API_SUPPORT)
#  include <qrect.h>
#endif

#include "BTypes.h"
#include "BCartoConst.h"

#if defined(_BMT_SAFE)
#  include "CBMutex.h"
#endif

class CBSVS;
class CBViewImp;
class CBProjection;
class CBGraphicChart;

/**
 * \enum EB_CLR_DEF
 * An enumeration that specifies the number of bits per pixel and color definition of an off-screen
 * @since v1.9.0 creation 
 */
enum EB_CLR_DEF {
  EB_CLR_DEF_UNDEFINED,
  EB_CLR_DEF_8,      //!<  8 bits per pixel : 256 gray level or palette entries
  EB_CLR_DEF_16_444, //!< 16 bits per pixel : 4 bits for red, 4 bits for green, 4 bits for blue (4 bits unused)
  EB_CLR_DEF_16_555, //!< 16 bits per pixel : 5 bits for red, 5 bits for green, 5 bits for blue (1 bit unused)
  EB_CLR_DEF_16_565, //!< 16 bits per pixel : 5 bits for red, 6 bits for green, 5 bits for blue
  EB_CLR_DEF_32_RGB  //!< 32 bits per pixel : 8 bits for red, 8 bits for green, 8 bits for blue (8 bits unused)
};

#define B_NB_BYTES_PER_PIXEL(n) ((n) == EB_CLR_DEF_UNDEFINED ? 0 : (n) == EB_CLR_DEF_32_RGB ? 4  : (n) != EB_CLR_DEF_8 ? 2 : 1)
#define B_NB_BITS_PER_PIXEL(n)  ((n) == EB_CLR_DEF_UNDEFINED ? 0 : (n) == EB_CLR_DEF_32_RGB ? 32 : (n) != EB_CLR_DEF_8 ? 16 : 8)


/**
 * @class CBView
 * The CBView class provides an on-screen view of static SVS data and methods to move and zoom inside.
 * To construct a CBView object depending on your platform, you should use the factory #CBViewFactory.
 * @note If you wish to add dynamic POIs over static SVS data, you must use the Fleet Management API
 * (See CBFleetMgr::CreateView).
 * @note Multithreading support : yes if you do not use the underlying projection (See #GetProjection)
 * to access or modify its parameters.
 * To enable multithreading support you should compile with the macro _BMT_SAFE defined and link 
 * against the suitable library or DLL. 
 */
class BRND_EXPORT CBView
{
public:

  /**
   * \internal
   * Constructor for internal use only.
   */
  CBView(CBViewImp * inViewImp);

  /**
   * Destructor
   */
  virtual ~CBView(void);
    
  /** 
   * Once you have created the view, you must call this method to initialize it.
   * @param inRedraw A flag that indicates whether the view must be redrawn or not.
   * @return \c true if the view was successfully initialized, \c false otherwise.
   */
  virtual TBbool Initialize(TBbool inRedraw = true);

  /**
   * Returns the width of the view (in pixels).
   * @return The width of the view (in pixels).
   */
  TBuint16 GetWidth(void) const;
  
  /**
   * Returns the height of the view (in pixels).
   * @return The height of the view (in pixels).
   */
  TBuint16 GetHeight(void) const;

  /**
   * Returns the current Graphic Chart used for parameterizing rendering operations.
   * @return The current Graphic Chart used for parameterizing rendering operations.
   */
  const CBGraphicChart * GetGraphicChart(void) const;

  /**
   * Assigns a new graphic chart for parameterizing rendering operations.
   * @param inGphChart New graphic chart to use.
   */
  void SetGraphicChart(const CBGraphicChart * inGphChart);

  /**
   * Enables or disables the antialiasing of polylines.
   * @param antiAliasing \c true to enable the antialiasing, \c false to disable.
   */
  void SetAntiAliasing(TBbool antiAliasing);

  /**
   * Assigns a preferential language code for text rendering
	 * @note Objects for which defined language code is not available, default language will be used (attribute code #KB_ATT_NAME)
   * @param inLanguageCode Language code to use (see #EB_LANGUAGE_CODE).
   */
	void SetLanguageCode(EB_LANGUAGE_CODE inLanguageCode);

  /**
   * Returns the current text display order used by the view to draw texts.
   * This value corresponds to a Class ID from which texts must be drawn (default is 10000).
   * @return The current text display order.
   */
  TBuint32 GetTextDisplayOrder(void) const;

  /**
   * Sets a new text display order from the specified Class ID \a inClassID.
   * @param inClassID The new text display order.
   */
  void SetTextDisplayOrder(TBuint32 inClassID);

  /**
   * Returns the underlying projection used by the view to display SVS data.
   * @return The underlying projection used by the view to display SVS data.
   * @warning DO NOT USE the returned projection to perform zoom operations. This 
   * may produce undefined behaviours if you use the #ZoomIn and #ZoomOut methods.
   */
  CBProjection * GetProjection(void) const;

  /**
   * Returns a pointer on the underlying offscreen
   * @return Pointer on the underlying offscreen.
   */
  TBany GetOffscreen(void)  const;

  /**
   * Returns the depth of the underlying offscreen
   * @return Depth of the underlying offscreen.
   */
  TBuint8 GetOffscreenDepth(void)  const;

  /**
   * Redraws the whole content of the view.
   * @param inDrawTexts A flag that indicates whether texts must be drawn or not.
   */
  virtual void Redraw(TBbool inDrawTexts = true);
    
  /**
   * Refreshes the whole content of the view by flushing the internal off-screen. 
   */
  virtual void Refresh(void);

  /**
   * Resizes the view to the specified dimensions.
   * @param inWidth The new width of the view.
   * @param inHeight The new height of the view.
   */
  virtual TBbool Resize(TBuint16 inWidth, TBuint16 inHeight);

  /**
   * Translates the view by a vector defined by screen points \a inPt1 and \a inPt2.
   * @param inPt1 First screen coordinate point
 	 * @param inPt2 Second screen coordinate point.
   * @param inRedraw A flag that indicates whether the view must be redrawn or not.
   */
  virtual void Move(const TB_2D_POINT & inPt1, 
                    const TB_2D_POINT & inPt2, 
                    TBbool              inRedraw = true);
  
  /**
   * Performs a zoom operation centered on the view according to the given scale.
   * @param inScale The projection scale.
   * @param inRedraw A flag that indicates whether the view must be redrawn or not.
   * @note \a inScale can not be smaller than 0.2
   */
  virtual void Zoom(TBfloat inScale, TBbool inRedraw = true);

  /**
   * Performs a zoom operation centered on a point in real coordinates (SVS coordinate system) 
   * according to the given scale.
   * @param inScale The projection scale.
   * @param inPoint The point in real coordinates (SVS coordinate system).
   * @param inRedraw A flag that indicates whether the view must be redrawn or not.
   * @note \a inScale can not be smaller than 0.2
   */
  virtual void Zoom(TBfloat inScale, const TB_2D_LONGPOINT& inPoint, TBbool inRedraw = true);

  /**
   * Performs a zoom operation centered on a point in real coordinates (SVS coordinate system) 
   * according to the given scale.
   * @param inScale The projection scale.
   * @param inPoint The point in real double coordinates (SVS coordinate system).
   * @param inRedraw A flag that indicates whether the view must be redrawn or not.
   * @note \a inScale can not be smaller than 0.2
   * @since v1.8.0 creation
   */
  virtual void Zoom(TBfloat inScale, const TB_2D_DBLPOINT& inPoint, TBbool inRedraw = true);

  /**
   * Performs a zoom operation centered on a screen point according to the given scale.
   * @param inScale The projection scale.
   * @param inPoint The screen point coordinates
   * @param inRedraw A flag that indicates whether the view must be redrawn or not.
   * @note \a inScale can not be smaller than 0.2
   */
  virtual void Zoom(TBfloat inScale, const TB_2D_POINT& inPoint, TBbool inRedraw = true);

  /**
   * Performs a zoom out operation by restoring the initial projection scale.
   * @param inRedraw A flag that indicates whether the view must be redrawn or not.
   */
  virtual void ZoomInitial(TBbool inRedraw = true) ;

  /**
   * Performs a zoom operation inside the specified screen rectangular area.
   * @param inRect The new screen rectangular limits of SVS objects to project on screen.
   * @param inRedraw A flag that indicates whether the view must be redrawn or not.
   */
  virtual void Zoom(const TB_2D_RECT & inRect, TBbool inRedraw = true);
  
  /**
   * Performs a zoom operation inside the specified real rectangular area (SVS coordinate system).
   * @param inRect The new real rectangular limits of SVS objects to project on screen.
   * @param inRedraw A flag that indicates whether the view must be redrawn or not.
   */
  virtual void Zoom(const TB_2D_LONGRECT & inRect, TBbool inRedraw = true);
  
  /**
   * Performs an unzoom operation centered on the view (projection scale becomes 
   * twice its current value).
   * @param inRedraw A flag that indicates whether the view must be redrawn or not.
   */
  virtual void UnZoom(TBbool inRedraw = true);

  /**
   * @name Stepped Zoom related methods
   * The two following methods are intended to be used with a predefined set of zoom levels
   * which are defined in the current Graphic Chart. These methods have no effect if the 
   * Graphic Chart is not in the "stepped zoom mode" (See CBGraphicChart::EB_ZOOM_MODE).
   */
  //@{
  /**
   * Performs a zoom 'in' operation centered on the view by using the projection scale
   * defined in the Graphic Chart at the next lower zoom level.
   * @param inRedraw A flag that indicates whether the view must be redrawn or not.
   * @return \c false if there is no lower zoom level, \c true otherwise.
   */
  virtual TBbool ZoomIn(TBbool inRedraw = true); 
  
  /**
   * Performs a zoom 'out' operation centered on the view by using the projection scale
   * defined in the Graphic Chart at the next upper zoom level.
   * @param inRedraw A flag that indicates whether the view must be redrawn or not.
   * @return \c false if there is no upper zoom level, \c true otherwise.
   */
  virtual TBbool ZoomOut(TBbool inRedraw = true);
  //@}

  /**
   * @name Advanced use of Projection methods
   * The first goal of the following methods is to provide a multithreading support 
   * for accessing or modifying parameters of the internal projection (Threaded applications
   * should not directly access the underlying projection via #GetProjection).   
   */
  //@{
  
  /**
   * Returns the current projection scale (see #CBProjection::mScale).
   * @return The current projection scale.
   */
  TBfloat GetScale(void) const;

  /**
	 * Returns the current projection factor (see #CBProjection::mFactor).
	 * @return The current projection factor
	 */
  TBfloat GetFactor(void) const;
 
  /**
	 * Returns the initial projection factor (see #CBProjection::mInitFactor).
	 * @return The Initial projection factor.
	 */
  TBfloat GetInitFactor(void) const;
  
  /**
	 * Returns the rotation angle around z axis.
	 * @return Rotation angle around z axis.
	 */
  TBint32 GetZAngle(void) const;

  /**
	 * Sets a rotation angle around z axis.
	 * @param inAngle Rotation angle around z axis in degrees.
	 */
  void SetZAngle(TBint32 inAngle = 0);

#if defined(_BSIV_LEVEL3)
  /**
	 * Returns the rotation angle around x axis.
	 * @return Rotation angle around x axis.
	 */
  TBint32 GetXAngle(void) const;

  /**
	 * Sets a rotation angle around x axis.
	 * @param inAngle Rotation angle around x axis in degrees.
	 * @note \a inAngle is bounded by 0° and 70° which means that 
	 * if \a inAngle is < 0°, the X-angle will be set to 0° 
	 * and if \a inAngle is > 70°, the X-angle will be set to 70°
	 */
	void SetXAngle(TBint32 inAngle = 0);

  /**   
	 * Returns the y screen coordinate of the horizon ().
   * @note 0 means that the horizon is not visible which is the case if and only if the X-angle
   * value is < 60°.
	 * @return The y screen coordinate of the horizon.
   * @since v1.5
	 */
  TBint16 GetHorizonHight(void) const;
#endif
  
  /**
	 * Returns the current real 2D rectangle corresponding to the visible SVS objects displayed in the view.	 
	 * @param outRect Current real 2D rectangle
	 */
  void GetRealRect(TB_2D_LONGRECT& outRect) const;

  /**
	 * Returns the initial real rectangle.
	 * @param outRect Initial real rectangle
	 */
  void GetInitialRealRect(TB_2D_LONGRECT& outRect) const;

  /**
   * Returns current real 2D-center point of the view.
   * @param outPoint Real (SVS coordinate system) 2D-center point of the view.
   * @since v1.10.0 Creation
   */
  void GetCenterRealPoint(TB_2D_LONGPOINT& outPoint) const;

  /**
   * Returns current real 2D-center point of the view (in \c double precision).
   * @param outPoint Real (SVS coordinate system) 2D-center point of the view
   * @since v1.10.0 Creation
   */
  void GetCenterRealDblPoint(TB_2D_DBLPOINT& outPoint) const;

  /**
	 * Computes screen projection of a real (SVS coordinate system) 2D point.
	 * @param inRealPoint Real coordinate 2D point
	 * @param outPoint Screen point = projection of \a inRealPoint on screen.
	 * @return \c false if \a inRealPoint 's projection is not visible (only if #CBProjection is a #CBGeoProjection),
	 * \c true otherwise
	 */
  TBbool Project(const TB_2D_LONGPOINT& inRealPoint, TB_2D_LONGPOINT& outPoint) const;

  /**
	 * Computes screen projection of a real (SVS coordinate system) 3D point.
	 * @note The z component of \a inRealPoint is not taken into account.
	 * @param inRealPoint Real coordinate 3D point
	 * @param outPoint Screen point = projection of \a inRealPoint on screen
   * @return \c false if \a inRealPoint 's projection is not visible (only if #CBProjection is a #CBGeoProjection),
	 * \c true otherwise
	 */
  TBbool Project(const TB_3D_LONGPOINT& inRealPoint, TB_2D_LONGPOINT& outPoint) const;

	/**
	 * Computes screen projection of a real (SVS coordinate system) 2D rectangle.
	 * @param inRealRect Real coordinate 2D rectangle
	 * @param outRect Screen rectangle = projection of \a inRealRect on screen
   * @return \c false if \a inRealRect 's projection is not visible (only if #CBProjection is a #CBGeoProjection),
	 * \c true otherwise
	 */
  TBbool Project(const TB_2D_LONGRECT& inRealRect, TB_2D_LONGRECT& outRect) const;

	/**
	 * Computes screen projection of a real (SVS coordinate system) 3D rectangle.
	 * @note The z components of \a inRealRect are not taken into account.
	 * @param inRealRect Real coordinate 3D rectangle
	 * @param outRect Screen rectangle = projection of \a inRealRect on screen
   * @return \c false if \a inRealRect 's projection is not visible (only if #CBProjection is a #CBGeoProjection),
	 * \c true otherwise
	 */
  TBbool Project(const TB_3D_LONGRECT& inRealRect, TB_2D_LONGRECT& outRect) const;

	/**
	 * Computes real (SVS coordinate system) coordinates of a screen point.
	 * @param inScreenPoint Screen point
	 * @param outPoint Real (SVS coordinate system) point
	 * @return \c false if \a inScreenPoint has a real coordinate (only if #CBProjection is a #CBGeoProjection),
	 * \c true otherwise
	 */
  TBbool DeProject(const TB_2D_POINT& inScreenPoint, TB_2D_LONGPOINT& outPoint) const;

	/**
	 * Computes real (SVS coordinate system) coordinates of a screen rectangle.
	 * @param inScreenRect Screen rectangle
	 * @param outRect Real (SVS coordinate system) rectangle
   * @return \c false if \a inScreenRect has no real coordinates (only if #CBProjection is a #CBGeoProjection),
	 * \c true otherwise
	 */
  TBbool DeProject(const TB_2D_RECT& inScreenRect, TB_2D_LONGRECT& outRect) const;

	/**
	 * Returns euclidian real distance between screen points \a inPt1 and \a inPt2.
	 * @note If #CBProjection is a #CBIsoProjection, distance is given in SVS unit.
	 * If #CBProjection is a #CBGeoProjection, distance is given in meters.
	 * @return Distance between screen points \a inPt1 and \a inPt2
	 */
  TBfloat GetDist(const TB_2D_POINT& inPt1, const TB_2D_POINT& inPt2) const;

	/**
	 * Returns euclidian real distance between real (SVS coordinate system) points \a inPt1 and \a inPt2.
	 * @note If #CBProjection is a #CBIsoProjection, distance is given in SVS unit.
	 * If #CBProjection is a #CBGeoProjection, distance is given in meters.
	 * @return Distance between real points \a inPt1 and \a inPt2
	 */
  TBfloat GetDist(const TB_2D_LONGPOINT& inPt1, const TB_2D_LONGPOINT& inPt2) const;

  /**
	 * Returns clockwise oriented angle (in degrees) between line (\a inPt1, \a inPt2)
	 * and vertical.
	 * @param inPt1 First point
	 * @param inPt2 Second point
	 * @return Angle in degrees
	 */
	TBint16 GetAngle(const TB_2D_LONGPOINT& inPt1, const TB_2D_LONGPOINT& inPt2) const;
  //@}


#if defined(_BWIN32_API_SUPPORT)
  /** 
   * @name Microsoft Specific
   */
  //@{ 
  /**
   * Returns the handle of the window in which drawing operations are performed.
   * @return The handle of the window in which drawing operations are performed.
   */
  HWND GetHWnd(void) const;

  /**
   * Returns the underlying Off-screen Device Context.
   * @return The underlying Off-screen Device Context.
   * @warning You should never release or keep a reference to the returned Windows Device Context.
   */
  HDC GetOffscreenDC(void);

  /**
   * Refreshes only the specified region by flushing the internal off-screen. 
   * @param inRegion The region to refresh.
   */
  void Refresh(const RECT & inRegion);

  /**
   * Sets a user defined drawing callback which will be called whenever the view has to 
   * be redrawn. This allows you to customize the view representation with additional 
   * informations such as current coordinates, progress meters, menus etc.
   * @param BCustomDrawFunc The user defined drawing callback.
   * @param inUserData An optional user data to pass to your callback.
   * @warning You should never release the Off-screen Device Context given to the callback !
   */
  void SetCustomDrawCbk(void (*BCustomDrawFunc)(HDC inOffscreenDC, const RECT& inClipRegion, TBany inUserData), 
                        TBany inUserData = NULL);
 

  //void UpdatePalette(TBbool inRealize=false);

#elif defined(_BQT_API_SUPPORT)
  /** 
   * @name Qt Specific
   */
  //@{ 

  /**
   * Refreshes only the specified rectangle by flushing the internal off-screen. 
   * @param inRect The specified rectangle
   */
  void Refresh(const QRect& inRect);

  /**
   * Sets a user defined drawing callback which will be called whenever the view has to 
   * be redrawn. This allows you to customize the view representation with additional 
   * informations such as current coordinates, progress meters, menus etc.
   * @param CustomDrawFunc The user defined drawing callback.
   * @param inUserData An optional user data to pass to your callback.   
   */
  void SetCustomDrawCbk(void (*BCustomDrawFunc)(QPixmap * inOffscreen, const QRect& inClipRegion, TBany inUserData), 
                        TBany inUserData = NULL);
#endif
  //@}

  /**
   * Sets an SVS filter callback in order to trigger rendering operations on specific SVS files.
   * @param BRenderSVSFilterCbk An optional SVS filter callback.   
   * @param inUserData An optional user data to pass to your used defined callback.
  */
  void SetSVSFilterCallback(TBbool (*BRenderSVSFilterCbk)(TBany inData, const CBSVS * inSVS), TBany inUserData = NULL);

  /**
   * \internal
   * Accessor to the internal view implementation.
   */
  inline CBViewImp * GetViewImp(void) const { return mViewImp; }  

protected:

  CBView (void);
  // Disable copy
  CBView (const CBView&);
  CBView & operator=(const CBView&);

private:
#if defined(_BMT_SAFE)
  mutable CBMutex mMutex;
#endif
  CBViewImp * mViewImp;
};

#endif /* _CBVIEW_H_ */

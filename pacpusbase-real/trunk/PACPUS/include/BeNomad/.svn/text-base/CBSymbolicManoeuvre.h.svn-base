/*==========================================================  (-*- C++ -*-)
 *
 * @file CBSymbolicManoeuvre.h
 * 
 * @version  $Id: CBSymbolicManoeuvre.h,v 1.14 2006/06/20 08:50:42 dlabrousse Exp $ 
 * 
 * @author  David Labrousse
 *
 * @copyright  (c) 2002-2006 BeNomad S.A.R.L., All Rights Reserved
 *
 * BeNomad confidential file protected by international copyright laws
 * UNAUTHORIZED ACCESS, USE, REPRODUCTION OR DISTRIBUTION IS PROHIBITED.
 *
 *========================================================================*/

#ifndef __CBSYMBOLIC_MANOEUVRE_H__
#define __CBSYMBOLIC_MANOEUVRE_H__

#if defined(_BSIV_LEVEL2) || defined(_BSIV_LEVEL3)

#if defined(_BWIN32_API_SUPPORT)
#  include <windows.h>
#endif

/*!
  @file CBSymbolicManoeuvre.h
	CBSymbolicManoeuvre class definition.
*/

#include "BTypes.h"
#include "BMacros.h"

// Forward declarations
class CBRouteSheet;
class CBPainter;


/**
 * @class CBSymbolicManoeuvre
 * The CBSymbolicManoeuvre class provides a bitmap offscreen of symbolic representation of a #CBRouteSheet manoeuvre.
 * Such a representation can be used in navigation applications in order to facilitate comprehension of a route instruction.
 * User can define the size of the view (square views are recommended for best use of available space) as well as customize
 * the graphic representation by defining a set of colors to be used.
 * @note Make sure that the given Route Sheet contains angles (see #CBRouteSheet constructor or #CBGuidance::TB_NAV_OPTIONS::computeRouteSheetAngles)
 * otherwise the #CBSymbolicManoeuvre::Draw method will always return \c false.
 * @since v1.8.0 Creation
 * @since v1.10.0 Added SetPenWidth method
 */
class BRND_EXPORT CBSymbolicManoeuvre
{
public:
  /**
   * @struct TB_SYMBOL_STYLE
   * A structure that contains RGB (Red Green Blue) color definitions.
   * @note use 8 weakest bits for Blue definition, 8 following bits for Green definition and 8 following bits for Red definition
   */
  typedef struct {
    TBuint32 mBGColor;       //!< The RGB color of the background
    TBuint32 mPenColor;      //!< The RGB color of the underlying roads
    TBuint32 mRoutePenColor; //!< The RGB color of the route
  } TB_SYMBOL_STYLE;

  /**
   * Default Constructor.
   */
  CBSymbolicManoeuvre(void);

#if defined(_BWIN32_API_SUPPORT)
  /** 
   * Creates and initializes the underlying off-screen. 
   * @param inWidth The width (in pixels) of the off-screen that contains the symbolic representation of the manoeuvre.
   * @param inHeight The height (in pixels) of the off-screen that contains the symbolic representation of the manoeuvre.
   * @param inDC Windows memory device context for compatibility.
   * @note Supported depths are 16bpps or 32bpps.
   */
  TBbool Initialize(TBuint16 inWidth, TBuint16 inHeight, HDC inDC);
#else
  /**
   * Creates and initializes the underlying off-screen.
   * @param inWidth The width (in pixels) of the off-screen that contains the symbolic representation of the manoeuvre.
   * @param inHeight The height (in pixels) of the off-screen that contains the symbolic representation of the manoeuvre.
   * @param inDepth The depth (number of bits per pixel) of off-screen.
   * @note Supported depths are 16bpps or 32bpps.
   */
  TBbool Initialize(TBuint16 inWidth, TBuint16 inHeight, TBuint8 inDepth);
#endif

  /**
   * Destructor.
   */
  ~CBSymbolicManoeuvre(void);

  /**
   * Returns the width (in pixels) of the off-screen that contains the symbolic representation of the manoeuvre.
   * @return The width (in pixels) of the off-screen that contains the symbolic representation of the manoeuvre.
   */
  inline TBuint16 GetWidth(void) const { return mWidth; }

  /**
   * Returns the height (in pixels) of the off-screen that contains the symbolic representation of the manoeuvre.
   * @return The height (in pixels) of the off-screen that contains the symbolic representation of the manoeuvre.
   */
  inline TBuint16 GetHeight(void) const { return mHeight; }

  /**
   * Returns the depth (in bpps) of the off-screen that contains the symbolic representation of the manoeuvre.
   * @return The depth (in bpps) of the off-screen that contains the symbolic representation of the manoeuvre.
   */
  TBuint8 GetDepth(void) const;

  /**
   * Returns last route sheet's index drawn (see #DrawSymbol).
   * @return Last route sheet's index drawn or 0xFFFFFFFF if #DrawSymbol has not been called yet.
   */
  inline TBuint32 GetCurIndex(void) const { return mCurIndex; }

  /**
   * Sets new color definitions.
   * @param inStyle The color definitions to set.
   */
  void SetStyle(const TB_SYMBOL_STYLE & inStyle);

  /**
   * Sets the pen width (wide or narrow)
   * @param inWide if \c true (default), pen will be wide, if \c false, pen will be narrow
   * @since v1.10.0 Creation 
   */
  void SetPenWidth(TBbool inWide = true);

  /**
   * Draws a route sheet's instruction
   * @param inRouteSheet the route sheet of the instruction
   * @param inRouteSheetIndex the index of the route instruction to draw.
   * @return \c true if drawing was succesful, \c false otherwise (invalid parameters or last instruction or no angles available in route sheet)
   * @note Two consecutive calls to this method with same parameters will be handled by exiting method without redrawing in second call.
   */
  TBbool Draw(const CBRouteSheet * inRouteSheet, TBuint32 inRouteSheetIndex);

#if defined(_BWIN32_API_SUPPORT)
  /**
   * Returns the underlying off-screen Device Context.
   * @return The underlying off-screen Device Context.
   * @warning You should never release or keep a reference to the returned Windows Device Context.
   */
  HDC GetOffscreenDC(void) const { return mMemoryDC; }

  /**
   * Transfers pixels from the underlying off-screen to the specified memory device context at
   * the given location.
   * @param inHDCDest Handle to the destination device context.
   * @param inX Specifies the x-coordinate of the upper-left corner of the destination rectangle.
   * @param inY Specifies the y-coordinate of the upper-left corner of the destination rectangle.
   * @return \c true on success, \c false otherwise.
   */
  TBbool BitBlt(HDC inHDCDest, int inX, int inY) const;
#endif

  /**
   * Returns a pointer on the underlying offscreen
   * @return Pointer on the underlying offscreen.
   */
  TBany GetOffscreen(void) const;

private:
  // Disable copy
  CBSymbolicManoeuvre(const CBSymbolicManoeuvre&);
  CBSymbolicManoeuvre& operator=(const CBSymbolicManoeuvre&);
private:
#if defined(_BWIN32_API_SUPPORT)
  HDC                  mMemoryDC; 
  HBITMAP              mDIB;
  TBany                mOffscreen;
#endif
  const CBRouteSheet * mRouteSheet;
  CBPainter          * mPainter;
  TBuint32             mCurIndex;
  TB_SYMBOL_STYLE      mStyle;
  TBuint16             mWidth;
  TBuint16             mHeight;
  TBuint16             mSize;
  TBuint16             mPenWidth1;
  TBuint16             mPenWidth2;
  TBint32              mRadius;  
  TBint16              mCurDAngle;
  TB_2D_LONGPOINT      mCurPosition;
};

#endif

#endif // __CBSYMBOLIC_MANOEUVRE_H__

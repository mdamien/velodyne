/*==========================================================  (-*- C++ -*-)
 *
 * @file CBViewFactory.h
 * 
 * @version  $Id: CBViewFactory.h,v 1.11 2006/06/06 12:09:10 dlabrousse Exp $ 
 * 
 * @author  William Kunkel
 *
  * @copyright  (c) 2002-2003 BeNomad S.A.R.L., All Rights Reserved
 *
 * BeNomad confidential file protected by international copyright laws
 * UNAUTHORIZED ACCESS, USE, REPRODUCTION OR DISTRIBUTION IS PROHIBITED.
 *
 *========================================================================*/

#ifndef _CBVIEW_FACTORY_H_
#define _CBVIEW_FACTORY_H_

/*!
  @file CBViewFactory.h
	CBViewFactory class definition.
*/

#if defined(_BWIN32_API_SUPPORT)
#  include <windows.h>
#endif

#include "BTypes.h"
#include "CBView.h"

class CBSVSMgr;
class CBGraphicChart;
#if defined(_BQT_API_SUPPORT)
class QWidget;
#endif

/**
 * @class CBViewFactory
 * The CBViewFactory class is a factory object which provides methods for view construction.
 * @note On all Win32 plateforms, you should compile with the macro _BWIN32_API_SUPPORT defined.
 * @note On Linux plateforms, you should compile with the macro _BQT_API_SUPPORT defined.
 */
class BRND_EXPORT CBViewFactory
{
public:

#if defined(_BWIN32_API_SUPPORT)
  /**
   * Creates a new CBView compatible with all Win32 plateforms.
   * @param inSVSMgr The SVS Manager that contains SVS data (See #CBSVSMgr).
   * @param inGphChart A pointer to a graphic chart (See #CBGraphicChart).
   * @param inHWnd The handle of a window in which rendering operations must be done.
   * @param inMaxNbText The maximum number of texts to display (default = 20).
   * @return The created view or \c null if an error occurs. 
   */
  static CBView * CreateWin32View (CBSVSMgr             * inSVSMgr, 
                                   const CBGraphicChart * inGphChart,
                                   HWND                   inHWnd,
                                   TBuint16               inMaxNbText = 20);

#elif defined(_BQT_API_SUPPORT)

  /**
   * Creates a new CBView compatible with all Linux/Qt plateforms.
   * @param inSVSMgr The SVS Manager that contains SVS data (See #CBSVSMgr).
   * @param inGphChart A pointer to a graphic chart (See #CBGraphicChart).
   * @param inQtWidget The Qt widget in which rendering operations must be done.
   * @param inMaxNbText The maximum number of texts to display (default = 20).
   * @return The created view or \c null if an error occurs. 
   */
  static CBView * CreateQtView (CBSVSMgr             * inSVSMgr, 
                                const CBGraphicChart * inGphChart,
                                QWidget              * inQtWidget,
                                TBuint16               inMaxNbText = 20);

#else

  /**
   * Creates a new CBView compatible with any plateform.
   * @param inSVSMgr The SVS Manager that contains SVS data (See #CBSVSMgr).
   * @param inGphChart A pointer to a graphic chart (See #CBGraphicChart).
   * @param inDepth The depth of the offscreen (must ne one of 8, 16 or 32 bits per pixel)
   * @param inWidth The width (in pixels) of the offscreen to create
   * @param inHeight The height (in pixels) of the offscreen to create
   * @param inMaxNbText The maximum number of texts to display (default = 20).
   * @return The created view or \c null if an error occurs. 
   */
  static CBView * CreateOffscreenView (CBSVSMgr             * inSVSMgr, 
                                       const CBGraphicChart * inGphChart,
                                       TBuint8                inDepth,
                                       TBuint16               inWidth,
                                       TBuint16               inHeight,
                                       TBuint16               inMaxNbText = 20);
  
  /**
   * Creates a new CBView compatible with any plateform.
   * @param inSVSMgr The SVS Manager that contains SVS data (See #CBSVSMgr).
   * @param inGphChart A pointer to a graphic chart (See #CBGraphicChart).
   * @param inClrDef The color definition of the offscreen (see #EB_CLR_DEF)
   * @param inWidth The width (in pixels) of the offscreen to create
   * @param inHeight The height (in pixels) of the offscreen to create
   * @param inMaxNbText The maximum number of texts to display (default = 20).
   * @return The created view or \c null if an error occurs. 
   */
  static CBView * CreateOffscreenView (CBSVSMgr             * inSVSMgr, 
                                       const CBGraphicChart * inGphChart,
                                       EB_CLR_DEF             inClrDef,
                                       TBuint16               inWidth,
                                       TBuint16               inHeight,
                                       TBuint16               inMaxNbText = 20);
#endif

private:
  CBViewFactory(void);
  // Disable copy
  CBViewFactory(const CBViewFactory&);
  CBViewFactory & operator=(const CBViewFactory&);
};

#endif /* _CBVIEW_FACTORY_H_ */

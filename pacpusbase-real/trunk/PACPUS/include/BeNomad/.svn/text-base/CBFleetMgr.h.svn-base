/*==========================================================  (-*- C++ -*-)
 *
 * @file CBFleetMgr.h
 * 
 * @version  $Id: CBFleetMgr.h,v 1.47 2006/02/15 10:38:20 wkunkel Exp $ 
 * 
 * @author  William Kunkel
 *
 * @copyright  (c) 2002-2003 BeNomad S.A.R.L., All Rights Reserved
 *
 * BeNomad confidential file protected by international copyright laws
 * UNAUTHORIZED ACCESS, USE, REPRODUCTION OR DISTRIBUTION IS PROHIBITED.
 *
 *========================================================================*/

#ifndef _CBFLEET_MGR_H_
#define _CBFLEET_MGR_H_

/*!
  @file CBFleetMgr.h
	CBFleetMgr class definition.
*/

#include <stdio.h>
#if defined(_BWIN32_API_SUPPORT)
#  include <windows.h>
#endif

#include "BTypes.h"
#include "CBStatePOI.h"

// Forward declarations
class CBSVS;
class CBSVSMgr;
class CBForm2D;
class CBVector;
class CBHashMap;
class CBImage;
class CBProjection;
class CBSecurityZone;
class CBDynamicForm;
class CBDynamicPOI;
class CBPolyline;
class CBView;
class CBGraphicChart;

#if defined(_BSIV_LEVEL2) || defined(_BSIV_LEVEL3)
  class CBRouteForm;
  class CBRoute;
#endif

#if defined(_BQT_API_SUPPORT)
class QWidget;
#endif

/**
 * @class CBFleetMgr
 * The CBFleetMgr class provides an interface dedicated to the Fleet Management.
 * This class allows you to create specific categories of State POIs in which it is 
 * possible to define up to 256 states (A category gathers a set of POIs which 
 * share the same states). In addition, the CBFleetMgr class manages an internal 
 * mapping between each state and an image (bitmap) as shown below :
 *
 * \image html fleet_model.png 
 *
 * The CBFleetMgr class acts as a dynamic forms factory and provides methods for 
 * creating State POIs, POIs, Security zones and Route objects.
 *
 * 
 */
class BFLT_EXPORT CBFleetMgr 
{
public:
  
  /**
   * Default constructor.
   */
  CBFleetMgr (void);

  /**
   * Destructor
   */
  ~CBFleetMgr (void);

  /** 
   * @name Fleet Management Initialization
   *  The following methods allow you to configure the Fleet Management API.
   */
  //@{
  /**
   * Adds a new category of state objects (i.e vehicles)
   * A category of state objects groups together all the POIs which share
   * the same states. A category allows you to handle up to \c inMaxStateCode
   * states (See #AddState method to define the mapping between these states and images).
   * @param inCategory  The state object category (the Class ID).
   * @param inMaxStateCode The maximum number of states for this category (up to 256)
   * @return \c false if this category is already handled, true otherwise.
   */
  TBbool AddCategory (TBuint32 inCategory, TBuint8 inMaxStateCode);

  /**
   * Defines the mapping between a state code and its bitmap representation for 
   * the specified category.
   * @param inCategory  The category of state objects.
   * @param inStateCode The state code
   * @param inFileName The file name of an image (bitmap) that represents this state.
   * @param inColorMask An optional color mask (RGB) for painting transparent bitmaps.
   * @return May return the following values:
   *  - 0 : the mapping has been successfully completed,
   *  - 1 : the given category does not exist.
   *  - 2 : the inStateCode argument is out of bounds
   *  - 3 : the image resource can not be loaded.
   */
  TBint16 AddState (TBuint32       inCategory,
                    TBuint8        inStateCode,
                    const TBchar * inFileName,
                    TBuint32       inColorMask=0xFFFFFFFF);

#if defined(_WIN32)
  /**
   * Associates a Windows bitmap resource according to a state code
   * for the given category of state objects. 
   * @param inCategory  The category of state objects.
   * @param inStateCode The state code
   * @param inBitmapResourceID The Windows resource ID
   * @param inModule Handle to the module whose executable file contains the resource. 
   * @param inColorMask An optional color mask (RGB) for painting transparent bitmaps.
   * @return May return the following values:
   *  - 0 : the mapping has been successfully completed,
   *  - 1 : the given category does not exist.
   *  - 2 : the inStateCode argument is out of bounds
   *  - 3 : the image resource can not be loaded.
   */
  TBint16 AddState (TBuint32  inCategory,
                    TBuint8   inStateCode,
                    TBuint32  inBitmapResourceID,
                    HMODULE   inModule=NULL,
                    TBuint32  inColorMask=0xFFFFFFFF);
#endif

  /**
   * Removes the specified state from the given category.
   * @param inCategory  The category of state objects.
   * @param inStateCode The state code to remove.
   * @return \c true if the given state has been successfully removed.
   */
  TBbool RemoveState (TBuint32 inCategory, TBuint8 inStateCode);

  /**
   * Returns the representation (if any) of the given state for
   * the specified category.
   * @param inCategory  The category of state objects.
   * @param inStateCode The state code
   * @return A \c CBImage object or \c null if there is no associated bitmap.
   */
  CBImage * GetImage (TBuint32 inCategory, TBuint8 inStateCode);
  //@}


  /** 
   * @name Dynamic Forms Creation
   * @warning The CBFleetMgr keeps the ownership on all created dynamic forms.
   * (State POIs, POIs, ...). So you <b>SHOULD NOT DESTROY</b> these objects using the 
   * delete operator. Use the CBFleetMgr::DeleteDynamicForm method to destroy a particular
   * in-memory form.
   */
  //@{

  /**
   * Creates a simple in-memory POI into the specified Class ID.
   * @param inClassID The Class ID that the POI belongs to.
   * @param inPosition The x and y ccordinates of the POI.
   * @note The representation of this POI will be determined by the SVS graphic chart.
   * @return A pointer to a valid CBDynamicPOI Object or NULL if an error occurs.
   */
  CBDynamicPOI * CreatePOI (TBuint32 inClassID, const TB_2D_LONGPOINT& inPosition);

  /**
   * Creates a new state POI into the specified category.
   * @param inCategory The category in which this state POI has to be created.
   * @param inPosition The x and y ccordinates of this POI.
   * @param inInitialState The initial state of this POI.
   * @note KB_UNDEFINED_STATE defines an undefined state.
   * @return A pointer to a valid state POI or NULL if an error occurs.
   */
  CBStatePOI * CreateStatePOI (TBuint32                inCategory, 
                               const TB_2D_LONGPOINT&  inPosition,
                               TBuint8                 inInitialState=KB_UNDEFINED_STATE);

  /**
   * Creates a dynamic 2D-polyline from an ordered array of points.
   * @param inClassID The Class ID that this object belongs to.
   * @param inPoints  An array of ordered points.
   * @param inNbPoints The number of points. 
   * @since v1.5 Creation.
   */
  CBPolyline * CreatePolyline(TBuint32                inClassID,
                              const TB_2D_LONGPOINT * inPoints,
                              TBuint32                inNbPoints);

  /**
   * Creates a new polygonal security zone into the specified Class ID.   
   * @param inClassID The Class ID that this object belongs to.
   * @param inPoints  An array of ordered 2D-points that defines a polygon.
   * @param inNbPoints The number of points.    
   * @param inColor The RGB code of the transparent fill color.      
   * @return A pointer to a valid CBSecurityZone object or NULL if an error occurs.
   * @since v1.5 Creation.
   */
  CBSecurityZone * CreateSecurityZone (TBuint32                inClassID,
                                       const TB_2D_LONGPOINT * inPoints,
                                       TBuint32                inNbPoints,                                       
                                       TBuint32                inColor); 
  
  /**
   * Creates a new polygonal security zone into the specified Class ID by
   * duplicating the geometry of the given CBForm2D object (Form's attributes
   * are not copied).
   * @param inClassID The Class ID that this object belongs to.
   * @param inClosedForm  A pointer to a Closed CBForm2D.
   * @param inColor The RGB code of the transparent fill color.      
   * @return A pointer to a valid CBSecurityZone object or NULL if an error occurs.
   * @since v1.5 Creation.
   */
  CBSecurityZone * CreateSecurityZone (TBuint32          inClassID,
                                       const CBForm2D  * inClosedForm,
                                       TBuint32          inColor); 

  /**
   * Creates a new security zone into the specified Class ID.
   * A security zone is defined by a series of ordered points and a distance
   * as shown below :
   * \image html security_zone.png
   * @param inClassID The Class ID that this object belongs to.
   * @param inPoints  An array of ordered points.
   * @param inNbPoints The number of points. 
   * @param inDist The orthogonal distance in meters.
   * @param inColor The RGB code of the transparent fill color.
   * @param inGeoScale An optional long/lat coordinate scale that may be used to limit distorsions.
   * @note The Security zone construction uses a complex algorithm that may be very 
   * time consuming if the given distance is too small ( O(N2) Algorithm ). This means
   * that creating a security zone with a distance of 300m will be nine times faster than
   * using a distane of 100m.
   * @return A pointer to a valid CBSecurityZone object or NULL if an error occurs.
   */
  CBSecurityZone * CreateSecurityZone (TBuint32                inClassID,
                                       const TB_2D_LONGPOINT * inPoints,
                                       TBuint32                inNbPoints,
                                       TBuint16                inDist,
                                       TBuint32                inColor,
                                       TBuint32                inGeoScale = 0);  

#if defined(_BSIV_LEVEL2) || defined(_BSIV_LEVEL3)
  /**
   * Creates a new security zone from a series of ordered points resulting from a route calculation.
   * @param inClassID The Class ID that this object belongs to.
   * @param inRoute  The route used to build this zone (See #CBRoute).
   * @param inDist The orthogonal distance in meters.
   * @param inColor The RGB code of the transparent fill color.
   * @param inGeoScale An optional long/lat coordinate scale that may be used to limit distorsions.
   * @note The Security zone construction use a complex algorithm that may be very 
   * time consuming if the given distance is too small ( O(N2) Algorithm ). This means
   * that creating a security zone with a distance of 300m will be nine times faster than
   * using a distane of 100m.
   * @return A pointer to a valid CBSecurityZone object or NULL if an error occurs.
   */
  CBSecurityZone * CreateSecurityZone (TBuint32        inClassID,
                                       const CBRoute * inRoute,
                                       TBuint16        inDist,
                                       TBuint32        inColor,
                                       TBuint32        inGeoScale = 0);  

  /**
   * Creates a CBRouteForm that can be used to represent a graphical route.
   * @param inClassID The Class ID that this object belongs to.
   * @param inRoute The route to display
   * @return A pointer to a valid CBRouteForm object or NULL if an error occurs.
   */                                                                                  
  CBRouteForm * CreateRoute (TBuint32 inClassID, const CBRoute * inRoute);
#endif
  //@}

  /**
   * Sets the visibility status of all dynamic objects of the specified class.
   * @note This method changes the internal visibility status of each dynamic object not the 
   * class visibility defined in a graphic chart !
   * @param inClassID The Class ID.
   * @param inFlag The visibility flag.
   */
  void SetVisibility(TBuint32 inClassID, TBbool inFlag);

  /**
   * Sets the label visibility status of all dynamic objects of the specified class.
   * @note This works only on dynamic POI objects which have a label.
   * @param inClassID The Class ID.
   * @param inFlag The visibility flag.
   */
  void SetLabelVisibility(TBuint32 inClassID, TBbool inFlag);
  
  /**
   * Sets the selection status of all dynamic objects of the specified class.
   * @param inClassID The Class ID.
   * @param inFlag The selection flag.
   */
  void SetSelection(TBuint32 inClassID, TBbool inFlag);
                                                                                                                                                     
  /**
   * Deletes the given dynamic form. 
   * This concerns state POIs, POIs, security zones or Route forms.
   * @param inDynForm The in-memory form to delete.
   * @return \c true if the given dynamic form has been successfully deleted,
   * \c false otherwise.
   */                                    
  TBbool DeleteDynamicForm (CBDynamicForm * inDynForm);

  /**
   * Deletes all dynamic forms of the given Class ID.
   * @param inClassID The Class ID
   */        
  void DeleteAllDynamicFormsFromClass (TBuint32 inClassID);

  /**
   * Deletes all dynamic forms handled by the Fleet Manager.
   */      
  void DeleteAllDynamicForms (void);

  /**
   * @return The underlying CBSVS object which contains dynamic forms.
   */ 
  inline CBSVS * GetSVS (void) const { return mSvs; }

#if !defined(_BNO_RENDERING)
# if defined(_BWIN32_API_SUPPORT)
  /**
   * A factory method which constructs a special #CBView object that allows you
   * to visualize cartographic data and dynamic forms resulting from a CBFleetMgr object.
   * @param inFleetMgr The CBFleetMgr object 
   * @param inSVSMgr A SVS Manager.
   * @param inGphChart A SVS graphic chart
   * @param inHWnd Handle to a window in which rendering operations must be done.
   * @param inMaxNbText The maximum number of texts to display.
   * @note To visualize dynamic forms resulting from a CBFleetMgr object, you have
   * to add yourself the underlying CBFleetMgr's CBSVS into the specified #CBSVSMgr
   * (See CBSVSMgr::Add and CBFleetMgr::GetSVS methods).
   */
  static CBView * CreateView (CBFleetMgr           * inFleetMgr,
                              CBSVSMgr             * inSVSMgr, 
                              const CBGraphicChart * inGphChart,
                              HWND                   inHWnd,
                              TBuint16               inMaxNbText);
# elif defined(_BQT_API_SUPPORT)
  static CBView * CreateView (CBFleetMgr           * inFleetMgr,
                              CBSVSMgr             * inSVSMgr, 
                              const CBGraphicChart * inGphChart,
                              QWidget              * inQtWidget,
                              TBuint16               inMaxNbText);
# else
  static CBView * CreateView (CBFleetMgr           * inFleetMgr,
			      CBSVSMgr             * inSVSMgr, 
			      const CBGraphicChart * inGphChart,
			      TBuint8                inDepth,
			      TBuint16               inWidth,
			      TBuint16               inHeight,
			      TBuint16               inMaxNbText);
# endif
#endif // _BNO_RENDERING

protected:
  // Disable copy
  CBFleetMgr (const CBFleetMgr& );
  CBFleetMgr & operator=(const CBFleetMgr& );

  TBint16 AddState (const TBuint32  inCategory,
                    const TBuint8   inStateCode,
                    CBImage       * inImage);

  static void BDynFormsCleanup (TBany key, TBany value, TBany userArg);

private:
  CBSVS     * mSvs;
  CBVector  * mCategoryInfo;
  CBHashMap * mDynForms;
};

#endif /* _CBFLEET_MGR_H_ */

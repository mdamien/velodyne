/*==========================================================  (-*- C++ -*-)
 *
 * @file CBGeoDecoder.h
 * 
 * @version  $Id: CBGeoDecoder.h,v 1.37 2006/05/03 17:47:15 dlabrousse Exp $ 
 * 
 * @author  William Kunkel
 *
 * @copyright  (c) 2002-2003 BeNomad S.A.R.L., All Rights Reserved
 *
 * BeNomad confidential file protected by international copyright laws
 * UNAUTHORIZED ACCESS, USE, REPRODUCTION OR DISTRIBUTION IS PROHIBITED.
 *
 *========================================================================*/

#ifndef _CBGEO_DECODER_H_
#define _CBGEO_DECODER_H_

/*!
  @file CBGeoDecoder.h
	CBGeoCoder class definition.
*/

#include "BGeoTypes.h"
#include "CBSVS.h"
#include "BCartoConst.h"

// Forward declarations
class CBSVSMgr;
class CBCursor;
class CBAttCursor;
class CBVector;
class CBGeoMapMatchedPoint;


/**
 * @class CBGeoDecoder
 * <B>Definition :</B>Reverse Geocoding is the process of translating a (Lat/Long) location back to
 * an address, place, city, state or identifying other attributes about or near the location.
 *
 * This class provides methods that allow you to :
 *
 * - retrieve geographical elements and their attributes located around a (x,y) location (See #Find).
 * - perform Road-Matching operations (See #RoadMatch)
 *
 * @note Multithreading support : The CBGeoDecoder class is compatible with multithreaded applications
 * but not thread-safe ! This means that two or more CBGeoDecoder objects can be run simultaneously 
 * in separate threads but multiple threads should not invoke methods of a CBGeoDecoder object at the same time.
 * To enable multithreading support you should compile with the macro _BMT_SAFE defined and link 
 * against the suitable library or DLL.
 *
 */
class BGEO_EXPORT CBGeoDecoder
{
public:

  /**
   * Constructs a new CBGeoDecoder object.
   * @param inSVSMgr The SVS Manager that contains geographical SVS data.
   */
  CBGeoDecoder (CBSVSMgr * inSVSMgr);

  /**
   * Destructor
   */
  ~CBGeoDecoder (void);

  /**
   * Returns the character encoding of resulting string attributes.    
   * @note The character encoding depends on the SVS source datasets (default is ISO-8859-1).
   * @since 1.7.0 Creation.
   */
  EB_ENCODING GetEncoding(void);

  /**
   * This method allows you to retrieve attribute values of objects being located around a geographical 
   * point of reference. For example, by specifying a class filter on the Road Network elements, you can use this method to
   * perform reverse geo-coding operations (i.e Finding the name of a road element being near a geographical point).
   * @param outItemFound Returns a valid pointer to a vector of #TB_GEODECODER_ITEM_DATA structures or \c null.
   * (one structure / found object). It's up to the caller to delete this vector and all its elements.
   * @param inGeoPoint The geographical point of reference.
   * @param inRadius The radius (in meters) in which this method must seek geographical elements.
   * @param inClassMatchFunc A user Class IDs filter (See #BClassMatchingFunc);
   * @param inClassMatchUserData An optional user data to pass to the Class IDs filter.
   * @param inAttCodeMatchFunc An optional callback to filter attributes (See #BAttCodeMatchingFunc).
   * @param inAttCodeMatchUserData An optional user data to pass to the attribute codes filter.
   * @return The number of found geographical elements.
   * @note The BCartoConst.h file contains all the Class IDs constants related to geographical data and 
   * reserved attribute codes.
   * @note It is strongly recommended to restrict the value of the \a inRadius argument. Indeed, 
   * the number of returned elements can be consequent (up to several thousands) and may
   * cause memory overflow. In addition, defining a small radius speeds up the processing time.
   */
  TBuint32 Find (CBVector            ** outItemFound,
                 const TB_2D_LONGPOINT& inGeoPoint,
                 TBuint32               inRadius,            
                 BClassMatchingFunc     inClassMatchFunc       = NULL,
                 TBany                  inClassMatchUserData   = NULL,
                 BAttCodeMatchingFunc   inAttCodeMatchFunc     = NULL,
                 TBany                  inAttCodeMatchUserData = NULL);
  
  /**
   * Performs a simple Road-Matching (or Map-Matching) operation on the given 2D-coordinates.
   * @param inGeoPoint The geographical point of reference.
   * @param inMaxRadius The radius in which the research is done.
   * @param inGetAdminPath Set this flag to \c true if you want to retrieve the complete 
   * hierarchical paths (left and right) of selected road (See CBGeoMapMatchedPoint::GetLeftPath
   * and CBGeoMapMatchedPoint::GetRightPath).
	 * @param inLanguageCode Preferential language for objects' names (see #EB_LANGUAGE_CODE).
   * @return A valid CBGeoMapMatchedPoint instance or \c NULL if the Road-Matching process failed.   
   * @note It's up to the caller to delete the returned object.
   * @since v1.3
   */
  CBGeoMapMatchedPoint * RoadMatch(const TB_2D_LONGPOINT & inGeoPoint,
                                   TBuint32                inMaxRadius,                    
                                   TBbool                  inGetAdminPath = false,
																	 EB_LANGUAGE_CODE        inLanguageCode = DEFAULT_LANGUAGE);

  /**
   * Performs a Road-Matching (or Map-Matching) process for a specified type of vehicle.
   * Road-matching consists of correcting uncertainties related to GPS measurements 
   * by repositioning a vehicle on most accurate segment of neighbouring roads.
   * @param inRtData GPS data (See TB_ROAD_MATCH_RT_DATA).
	 * @param inMaxRadius Maximum search radius around GPS point
	 * @param inTransMode Type of vehicle (see #EB_TRANSP_MODE)
   * @param inGetAdminPath Set this flag to \c true if you want to retrieve the complete 
   * hierarchical paths (left and right) of selected road (See CBGeoMapMatchedPoint::GetLeftPath
   * and CBGeoMapMatchedPoint::GetRightPath).
	 * @param inLanguageCode Preferential language for objects' names (see #EB_LANGUAGE_CODE).
   * @return A valid CBGeoMapMatchedPoint instance or \c NULL if the road-matching process failed.
   * @note It's up to the caller to delete the returned object.
   * @since v1.3
   */
  CBGeoMapMatchedPoint * RoadMatch(const TB_ROAD_MATCH_RT_DATA & inRtData,
										               TBuint32                      inMaxRadius,
										               EB_TRANSP_MODE                inTransMode,
										               TBbool											   inGetAdminPath = false,
																	 EB_LANGUAGE_CODE              inLanguageCode = DEFAULT_LANGUAGE);
  /**
   * @example revgeocoding.cpp
   * This is an example of how to perform a reverse geo-coding operation.
   */

protected:

  CBGeoDecoder (void);
  CBGeoDecoder (const CBGeoDecoder&);
  CBGeoDecoder& operator=(const CBGeoDecoder&);

  static TBbool ClassFilterCbk    (TBany inData, const TBuint32 inClassID, const EB_GEOTYPE inType);
  static void   ObjectFilterCbk   (TBany inData, const TB_FORM_PARAMETERS& inFormParam, const TBuint16 inNbAtt);
//   static TBbool AttributeFilterCbk(TBany inData, const TB_ATTRIBUTE& inAtt, const EB_ORDER& inOrder);
  static TBbool AttributeCursorCbk(TBany inData, CBAttCursor& inAttCursor);

  static void ClosedFunc (TBany inData, const TB_RENDERPOINT& inPoint, const EB_ORDER& inOrder);
  static void OpenFunc   (TBany inData, const TB_RENDERPOINT& inPoint, const EB_ORDER& inOrder);
  static void PointFunc  (TBany inData, const TB_2D_LONGPOINT& inPoint);
  static void RectFunc   (TBany inData, const TB_2D_LONGRECT& inRect);
  static void ArcFunc    (TBany inData, const TB_2D_ARC& inArc);

  static void ProcessClippedObject (TBany inData);

	static TBbool NetworkFilterFunc(TBany inData, const TBuint32 inClassID, const EB_GEOTYPE inType);
	static void RoadMatchObjectFunc(TBany inData, const TB_FORM_PARAMETERS& inFrmParam, const TBuint16 inNbAtt);
	static void RoadMatchOpenFunc  (TBany inData, const TB_RENDERPOINT& inPoint, const EB_ORDER& inOrder);

	void FindMatch(const TB_2D_LONGPOINT& inGeoPoint,
								 TBuint32               inMaxRadius,
								 TBany                  inItem,
								 TBbool                 dynamic = false);

#if defined(_BSIV_LEVEL3)
	CBGeoMapMatchedPoint * NavRoadMatch(const TB_ROAD_MATCH_RT_DATA & inRtData,
																			TBuint32                      inMaxRadius,
																			EB_TRANSP_MODE                inTransMode);

	static TBbool NavFilterFunc(TBany inData, const TBuint32 inClassID, const EB_GEOTYPE inType);
	static void   NavObjectFunc(TBany inData, const TB_FORM_PARAMETERS& inFrmParam, const TBuint16 inNbAtt);
	static void   NavOpenFunc  (TBany inData, const TB_RENDERPOINT& inPoint, const EB_ORDER& inOrder);

	void FindNavMatch(const TB_2D_LONGPOINT& inGeoPoint,
					 					TBuint32               inMaxRadius,
										TBuint32               inRouteClassID,
										TBany                  inItem);

	CBGeoMapMatchedPoint * NavRoadMatch(const TB_ROAD_MATCH_RT_DATA & inRtData,
																			TBuint32                      inMaxRadius,
																			TBuint32                      inRouteClassID,
																			EB_TRANSP_MODE                inTransMode,
																			TBbool                      & outOnRoute);
#endif

	TBbool SetAdditionalData(CBGeoMapMatchedPoint * ioMatchedPt,
													 TBbool                 inGetAdminPath,
													 EB_LANGUAGE_CODE       inLanguageCode) const;

	void SetStreetNum(TBuint16 left1,	 TBuint16 left2, TBuint16 right1, TBuint16 right2,
										const TB_2D_FORM * frm, CBGeoMapMatchedPoint * ioMatchedPt) const;

	void SetStreetNum(TBuint16 left1,	 TBuint16 left2, TBuint16 right1, TBuint16 right2,
										const TB_2D_FORM * frm, TBany ioData) const;

private:

  CBSVSMgr * mSVSMgr;
  CBCursor * mCursor;
	
  friend class CBGuidanceImp;
};

#endif /* _CBGEO_DECODER_H_ */

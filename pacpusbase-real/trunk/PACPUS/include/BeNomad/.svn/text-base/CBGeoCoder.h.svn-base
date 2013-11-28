/*==========================================================  (-*- C++ -*-)
 *
 * @file CBGeoCoder.h
 *
 * @version  $Id: CBGeoCoder.h,v 1.50 2006/05/03 17:47:15 dlabrousse Exp $
 *
 * @author  William Kunkel
 *
 * @copyright  (c) 2002-2005 BeNomad S.A.R.L., All Rights Reserved
 *
 * BeNomad confidential file protected by international copyright laws
 * UNAUTHORIZED ACCESS, USE, REPRODUCTION OR DISTRIBUTION IS PROHIBITED.
 *
 *========================================================================*/

#ifndef _CBGEO_CODER_H_
#define _CBGEO_CODER_H_

/*!
  @file CBGeoCoder.h
	CBGeoCoder class definition.
*/

#include "CBObserver.h"
#include "CBVector.h"
#include "BGeoTypes.h"
#include "CBHashMapIter.h"

#if defined(_BMT_SAFE)
#  include "CBMutex.h"
#endif

// Forward declarations
class CBSVS;
class CBForm2D;
class CBCursor;
class CBAttCursor;
class CBSVSMgr;
class CBHashMap;
class CBGeoStreetNumber;
class CBCityFinder;

/**
 * @class CBGeoCoder
 * <B>Definition :</B>Geocoding is the process of converting textual addresses into geographical coordinates
 * (Lat/Long coordinates).
 *
 * This class provides methods that allow you to perform geocoding operations starting from a textual criteria
 * and possibly a restriction on the zone of research (within a particular administrative boundary).
 * 
 * @note Multithreading support : The CBGeoCoder class is compatible with multithreaded applications
 * but not thread-safe ! This means that two or more CBGeoCoder objects can be run simultaneously
 * in separate threads but multiple threads should not invoke methods of a CBGeoCoder object at the same time.
 * To enable multithreading support you should compile with the macro _BMT_SAFE defined and link
 * against the suitable library or DLL.
 *
 * @note All Geocoding operations require that SVS files contain geocoding data (i.e relations
 * between administrative boundaries).
 */
class BGEO_EXPORT CBGeoCoder : public CBObserver
{
public:

  /**
   * \enum EB_SEARCH_TYPE
   * This enumeration defines all the possible types of research that can be applied
   * to a textual pattern (see #Find method).
   * @since v1.7.0 New EB_FUZZY and EB_FUZZY_MORE search types which provide Fuzzy Searching
   * capabilities (two fuzziness levels) for searching text that may contain misspelled words.
   */
  enum EB_SEARCH_TYPE {
    EB_STRICT            = 0, //!< Required strings must be strictly equal to the pattern
    EB_STRICT_BEGINNING  = 1, //!< Required strings must begin with the pattern
    EB_CONTAINS          = 2, //!< The pattern must be contained in the required strings
    EB_ALL               = 3, //!< All strings are returned (pattern is not taken into account)
    EB_FUZZY             = 4, //!< Specifies a fuzzy search based on the given pattern.
    EB_FUZZY_MORE        = 5  //!< Specifies a fuzzy search based on the given pattern (Contrary to the EB_FUZZY type, this search type tries to look for the maximum number of similar strings).
  };

  /**
   * Constructs a new CBGeoCoder.
   * @param inSVSMgr The SVS Manager that contains geographical SVS data
   */
  CBGeoCoder (CBSVSMgr * inSVSMgr);

  /**
   * Destructor
   */
  ~CBGeoCoder (void);

  /**
   * Sets an explicit geographical restriction on the zone of research (e.g To locate geographical
   * elements that intersect the given area). This restriction can be removed or changed respectively
   * by the #Reset or #Find methods.
   * @param inRect The geographical area.
   */
  void SetAreaRestriction(const TB_2D_LONGRECT & inRect);

  /**
   * This method allows you to parametrize the #Find method in order to minimize the memory used
   * by the geocoding process.
   * @param inMaxNbItems The maximum number of items to search (The value -1 specifies no limit).
   * @param inGetFormParameters A flag that indicates if the geometric description of each
   * geographical element (See #TB_FORM_PARAMETERS) must be retrieved or not. If \c false, the
   * TB_GEOCODER_ITEM_DATA::mObjs member will remain to \c null.
   */
  inline void SetFindOptions(TBuint32 inMaxNbItems        = (TBuint32) -1,
                             TBbool   inGetFormParameters = true)
  {
    mMaxNbItems    = inMaxNbItems;
    mGetFormParams = inGetFormParameters;
  }

  /**
   * Returns the current Find options.
   * @param outMaxNbItems The maximum number of items to search (The value -1 specifies no limit).
   * @param outGetFormParameters A flag that indicates if the geometric description of each
   * geographical element (See #TB_FORM_PARAMETERS) must be retrieved or not. If \c false, the
   * TB_GEOCODER_ITEM_DATA::mObjs member will remain to \c null.
   */
  inline void GetFindOptions(TBuint32 & outMaxNbItems, TBbool & outGetFormParameters)
  {
    outMaxNbItems        = mMaxNbItems;
    outGetFormParameters = mGetFormParams;
  }

  /**
   * Assigns a preferential language code for address lookup.
	 * @note Objects for which defined language code is not available, default language
   * will be used (attribute code #KB_ATT_NAME).
   * @param inLanguageCode Language code to use (see #EB_LANGUAGE_CODE).
   */
  inline void SetLanguageCode(EB_LANGUAGE_CODE inLanguageCode = DEFAULT_LANGUAGE) { mLang = inLanguageCode; }


  /**
   * Returns the character encoding used for geo-coding operations. This concerns both resulting strings
   * (see #TB_ADMIN_AREA.mName, #TB_GEOCODER_ITEM_DATA.mName) and the search pattern you must specify to
   * the #Find method.
   * @note The character encoding depends on the SVS source datasets (default is ISO-8859-1).
   * @since 1.7.0 Creation.
   */
  inline EB_ENCODING GetEncoding(void) const { return mEncoding; }

  /**
   * This method allows you to locate geographical elements according to five criteria :
   *
   * - A textual pattern,
   * - The type of research applied to the pattern (see #EB_SEARCH_TYPE),
   * - The nature of the required elements (It acts like a filter on SVS Class IDs),
   * - An implicit criteria based on a geographical restriction on the zone of research.
   *
   * @note The BCartoConst.h file contains all the Class IDs constants related to geographical data.
   * @note It is strongly recommended to restrict any research within an administrative boundary and/or to use
   * the #SetFindOptions method. Indeed, the number of geographical elements can be consequent (up to several
   * thousands) and may cause memory overflow. In addition, applying a geographical restriction speeds up
   * the processing time.
   *
   * @param inPattern The pattern to search
   * @param inSearchType The type of research
   * @param inClassMatchFunc A user Class IDs filter (See #BClassMatchingFunc);
   * @param inClassMatchUserData An optional user data to pass to the Class IDs filter.
   * @param inAutomaticRestriction A flag that indicates if this method must restrict
   * next research to the area relative to an administravive boundary. This means that this
   * restriction will apply only if this method returns only one geographical element defining
   * an administravive boundary.
	 * @note If desired language is not available, default language (depending on country) will be used.
   * @return The number of geographical items found. If the real number of matching items exceeds
   * the maximum number of items you want to retrieve (See #SetFindOptions), this method returns
   * 'MaxNbItems' + 1.
   */
  TBuint32 Find (const TBint8         * inPattern,
                 const EB_SEARCH_TYPE & inSearchType,
                 BClassMatchingFunc     inClassMatchFunc,
                 TBany                  inClassMatchUserData   = NULL,
                 TBbool                 inAutomaticRestriction = true);

  /**
   * Returns the number of Postal Districts that match. You must use this method in complement
   * of the value returned by the #Find method in order to obtain the real number of Postal
   * Districts found. Contrary to other administrative areas, the relation of inclusion between
   * a postal district and its immediate upper administrative area (city or district)is not
   * a strict one-one relation but a n-n relation. For instance, a city may contain more than
   * one postal district and a unique postal district may be shared by several cities (or districts).<BR><BR>
   * Example: If you try to locate the '06500' postal code (zip code) in France, the #Find method
   * will return the value '5' whereas the #GetNbPostalDistricts will return '1'. This means that the
   * '06500' postal district is unique but shared by 5 city areas:<BR>
   * \image html 06500.jpg
   * Below the geographical view:<BR>
   * \image html pcodes.jpg
   * @return The real number of Postal Districts found.
   * @since v1.4 Creation
   */
  inline TBuint32 GetNbPostalDistricts(void) { return mNbPostalDistricts; }

  /**
   * @name Getting results (two ways)
   * If the CBGeoCoder::Find method returns at least one element, you can retrieve the results
   * by using the two following methods :
   *
   */
  //@{
  /**
   * Returns all results via a user callback. See prototype of #BGeoItemFunc for more details.
   * @param inGeoItemCbk The user callback
   * @param inUserData An optional user data to pass to the callback.
   */
  void GetResults (BGeoItemFunc inGeoItemCbk, TBany inUserData = NULL);

  /**
   * This method allows you to retrieve results in an iterative way. All found geographical elements
   * are gathered according to the smallest known administrative boundary. In general, this regrouping
   * is carried out on city boundaries (districts sometimes) for all road network objects and POIs.
   * @param outPath A pointer to a vector of #TB_ADMIN_AREA structures or \c null if there is no upper
   * administrative boundary (e.g In the case of a research on the countries). This vector defines a hierarchical
   * path up to the smallest known administrative boundary that contains the found elements.
   * @param outGeoItems A vector of #TB_GEOCODER_ITEM_DATA structures. This vector contains one TB_GEOCODER_ITEM_DATA
   * description for each found element.
   * @return \c false if there is no more element, \c true otherwise.
   */
  TBbool NextResult (const CBVector *& outPath, CBVector& outGeoItems);

  /**
   * Reinitializes the internal result iterator such that you can retrieve all the results more than once via
   * the #NextResult method.
   */
  void ResetResultIterator (void);

  //@}

  /**
   * Reinitializes the CBGeoCoder object by releasing all the resources allocated by the #Find method,
   * and optionaly by removing the geographical restriction.
   * @param inRemoveAreaRestriction A flag that indicates whether a previous geographical
   * restriction must be removed or not.
   * @note An internal Reset(false) is also done by the #Find method.
   */
  void Reset (TBbool inRemoveAreaRestriction = true);

  /**
   * Following an operation of geocoding on "Road Network" elements, the FindStreetNumber
   * method makes it possible to locate precisely the x and y geographical coordinates
   * of a Street Number (House Number).
   * @param inFormParams An array of #TB_FORM_PARAMETERS structures resulting from a geocoding process.
   * @param inNbForms The number of #TB_FORM_PARAMETERS structures contained in the array.
   * @param inStreetNumber The Street Number to locate.
   * @return A valid CBGeoStreetNumber instance or \c NULL if an error occurs (It's up to the caller to
   * delete the returned object).
   * @since v1.3
   */
  CBGeoStreetNumber * FindStreetNumber (const TB_FORM_PARAMETERS * inFormParams,
                                        TBuint32                   inNbForms,
                                        TBuint16                   inStreetNumber);

  /** 
   * @example geocoding.cpp
   * This is an example of how to perform geocoding operations.
   */

protected:

  inline CBSVSMgr * GetSVSMgr(void) { return mSVSMgr; }  

  void Update(CBSubject * inChangedSubject, TBuint32 inEventType, TBany inUserData=NULL);

#if defined(_BMT_SAFE)
  void Lock(void);
  void Unlock(void);
#endif

  static TBbool ClassFilterCbk    (TBany inData, const TBuint32 inClassID, const EB_GEOTYPE inType);
  static void   ObjectFilterCbk   (TBany inData, const TB_FORM_PARAMETERS& inFormParam, const TBuint16 inNbAtt);
  static TBbool AttributeFilterCbk(TBany inData, CBAttCursor& inAttCursor);
//   static TBbool AttributeFilterCbk(TBany inData, const TB_ATTRIBUTE& inAtt, const EB_ORDER& inOrder);
  static void ProcessOpenCbk      (TBany inData, const TB_RENDERPOINT& inPoint, const EB_ORDER& inOrder);
  static void ProcessClosedCbk    (TBany inData, const TB_RENDERPOINT& inPoint, const EB_ORDER& inOrder);
  static void ProcessPointCbk     (TBany inData, const TB_2D_LONGPOINT& inPoint);
  static void ProcessRectCbk      (TBany inData, const TB_2D_LONGRECT& inRect);
  static void ProcessArcCbk       (TBany inData, const TB_2D_ARC& inArc);
  static void BuildHierarchies    (TBany inCursorCtxt);
  static void BuildHierarchy      (TBany inCursorCtxt);

  static void PathsCleanUpFunc    (TBany key, TBany value, TBany userArg);
  static void GetAllPathsFunc     (TBany key, TBany value, TBany userArg);
  static void GetAllGeoItemsFunc  (TBany key, TBany value, TBany userArg);
  static void GetGeoItemsFunc     (TBany key, TBany value, TBany userArg);

  static void SetUpperAreaCbk     (const CBVector              * inPath,
                                   const TB_GEOCODER_ITEM_DATA & inGeoItem,
                                   TBany                         inUserData);

private:

	TBuint16 GetCost(TBint32 inNum1, TBint32 inNum2, TBint32 inNum) const;

  void SetPostalCode(const CBForm2D * inForm, TBbool inLeftSide);

  /**
   * \enum EB_SN_STATUS
   * This enumeration defines all the possible values retuned by the #FindStreetNumber method.
   */
  enum EB_SN_STATUS {
    EB_SN_ERROR     = 0, //!< Invalid #TB_FORM_PARAMETERS argument. Only elements of the road network are allowed.
    EB_SN_FOUND     = 1, //!< The exact location of the street number was found.
    EB_SN_NOT_FOUND = 2, //!< The exact location of the street number was not found. In this case, the FindStreetNumber returns an arbitrary position on the road.
  };


  CBGeoCoder::EB_SN_STATUS FindStreetNumber(const TB_FORM_PARAMETERS * inFormParams,
                                            TBuint32                   inNbForms,
                                            TBuint16                   inStreetNumber,
                                            TB_2D_LONGPOINT          * outPt,
                                            TB_FORM_PARAMETERS       & outFormParams,
                                            TBuint32                 & outNumber);

public:

  /**
   * @struct TB_GEO_CTXT
   * \internal
   */
  struct TB_GEO_CTXT {
    TBuint32       mUpperAdminClassID;
		TBuint32       mUpperAdminKey;
		TBint8 *       mUpperPostalCode;
    TB_2D_LONGRECT mClipRegion;
  };

private:
#if defined(_BMT_SAFE)
  mutable CBMutex  mMutex;
#endif
  CBSVSMgr       * mSVSMgr;
  CBCursor       * mCursor;
  CBHashMap      * mPaths;
  CBCursor       * mPathCursor;
  TBint8         * mPCode;
  TBuint32         mNbItems;
  TBuint32         mNbPostalDistricts;
  TBany            mBestGeoItem;
  TBany            mBestAreaSet;
  TB_GEO_CTXT      mGeoCtxt;
  CBHashMapIter    mPathsIter;
  TBuint32         mMaxNbItems;
  EB_LANGUAGE_CODE mLang;
  EB_ENCODING      mEncoding;
  TBbool           mGetFormParams;  
};

#endif /* _CBGEO_CODER_H_ */

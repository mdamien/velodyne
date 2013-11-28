/*==========================================================  (-*- C++ -*-)
 *
 * @file CBAddressLocator.h
 *
 * @version  $Id: CBAddressLocator.h,v 1.15 2006/06/21 07:32:04 dlabrousse Exp $
 *
 * @author  David Labrousse
 *
 * @copyright  (c) 2002-2005 BeNomad S.A.R.L., All Rights Reserved
 *
 * BeNomad confidential file protected by international copyright laws
 * UNAUTHORIZED ACCESS, USE, REPRODUCTION OR DISTRIBUTION IS PROHIBITED.
 *
 *========================================================================*/

#ifndef _CBADDR_LOCATOR_H_
#define _CBADDR_LOCATOR_H_

/*!
  @file CBAddressLocator.h
	CBAddressLocator class definition.
*/

#include "BTypes.h"
#include "BCartoConst.h"
#include "CBObserver.h"
#include "CBVector.h"
#include "BGeoTypes.h"

#if defined(_BMT_SAFE)
#  include "CBMutex.h"
#endif


#define KB_MAX_ADDRESS_MATCHES 1000

// Forward declarations
class CBSVSMgr;
class CBMemory;
class CBGeoStreetNumber;
class CBPatternMatching;
class CBGeoMapMatchedPoint;

struct TB_SAVE_DATA;
struct TB_LOC_ITEM;

/**
 * @class CBAddressLocator
 *
 * This class provides methods that allow you to perform address location based on a country, a city (any settlement) or a postal district,
 * a road (or street) and a street address number or a POI (Point of Interest). It is designed to provide user with a list of solutoins
 * each time a new letter is added to the pattern. This class is a friendly user, specialized geo-coder (see class #CBGeoCoder).
 *
 * This class should be used the following way :
 * 0. Set a user pattern to an empty string.
 * 1. Call #FindCountry each time user adds a new letter to the pattern (or if pattern is modified in any way)
 * 2. Call #Select when user selects one of returned matches and reset user's pattern to empty string
 * 3. Call #FindCity or #FindPostal each time user adds a new letter to the pattern  (or if pattern is modified in any way)
 * 4. Call #Select when user selects one of returned matches and reset user's pattern to empty string
 * 5. Call #FindRoad or #FindPOI each time user adds a new letter to the pattern  (or if pattern is modified in any way)
 * 6. Call #Select when user selects one of returned matches and reset user's pattern to empty string
 * 7. If #FindRoad in step 5 : call #FindNumberPos with user's desired street address number or
 *                             call #FindCrossRoad to find intersecting roads + call #Select + call #FindCrossPos to get intersection position
 *    If #FindPOI in step 5  : call #FindPOIPos to map match selected POI on nearest road.
 * 
 * @note:
 *  -# Pattern matching is first based on #CBGeoCoder::EB_STRICT_BEGINNING and secondly on #CBGeoCoder::EB_CONTAINS (except for 
 * postal districts and only if the number of matches is smaller than the specified maximum number of desired matches).
 *  -# Matches are sorted by alphabetical order for each type of pattern matching
 *  -# For cities' search, this class uses additional files (one per country and per language code) named XXX-YY.cty where XXX is
 * the ISO_3166 alpha-3 country code and YY is the language code (see #EB_LANGUAGE_CODE).
 *  -# For postal districts' search, this class uses additional files (one per country) named XXX.psd where XXX is
 * the ISO_3166 alpha-3 country code.
 *  -# The number of desired matches is bounded by #KB_MAX_ADDRESS_MATCHES
 *
 * @since 1.7.1 creation
 */
class BGEO_EXPORT CBAddressLocator : public CBObserver
{
public:

  /**
    * @enum EB_ERROR
    * This enum defines all the possible errors than can occur while using methods of this class.
    * @since v1.8.1 Creation
    */
  enum EB_ERROR {
    NONE                        =  0, //!< No error
		NOT_ENOUGH_MEMORY           =  1, //!< Not enough memory
    INTERNAL_ERROR              =  2, //!< Internal error
    INVALID_PATTERN             =  3, //!< Invalid pattern
    NO_COUNTRIES                =  4, //!< No countries found in SVS pool of SVS manager
    SELECT_COUNTRY_FIRST        =  5, //!< The type of items you are searching for requires that a country be selected first
    SELECT_CITY_OR_POSTAL_FIRST =  6, //!< The type of items you are searching for requires that a city or a postal district be selected first
    SELECT_ROAD_FIRST           =  7, //!< The type of items you are searching for requires that a road be selected first
    SELECT_CROSS_ROAD_FIRST     =  8, //!< You are calling #FindCrossPos but you have not selected a cross road yet
    SELECT_POI_FIRST            =  9, //!< You are calling #FindPOIPos but you have not selected a POI yet
    INVALID_ITEM_INDEX          = 10, //!< You are trying to select an item (with #Select) with an item index greater than the number of items found
    CITY_FILE_NOT_FOUND         = 11, //!< Cannot find the city file (XXX-YY.cty)
    POSTAL_FILE_NOT_FOUND       = 12, //!< Cannot find the postal code file (XXX.psd)
    CITY_FILE_NOT_COMPATIBLE    = 13, //!< City file (XXX-YY.cty) is not compatible with SVS pool in SVS manager (Text encoding or coordinate system)
    POSTAL_FILE_NOT_COMPATIBLE  = 14  //!< Postal code file (XXX.psd) is not compatible with SVS pool in SVS manager (Text encoding or coordinate system)
  };

  /**
   * Constructs a new CBAddressLocator.
   * @param inSVSMgr The SVS Manager that contains geographical SVS data
   * @param inFilePath The path where are located the "XXX-YY.cty" and "XXX.psd" files use by #FindCity and #FindPostal methods.
   */
  CBAddressLocator(CBSVSMgr     * inSVSMgr,
                   const TBchar * inFilePath = NULL);

  /**
   * Destructor
   */
  ~CBAddressLocator();

  /**
   * This method returns \c true if after a call to one of Find methods there are more items that match than the parameter \a inMaxItems.
   * @return \c true if after a call to one of Find methods there are more items that match than the parameter \a inMaxItems, \false otherwise
   * @since v1.8.1 Creation
   */
  inline TBbool MoreItems(void) const { return mMoreItems; }

  /**
   * This method returns the last error.
   * @return Last error
   * @since v1.8.1 Creation
   */
  inline EB_ERROR GetLastError(void) const { return mError; }

  /**
   * Sets the path where are located the "XXX-YY.cty" and "XXX.psd" files use by #FindCity and #FindPostal methods.
   * @param inFilePath The path where are located the "XXX-YY.cty" and "XXX.psd" files use by #FindCity and #FindPostal methods.
   * @note You can use this method if the path has not been assigned in constructor or if path needs to be changed.
   * @since v1.8.1 Creation
   */
  void SetFilePath(const TBchar * inFilePath);

  /**
   * Assigns a preferential language code for address lookup.
	 * @note Objects for which defined language code is not available, default language
   * will be used (attribute code #KB_ATT_NAME).
   * @param inLanguageCode Language code to use (see #EB_LANGUAGE_CODE).
   */
  void SetLanguageCode(EB_LANGUAGE_CODE inLanguageCode = DEFAULT_LANGUAGE);

  /**
   * This method allows you to search a country :
   * @param inPattern The pattern to search
   * @param inMaxItems The maximum number of items to be found (bounded by #KB_MAX_ADDRESS_MATCHES)
   * @return The number of items found
   */
  TBuint32 FindCountry(const TBint8 * inPattern, TBuint32 inMaxItems);

  /**
   * Following a country selection, this method allows you to search for a city (any settlement) :
   * @param inPattern The pattern to search
   * @param inMaxItems The maximum number of items to be found (bounded by #KB_MAX_ADDRESS_MATCHES)
   * @return The number of items found
   */
  TBuint32 FindCity   (const TBint8 * inPattern, TBuint32 inMaxItems);

  /**
   * Following a country selection, this method allows you to search for a postal district
   * @param inPattern The pattern to search
   * @param inMaxItems The maximum number of items to be found (bounded by #KB_MAX_ADDRESS_MATCHES)
   * @return The number of items found
   */
  TBuint32 FindPostal  (const TBint8 * inPattern, TBuint32 inMaxItems);

  /**
   * Following a country and a city or postal district selection, this method allows you to search for a road :
   * @param inPattern The pattern to search
   * @param inMaxItems The maximum number of items to be found (bounded by #KB_MAX_ADDRESS_MATCHES)
   * @return The number of items found
   */
  TBuint32 FindRoad   (const TBint8 * inPattern, TBuint32 inMaxItems);

  /**
   * Following a country and a city selection, this method 
   * returns the x and y geographical position of the selected city's center.
   * @return A pointer on a #TB_2D_LONGPOINT structure or \c NULL if an error occured (a city has not been selected yet) 
   * @note This method is a shortcut to get to an x, y position without having so select a road/streetnumber or a POI.
   * You can use a #CBGeoDecoder to match the returned position on a neighbouring road.
   * @since v1.8.0 Creation
   */
  const TB_2D_LONGPOINT * GetCityCenter(void);

  /**
   * Following a country, a city or postal district and a road selection, this
   * method makes it possible to locate the x and y geographical position of a street address number
   * @param inNumber The street address number to locate.
   * @param outMinNumber The minimum available number (if exact number not found)
   * @param outMaxNumber The maximum available number (if exact number not found)
   * @return A valid CBGeoStreetNumber instance or \c NULL if an error occurs (it's up to the caller to delete the returned object).
   * @note If \a inNumber is 0, returns any valid CBGeoStreetNumber
   */
  CBGeoStreetNumber * FindNumberPos(TBuint32 inNumber, TBuint32& outMinNumber, TBuint32& outMaxNumber);

  /**
   * Following a country, a city or postal district and a road selection, this
   * method allows you to search for intersecting roads with selected road.
   * @param inPattern The pattern to search
   * @param inMaxItems The maximum number of items to be found (bounded by #KB_MAX_ADDRESS_MATCHES)
   * @return The number of items found
   * @since v1.8.1 Creation
   */
  TBuint32 FindCrossRoad(const TBint8 * inPattern, TBuint32 inMaxItems);

  /**
   * Following a country, a city or postal district a road selection and a cross road selection, this
   * method makes it possible to locate the x and y geographical position of intersection
   * @return A valid CBGeoMapMatchedPoint instance or \c NULL if an error occurs (it's up to the caller to delete the returned object).
   * @since v1.8.1 Creation
   */
  CBGeoMapMatchedPoint * FindCrossPos(void);

  /**
   * Following a country and a city or postal district selection, this method allows you to search for a POI (point of interest) :
   * @param inPattern The pattern to search
   * @param inMaxItems The maximum number of items to be found (bounded by #KB_MAX_ADDRESS_MATCHES)
   * @param inClassMatchFunc An optional user Class IDs filter (See #BClassMatchingFunc)
   * @param inClassMatchUserData An optional user data to pass to the Class IDs filter.
   * @return The number of items found
   */
  TBuint32 FindPOI    (const TBint8     * inPattern,
                       TBuint32           inMaxItems,
                       BClassMatchingFunc inClassMatchFunc     = NULL,
                       TBany              inClassMatchUserData = NULL);

  /**
   * Following a country, a city or postal district and a POI selection, this
   * method makes it possible to locate the nearest x and y geographical position on a road to the selected POI
   * @return A valid CBGeoMapMatchedPoint instance or \c NULL if an error occurs (it's up to the caller to delete the returned object).
   */
  CBGeoMapMatchedPoint * FindPOIPos(void);

  /**
   * Returns the number of items found in last call to one of #FindCountry, #FindCity, #FindPostal, #FindRoad or #FindPOI.
   * @return The number of items found in last call to one of #FindCountry, #FindCity, #FindPostal, #FindRoad or #FindPOI.
   */
  inline TBuint32 GetNbItems(void) const { return mNbItems; }

  /**
   * Returns the ith item's name found in last call to one of #FindCountry, #FindCity, #FindPostal, #FindRoad or #FindPOI.
   * @param inItemIdx The index of the item 
   * @return The ith item's name found in last call to one of #FindCountry, #FindCity, #FindPostal, #FindRoad or #FindPOI.
   */
  const TBint8 * GetItem(TBuint32 inItemIdx) const;

  /**
   * Returns the ith POI's classID found in last call to #FindPOI.
   * @param inItemIdx The index of the item 
   * @return The ith item's classID found in last call to #FindPOI.
   */
  const TBuint32 GetPOIClassID(TBuint32 inItemIdx) const;

  /**
   * This method selects the ith item found in last call to one of #FindCountry, #FindCity, #FindPostal, #FindRoad or #FindPOI.
   * Call this method before calling #FindCity or #FinPOstal to select a country, before #FindRoad or #FindPOI
   * to select a city or postal district or before #FindNumberPos or #FindPOIPos to select a road or a POI.
   * @param inItemIdx The index of the item to select
   * @return \c false if an error occured, \c true otherwise.
   */
  TBbool Select(TBuint32 inItemIdx);

protected:

  void Update(CBSubject * inChangedSubject, TBuint32 inEventType, TBany inUserData=NULL);

#if defined(_BMT_SAFE)
  void Lock(void);
  void Unlock(void);
#endif

private:

  TBuint32 Error(EB_ERROR inError);

  void ClearContext(void);

  TBbool CheckPrevItems(const TBuint8           * pattern,
                        TBuint16                  len,
                        const CBPatternMatching * patMatching,
                        TBuint32                  inMaxItems);

  void InsertPoint(const TB_2D_LONGPOINT& p);

  TBuint32 Find(TBuint8            inStatus,
                const TBint8     * inPattern,
                TBuint32           inMaxItems,
                BClassMatchingFunc inClassMatchFunc     = NULL,
                TBany              inClassMatchUserData = NULL);

  CBGeoStreetNumber * FindStrNumber(TB_LOC_ITEM * slc,
                                    TBuint32  inNumber,
                                    TBuint32& outMinNumber,
                                    TBuint32& outMaxNumber,
                                    TBuint32& outNb);

  void Reset(void);

  TBbool SelectCity  (TBuint32 inItemIdx);

  TBbool SelectPostal(TBuint32 inItemIdx);

  TBbool OpenCityFile  (void);

  TBbool OpenPostalFile(void);

  TBbool CheckFileValidity(TBany inFile);

private:

  /**
   * @struct TB_LOC_CTXT
   * \internal
   */
  struct TB_LOC_CTXT {
		CBVector     *  mAdminKeyes;
		TBint8       *  mPostalCode;
    TB_2D_LONGRECT  mClipRegion;
  };

#if defined(_BMT_SAFE)
  mutable CBMutex   mMutex;
#endif

  TBuint8           mStatus;
  TBbool            mResetCountries;
  TBbool            mMoreItems;
  TBint8          * mCountryCode;
  TBchar          * mFilePath;
  TB_SAVE_DATA    * mSaveData;
  TBuint32          mNbItems;
  TBuint32          mVersion;
  CBSVS           * mCityFile;
  CBSVS           * mPostalFile;
  CBSVSMgr        * mSVSMgr;
  CBMemory        * mMemory;
  CBVector          mCountries;
  TB_LOC_ITEM     * mItems;
  TBuint32          mSelectedItemIdx;
  EB_LANGUAGE_CODE  mLang;
  EB_LANGUAGE_CODE  mCityLang;
  EB_ENCODING       mEncoding;
  TB_LOC_CTXT       mLocCtxt;
  TBany             mBTree;
  TBany             mRoot;
  TBuint32          mNbCrossPt;
  CBVector        * mCrossParam;
  TB_2D_LONGRECT    mCrossBRect;
  EB_ERROR          mError;
  TB_LOC_ITEM     * mSelections;
};

#endif // _CBADDR_LOCATOR_H_

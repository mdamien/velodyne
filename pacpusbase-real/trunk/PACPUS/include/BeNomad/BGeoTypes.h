/*==========================================================  (-*- C++ -*-)
 *
 * @file BGeoTypes.h
 * 
 * @version  $Id: BGeoTypes.h,v 1.35 2005/05/17 16:12:12 wkunkel Exp $ 
 * 
 * @author  William Kunkel
 *
 * @copyright  (c) 2002-2003 BeNomad S.A.R.L., All Rights Reserved
 *
 * BeNomad confidential file protected by international copyright laws
 * UNAUTHORIZED ACCESS, USE, REPRODUCTION OR DISTRIBUTION IS PROHIBITED.
 *
 *========================================================================*/

#ifndef _BGEO_TYPES_H_
#define _BGEO_TYPES_H_

#include "BTypes.h"
#include "CBSVS.h"
#include "BCartoConst.h"

/*!
  @file BGeoTypes.h
	Definition of structures and prototypes used by the geo-coding part of the SDK.
*/

// Forward declaration
class CBVector;
 
/**
 * @name Class IDs filter
 */
//@{
/**
 * \typedef BClassMatchingFunc
 * This typedef defines the prototype of a "Class ID" filter.
 * @note See BCartoConst.h file to implement your own cartographic class filters.
 * @param The current Class ID
 * @param A user data.
 * @return \c true to allow parsing of elements of the given Class ID, \c false otherwise.
 */
typedef TBbool (*BClassMatchingFunc)(const TBuint32 inClassID, TBany inUserData);
//@}

/**
 * @struct TB_ADMIN_AREA
 * A structure that contains all the informations related to an administrative area (boundary).
 */
struct TB_ADMIN_AREA {
  TBuint32        mKey;     //!< Unique identifier associated with this administrative boundary.
  TBuint32        mClassID; //!< The class ID this element belongs to.
  const TBint8 *  mName;    //!< Name of this administrative area.
};


/**
 * @struct TB_GEOCODER_ITEM_DATA
 * A structure that contains all the informations related to a geographical element 
 * resulting from a geo-coding process.
 * @see #BTranslateGeoCoderItem
 */
struct TB_GEOCODER_ITEM_DATA {
  TB_2D_LONGRECT   mBRect;   //!< Global bounding rect of the geographical element.
  const TBint8   * mName;    //!< Geographical element's name.
  const CBVector * mObjs;    //!< A vector of #TB_FORM_PARAMETERS structures. A single geographical element may be composed of multiple geometric forms.
  TBuint32         mClassID; //!< The class ID this element belongs to.
};
 

/**
 * \typedef BGeoItemFunc
 * This typedef defines the prototype of the user callback used by the CBGeoCoder::GetResults method
 * to return geo-coding results. This callback is called on each result (geographical elements are not
 * gathered compared to the smallest known administrative boundary). However, you can test the equality between
 * two \a inPath pointers (hierarchical path) to determine whether two geographical elements belong to the same administrative
 * boundary.
 * @param inPath The hierarchical path represented as a pointer to a vector of #TB_ADMIN_AREA structures (or \c null).
 * @param inGeoItem A #TB_GEOCODER_ITEM_DATA structure which describes the current geographical element.
 * @param inUserData A user data.
 */
typedef void (*BGeoItemFunc) (const CBVector              * inPath, 
                              const TB_GEOCODER_ITEM_DATA & inGeoItem,
                              TBany                         inUserData);

/**
 * \typedef BAttCodeMatchingFunc
 * This typedef defines the prototype of the user callback used by the CBGeoDecoder::Find method to 
 * filter the SVS attributes.
 * @note See BCartoConst.h file to all reserved attribute codes.
 * @param inAttCode The current attribute's code to check.
 * @param inUserData A user data.
 */
typedef TBbool (*BAttCodeMatchingFunc)(const TBuint16 inAttCode, TBany inUserData);


/**
 * @struct TB_GEODECODER_ITEM_DATA
 * A structure that contains all the informations related to SVS attributes  
 * resulting from a call to the CBGeoDecoder::Find method.
 * @note It's up to the caller to free the array of #TB_ATTRIBUTE structures and its internal 
 * string attributes (type: #EB_ATTTYPE_ALPHA) by using the #BCleanupGeoCoderItemData function. 
 */
struct TB_GEODECODER_ITEM_DATA {
  TB_FORM_PARAMETERS   mFormParam;  //!< A TB_FORM_PARAMETERS structure which allows you to identify the corresponding geographical element.
  TBuint32             mClassID;    //!< The Class ID of which this element belongs.
  TB_ATTRIBUTE       * mAtts;       //!< Array of filtered attributes. 
  TBuint16             mNbAtts;     //!< The number of filtered attributes carried by this element.
};


/**
 * Helper function that cleanups all attributes of a #TB_GEODECODER_ITEM_DATA structure.
 * @note On windows platforms you must not delete the internal array of TB_ATTRIBUTE elements yourself
 * since these blocks of memory has been allocated within the local heap of the SIV DLL and not the
 * local heap of your application. Freeing a memory block that has been allocated from a different heap
 * can lead your application to crash (i.e _CrtIsValidHeapPointer assertion) if your application is not 
 * linked against the msvcrt.dll C Run-time library.
 * @since v1.5.2 Creation.
 */
extern "C" BGEO_EXPORT void BCleanupGeoCoderItemData(TB_GEODECODER_ITEM_DATA & ioData);


/**
 * @enum EB_TRANSP_MODE
 * This enum defines all the possible transportation modes.
 */
enum EB_TRANSP_MODE {
  EB_PEDESTRIAN     = 0, //!< Pedestrian
	EB_PASSENGER_CAR  = 1, //!< Passenger car (tourist car)
	EB_TAXI           = 2, //!< Taxi
	EB_PUBLIC_BUS     = 3, //!< Public bus
	EB_DELIVERY_TRUCK = 4, //!< Delivery truck
	EB_BICYCLE        = 5, //!< Bicycle
  EB_EMERGENCY_VEH  = 6  //!< Emergency vehicle
};


/**
 * @struct TB_ROAD_MATCH_RT_DATA
 * A structure that contains real-time GPS measuring data used for road-matching.
 * (See CBGeoDecoder::RoadMatch).
 */
struct TB_ROAD_MATCH_RT_DATA {  // RT_DATA for real-time data   
  TBint16         mNumSat;   //!< Number of GPS satellites (not used).
  TBint16         mAngle;    //!< GPS orientation measure in degrees (clock-wise)
  TBuint32        mSpeed;    //!< GPS speed measure in km/h (if set to 0, \a angle will not be used for map-matching)
  TB_2D_LONGPOINT mGPSPoint; //!< GPS position measure
};

#endif /* _BGEO_TYPES_H_ */

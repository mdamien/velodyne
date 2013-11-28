/*==========================================================  (-*- C++ -*-)
 *
 * @file CBGeoMapMatchedPoint.h
 * 
 * @version  $Id: CBGeoMapMatchedPoint.h,v 1.12 2006/03/02 14:22:33 dlabrousse Exp $ 
 * 
 * @author  William Kunkel
 *
 * @copyright  (c) 2002-2006 BeNomad S.A.R.L., All Rights Reserved
 *
 * BeNomad confidential file protected by international copyright laws
 * UNAUTHORIZED ACCESS, USE, REPRODUCTION OR DISTRIBUTION IS PROHIBITED.
 *
 *========================================================================*/

#ifndef _CBGEO_MAPMATCHED_POINT_H_
#define _CBGEO_MAPMATCHED_POINT_H_

/*!
  @file CBGeoMapMatchedPoint.h
	CBGeoMapMatchedPoint class definition.
*/

#include "CBGeoRoadLocation.h"

// Forward declarations
class CBVector;

/**
 * @class CBGeoMapMatchedPoint
 * Encapsulates the result of a Map-Matching operation.  
 * @since v1.3 Creation
 */
class BGEO_EXPORT CBGeoMapMatchedPoint : public CBGeoRoadLocation
{
public:

  /**
   * @enum EB_SIDE_OF_ROAD
   * Defines all the possible position of a non Map-Matched point in relation to
   * a road segment.
   */
  enum EB_SIDE_OF_ROAD {
    LEFT   = -1,
    MIDDLE =  0,
    RIGHT  =  1
  };

  /**
   * Destructor
   */
  ~CBGeoMapMatchedPoint(void);
  
  /**
   * Returns the name of the road.
   * @return The name of the road.
   */
  inline const TBint8 * GetName(void) const { return mName; }

  /**
   * Returns the Route Number of the road (if any).
   * @return The Route Number of the road.
   * @since v1.8.0
   */
  inline const TBint8 * GetRouteNumber(void) const { return mRN; }

  /**
   * Returns a value of confidence on result in range [0, 1]. Value 0 means
   * that road matching has failed (no road element found), value 1 is best confidence.
   * Values over 0.5 should be considered as trustful.   
   */
  inline TBdouble GetConfidenceValue(void) const { return mConfValue; }

  /**
   * Returns side of the road element the point before match was (see #EB_SIDE_OF_ROAD).
   * @return side of the road element the point before match was.
   */
  inline EB_SIDE_OF_ROAD GetSide(void) const { return mSide; }

  /**
   * Returns maximum speed (in km/h) authorized on road element or 0 if not available.
   * @return maximum speed (in km/h) authorized on road element or 0 if not available.
   */
  inline TBuint16 GetMaxSpeed(void) const { return mMaxSpeed; }

  /**
   * Returns the Left Street Number (House Number) if any (!= 0)
   * @return The Left Street Number (House Number) if any (!= 0)
   */
  inline TBuint16 GetLeftStreetNum(void) const { return mLStreetNum; }

  /**
   * Returns the Left Postal Code (Zip Code) if any, \c NULL otherwise.
   * @return The Left Postal Code (Zip Code) if any, \c NULL otherwise.
   */
  inline const TBint8 * GetLeftPostalCode(void) const { return mLPCode; }

  /**
   * Returns the optional left hierarchical path if any, \c NULL otherwise.
   * @return The left hierarchical path represented as a pointer to a vector
   * of #TB_ADMIN_AREA structures (or \c null).
   */
  inline const CBVector * GetLeftPath(void) const { return mLPath; }

   /**
   * Returns the Right Street Number (House Number) if any and different 
   * from the the left side.
   * @return The Right Street Number (House Number) if any and different 
   * from the the left side.
   */
  inline TBuint16 GetRightStreetNum(void) const { return mRStreetNum; }

   /**
   * Returns the Right Postal Code (Zip Code) if any and different 
   * from the the left side.
   * @return The Right Postal Code (Zip Code) if any and different 
   * from the the left side.
   */
  inline const TBint8 * GetRightPostalCode(void) const { return mRPCode; }

  /**
   * Returns the optional right hierarchical path if any, \c NULL otherwise.
   * @return The left hierarchical path represented as a pointer to a vector
   * of #TB_ADMIN_AREA structures (or \c null).
   */
  inline const CBVector * GetRightPath(void) const { return mRPath; }

protected:
	
  /**
   * @internal
   */
  CBGeoMapMatchedPoint(const CBGeoRoadLocation& inRoadLocation);

private:

  // Disabled default ctor
  CBGeoMapMatchedPoint(void);

  // Disable copy ctor
  CBGeoMapMatchedPoint(const CBGeoMapMatchedPoint&);
  CBGeoMapMatchedPoint & operator=(const CBGeoMapMatchedPoint&);

  CBGeoMapMatchedPoint(const TB_FORM_PARAMETERS & inFormParam,
                       const TB_2D_LONGPOINT    & inPoint,
	                     TBint16                    inAngle,
                       EB_SIDE_OF_ROAD            inSideOfRoad);
   
  CBGeoMapMatchedPoint(const TB_FORM_PARAMETERS & inFormParam,
                       const TB_2D_DBLPOINT     & inPoint,
	                     TBint16                    inAngle,
                       EB_SIDE_OF_ROAD            inSideOfRoad);
    
  friend class CBGeoDecoder;   
  friend class CBGuidanceImp;

private:

  EB_SIDE_OF_ROAD mSide;
  TBuint16        mMaxSpeed;
  TBuint16        mLStreetNum;
  TBuint16        mRStreetNum;
  TBint8        * mName;
  TBint8        * mRN;
  TBint8        * mLPCode;
  TBint8        * mRPCode;
  CBVector      * mLPath; 
  CBVector      * mRPath;
  TBdouble        mConfValue;
};

#endif /* _CBGEO_MAPMATCHED_POINT_H_ */

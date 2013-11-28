/*==========================================================  (-*- C++ -*-)
 *
 * @file CBGeoRoadLocation.h
 * 
 * @version  $Id: CBGeoRoadLocation.h,v 1.9 2006/03/02 14:53:04 dlabrousse Exp $ 
 * 
 * @author  William Kunkel
 *
 * @copyright  (c) 2002-2004 BeNomad S.A.R.L., All Rights Reserved
 *
 * BeNomad confidential file protected by international copyright laws
 * UNAUTHORIZED ACCESS, USE, REPRODUCTION OR DISTRIBUTION IS PROHIBITED.
 *
 *========================================================================*/

#ifndef _CBGEO_ROAD_LOCATION_H_
#define _CBGEO_ROAD_LOCATION_H_

/*!
  @file CBGeoRoadLocation.h
	CBGeoRoadLocation class definition.
*/

#include "CBSVS.h"


/**
 * @class CBGeoRoadLocation 
 * A class that represents an (x,y) position on a road segment.
 * @since v1.3
 */
class BGEO_EXPORT CBGeoRoadLocation
{
public:
  
  /**
   * Constructs a new Road Location.
   * @param inFormParam Internal object identifier of a road segment
   * @param inPoint Matched 2D-coordinates point which defines the position on the road segment.
   * @param inAngle Angle of the road segment in degrees (clockwise oriented from north).
   */
  CBGeoRoadLocation(const TB_FORM_PARAMETERS & inFormParam,
                    const TB_2D_LONGPOINT    & inPoint,
										TBint16                    inAngle);
  
  /**
   * Constructs a new Road Location.
   * @param inFormParam Internal object identifier of a road segment
   * @param inPoint Matched 2D-coordinates point (double precision) which defines the position on the road segment.
   * @param inAngle Angle of the road segment in degrees (clockwise oriented from north).
   * @since v1.8.0 creation
   */
  CBGeoRoadLocation(const TB_FORM_PARAMETERS & inFormParam,
                    const TB_2D_DBLPOINT     & inPoint,
										TBint16                    inAngle);

  /**
   * Copy constructor
   */
	CBGeoRoadLocation(const CBGeoRoadLocation& inOther);

  /**
   * Destructor
   */
  virtual ~CBGeoRoadLocation(void) {}
  
  /**
   * Returns the internal object identifier of the road segment.
   * @return The internal object identifier of the road segment.
   */
  inline const TB_FORM_PARAMETERS & GetObjectID(void) const { return mFormParam; }

  /**
   * Returns the 2D-coordinates of this road location.
   * @return The 2D-coordinates of this road location.
   */
  inline const TB_2D_LONGPOINT & GetPoint(void) const { return mPoint; }

  /**
   * Returns the 2D-coordinates (\c double) of this road location.
   * @return The 2D-coordinates (\c double) of this road location.
   * @since v1.8.0 creation
   */
  inline const TB_2D_DBLPOINT & GetDblPoint(void) const { return mDblPoint; }

  /**
   * Returns angle of the road segment.
   * @return angle of the road segment.
   */
  inline TBint16 GetAngle(void) const { return mAngle; }

private:

  // Disable default ctor
  CBGeoRoadLocation(void);

protected:
	
	TBint16            mAngle;
  TB_2D_LONGPOINT    mPoint; 
  TB_FORM_PARAMETERS mFormParam;
  TB_2D_DBLPOINT     mDblPoint; 
};

#endif /* _CBGEO_ROAD_LOCATION_H_ */

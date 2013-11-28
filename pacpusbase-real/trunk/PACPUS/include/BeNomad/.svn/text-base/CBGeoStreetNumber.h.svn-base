/*==========================================================  (-*- C++ -*-)
 *
 * @file CBGeoStreetNumber.h
 * 
 * @version  $Id: CBGeoStreetNumber.h,v 1.7 2005/12/21 09:24:15 dlabrousse Exp $ 
 * 
 * @author  William Kunkel
 *
 * @copyright  (c) 2002-2005 BeNomad S.A.R.L., All Rights Reserved
 *
 * BeNomad confidential file protected by international copyright laws
 * UNAUTHORIZED ACCESS, USE, REPRODUCTION OR DISTRIBUTION IS PROHIBITED.
 *
 *========================================================================*/

#ifndef _CBGEO_STREET_NUMBER_H_
#define _CBGEO_STREET_NUMBER_H_

/*!
  @file CBGeoStreetNumber.h
	CBGeoStreetNumber class definition.
*/

#include "CBGeoRoadLocation.h"

/**
 * @class CBGeoStreetNumber 
 * Encapsulates the result of the CBGeoCoder::FindStreetNumber method.
 * @since v1.3 Creation
 */
class BGEO_EXPORT CBGeoStreetNumber : public CBGeoRoadLocation
{
public:
  
  /**
   * \internal Constructs a new CBGeoStreetNumber.
   * @param inFormParam Internal object identifier of a road segment
   * @param inPoint The 2D-coordinates which define the position on a road element.  
   * @param inExactLocation Indicates if the exact street number location was found.
   * @param inPostalCode Optional postal code
   * @param inNumber The street number (default 0)
   */
  CBGeoStreetNumber(const TB_FORM_PARAMETERS & inFormParam,
                    const TB_2D_LONGPOINT    & inPoint,
                    TBbool                     inExactLocation,
                    TBint8                   * inPostalCode = NULL,
                    TBuint32                   inNumber     = 0);
  /**
   * Destructor
   */
  virtual ~CBGeoStreetNumber(void);
  
  /**
   * Indicates if the location of this GeoStreetNumber corresponds exactly 
   * to the required street number. 
   * @return \c true if the location is exact, \c false otherwise.
   */
  inline TBbool IsExactLocation(void) const { return mExactLoc; }

  /**
   * @since v1.5
   * Returns the corresponding Postal Code if any, \c null otherwise.
   * @return The corresponding Postal Code if any, \c null otherwise.
   */
  inline const TBint8 * GetPostalCode(void) const { return mPCode; }

  /**
   * Returns the street number.
   * @return The street number.
   * @since v1.7.1 Creation
   */
  inline TBuint32 GetNumber(void) const { return mNumber; }

private:
  // Disable default ctor
  CBGeoStreetNumber(void);

private:  
  TBbool   mExactLoc;
  TBint8 * mPCode;
  TBuint32 mNumber;
  
};

#endif /* _CBGEO_STREET_NUMBER_H_ */

/*==========================================================  (-*- C++ -*-)
 *
 * @file UGeometry.h
 * 
 * @version  $Id: UGeometry.h,v 1.36 2006/06/16 15:18:47 wkunkel Exp $ 
 * 
 * @author  David Labrousse
 *
 * @copyright  (c) 2002-2003 BeNomad S.A.R.L., All Rights Reserved
 *
 * BeNomad confidential file protected by international copyright laws
 * UNAUTHORIZED ACCESS, USE, REPRODUCTION OR DISTRIBUTION IS PROHIBITED.
 *
 *========================================================================*/

#ifndef __UGEOMETRY_H__
#define __UGEOMETRY_H__

/*!
  @file UGeometry.h
	UGeometry class definition.
*/

#include "BTypes.h"
#include "BMacros.h"

class CBProjection;

/**
 * @class UGeometry
 *
 * @brief This static class provides a set of geometric operation functions 
 *
 */
class BSVS_EXPORT UGeometry
{
 public:

  /**
   * @enum
   * This enum defines all the possible positions relative to a rectangle
	 * with horizontal and verticale sides. For any given rectangle, the plan
	 * is divided in nine sub-plans defined by the four infinite lines of the
	 * rectangle. A code (zone code) is associated to each of these nine sub-plans.
	 *
	 * Zone codes :
	 * \arg                         0 : inside rectangle
	 * \arg \c Left              =  1 : left of rectangle 
	 * \arg \c Top               =  2 : above rectangle
	 * \arg \c Right             =  4 : right of rectangle
	 * \arg \c Bottom            =  8 : below rectangle
	 * \arg \c Left  | \c Top    =  3 : above, left of rectangle
	 * \arg \c Right | \c Top    =  6 : above, right of rectangle
	 * \arg \c Left  | \c Bottom =  9 : below, left of rectangle
	 * \arg \c Right | \c Bottom = 12 : below, right  of rectangle
   */
  enum {
    Left   = 1,
    Top    = 2,
    Right  = 4,
    Bottom = 8
  };

  /**
   * Returns the zone code of a 2D point with respect of a 2D rectangle.
   * @param inPoint 2D point
   * @param inRect 2D rectangle
   * @return Zone code
   */
  static TBint8 GetZoneCode(const TB_2D_LONGPOINT& inPoint,
                            const TB_2D_LONGRECT & inRect)
  {
    return (TBint8)
      (((inPoint.x < inRect.min.x) ? Left   : (inPoint.x > inRect.max.x) ? Right : 0) |
       ((inPoint.y < inRect.min.y) ? Bottom : (inPoint.y > inRect.max.y) ? Top   : 0));
  }

  /**
   * Returns the zone code of a 3D point with respect of a 2D rectangle.
	 * @note The z component of \a inPoint is not taken into account.
   * @param inPoint 3D point
   * @param inRect 2D rectangle
   * @return Zone code
   */
  static TBint8 GetZoneCode(const TB_3D_LONGPOINT& inPoint,
                            const TB_2D_LONGRECT & inRect)
  {
    return (TBint8)
      (((inPoint.x < inRect.min.x) ? Left   : (inPoint.x > inRect.max.x) ? Right : 0) |
       ((inPoint.y < inRect.min.y) ? Bottom : (inPoint.y > inRect.max.y) ? Top   : 0));
  }

  /**
   * Checks if \a inPoint is on one of \a inRect's edges.
   * @param inPoint 2D point
   * @param inRect 2D rectangle
   * @return edge's zone code or 0 if \a inPoint is not on one of \a inRect's edges.
   */
  static TBint8 IsOnEdge(const TB_2D_LONGPOINT& inPoint,
                         const TB_2D_LONGRECT & inRect)
  {
    return (TBint8)
      ((inPoint.x == inRect.min.x) ? Left   : (inPoint.x == inRect.max.x) ? Right :
       (inPoint.y == inRect.min.y) ? Bottom : (inPoint.y == inRect.max.y) ? Top   : 0);
  }

 /**
   * Returns \c true if 2D point \a inPoint belongs to 2D rectangle \a inRect
   * @param inPoint 2D point
   * @param inRect 2D rectangle
   * @return \c true if \a inPoint belongs to \a inRect, \c false otherwise.
   */
  static TBbool PointInRect(const TB_2D_LONGPOINT& inPoint,
                            const TB_2D_LONGRECT & inRect)
    {
      return inPoint.x >= inRect.min.x && inPoint.x <= inRect.max.x && inPoint.y >= inRect.min.y && inPoint.y <= inRect.max.y;
    }

  /**
   * Returns \c true if 2D point \a inPoint belongs to 3D rectangle \a inRect
   * @param inPoint 2D point
   * @param inRect 3D rectangle
   * @return \c true if \a inPoint belongs to \a inRect, \c false otherwise.
   */
  static TBbool PointInRect(const TB_2D_LONGPOINT& inPoint,
                            const TB_3D_LONGRECT & inRect)
    {
      return inPoint.x >= inRect.min.x && inPoint.x <= inRect.max.x && inPoint.y >= inRect.min.y && inPoint.y <= inRect.max.y;
    }

  /**
   * Returns \c true if 3D point \a inPoint belongs to 2D rectangle \a inRect
	 * @note The z component of \a inPoint is not taken into account.
   * @param inPoint 3D point
   * @param inRect 2D rectangle
   * @return \c true if \a inPoint belongs to \a inRect, \c false otherwise.
   */
  static TBbool PointInRect(const TB_3D_LONGPOINT& inPoint,
                            const TB_2D_LONGRECT & inRect)
    {
      return inPoint.x >= inRect.min.x && inPoint.x <= inRect.max.x && inPoint.y >= inRect.min.y && inPoint.y <= inRect.max.y;
    }

  /**
   * Returns \c true if 3D point \a inPoint belongs to 3D rectangle \a inRect
	 * @note The z component of \a inPoint is not taken into account.
   * @param inPoint 3D point
   * @param inRect 3D rectangle
   * @return \c true if \a inPoint belongs to \a inRect, \c false otherwise.
   */
  static TBbool PointInRect(const TB_3D_LONGPOINT& inPoint,
                            const TB_3D_LONGRECT & inRect)
    {
      return inPoint.x >= inRect.min.x && 
             inPoint.x <= inRect.max.x && 
             inPoint.y >= inRect.min.y && 
             inPoint.y <= inRect.max.y &&
             inPoint.z >= inRect.min.z &&
             inPoint.z <= inRect.max.z;
    }
	
  /**
   * Returns \c 0 if 2D rectangles \a inRect1 and \a inRect2 do not intersect,
	 * 2 \a if inRect1 is inside \a inRect2 and 1 in all other cases
   * @param inRect1 First 2D rectangle
   * @param inRect2 Second 2D rectangle
   * @return \c 0 if 2D rectangles \a inRect1 and \a inRect2 do not intersect,
	 * 2 \a if inRect1 is inside \a inRect2 and 1 in all other cases.
   */
	static TBuint8 RectInsideRect(const TB_2D_LONGRECT& inRect1,
                                const TB_2D_LONGRECT& inRect2);
	
  /**
   * Returns \c 0 if 3D rectangles \a inRect1 and \a inRect2 do not intersect,
	 * 2 \a if inRect1 is inside \a inRect2 and 1 in all other cases
   * @param inRect1 First 3D rectangle
   * @param inRect2 Second 3D rectangle
   * @return \c 0 if 3D rectangles \a inRect1 and \a inRect2 do not intersect,
	 * 2 \a if inRect1 is inside \a inRect2 and 1 in all other cases.
   * @note this is only a 2D check (z values are not checked)
   */
	static TBuint8 RectInsideRect(const TB_3D_LONGRECT& inRect1,
                                const TB_3D_LONGRECT& inRect2);

  /**
   * Returns \c true if 2D rectangles \a inRect1 and \a inRect2 intersect.
   * @param inRect1 First 2D rectangle
   * @param inRect2 Second 2D rectangle
   * @return \c true if \a inRect1 and \a inRect2 intersect, \c false otherwise.
   */
  static TBbool RectIntersectsRect(const TB_2D_LONGRECT& inRect1,
                                   const TB_2D_LONGRECT& inRect2);

  /**
   * Returns \c true if 3D rectangles \a inRect1 and \a inRect2 intersect.
   * @param inRect1 First 3D rectangle
   * @param inRect2 Second 3D rectangle
   * @return \c true if \a inRect1 and \a inRect2 intersect, \c false otherwise.
   */
  static TBbool RectIntersectsRect(const TB_3D_LONGRECT& inRect1,
                                   const TB_3D_LONGRECT& inRect2);

  /**
   * Returns \c true if 3D rectangles \a inRect1 and \a inRect2 intersect.
   * @param inRect1 First 3D rectangle
   * @param inRect2 Second 2D or 3D rectangle
   * @param in3D \c true if inRect2 is a 3D Rectangle, \c false otherwise
   * @return \c true if \a inRect1 and \a inRect2 intersect, \c false otherwise.
   */
  static TBbool RectIntersectsRect(const TB_2D_LONGRECT& inRect1,
                                   const TB_LONGRECT&    inRect2,
																	 TBbool                in3D = false);

  /**
   * Computes the intersection of two 2D rectangles.
   * @param inRect1 First 2D rectangle
   * @param inRect2 Second 2D rectangle
   * @param outRect Intersection 2D rectangle
   * @return \c true if \a inRect1 and \a inRect2 intersect, \c false otherwise.
   */
  static TBbool RectIntersection(const TB_2D_LONGRECT& inRect1,
                                 const TB_2D_LONGRECT& inRect2,
                                 TB_2D_LONGRECT      & outRect);

  /**
   * Computes the intersection of two 3D rectangles.
   * @param inRect1 First 3D rectangle
   * @param inRect2 Second 3D rectangle
   * @param outRect Intersection 3D rectangle
   * @return \c true if \a inRect1 and \a inRect2 intersect, \c false otherwise.
   */
  static TBbool RectIntersection(const TB_3D_LONGRECT& inRect1,
                                 const TB_3D_LONGRECT& inRect2,
                                 TB_3D_LONGRECT      & outRect);

  /**
   * Computes the intersection of a 2D and a 3D rectangle.
   * @param inRect1 First 2D rectangle
   * @param inRect2 Second 3D rectangle
   * @param outRect Intersection 2D rectangle
   * @return \c true if \a inRect1 and \a inRect2 intersect, \c false otherwise.
   */
  static TBbool RectIntersection(const TB_2D_LONGRECT& inRect1,
                                 const TB_3D_LONGRECT& inRect2,
                                 TB_2D_LONGRECT      & outRect);

  /**
   * Computes the bounding rectangle of a #TB_GEOMETRY object.
   * @param outRect Object's bounding rectangle
   * @param inGeo Geometric object
   * @param inIs3D Set to \c true if \a inGeo is a 3D geometric object and \c false otherwise (default)
   * @return \c false if an errors occurs (i.e. bad geometric type #EB_GEOTYPE_ABSTRACT)
   */
  static TBbool GetBoundingRect(TB_LONGRECT      & outRect,
                                const TB_GEOMETRY& inGeo,
                                const TBbool       inIs3D = false);

  /**
   * Computes the 2D bounding rectangle of a #TB_2D_FORM form.
   * @param inElemForm #TB_2D_FORM form
   * @param outRect Form's 2D bounding rectangle
   */
  static void GetBoundingRect(const TB_2D_FORM& inElemForm,
                              TB_2D_LONGRECT  & outRect);

  /**
   * Computes the 3D bounding rectangle of a #TB_3D_FORM form.
   * @param inElemForm #TB_3D_FORM form
   * @param outRect Form's 3D bounding rectangle
   */
  static void GetBoundingRect(const TB_3D_FORM& inElemForm,
                              TB_3D_LONGRECT  & outRect);

  /**
   * Computes the 2D bounding rectangle of an array of 2D points
   * @param	inPoints Array of 2D points
   * @param	inNbPoints Number of points in array
   * @param	outRect \a inPoints' 2D bounding rectangle
   */
  static void GetBoundingRect(const TB_2D_LONGPOINT * inPoints, 
                              const TBuint32          inNbPoints,
                              TB_2D_LONGRECT        & outRect);

  /**
   * Computes the 3D bounding rectangle of an array of 3D points
   * @param	inPoints Array of 3D points
   * @param	inNbPoints Number of points in array
   * @param	outRect \a inPoints' 3D bounding rectangle
   */
  static void GetBoundingRect(const TB_3D_LONGPOINT * inPoints,
                              const TBuint32          inNbPoints,
                              TB_3D_LONGRECT        & outRect);

  /**
   * Computes the 2D bounding rectangle of an array of #TB_2D_FORM forms.
   * @param	inElemForms Array of #TB_2D_FORM forms
   * @param	inNbForm Number of #TB_2D_FORM forms in array
   * @param	outRect \a inElemForms' 2D bounding rectangle
   */
  static void GetBoundingRect(const TB_2D_FORM * inElemForms,
                              const TBuint32     inNbForm,
                              TB_2D_LONGRECT   & outRect);

  /**
   * Computes the 3D bounding rectangle of an array of #TB_3D_FORM forms.
   * @param	inElemForms Array of #TB_3D_FORM forms
   * @param	inNbForm Number of #TB_3D_FORM forms in array
   * @param	outRect \a inElemForms' 3D bounding rectangle
   */
  static void GetBoundingRect(const TB_3D_FORM * inElemForms,
                              const TBuint32     inNbForm,
                              TB_3D_LONGRECT   & outRect);

  /**
   * Computes the 2D rectangle resulting from the union of two 2D rectangles.
   * @param	inRect1 First 2D rectangle
   * @param	inRect2 Second 2D rectangle
   * @param	outRect Union of \a inRect1 and \a inRect2
   */
  static void GetRectUnion(const TB_2D_LONGRECT& inRect1,
                           const TB_2D_LONGRECT& inRect2,
                           TB_2D_LONGRECT      & outRect);

  /**
   * Computes the 3D rectangle resulting from the union of two 3D rectangles.
   * @param	inRect1 First 3D rectangle
   * @param	inRect2 Second 3D rectangle
   * @param	outRect Union of \a inRect1 and \a inRect2
   */
  static void GetRectUnion(const TB_3D_LONGRECT& inRect1,
                           const TB_3D_LONGRECT& inRect2,
                           TB_3D_LONGRECT      & outRect);

  /**
   * \internal 
   */
  static void FilterClosed(const TBdouble  & inThreshold,
                           TB_2D_LONGPOINT * inPoints,
                           TBuint32        & ioNbPoints,
                           TBuint32          inGeoScale = 0);

  /**
   * \internal 
   */
  static void FilterClosed(const TBdouble  & inThreshold,
                           TB_3D_LONGPOINT * inPoints,
                           TBuint32        & ioNbPoints,
                           TBuint32          inGeoScale = 0);

  /**
   * \internal 
   */
  static void FilterOpen(const TBdouble  & inThreshold,
                         TB_2D_LONGPOINT * inPoints,
                         TBuint32        & ioNbPoints,
                         TBuint32          inGeoScale = 0);

  /**
   * \internal 
   */
  static void FilterOpen(const TBdouble  & inThreshold,
                         TB_3D_LONGPOINT * inPoints,
                         TBuint32        & ioNbPoints,
                         TBuint32          inGeoScale = 0);

  /**
   * \internal 
   */
  static TBbool ClipLineToRect(const TB_2D_LONGRECT& inLine,
                               const TB_2D_LONGRECT& inRect,
                               TB_2D_LONGRECT      & outLine);

  /**
   * Builds from an array of \a inNbPts #TB_2D_LONGPOINT points an open #TB_2D_FORM.
	 * If necessay, will add additional intermediate vectors to \a outForm.intPoints
   * when two consecutive points are such that resulting vector components do not fit on 16 bits signed integer.
   * If \a inFilterThreshold is > 0, a Douglas-Peucker's curve simplification algorithm is
   * used for suppressing non significant points from input array. The algorithm guaranties that local error
   * resulting from filtering points is less than \a inFilterThreshold (using euclidian distance).
	 * @note \a outForm.intPoints has to be desallocated by caller using \c <tt> delete [] </tt> operator
	 * @param	inPts Array of 2D points
	 * @param inNbPts Number of 2D points in array
	 * @param inFilterThreshold Maximum error tolerance
	 * @param optimize if \c true conversion will be optimized for better SVS concision (used this only if object
   * is aimed to be written into an SVS)
	 * @param outForm Open #TB_2D_FORM
	 * @param	inGeoScale Number of SVS units per degree (only if coordinates are given in longitude/latitude system)
	 * @return\c false if \a inPts is NULL or \a inNbPts is < 2, \c true otherwise
	 */
  static TBbool ConvertPointsToOpenForm(TB_2D_LONGPOINT * inPts,
                                        TBuint32          inNbPts,
                                        const TBdouble&   inFilterThreshold,
                                        TBbool            optimize,
                                        TB_2D_FORM&       outForm,
                                        TBuint32          inGeoScale = 0);

  /**
   * Builds from an array of \a inNbPts #TB_3D_LONGPOINT points an open #TB_3D_FORM.
	 * If necessay, will add additional intermediate vectors to \a outForm.intPoints
   * when two consecutive points are such that resulting vector components do not fit on 16 bits signed integer.
   * If \a inFilterThreshold is > 0, a Douglas-Peucker's curve simplification algorithm is
   * used for suppressing non significant points from input array. The algorithm guaranties that local error
   * resulting from filtering points is less than \a inFilterThreshold (using euclidian distance).
	 * @note \a outForm.intPoints has to be desallocated by caller using \c <tt> delete [] </tt> operator
	 * @param	inPts Array of 3D points
	 * @param inNbPts Number of 3D points in array
	 * @param inFilterThreshold Maximum error tolerance
	 * @param optimize if \c true conversion will be optimized for better SVS concision (used this only if object
   * is aimed to be written into an SVS)
	 * @param outForm Open #TB_3D_FORM
	 * @param	inGeoScale Number of SVS units per degree (only if coordinates are given in longitude/latitude system)
	 * @return\c false if \a inPts is NULL or \a inNbPts is < 2, \c true otherwise
	 */
  static TBbool ConvertPointsToOpenForm(TB_3D_LONGPOINT * inPts,
                                        TBuint32          inNbPts,
                                        const TBdouble&   inFilterThreshold,
                                        TBbool            optimize,
                                        TB_3D_FORM&       outForm,
                                        TBuint32          inGeoScale = 0);

  /**
   * Builds from an array of \a inNbPts #TB_2D_LONGPOINT points an closed #TB_2D_FORM.
	 * If necessay, will add additional intermediate vectors to \a outForm.intPoints
   * when two consecutive points are such that resulting vector components do not fit on 16 bits signed integer.
   * If \a inFilterThreshold is > 0, a Douglas-Peucker's curve simplification algorithm is
   * used for suppressing non significant points from input array. The algorithm guaranties that local error
   * resulting from filtering points is less than \a inFilterThreshold (using euclidian distance).
	 * @note \a outForm.intPoints has to be desallocated by caller using \c <tt> delete [] </tt> operator
	 * @param	inPts Array of 2D points
	 * @param inNbPts Number of 2D points in array
	 * @param inFilterThreshold Maximum error tolerance
	 * @param optimize if \c true conversion will be optimized for better SVS concision (used this only if object
   * is aimed to be written into an SVS)
	 * @param outForm Closed #TB_2D_FORM
	 * @param	inGeoScale Number of SVS units per degree (only if coordinates are given in longitude/latitude system)
	 * @return\c false if \a inPts is NULL or \a inNbPts is < 2, \c true otherwise
	 */
  static TBbool ConvertPointsToClosedForm(TB_2D_LONGPOINT * inPts,
                                          TBuint32          inNbPts,
                                          const TBdouble&   inFilterThreshold,
                                          TBbool            optimize,
                                          TB_2D_FORM&       outForm,
                                          TBuint32          inGeoScale = 0);

  /**
   * Builds from an array of \a inNbPts #TB_3D_LONGPOINT points an closed #TB_3D_FORM.
	 * If necessay, will add additional intermediate vectors to \a outForm.intPoints
   * when two consecutive points are such that resulting vector components do not fit on 16 bits signed integer.
   * If \a inFilterThreshold is > 0, a Douglas-Peucker's curve simplification algorithm is
   * used for suppressing non significant points from input array. The algorithm guaranties that local error
   * resulting from filtering points is less than \a inFilterThreshold (using euclidian distance).
	 * @note \a outForm.intPoints has to be desallocated by caller using \c <tt> delete [] </tt> operator
	 * @param	inPts Array of 3D points
	 * @param inNbPts Number of 3D points in array
	 * @param inFilterThreshold Maximum error tolerance
	 * @param optimize if \c true conversion will be optimized for better SVS concision (used this only if object
   * is aimed to be written into an SVS)
	 * @param outForm Closed #TB_3D_FORM
	 * @param	inGeoScale Number of SVS units per degree (only if coordinates are given in longitude/latitude system)
	 * @return\c false if \a inPts is NULL or \a inNbPts is < 2, \c true otherwise
	 */
  static TBbool ConvertPointsToClosedForm(TB_3D_LONGPOINT * inPts,
                                          TBuint32          inNbPts,
                                          const TBdouble&   inFilterThreshold,
                                          TBbool            optimize,
                                          TB_3D_FORM&       outForm,
                                          TBuint32          inGeoScale = 0);

  /**
   * Checks if 2D point \a inPoint is inside (multiple) 2D polygon \a inGeo.
	 * If \a inGeo is composed of several polygons, this method deals with
	 * 'holes' (when one of the polygon is inside another polygon) : if \a inPoint
	 * is inside a 'hole', \a inPoint is considered outside of \a inGeo
	 * @param	inPoint 2D point
	 * @param inGeo 2D geometry
	 * @return \c false if geometric type of inGeo is different of #EB_GEOTYPE_CLOSED or if \a inPoint does not belong to \a inGeo, \c true otherwise
	 */
  static TBbool PointIn2DClosed(const TB_2D_LONGPOINT& inPoint,
                                const TB_GEOMETRY    & inGeo);

  /**
   * Checks if 3D point \a inPoint is inside (multiple) 3D polygon \a inGeo.
	 * If \a inGeo is composed of several polygons, this method deals with
	 * 'holes' (when one of the polygon is inside another polygon) : if \a inPoint
	 * is inside a 'hole', \a inPoint is considered outside of \a inGeo.
	 * @param	inPoint 3D point
	 * @param inGeo 3D geometry
	 * @return \c false if geometric type of inGeo is different of #EB_GEOTYPE_CLOSED or if \a inPoint does not belong to \a inGeo, \c true otherwise
	 */
  static TBbool PointIn3DClosed(const TB_3D_LONGPOINT& inPoint,
                                const TB_GEOMETRY    & inGeo);

  /**
   * Builds a (multiple) polygon corresponding to a corridor around an array of 2D points.
	 * Corridor width is defined by \a inDist.
	 * @param	inPoints Array of 2D points
	 * @param inNbPoints Number of 2D points in array
	 * @param inDist Corridor's width
	 * @param outGeo Corridor, a 2D (possibly a multiple) polygon (geometric type = #EB_GEOTYPE_CLOSED)
	 * @param	inGeoScale Number of SVS units per degree (only if coordinates are given in longitude/latitude system)
	 * @return \c false if inNbPoints = 0 or inPoints = NULL or inDist = 0, \c true otherwise
	 */
  static TBbool BuildZone(const TB_2D_LONGPOINT * inPoints,
                          const TBuint32          inNbPoints,
                          const TBuint16          inDist,
                          TB_GEOMETRY           & outGeo,
                          TBuint32                inGeoScale = 0);


	/**
	 * Returns the orthogonal projection of \a inPoint on segment [\a inPt1, \a inPt2].
	 * If projected point is out of segment's bounds, returns either \a inPt1 or \a inPt2
	 * according to which is closest to effective projection on line (\a inPt1, \a inPt2).
	 * @param	inPt1 First 2D point
	 * @param	inPt2 Second 2D point
	 * @param	inPoint 2D point to project
	 * @param	outPoint Projected point
	 * @param	outSquareDist Square distance between \a inPoint and \a outPoint
	 * @param	inGeoScale Number of SVS units per degree (only if coordinates are given in longitude/latitude system)
	 */
  static void GetNearestPoint(const TB_2D_LONGPOINT& inPt1,
															const TB_2D_LONGPOINT& inPt2,
								              const TB_2D_LONGPOINT& inPoint,
									            TB_2D_LONGPOINT      & outPoint,
										          TBuint32             & outSquareDist,
															TBuint32               inGeoScale = 0);

	/**
	 * Returns the orthogonal projection of \a inPoint on segment [\a inPt1, \a inPt2].
	 * If projected point is out of segment's bounds, returns either \a inPt1 or \a inPt2
	 * according to which is closest to effective projection on line (\a inPt1, \a inPt2).
	 * @param	inPt1 First 2D point
	 * @param	inPt2 Second 2D point
	 * @param	inPoint 2D point to project
	 * @param	outPoint Projected point
	 * @param	outSquareDist Square distance between \a inPoint and \a outPoint (in double precision)
	 * @param	inGeoScale Number of SVS units per degree (only if coordinates are given in longitude/latitude system)
	 */
	static void GetNearestPoint(const TB_2D_LONGPOINT& inPt1,
															const TB_2D_LONGPOINT& inPt2,
															const TB_2D_LONGPOINT& inPoint,
															TB_2D_LONGPOINT      & outPoint,
															TBdouble             & outSquareDist,
															TBuint32               inGeoScale);

	/**
	 * Returns the orthogonal projection of \a inPoint on segment [\a inPt1, \a inPt2].
	 * If projected point is out of segment's bounds, returns either \a inPt1 or \a inPt2
	 * according to which is closest to effective projection on line (\a inPt1, \a inPt2).
	 * @param	inPt1 First 2D point
	 * @param	inPt2 Second 2D point
	 * @param	inPoint 2D point to project
	 * @param	outPoint Projected point (\c double coordinates)
	 * @param	outSquareDist Square distance between \a inPoint and \a outPoint (in double precision)
	 * @param	inGeoScale Number of SVS units per degree (only if coordinates are given in longitude/latitude system)
   * @param inBounds \c true if orthogonal projection of \a inPoint is within segment's bounds, \c false otherwise
	 */
	static void GetNearestPoint(const TB_2D_LONGPOINT& inPt1,
															const TB_2D_LONGPOINT& inPt2,
															const TB_2D_LONGPOINT& inPoint,
															TB_2D_DBLPOINT       & outPoint,
															TBdouble             & outSquareDist,
															TBuint32               inGeoScale,
                              TBbool&                inBounds);

  /**
   * \internal 
   */
  static TBint32 GetIntersection(TBint32 dx,
                                 TBint32 dy,
                                 TBint32 y0);

	/**
	 * Deallocates and cleans a 2D #TB_GEOMETRY structure
	 * @param	inGeo The structure to clean
	 * @note All allocations must have been done with #BNew operator
	 */
	static void Clean2DGeometry(TB_GEOMETRY& inGeo);

	/**
	 * Deallocates and cleans a 3D #TB_GEOMETRY structure
	 * @param	inGeo The structure to clean
	 * @note All allocations must have been done with #BNew operator
	 */
	static void Clean3DGeometry(TB_GEOMETRY& inGeo);

	/**
	 * Converts 3D #TB_GEOMETRY structure into an equivalent 2D #TB_GEOMETRY structure
	 * @param	in3DGeo The 3D structure to convert
	 * @param	in2DGeo The 2D converted structure
	 * @note All allocations are done with #BNew operator
	 * @return \c false if \a in3DGeo is invalid or if not enough memory, \c true otherwise
	 */
	static TBbool ConvertIn2D(const TB_GEOMETRY& in3DGeo,
                            TB_GEOMETRY&       out2DGeo);

  /**
   * Checks if 2D point \a inPoint is inside 2D polygon \a inForm.
	 * @param	inPoint 2D point
	 * @param inForm 2D geometry
	 * @return \c false if \a inPoint does not belong to \a inForm, \c true otherwise
	 */
  static TBbool PointIn2DPolygon(const TB_2D_LONGPOINT& inPoint,
                                 const TB_2D_FORM     & inForm);

  /**
   * Checks if 3D point \a inPoint is inside 3D polygon \a inForm.
	 * @param	inPoint 3D point
	 * @param inForm 3D geometry
	 * @return \c false if \a inPoint does not belong to \a inForm, \c true otherwise
   * @note z components are ignored
	 */
  static TBbool PointIn3DPolygon(const TB_3D_LONGPOINT& inPoint,
                                 const TB_3D_FORM&      inForm);

 private:

  /**
   * \internal 
   */
  static void ShiftPolyPoints(TB_2D_LONGPOINT * inPoints,
                              TBuint32          inNbPoints,
															TBuint32          inGeoScale = 0);

  /**
   * \internal 
   */
  static void ShiftPolyPoints(TB_3D_LONGPOINT * inPoints,
                              const TBuint32    inNbPoints,
															TBuint32          inGeoScale = 0);

  /**
   * \internal 
	 */
  static TBuint32 ConvertPointsToDeltaPoints(const TB_2D_LONGPOINT * inPoints,
                                             const TBuint32          inNbIntPoints,
                                             TB_2D_DELTAPOINT     *& outDeltas,
                                             TBbool                  optimize = true);

  /**
   * \internal 
	 */
  static TBuint32 ConvertPointsToDeltaPoints(const TB_3D_LONGPOINT * inPoints,
                                             const TBuint32          inNbIntPoints,
                                             TB_3D_DELTAPOINT     *& outDeltas,
                                             TBbool                  optimize = true);

  static void GetBestBitSize(const TB_2D_LONGPOINT * inPoints,
                             TBuint32                inNbIntPoints,
                             TBint32&                outXMaxBit,
                             TBint32&                outYMaxBit);

  static void GetBestBitSize(const TB_3D_LONGPOINT * inPoints,
                             TBuint32                inNbIntPoints,
                             TBint32&                outXMaxBit,
                             TBint32&                outYMaxBit);
};

#endif // __UGEOMETRY_H__

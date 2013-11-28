/*==========================================================  (-*- C++ -*-)
 *
 * @file CBClipZone.h
 * 
 * @version  $Id: CBClipZone.h,v 1.4 2006/03/02 14:14:21 dlabrousse Exp $ 
 * 
 * @author  David Labrousse
 *
 * @copyright  (c) 2002-2003 BeNomad S.A.R.L., All Rights Reserved
 *
 * BeNomad confidential file protected by international copyright laws
 * UNAUTHORIZED ACCESS, USE, REPRODUCTION OR DISTRIBUTION IS PROHIBITED.
 *
 *========================================================================*/

#ifndef __CBCLIPZONE_H__
#define __CBCLIPZONE_H__

/*!
  @file CBClipZone.h
	CBClipZone class definition.
*/

#include "BTypes.h"
#include "BMacros.h"


/**
 * @class CBClipZone
 *
 * @brief This class defines a clipping area which can either be a 2D rectangle or a 2D convex polygon.
 *
 * CBClipZone defines a clipping area which can either be a 2D rectangle or a 2D convex polygon.
 * It allows you to :
 * 1. Define geometry of a clipping zone
 * 2. retrieve geometry of clipping zone.
 * 3. check if a given point is inside or outside clipping zone.
 * 4. check if a given line intersects clipping zone and if it does, computes line resulting from clipping.
 * 5. check if a given 2D rectangle intersects clipping zone.
 *
 * @note If clipping zone is a non-convex polygon, line clipping may not work properly.
 */
class BSVS_EXPORT CBClipZone
{
	typedef struct {
		TBuint8 count;
		TBint8  clock;
		TBuint8 stack[12];
	} TB_EDGESTACK;

public:

	/**
	 * Default constructor.
	 */
	CBClipZone(void);

	/**
	 * Constructor. Builds a CBClipZone from a 2D rectangle
	 * @param inRect 2D bounding rectangle
	 */
	CBClipZone(const TB_2D_LONGRECT& inRect);

	/**
	 * Copy constructor.
	 */
	CBClipZone(const CBClipZone&);

  CBClipZone& operator=(const CBClipZone&);

	/**
	 * Destructor.
	 */
	~CBClipZone(void);

	/**
	 * Returns 2D bounding rectangle of clip zone.
	 * @note If clip zone is a rectangular zone, clip zone's geometry resumes to returned rectangle.
	 * @return 2D bounding rectangle of clip zone.
	 */
	inline const TB_2D_LONGRECT& GetBoundingRect(void) const { return mBoundingRect; }

	/**
	 * Sets 2D bounding rectangle to clip zone.
	 * @param inRect 2D bounding rectangle
	 * @note Previous clip zone's geometry will be lost and clip zone's geometry will resume to \a inRect.
	 */
	void SetClipRect(const TB_2D_LONGRECT& inRect);

  TBint8 GetClock(TBuint16 internal = 0) const;

	/**
	 * This method allows you to retrieve clip zone's geometry. It returns coordinates of
	 * \a inPointIdx-th point.
	 * @note If clip zone is a rectangular zone and if \a inPointIdx < 4, this method returns
	 * one of clip zone's bounding rectangle corners (either in clockwise or in trigonometric
	 * order depending on x, y axis orientation).
	 * @param inPointIdx Index of point to get coordinates from
	 * @param outPoint Coordinates of clip zone's point
   * @param internal Internal parameter : do not modify default value (0).
	 * @return \c false if \a inPointIdx is >= than number of points in corresponding area, \c true otherwise.
	 */
	TBbool GetPoint(TBuint32         inPointIdx,
									TB_2D_LONGPOINT& outPoint,
                  TBuint16         internal = 0) const;

	/**
	 * This method checks intersection of \a inRect with clip zone.
	 * @param inRect The 2D rectangle to check.
	 * @return 0 if no intersection, 2 if \a inRect is fully inside clip zone (inclusion)
	 * and 1 otherwise (strict intersection)
	 */
	TBuint8 IntersectsWithRect(const TB_2D_LONGRECT& inRect) const;

	/**
	 * This method checks intersection of \a inRect with clip zone.
	 * @param inRect The 3D rectangle to check.
	 * @return 0 if no intersection, 2 if \a inRect is fully inside clip zone (inclusion)
	 * and 1 otherwise (strict intersection)
	 */
	TBuint8 IntersectsWithRect(const TB_3D_LONGRECT& inRect) const;

	/**
	 * This method checks intersection of \a inRect with clip zone.
	 * @param inRect The 2D/3D rectangle to check.
	 * @param in3D   Set to \c true if \a inRect is a 3D rectangle, false otherwise.
	 * @return 0 if no intersection, 2 if \a inRect is fully inside clip zone (inclusion)
	 * and 1 otherwise (strict intersection)
	 */
	TBuint8 IntersectsWithRect(const TB_LONGRECT& inRect,
                             TBbool             in3D) const;

	/**
	 * This method checks \a inPt is inside clip zone.
	 * @return \c true if \a inPt is inside clip zone, \c false otherwise
	 */
	TBbool ContainsPoint(const TB_2D_LONGPOINT& inPt) const;

	/**
	 * This method computes line resulting from clipping \a inLine to clipping zone.
	 * @param inMask Set to 1 (resp. 2) if \a inLine's first (resp. second) point is inside clipping zone,
   * set to 0 if both points are out (use method #ContainsPoint first).
	 * @param inLine  Line to clip
	 * @param outLine Result of \a inLine's clipping (only if \a inLine intersects clipping zone).
	 * @return \c true if \a inLine intersects clipping zone, \c false otherwise.
   * @note If clipping zone is a non-convex polygon, this method may not work properly.
	 */
	TBbool ClipLine(TBuint8               inMask,
									const TB_2D_LONGRECT& inLine,
									TB_2D_LONGRECT&       outLine) const;

	/**
	 * Adds a new point to clipZone's geometry
   * @param inPoint New point to add to geometry
   * @note There is no check that clipZone's geometry is convex. If clipZone's geometry is not convex
   * there is no guarantie for correct clipping operations.
	 */
	void AddPoint(const TB_2D_LONGPOINT& inPoint);

	/**
	 * Resets clipZone's geometry. All points are removed and bounding rectangle is set to (0, 0, 0, 0).
	 */
	void Reset(void);

	/**
	 * @internal
	 */
  TBbool ClipLine(TBuint8               inMask,
                  const TB_2D_LONGRECT& inLine,
                  TB_2D_LONGRECT&       outLine,
                  TBuint32&             outEdgeIdx1,
                  TBuint32&             outEdgeIdx2) const;

protected:

	/**
	 * @internal
	 */
	inline TBuint16 GetNbAreas(void) const { return mNbAreas; }

	/**
	 * @internal
	 */
	void AddPoint(const TB_2D_LONGPOINT& inPoint,
								TBuint16               inAreaIdx);

	/**
	 * @internal
	 */
  inline TBuint8 * GetStartCount(void) const { return mStartCount; }

	/**
	 * @internal
	 */
  inline TBuint8 * GetCount(void) const { return mCount; }

	/**
	 * @internal
	 */
  inline TBuint32 GetCountSize(void) const { return mCountSize; }

private:

	TBint8 GetClock(TBuint8                curIdx,
									TBuint8                prevIdx,
									const TB_2D_LONGPOINT& inPt,
									const TB_2D_LONGRECT&  inLine) const;
	
	void Stack(const TB_2D_LONGRECT& inLine,
						 const TB_2D_LONGRECT& inRect,
						 TB_EDGESTACK&         s) const;

	TBbool LineIntersection(const TB_2D_LONGRECT& inLine1,
													const TB_2D_LONGRECT& inBRect1,
													const TB_2D_LONGRECT& inLine2,
													TB_2D_LONGPOINT&      outPt) const;

private:

	typedef struct {
		TBuint32          nbPt;
		TB_2D_LONGPOINT * pts;
	} TB_CLIP_AREA;

	TBuint16       mNbAreas;
	TBuint16       mNbAllocatedAreas;
	TB_CLIP_AREA * mAreas;
  TBuint8      * mStartCount;
  TBuint8      * mCount;
  TBuint32       mCountSize;
	TB_2D_LONGRECT mBoundingRect;

	friend class CBGeoProjection;
	friend class CBIsoProjection;
	friend class CBClipper;
};

#endif // __CBCLIPZONE_H__

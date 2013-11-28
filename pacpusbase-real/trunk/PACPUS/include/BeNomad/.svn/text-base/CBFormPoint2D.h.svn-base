/*==========================================================  (-*- C++ -*-)
 *
 * @file CBFormPoint2D.h
 * 
 * @version  $Id: CBFormPoint2D.h,v 1.21 2006/05/03 17:45:26 dlabrousse Exp $ 
 * 
 * @author  David Labrousse
 *
 * @copyright  (c) 2002-2005 BeNomad S.A.R.L., All Rights Reserved
 *
 * BeNomad confidential file protected by international copyright laws
 * UNAUTHORIZED ACCESS, USE, REPRODUCTION OR DISTRIBUTION IS PROHIBITED.
 *
 *========================================================================*/

#ifndef __CBFORMPOINT2D_H__
#define __CBFORMPOINT2D_H__

/*!
  @file CBFormPoint2D.h
	CBFormPoint2D class definition.
*/

#include "CBForm.h"

class CBCursor;
class CBBitStream;
class CBTreeParser;

/**
 * @class CBFormPoint2D
 *
 * @brief This class defines a SVS 2D form of geometric type #EB_GEOTYPE_POINT.
 *
 * CBFormPoint2D is a class that defines a SVS 2D form of geometric type #EB_GEOTYPE_POINT.
 * This class handles form's geometry.
 *
 */
class BSVS_EXPORT CBFormPoint2D : public CBForm
{
 private:
  
  TBuint32          mSize;          //!< Form's size = max(dx, dy) where dx (resp. dy) is form's bounding rect's size in x (resp. y)
  TBuint32          mDynamicStatus; 
  TB_2D_LONGPOINT * mGeo;           //!< Form's geometry = array of #TB_2D_LONGPOINT

 public:

  /**
   * Default constructor.
   */
  CBFormPoint2D(void);

  /**
   * Constructs a CBFormPoint2D from a #TB_EXTERN_OBJECT object (see BTypes.h).
	 * Copies \a inObject's geometry into form's geometry and computes form's bounding rectangle.
   * @param inObject Object to build from
   * @param outRect  Form's bounding rectangle
   */
  CBFormPoint2D(const TB_EXTERN_OBJECT& inObject,
								TB_LONGRECT           & outRect);

  /**
   * \internal
   * Constructs a CBFormPoint2D by reading data from a SVS stream.
   * @param inBitStream SVS stream to read from
   * @param inObjectMgr Form's object manager
   * @param outRect     Form's bounding rectangle
   */
  CBFormPoint2D(CBBitStream        * inBitStream,
								const CBObjectMgr  * inObjectMgr,
                const CBTreeParser * inTreeParser,
								TB_LONGRECT        & outRect);

  /**
   * Destructor.
   */
  virtual ~CBFormPoint2D(void);

  /**
   * Copies form into a new CBFormPoint2D and returns new form.
   * @param inCopyAttributes If \c false, attributes will not be copied (only geometry)
   * @return New form
   */
  virtual CBForm * Copy(TBbool inCopyAttributes = true) const;

  /**
   * Returns form's geometric type (#EB_GEOTYPE_POINT).
   * @return #EB_GEOTYPE_POINT
   */
  virtual EB_GEOTYPE GetType(void) const
  {
    return EB_GEOTYPE_POINT;
  }

  /**
   * Is form a 3D form ? No !
   * @return \c false
   */
  TBbool Is3D(void) const
  {
    return false;
  }

  /**
   * Returns form's size = max in x,y of form's bounding rectangle.
	 * @note A point form, like all other geometric forms, can be composed of several
	 * elementary forms (i.e. a point form can be composed of several points).
	 * Therefore, form's size is not always 0.
   * @return Form's size
   */
  TBuint32 GetSize(void) const
  {
    return mSize;
  }

  TBuint32 GetOffset(void) const
  {
    return mDynamicStatus;
  }

  void SetOffset(TBuint32 inOffset)
  {
    mDynamicStatus = inOffset;
  }

  TBuint32 GetNodeIndex(void) const
  {
    return mDynamicStatus;
  }

  void SetNodeIndex(TBuint32 inIndex)
  {
    mDynamicStatus = inIndex;
  }

  /**
   * Computes form's bounding rectangle.
   * @param outRect Form's bounding rectangle
   */
  void GetBoundingRect(TB_LONGRECT& outRect) const;

	/**
   * Fills structure #TB_GEOMETRY (see BTypes.h) with form's geometry.
   * @param inGeo Form's geometry
   */
  void GetGeometry(TB_GEOMETRY& inGeo) const
  {
    inGeo.nbForm = GetNbForm();
    inGeo.g.pnt2 = mGeo;
    inGeo.type   = EB_GEOTYPE_POINT;
  }
	
  /**
   * \internal
   */
  virtual TBany GetGeo(void) const { return mGeo; }

  /**
   * Writes form into a SVS stream.
   * @param inBitStream SVS stream
   * @param inObjectMgr Form's object manager
   */
  virtual void WriteToStream(CBBitStream        * inBitStream,
                             const CBTreeParser * inTreeParser) const;

  static TB_2D_LONGPOINT * ReadGeoFromStream(CBBitStream        * inBitStream,
                                             const CBTreeParser * inTreeParser,
																						 TBuint16             inNbForm);

  static void WriteGeoToStream(CBBitStream           * inBitStream,
                               const CBTreeParser    * inTreeParser,
															 TBuint16                inNbForm,
															 const TB_2D_LONGPOINT * inGeo);

  static TBuint32 ProcessPointCallback(CBBitStream    * inBitStream,
																			 const CBCursor * inCursor);

  static void ProcessGeoPointCallback(CBBitStream    * inBitStream,
																			const CBCursor * inCursor,
																			TB_2D_LONGRECT & outBdRect);

  static void SkipGeometry(CBBitStream        * inBitStream,
                           const CBTreeParser * inTreeParser);

  virtual TBuint32 Process(const CBCursor * inCursor) const;

  static void ProcessGeoPoint(const CBCursor        * inCursor,
														  TBuint16                inNbForm,
															const TB_2D_LONGPOINT * inGeo);

protected:

  /**
   * Copy constructor.
   * @param inSource Source form
   * @param inCopyAttributes If \c false, attributes will not be copied (only geometry)
   */
  CBFormPoint2D(const CBFormPoint2D& inSource,
								TBbool               inCopyAttributes = true);

  /**
   * Assigment operator
   * @param inSource Source form
   */
  CBFormPoint2D & operator=(const CBFormPoint2D& inSource);

  void SetSize(TB_LONGRECT& outRect);

  static void ReadPoint(CBBitStream          * inBitStream,
												const TB_2D_LONGPOINT& inNodeOrigin,
												const TB_2D_BITSIZE  & inBitSize,
												TB_2D_LONGPOINT      & outPoint);
};

#endif //  __CBFORMPOINT2D_H__

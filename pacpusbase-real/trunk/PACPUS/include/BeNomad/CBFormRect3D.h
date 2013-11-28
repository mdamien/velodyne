/*==========================================================  (-*- C++ -*-)
 *
 * @file CBFormRect3D.h
 * 
 * @version  $Id: CBFormRect3D.h,v 1.21 2006/05/03 17:45:26 dlabrousse Exp $ 
 * 
 * @author  David Labrousse
 *
 * @copyright  (c) 2002-2005 BeNomad S.A.R.L., All Rights Reserved
 *
 * BeNomad confidential file protected by international copyright laws
 * UNAUTHORIZED ACCESS, USE, REPRODUCTION OR DISTRIBUTION IS PROHIBITED.
 *
 *========================================================================*/

#ifndef __CBFORMRECT3D_H__
#define __CBFORMRECT3D_H__

/*!
  @file CBFormRect3D.h
	CBFormRect3D class definition.
*/

#include "CBForm.h"

class CBCursor;
class CBBitStream;
class CBTreeParser;

/**
 * @class CBFormRect3D
 *
 * @brief This class defines a SVS 3D form of geometric type #EB_GEOTYPE_ELLIPSE.
 *
 * CBFormRect3D is a class that defines a SVS 3D form of geometric type #EB_GEOTYPE_ELLIPSE.
 * This class handles form's geometry.
 *
 */
class BSVS_EXPORT CBFormRect3D : public CBForm
{
 private:
  
  TBuint32         mSize;          //!< Form's size = max(dx, dy, dz) where dx (resp. dy, dz) is form's bounding rect's size in x (resp. y, z)
  TBuint32         mDynamicStatus; 
  TB_3D_LONGRECT * mGeo;           //!< Form's geometry = array of #TB_3D_LONGRECT

 public:

  /**
   * Default constructor.
   */
  CBFormRect3D(void);

  /**
   * Constructs a CBFormRect3D from a #TB_EXTERN_OBJECT object (see BTypes.h).
	 * Copies \a inObject's geometry into form's geometry and computes form's bounding rectangle.
   * @param inObject Object to build from
   * @param outRect  Form's bounding rectangle
   */
  CBFormRect3D(const TB_EXTERN_OBJECT& inObject,
							 TB_LONGRECT           & outRect);

  /**
   * \internal
   * Constructs a CBFormRect3D by reading data from a SVS stream.
   * @param inBitStream SVS stream to read from
   * @param inObjectMgr Form's object manager
   * @param outRect     Form's bounding rectangle
   */
  CBFormRect3D(CBBitStream        * inBitStream,
							 const CBObjectMgr  * inObjectMgr,
               const CBTreeParser * inTreeParser,
							 TB_LONGRECT        & outRect);

  /**
   * Destructor.
   */
  virtual ~CBFormRect3D(void);

  /**
   * Copies form into a new CBFormRect3D and returns new form.
   * @param inCopyAttributes If \c false, attributes will not be copied (only geometry)
   * @return New form
   */
  virtual CBForm * Copy(TBbool inCopyAttributes = true) const;

  /**
   * Returns form's geometric type (#EB_GEOTYPE_ELLIPSE).
   * @return #EB_GEOTYPE_ELLIPSE
   */
  virtual EB_GEOTYPE GetType(void) const
  {
    return (mSize & 1) != 0 ? EB_GEOTYPE_ELLIPSE : EB_GEOTYPE_RECTANGLE;
  }

  /**
   * Is form a 3D form ? Yes !
   * @return \c true
   */
  TBbool Is3D(void) const
  {
    return true;
  }

  /**
   * Returns form's size = max in x,y,z of form's bounding rectangle.
   * @return Form's size
   */
  TBuint32 GetSize(void) const
  {
    return mSize >> 1;
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
    inGeo.g.rec3 = mGeo;
    inGeo.type   = (mSize & 1) != 0 ? EB_GEOTYPE_ELLIPSE : EB_GEOTYPE_RECTANGLE;
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

  static TB_3D_LONGRECT * ReadGeoFromStream(CBBitStream        * inBitStream,
                                            const CBTreeParser * inTreeParser,
																						TBuint16             inNbForm);

  static void WriteGeoToStream(CBBitStream          * inBitStream,
                               const CBTreeParser   * inTreeParser,
															 TBuint16               inNbForm,
															 const TB_3D_LONGRECT * inGeo);

  static TBuint32 ProcessRectCallback(CBBitStream    * inBitStream,
																			const CBCursor * inCursor);

  static TBuint32 ProcessEllipseCallback(CBBitStream    * inBitStream,
																				 const CBCursor * inCursor);

  static void ProcessGeoRectCallback(CBBitStream    * inBitStream,
																		 const CBCursor * inCursor,
																		 TB_2D_LONGRECT & outBdRect);

  static void ProcessGeoEllipseCallback(CBBitStream    * inBitStream,
																				const CBCursor * inCursor,
																				TB_2D_LONGRECT & outBdRect);

  static void SkipGeometry(CBBitStream        * inBitStream,
                           const CBTreeParser * inTreeParser);

  virtual TBuint32 Process(const CBCursor * inCursor) const;

  static void ProcessGeoRect(const CBCursor       * inCursor,
														 TBuint16               inNbForm,
														 const TB_3D_LONGRECT * inGeo);

  static void ProcessGeoEllipse(const CBCursor       * inCursor,
																TBuint16               inNbForm,
																const TB_3D_LONGRECT * inGeo);

protected:

  /**
   * Copy constructor.
   * @param inSource Source form
   * @param inCopyAttributes If \c false, attributes will not be copied (only geometry)
   */
  CBFormRect3D(const CBFormRect3D& inSource,
							 TBbool              inCopyAttributes = true);

  /**
   * Assigment operator
   * @param inSource Source form
   */
  CBFormRect3D & operator=(const CBFormRect3D& inSource);


  void SetSize(TB_LONGRECT& outRect);

  static void ReadRect(CBBitStream          * inBitStream,
											 const TB_3D_LONGPOINT& inNodeOrigin,
											 const TB_3D_BITSIZE  & inBitSize,
											 TB_3D_LONGRECT       & outRect);
};

#endif //  __CBFORMRECT3D_H__

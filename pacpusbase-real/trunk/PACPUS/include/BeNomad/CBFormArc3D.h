/*==========================================================  (-*- C++ -*-)
 *
 * @file CBFormArc3D.h
 * 
 * @version  $Id: CBFormArc3D.h,v 1.20 2006/03/09 16:42:13 wkunkel Exp $ 
 * 
 * @author  David Labrousse
 *
 * @copyright  (c) 2002-2005 BeNomad S.A.R.L., All Rights Reserved
 *
 * BeNomad confidential file protected by international copyright laws
 * UNAUTHORIZED ACCESS, USE, REPRODUCTION OR DISTRIBUTION IS PROHIBITED.
 *
 *========================================================================*/

#ifndef __CBFORMARC3D_H__
#define __CBFORMARC3D_H__

/*!
  @file CBFormArc3D.h
	CBFormArc3D class definition.
*/

#include "CBForm.h"

class CBCursor;
class CBBitStream;
class CBTreeParser;


/**
 * @class CBFormArc3D
 *
 * @brief This class defines a SVS 3D form of geometric type #EB_GEOTYPE_ARC.
 *
 * CBFormArc3D is a class that defines a SVS 3D form of geometric type #EB_GEOTYPE_ARC.
 * This class handles form's geometry.
 *
 */
class BSVS_EXPORT CBFormArc3D : public CBForm
{
 private:
  
  TBuint32    mSize;          //!< Form's size = max(dx, dy, dz) where dx (resp. dy, dz) is form's bounding rect's size in x (resp. y, z)
  TBuint32    mDynamicStatus; 
  TB_3D_ARC * mGeo;           //!< Form's geometry = array of #TB_3D_ARC

 public:

  /**
   * Default constructor.
   */
  CBFormArc3D(void);

  /**
   * Constructs a CBFormArc3D from a #TB_EXTERN_OBJECT object (see BTypes.h).
	 * Copies \a inObject's geometry into form's geometry and computes form's bounding rectangle.
   * @param inObject Object to build from
   * @param outRect  Form's bounding rectangle
   */
  CBFormArc3D(const TB_EXTERN_OBJECT& inObject,
							TB_LONGRECT           & outRect);

  /**
   * \internal
   * Constructs a CBFormArc3D by reading data from a SVS stream.
   * @param inBitStream SVS stream to read from
   * @param inObjectMgr Form's object manager
   * @param outRect     Form's bounding rectangle
   */
  CBFormArc3D(CBBitStream        * inBitStream,
							const CBObjectMgr  * inObjectMgr,
              const CBTreeParser * inTreeParser,
							TB_LONGRECT        & outRect);

  /**
   * Destructor.
   */
  virtual ~CBFormArc3D(void);

  /**
   * Copies form into a new CBFormArc3D and returns new form.
   * @param inCopyAttributes If \c false, attributes will not be copied (only geometry)
   * @return New form
   */
  virtual CBForm * Copy(TBbool inCopyAttributes = true) const;

  /**
   * Returns form's geometric type (#EB_GEOTYPE_ARC).
   * @return #EB_GEOTYPE_ARC
   */
  virtual EB_GEOTYPE GetType(void) const
  {
    return EB_GEOTYPE_ARC;
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
   * Is form a 2D form ? No !
   * @return \c true
   */
  TBbool Is2D(void) const
  {
    return false;
  }

  /**
   * Returns form's size = max in x,y,z of form's bounding rectangle.
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
    inGeo.g.arc3 = mGeo;
    inGeo.type   = EB_GEOTYPE_ARC;
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

  static TB_3D_ARC * ReadGeoFromStream(CBBitStream        * inBitStream,
                                       const CBTreeParser * inTreeParser,
																			 TBuint16             inNbForm);

  static void WriteGeoToStream(CBBitStream        * inBitStream,
                               const CBTreeParser * inTreeParser,
															 TBuint16             inNbForm,
															 const TB_3D_ARC    * inGeo);

  static void SkipGeometry(CBBitStream        * inBitStream,
                           const CBTreeParser * inTreeParser);

  static TBuint32 ProcessArcCallback(CBBitStream    * inBitStream,
																		 const CBCursor * inCursor);

  static void ProcessGeoArcCallback(CBBitStream    * inBitStream,
																		const CBCursor * inCursor,
																		TB_2D_LONGRECT & outBdRect);

  virtual TBuint32 Process(const CBCursor * inCursor) const;

  static void ProcessGeoArc(const CBCursor  * inCursor,
														TBuint16          inNbForm,
														const TB_3D_ARC * inGeo);

protected:

  /**
   * Copy constructor.
   * @param inSource Source form
   * @param inCopyAttributes If \c false, attributes will not be copied (only geometry)
   */
  CBFormArc3D(const CBFormArc3D& inSource,
						  TBbool             inCopyAttributes = true);

  /**
   * Assigment operator
   * @param inSource Source form
   */
  CBFormArc3D & operator=(const CBFormArc3D& inSource);

  void SetSize(TB_LONGRECT& outRect);

  static void ReadRect(CBBitStream          * inBitStream,
											 const TB_3D_LONGPOINT& inNodeOrigin,
											 const TB_3D_BITSIZE  & inBitSize,
											 TB_3D_LONGRECT       & outRect);

  static void ReadAngles(CBBitStream * inBitStream,
												 TBint16     & outSAngle,
												 TBint16     & outDAngle);
};

#endif //  __CBFORMARC3D_H__

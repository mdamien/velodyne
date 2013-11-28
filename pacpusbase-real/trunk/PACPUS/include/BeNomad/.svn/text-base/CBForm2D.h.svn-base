/*==========================================================  (-*- C++ -*-)
 *
 * @file CBForm2D.h
 * 
 * @version  $Id: CBForm2D.h,v 1.30 2006/03/09 16:42:13 wkunkel Exp $ 
 * 
 * @author  David Labrousse
 *
 * @copyright  (c) 2002-2005 BeNomad S.A.R.L., All Rights Reserved
 *
 * BeNomad confidential file protected by international copyright laws
 * UNAUTHORIZED ACCESS, USE, REPRODUCTION OR DISTRIBUTION IS PROHIBITED.
 *
 *========================================================================*/

#ifndef __CBFORM2D_H__
#define __CBFORM2D_H__

/*!
  @file CBForm2D.h
	CBForm2D class definition.
*/

#include "CBForm.h"

class CBCursor;
class CBBitStream;
class CBTreeParser;


/**
 * @class CBForm2D
 *
 * @brief This class defines a SVS 2D form of geometric type #EB_GEOTYPE_CLOSED or #EB_GEOTYPE_OPEN.
 *
 * CBForm2D is a class that defines a SVS 2D form of geometric type #EB_GEOTYPE_CLOSED or #EB_GEOTYPE_OPEN.
 * This class handles form's geometry.
 *
 */
class BSVS_EXPORT CBForm2D : public CBForm
{
 private:

  TBuint32     mSize;          //!< Form's size = max(dx, dy) where dx (resp. dy) is form's bounding rect's size in x (resp. y)
  TBuint32     mDynamicStatus; 
  TB_2D_FORM * mGeo;           //!< Form's geometry = array of #TB_2D_FORM

 public:

  /**
   * Default constructor.
   */
  CBForm2D(void);

  /**
   * Constructs a CBForm2D from a #TB_EXTERN_OBJECT object (see BTypes.h).
	 * Copies \a inObject 's geometry into form's geometry and computes form's bounding rectangle.
   * @param inObject Object to build from
   * @param outRect  Form's bounding rectangle
   */
  CBForm2D(const TB_EXTERN_OBJECT& inObject,
           TB_LONGRECT&            outRect);

  /**
   * \internal
   * Constructs a CBForm2D by reading data from a SVS stream.
   * @param inBitStream SVS stream to read from
   * @param inObjectMgr Form's object manager
   * @param outRect     Form's bounding rectangle
   */
  CBForm2D(CBBitStream        * inBitStream,
           const CBObjectMgr  * inObjectMgr,
           const CBTreeParser * inTreeParser,
           TB_LONGRECT        & outRect);

  /**
   * Destructor.
   */
  virtual ~CBForm2D(void);

  /**
   * Copies form into a new CBForm2D and returns new form.
   * @param inCopyAttributes If \c false, attributes will not be copied (only geometry)
   * @return New form
   */
  virtual CBForm * Copy(TBbool inCopyAttributes = true) const;

  /**
   * Returns form's geometric type (either #EB_GEOTYPE_CLOSED or #EB_GEOTYPE_OPEN).
   * @return Form's geometric type
   */
  virtual EB_GEOTYPE GetType(void) const
  {
    return (mSize & 1) != 0 ? EB_GEOTYPE_CLOSED : EB_GEOTYPE_OPEN;
  }

  /**
   * Returns form's size = max in x,y of form's bounding rectangle.
   * @return Form's size.
   */
  virtual TBuint32 GetSize(void) const
  {
    return mSize >> 1;
  }

  /** 
   * \internal
   * Returns form's offset (in bytes).
   * @return Form's offset.
   */
  virtual TBuint32 GetOffset(void) const
  {
    return mDynamicStatus;
  }

  /**
   * \internal
   * Sets form's offset (in bytes).
   * @param inOffset Form's offset.
   */
  virtual void SetOffset(TBuint32 inOffset)
  {
    mDynamicStatus = inOffset;
  }

  /**
   * \internal
   * Returns form's spatial tree node index.
   * @return Form's spatial tree node index.
   */
  virtual TBuint32 GetNodeIndex(void) const
  {
    return mDynamicStatus;
  }

  /**
   * \internal
   * Sets form's spatial tree node index
   * @param inIndex Form's spatial tree node index
   */
  virtual void SetNodeIndex(TBuint32 inIndex)
  {
    mDynamicStatus = inIndex;
  }

  /**
   * Computes form's bounding rectangle.
   * @param outRect Form's bounding rectangle
   */
  virtual void GetBoundingRect(TB_LONGRECT& outRect) const;

  /**
   * Fills structure #TB_GEOMETRY (see BTypes.h) with form's geometry.
   * @param inGeo Form's geometry
   */
  virtual void GetGeometry(TB_GEOMETRY& inGeo) const
  {
    inGeo.nbForm = GetNbForm();
    inGeo.g.frm2 = mGeo;
    inGeo.type   = (mSize & 1) != 0 ? EB_GEOTYPE_CLOSED : EB_GEOTYPE_OPEN;
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

  /**
   * \internal
   * Reads form's geometry from a SVS stream, fills an array of #TB_2D_FORM (see BTypes.h)
   * and returns a pointer on this array.
   * @param inBitStream SVS stream to read from
   * @param inObjectMgr Form's object manager
   * @param inNbForm Number of #TB_2D_FORM geometric forms
   * @param open \c true if form is open, \c false if form is closed
   * @return Form's geometry
   */
  static TB_2D_FORM * ReadGeoFromStream(CBBitStream        * inBitStream,
                                        const CBTreeParser * inTreeParser,
                                        TBuint16             inNbForm,
                                        TBbool               open);

  /**
   * \internal
   * Writes form's geometry into a SVS stream.
   * @param inBitStream SVS stream to write in
   * @param inObjectMgr Form's object manager
   * @param inNbForm Number of #TB_2D_FORM geometric forms
   * @param inGeo Array of #TB_2D_FORM geometric forms
   * @param open \c true if form is open, \c false if form is closed
   */
  static void WriteGeoToStream(CBBitStream        * inBitStream,
                               const CBTreeParser * inTreeParser,
                               const TBuint16       inNbForm,
                               const TB_2D_FORM   * inGeo,
                               TBbool               open);

  /**
   * \internal
   * Callback called by SVS cursor (if form is of geometric type #EB_GEOTYPE_CLOSED).
   * Reads form's attributes and geometry and returns form's size.
   * @param inBitStream SVS stream to read from
   * @param inCursor SVS cursor
   * @return Form's size
   */
  static TBuint32 ProcessClosedCallback(CBBitStream    * inBitStream,
                                        const CBCursor * inCursor);

  /**
   * \internal
   * Callback called by ProcessClosedCallback (form is of geometric type #EB_GEOTYPE_CLOSED).
   * Reads form's geometry and computes bounding rectangle.
   * @param inBitStream SVS stream to read from
   * @param inCursor SVS cursor
   * @param outBoundingRect Form's bounding rectangle
   */
  static void ProcessGeoClosedCallback(CBBitStream    * inBitStream,
                                       const CBCursor * inCursor,
                                       TB_2D_LONGRECT&  outBoundingRect);

  /**
   * \internal
   * Callback called by SVS cursor (if form is of geometric type #EB_GEOTYPE_OPEN)
   * (or by \c CBFormComplex2D::ProcessComplexCallback()).
   * Reads form's attributes and geometry and returns form's size.
   * @param inBitStream SVS stream to read from
   * @param inCursor SVS cursor
   * @return Form's size
   */
  static TBuint32 ProcessOpenCallback(CBBitStream    * inBitStream,
                                      const CBCursor * inCursor);

  /**
   * \internal
   * Callback called by ProcessOpenCallback (form is of geometry type #EB_GEOTYPE_OPEN).
   * Reads form's geometry and computes bounding rectangle.
   * @param inBitStream SVS stream to read from
   * @param inCursor SVS cursor
   * @param outBoundingRect Form's bounding rectangle
   */
  static void ProcessGeoOpenCallback(CBBitStream    * inBitStream,
                                     const CBCursor * inCursor,
                                     TB_2D_LONGRECT&  outBoundingRect);

  /**
   * \internal
   * Called either by ProcessClosedCallback or by ProcessOpenCallback
   * (or by CBFormComplex2D::SkipGeometry()) when reading geometry is not needed.
   * Skips form's geometry (fast read) in order to set cursor on next form.
   * @param inBitStream SVS stream to read from
   * @param inTree Form's spatial tree
   * @param open \c true if form is open, \c false if form is closed
   */
  static void SkipGeometry(CBBitStream        * inBitStream,
                           const CBTreeParser * inTreeParser,
                           TBbool               open);

  /**
   * \internal
   * Called by SVS cursor (if form is built in memory)
   * Reads form's attributes and geometry and returns form's size.
   * @param inCursor SVS cursor
   * @return Form's size
   */
  virtual TBuint32 Process(const CBCursor * inCursor) const;

  /**
   * \internal
   * Callback called by Process() (if form is of geometry type #EB_GEOTYPE_CLOSED).
   * Reads form's geometry.
   * @param inCursor SVS cursor
   * @param inNbForm Number of #TB_2D_FORM geometric forms
   * @param inGeo Array of #TB_2D_FORM geometric forms
   */
  static void ProcessGeoClosed(const CBCursor   * inCursor,
                               TBuint16           inNbForm,
                               const TB_2D_FORM * inGeo);

  /**
   * \internal
   * Callback called by Process() (if form is of geometry type #EB_GEOTYPE_OPEN).
   * Reads form's geometry.
   * @param inCursor SVS cursor
   * @param inNbForm Number of #TB_2D_FORM geometric forms
   * @param inGeo Array of #TB_2D_FORM geometric forms
   */
  static void ProcessGeoOpen(const CBCursor   * inCursor,
                             TBuint16           inNbForm,
                             const TB_2D_FORM * inGeo);

  /**
   * \internal
   * Computes form's bounding rectangle and sets form's size.
   * @param outRect Form's bounding rectangle
   */
  void SetSize(TB_LONGRECT& outRect);

  /**
   * \internal
   * Merges form with \a inFrm. Geometry will be merged by creating new elementary
	 * forms (i.e. by adding new entries to \c mGeo member).
   * @param inFrm Form to merge with
   * @param inCopyAttributes If \c true, merge attributes with \a inFrm 's atributes
   * @param inDestroyForm If \c true destroys \a inFrm and \a inFrm is set to NULL
	 * @return \c false if an error occured (\a inFrm is NULL or too many elementary forms), \c true otherwise
   */
	TBbool MergeWith(CBForm2D *& inFrm,
									 TBbool      inCopyAttributes = false,
									 TBbool      inDestroyForm = false);

protected:

  /**
   * Copy constructor.
   * @param inSource Source form
   * @param inCopyAttributes If \c false, attributes will not be copied (only geometry)
   */
  CBForm2D(const CBForm2D& inSource,
           TBbool          inCopyAttributes = true);

  /**
   * Assigment operator
   * @param inSource Source form
   */
  CBForm2D & operator=(const CBForm2D& inSource);

#if 0
  /**
   * \internal
   * Callback that reads from a SVS stream the number of intermediate vectors of a #TB_2D_FORM structure (see BTypes.h).
   * @param inBitStream SVS stream to read from
   * @param open \c true if form is an ope form, \c false if form is a closed form
   */
  static TBuint32 ReadNbIntPoint(CBBitStream * inBitStream,
                                 TBbool        open);

  /**
   * \internal
   * Callback that reads from a SVS stream the number of bits required to decode
   * intermediate vectors of a #TB_2D_FORM structure (see BTypes.h).
   * @param inBitStream SVS stream to read from
   * @param outDeltaBitSize Number of bits required to decode intermediate vectors
   * @param single \c true if form is open and has only 1 intermediate point, \c false otherwise
   */
  static void ReadDeltaBitSize(CBBitStream  * inBitStream,
                               TB_2D_BITSIZE& outDeltaBitSize,
                               TBbool         single);
#endif
  static TBuint32 ReadNbIntPtAndBitSize(CBBitStream  * inBitStream,
                                        TB_2D_BITSIZE& outDeltaBitSize,
                                        TBbool         open);
};
#endif //  __CBFORM2D_H__

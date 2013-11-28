/*==========================================================  (-*- C++ -*-)
 *
 * @file CBForm.h
 * 
 * @version  $Id: CBForm.h,v 1.32 2006/05/03 17:45:26 dlabrousse Exp $ 
 * 
 * @author  David Labrousse
 *
 * @copyright  (c) 2002-2005 BeNomad S.A.R.L., All Rights Reserved
 *
 * BeNomad confidential file protected by international copyright laws
 * UNAUTHORIZED ACCESS, USE, REPRODUCTION OR DISTRIBUTION IS PROHIBITED.
 *
 *========================================================================*/

#ifndef __CBFORM_H__
#define __CBFORM_H__

/*!
  @file CBForm.h
	CBForm class definition.
*/

#include "BTypes.h"
#include "BMacros.h"

class CBAttMgr;
class CBObjectMgr;
class CBCursor;
class CBBitStream;
class CBTreeParser;


/**
 * @class CBForm
 *
 * @brief This virtual class defines any SVS form.
 *
 * CBForm is a virtual class that defines any type of SVS form.
 * This class handles form's attributes independantly of form's geometric type.
 *
 */
class BSVS_EXPORT CBForm
{
protected:
  
  TBuint32       mStatus;     //!< nbForm (2 bytes) + nbAtt (2 bytes)
  TB_ATTRIBUTE * mAttributes; //!< Array of attributes (see #TB_ATTRIBUTE)

public:

  /**
   * Default constructor
   */
  CBForm(void);

  /**
   * Constructs a CBForm from a #TB_EXTERN_OBJECT object.
	 * Copies \a inObject's attributes into form's attributes
   * @param inObject Object to build from
   */
  CBForm(const TB_EXTERN_OBJECT& inObject);

  /**
   * Virtual destructor
   */
  virtual ~CBForm(void);

  /**
   * Copies form into a new form and returns new form.
   * @param inCopyAttributes If \c false, attributes will not be copied (only geometry)
   * @return New form
   */
  virtual CBForm * Copy(TBbool inCopyAttributes = true) const = 0;

  /**
   * Returns number of elementary geometric elements of form's geometry.
   * @return Number of elementary geometric elements
   */
  inline TBuint16 GetNbForm(void) const
  {
    return (TBuint16) (mStatus >> 16);
  }

  /**
   * Sets the number of elementary geometric elements of form's geometry.
   * @param inNbForm Number of elementary geometric elements
   */
  inline void SetNbForm(TBuint16 inNbForm)
  {
    mStatus = ((TBuint32) inNbForm << 16) | (mStatus & 0xFFFF);
  }

  /**
   * Returns number of form's attributes.
   * @return Number of form's attributes
   */
  inline TBuint16 GetNbAtt(void) const
  {
    return (TBuint16) (mStatus & 0xFFFF);
  }

  /**
   * Returns the array of form's attributes.
   * @return Array of form's attributes
   */
  inline TB_ATTRIBUTE * GetAttributes(void) const
  {
    return mAttributes;
  }

  /**
   * Returns \a inIdx -th form's attribute.
   * @param inIdx Attribute's index
   * @return \a inIdx -th form's attribute
   */
  inline const TB_ATTRIBUTE& GetAttribute(TBuint16 inIdx) const
  {
    return mAttributes[inIdx];
  }

  /**
   * Sets new attribute to form at rank \a inIdx.
   * @param inIdx Attribute's rank
   * @param inAttribute New attribute
   */
  inline void SetAttribute(TBuint16            inIdx,
													 const TB_ATTRIBUTE& inAttribute)
  {
    mAttributes[inIdx] = inAttribute;
  }

  /**
   * Removes attribute of rank \a inIdx from form.
   * @param inIdx Attribute's rank
   * @return \c false if \a inIdx is greater or equal to number of form's attributes, \c true otherwise
   */
  TBbool RemoveAttribute(TBuint16 inIdx);

  /**
   * Removes and destroys if required all attached attributes.      
   * @param inDestroy Indicates if alpha or meta attributes should be destroyed.
   */
  void RemoveAllAttributes(TBbool inDestroy = true);

  /**
   * Adds a set of \a inNbAtt attributes to form's attributes.
   * @param inAttributes Array of new attributes
   * @param inNbAtt Number of new attributes (default = 1)
   * @param copyAlphaAndMetaAtt If \c true and inAttributes has #EB_ATTTYPE_ALPHA or #EB_ATTTYPE_META
	 * attributes, structures will be duplicated, if \c false (default) pointers will be copied
   * @return \c false if an error occured, \c true otherwise
   */
  TBbool AddAttributes(const TB_ATTRIBUTE * inAttributes,
											 TBuint16             inNbAtt = 1,
											 TBbool               copyAlphaAndMetaAtt = false);

  /**
   * Returns form's geometric type (see BTypes.h).
   * @return Form's geometric type
   */
  virtual EB_GEOTYPE GetType(void) const = 0;

  virtual TBuint32 GetOffset(void) const = 0;

  virtual void SetOffset(TBuint32 inOffset) = 0;

  virtual TBuint32 GetNodeIndex(void) const = 0;

  virtual void SetNodeIndex(TBuint32 inIndex) = 0;

  /**
   * Returns form's geometric size : max in x, y, (z) of form's bounding rectangle
	 * @note If form is of geometric type #EB_GEOTYPE_ABSTRACT, returns 0.
   * @return Form's geometric size
   */
  virtual TBuint32 GetSize(void) const = 0;

  /**
   * Calculates form's bounding rectangle
	 * @note Form must be a geometric form (i.e. type != #EB_GEOTYPE_ABSTRACT)
   * @param outRect Form's bounding rectangle
   */
  virtual void GetBoundingRect(TB_LONGRECT& outRect) const = 0;

  /**
   * Returns \c true if form is a 3D form
	 * @note If form is of geometric type #EB_GEOTYPE_ABSTRACT, returns \c false.
   * @return \c true if form is a 3D form, \c false if form is a 2D form
   */
  virtual TBbool Is3D(void) const { return false; }

  /**
   * Returns \c true if form is a 2D form
	 * @note If form is of geometric type #EB_GEOTYPE_ABSTRACT, returns \c true.
   * @return \c true if form is a 2D form, \c false if form is a 3D form
   */
  virtual TBbool Is2D(void) const { return true; }

  /**
   * Fills structure #TB_GEOMETRY (see BTypes.h) with form's geometry
   * @param inGeo Form's geometry
   */
  virtual void GetGeometry(TB_GEOMETRY& inGeo) const = 0;
	
  /**
   * \internal
   */
  virtual TBany GetGeo(void) const = 0;

  /**
   * Writes form into a SVS stream
   * @param inBitStream SVS stream
   * @param inObjectMgr Form's object manager
   */
  virtual void WriteToStream(CBBitStream        * inBitStream,
                             const CBTreeParser * inTreeParser) const = 0;

  static TBbool ProcessAttCallback(CBBitStream    * inBitStream,
                                   const CBCursor * inCursor);

  TBbool ProcessAtt(const CBCursor * inCursor) const;

  virtual TBuint32 Process(const CBCursor * inCursor) const = 0;

  static void ReadNFirstAtt(const CBObjectMgr * inObjMgr,
                            CBBitStream       * inBitStream,
                            TB_ATTRIBUTE      * outAtt,
                            TBuint16          & ioNbAtt);

protected:

  /**
   * Copy constructor
   * @param inSource Source form
   * @param inCopyAttributes If \c false, attributes will not be copied (only geometry)
   */
  CBForm(const CBForm& inSource, TBbool inCopyAttributes = true);

  inline void SetNbAtt(TBuint16 inNbAtt)
  {
    mStatus = (mStatus & 0xFFFF0000) | (TBuint32) inNbAtt;
  }

  TBbool ReadAttFromStream(CBBitStream    * inBitStream,
					                 const CBAttMgr * inAttMgr);

  void WriteAttToStream(CBBitStream    * inBitStream,
                        const CBAttMgr * inAttMgr) const;

  static TBuint16 ReadNbOptAttFromStream(CBBitStream * inBitStream);

  static void WriteNbOptAttToStream(CBBitStream  * inBitStream,
                                    const TBuint16 inNbOptAtt);

  static TBuint16 ReadNbFormFromStream(CBBitStream * inBitStream);

  static void WriteNbFormToStream(CBBitStream  * inBitStream,
                                  const TBuint16 inNbForm); 
};
#endif //  __CBFORM_H__

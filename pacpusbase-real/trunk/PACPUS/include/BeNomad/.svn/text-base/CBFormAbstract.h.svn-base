/*==========================================================  (-*- C++ -*-)
 *
 * @file CBFormAbstract.h
 * 
 * @version  $Id: CBFormAbstract.h,v 1.19 2006/03/09 16:42:13 wkunkel Exp $ 
 * 
 * @author  David Labrousse
 *
 * @copyright  (c) 2002-2005 BeNomad S.A.R.L., All Rights Reserved
 *
 * BeNomad confidential file protected by international copyright laws
 * UNAUTHORIZED ACCESS, USE, REPRODUCTION OR DISTRIBUTION IS PROHIBITED.
 *
 *========================================================================*/

#ifndef __CBFORMABSTRACT_H__
#define __CBFORMABSTRACT_H__

/*!
  @file CBFormAbstract.h
	CBFormAbstract class definition.
*/

#include "CBForm.h"
#include "BMacros.h"

class CBBitStream;
class CBTreeParser;

/**
 * @class CBFormAbstract
 *
 * @brief This class defines a SVS form of geometric type #EB_GEOTYPE_ABSTRACT (no geometry).
 *
 * CBFormAbstract is a class that defines a SVS form of geometric type #EB_GEOTYPE_ABSTRACT.
 * Abstract forms have no geometry (only attributes).
 *
 */
class BSVS_EXPORT CBFormAbstract : public CBForm
{
 public:

  /**
   * Default constructor.
   */
  CBFormAbstract();

  /**
   * Constructs a CBFormAbstract from a #TB_EXTERN_OBJECT object (see BTypes.h).
   * @param inObject Object to build from
   */
  CBFormAbstract(const TB_EXTERN_OBJECT& inObject);

  /**
   * \internal
   * Constructs a CBFormAbstract by reading data from a SVS stream.
   * @param inBitStream SVS stream to read from
   * @param inObjectMgr Form's object manager
   */
  CBFormAbstract(CBBitStream       * inBitStream,
								 const CBObjectMgr * inObjectMgr);

  /**
   * Destructor.
   */
  virtual ~CBFormAbstract(void) {};

	/**
   * Copies form into a new CBFormAbstract and returns new form.
   * @param inCopyAttributes Attributes are always be copied
   * @return New form
   */
  virtual CBForm * Copy(TBbool inCopyAttributes = true) const;

  /**
   * Returns form's geometric type (#EB_GEOTYPE_ABSTRACT).
   * @return #EB_GEOTYPE_ABSTRACT
   */
  virtual EB_GEOTYPE GetType(void) const
  {
    return EB_GEOTYPE_ABSTRACT;
  }

  /**
   * Is form a 2D form ? No ! (Abstract forms have no geometry but are considered as 2D forms)
   * @return \c false
   */
  TBbool Is2D(void) const
  {
    return false;
  }

  /**
   * Returns form's size = 0 (No geometry !).
   * @return 0
   */
  virtual TBuint32 GetSize(void) const
  {
    return 0;
  }

  TBuint32 GetOffset(void) const
  {
    B_ASSERT(false);
    return 0UL;
  }

  void SetOffset(TBuint32 inOffset)
  {
    B_ASSERT(false);
  }

  TBuint32 GetNodeIndex(void) const
  {
    B_ASSERT(false);
    return 0UL;
  }

  void SetNodeIndex(TBuint32 inIndex)
  {
    B_ASSERT(false);
  }

  void GetBoundingRect(TB_LONGRECT& outRect) const
  {
    B_ASSERT(false);
  }

  void GetGeometry(TB_GEOMETRY& inGeo) const
  {
    B_ASSERT(false);
  }
	
  /**
   * \internal
   */
  virtual TBany GetGeo(void) const { return NULL; }

  /**
   * Writes form into a SVS stream.
   * @param inBitStream SVS stream
   * @param inObjectMgr Form's object manager
   */
  virtual void WriteToStream(CBBitStream        * inBitStream,
                             const CBTreeParser * inTreeParser) const;

  TBuint32 Process(const CBCursor * inCursor) const
  {
    B_ASSERT(false);
    return 0;
  }

protected:

  /**
   * Copy constructor.
   * @param inSource Source form
   */
  CBFormAbstract(const CBFormAbstract& inSource);

  CBFormAbstract & operator=(const CBFormAbstract& inSource);
};

#endif //  __CBFORMABSTRACT_H__

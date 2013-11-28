/*==========================================================  (-*- C++ -*-)
 *
 * @file CBSVSHeader.h
 * 
 * @version  $Id: CBSVSHeader.h,v 1.2 2003/10/28 19:10:21 wkunkel Exp $ 
 * 
 * @author  William Kunkel
 *
 * @copyright  (c) 2002-2003 BeNomad S.A.R.L., All Rights Reserved
 *
 * BeNomad confidential file protected by international copyright laws
 * UNAUTHORIZED ACCESS, USE, REPRODUCTION OR DISTRIBUTION IS PROHIBITED.
 *
 *========================================================================*/

#ifndef __CBSVS_HEADER_H__
#define __CBSVS_HEADER_H__

/*!
 * @file CBSVSHeader.h
 * CBSVSHeader class definition.
 */

#include "BTypes.h"
#include "CBVector.h"

class CBSVS;

/**
 * @class CBSVSHeader
 *
 * This class provides methods for managing (getting or setting) SVS header information.
 * An SVS header is defined by a set of abstract objects (#EB_GEOTYPE_ABSTRACT) stored 
 * in the class of ID 0. With each abstract object a list of one or more attributes can
 * be associated.
 */
class BSVS_EXPORT CBSVSHeader
{
public:

  /**
   * Constructs an empty SVS Header.
   */
  CBSVSHeader(void);

  /**
   * Copy constructor.
   */
  CBSVSHeader(const CBSVSHeader & inSource);

  /**
   * Assignment operator.
   */
  CBSVSHeader& operator=(const CBSVSHeader & inOther);

  /**
   * Destructor.
   */
  virtual ~CBSVSHeader(void);

  /**
   * Method interface to determine whether this SVS Header contains valid information.
   * @return \c true if this header contains valid information, \c false otherwise.
   */
  virtual TBbool IsValid(void) const = 0;

  /**
   * Populates this class with all the header information coming from the given SVS.
   * @param inSVS The SVS which contains header information to extract.
   * @return \c true if this header contains header information, \c false otherwise.
   */
  virtual TBbool Get(CBSVS * inSVS);

  /**
   * Assigns header information to the given SVS (Older header information will be erased).
   * @param inSVS The SVS which must contain header information.
   * @return \c false if an error occurs, \c true otherwise.
   */
  virtual TBbool Set(CBSVS * inSVS);
  
  /**
   * Resets all information from this SVS Header such that it becomes empty.
   */
  virtual void Reset(void);

  /**
   * Returns the number of equivalent abstract objects contained in this SVS header.   
   * @return The number of equivalent abstract objects contained in this SVS header.   
   */
  TBuint32 GetNbAbstracts(void) const { return mAttList.GetCount(); }

  /**
   * Returns the array of attributes corresponding to the nth abstract object.
   * @param inIndex The nth abstract object.
   * @param outNbAtts The number TB_ATTRIBUTE structures contained in the array.
   * @return The array of attributes corresponding to the nth abstract object or
   * \c null if the given index is out of bounds.
   */
  const TB_ATTRIBUTE * GetAttributes(TBuint32 inIndex, TBuint16 & outNbAtts);

  /**
   * Adds a new array of attributes to the SVS Header. This is equivalent to add 
   * a new abstract object with its attributes.
   * @param inAtts The array of attributes to add.
   * @param inNbAtts The number TB_ATTRIBUTE structures contained in the array.
   * @return \c false if an error occurs, \c true otherwise.
   */
  TBbool AddAttributes(const TB_ATTRIBUTE * inAtts, TBuint16 inNbAtts);

  /**
   * Replaces all the attributes associated with an existing abstract object.   
   * @param inIndex The index of the abstract object.
   * @param inAtts The new array of attributes.
   * @param inNbAtts The number TB_ATTRIBUTE structures contained in the array.
   * @return \c false if an error occurs, \c true otherwise.
   */
  TBbool ReplaceAttributes(TBuint32 inIndex, const TB_ATTRIBUTE * inAtts, TBuint16 inNbAtts);
  

protected:
  
  TB_ATTRIBUTE * CopyAttributes  (const TB_ATTRIBUTE * inAtts, TBuint16 inNbAtts);
  void           DeleteAttributes(TB_ATTRIBUTE * inAtts, TBuint16 inNbAtts);

  static TBbool HeaderFilterFunc(void * inData, const TBuint32 inClassID, const EB_GEOTYPE inType) {
    return (inClassID == 0) && (inType == EB_GEOTYPE_ABSTRACT);
  }

protected:

  typedef struct {
    TBuint16       mNbAtts;
    TB_ATTRIBUTE * mAtts;
  } TB_ATT_INFO;
    
  CBVector mAttList; //!< A vector of TB_ATT_INFO structures (one TB_ATT_INFO per abstract object).
};

#endif /* __CBSVS_HEADER_H__ */

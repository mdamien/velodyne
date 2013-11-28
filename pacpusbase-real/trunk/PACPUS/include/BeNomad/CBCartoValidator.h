/*==========================================================  (-*- C++ -*-)
 *
 * @file CBCartoValidator.h
 * 
 * @version  $Id: CBCartoValidator.h,v 1.10 2005/08/20 16:33:56 wkunkel Exp $ 
 * 
 * @author  William Kunkel
 *
 * @copyright  (c) 2002-2003 BeNomad S.A.R.L., All Rights Reserved
 *
 * BeNomad confidential file protected by international copyright laws
 * UNAUTHORIZED ACCESS, USE, REPRODUCTION OR DISTRIBUTION IS PROHIBITED.
 *
 *========================================================================*/

#ifndef _CBCARTO_VALIDATOR_H_
#define _CBCARTO_VALIDATOR_H_

/*!
  @file CBCartoValidator.h
	CBCartoValidator class definition.
*/

#include "CBSVSValidator.h"
#include "CBCartoHeader.h"


/*!
 * @class CBCartoValidator
 *
 * This class checks compatibility of an SVS's header with a reference header (see #CBCartoHeader).
 *
 * When several SVS are opened, it is necessary to check that they are all compatible.
 * In particular they need to have same coordinate system and scale (for srceen projection purpose)
 * and same type (for style chart purpose). Therefore, before adding an SVS in a SVS manager
 * (see class #CBSVSMgr), we need to check compatibility with previously opened SVS.
 * The first SVS opened serves as a reference for the others. If an SVS is not compatible, it will not be opened
 * and a validation error is set.
 */
class BSVS_EXPORT CBCartoValidator : public CBSVSValidator
{
public:

  /**
   * Constructor.
   */
  CBCartoValidator(void);

  /**
   * Destructor.
   */
  ~CBCartoValidator(void) {}

  /**
   * Returns reference header (see #CBCartoHeader).
   */
  const CBCartoHeader & GetHeader(void) const { return mCartoHeader; }

  /**
   * Initializes reference header to 'undefined header'.
   */
  virtual void Init(void) { mCartoHeader = CBCartoHeader(); }

  /**
   * Returns header's coordinate scale (see #CBCartoHeader).
   */
	inline TBuint32 GetScale(void) const { return mCartoHeader.GetScale(); }

  /**
   * Checks compatibility of \a inSVS with reference header.
	 * @param inSVS SVS to check compatibility
   */
  virtual TBbool IsValid(CBSVS * inSVS);

  /**
   * Returns validation error (#EB_ERROR::NONE if no error).
   */
  virtual const TBchar * GetValidationError(void) const;

protected:

  /**
   * @enum EB_ERROR
   * This enum defines all the possible validation error
   */
  enum EB_ERROR {
    NONE = 0,                 //!< No error
    INVALID_TYPE = 1,         //!< Incompatible type (see #CBCartoHeader::EB_SVS_TYPE)
    INVALID_COORD_SYSTEM = 2, //!< Incompatible coordinate system (see #CBCartoHeader::EB_COORD)
    INVALID_SCALE = 3,        //!< Incompatible coordinate scale
    INVALID_ENCODING = 4      //!< Incompatible encoding
  };

  static const TBchar * mErrMsg[];

  CBCartoHeader mCartoHeader;
  EB_ERROR      mErr;
};

#endif /* _CBCARTO_VALIDATOR_H_ */

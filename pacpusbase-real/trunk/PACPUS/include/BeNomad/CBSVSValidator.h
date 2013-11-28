/*==========================================================  (-*- C++ -*-)
 *
 * @file CBSVSValidator.h
 * 
 * @version  $Id: CBSVSValidator.h,v 1.9 2005/07/29 15:30:47 dlabrousse Exp $ 
 * 
 * @author  William Kunkel
 *
 * @copyright  (c) 2002-2003 BeNomad S.A.R.L., All Rights Reserved
 *
 * BeNomad confidential file protected by international copyright laws
 * UNAUTHORIZED ACCESS, USE, REPRODUCTION OR DISTRIBUTION IS PROHIBITED.
 *
 *========================================================================*/

#ifndef _CBSVS_VALIDATOR_H_
#define _CBSVS_VALIDATOR_H_

/*!
  @file CBSVSValidator.h
	CBSVSValidator class definition.
*/

#include "BTypes.h"

class CBSVS;

/**
 * @class CBSVSValidator
 * This abstraction defines a basic interface for SVS Validator objects.
 * A SVS Validator may be used by the #CBSVSMgr class to perform validation
 * on data contained in a SVS file (typically on header informations).
 * If the validation process fails, the #CBSVSMgr will reject the SVS file that 
 * the user wants to open.
 */
class BSVS_EXPORT CBSVSValidator
{
public:

  /**
   * Default constructeur
   */
  CBSVSValidator(void) {}

  /**
   * Destructeur
   */
  virtual ~CBSVSValidator(void) {}

  /**
   * Override this method to implement your own SVS validator.
   * @param inSVS The #CBSVS object to validate.
   * @return Must return \c false if the validation failed, \c true otherwise.
   */
  virtual TBbool IsValid(CBSVS * inSVS) = 0;

  /**
   * Initializes reference header to 'undefined header'.
	 * This method is called each time SVSMgr is empty (after a close of last SVS or a close all).
	 * It may be useful if the first SVS openned is used as a reference for validation of other SVS
   * Override this method to implement your own initialization.
   */
  virtual void Init(void) = 0;


  /**
   * Override this method to return an explicit validation error.
   */
  virtual const TBchar * GetValidationError(void) const = 0;
};

#endif /* _CBSVS_VALIDATOR_H_ */

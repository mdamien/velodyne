/*==========================================================  (-*- C++ -*-)
 *
 * @file BConfig.h
 * 
 * @version  $Id: BConfig.h,v 1.3 2004/10/31 15:06:18 wkunkel Exp $ 
 * 
 * @author  William Kunkel
 *
 * @copyright  (c) 2002-2004 BeNomad S.A.R.L., All Rights Reserved
 *
 * BeNomad confidential file protected by international copyright laws
 * UNAUTHORIZED ACCESS, USE, REPRODUCTION OR DISTRIBUTION IS PROHIBITED.
 *
 *========================================================================*/

#ifndef __BCONFIG_H__
#define __BCONFIG_H__

#if defined(_WIN32)
#  define _BDLL
#  define _BWIN32_API_SUPPORT
   
   // undef Windows macros defined in DLGS.H
#  undef   frm2
#  undef   frm3
#  undef   Form
#endif

#if defined(NDEBUG)
   // In non debug mode, disable assertion checks, 
#  define _BNOASSERTION
   // and trace output
#  define _BNOTRACE
#endif

#define _BSIV_LEVEL2

#define HAVE_PLACEMENT_OPERATOR_NEW 

#define HAVE_TIME_T

#endif /* __BCONFIG_H__ */

/*==========================================================  (-*- C++ -*-)
 *
 * @file BPlatforms.h
 * 
 * @version  $Id: BPlatforms.h,v 1.18 2005/02/07 13:20:36 wkunkel Exp $ 
 * 
 * @author  William Kunkel
 *
 * @copyright  (c) 2002-2003 BeNomad S.A.R.L., All Rights Reserved
 *
 * BeNomad confidential file protected by international copyright laws
 * UNAUTHORIZED ACCESS, USE, REPRODUCTION OR DISTRIBUTION IS PROHIBITED.
 *
 *========================================================================*/

#ifndef __BPLATFORMS_H__
#define __BPLATFORMS_H__

#include "BConfig.h"

#if defined (Linux)
#  define  KB_GCC_PACKED __attribute__((packed))
#  define  KB_LITTLE_ENDIAN
#  undef   KB_BIG_ENDIAN
#elif defined (_WIN32)
#  define  GCC_PACKED
#  define  KB_LITTLE_ENDIAN
#  undef   KB_BIG_ENDIAN
#endif

#if defined(KB_BIG_ENDIAN)
#  define B_BIG_TO_LITTLE(v) v
#else
#  define B_BIG_TO_LITTLE(v)
#endif

#define BSVS_EXPORT
#define BGEO_EXPORT
#define BRND_EXPORT
#define BFLT_EXPORT
#define BPLN_EXPORT
#define BNAV_EXPORT

// Define the DLL interface for windows shared libraries
#if defined(_WIN32) && defined(_BDLL)
#  if defined(_BBUILDLIBS)
#    define B_BASEEXPORT __declspec(dllexport)
#  else
#    define B_BASEEXPORT __declspec(dllimport)
#  endif
#  undef  BSVS_EXPORT
#  define BSVS_EXPORT B_BASEEXPORT
#  undef  BGEO_EXPORT
#  define BGEO_EXPORT B_BASEEXPORT
#  undef  BRND_EXPORT
#  define BRND_EXPORT B_BASEEXPORT
#  undef  BFLT_EXPORT
#  define BFLT_EXPORT B_BASEEXPORT
#  undef  BPLN_EXPORT
#  define BPLN_EXPORT B_BASEEXPORT
#  undef  BNAV_EXPORT
#  define BNAV_EXPORT B_BASEEXPORT
#endif

#endif /* __BPLATFORMS_H__ */

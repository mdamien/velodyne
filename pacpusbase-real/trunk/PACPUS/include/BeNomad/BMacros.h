/*==========================================================  (-*- C++ -*-)
 *
 * @file BMacros.h
 * 
 * @version  $Id: BMacros.h,v 1.46 2006/03/02 14:10:41 dlabrousse Exp $ 
 * 
 * @author  David Labrousse
 *
 * @copyright  (c) 2002-2003 BeNomad S.A.R.L., All Rights Reserved
 *
 * BeNomad confidential file protected by international copyright laws
 * UNAUTHORIZED ACCESS, USE, REPRODUCTION OR DISTRIBUTION IS PROHIBITED.
 *
 *========================================================================*/

#ifndef __BMACROS_H__
#define __BMACROS_H__

/*!
  @file BMacros.h
	Definition of macros used in SDK.
*/

/************** Plateform dependent macros **************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#include "BPlatforms.h"

#if !defined (_BNOASSERTION)
#  define B_ASSERT(condition)   ((void) ((condition) ? 0 : \
                                (printf("Assert failed: '%s' file %s line %d\n", \
                                #condition, __FILE__, __LINE__))))
#else
#  define B_ASSERT(condition) 
#endif


#if !defined(_BNOTRACE)
#  if !defined(_WIN32)
#    define V(a) a;fflush(stdout);
#  else
#    define V(a) a;   
#  endif
#else 
#  define V(a)
#endif


#if defined(HAVE_PLACEMENT_OPERATOR_NEW)
#  include <new.h>
#endif

#define VERSION_7_SUPPORT
#define B_MEM_OPTIM

//#define B_CHECK_MEM_ALLOC

/*!
 * Returns a pointer on a reserved memory space of size \a n (equivalent to \c malloc (\a n))
 */
#define BAlloc(n) ::malloc((n))

/*!
 * Reallocates pointer \a p to a \a n bytes memory space and returns new value of \a p (equivalent to \c realloc(\a p, \a n)).
 * @note If \a p is NULL, will do #BAlloc.
 */
#define BRealloc(p, n)  ((p) ? (::realloc((p), (size_t) (n))) : (BAlloc(n)))

/*!
 * Frees memory space pointed by \a p (equivalent to \c free (\a p)).
 * @note \a p is set to NULL.
 */
#define BFree(p) {::free(p); p = NULL;}

/*!
 * Equivalent to C++ operator \c new \a p.
 */
#define BNew(p) ::new p

/*!
 * Equivalent to \c memset (\a p, \a c, \a n).
 */
#define BMemset(p, c, n)    ::memset((void *) (p), (c), (n))

/*!
 * Equivalent to \c memcpy (\a d, \a s, \a n).
 */
#define BMemcpy(d, s, n)    ::memcpy((d), (s), (n))

/*!
 * Equivalent to \c memmove (\a d, \a s, \a n).
 */
#define BMemmove(d, s, n)   ::memmove((d), (s), (n))

/*!
 * Equivalent to \c memcmp (\a pd \a s, \a n).
 */
#define BMemcmp(d, s, n)    ::memcmp((const void *) (d), (const void *) (s), (n))

/*!
 * Equivalent to \c strlen (\a p).
 */
#define BStrlen(p)          strlen((const char *)(p))

/*!
 * Equivalent to \c strchr (\a s, \a c).
 */
#define BStrchr(s, c)       strchr((const char *)  (s), (int)(c))

/*!
 * Equivalent to \c strrchr (\a s, \a c).
 */
#define BStrrchr(s, c)      ::strrchr((const char *) (s), (int)(c))

/*!
 * Equivalent to \c strcpy (\a s1, \a s2).
 */
#define BStrcpy(s1, s2)     ::strcpy((char *) (s1), (const char *) (s2))

/*!
 * Equivalent to \c strncpy (\a s1, \a s2, \a n).
 */
#define BStrncpy(s1, s2, n) ::strncpy((char *) (s1), (const char *) (s2), (n))

/*!
 * Equivalent to \c strcat (\a s1, \a s2).
 */
#define BStrcat(s1, s2)     ::strcat((char *) (s1), (const char *) (s2))

/*!
 * Equivalent to \c strcmp (\a s1, \a s2).
 */
#define BStrcmp(s1, s2)     ::strcmp((const char *) (s1), (const char *) (s2))

/*!
 * Equivalent to \c strncmp (\a s1, \a s2, \a n).
 */
#define BStrncmp(s1, s2, n) ::strncmp((const char *) (s1), (const char *) (s2), (n))

/*!
 * Equivalent to \c strstr (\a s1, \a s2).
 */
#define BStrstr(s1, s2)     ::strstr((const char *) (s1), (const char *) (s2))

/*!
 * Equivalent to sprintf
 */
#define BStrFormat          ::sprintf

/*!
 * Equivalent to scanf
 */
#define BScanf              ::scanf

/*!
 * Equivalent to sscanf
 */
#define BSscanf              ::sscanf

#if defined(HAVE_TIME_T)
#include <time.h>
/*!
 * Equivalent to strftime
 */
#  define BStrftime(d, s, f, t) ::strftime((char *)(d), (size_t)(s), (const char *)(f), t)
#endif

/*!
 * Converts \a c into corresponding capital character.
 */
#define BToupper(c)         ((c >= 'a' && c <= 'z') ? c-32 : c)

/*!
 * Converts \a c to lowercase.
 */
#define BTolower(c)         ((c >= 'A' && c <= 'Z') ? c+32 : c)


/*!
 * Equivalent to \c printf 
 */ 
#define BPrintf                   printf

#if defined(_WIN32)
/*!
 * Allocates a memory block of \a n bytes on the stack.
 * @warning Do not pass the returned pointer value as an argument to free.
 */
# define BAlloca(n)                _alloca((n))
/*!
 * Equivalent to \c _snprintf 
 */ 
# define BSnprintf                _snprintf
/*!
 * Equivalent to \c _strdup (\a s).
 */
# define BStrdup(s)               _strdup((const char *)(s))
/*!
 * Equivalent to \c _stricmp (\a s1, \a s2).
 */
# define BStrcasecmp(s1, s2)      _stricmp((const char *) (s1), (const char *) (s2))
/*!
 * Equivalent to \c _strnicmp (\a s1, \a s2, \a n).
 */
# define BStrncasecmp(s1, s2, n)  _strnicmp((const char *) (s1), (const char *) (s2), (n))
/*!
 * Suspends execution of the calling process for t milliseconds.
 */
# define BSleep(t)                ::Sleep((t))
#else
# include <unistd.h>
/*!
 * Allocates a memory block of \a n bytes on the stack.
 * @warning Do not pass the returned pointer value as an argument to free.
 */
# define BAlloca(n)               ::alloca((n))
/*!
 * Equivalent to \c snprintf 
 */ 
# define BSnprintf                ::snprintf
/*!
 * Equivalent to \c strdup (\a s).
 */
# define BStrdup(s)               ::strdup((const char *)(s))
/*!
 * Equivalent to \c strcasecmp (\a s1, \a s2).
 */
# define BStrcasecmp(s1, s2)      ::strcasecmp((const char *) (s1), (const char *) (s2))
/*!
 * Equivalent to \c strncasecmp (\a s1, \a s2, \a n).
 */
# define BStrncasecmp(s1, s2, n)  ::strncasecmp((const char *) (s1), (const char *) (s2), (n))
/*!
 * Suspends execution of the calling process for t milliseconds.
 */
# define BSleep(t)                ::usleep((t)*1000);
#endif

// **************************************************
//    Wide char specific string macros
// **************************************************
#if defined(_WIN32)
#  include <TCHAR.h>
#else
#  include <wchar.h>  
#endif

#define BWCSlen(p)            wcslen((const wchar_t *)(p))
#define BWCSchr(s,c)          wcschr((const wchar_t*)(s), (wchar_t)(c))
#define BWCSrchr(s,c)         wcsrchr((const wchar_t*)(s), (wchar_t)(c))
#define BWCScpy(s1,s2)        wcscpy((wchar_t *)(s1), (const wchar_t *)(s2))
#define BWCSncpy(s1,s2,n)     wcsncpy((wchar_t *)(s1), (const wchar_t *)(s2),(size_t)(n))
#define BWCScat(s1,s2)        wcscat((wchar_t *)(s1), (const wchar_t *)(s2))
#define BWCScmp(s1,s2)        wcscmp((const wchar_t *)(s1), (const wchar_t *)(s2))
#define BWCSncmp(s1,s2)       wcsncmp((const wchar_t *)(s1), (const wchar_t *)(s2),(size_t)(n))
#define BWCSstr(s1,s2)        wcsstr((const wchar_t *)(s1), (const wchar_t *)(s2))
#define BWToupper(c)          towupper((wchar_t)(c))
#define BWTolower(c)          towlower((wchar_t)(c))
#define BWCPrintf             wprintf
#define BWCSformat            swprintf
#define BWCScanf              wscanf
#define BWCSscanf             swscanf
#if defined(HAVE_TIME_T)
#define BWCSftime(d, s, f, t) wcsftime((wchar_t *)(d), (size_t)(s), (const wchar_t *)(f), t)
#endif

#if defined(_WIN32)
#  define BWCSdup(s)            _wcsdup((const wchar_t *)(s))
#  define BWCScasecmp(s1,s2)    _wcsicmp((const wchar_t *)(s1), (const wchar_t *)(s2))
#  define BWCSncasecmp(s1,s2)   _wcsnicmp((const wchar_t *)(s1), (const wchar_t *)(s2),(size_t)(n))

#else   
#  define BWCSdup(s)            wcsdup((const wchar_t *)(s)) 
#  define BWCScasecmp(s1,s2)    wcscasecmp((const wchar_t *)(s1), (const wchar_t *)(s2))
#  define BWCSncasecmp(s1,s2)   wcsncasecmp((const wchar_t *)(s1), (const wchar_t *)(s2),(size_t)(n))
#endif

// **************************************************
//   Generic String macros (ANSI/UNICODE)
// **************************************************
#if defined(_UNICODE)
#  define BTCSlen(p)            BWCSlen(p)
#  define BTCSchr(s,c)          BWCSchr(s,c)
#  define BTCSrchr(s,c)         BWCSrchr(s,c)
#  define BTCScpy(s1,s2)        BWCScpy(s1,s2)
#  define BTCSncpy(s1,s2,n)     BWCScpy(s1,s2,n)
#  define BTCScat(s1,s2)        BWCScat(s1,s2)
#  define BTCScmp(s1,s2)        BWCScmp(s1,s2)
#  define BTCSncmp(s1,s2,n)     BWCSncmp(s1,s2,n)
#  define BTCScasecmp(s1,s2)    BWCScasecmp(s1,s2)
#  define BTCSncasecmp(s1,s2,n) BWCSncasecmp(s1,s2,n)
#  define BTCSstr(s1,s2)        BWCSstr(s1,s2)
#  define BTCSdup(s)            BWCSdup(s)
#  define BTCToupper(c)         BWToupper(c)
#  define BTCTolower(c)         BWTolower(c)
#  define BTCPrintf             BWCPrintf
#  define BTCSformat            BWCSformat
#  define BTCScanf              BWCScanf
#  define BTCSscanf             BWCSscanf
#if defined(HAVE_TIME_T)
#  define BTCSftime(d, s, f, t) BWCSftime(d, s, f, t)
#endif
#else
#  define BTCSlen(p)            BStrlen(p)
#  define BTCSchr(s,c)          BStrchr(s,c)
#  define BTCSrchr(s,c)         BStrrchr(s,c)
#  define BTCScpy(s1,s2)        BStrcpy(s1,s2)
#  define BTCSncpy(s1,s2,n)     BStrncpy(s1,s2,n)
#  define BTCScat(s1,s2)        BStrcat(s1,s2)
#  define BTCScmp(s1,s2)        BStrcmp(s1,s2)
#  define BTCSncmp(s1,s2,n)     BStrncmp(s1,s2,n)
#  define BTCScasecmp(s1,s2)    BStrcasecmp(s1,s2)
#  define BTCSncasecmp(s1,s2,n) BStrncasecmp(s1,s2,n)
#  define BTCSstr(s1,s2)        BStrstr(s1,s2)
#  define BTCSdup(s)            BStrdup(s)
#  define BTCToupper(c)         BToupper(c)
#  define BTCTolower(c)         BTolower(c)
#  define BTCPrintf             BPrintf
#  define BTCSformat            BStrFormat
#  define BTCScanf              BScanf
#  define BTCSscanf             BSscanf
#if defined(HAVE_TIME_T)
#  define BTCSftime(d, s, f, t) BStrftime(d, s, f, t)
#endif
#endif


#include <math.h>

#define KB_PI         (TBdouble) 3.1415926535897932384626433832795   /*!< Pi   constant  */
#define KB_2PI        (TBdouble) 6.283185307179586476925286766559    /*!< 2*Pi constant  */
#define KB_PI_OVER_2  (TBdouble) 1.5707963267948966192313216916398   /*!< Pi/2 constant  */
#define KB_PI_OVER_4  (TBdouble) 0.78539816339744830961566084581988  /*!< Pi/4 constant  */
#define KB_DEG2RAD    (TBdouble) 0.017453292519943295769236907684886 /*!< Pi / 180       */
#define KB_RAD2DEG    (TBdouble) 57.295779513082320876798154814105   /*!< 180 / Pi       */

/*!
 * Equivalent to \c cos (\a a)
 */
#define B_COS(a)    ::cos(a)

/*!
 * Equivalent to \c sin (\a a)
 */
#define B_SIN(a)    ::sin(a)

/*!
 * Converts a \c double into a \c long \c int by rounding it up to nearset integer
 */
#define B_DBL2INT(x) (TBint32) ((x) + ((x) > 0 ? 0.5 : -0.5))

// Smallest values such that 1.0 + EPSILON != 1.0
#if defined (_WIN32)
#  include <float.h>
#  define B_FLT_EPSILON FLT_EPSILON 
#  define B_DBL_EPSILON DBL_EPSILON   
#else
#  define B_FLT_EPSILON 1.1e-07F // To check
#  define B_DBL_EPSILON 2.2e-016   
#endif



/************** Plateform independent macros **************/

/*!
 * Computes the absolute value of its argument \a v.
 */
#define	B_ABS(v)      ((v) > 0 ?  (v) : -(v))

/*!
 * Computes the minimum of \a a and \a b.
 */
#define	B_MIN(a, b)   ((a) < (b) ? (a) : (b))

/*!
 * Computes the maximum of \a a and \a b.
 */
#define	B_MAX(a, b)   ((a) > (b) ? (a) : (b))

/*!
 * Returns 1 if \a n is odd, 0 otherwise.
 */
#define B_ISODD(n)    ((n) & 0x1)

/*!
 * Returns 1 if \a n is even, 0 otherwise.
 */
#define B_ISEVEN(n)   (!(B_ISODD(n)))

/**
 * @name Checking whether bits are enabled or disabled
 */
//@{
#define B_BIT_ENABLED(word,  bit) (((word) & (bit)) != 0)
#define B_BIT_DISABLED(word, bit) (((word) & (bit)) == 0)
#define B_BIT_CMP_MASK(word, bit, MASK) (((word) & (bit)) == MASK)
#define B_SET_BITS(word, bits) (word |=  (bits))
#define B_CLR_BITS(word, bits) (word &= ~(bits))
//@}

/**
 * \internal 
 * Swap the Blue and Red components of the given 24 bits color.
 */
#define B_RGB_SWAP(c) ((c & 0xFF0000)>>16 |(c & 0x00FF00)|(c & 0xFF)<<16)

#endif // __BMACROS_H__

/* sdtypes.h - General defines and types */

/* Copyright(c) 2000, Solution Mindready Inc. All rights reserved. */

/*
modification history
--------------------
01c,26Oct99,fb4 Corrected capital letters of VxWorks files for Unix
                compatibility.
01b,10Aug99,fb4 Updated copyright
01a,17Feb99,fb4 This file was created.
*/

/*
Basic data types and defines used by programmers.
*/

#ifndef __INCsdtypesh
#define __INCsdtypesh

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*
 * Type compatibility
 */

/*
 * Some useful values
 */

#ifndef NULL
#ifdef __cplusplus
#define NULL	0		/* Value used to return or test a null pointer */
#else
#define NULL	((void *)0)
#endif
#endif

#ifndef ZERO
#define ZERO	0		/* Value used to return or test a null value */
#endif

#ifndef FALSE
#define FALSE	0		/* Value used to return or test a false boolean value */
#endif

#ifndef TRUE
#define TRUE	1		/* Value used to return or test a true boolean value */
#endif

/*
 * Basic C/C++ types
 * The important point is to clearly show the number of bits used.
 */

#if defined(WIN32) || defined(WIN32K) || defined(_KRNL32_)

typedef unsigned int UINT32;	/* Used when the range is [0,4294967295] */
typedef unsigned short UINT16;	/* Used when the range is [0,65535] */
typedef unsigned char UINT8;	/* Used when the range is [0,255] */
typedef short INT16;			/* Used when the range is [-32768,32767] */
typedef int INT32; 				/* Used when the range is [-2147483648,2147483647] */
typedef signed char INT8;				/* Used when the range is [-128,127] */


/* ANSI standard types */
typedef	char  int8_t;
typedef	short int16_t;		/* Used when the range is [-32768,32767] */
typedef	int   int32_t;

typedef	unsigned char	uint8_t;	/* Used when the range is [0,255] */
typedef	unsigned short  uint16_t;	/* Used when the range is [0,65535] */
typedef	unsigned int    uint32_t;	/* Used when the range is [0,4294967295] */

//typedef	uint32_t	off_t;
typedef	uint32_t    size_t;


#elif defined(__LYNX__)

#include <sys/mman.h>				/* off_t */

typedef volatile unsigned int VUINT32;	/* Used for 32-bits hardware access */
typedef volatile unsigned char VUINT8;	/* Used for 8-bits hardware access */
typedef unsigned int UINT32;	/* Used when the range is [0,4294967295] */
typedef unsigned short UINT16;	/* Used when the range is [0,65535] */
typedef unsigned char UINT8;	/* Used when the range is [0,255] */
typedef int INT32; 		/* Used when the range is [-2147483648,2147483647] */
typedef short INT16;	/* Used when the range is [-32768,32767] */
typedef char INT8;		/* Used when the range is [-128,127] */
typedef void VOID;		/* Used for unknown type or no type */

#elif defined(__QNXNTO__)

#include <inttypes.h>   	    	/* integer types */
#include <sys/mman.h>				/* off_t */

typedef	int8_t		INT8;
typedef	int16_t	    INT16;			/* Used when the range is [-32768,32767] */
typedef	int32_t	    INT32;

typedef	uint8_t     UINT8;			/* Used when the range is [0,255] */
typedef	uint16_t	UINT16;			/* Used when the range is [0,65535] */
typedef	uint32_t	UINT32;			/* Used when the range is [0,4294967295] */

#define VOID void

#elif defined(__VXWORKS__)
#include <vxWorks.h>
#else
#error "Unsupported Operating System"
#endif


#ifndef VUINT32
#define VUINT32 volatile UINT32
#endif

#ifndef VUINT8
#define VUINT8 volatile UINT8
#endif



#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __INCsdtypesh */

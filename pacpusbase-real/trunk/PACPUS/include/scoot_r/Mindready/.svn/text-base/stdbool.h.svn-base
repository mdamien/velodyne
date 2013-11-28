/* stdbool.h - ANSI C Standard Header -- Boolean type and values */

/* Copyright(c) 2001, Mindready Solutions Inc. All rights reserved. */

/*
 * $Log: /Common/Design/Src/misc/Dev/winNT4/main/inc/stdbool.h $
 * 
 * 1     7/27/01 9:07a Sro
 *
 * 4     4/06/01 14:50 Blc
 * For inter-operability with GNU C++, we found that sizeof(bool) must be
 * 1. Replaced the enum with a simple char to define the type _Bool.
 *
 * 3     4/02/01 16:37 Blc
 * Fixed for proper compilation under C++
 *
 * 2     2/20/01 4:18p Jfha
 * Updated to ANSI C standard boolean type.
 *
 * $NoKeywords: $
 */

#ifndef __INCstdboolh
#define __INCstdboolh

/* This header file makes sense only in C since C++ has a builtin type for boolean. */
#ifndef __cplusplus

/* This header is NOT for use with ANSI C 1999 compliant compiler */
#ifdef __bool_true_false_are_defined
#error "Do not use this header. Your compiler supports a native <stdbool.h>"
#endif


/* Defines */

#define bool _Bool
#define true 1
#define false 0

#define __bool_true_false_are_defined 1


/* Typedefs */

typedef char _Bool;		/* sizeof(bool) = 1, this is important for inter-operability with g++ */

#endif /* __cplusplus */

#endif /* __INCstdboolh */

/* end of stdbool.h */
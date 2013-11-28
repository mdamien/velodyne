// %pacpus:license{
// This file is part of the PACPUS framework distributed under the
// CECILL-C License, Version 1.0.
// %pacpus:license}
/// @file
/// @author  Marek Kurdej <firstname.surname@utc.fr>
/// @date    June, 2012
/// @version $Id: cstdint.h 91 2013-05-19 10:32:48Z gdherbom $
/// @copyright Copyright (c) UTC/CNRS Heudiasyc 2006 - 2013. All rights reserved.
/// @brief Portable version of \<cstdint\> C99 header.
///
/// Portable version of \<cstdint\> C99 header.
/// It is necessary due to the non-conformance of MSVC before version 2010 to the C99 standard.

#ifndef DEF_PACPUS_CSTDINT_H
#define DEF_PACPUS_CSTDINT_H

#if defined(_MSC_VER) && _MSC_VER < 1600
// MSVC before 2010 has not <stdint.h> header (is not C99-compatible)

typedef __int8      int8_t;
typedef __int16     int16_t;
typedef __int32     int32_t;
typedef __int64     int64_t;

typedef unsigned __int8      uint8_t;
typedef unsigned __int16    uint16_t;
typedef unsigned __int32    uint32_t;
typedef unsigned __int64    uint64_t;

#else

#include <stdint.h>

#endif

#endif // DEF_PACPUS_CSTDINT_H


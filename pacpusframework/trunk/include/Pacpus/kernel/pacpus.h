// %pacpus:license{
// This file is part of the PACPUS framework distributed under the
// CECILL-C License, Version 1.0.
// %pacpus:license}
/// @file
/// @author  Gerald Dherbomez <firstname.surname@utc.fr>
/// @author  Marek Kurdej <firstname.surname@utc.fr>
/// @date    February, 2006
/// @version $Id: pacpus.h 116 2013-06-25 11:44:25Z kurdejma $
/// @copyright Copyright (c) UTC/CNRS Heudiasyc 2006 - 2013. All rights reserved.
/// @brief Brief description.
///
/// Detailed description.

#ifndef DEF_PACPUS_H
#define DEF_PACPUS_H

#include <Pacpus/kernel/PacpusLibConfig.h>
#include <Pacpus/kernel/road_time.h>

/// Pi math constant
/// 
/// @deprecated Use M_PI from \<cmath\>.
#ifndef PACPUS_PI
#   define PACPUS_PI       3.1415926
#endif

/// @def PACPUS_DEPRECATED(func)
/// Develops to the function or method declaration @b func
/// and marks it as deprecated.

/// @def PACPUS_DEPRECATED_MSG(func, msg)
/// Develops to the function or method declaration @b func
/// and marks it as deprecated with a given comment @b msg.
#ifdef __GNUC__
#   define PACPUS_DEPRECATED(func)              func __attribute__ ((deprecated))
#   define PACPUS_DEPRECATED_MSG(func, msg)     PACPUS_DEPRECATED(func)
#elif defined(_MSC_VER)
#   define PACPUS_DEPRECATED(func)              __declspec(deprecated) func
#   define PACPUS_DEPRECATED_MSG(func, msg)     __declspec(deprecated("was declared deprecated: " msg)) func
#else
#   pragma message("WARNING: You need to implement PACPUS_DEPRECATED for this compiler")
#   define PACPUS_DEPRECATED(func)              func
#   define PACPUS_DEPRECATED_MSG(func, msg)     func
#endif

#endif // DEF_PACPUS_H

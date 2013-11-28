// %pacpus:license{
// This file is part of the PACPUS framework distributed under the
// CECILL-C License, Version 1.0.
// %pacpus:license}
/// @file
/// @author  Gerald Dherbomez <firstname.surname@utc.fr>
/// @date    June, 2013
/// @version $Id:$
/// @copyright Copyright (c) UTC/CNRS Heudiasyc 2006 - 2013. All rights reserved.
/// @brief DLL import/export macro definitions file.
///
/// DLL import/export macro definitions file.
/// Declares \<library name\>_API macro as __declspec(dllexport) or __declspec(dllimport)
/// on Windows system and as an empty macro on other systems.
/// DLL exporting is performed when \<library name\>_EXPORTS is defined.

#ifndef __PACPUSTOOLSCONFIG_H__
#define __PACPUSTOOLSCONFIG_H__

// Export macro for FileLib DLL for Windows only
#ifdef WIN32
#   ifdef PACPUSTOOLS_EXPORTS
        // make DLL
#       define PACPUSTOOLS_API __declspec(dllexport)
#   else
        // use DLL
#       define PACPUSTOOLS_API __declspec(dllimport)
#   endif
#else
    // On other platforms, simply ignore this 
#   define PACPUSTOOLS_API 
#endif

#endif // __PACPUSTOOLSCONFIG_H__

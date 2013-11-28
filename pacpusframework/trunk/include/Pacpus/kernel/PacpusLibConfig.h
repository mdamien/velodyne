// %pacpus:license{
// This file is part of the PACPUS framework distributed under the
// CECILL-C License, Version 1.0.
// %pacpus:license}
/// @file
/// @author  Marek Kurdej <firstname.surname@utc.fr>
/// @date    January, 2013
/// @version $Id: FileLibConfig.h 76 2013-01-10 17:05:10Z kurdejma $
/// @copyright Copyright (c) UTC/CNRS Heudiasyc 2006 - 2013. All rights reserved.
/// @brief DLL import/export macro definitions file.
///
/// DLL import/export macro definitions file.
/// Declares \<library name\>_API macro as __declspec(dllexport) or __declspec(dllimport)
/// on Windows system and as an empty macro on other systems.
/// DLL exporting is performed when \<library name\>_EXPORTS is defined.

#ifndef DEF_PACPUS_PACPUSLIBCONFIG_H
#define DEF_PACPUS_PACPUSLIBCONFIG_H

/// Export macro for PacpusLib DLL for Windows only
#ifdef WIN32
#   ifdef PACPUSLIB_EXPORTS
//  make DLL
#       define PACPUSLIB_API __declspec(dllexport)
#   else
//      use DLL
#       define PACPUSLIB_API __declspec(dllimport)
#   endif
#else
//  On other platforms, simply ignore this
#   define PACPUSLIB_API
#endif

#endif // DEF_PACPUS_PACPUSLIBCONFIG_H

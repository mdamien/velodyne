// %pacpus:license{
// This file is part of the PACPUS framework distributed under the
// CECILL-C License, Version 1.0.
// %pacpus:license}
/// @file
/// @author  Firstname Surname <firstname.surname@utc.fr>
/// @date    Month, Year
/// @version $Id: DbitePlayerConfig.h 76 2013-01-10 17:05:10Z kurdejma $
/// @copyright Copyright (c) UTC/CNRS Heudiasyc 2006 - 2013. All rights reserved.
/// @brief Brief description.
///
/// Detailed description.

#ifndef DEF_PACPUS_DBITEPLAYERCONFIG_H
#define DEF_PACPUS_DBITEPLAYERCONFIG_H

// Export macro for DbitePlayer DLL for Windows only
#ifdef WIN32
#   ifdef DBITE_PLAYER_EXPORTS
        // make DLL
#       define DBITE_PLAYER_API __declspec(dllexport)
#   else
        // use DLL
#       define DBITE_PLAYER_API __declspec(dllimport)
#   endif
#else
    // On other platforms, simply ignore this 
#   define DBITE_PLAYER_API 
#endif

#endif // DEF_PACPUS_DBITEPLAYERCONFIG_H

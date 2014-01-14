#ifndef DBTPLYVISIONCONFIG_H
#define DBTPLYVISIONCONFIG_H

// Export macro for DbtPlyVision DLL for Windows only
#ifdef WIN32
#   if defined(DBTPLYVISION_EXPORTS) || defined(STEREO_EXPORTS)
        // make DLL
#       define DBTPLYVISION_API __declspec(dllexport)
#   else
        // use DLL
#       define DBTPLYVISION_API __declspec(dllimport)
#   endif
#else
    // On other platforms, simply ignore this 
#   define DBTPLYVISION_API 
#endif

#endif // DBTPLYVISIONCONFIG_H

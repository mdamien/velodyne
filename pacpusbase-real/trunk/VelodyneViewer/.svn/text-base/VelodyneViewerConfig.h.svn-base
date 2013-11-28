#ifndef VELODYNEVIEWERCONFIG_H
#define VELODYNEVIEWERCONFIG_H

// Export macro for VelodyneViewer DLL for Windows only
#ifdef WIN32
#   ifdef VELODYNEVIEWER_EXPORTS
        // make DLL
#       define VELODYNEVIEWER_API __declspec(dllexport)
#   else
        // use DLL
#       define VELODYNEVIEWER_API __declspec(dllimport)
#   endif
#else
    // On other platforms, simply ignore this 
#   define VELODYNEVIEWER_API /* nothing */
#endif

#endif // VELODYNEVIEWERCONFIG_H

#################################################
#   ___________    ____ ______  __ __  _____    #
#   \____ \__  \ _/ ___\\____ \|  |  \/  ___/   #
#   |  |_> > __ \\  \___|  |_> >  |  /\___ \    #
#   |   __(____  /\___  >   __/|____//____  >   #
#   |__|       \/     \/|__|              \/    #
#                                               #
#################################################

# ========================================
# Build-specific configuration
# ========================================

# TODO : check how cache variables work? Why the commented line doesn't work? 

if(IS_BUILDING_PACPUS)
	if(PACPUS_INSTALL_WITH_VERSION_NUMBER)
		pacpus_purge_backslash(PACPUS_INSTALL_DIR)
		set(PACPUS_INSTALL_DIR ${PACPUS_INSTALL_DIR}/${PACPUS_VERSION})
#    	set(PACPUS_INSTALL_DIR    ${CMAKE_INSTALL_PREFIX}/${PACPUS_VERSION}   CACHE PATH "Installation directory for the library")
	endif()
    set(PACPUS_INSTALL_3RD    FALSE                     CACHE BOOL      "Installation of the 3rd party")
endif()


# ========================================
# Global configuration
# ========================================
set(PACPUS_USE_LOG      TRUE  CACHE BOOL "Logging using log4cxx, the library is required")
if(win32) 
	set(PACPUS_INSTALL_3RD  TRUE CACHE BOOL "Installation of the 3rd party")
else()
	set(PACPUS_INSTALL_3RD  FALSE CACHE BOOL "Installation of the 3rd party")
endif()
set(PACPUS_BUILD_DOC    FALSE CACHE BOOL "Whether build the documentation - requires Doxygen")
set(PACPUS_USE_SOLUTION_FOLDERS  FALSE CACHE BOOL "Use solution folders to classify projects, works in MS Visual Studio")

if(PACPUS_USE_SOLUTION_FOLDERS)
    if(CMAKE_VERSION VERSION_GREATER "2.8.0")
        set_property(GLOBAL PROPERTY USE_FOLDERS ON)
    else()
        message(AUTHOR_WARNING "Folders are only supported with CMake 2.8.0 and newer, and MSVC 2005 and newer except for 2005/2008/2010 Express Edition")
    endif()
endif(PACPUS_USE_SOLUTION_FOLDERS)
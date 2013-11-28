#################################################
#   ___________    ____ ______  __ __  _____    #
#   \____ \__  \ _/ ___\\____ \|  |  \/  ___/   #
#   |  |_> > __ \\  \___|  |_> >  |  /\___ \    #
#   |   __(____  /\___  >   __/|____//____  >   #
#   |__|       \/     \/|__|              \/    #
#                                               #
#################################################

# TODO: write the output variables of this CMake file.

# Check PACPUS_ROOT
if(NOT PACPUS_ROOT)
    if(NOT ENV{PACPUS_ROOT} STREQUAL "")
        set(PACPUS_ROOT $ENV{PACPUS_ROOT})
		string (REPLACE "\\" "/" PACPUS_ROOT ${PACPUS_ROOT})
        message(STATUS "Detected PACPUS_ROOT in environment, set to '${PACPUS_ROOT}'")
    else()
      if(PACPUS_FIND_REQUIRED)
		MESSAGE(FATAL_ERROR "Could'not find PACPUS_ROOT ")
      else()
		MESSAGE(STATUS "Could'not find PACPUS_ROOT ")
		return()
      endif()
    endif()
else()
	string (REPLACE "\\" "/" PACPUS_ROOT ${PACPUS_ROOT})
	message(STATUS "Detected PACPUS_ROOT as argument with the path: '${PACPUS_ROOT}'")
endif()



# Hint directories
set(PACPUS_INCLUDE_HINT ${PACPUS_ROOT}/include)
set(PACPUS_LIBRARY_HINT ${PACPUS_ROOT}/lib)

# Locate the include files
find_path(
    PACPUS_INCLUDE_DIR
    NAMES
        "Pacpus"
    HINTS
        ${PACPUS_INCLUDE_HINT}
    DOC
        "The Pacpus include directory"
)

# List of required modules
set(PACPUS_MODULES "FileLib" "PacpusLib" "PacpusTools" "dbiteplayerlib")
if(WIN32)
    list(APPEND PACPUS_MODULES "ROAD_TIME")
endif()

set(MODULE_MISSING FALSE)
set(PACPUS_LIBRARIES "")

# Check the presence of each module
foreach(module ${PACPUS_MODULES})
    find_library(
        PACPUS_${module}_LIB
        NAMES
            ${module}
        HINTS
            ${PACPUS_LIBRARY_HINT}
    )
    find_library(
        PACPUS_${module}_LIBD
        NAMES
            ${module}_d
        HINTS
            ${PACPUS_LIBRARY_HINT}
    )

    if(PACPUS_${module}_LIB AND PACPUS_${module}_LIBD)
        list(APPEND PACPUS_LIBRARIES optimized ${PACPUS_${module}_LIB})
        list(APPEND PACPUS_LIBRARIES debug ${PACPUS_${module}_LIBD})
    else()
        set(MODULE_MISSING TRUE)
    endif()
endforeach()

if(NOT MODULE_MISSING AND PACPUS_INCLUDE_DIR)
    set(PACPUS_FOUND TRUE)

    # Configure Pacpus
    list(APPEND CMAKE_MODULE_PATH "${PACPUS_ROOT}/cmake")
    include(${PACPUS_ROOT}/cmake/PacpusUtilities.cmake)
    include(${PACPUS_ROOT}/cmake/PacpusConfiguration.cmake)
    include(${PACPUS_ROOT}/cmake/PacpusDependencies.cmake)
    include(${PACPUS_ROOT}/cmake/PacpusPlatforms.cmake)

    #set(CMAKE_INSTALL_PREFIX ${PACPUS_ROOT})
    set(PACPUS_INSTALL_DIR ${PACPUS_ROOT})
    set(PACPUS_LIB_DIR "${PACPUS_ROOT}/lib")
    MESSAGE(STATUS "PACPUS_ROOT found ${PACPUS_ROOT}")

else()
    set(PACPUS_FOUND FALSE)

    if(PACPUS_FIND_REQUIRED)
      MESSAGE(FATAL_ERROR "Could'not find PACPUS_ROOT ")
    else()
      MESSAGE(STATUS "Could'not find PACPUS_ROOT ")
    endif()

endif()

#################################################
#   ___________    ____ ______  __ __  _____    #
#   \____ \__  \ _/ ___\\____ \|  |  \/  ___/   #
#   |  |_> > __ \\  \___|  |_> >  |  /\___ \    #
#   |   __(____  /\___  >   __/|____//____  >   #
#   |__|       \/     \/|__|              \/    #
#                                               #
#################################################

project(Pacpus)
cmake_minimum_required(VERSION 2.8)

# ========================================
# Pacpus version
# ========================================
set(PACPUS_MAJOR_VERSION 0)
set(PACPUS_MINOR_VERSION 0)
set(PACPUS_PATCH_VERSION 1)
set(PACPUS_VERSION
    "${PACPUS_MAJOR_VERSION}.${PACPUS_MINOR_VERSION}.${PACPUS_PATCH_VERSION}")

# ========================================
# CMake variables
# ========================================
set(IS_BUILDING_PACPUS      TRUE)
set(PACPUS_ROOT_DIR         ${CMAKE_SOURCE_DIR})
set(PACPUS_3RD_PARTY_DIR    ${PACPUS_ROOT_DIR}/3rd)
set(PACPUS_CMAKE_DIR        ${PACPUS_ROOT_DIR}/cmake)
set(PACPUS_DOC_DIR          ${PACPUS_ROOT_DIR}/doc)
set(PACPUS_INCLUDE_DIR      ${PACPUS_ROOT_DIR}/include/)
set(PACPUS_SCRIPTS_DIR      ${PACPUS_ROOT_DIR}/scripts)
set(PACPUS_SOURCE_DIR       ${PACPUS_ROOT_DIR}/src)

# ========================================
# Configure CMake
# ========================================
list(APPEND CMAKE_MODULE_PATH ${PACPUS_CMAKE_DIR})

# ========================================
# Import some functions
# ========================================
include(${PACPUS_CMAKE_DIR}/PacpusUtilities.cmake)

# ========================================
# Configure Pacpus
# ========================================
include(${PACPUS_CMAKE_DIR}/PacpusConfiguration.cmake)

# ========================================
# Find dependencies
# ========================================
include(${PACPUS_CMAKE_DIR}/PacpusDependencies.cmake)

# ========================================
# Handle platform specific behaviors
# ========================================
include(${PACPUS_CMAKE_DIR}/PacpusPlatforms.cmake)

# ========================================
# Pre-configuration of the compiler
# ========================================
# Includes directories
include_directories(
  ${PACPUS_DEPENDENCIES_INC}
  ${PACPUS_INCLUDE_DIR}
)
# Compiler flags coming from PacpusDependencies and PacpusPlatforms
add_definitions(${PACPUS_DEFINITIONS})

# ========================================
# Build the Pacpus' modules
# ========================================
add_subdirectory(${PACPUS_SOURCE_DIR})

# ========================================
# Build the documentation if enabled
# ========================================
if(PACPUS_BUILD_DOC)
    add_subdirectory(${PACPUS_DOC_DIR})
endif()

# ========================================
# Pacpus Installation
# ========================================
include(${PACPUS_CMAKE_DIR}/PacpusInstall.cmake)
set( ENV{PACPUS_ROOT} ${PACPUS_INSTALL_DIR} )

# ========================================
# Summary
# ========================================
pacpus_info("")
pacpus_info("=====================================================================")
pacpus_info("Configuration for Pacpus ${PACPUS_VERSION}")
pacpus_info("=====================================================================")
pacpus_info("")
pacpus_info("  Platform:")
pacpus_info("    Host:" ${CMAKE_HOST_SYSTEM_NAME} ${CMAKE_HOST_SYSTEM_VERSION} ${CMAKE_HOST_SYSTEM_PROCESSOR})
if(CMAKE_CROSS_COMPILING)
    pacpus_info("    Target:" ${CMAKE_SYSTEM_NAME} ${CMAKE_SYSTEM_VERSION} ${CMAKE_SYSTEM_PROCESSOR})
endif()
pacpus_info("    CMake:" ${CMAKE_VERSION})
pacpus_info("    CMake generator:" ${CMAKE_GENERATOR})
pacpus_info("    CMake build tool:" ${CMAKE_BUILD_TOOL})
if(MSVC)
    pacpus_info("    MSVC:" ${MSVC_VERSION})
else()
    pacpus_info("    Configuration:" ${CMAKE_BUILD_TYPE})
endif()
pacpus_info("")
pacpus_info("  Compiler:")
pacpus_info("    C++ Compiler:" ${CMAKE_CXX_COMPILER})
pacpus_info("    C++ flags (release):" ${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE})
pacpus_info("    C++ flags (debug):" ${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG})
pacpus_info("")
pacpus_info("  Result:")
pacpus_info("    Install directory:" ${PACPUS_INSTALL_DIR})
pacpus_info("    Install with version number:" ${PACPUS_INSTALL_WITH_VERSION_NUMBER})
pacpus_info("")
pacpus_info("  Options:")
pacpus_info("    Logging enabled:" ${PACPUS_USE_LOG})
pacpus_info("    Installation of 3rd party:" ${PACPUS_INSTALL_3RD})
pacpus_info("    Documentation enabled:" ${PACPUS_BUILD_DOC})
pacpus_info("")
if("${CMAKE_CURRENT_SOURCE_DIR}" STREQUAL "${CMAKE_CURRENT_BINARY_DIR}")
    message(WARNING "The source directory is the same as build directory. \"make clean\" may damage the source tree")
endif()

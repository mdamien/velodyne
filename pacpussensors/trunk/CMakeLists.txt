######################################################################################################
#                                                                                                    #
#  __________                                     _________                                          #
#  \______   \_____    ____ ______  __ __  ______/   _____/ ____   ____   _________________  ______  #
#  |     ___/\__  \ _/ ___\\____ \|  |  \/  ___/\_____  \_/ __ \ /    \ /  ___/  _ \_  __ \/  ___/   #
#  |    |     / __ \\  \___|  |_> >  |  /\___ \ /        \  ___/|   |  \\___ (  <_> )  | \/\___ \    #
#  |____|    (____  /\___  >   __/|____//____  >_______  /\___  >___|  /____  >____/|__|  /____  >   #
#                 \/     \/|__|              \/        \/     \/     \/     \/                 \/    #
#                                                                                                    #
######################################################################################################

project(PacpusSensors)
cmake_minimum_required(VERSION 2.8)

# ========================================
# PacpusSensors version
# ========================================
set(PacpusSensors_MAJOR_VERSION 0)
set(PacpusSensors_MINOR_VERSION 1)
set(PacpusSensors_PATCH_VERSION 0)
set(PacpusSensors_VERSION
    "${PacpusSensors_MAJOR_VERSION}.${PacpusSensors_MINOR_VERSION}.${PacpusSensors_PATCH_VERSION}")

# ========================================
# CMake variables
# ========================================
#set(PacpusSensors_ROOT_DIR         ${CMAKE_SOURCE_DIR})
#set(PacpusSensors_CMAKE_DIR        ${PacpusSensors_ROOT_DIR}/cmake)
#set(PacpusSensors_DOC_DIR          ${PacpusSensors_ROOT_DIR}/doc)
#set(PacpusSensors_INCLUDE_DIR      ${PacpusSensors_ROOT_DIR}/include)
set(PACPUS_INCLUDE_DIR      ${PACPUS_ROOT_DIR}/include)

# ========================================
# Configure CMake 
# ========================================
if(NOT ${PACPUS_ROOT} STREQUAL "")
	set(CMAKE_MODULE_PATH ${PACPUS_ROOT}/cmake)
	string (REPLACE "\\" "/" CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH})
	message (STATUS "setting CMAKE_MODULE_PATH to: "  ${CMAKE_MODULE_PATH})
elseif( NOT $ENV{PACPUS_ROOT} STREQUAL "")
    set(PACPUS_ROOT $ENV{PACPUS_ROOT})
	set(CMAKE_MODULE_PATH $ENV{PACPUS_ROOT}/cmake)
	string (REPLACE "\\" "/" CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH})
	message (STATUS "setting CMAKE_MODULE_PATH to: " ${CMAKE_MODULE_PATH})
    message (STATUS "PACPUS_ROOT is: " ${PACPUS_ROOT})
else()
	message (FATAL_ERROR "Environment variable PACPUS_ROOT not set, please define it in your operating system or pass it as argument to the cmake command")
endif()

    include(${CMAKE_MODULE_PATH}/PacpusUtilities.cmake)
    include(${CMAKE_MODULE_PATH}/PacpusConfiguration.cmake)
    include(${CMAKE_MODULE_PATH}/PacpusDependencies.cmake)
    include(${CMAKE_MODULE_PATH}/PacpusPlatforms.cmake)

# ========================================
# Pre-configuration of the compiler
# ========================================
find_package(Pacpus REQUIRED)
# Includes directories
if(PACPUS_FOUND)
include_directories(
  ${PACPUS_DEPENDENCIES_INC}
  ${PACPUS_INCLUDE_DIR}
)
# Compiler flags coming from PacpusDependencies and PacpusPlatforms
add_definitions(${PACPUS_DEFINITIONS})
endif(PACPUS_FOUND)


# ========================================
# Find dependencies
# ========================================
find_package(Qt4 REQUIRED)
if(QT4_FOUND)
    set(QT_USE_QTNETWORK TRUE)
    set(QT_USE_QTOPENGL TRUE)
    set(QT_USE_QTXML TRUE)
    include(${QT_USE_FILE})
    add_definitions( ${QT_DEFINITIONS} )
    add_definitions( -DQT_PLUGIN )
endif(QT4_FOUND)

include_directories(
  ${PACPUS_DEPENDENCIES_INC}
  ${PACPUS_INCLUDE_DIR}
  ${PACPUS_INCLUDE_HINT}
  ${PACPUS_INCLUDE_HINT}/Pacpus
  ./PACPUS/include
)

# ========================================
# Build the PacpusSensors' modules
# ========================================
#add_subdirectory(Alasca)
#add_subdirectory(CanGateway)
#add_subdirectory(LMOComponent)
add_subdirectory(StdDbtPlayerComponents)
add_subdirectory(VelodyneComponent)
add_subdirectory(tx_p12)
#add_subdirectory(VelodyneViewer)        # requires -lqwtplot3d (pacpusextlib)
#add_subdirectory(Dualshock)
#add_subdirectory(Wifibot)
#add_subdirectory(PacpusSocket)

# ========================================
# Summary
# ========================================
pacpus_info("")
pacpus_info("=====================================================================")
pacpus_info("Configuration for PacpusSensors ${PacpusSensors_VERSION}")
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
pacpus_info("  Pacpus:")
pacpus_info("    PacpusFramework path:" ${PACPUS_ROOT})
pacpus_info("    Log4cxx logging enabled:" ${PACPUS_USE_LOG})
pacpus_info("")
if("${CMAKE_CURRENT_SOURCE_DIR}" STREQUAL "${CMAKE_CURRENT_BINARY_DIR}")
    message(WARNING "The source directory is the same as build directory. \"make clean\" may damage the source tree")
endif()

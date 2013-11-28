#################################################
#   ___________    ____ ______  __ __  _____    #
#   \____ \__  \ _/ ___\\____ \|  |  \/  ___/   #
#   |  |_> > __ \\  \___|  |_> >  |  /\___ \    #
#   |   __(____  /\___  >   __/|____//____  >   #
#   |__|       \/     \/|__|              \/    #
#                                               #
#################################################

# ========================================
# Output
# ========================================
set(PACPUS_DEFINITIONS "")
set(PACPUS_DEPENDENCIES_INC "")
set(PACPUS_DEPENDENCIES_LIB "")

# ========================================
# All the Pacpus' modules depends from Qt4
# However, since each module requires specific Qt's modules, they have to include their own QT_USE_FILE
# ========================================
find_package(Qt4 REQUIRED)

# ========================================
# Boost
# Do not use compiled modules, include-only headers.
# ========================================
find_package(Boost 1.49.0 REQUIRED)
list(APPEND PACPUS_DEPENDENCIES_INC ${Boost_INCLUDE_DIRS})

# ========================================
# log4cxx
# ========================================
if(PACPUS_USE_LOG)
    find_package(log4cxx REQUIRED)

    list(APPEND PACPUS_DEFINITIONS " -DPACPUS_USE_LOG ")
    list(APPEND PACPUS_DEPENDENCIES_INC ${LOG4CXX_INCLUDE_DIRS})
    list(APPEND PACPUS_DEPENDENCIES_LIB ${LOG4CXX_LIBRARIES})

    # If needed, install the dll of log4cxx
    if(WIN32 AND MSVC AND IS_BUILDING_PACPUS)
        pacpus_get_msvc(MSVC_VERSION)
        pacpus_purge_backslash(LOG4CXX_ROOT)

        install(
            FILES
                ${LOG4CXX_ROOT}/bin/${MSVC_VERSION}/log4cxx.dll
                ${LOG4CXX_ROOT}/bin/${MSVC_VERSION}/log4cxx_d.dll
            DESTINATION
                ${PACPUS_INSTALL_DIR}/bin
        )
    endif()
endif()

# ========================================
# Doxygen
# ========================================
if(PACPUS_BUILD_DOC)
    find_package(Doxygen)
    if(NOT DOXYGEN_FOUND)
        message(FATAL_ERROR "Doxygen is needed to build the documentation. Please install it correctly")
    endif()
endif()
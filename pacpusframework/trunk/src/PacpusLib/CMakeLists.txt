#################################################
#   ___________    ____ ______  __ __  _____    #
#   \____ \__  \ _/ ___\\____ \|  |  \/  ___/   #
#   |  |_> > __ \\  \___|  |_> >  |  /\___ \    #
#   |   __(____  /\___  >   __/|____//____  >   #
#   |__|       \/     \/|__|              \/    #
#                                               #
#################################################
project(PacpusLib)

# ========================================
# Configure qt4
# ========================================
if(QT4_FOUND)
    set(QT_USE_QTXML true)
    include(${QT_USE_FILE})
else()
    message(ERROR "Qt4 needed")
endif()

# ========================================
# Compiler definitions
# ========================================
add_definitions(
    -DPACPUSLIB_EXPORTS
    -DQT_NO_KEYWORDS
    ${QT_DEFINITIONS}
)

# ========================================
# Include directories
# ========================================
include_directories(
    ${QT_INCLUDE_DIR}
)

# ========================================
# List of sources
# ========================================
set(
    PROJECT_SRCS
    ${PACPUS_INCLUDE_DIR}/Pacpus/kernel/cstdint.h
    ${PACPUS_INCLUDE_DIR}/Pacpus/kernel/ComponentBase.h
    ${PACPUS_INCLUDE_DIR}/Pacpus/kernel/ComponentFactory.h
    ${PACPUS_INCLUDE_DIR}/Pacpus/kernel/ComponentFactoryBase.h
    ${PACPUS_INCLUDE_DIR}/Pacpus/kernel/ComponentManager.h
    ${PACPUS_INCLUDE_DIR}/Pacpus/kernel/Log.h
    ${PACPUS_INCLUDE_DIR}/Pacpus/kernel/pacpus.h
    ${PACPUS_INCLUDE_DIR}/Pacpus/kernel/PacpusApplication.h
    ${PACPUS_INCLUDE_DIR}/Pacpus/kernel/PacpusException.h
    ${PACPUS_INCLUDE_DIR}/Pacpus/kernel/PacpusLibConfig.h
    ${PACPUS_INCLUDE_DIR}/Pacpus/kernel/road_time.h
    ${PACPUS_INCLUDE_DIR}/Pacpus/kernel/XmlComponentConfig.h
    ${PACPUS_INCLUDE_DIR}/Pacpus/kernel/XmlConfigFile.h
    ./ComponentBase.cpp
    ./ComponentFactoryBase.cpp
    ./ComponentManager.cpp
    ./Log.cpp
    ./PacpusApplication.cpp
    ./PacpusException.cpp
    ./XmlComponentConfig.cpp
    ./XmlConfigFile.cpp
)

# ========================================
# Build a library
# ========================================
pacpus_add_library(
    ${PROJECT_NAME} SHARED
    ${PROJECT_SRCS}
)

# ========================================
# Libraries
# ========================================
target_link_libraries(
    ${PROJECT_NAME}
    ${QT_LIBRARIES}
    ${PACPUS_DEPENDENCIES_LIB}
)

# ========================================
# Install
# ========================================
pacpus_install(${PROJECT_NAME})

# ========================================
# Folder
# ========================================
pacpus_folder(${PROJECT_NAME} "libraries")

#################################################
#   ___________    ____ ______  __ __  _____    #
#   \____ \__  \ _/ ___\\____ \|  |  \/  ___/   #
#   |  |_> > __ \\  \___|  |_> >  |  /\___ \    #
#   |   __(____  /\___  >   __/|____//____  >   #
#   |__|       \/     \/|__|              \/    #
#                                               #
#################################################
project(DBITEPlayer)

# ========================================
# Configure qt4
# ========================================
if(QT4_FOUND)
  set(QT_USE_QTXML true)
  set(QT_USE_QTNETWORK true)
  include(${QT_USE_FILE})
else()
  message(ERROR "Qt4 needed")
endif()

# ========================================
# Compiler definitions
# ========================================
add_definitions(
    ${QT_DEFINITIONS}
)

# ========================================
# Include directories
# ========================================
include_directories(
    ${CMAKE_BINARY_DIR}/DBITEPlayer
    ${QT_INCLUDE_DIR}
)

# ========================================
# List of sources
# ========================================
set(
    PROJECT_SRCS
    ${PACPUS_INCLUDE_DIR}/Pacpus/kernel/cstdint.h
    ${PACPUS_INCLUDE_DIR}/Pacpus//kernel/ComponentBase.h
    ${PACPUS_INCLUDE_DIR}/Pacpus/kernel/ComponentFactory.h
    ${PACPUS_INCLUDE_DIR}/Pacpus/kernel/ComponentFactoryBase.h
    ${PACPUS_INCLUDE_DIR}/Pacpus/kernel/ComponentManager.h
    ${PACPUS_INCLUDE_DIR}/Pacpus/kernel/Log.h
    ${PACPUS_INCLUDE_DIR}/Pacpus/kernel/pacpus.h
    ${PACPUS_INCLUDE_DIR}/Pacpus/kernel/road_time.h
    ${PACPUS_INCLUDE_DIR}/Pacpus/kernel/XmlComponentConfig.h
    ${PACPUS_INCLUDE_DIR}/Pacpus/kernel/XmlConfigFile.h
    ./ComponentBase.cpp
    ./ComponentFactoryBase.cpp
    ./ComponentManager.cpp
    ./Log.cpp
    ./XmlComponentConfig.cpp
    ./XmlConfigFile.cpp
)

# ========================================
# Build an executable
# ========================================
pacpus_add_executable(
    ${PROJECT_NAME}
    ./src/main.cpp
)

# ========================================
# Libraries & Dependencies
# ========================================
# All the platform
target_link_libraries(
    ${PROJECT_NAME}
    ${QT_LIBRARIES}
    dbiteplayerlib
)
# Windows
if(WIN32)
    target_link_libraries(
        ${PROJECT_NAME}
        ROAD_TIME
        Winmm
    )
endif()

# ========================================
# Install
# ========================================
pacpus_install(${PROJECT_NAME})

# ========================================
# Folder
# ========================================
pacpus_folder(${PROJECT_NAME} "tools")

#################################################
#   ___________    ____ ______  __ __  _____    #
#   \____ \__  \ _/ ___\\____ \|  |  \/  ___/   #
#   |  |_> > __ \\  \___|  |_> >  |  /\___ \    #
#   |   __(____  /\___  >   __/|____//____  >   #
#   |__|       \/     \/|__|              \/    #
#                                               #
#################################################
project(PacpusSensor)

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
  ${PROJECT_BINARY_DIR}
  ${QT_INCLUDE_DIR}
)

# ========================================
# List of sources
# ========================================
set(
  PROJECT_SRCS
  src/ui/pacpusmainwindow.cpp
  src/ui/pacpusmainwindow.h
  src/main.cpp
)

# ========================================
# Qt4 stuff
# ========================================
set(SENSOR_UI_CLASSES src/ui/pacpusmainwindow.ui)
set(SENSOR_MOC_CLASSES src/ui/pacpusmainwindow.h)
qt4_wrap_ui(SENSOR_UI_SOURCES_H ${SENSOR_UI_CLASSES})
qt4_wrap_cpp(SENSOR_MOC_SOURCES ${SENSOR_MOC_CLASSES})
source_group(Main_ui FILES ${PROJECT_SRCS} )
source_group(moc FILES ${SENSOR_MOC_SOURCES} ${SENSOR_UI_SOURCES_H} )

# ========================================
# Build an executable
# ========================================
pacpus_add_executable(
    ${PROJECT_NAME}
    ./src/main.cpp
    ./src/ui/pacpusmainwindow.cpp
    ./src/ui/pacpusmainwindow.h
    ${SENSOR_MOC_SOURCES}
    ${SENSOR_UI_CLASSES}
)

# ========================================
# Libraries
# ========================================
# All the platform
target_link_libraries(
    ${PROJECT_NAME}
	${PACPUS_DEPENDENCIES_LIB}
    ${QT_LIBRARIES}
	PacpusLib
	FileLib
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

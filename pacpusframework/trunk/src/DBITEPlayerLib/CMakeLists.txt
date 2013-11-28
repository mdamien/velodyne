#################################################
#   ___________    ____ ______  __ __  _____    #
#   \____ \__  \ _/ ___\\____ \|  |  \/  ___/   #
#   |  |_> > __ \\  \___|  |_> >  |  /\___ \    #
#   |   __(____  /\___  >   __/|____//____  >   #
#   |__|       \/     \/|__|              \/    #
#                                               #
#################################################
project(dbiteplayerlib)

# ========================================
# Configure qt4
# ========================================
if(QT4_FOUND)
    set(QT_USE_QTXML true)
    set(QT_USE_QTNETWORK TRUE)
    include(${QT_USE_FILE})
else()
    message(ERROR "Qt4 needed")
endif(QT4_FOUND)

# ========================================
# Compiler definitions
# ========================================
add_definitions(
    -DDBITE_PLAYER_EXPORTS
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
    ./DbtPlyEngine.cpp
    ./DbtPlyUserInterface.cpp
    ./DbtPlyEngineStateChart.cpp
    ./DbtPlyFileManager.cpp
    ./DbtPlyTrigger.cpp
    ${PACPUS_INCLUDE_DIR}/Pacpus/DbitePlayer/DbtPlyEngine.h
    ${PACPUS_INCLUDE_DIR}/Pacpus/DbitePlayer/DbtPlyFileManager.h
    ${PACPUS_INCLUDE_DIR}/Pacpus/DbitePlayer/DbtPlyTrigger.h
    ${PACPUS_INCLUDE_DIR}/Pacpus/DbitePlayer/DbtPlyEngineStateChart.h
    ${PACPUS_INCLUDE_DIR}/Pacpus/DbitePlayer/DbtPlyUserInterface.h
)

# ========================================
# Files to MOC
# ========================================
set(
    FILES_TO_MOC
    ${PACPUS_INCLUDE_DIR}/Pacpus/DbitePlayer/DbtPlyEngine.h
    ${PACPUS_INCLUDE_DIR}/Pacpus/DbitePlayer/DbtPlyFileManager.h
    ${PACPUS_INCLUDE_DIR}/Pacpus/DbitePlayer/DbtPlyTrigger.h
    ${PACPUS_INCLUDE_DIR}/Pacpus/DbitePlayer/DbtPlyUserInterface.h
)

# ========================================
# Call MOC
# ========================================
qt4_wrap_cpp(
    PROJECT_MOC_SRCS
    ${FILES_TO_MOC}
)

# ========================================
# Directories architecture
# ========================================
SOURCE_GROUP(Core FILES ${PROJECT_SRCS} )
SOURCE_GROUP(moc FILES ${PROJECT_MOC_SRCS})

# ========================================
# Build a library
# ========================================
pacpus_add_library(
    ${PROJECT_NAME} SHARED
    ${PROJECT_SRCS}
    ${PROJECT_MOC_SRCS}
)

# ========================================
# Libraries
# ========================================
# All platform
target_link_libraries(
    ${PROJECT_NAME}
	${PACPUS_DEPENDENCIES_LIB}
    PacpusLib
	FileLib
    ${QT_LIBRARIES}
)
# Windows platform
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
pacpus_folder(${PROJECT_NAME} "libraries")

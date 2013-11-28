#################################################
#   ___________    ____ ______  __ __  _____    #
#   \____ \__  \ _/ ___\\____ \|  |  \/  ___/   #
#   |  |_> > __ \\  \___|  |_> >  |  /\___ \    #
#   |   __(____  /\___  >   __/|____//____  >   #
#   |__|       \/     \/|__|              \/    #
#                                               #
#################################################
project(PacpusTools)

# ========================================
# Configure qt4
# ========================================
if(QT4_FOUND)
    set(QT_USE_QTXML true)
    include(${QT_USE_FILE})
else()
    message(ERROR "Qt4 needed")
endif(QT4_FOUND)

# ========================================
# Compiler definitions
# ========================================
add_definitions(
	-DPACPUSTOOLS_EXPORTS
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
    ${PACPUS_INCLUDE_DIR}/Pacpus/PacpusTools/matrice.h
    ${PACPUS_INCLUDE_DIR}/Pacpus/PacpusTools/BinaryDecoder.h
    ${PACPUS_INCLUDE_DIR}/Pacpus/PacpusTools/PosixShMem.h
    ${PACPUS_INCLUDE_DIR}/Pacpus/PacpusTools/ShMem.h
    ${PACPUS_INCLUDE_DIR}/Pacpus/PacpusTools/geodesie.h
	${PACPUS_INCLUDE_DIR}/Pacpus/PacpusTools/AsyncWorkerBase.h
	${PACPUS_INCLUDE_DIR}/Pacpus/PacpusTools/PeriodicWorker.h
    ./src/matrice.cpp
    ./src/geodesie.cpp
    ./src/AsyncWorkerBase.cpp
    ./src/PeriodicWorker.cpp
)

# ========================================
# Files to MOC
# ========================================
set(
    FILES_TO_MOC
    ${PACPUS_INCLUDE_DIR}/Pacpus/PacpusTools/AsyncWorkerBase.h
    ${PACPUS_INCLUDE_DIR}/Pacpus/PacpusTools/PeriodicWorker.h
)

# ========================================
# Call MOC
# ========================================
qt4_wrap_cpp(
    PROJECT_MOC_SRCS
    ${FILES_TO_MOC}
)

# ========================================
# Platform specific sources
# ========================================
# Unix
if(UNIX)
    list(
        APPEND PROJECT_SRCS
        ${PACPUS_INCLUDE_DIR}/Pacpus/PacpusTools/PosixShMem.h
        src/PosixShMem.cpp
    )
endif()
# Windows
if(WIN32)
    list(
        APPEND PROJECT_SRCS
        ${PACPUS_INCLUDE_DIR}/Pacpus/PacpusTools/Win32ShMem.h
        src/Win32ShMem.cpp
    )
endif()

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
target_link_libraries(
    ${PROJECT_NAME}
    ${QT_LIBRARIES}
    ${PACPUS_DEPENDENCIES_LIB}
	PacpusLib
)


# ========================================
# Install
# ========================================
pacpus_install(${PROJECT_NAME})

# ========================================
# Folder
# ========================================
pacpus_folder(${PROJECT_NAME} "libraries")

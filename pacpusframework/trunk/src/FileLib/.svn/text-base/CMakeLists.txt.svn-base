#################################################
#   ___________    ____ ______  __ __  _____    #
#   \____ \__  \ _/ ___\\____ \|  |  \/  ___/   #
#   |  |_> > __ \\  \___|  |_> >  |  /\___ \    #
#   |   __(____  /\___  >   __/|____//____  >   #
#   |__|       \/     \/|__|              \/    #
#                                               #
#################################################
project(FileLib)

# ========================================
# Compiler definitions
# ========================================
add_definitions(
    -DFILELIB_EXPORTS
)

# ========================================
# List of sources
# ========================================
set(
    PROJECT_SRCS
    ${PACPUS_INCLUDE_DIR}/Pacpus/kernel/DbiteException.h
    ${PACPUS_INCLUDE_DIR}/Pacpus/kernel/DbiteFile.h
    ${PACPUS_INCLUDE_DIR}/Pacpus/kernel/DbiteFileTypes.h
    ${PACPUS_INCLUDE_DIR}/Pacpus/kernel/FileLibConfig.h
    ${PACPUS_INCLUDE_DIR}/Pacpus/kernel/hdfile_header_t
    ${PACPUS_INCLUDE_DIR}/Pacpus/kernel/road_time.h
    src/DbiteException.cpp
    src/DbiteFile.cpp
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

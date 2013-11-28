project(PacpusDataCollector)
################################################################################
add_definitions( -DPACPUSDATACOLLECTOR_EXPORTS )

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
# Link directories
# ========================================
link_directories(
)

pacpus_plugin(PLUGIN_CPP PLUGIN_H ${PROJECT_NAME} )

# ========================================
# List of sources
# ========================================
set(
    PROJECT_SRCS
    PacpusDataCollector.cpp
    ${PLUGIN_CPP}
)

# ========================================
# Files to MOC
# ========================================
set(
    FILES_TO_MOC
    PacpusDataCollector.h
    ${PLUGIN_H}
)

set(
    UI_FILES

)

# ========================================
# Call MOC
# ========================================
qt4_wrap_cpp(
    PROJECT_MOC_SRCS
    ${FILES_TO_MOC}
)

qt4_wrap_ui(
    PROJECT_UI_SRCS
    ${UI_FILES}
)

# ========================================
# Build a library
# ========================================
pacpus_add_library(
    ${PROJECT_NAME} SHARED
    ${PROJECT_SRCS}
    ${PROJECT_MOC_SRCS}
    ${PROJECT_UI_SRCS}
)

# ========================================
# Libraries
# ========================================
# All the platform
target_link_libraries(
    ${PROJECT_NAME}
    ${PACPUS_LIBRARIES}
    ${QT_LIBRARIES}
	${PACPUS_DEPENDENCIES_LIB}	
	C:/Pacpus/0.0.1/lib/PacpusSocket.lib
)

# ========================================
# Install
# ========================================
pacpus_install(${PROJECT_NAME})
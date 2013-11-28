project(VtkPlotInterface)

cmake_minimum_required(VERSION 2.8)

#Tell cmake that this project needs to use VTK.
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

add_definitions(-DPLUGINLIB_EXPORTS)

set(PROJECT_SOURCE_FILES 
    # add your sources file to compile here
    VtkPlotInterface.cpp
    VtkPlotInterface.h
    VtkPlotViewer.cpp
    VtkPlotViewer.h
    Curve.cpp
    Curve.h
    VtkCurve.cpp
    VtkCurve.h
)
  
set(FILES_TO_MOC 
    # add here the header files that you want to MOC
    #VtkPlotInterface.h
    #VtkPlotViewer.h
)
  
set(LIB_TO_LINK
    # add your specific libraries to link here
    vtkHybrid
    vtkRendering
    QVTK
)
#set(CMAKE_BUILD_TYPE Debug)

#common directives for creating the plugin

include(${PACPUSDEV_CMAKE_DIR}/GlobalCmakePacpus.txt)
include(${PACPUSDEV_CMAKE_DIR}/PacpusPlugin.cmake)
pacpus_plugin(PLUGIN_CPP PLUGIN_H ${PROJECT_NAME} )

include_directories(${PACPUSINCLUDE_DIRECTORY})
 
message("Creating source files for the plugin(s)")
message(STATUS PLUGIN_H=${PLUGIN_H})
message(STATUS PLUGIN_CPP=${PLUGIN_CPP})

qt4_wrap_cpp(PLUGIN_MOC_SOURCES 
    ${PLUGIN_H}
    ${FILES_TO_MOC}
)

add_library(${PROJECT_NAME} SHARED
    ${PROJECT_SOURCE_FILES}
    ${PLUGIN_CPP}
    ${PLUGIN_MOC_SOURCES}
)

target_link_libraries(${PROJECT_NAME} PacpusTools PacpusLib FileLib ${QT_LIBRARIES} ${LIB_TO_LINK})

set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX "_d" )
# FOLDERS
if(PACPUS_FOLDERS)
    set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "components")
endif()

################################################################################
# INSTALL
install(TARGETS ${PROJECT_NAME} 
    RUNTIME DESTINATION ${PACPUSBIN_DIRECTORY}
    LIBRARY DESTINATION ${PACPUSBIN_DIRECTORY}
    ARCHIVE DESTINATION ${PACPUSLIB_DIRECTORY}
)

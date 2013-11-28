project(VelodyneViewer)

pacpus_plugin(PLUGIN_CPP PLUGIN_H ${PROJECT_NAME})

################################################################################
add_definitions( -DVELODYNEVIEWER_EXPORTS )

################################################################################
# Qt4
qt4_wrap_cpp(PROJECT_MOC_SOURCES
    VelodyneViewer.h
    glWidget.h
    ${PLUGIN_H}
)
source_group(moc FILES ${PROJECT_MOC_SOURCES})

################################################################################
include_directories(${PACPUSINCLUDE_DIRECTORY})
link_directories(${PACPUSLIB_DIRECTORY})
link_directories(${PACPUSBIN_DIRECTORY})

################################################################################
# OpenGL
find_package(OpenGL REQUIRED)
link_directories(${OPENGL_LIBRARIES})

################################################################################
# BUILD AND LINK
add_definitions( -DQWT3D_DLL )
add_library(${PROJECT_NAME} SHARED
    VelodyneViewer.cpp
    glWidget.cpp
    ${PLUGIN_CPP}
    ${PROJECT_MOC_SOURCES}
)
# LIBS
list(APPEND LIBS
    optimized FileLib debug FileLib_d
    optimized PacpusLib debug PacpusLib_d
    optimized PacpusTools debug PacpusTools_d
    ${OPENGL_LIBRARIES}
    ${QT_LIBRARIES}
    optimized qwtplot3d debug qwtplot3d_d
)
if(WIN32)
    list(APPEND LIBS
        optimized ROAD_TIME debug ROAD_TIME_d
    )
endif()
# LINK
target_link_libraries(${PROJECT_NAME} ${LIBS})
# PROPERTIES
set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX "_d")
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

project(DbtPlyVelodyne)

################################################################################
add_definitions( -DDBTPLYVELODYNE_EXPORTS )

################################################################################
# FILES
set(HDRS
    DbtPlyVelodyneManager.cpp
    DbtPlyVelodyneManager.h
)

set(SRCS
    DbtPlyVelodyneManager.cpp
    DbtPlyVelodyneManager.h
)

set(FILES_TO_MOC
    DbtPlyVelodyneManager.h
)

################################################################################
#common directives for creating the plugin
include(${PACPUSDEV_CMAKE_DIR}/PacpusPlugin.cmake )
pacpus_plugin(PLUGIN_CPP PLUGIN_H ${PROJECT_NAME} )

message("Creating source files for the plugin(s)")
message(STATUS PLUGIN_H=${PLUGIN_H})
message(STATUS PLUGIN_CPP=${PLUGIN_CPP})

################################################################################
include_directories(${PACPUSINCLUDE_DIRECTORY})
link_directories(${PACPUSLIB_DIRECTORY})
link_directories(${PACPUSBIN_DIRECTORY})

qt4_wrap_cpp(PLUGIN_MOC_SOURCES
    ${PLUGIN_H}
    ${FILES_TO_MOC}
)

################################################################################
# BUILD and LINK
add_library(${PROJECT_NAME} SHARED
    ${HDRS}
    ${SRCS}
    ${PLUGIN_CPP}
    ${PLUGIN_MOC_SOURCES}
)
# LIBS
list(APPEND LIBS
    optimized dbiteplayerlib debug dbiteplayerlib_d
    optimized FileLib debug FileLib_d
    optimized PacpusLib debug PacpusLib_d
    optimized PacpusTools debug PacpusTools_d
    ${QT_LIBRARIES}
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
    set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "DbtPly")
endif()

################################################################################
# INSTALL
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION ${PACPUSBIN_DIRECTORY}
    LIBRARY DESTINATION ${PACPUSBIN_DIRECTORY}
    ARCHIVE DESTINATION ${PACPUSLIB_DIRECTORY}
)

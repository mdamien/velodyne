project(DummyPacpusPlugin)

cmake_policy(SET CMP0015 NEW)

################################################################################
add_definitions( -DDUMMYPACPUSPLUGIN_EXPORTS )

################################################################################
# FILES
set(PROJECT_SOURCE_FILES
  )

set(FILES_TO_MOC
  )

set(LIB_TO_LINK
  )

#######################################################################################
#######################################################################################
#common directives for creating the plugin
include(${PACPUSINCLUDE_DIRECTORY}/../cmake_modules/PacpusPlugin.cmake )
pacpus_plugin(PLUGIN_CPP PLUGIN_H ${PROJECT_NAME} )

# for Qt Plugin
find_package(Qt4 REQUIRED)
set(QT_USE_QTXML true)
include(${QT_USE_FILE})
include_directories(${QT_INCLUDE_DIR})
link_directories (${QT_LIBRARIES})
add_definitions(${QT_DEFINITIONS})
add_definitions(-DQT_PLUGIN)

include_directories(${PACPUSINCLUDE_DIRECTORY})
link_directories(${PACPUSLIB_DIRECTORY})
link_directories(${PACPUSBIN_DIRECTORY})

message("Creating source files for the plugin")
message(STATUS PLUGIN_H=${PLUGIN_H})
message(STATUS PLUGIN_CPP=${PLUGIN_CPP})

qt4_wrap_cpp(PLUGIN_MOC_SOURCES
    ${PLUGIN_H}
    ${FILES_TO_MOC}
)

################################################################################
# BUILD AND LINK
add_library(${PROJECT_NAME} SHARED
  ${PROJECT_SOURCE_FILES}
  ${PLUGIN_CPP}
  ${PLUGIN_MOC_SOURCES}
)
# LIBS
list(APPEND LIBS
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
    set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "tutorials")
endif()

################################################################################
# INSTALL
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION ${PACPUSBIN_DIRECTORY}
    LIBRARY DESTINATION ${PACPUSBIN_DIRECTORY}
    ARCHIVE DESTINATION ${PACPUSLIB_DIRECTORY}
)

project(DbtPlyDummy)

cmake_policy(SET CMP0015 NEW)

################################################################################
add_definitions( -DDBTPLYDUMMY_EXPORTS )

################################################################################
# FILES
set(SRCS
    DbtPlyDummy.cpp
)
set(HDRS
    DbtPlyDummy.h
)
set(MOC_FILES
    DbtPlyDummy.h
)

################################################################################
# PACPUS
#common directives for creating the plugin
pacpus_plugin(PLUGIN_CPP PLUGIN_H ${PROJECT_NAME})

################################################################################
# Qt4
# for Qt Plugin
find_package(Qt4 REQUIRED)
if(QT4_FOUND)
    set(QT_USE_QTXML true)
    include(${QT_USE_FILE})
    include_directories(${QT_INCLUDE_DIR})
    link_directories (${QT_LIBRARIES})
    add_definitions( ${QT_DEFINITIONS} )
    add_definitions( -DQT_PLUGIN )
endif()

message("Creating source files for the plugin(s)")
message(STATUS PLUGIN_H=${PLUGIN_H})
message(STATUS PLUGIN_CPP=${PLUGIN_CPP})

qt4_wrap_cpp(MOC_SRCS
    ${PLUGIN_H}
    ${MOC_FILES}
)

################################################################################
# BUILD
add_library(${PROJECT_NAME} SHARED
    ${SRCS}
    ${HDRS}
    ${PLUGIN_CPP}
    ${MOC_SRCS}
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
endif(WIN32)
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

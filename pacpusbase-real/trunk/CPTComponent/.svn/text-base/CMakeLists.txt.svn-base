project(CPTComponent)

################################################################################
add_definitions( -DCPTCOMPONENT_EXPORTS )
add_definitions( -DPLUGINLIB_EXPORTS ) 

################################################################################
# FILES
set(HDRS
    CPTComponent.h
    ${CMAKE_SOURCE_DIR}/driver/AbstractSerialPort.h
)
set(SRCS
    CPTComponent.cpp
    ${CMAKE_SOURCE_DIR}/driver/AbstractSerialPort.cpp
)

if(UNIX)
    list(APPEND HDRS
        ${CMAKE_SOURCE_DIR}/driver/PosixSerialPort.h
    )
    list(APPEND SRCS
        ${CMAKE_SOURCE_DIR}/driver/PosixSerialPort.cpp
    )
endif(UNIX)
if(WIN32)
    list(APPEND HDRS
        ${CMAKE_SOURCE_DIR}/driver/win32SerialPort.h
    )
    list(APPEND SRCS
        ${CMAKE_SOURCE_DIR}/driver/win32SerialPort.cpp
    )
endif(WIN32)

set(FILES_TO_MOC 
    # add here the header files that you want to MOC
    ${CMAKE_SOURCE_DIR}/driver/PosixSerialPort.h
    CPTComponent.h
)

if(UNIX)
    list(APPEND FILES_TO_MOC
        ${CMAKE_SOURCE_DIR}/driver/PosixSerialPort.h
    )
endif(UNIX)
if(WIN32)
    list(APPEND FILES_TO_MOC
        ${CMAKE_SOURCE_DIR}/driver/win32SerialPort.h
    )
endif(WIN32)

pacpus_plugin(PLUGIN_CPP PLUGIN_H ${PROJECT_NAME})

################################################################################
include_directories(${PACPUSINCLUDE_DIRECTORY})
link_directories(${PACPUSLIB_DIRECTORY})
link_directories(${PACPUSBIN_DIRECTORY})

message("Creating source files for the plugin(s)")
message(STATUS PLUGIN_H=${PLUGIN_H})
message(STATUS PLUGIN_CPP=${PLUGIN_CPP})

qt4_wrap_cpp(PLUGIN_MOC_SOURCES 
    ${PLUGIN_H}
    ${FILES_TO_MOC}
)

################################################################################
# BUILD AND LINK
add_library(${PROJECT_NAME} SHARED
    ${HDRS}
    ${SRCS}
    ${PLUGIN_CPP}
    ${PLUGIN_MOC_SOURCES}
)
# LIBS
list(APPEND LIBS
    optimized FileLib debug FileLib_d
    optimized PacpusLib debug PacpusLib_d
    optimized PacpusTools debug PacpusTools_d
    optimized NMEA0183LIB debug NMEA0183LIB_d
    ${QT_LIBRARIES}
    ${OpenCV_LIBS}
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

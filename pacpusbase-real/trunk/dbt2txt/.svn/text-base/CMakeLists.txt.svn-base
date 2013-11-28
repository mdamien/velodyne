project(dbt2txt)

################################################################################
# INCLUDES
include_directories(${PACPUSINCLUDE_DIRECTORY})
link_directories(${PACPUSLIB_DIRECTORY})
link_directories(${PACPUSBIN_DIRECTORY})

################################################################################
set(SRCS
    main.cpp
    AlascaConverter.cpp
    DbiteConverter.cpp
    SpanCptConverter.cpp
    VelodyneConverter.cpp
)

set(HDRS
    AlascaConverter.h
    DbiteConverter.h
    SpanCptConverter.h
    VelodyneConverter.h
)

################################################################################
# BUILD and LINK
add_executable(${PROJECT_NAME}
    ${SRCS}
    ${HDRS}
)
message("PACPUS_LOG_LIBRARIES = ${PACPUS_LOG_LIBRARIES}")
# LIBS
list(APPEND LIBS
    optimized FileLib debug FileLib_d
    optimized NMEA0183LIB debug NMEA0183LIB_d
    optimized PacpusLib debug PacpusLib_d
    ${PACPUS_LOG_LIBRARIES}
    ${OpenCV_LIBS}
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
    set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "tools")
endif()

################################################################################
# INSTALL
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION ${PACPUSBIN_DIRECTORY}
)

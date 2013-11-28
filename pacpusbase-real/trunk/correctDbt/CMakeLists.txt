project(correctDbt)

################################################################################
include_directories(${PACPUSINCLUDE_DIRECTORY})
link_directories(${PACPUSLIB_DIRECTORY})
link_directories(${PACPUSBIN_DIRECTORY})

################################################################################
# BUILD and LINK
add_executable(${PROJECT_NAME}
    main.cpp
)

list(APPEND LIBS
    optimized FileLib debug FileLib_d
    #optimized PacpusLib debug PacpusLib_d
    ${PACPUS_LOG_LIBRARIES}
)
if(WIN32)
    list(APPEND LIBS ROAD_TIME)
endif(WIN32)

target_link_libraries(${PROJECT_NAME} ${LIBS})
set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX "_d")
# FOLDERS
if(PACPUS_FOLDERS)
    set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "tools")
endif()

################################################################################
# INSTALL
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION ${PACPUSBIN_DIRECTORY}
    LIBRARY DESTINATION ${PACPUSBIN_DIRECTORY}
    ARCHIVE DESTINATION ${PACPUSLIB_DIRECTORY}
)

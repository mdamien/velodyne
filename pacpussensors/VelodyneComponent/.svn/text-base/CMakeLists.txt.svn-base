project(VelodyneHDL64S2)

################################################################################
add_definitions( -DVELODYNEHDL64S2_EXPORTS )

################################################################################
# FILES
set(PROJECT_SOURCE_FILES 
    # add your sources file to compile here
    VelodyneComponent.cpp
)
  
set(FILES_TO_MOC 
    # add here the header files that you want to MOC
    VelodyneComponent.h
)
  
list(APPEND LIBS
    # add your specific libraries to link here
)

pacpus_plugin(PLUGIN_CPP PLUGIN_H ${PROJECT_NAME})

include_directories(${PACPUSINCLUDE_DIRECTORY})
link_directories(${PACPUSLIB_DIRECTORY})
link_directories(${PACPUSBIN_DIRECTORY})

message ("Creating source files for the plugin(s)")
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
    set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "components")
endif()

################################################################################
# INSTALL
install(TARGETS ${PROJECT_NAME} 
    RUNTIME DESTINATION ${PACPUSBIN_DIRECTORY} 
    LIBRARY DESTINATION ${PACPUSBIN_DIRECTORY} 
    ARCHIVE DESTINATION ${PACPUSLIB_DIRECTORY} 
)

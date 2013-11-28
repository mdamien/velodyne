#################################################
#   ___________    ____ ______  __ __  _____    #
#   \____ \__  \ _/ ___\\____ \|  |  \/  ___/   #
#   |  |_> > __ \\  \___|  |_> >  |  /\___ \    #
#   |   __(____  /\___  >   __/|____//____  >   #
#   |__|       \/     \/|__|              \/    #
#                                               #
#################################################

if(PACPUS_BUILD_DOC)
    # Debug
    pacpus_info("Adding target: documentation")
    # Configure the template Doxyfile for our specific project
    configure_file(doxyfile.in ${CMAKE_BINARY_DIR}/Doxyfile @ONLY IMMEDIATE)
    # Add a custom target to run Doxygen when ever the project is built
    add_custom_target (
        documentation 
        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_BINARY_DIR}/Doxyfile
        SOURCES ${CMAKE_BINARY_DIR}/Doxyfile)
endif()

#################################################
#   ___________    ____ ______  __ __  _____    #
#   \____ \__  \ _/ ___\\____ \|  |  \/  ___/   #
#   |  |_> > __ \\  \___|  |_> >  |  /\___ \    #
#   |   __(____  /\___  >   __/|____//____  >   #
#   |__|       \/     \/|__|              \/    #
#                                               #
#################################################

# ========================================
# CMake files
# ========================================
install(
    DIRECTORY
        ${PACPUS_CMAKE_DIR}
    DESTINATION
        ${PACPUS_INSTALL_DIR}
)

# ========================================
# Include files
# ========================================
install(
    DIRECTORY
        ${PACPUS_INCLUDE_DIR}
    DESTINATION
        ${PACPUS_INSTALL_DIR}/include
)

# ========================================
# Installation of the 3rd party
# ========================================
if(PACPUS_INSTALL_3RD)
	if(WIN32)
		install(
		DIRECTORY
			${PACPUS_3RD_PARTY_DIR}
		DESTINATION
			${PACPUS_INSTALL_DIR}
			)
	endif()
endif()

# ========================================
# Installation of the documentation
# ========================================
if(PACPUS_BUILD_DOC)
    install(
        DIRECTORY
            ${CMAKE_BINARY_DIR}/doc/html
        DESTINATION
            ${PACPUS_INSTALL_DIR}/doc
    )
endif()

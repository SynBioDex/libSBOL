FIND_PACKAGE( Doxygen )

IF( DOXYGEN_FOUND )

    CONFIGURE_FILE(
        ${SBOL_MANUAL_DIR}/Doxyfile.in
        ${SBOL_MANUAL_DIR}/Doxyfile
    )

    ADD_CUSTOM_TARGET( sbol_manual
        ALL
        ${DOXYGEN_EXECUTABLE}
        ${SBOL_MANUAL_DIR}/Doxyfile
        WORKING_DIRECTORY ${SBOL_RELEASE_DIR}
    )

ELSE()

    MESSAGE( "Doxygen not found; unable to generate documentation" )

ENDIF()

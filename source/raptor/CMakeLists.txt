# Get the binaries for the dependencies
SET( LINK_DIR				${CMAKE_CURRENT_SOURCE_DIR}/lib )
IF (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    FIND_LIBRARY(raptor2
        NAME raptor2.lib
        PATHS ${LINK_DIR}
        )
	FIND_LIBRARY(xml2
		NAME libxml2_a.lib
		PATHS ${LINK_DIR}
		)
	FIND_LIBRARY(zlib
		NAME zlib.lib
		PATHS ${LINK_DIR}
		)
	FIND_LIBRARY(iconv
		NAME iconv_a.lib
		PATHS ${LINK_DIR}
		)
	MESSAGE(${raptor2})
	INSTALL(FILES ${LINK_DIR}/raptor2.lib DESTINATION lib)
	INSTALL(FILES ${LINK_DIR}/libxml2_a.lib DESTINATION lib)
	INSTALL(FILES ${LINK_DIR}/zlib.lib DESTINATION lib)
	INSTALL(FILES ${LINK_DIR}/iconv_a.lib DESTINATION lib)
ELSE ()
    FIND_LIBRARY (raptor2 NAMES libraptor2.a raptor)
    FIND_LIBRARY (xml2 xml2)
    FIND_LIBRARY (zlib z)
    FIND_LIBRARY (iconv iconv)
ENDIF ()

# Copy the Raptor library headers over
SET( RAPTOR_HEADER_DIR		${CMAKE_CURRENT_SOURCE_DIR}/include/raptor2 CACHE PATH "raptor path")
FILE(GLOB RAPTOR_HEADER_FILES 
	${RAPTOR_HEADER_DIR}/*.h )
MESSAGE(${RAPTOR_HEADER_FILES})
FILE(COPY ${RAPTOR_HEADER_FILES} DESTINATION  ${HEADER_OUTPUT_PATH} )


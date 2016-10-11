# Get the binaries for the dependencies
set( LINK_DIR				${CMAKE_CURRENT_SOURCE_DIR}/lib )
set( BUILD_SHARED_LIBS OFF )
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

ELSE ()  # If Mac OSX and Linux

    set(CMAKE_MODULE_PATH "${SBOL_SOURCE_DIR}/raptor")

    # Search for raptor library.  It is non-native on Mac OSX and must be downloaded from a package installer like Homebrew
    if(SBOL_BUILD_STATIC)
        # Search for Raptor as a static library
        set(CMAKE_FIND_LIBRARY_SUFFIXES .a .so)
        add_definitions(-DLIBXML_STATIC -DRAPTOR_STATIC -DLIBXSLT_STATIC -DCURL_STATIC)
        find_package( RAPTOR )
    else(SBOL_BUILD_STATIC)
        # Search for Raptor as a dynamic dependency
        set(CMAKE_FIND_LIBRARY_SUFFIXES .dll .dylib )
        find_package( RAPTOR )
    endif(SBOL_BUILD_STATIC)
message(${CMAKE_FIND_LIBRARY_SUFFIXES})
    # Search for curl and libxslt dependencies.  These are native system libraries on Mac OSX and can be linked dynamically.
    set(CMAKE_FIND_LIBRARY_SUFFIXES .dll .dylib )
    find_package( CURL )
    find_package( LibXslt )

ENDIF ()


FILE(GLOB RAPTOR_HEADER_FILES
	${RAPTOR_INCLUDE_DIR}/*.h )
FILE(COPY ${RAPTOR_HEADER_FILES} DESTINATION  ${HEADER_OUTPUT_PATH} )
MESSAGE("Copying ${RAPTOR_HEADER_FILES} to ${HEADER_OUTPUT_PATH}")



# Copy the Raptor library headers over
#SET( RAPTOR_HEADER_DIR		${CMAKE_CURRENT_SOURCE_DIR}/include/raptor2 CACHE PATH "raptor path")
#FILE(GLOB RAPTOR_HEADER_FILES
#	${RAPTOR_HEADER_DIR}/*.h )
#MESSAGE(${RAPTOR_HEADER_FILES})
#FILE(COPY ${RAPTOR_HEADER_FILES} DESTINATION  ${HEADER_OUTPUT_PATH} )
#
#SET( RAPTOR_INCLUDE_DIR		${CMAKE_CURRENT_SOURCE_DIR}/include/raptor2 CACHE PATH "raptor path")
#FILE(GLOB RAPTOR_HEADER_FILES
#    ${RAPTOR_INCLUDE_DIR}/*.h )
#MESSAGE(${RAPTOR_HEADER_FILES})
#FILE(COPY ${RAPTOR_HEADER_FILES} DESTINATION  ${HEADER_OUTPUT_PATH} )

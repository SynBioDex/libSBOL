# Get the binaries for the dependencies
set( LINK_DIR				${CMAKE_CURRENT_SOURCE_DIR}/lib )
set( BUILD_SHARED_LIBS OFF )
IF (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    IF(SBOL_BUILD_32)
        FIND_LIBRARY(raptor2
            NAME raptor2.lib
            PATHS ${LINK_DIR}
            )
        FIND_LIBRARY(xml2
            NAME libxml2-static.lib
            PATHS ${LINK_DIR}
            )
        FIND_LIBRARY(zlib
            NAME libz-static.lib
            PATHS ${LINK_DIR}
            )
        FIND_LIBRARY(iconv
            NAME libiconv-static.lib
            PATHS ${LINK_DIR}
            )
        INSTALL(FILES ${LINK_DIR}/raptor2.lib DESTINATION lib)
        INSTALL(FILES ${LINK_DIR}/libxml2-static.lib DESTINATION lib)
        INSTALL(FILES ${LINK_DIR}/libz-static.lib DESTINATION lib)
        INSTALL(FILES ${LINK_DIR}/libiconv-static.lib DESTINATION lib)
    ELSEIF(SBOL_BUILD_64)
        FIND_LIBRARY(raptor2
            NAME raptor2_64.lib
            PATHS ${LINK_DIR}
            )
        FIND_LIBRARY(xml2
            NAME libxml2-static_64.lib
            PATHS ${LINK_DIR}
            )
        FIND_LIBRARY(zlib
            NAME libz-static_64.lib
            PATHS ${LINK_DIR}
            )
        FIND_LIBRARY(iconv
            NAME libiconv-static_64.lib
            PATHS ${LINK_DIR}
            )
        INSTALL(FILES ${LINK_DIR}/raptor2_64.lib DESTINATION lib)
        INSTALL(FILES ${LINK_DIR}/libxml2-static_64.lib DESTINATION lib)
        INSTALL(FILES ${LINK_DIR}/libz-static_64.lib DESTINATION lib)
        INSTALL(FILES ${LINK_DIR}/libiconv-static_64.lib DESTINATION lib)
    ENDIF()
    find_path(RAPTOR_INCLUDE_DIR raptor2.h
        PATHS ${CMAKE_CURRENT_SOURCE_DIR}/include/raptor2
        )
    #MESSAGE(${raptor2})

ELSE ()  # If Mac OSX or Linux

    set(CMAKE_MODULE_PATH "${SBOL_SOURCE_DIR}/raptor")

    # Search for raptor library.  It is non-native on Mac OSX and must be downloaded from a package installer like Homebrew
    # Search for curl and libxslt dependencies.  These are native system libraries on Mac OSX and can be linked dynamically.
    if(SBOL_BUILD_STATIC)
        # Search for Raptor as a static library
        set(CMAKE_FIND_LIBRARY_SUFFIXES .so .a)
        add_definitions(-DLIBXML_STATIC -DRAPTOR_STATIC -DLIBXSLT_STATIC -DCURL_STATIC)
        find_package( RAPTOR )
        find_package( CURL )
        find_package( LibXslt )
        find_package( JsonCpp )
    else(NOT SBOL_BUILD_STATIC)
        # Search for Raptor as a dynamic dependency
        set(CMAKE_FIND_LIBRARY_SUFFIXES .dll .dylib)
        find_package( RAPTOR )
        find_package( CURL )
        find_package( LibXslt )
        find_package( JsonCpp )
    endif(SBOL_BUILD_STATIC)

ENDIF ()

MESSAGE("Found raptor2 library at ${raptor2}")

if (NOT RAPTOR_INCLUDE_DIR)
    SET( RAPTOR_INCLUDE_DIR		${CMAKE_CURRENT_SOURCE_DIR}/include/raptor2)
endif ()

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

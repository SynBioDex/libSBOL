# Get the binaries for the dependencies
set( LINK_DIR_x86				${CMAKE_CURRENT_SOURCE_DIR}/lib/x86 )
set( LINK_DIR_x64				${CMAKE_CURRENT_SOURCE_DIR}/lib/x64 )
#set( BUILD_SHARED_LIBS OFF )
IF (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    IF(SBOL_BUILD_32)
        FIND_LIBRARY(raptor2
            NAME raptor2.lib
            PATHS ${LINK_DIR_x86}
            )
        FIND_LIBRARY(xml2
            NAME libxml2.lib
            PATHS ${LINK_DIR_x86}
            )
        FIND_LIBRARY(zlib
            NAME libz.lib
            PATHS ${LINK_DIR_x86}
            )
        FIND_LIBRARY(iconv
            NAME libiconv.lib
            PATHS ${LINK_DIR_x86}
            )
        FIND_LIBRARY(jsoncpp
            NAME jsoncpp.lib
            PATHS ${LINK_DIR_x86}
            )
        FIND_LIBRARY(libcurl
            NAME libcurl.lib
            PATHS ${LINK_DIR_x86}
            )
        INSTALL(FILES ${LINK_DIR_x86}/raptor2.lib DESTINATION lib)
        INSTALL(FILES ${LINK_DIR_x86}/libxml2.lib DESTINATION lib)
        INSTALL(FILES ${LINK_DIR_x86}/libz.lib DESTINATION lib)
        INSTALL(FILES ${LINK_DIR_x86}/libiconv.lib DESTINATION lib)
        INSTALL(FILES ${LINK_DIR_x86}/jsoncpp.lib DESTINATION lib)
        INSTALL(FILES ${LINK_DIR_x86}/libcurl.lib DESTINATION lib)
    ELSEIF(SBOL_BUILD_64)
        FIND_LIBRARY(raptor2
            NAME raptor2.lib
            PATHS ${LINK_DIR_x64}
            )
        FIND_LIBRARY(xml2
            NAME libxml2.lib
            PATHS ${LINK_DIR_x64}
            )
        FIND_LIBRARY(zlib
            NAME libz.lib
            PATHS ${LINK_DIR_x64}
            )
        FIND_LIBRARY(iconv
            NAME libiconv.lib
            PATHS ${LINK_DIR_x64}
            )
        FIND_LIBRARY(jsoncpp
            NAME jsoncpp.lib
            PATHS ${LINK_DIR_x64}
            )
        FIND_LIBRARY(libcurl
            NAME libcurl.lib
            PATHS ${LINK_DIR_x64}
            )
        INSTALL(FILES ${LINK_DIR_x64}/raptor2.lib DESTINATION lib)
        INSTALL(FILES ${LINK_DIR_x64}/libxml2.lib DESTINATION lib)
        INSTALL(FILES ${LINK_DIR_x64}/libz.lib DESTINATION lib)
        INSTALL(FILES ${LINK_DIR_x64}/libiconv.lib DESTINATION lib)
        INSTALL(FILES ${LINK_DIR_x64}/jsoncpp.lib DESTINATION lib)
        INSTALL(FILES ${LINK_DIR_x64}/libcurl.lib DESTINATION lib)
    ENDIF()
    find_path(RAPTOR_INCLUDE_DIR raptor2.h
        PATHS ${CMAKE_CURRENT_SOURCE_DIR}/include/raptor2
        )
    find_path(JSONCPP_INCLUDE_DIR json.h
        PATHS ${CMAKE_CURRENT_SOURCE_DIR}/include/json
        )
    find_path(CURL_INCLUDE_DIR curl.h
        PATHS ${CMAKE_CURRENT_SOURCE_DIR}/include/curl
        )
    #MESSAGE(${raptor2})

ELSE ()  # If Mac OSX or Linux

    set(CMAKE_MODULE_PATH "${SBOL_SOURCE_DIR}/raptor")

    # Search for raptor library.  It is non-native on Mac OSX and must be downloaded from a package installer like Homebrew
    # Search for curl and libxslt dependencies.  These are native system libraries on Mac OSX and can be linked dynamically.
    if(NOT SBOL_BUILD_SHARED)
        # Search for Raptor as a static library
        set(CMAKE_FIND_LIBRARY_SUFFIXES .lib .a)
        add_definitions(-DLIBXML_STATIC -DRAPTOR_STATIC -DLIBXSLT_STATIC -DCURL_STATIC)
        find_package( RAPTOR)
        find_package( CURL )
        find_package( LibXslt )
        find_package( JsonCpp )
    endif()
    if(SBOL_BUILD_SHARED)
        # Search for Raptor as a dynamic dependency
        set(CMAKE_FIND_LIBRARY_SUFFIXES .dll .dylib .so)
        find_package( RAPTOR )
        find_package( CURL )
        find_package( LibXslt )
        find_package( JsonCpp )
    endif(SBOL_BUILD_SHARED)
ENDIF ()


if (NOT RAPTOR_INCLUDE_DIR)
    SET( RAPTOR_INCLUDE_DIR		${CMAKE_CURRENT_SOURCE_DIR}/include/raptor2)
endif ()
if (NOT JSONCPP_INCLUDE_DIR)
    SET( JSONCPP_INCLUDE_DIR		${CMAKE_CURRENT_SOURCE_DIR}/include/json)
endif ()
if (NOT CURL_INCLUDE_DIR)
    SET( CURL_INCLUDE_DIR		${CMAKE_CURRENT_SOURCE_DIR}/include/curl)
endif ()

FILE(GLOB RAPTOR_HEADER_FILES
	${RAPTOR_INCLUDE_DIR}/*.h )
FILE(GLOB JSONCPP_HEADER_FILES
	${JSONCPP_INCLUDE_DIR}/*.h )
FILE(GLOB CURL_HEADER_FILES
	${CURL_INCLUDE_DIR}/*.h )    
FILE(COPY ${RAPTOR_HEADER_FILES} DESTINATION  ${HEADER_OUTPUT_PATH} )
FILE(COPY ${JSONCPP_HEADER_FILES} DESTINATION  ${HEADER_OUTPUT_PATH}/json )
FILE(COPY ${CURL_HEADER_FILES} DESTINATION  ${HEADER_OUTPUT_PATH}/curl )


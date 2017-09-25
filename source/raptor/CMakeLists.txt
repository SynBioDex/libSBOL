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

ELSEIF (${CMAKE_SYSTEM_NAME} MATCHES "Linux")   # If Linux
    set(CMAKE_MODULE_PATH "${SBOL_SOURCE_DIR}/raptor")
    if(NOT SBOL_BUILD_SHARED)
        # Workaround for issue with dependencies built without PIC support
        # Search for Raptor and JsonCpp as a static library
        message("Using precompiled dependencies")
        unset(JsonCpp_LIBRARY CACHE)
        unset(RAPTOR_LIBRARY CACHE)
        unset(JsonCpp_INCLUDE_DIR CACHE)
        unset(RAPTOR_INCLUDE_DIR CACHE)
        unset(ZLIB_LIBRARY CACHE)
        unset(LIBXML_LIBRARY CACHE)
        unset(LIBXSLT_LIBRARY CACHE)
        unset(ZLIB_INCLUDE_DIR CACHE)
        unset(LIBXML_INCLUDE_DIR CACHE)
        unset(LIBXSLT_INCLUDE_DIR CACHE)
        set(CMAKE_FIND_LIBRARY_SUFFIXES .lib .a)
        add_definitions(-DRAPTOR_STATIC)

        FIND_LIBRARY(RAPTOR_LIBRARY
            NAME libraptor2.a
            PATHS ${CMAKE_CURRENT_SOURCE_DIR}/linux/raptor2/lib
            NO_DEFAULT_PATH
            )
        FIND_LIBRARY(JsonCpp_LIBRARY
            NAME libjsoncpp.a
            PATHS ${CMAKE_CURRENT_SOURCE_DIR}/linux/jsoncpp/lib
            NO_DEFAULT_PATH
            )
        find_path(RAPTOR_INCLUDE_DIR raptor2.h
        PATHS ${CMAKE_CURRENT_SOURCE_DIR}/linux/raptor2/include/raptor2
            NO_DEFAULT_PATH
        )
        find_path(JsonCpp_INCLUDE_DIR json
        PATHS ${CMAKE_CURRENT_SOURCE_DIR}/linux/jsoncpp/include
            NO_DEFAULT_PATH
        )   
        FIND_LIBRARY(ZLIB_LIBRARY
            NAME libz.a
            PATHS ${CMAKE_CURRENT_SOURCE_DIR}/linux/zlib/lib
            NO_DEFAULT_PATH
            )
        find_path(ZLIB_INCLUDE_DIR zlib.h
        PATHS ${CMAKE_CURRENT_SOURCE_DIR}/linux/zlib/include
        NO_DEFAULT_PATH
        )
        FIND_LIBRARY(LIBXML_LIBRARY
            NAME libxml2.a
            PATHS ${CMAKE_CURRENT_SOURCE_DIR}/linux/libxml2/lib
            NO_DEFAULT_PATH
            )
        find_path(LIBXML_INCLUDE_DIR libxml2
        PATHS ${CMAKE_CURRENT_SOURCE_DIR}/linux/libxml2/include
            NO_DEFAULT_PATH
        )
        FIND_LIBRARY(LIBXSLT_LIBRARIES
            NAME libxslt.a
            PATHS ${CMAKE_CURRENT_SOURCE_DIR}/linux/libxslt/lib
            NO_DEFAULT_PATH
            )
        find_path(LIBXSLT_INCLUDE_DIR libxslt
        PATHS ${CMAKE_CURRENT_SOURCE_DIR}/linux/libxslt/include
            NO_DEFAULT_PATH
        )
    endif()
    if(SBOL_BUILD_SHARED)
        # Search for Raptor and JsonCpp as a dynamic dependency
        unset(JsonCpp_LIBRARY CACHE)
        unset(RAPTOR_LIBRARY CACHE)
        unset(JsonCpp_INCLUDE_DIR CACHE)
        unset(RAPTOR_INCLUDE_DIR CACHE)
        set(CMAKE_FIND_LIBRARY_SUFFIXES .dll .dylib .so)
        find_package( RAPTOR )
        find_package( JsonCpp )
    endif(SBOL_BUILD_SHARED)
        set(CMAKE_FIND_LIBRARY_SUFFIXES .dll .dylib .so)
        find_package( CURL ) 

ELSE ()  # If Mac OSX
    set(CMAKE_MODULE_PATH "${SBOL_SOURCE_DIR}/raptor")
    # Search for raptor library.  It is non-native on Mac OSX and must be downloaded from a package installer like Homebrew
    # Search for curl and libxslt dependencies.  These are native system libraries on Mac OSX and can be linked dynamically.
    if(NOT SBOL_BUILD_SHARED)
        # Search for Raptor as a static library
        set(CMAKE_FIND_LIBRARY_SUFFIXES .lib .a)
        add_definitions(-DRAPTOR_STATIC)
        find_package( RAPTOR)
        find_package( JsonCpp )
    endif()
    if(SBOL_BUILD_SHARED)
        # Search for Raptor as a dynamic dependency
        set(CMAKE_FIND_LIBRARY_SUFFIXES .dll .dylib .so)
        find_package( RAPTOR )
        find_package( JsonCpp )
    endif(SBOL_BUILD_SHARED)
    set(CMAKE_FIND_LIBRARY_SUFFIXES .dll .dylib .so)
    find_package( LibXslt )
    find_package( CURL )
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


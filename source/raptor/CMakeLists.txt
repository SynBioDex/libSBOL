set(SBOL_BUILD_STATIC OFF)

if(SBOL_BUILD_STATIC)
    set(CMAKE_FIND_LIBRARY_SUFFIXES .a .so .dll .dylib)
    add_definitions(-DLIBXML_STATIC -DRAPTOR_STATIC -DLIBXSLT_STATIC -DCURL_STATIC)
else(SBOL_BUILD_STATIC)
    set(CMAKE_FIND_LIBRARY_SUFFIXES .dll .dylib )
endif(SBOL_BUILD_STATIC)

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
ELSE ()
    #FIND_LIBRARY (raptor2 NAMES libraptor2.a raptor)
    #FIND_LIBRARY (xml2 NAMES libxml2.a xml2)

    FIND_LIBRARY (zlib NAMES z PATHS /usr/local/opt/zlib/lib)
    FIND_LIBRARY (iconv NAMES iconv )
#set(iconv /usr/local/opt/libiconv/lib/libiconv.dylib CACHE FILEPATH "libiconv path")
#set(ICONV_INCLUDE_DIR  /usr/local/opt/libiconv/include/ CACHE PATH "libiconv path" )
    find_path (LIBZ_INCLUDE_DIR NAMES zlib.h PATHS /usr/local/opt/zlib/include)
    find_path (ICONV_INCLUDE_DIR NAMES iconv.h PATHS /usr/local/opt/libiconv/include  )
    set(LDAP /System/Library/Frameworks/LDAP.framework/LDAP CACHE FILEPATH "")
    set(LDAP_INCLUDE_DIR /System/Library/Frameworks/LDAP.framework/Headers CACHE FILEPATH "")

    set(CMAKE_MODULE_PATH "${SBOL_SOURCE_DIR}/raptor")

#find_package( RAPTOR )
    find_package( CURL )
    find_package( LibXslt )
    find_package(LibXml2)
    find_library(SECURITY Security)
    find_library(CORE_FOUNDATION CoreFoundation)
    set(RAPTOR_LIBRARY /usr/local/lib/libraptor2.a CACHE FILEPATH "" FORCE)
    set(RAPTOR_INCLUDE_DIR /usr/local/include/raptor2 CACHE PATH "" FORCE)

ENDIF ()


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

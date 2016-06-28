PROJECT( SBOL_TEST )
CMAKE_MINIMUM_REQUIRED( VERSION 2.8 )
cmake_policy(SET CMP0015 NEW)  # set policy for using relative paths
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


IF (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    SET( LINK_DIR ${CMAKE_INSTALL_PREFIX}/SBOL/lib )  # Windows library path
    SET( HEADER_DIR	${CMAKE_INSTALL_PREFIX}/SBOL/include   )  # Windows header path

    find_library(xml2
        NAME libxml2_a.lib
        PATHS ${LINK_DIR}
        )
    find_library(zlib
        NAME zlib.lib
        PATHS ${LINK_DIR}
        )
    find_library(iconv
        NAME iconv_a.lib
        PATHS ${LINK_DIR}
        )
    find_library(xml2
        NAME libxml2.a
        PATHS ${LINK_DIR}
        )
    FIND_LIBRARY(raptor2
        NAME raptor2.lib
        PATHS ${LINK_DIR}
        )
    find_library(sbol
        NAME sbol.lib
        PATHS ${LINK_DIR}
        )
ELSE ()
    SET( LINK_DIR ${CMAKE_INSTALL_PREFIX}/lib )                 # Mac library path
    SET( HEADER_DIR ${CMAKE_INSTALL_PREFIX}/include/sbol )      # Mac header path

    FIND_LIBRARY (sbol sbol)
    FIND_LIBRARY (raptor2 raptor2)
    FIND_LIBRARY (xml2 xml2)
    FIND_LIBRARY (zlib z)
    FIND_LIBRARY (iconv iconv)
ENDIF ()

# gather headers
INCLUDE_DIRECTORIES( ${HEADER_DIR} )
MESSAGE("${HEADER_DIR}")


# gather source files
FILE( GLOB APPLICATION_FILES
    "*.h"
    "Source.cpp"
    )

# build test executable
ADD_EXECUTABLE( sbol_test
    ${APPLICATION_FILES}
    )

IF (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    TARGET_LINK_LIBRARIES( sbol_test
        ${sbol}
        ${raptor2}
        ${xml2}
        ${zlib}
        ${iconv}
        ws2_32
        )
ELSE ()
    TARGET_LINK_LIBRARIES( sbol_test
        ${sbol}
        ${raptor2}
        ${xml2}
        ${zlib}
        ${iconv}
        )
MESSAGE("${sbol}")
ENDIF ()


PROJECT( SBOL_TEST CXX)
CMAKE_MINIMUM_REQUIRED( VERSION 2.8 )
cmake_policy(SET CMP0015 NEW)  # set policy for using relative paths
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# gather source files
FILE( GLOB APPLICATION_FILES "test.cpp" )

set( LINK_DIR ${SBOL_LIBRARY_OUTPUT_PATH}/bin )
set( HEADER_DIR ${HEADER_OUTPUT_PATH} )
include_directories( ${HEADER_DIR} )

if(TARGET sbol32)
    add_library(sbol ALIAS sbol32)
elseif(TARGET sbol32-shared)
    add_library(sbol ALIAS sbol32)
elseif(TARGET sbol64)
    add_library(sbol ALIAS sbol64)
elseif(TARGET sbol64-shared)
    add_library(sbol ALIAS sbol64-shared)
endif()

IF ( ${CMAKE_SYSTEM_NAME} MATCHES "Windows" )
    # build test executable
    file( GLOB DIRENT_FILES "dirent.h" "dirent.c" )  # dirent is not default system header on Windows
    set(APPLICATION_FILES ${APPLICATION_FILES} ${DIRENT_FILES})
    add_executable( sbol_test ${APPLICATION_FILES} )
    set_target_properties(sbol_test PROPERTIES LINKER_LANGUAGE CXX)
    target_link_libraries( sbol_test
        sbol
        ${raptor2}
        ${xml2}
        ${zlib}
        ${iconv}
        ${jsoncpp}
        ${libcurl}
        Ws2_32.lib
        )
ELSE ()
    # build test executable
    add_executable( sbol_test ${APPLICATION_FILES} )
    set_target_properties(sbol_test PROPERTIES LINKER_LANGUAGE CXX)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64")

    target_link_libraries( sbol_test
        sbol
        ${RAPTOR_LIBRARY}
        ${CURL_LIBRARY}
        ${LIBXSLT_LIBRARIES}
        ${JsonCpp_LIBRARY}
        )
ENDIF ()

install(TARGETS sbol_test DESTINATION bin)

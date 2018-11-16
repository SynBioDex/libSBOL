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

# pass definitions to compiler for conditional compilation
if (SBOL_BUILD_PYTHON3)
    find_package( PythonLibs 3 )
    ADD_DEFINITIONS(-DSBOL_BUILD_PYTHON3)
    include_directories( ${PYTHON_INCLUDE_DIR} )
elseif(SBOL_BUILD_PYTHON2)
    find_package( PythonLibs 2 )
    ADD_DEFINITIONS(-DSBOL_BUILD_PYTHON2)
    include_directories( ${PYTHON_INCLUDE_DIR} )
endif()
if( SBOL_BUILD_MANYLINUX )
    add_definitions(-DSBOL_BUILD_MANYLINUX)
endif()



IF ( ${CMAKE_SYSTEM_NAME} MATCHES "Windows" )
    # build test executable
    file( GLOB DIRENT_FILES "dirent.h" "dirent.c" )  # dirent is not default system header on Windows
    set(APPLICATION_FILES ${APPLICATION_FILES} ${DIRENT_FILES})
    add_executable( sbol_test ${APPLICATION_FILES} )
    set_target_properties(sbol_test PROPERTIES LINKER_LANGUAGE CXX)
    target_link_libraries( sbol_test
        sbol
        ${PYTHON_LIBRARIES} #temporary fix
        ${raptor2}
        ${xml2}
        ${zlib}
        ${iconv}
        ${jsoncpp}
        ${libcurl}
        Ws2_32.lib
        )
    file(MAKE_DIRECTORY "${CMAKE_INSTALL_PREFIX}/test")
    add_custom_command(TARGET sbol_test PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/SBOLTestSuite/SBOL2 ${CMAKE_INSTALL_PREFIX}/test/roundtrip)
    set_target_properties(sbol_test PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_INSTALL_PREFIX}/test")
ELSE ()
    # build test executable
    add_executable( sbol_test ${APPLICATION_FILES} )
    set_target_properties(sbol_test PROPERTIES LINKER_LANGUAGE CXX)

    if( RASQAL_LIBRARY )
        SET(RASQAL_LDFLAGS ${RASQAL_LIBRARY})
    endif()
    target_link_libraries( sbol_test
        sbol
        #${PYTHON_LIBRARIES} #temporary fix
        ${RAPTOR_LIBRARY}
        ${RASQAL_LDFLAGS}
        ${CURL_LIBRARY}
        ${LIBXSLT_LIBRARIES}
        ${JsonCpp_LIBRARY}
        )
    file(MAKE_DIRECTORY "${SBOL_RELEASE_DIR}/test")
    add_custom_command(TARGET sbol_test PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/SBOLTestSuite/SBOL2 ${SBOL_RELEASE_DIR}/test/roundtrip)
    set_target_properties(sbol_test PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${SBOL_RELEASE_DIR}/test")
ENDIF ()


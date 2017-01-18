
CMAKE_MINIMUM_REQUIRED( VERSION 2.8 )
PROJECT( SBOL )

# set up folder structure
SET( SBOL_ROOT_DIR          ${CMAKE_CURRENT_SOURCE_DIR} )
SET( SBOL_SOURCE_DIR        ${SBOL_ROOT_DIR}/source     )
SET( SBOL_EXAMPLE_DIR       ${SBOL_ROOT_DIR}/examples   )
SET( SBOL_TEST_DIR          ${SBOL_ROOT_DIR}/tests      )
SET( SBOL_MANUAL_DIR        ${SBOL_ROOT_DIR}/manual     )
SET( SBOL_WRAPPER_DIR       ${SBOL_ROOT_DIR}/wrapper    )
SET( SBOL_BUILD_DIR         ${SBOL_ROOT_DIR}/build      )
SET( SBOL_RELEASE_DIR       ${SBOL_ROOT_DIR}/release    )
SET( EXECUTABLE_OUTPUT_PATH ${SBOL_RELEASE_DIR}         )
SET( LIBRARY_OUTPUT_PATH    ${SBOL_RELEASE_DIR}/library )
IF (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    SET( HEADER_OUTPUT_PATH		${LIBRARY_OUTPUT_PATH}/include )
ELSE()
    SET( HEADER_OUTPUT_PATH		${LIBRARY_OUTPUT_PATH}/sbol )
ENDIF()

# set build options
OPTION( SBOL_BUILD_STATIC     "Build statically linked library"           TRUE )
OPTION( SBOL_BUILD_SHARED     "Build dynamically linked library"           FALSE )
#OPTION( SBOL_BUILD_COMBINED  "Build libSBOL and Raptor RDF archives combined" FALSE )
#OPTION( SBOL_DEBUG_STATEMENTS "Add some print statements for debugging"   FALSE )
#OPTION( SBOL_BUILD_EXAMPLES   "Build the example programs"                FALSE )
#OPTION( SBOL_BUILD_TESTS      "Build the unit tests and example tests"    FALSE )
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
	OPTION( SBOL_BUILD_32      "Build on x86 architecture" FALSE )
	OPTION( SBOL_BUILD_64      "Build on x64 architecture" TRUE)
else()
	OPTION( SBOL_BUILD_32      "Build on x86 architecture" TRUE )
	OPTION( SBOL_BUILD_64      "Build on x64 architecture" FALSE)
endif()
OPTION( SBOL_BUILD_PYTHON2  "Generate Python version 2 wrapper using SWIG" FALSE )
OPTION( SBOL_BUILD_PYTHON3  "Generate Python version 3 wrapper using SWIG" FALSE )
OPTION( SBOL_BUILD_MANUAL  "Generate SBOL documentation using Doxygen" FALSE )
OPTION( SBOL_BUILD_JSON  "Build JsonCpp library (for Linux users primarily)" FALSE)
OPTION( SBOL_BUILD_OSX_DIST  "For pySBOL distributions on Mac, target frameworks back to OSX 10.9" FALSE)

# -fPIC from boost Python
set (CMAKE_POSITION_INDEPENDENT_CODE TRUE)

# build json parser
IF( SBOL_BUILD_JSON )
    ADD_SUBDIRECTORY( jsoncpp )
ENDIF()

# target old OSX frameworks
IF( SBOL_BUILD_OSX_DIST )
    set(CMAKE_OSX_DEPLOYMENT_TARGET "10.9")
    set(CMAKE_OSX_SYSROOT /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.11.sdk)
ENDIF()

# build libSBOL
ADD_SUBDIRECTORY( source )

# build examples
#IF( SBOL_BUILD_EXAMPLES )
#    ADD_SUBDIRECTORY( examples )
#ENDIF()

# build tests
#IF( SBOL_BUILD_TESTS )
#    ADD_SUBDIRECTORY( tests )
#ENDIF()

# generate documentation
IF( SBOL_BUILD_MANUAL )
    ADD_SUBDIRECTORY( manual )
ENDIF()

IF( SBOL_BUILD_PYTHON2 OR SBOL_BUILD_PYTHON3 )
    ADD_SUBDIRECTORY( wrapper )
ENDIF()


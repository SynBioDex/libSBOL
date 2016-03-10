PROJECT( SBOL )
CMAKE_MINIMUM_REQUIRED( VERSION 2.8 )
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        MESSAGE(64)
    else()
        MESSAGE(32)
    endif()

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
OPTION( SBOL_BUILD_STATIC     "Build statically linked library"           FALSE )
OPTION( SBOL_BUILD_COMBINED  "Build libxml2 and libSBOL combined" FALSE )
OPTION( SBOL_DEBUG_STATEMENTS "Add some print statements for debugging"   FALSE )
OPTION( SBOL_BUILD_EXAMPLES   "Build the example programs"                FALSE )
OPTION( SBOL_BUILD_TESTS      "Build the unit tests and example tests"    FALSE )
OPTION( SBOL_GENERATE_PYTHON  "Generate Python wrapper using SWIG"        FALSE )
OPTION( SBOL_GENERATE_MANUAL  "Generate SBOL documentation using Doxygen" FALSE )

# build libSBOLc
#ADD_SUBDIRECTORY( schema )
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
#IF( SBOL_GENERATE_MANUAL )
#    ADD_SUBDIRECTORY( manual )
#ENDIF()

IF( SBOL_GENERATE_PYTHON )
    ADD_SUBDIRECTORY( wrapper )
ENDIF()


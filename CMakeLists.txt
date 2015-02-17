PROJECT( SBOL )
CMAKE_MINIMUM_REQUIRED( VERSION 2.8 )

# set up folder structure
SET( SBOL_ROOT_DIR          ${CMAKE_CURRENT_SOURCE_DIR} )
SET( SBOL_SCHEMA_DIR        ${SBOL_ROOT_DIR}/schema     )
SET( SBOL_SOURCE_DIR        ${SBOL_ROOT_DIR}/source     )
SET( SBOL_EXAMPLE_DIR       ${SBOL_ROOT_DIR}/examples   )
SET( SBOL_TEST_DIR          ${SBOL_ROOT_DIR}/tests      )
SET( SBOL_MANUAL_DIR        ${SBOL_ROOT_DIR}/manual     )
SET( SBOL_WRAPPER_DIR       ${SBOL_ROOT_DIR}/wrapper    )
SET( SBOL_BUILD_DIR         ${SBOL_ROOT_DIR}/build      )
SET( SBOL_RELEASE_DIR       ${SBOL_ROOT_DIR}/release    )
SET( EXECUTABLE_OUTPUT_PATH ${SBOL_RELEASE_DIR}         )
SET( LIBRARY_OUTPUT_PATH    ${SBOL_RELEASE_DIR}         )

# set build options
OPTION( SBOL_BUILD_STATIC     "Build statically linked library"           FALSE )
OPTION( SBOL_BUILD_COMBINED  "Build libxml2 and libSBOL combined" FALSE )
OPTION( SBOL_DEBUG_STATEMENTS "Add some print statements for debugging"   FALSE )
OPTION( SBOL_BUILD_EXAMPLES   "Build the example programs"                FALSE )
OPTION( SBOL_BUILD_TESTS      "Build the unit tests and example tests"    FALSE )
OPTION( SBOL_GENERATE_PYTHON  "Generate Python wrapper using SWIG"        FALSE )
OPTION( SBOL_GENERATE_MANUAL  "Generate SBOL documentation using Doxygen" FALSE )

# build libSBOLc
# ADD_SUBDIRECTORY( schema )
ADD_SUBDIRECTORY( source )

# build examples
IF( SBOL_BUILD_EXAMPLES )
    ADD_SUBDIRECTORY( examples )
ENDIF()

# build tests
IF( SBOL_BUILD_TESTS )
    ADD_SUBDIRECTORY( tests )
ENDIF()

# generate documentation
IF( SBOL_GENERATE_MANUAL )
    ADD_SUBDIRECTORY( manual )
ENDIF()

# generate python wrapper
IF( SBOL_GENERATE_PYTHON )
    ADD_SUBDIRECTORY( wrapper )
ENDIF()

INSTALL(TARGETS SBOL DESTINATION)

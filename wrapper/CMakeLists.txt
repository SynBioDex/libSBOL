FIND_PACKAGE( SWIG REQUIRED )
IF( SWIG_FOUND )

	# adjust paths
	SET( SBOL_RELEASE_DIR       ${SBOL_RELEASE_DIR}/wrapper )
	SET( EXECUTABLE_OUTPUT_PATH ${SBOL_RELEASE_DIR}         )
	SET( LIBRARY_OUTPUT_PATH    ${SBOL_RELEASE_DIR}         )

	# gather headers
	INCLUDE_DIRECTORIES(
	    ${XML2_HEADER_DIR}
        ${RAPTOR_HEADER_DIR}
	    ${SBOL_SOURCE_DIR}
	)
	
	# gather source files
	FILE( GLOB SBOL_SOURCE_FILES
		${SBOL_SOURCE_DIR}/*.h
		${SBOL_SOURCE_DIR}/*.cpp
    )

    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    ADD_DEFINITIONS(-DLIBXML_STATIC -DRAPTOR_STATIC)


	# build a shared library without visibility limitations
	# because the non-SBOLAPIEXPORTS functions could be useful
	# in writing a higher-level wrapper, and because Python
	# will try to import them anyway and fail
#ADD_LIBRARY( sbol_swig
#		STATIC
#		${SBOL_SOURCE_FILES}
#	)

#   TARGET_LINK_LIBRARIES( sbol_swig
#       ${raptor2}
#       ${xml2}
#       ${zlib}
#       ${iconv}
#	)
#   SET_TARGET_PROPERTIES(sbol_swig PROPERTIES LINKER_LANGUAGE CXX)

#   INSTALL(TARGETS sbol_swig DESTINATION lib)
#
	# set up some SWIG stuff
    INCLUDE( ${SWIG_USE_FILE} )
    IF (SBOL_GENERATE_PYTHON2)
        FIND_PACKAGE( PythonLibs 2 )
    ENDIF()
    IF (SBOL_GENERATE_PYTHON3)
        FIND_PACKAGE(PythonLibs 3)
    ENDIF()

    IF(NOT PYTHONLIBS_FOUND)
      MESSAGE( "Python libraries not found; unable to generate Python bindings" )
    ENDIF()
    INCLUDE_DIRECTORIES( ${PYTHON_INCLUDE_DIRS} )
    SET( CMAKE_SWIG_FLAGS "-c++" )
    SET_SOURCE_FILES_PROPERTIES(libsbol.i PROPERTIES CPLUSPLUS ON)

    SET( CMAKE_SWIG_OUTDIR ${SBOL_RELEASE_DIR} )

	# build the SWIG wrapper
    SWIG_ADD_MODULE( libsbol
        python
        libsbol.i
    )
    IF(APPLE)
      # Do not link in the Python libraries
      SWIG_LINK_LIBRARIES( libsbol
          sbol
          ${raptor2}
          ${xml2}
          ${zlib}
          ${iconv} )

      # Resolve Python symbols dynamically due to differing runtime env
      SET_TARGET_PROPERTIES(_libsbol PROPERTIES LINK_FLAGS "-undefined dynamic_lookup")
    ELSE()
      SWIG_LINK_LIBRARIES( libsbol
          ${PYTHON_LIBRARIES}
          sbol
      )
    ENDIF()
MESSAGE(${PYTHON_LIBRARIES})
    INSTALL(TARGETS _libsbol DESTINATION lib)

ELSE()

    MESSAGE( "SWIG not found; unable to generate Python bindings" )

ENDIF()
MESSAGE( ${PYTHON_INCLUDE_DIRS} )

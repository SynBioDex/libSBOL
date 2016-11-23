FIND_PACKAGE( SWIG REQUIRED )
IF( SWIG_FOUND )

	# adjust paths
	SET( SBOL_RELEASE_DIR       ${SBOL_RELEASE_DIR}/wrapper )
	SET( EXECUTABLE_OUTPUT_PATH ${SBOL_RELEASE_DIR}         )
	SET( LIBRARY_OUTPUT_PATH    ${SBOL_RELEASE_DIR}         )
    set( CMAKE_SWIG_OUTDIR ${SBOL_RELEASE_DIR} )

    # set up some SWIG stuff
    include( ${SWIG_USE_FILE} )
    set( CMAKE_SWIG_FLAGS "-c++" )
    set_source_files_properties(libsbol.i PROPERTIES CPLUSPLUS ON)
    if(SBOL_BUILD_STATIC)
        add_definitions(-DLIBXML_STATIC -DRAPTOR_STATIC -DLIBXSLT_STATIC -DCURL_STATIC)
    endif()

    include_directories(
        ${SBOL_SOURCE_DIR}
        ${RAPTOR_INCLUDE_DIR}
        ${CURL_INCLUDE_DIR}
        ${LIBXSLT_INCLUDE_DIR}
        ${LIBXML2_INCLUDE_DIR}
        ${LIBZ_INCLUDE_DIR}
        ${LIBXSLT_EXSLT_INCLUDE_DIR}
        ${LIBICONV_INCLUDE_DIR}
        ${LDAP_INCLUDE_DIR}
)

#get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
#foreach(dir ${dirs})
#message(STATUS "dir='${dir}'")
#endforeach()

# gather source files
FILE( GLOB SBOL_SOURCE_FILES
    ${SBOL_SOURCE_DIR}/*.h
    ${SBOL_SOURCE_DIR}/*.cpp )

#get_directory_property( DirDefs COMPILE_DEFINITIONS )
#message( "COMPILE_DEFINITIONS = ${DirDefs}" )

IF (SBOL_BUILD_PYTHON3)
    find_package( PythonLibs 3 )
    INCLUDE_DIRECTORIES( ${PYTHON_INCLUDE_DIRS} )
    if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin" OR ${CMAKE_SYSTEM_NAME} MATCHES "Linux")
        if (SBOL_BUILD_32)
            set(PYSBOL_CONFIG "Mac_32_3")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -m32")

            # build the SWIG wrapper
            swig_add_module( libsbol32_3
                python
                libsbol.i )

            # Do not link in the Python libraries on MacOSX....
            swig_link_libraries( libsbol32_3
                sbol32
                ${RAPTOR_LIBRARY}
                ${CURL_LIBRARY}
                ${LIBXSLT_LIBRARIES}
#                ${SECURITY} ${CORE_FOUNDATION} ${LDAP}
#                ${LIBXML2_LIBRARIES}
#                ${zlib}
#                ${iconv}
                )

            # ...rather, resolve Python symbols dynamically due to differing runtime env
            set_target_properties(_libsbol32_3 PROPERTIES LINK_FLAGS "-undefined dynamic_lookup")

            # Move target to a new directory and rename it, so the SWIG libraries can be directly copied into the pySBOL project

            file(MAKE_DIRECTORY "${CMAKE_SWIG_OUTDIR}/${PYSBOL_CONFIG}")
            set_target_properties(_libsbol32_3 PROPERTIES OUTPUT_NAME "${PYSBOL_CONFIG}/_libsbol")
            add_custom_command(TARGET _libsbol32_3 POST_BUILD COMMAND mv ${CMAKE_SWIG_OUTDIR}/libsbol* ${CMAKE_SWIG_OUTDIR}/${PYSBOL_CONFIG})
        endif()
        if(SBOL_BUILD_64)
            set(PYSBOL_CONFIG "Mac_64_3")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -m64")

            # build the SWIG wrapper
            swig_add_module( libsbol64_3
                python
                libsbol.i )

            # Do not link in the Python libraries on MacOSX....
            swig_link_libraries( libsbol64_3
                sbol64
                ${RAPTOR_LIBRARY}
                ${CURL_LIBRARY}
                ${LIBXSLT_LIBRARIES}
#                ${SECURITY} ${CORE_FOUNDATION} ${LDAP}
#                ${LIBXML2_LIBRARIES}
#                ${zlib}
#                ${iconv}
                )

            # ...rather, resolve Python symbols dynamically due to differing runtime env
            set_target_properties(_libsbol64_3 PROPERTIES LINK_FLAGS "-undefined dynamic_lookup")

            file(MAKE_DIRECTORY ${CMAKE_SWIG_OUTDIR}/${PYSBOL_CONFIG})
            set_target_properties(_libsbol64_3 PROPERTIES OUTPUT_NAME "${PYSBOL_CONFIG}/_libsbol")
            add_custom_command(TARGET _libsbol64_3 POST_BUILD
                               COMMAND mv ${CMAKE_SWIG_OUTDIR}/libsbol* ${CMAKE_SWIG_OUTDIR}/${PYSBOL_CONFIG})

        endif()
    else()
        if (SBOL_BUILD_32)
            swig_add_module( libsbol
                python
                libsbol.i )		
            swig_link_libraries( libsbol
                ${raptor2}
                ${PYTHON_LIBRARIES}
                ${CURL_LIBRARY}
                ${xml2}
                ${LIBXSLT_LIBRARIES}
                sbol32)
        endif()
        if (SBOL_BUILD_64)
            swig_add_module( libsbol
                python
                libsbol.i )	
            swig_link_libraries( libsbol
                ${raptor2}
                ${PYTHON_LIBRARIES}
                ${CURL_LIBRARY}
                ${xml2}
                ${LIBXSLT_LIBRARIES}
                sbol64)
        endif()
    endif()
endif()

#message(${PYTHONLIBS_FOUND})
#message(${PYTHON_INCLUDE_DIRS})
#message(${PYTHON_INCLUDE_DIR})
#message(${PYTHON_LIBRARIES})
#message(${PYTHONLIBS_VERSION_STRING})
#message(${PYTHON_INCLUDE_PATH})
unset( PYTHON_LIBRARIES CACHE  )
unset( PYTHONLIBS_FOUND CACHE  )
unset(PYTHON_INCLUDE_DIRS CACHE  )
unset(PYTHON_INCLUDE_DIR CACHE  )

unset(PYTHONLIBS_VERSION_STRING CACHE )
unset(PYTHON_INCLUDE_PATH CACHE)
unset( PYTHON_LIBRARIES   )
unset( PYTHONLIBS_FOUND   )
unset(PYTHON_INCLUDE_DIRS   )
unset(PYTHON_INCLUDE_DIR   )

unset(PYTHONLIBS_VERSION_STRING  )
unset(PYTHON_INCLUDE_PATH )
#message(${PYTHONLIBS_FOUND})
#message(${PYTHON_INCLUDE_DIRS})
#message(${PYTHON_LIBRARIES})
#message(${PYTHONLIBS_VERSION_STRING})
#message(${PYTHON_INCLUDE_PATH})
#message(${PYTHON_INCLUDE_DIR})



IF (SBOL_BUILD_PYTHON2)
    find_package( PythonLibs 2 EXACT)

    message( "FOUND PYTHON = ${PYTHONLIBS_FOUND} at ${PYTHON_LIBRARIES}")
    message( "PYTHON INCLUDE DIRS = ${PYTHON_INCLUDE_DIRS}")
    #message(${PYTHON_INCLUDE_DIR})
    #message(${PYTHON_LIBRARIES})
    message( "FOUND PYTHON VERSION ${PYTHONLIBS_VERSION_STRING}")
    #message(${PYTHON_INCLUDE_PATH})
    INCLUDE_DIRECTORIES( ${PYTHON_INCLUDE_DIRS} )

    if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
        if (SBOL_BUILD_32)
            set(PYSBOL_CONFIG "Mac_32_2")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -m32")

            # build the SWIG wrapper
            swig_add_module( libsbol32_2
                python
                libsbol.i )

            # Do not link in the Python libraries on MacOSX....
            swig_link_libraries( libsbol32_2
                sbol32
                ${RAPTOR_LIBRARY}
                ${CURL_LIBRARY}
                ${LIBXSLT_LIBRARIES}
#                ${SECURITY} ${CORE_FOUNDATION} ${LDAP}
#                ${LIBXML2_LIBRARIES}
#                ${zlib}
#                ${iconv}
)

            # ...rather, resolve Python symbols dynamically due to differing runtime env
            set_target_properties(_libsbol32_2 PROPERTIES LINK_FLAGS "-undefined dynamic_lookup")

            # Move target to a new directory and rename it, so the SWIG libraries can be directly copied into the pySBOL project
            file(MAKE_DIRECTORY ${CMAKE_SWIG_OUTDIR}/${PYSBOL_CONFIG})
            set_target_properties(_libsbol32_2 PROPERTIES OUTPUT_NAME "${PYSBOL_CONFIG}/_libsbol")
            add_custom_command(TARGET _libsbol32_2 POST_BUILD COMMAND mv ${CMAKE_SWIG_OUTDIR}/libsbol* ${CMAKE_SWIG_OUTDIR}/${PYSBOL_CONFIG})
        endif()
        if(SBOL_BUILD_64)
            set(PYSBOL_CONFIG "Mac_64_2")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -m64")

            # build the SWIG wrapper
            swig_add_module( libsbol64_2
                python
                libsbol.i )

            # Do not link in the Python libraries on MacOSX....
            swig_link_libraries( libsbol64_2
                sbol64
                ${RAPTOR_LIBRARY}
                ${CURL_LIBRARY}
                ${LIBXSLT_LIBRARIES}
#                ${SECURITY} ${CORE_FOUNDATION} ${LDAP}
#                ${LIBXML2_LIBRARIES}
#                ${zlib}
#                ${iconv}
                )



            # ...rather, resolve Python symbols dynamically due to differing runtime env
            set_target_properties(_libsbol64_2 PROPERTIES LINK_FLAGS "-undefined dynamic_lookup")

            # Move target to a new directory and rename it, so the SWIG libraries can be directly copied into the pySBOL project
            file(MAKE_DIRECTORY ${CMAKE_SWIG_OUTDIR}/${PYSBOL_CONFIG})
            set_target_properties(_libsbol64_2 PROPERTIES OUTPUT_NAME "${PYSBOL_CONFIG}/_libsbol")
            add_custom_command(TARGET _libsbol64_2 POST_BUILD
                               COMMAND mv ${CMAKE_SWIG_OUTDIR}/libsbol* ${CMAKE_SWIG_OUTDIR}/${PYSBOL_CONFIG})
        endif()
    elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
        if (SBOL_BUILD_32)
            set(PYSBOL_CONFIG "python/libsbol")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -m32")
            swig_add_module( libsbol
                python
                libsbol.i )
            swig_link_libraries( libsbol
                ${PYTHON_LIBRARIES}
                ${CURL_LIBRARY}
                ${LIBXSLT_LIBRARIES}
                sbol32)

            file(MAKE_DIRECTORY ${CMAKE_SWIG_OUTDIR}/${PYSBOL_CONFIG})
            set_target_properties(_libsbol PROPERTIES OUTPUT_NAME "${PYSBOL_CONFIG}/_libsbol")
            add_custom_command(TARGET _libsbol POST_BUILD
                               COMMAND mv ${CMAKE_SWIG_OUTDIR}/libsbol* ${CMAKE_SWIG_OUTDIR}/${PYSBOL_CONFIG})
        endif()
        if (SBOL_BUILD_64)
            set(PYSBOL_CONFIG "python/libsbol")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -m64")
            swig_add_module( libsbol
                python
                libsbol.i )
            swig_link_libraries( libsbol
                ${PYTHON_LIBRARIES}
                ${CURL_LIBRARY}
                ${LIBXSLT_LIBRARIES}
                sbol64)

            file(MAKE_DIRECTORY ${CMAKE_SWIG_OUTDIR}/${PYSBOL_CONFIG})
            set_target_properties(_libsbol PROPERTIES OUTPUT_NAME "${PYSBOL_CONFIG}/_libsbol")
            add_custom_command(TARGET _libsbol POST_BUILD
                               COMMAND mv ${CMAKE_SWIG_OUTDIR}/libsbol* ${CMAKE_SWIG_OUTDIR}/${PYSBOL_CONFIG})
        endif()
    else()
        if (SBOL_BUILD_32)
            swig_add_module( libsbol
                python
                libsbol.i )
            swig_link_libraries( libsbol
                ${raptor2}
                ${PYTHON_LIBRARIES}
                ${CURL_LIBRARY}
                ${xml2}
                ${LIBXSLT_LIBRARIES}
                sbol32)
        endif()
        if (SBOL_BUILD_64)
            swig_add_module( libsbol
                python
                libsbol.i )
            swig_link_libraries( libsbol
                ${raptor2}
                ${PYTHON_LIBRARIES}
                ${CURL_LIBRARY}
                ${xml2}
                ${LIBXSLT_LIBRARIES}
                sbol64)
        endif()
    endif()
endif()


#install(TARGETS _libsbol DESTINATION lib)

ELSE()

    MESSAGE( "SWIG not found; unable to generate Python bindings" )

ENDIF()

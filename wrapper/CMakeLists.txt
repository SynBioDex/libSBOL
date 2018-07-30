find_package( SWIG REQUIRED )
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
    add_definitions(-DRAPTOR_STATIC)

    if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
        add_definitions(-DLIBXML_STATIC -DLIBXSLT_STATIC -DCURL_STATICLIB -DCURL_STATIC)
    endif()

    # pass definition to compiler for conditional compilation of code
    if( SBOL_BUILD_MANYLINUX )
        add_definitions(-DSBOL_BUILD_MANYLINUX)
    endif()

    include_directories(
        ${SBOL_SOURCE_DIR}
        ${RAPTOR_INCLUDE_DIR}
        ${CURL_INCLUDE_DIR}
        ${JsonCpp_INCLUDE_DIR}
	${OPENSSL_INCLUDE_DIR}
        # ${LIBXSLT_INCLUDE_DIR}
        # ${LIBXML2_INCLUDE_DIR}
        # ${LIBZ_INCLUDE_DIR}
        # ${LIBXSLT_EXSLT_INCLUDE_DIR}
        # ${LIBICONV_INCLUDE_DIR}
        # ${LDAP_INCLUDE_DIR}
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
    message( "FOUND PYTHON = ${PYTHONLIBS_FOUND} at ${PYTHON_LIBRARIES}")
    message( "PYTHON INCLUDE DIRS = ${PYTHON_INCLUDE_DIRS}")
    message( "FOUND PYTHON VERSION ${PYTHONLIBS_VERSION_STRING}")
    INCLUDE_DIRECTORIES( ${PYTHON_INCLUDE_DIRS} )
    ADD_DEFINITIONS(-DSBOL_BUILD_PYTHON3)
    set(CMAKE_SWIG_FLAGS -DSBOL_BUILD_PYTHON3)

    if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

        ###### Python 3 for Mac 32x ######
        if (SBOL_BUILD_32)
            set(PYSBOL_TARGET_DIR "Mac_32_3/sbol")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -m32")

            # build the SWIG wrapper
            if (${CMAKE_VERSION} VERSION_LESS "3.8.0")
                swig_add_module( libsbol32_3
                python
                libsbol.i )
            else ()
                SWIG_ADD_LIBRARY( libsbol32_3
                    LANGUAGE python
                    SOURCES libsbol.i )
            endif()
                    
            # Do not link in the Python libraries on MacOSX....
            if(SBOL_BUILD_SHARED)
                swig_link_libraries( libsbol32_3
                    ${RAPTOR_LIBRARY}
                    ${CURL_LIBRARY}
                    ${LIBXSLT_LIBRARIES}
                    sbol32-shared)
            else()
                swig_link_libraries( libsbol32_3
                    ${RAPTOR_LIBRARY}
                    ${CURL_LIBRARY}
                    ${LIBXSLT_LIBRARIES}
                    sbol32)
            ENDIF()

            # ...rather, resolve Python symbols dynamically due to differing runtime env
            set_target_properties(_libsbol32_3 PROPERTIES LINK_FLAGS "-undefined dynamic_lookup")

            # Move target to a new directory and rename it, so the SWIG libraries can be directly copied into the pySBOL project
            set_target_properties(_libsbol32_3 PROPERTIES OUTPUT_NAME "${PYSBOL_TARGET_DIR}/_libsbol")
            file(MAKE_DIRECTORY ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR})
            file(MAKE_DIRECTORY ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR}/test)
            add_custom_command(TARGET _libsbol32_3 PRE_BUILD
                               COMMAND cp -r ${PROJECT_SOURCE_DIR}/test/SBOLTestSuite/* ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR}/test)
            add_custom_command(TARGET _libsbol32_3 PRE_BUILD
                               COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/__init__.py ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR}/__init__.py)
            add_custom_command(TARGET _libsbol32_3 PRE_BUILD
                               COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/sbol.py ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR}/sbol.py)
            add_custom_command(TARGET _libsbol32_3 PRE_BUILD
                               COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/CRISPR_example.py ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR}/CRISPR_example.py)
            add_custom_command(TARGET _libsbol32_3 PRE_BUILD
                               COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/crispr_example.xml ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR}/crispr_example.xml)
            add_custom_command(TARGET _libsbol32_3 PRE_BUILD
                               COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/unit_tests.py ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR}/unit_tests.py)
            add_custom_command(TARGET _libsbol32_3 PRE_BUILD
                               COMMAND cp ${CMAKE_SWIG_OUTDIR}/libsbol.py ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR}/libsbol.py)
            add_custom_command(TARGET _libsbol32_3 POST_BUILD
                               COMMAND mv ${CMAKE_SWIG_OUTDIR}/libsbol* ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR})
        endif()

        ##### Python 3 for Mac 64x ######
        if(SBOL_BUILD_64)
            set(PYSBOL_TARGET_DIR "Mac_64_3/sbol")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -m64")

            # build the SWIG wrapper
            if (${CMAKE_VERSION} VERSION_LESS "3.8.0")
                swig_add_module( libsbol64_3
                python
                libsbol.i )
            else ()
                SWIG_ADD_LIBRARY( libsbol64_3
                    LANGUAGE python
                    SOURCES libsbol.i )
            endif()

            # Do not link in the Python libraries on MacOSX....
            if(SBOL_BUILD_SHARED)
                swig_link_libraries( libsbol64_3
                    ${RAPTOR_LIBRARY}
                    ${CURL_LIBRARY}
                    ${LIBXSLT_LIBRARIES}
                    sbol64-shared)
            else()
                swig_link_libraries( libsbol64_3
                    ${RAPTOR_LIBRARY}
                    ${CURL_LIBRARY}
                    ${LIBXSLT_LIBRARIES}
                    sbol64)
            ENDIF()

            # ...rather, resolve Python symbols dynamically due to differing runtime env
            set_target_properties(_libsbol64_3 PROPERTIES LINK_FLAGS "-undefined dynamic_lookup")

            # Move target to a new directory and rename it, so the SWIG libraries can be directly copied into the pySBOL project
            set_target_properties(_libsbol64_3 PROPERTIES OUTPUT_NAME "${PYSBOL_TARGET_DIR}/_libsbol")
            file(MAKE_DIRECTORY ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR})
            file(MAKE_DIRECTORY ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR}/test)
            add_custom_command(TARGET _libsbol64_3 PRE_BUILD
                               COMMAND cp -r ${PROJECT_SOURCE_DIR}/test/SBOLTestSuite/* ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR}/test)
            add_custom_command(TARGET _libsbol64_3 PRE_BUILD
                               COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/__init__.py ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR}/__init__.py)
            add_custom_command(TARGET _libsbol64_3 PRE_BUILD
                               COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/sbol.py ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR}/sbol.py)
            add_custom_command(TARGET _libsbol64_3 PRE_BUILD
                               COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/CRISPR_example.py ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR}/CRISPR_example.py)
            add_custom_command(TARGET _libsbol64_3 PRE_BUILD
                               COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/crispr_example.xml ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR}/crispr_example.xml)
            add_custom_command(TARGET _libsbol64_3 PRE_BUILD
                               COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/unit_tests.py ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR}/unit_tests.py)
            add_custom_command(TARGET _libsbol64_3 PRE_BUILD
                               COMMAND cp ${CMAKE_SWIG_OUTDIR}/libsbol.py ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR}/libsbol.py)
            add_custom_command(TARGET _libsbol64_3 POST_BUILD
                               COMMAND mv ${CMAKE_SWIG_OUTDIR}/libsbol* ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR})
        endif()
    elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
        ##### Python 3 for Linux 32x #####
        if (SBOL_BUILD_32)
            set(PYSBOL_TARGET_DIR "Linux_32_3/sbol")  # target directory is synced with target directory for setup.py script
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -m32")

            # build the SWIG wrapper
            if (${CMAKE_VERSION} VERSION_LESS "3.8.0")
                swig_add_module( libsbol
                python
                libsbol.i )
            else()
                SWIG_ADD_LIBRARY( libsbol
                    LANGUAGE python
                    SOURCES libsbol.i )
            endif()

            if(SBOL_BUILD_SHARED)
                swig_link_libraries( libsbol
                    ${PYTHON_LIBRARIES}
                    ${RAPTOR_LIBRARY}
                    ${CURL_LIBRARY}
                    ${LIBXSLT_LIBRARIES}
                    sbol32-shared)
            else()
                swig_link_libraries( libsbol
                    ${PYTHON_LIBRARIES}
                    ${RAPTOR_LIBRARY}
                    ${CURL_LIBRARY}
		    ${OPENSSL_LIBRARY}  # linux only
		    ${CRYPTO_LIBRARY}   # linux only
                    ${LIBXSLT_LIBRARIES}
                    sbol32)
            ENDIF()

            # Move target to a new directory and rename it, so the SWIG libraries can be directly copied into the pySBOL project
            file(MAKE_DIRECTORY ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR})
            file(MAKE_DIRECTORY ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR}/test)
            set_target_properties(_libsbol PROPERTIES OUTPUT_NAME "_libsbol")
            add_custom_command(TARGET _libsbol PRE_BUILD
                               COMMAND cp -r ${CMAKE_CURRENT_SOURCE_DIR}/__init__.py ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR})
            add_custom_command(TARGET _libsbol PRE_BUILD
                               COMMAND cp -r ${CMAKE_CURRENT_SOURCE_DIR}/CRISPR_example.py ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR})
            add_custom_command(TARGET _libsbol PRE_BUILD
                               COMMAND cp -r ${CMAKE_CURRENT_SOURCE_DIR}/crispr_example.xml ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR})
            add_custom_command(TARGET _libsbol PRE_BUILD
                               COMMAND cp -r ${CMAKE_CURRENT_SOURCE_DIR}/sbol.py ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR})
            add_custom_command(TARGET _libsbol PRE_BUILD
                               COMMAND cp -r ${CMAKE_CURRENT_SOURCE_DIR}/unit_tests.py ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR})
            add_custom_command(TARGET _libsbol PRE_BUILD
                               COMMAND cp -r ${PROJECT_SOURCE_DIR}/test/SBOLTestSuite/* ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR}/test)
            add_custom_command(TARGET _libsbol POST_BUILD
                               COMMAND cp -r ${CMAKE_SWIG_OUTDIR}/libsbol.py ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR})
            add_custom_command(TARGET _libsbol POST_BUILD
                               COMMAND mv ${CMAKE_SWIG_OUTDIR}/_libsbol.so ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR})
            add_custom_command(TARGET _libsbol POST_BUILD
                               COMMAND mv ${CMAKE_SWIG_OUTDIR}/libsbol* ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR})
        endif()
        ##### Python 3 for Linux 64x #####
        if(SBOL_BUILD_64)
            set(PYSBOL_TARGET_DIR "Linux_64_3/sbol")  # target directory is synced with target directory for setup.py script
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -m64")

            # build the SWIG wrapper
            if (${CMAKE_VERSION} VERSION_LESS "3.8.0")
                swig_add_module( libsbol
                python
                libsbol.i )
            else()
                SWIG_ADD_LIBRARY( libsbol
                    LANGUAGE python
                    SOURCES libsbol.i )
            endif()    
                
            if(SBOL_BUILD_SHARED)
                swig_link_libraries( libsbol
                    ${PYTHON_LIBRARIES}
                    ${RAPTOR_LIBRARY}
                    ${CURL_LIBRARY}
                    ${LIBXSLT_LIBRARIES}
                    sbol64-shared)
            else()
                swig_link_libraries( libsbol
                    ${PYTHON_LIBRARIES}
                    ${RAPTOR_LIBRARY}
                    ${CURL_LIBRARY}
		    ${OPENSSL_LIBRARY}  # linux only
		    ${CRYPTO_LIBRARY}   # linux only
                    ${LIBXSLT_LIBRARIES}
                    sbol64)
            ENDIF()

            file(MAKE_DIRECTORY ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR})
            file(MAKE_DIRECTORY ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR}/test)
            set_target_properties(_libsbol PROPERTIES OUTPUT_NAME "_libsbol")
            add_custom_command(TARGET _libsbol PRE_BUILD
                               COMMAND cp -r ${CMAKE_CURRENT_SOURCE_DIR}/__init__.py ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR})
            add_custom_command(TARGET _libsbol PRE_BUILD
                               COMMAND cp -r ${CMAKE_CURRENT_SOURCE_DIR}/CRISPR_example.py ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR})
            add_custom_command(TARGET _libsbol PRE_BUILD
                               COMMAND cp -r ${CMAKE_CURRENT_SOURCE_DIR}/crispr_example.xml ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR})
            add_custom_command(TARGET _libsbol PRE_BUILD
                               COMMAND cp -r ${CMAKE_CURRENT_SOURCE_DIR}/sbol.py ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR})
            add_custom_command(TARGET _libsbol PRE_BUILD
                               COMMAND cp -r ${CMAKE_CURRENT_SOURCE_DIR}/unit_tests.py ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR})
            add_custom_command(TARGET _libsbol PRE_BUILD
                               COMMAND cp -r ${PROJECT_SOURCE_DIR}/test/SBOLTestSuite/* ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR}/test)
            add_custom_command(TARGET _libsbol POST_BUILD
                               COMMAND cp -r ${CMAKE_SWIG_OUTDIR}/libsbol.py ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR})
            add_custom_command(TARGET _libsbol POST_BUILD
                               COMMAND mv ${CMAKE_SWIG_OUTDIR}/_libsbol.so ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR})
            add_custom_command(TARGET _libsbol POST_BUILD
                               COMMAND mv ${CMAKE_SWIG_OUTDIR}/libsbol* ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR})
        endif()
    else()
        ##### Python 3 for Windows 32x #####
        include_directories( ${JSONCPP_INCLUDE_DIR}/..)
        include_directories( ${CURL_INCLUDE_DIR}/..)
        if (SBOL_BUILD_32)
            set(PYSBOL_TARGET_DIR "Win_32_3/sbol")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj")
            
            if (${CMAKE_VERSION} VERSION_LESS "3.8.0")
                swig_add_module( libsbol
                python
                libsbol.i )
            else()
                SWIG_ADD_LIBRARY( libsbol32_3
                    LANGUAGE python
                    SOURCES libsbol.i )	
            endif()
                    
            swig_link_libraries( libsbol32_3
                ${raptor2}
                ${PYTHON_LIBRARIES}
                ${curl}
                ${xml2}
                ${zlib}
                ${iconv}
                ${jsoncpp}
                ${LIBXSLT_LIBRARIES}
                sbol32)
            set_target_properties(_libsbol32_3 PROPERTIES OUTPUT_NAME "_libsbol")
 			file(MAKE_DIRECTORY ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR})
            file(MAKE_DIRECTORY ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR}/test)
            add_custom_command(TARGET _libsbol32_3 PRE_BUILD
                               COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/__init__.py ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR})
            add_custom_command(TARGET _libsbol32_3 PRE_BUILD
                               COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/CRISPR_example.py ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR})
            add_custom_command(TARGET _libsbol32_3 PRE_BUILD
                               COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/crispr_example.xml ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR})
            add_custom_command(TARGET _libsbol32_3 PRE_BUILD
                               COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/sbol.py ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR})
            add_custom_command(TARGET _libsbol32_3 PRE_BUILD
                               COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/unit_tests.py ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR})
            add_custom_command(TARGET _libsbol32_3 PRE_BUILD
                               COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/test/SBOLTestSuite ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR}/test)
            add_custom_command(TARGET _libsbol32_3 POST_BUILD
                               COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SWIG_OUTDIR}/libsbol.py ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR})
            add_custom_command(TARGET _libsbol32_3 POST_BUILD
                               COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SWIG_OUTDIR}/Release/_libsbol.pyd ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR})
			add_custom_command(TARGET _libsbol32_3 POST_BUILD
							   COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_SWIG_OUTDIR}/libsbol.py)
			add_custom_command(TARGET _libsbol32_3 POST_BUILD
							   COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_SWIG_OUTDIR}/libsbolPYTHON_wrap.cxx)
			add_custom_command(TARGET _libsbol32_3 POST_BUILD
							   COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_SWIG_OUTDIR}/Release)
        endif()
        ##### Python 3 for Windows 64x #####
        if (SBOL_BUILD_64)
			set(PYSBOL_TARGET_DIR "Win_64_3/sbol")
			set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj")
            
            if (${CMAKE_VERSION} VERSION_LESS "3.8.0")
                swig_add_module( libsbol64_3
                python
                libsbol.i )
            else()
                SWIG_ADD_LIBRARY( libsbol64_3
                    LANGUAGE python
                    SOURCES libsbol.i )	
            endif()
                    
            swig_link_libraries( libsbol64_3
                ${raptor2}
                ${PYTHON_LIBRARIES}
                ${curl}
                ${xml2}
                ${zlib}
                ${iconv}
                ${jsoncpp}
                ${LIBXSLT_LIBRARIES}
                sbol64)

            set_target_properties(_libsbol64_3 PROPERTIES OUTPUT_NAME "_libsbol")
 			file(MAKE_DIRECTORY ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR})
            file(MAKE_DIRECTORY ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR}/test)
            add_custom_command(TARGET _libsbol64_3 PRE_BUILD
                               COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/__init__.py ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR})
            add_custom_command(TARGET _libsbol64_3 PRE_BUILD
                               COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/CRISPR_example.py ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR})
            add_custom_command(TARGET _libsbol64_3 PRE_BUILD
                               COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/crispr_example.xml ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR})
            add_custom_command(TARGET _libsbol64_3 PRE_BUILD
                               COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/sbol.py ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR})
            add_custom_command(TARGET _libsbol64_3 PRE_BUILD
                               COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/unit_tests.py ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR})
            add_custom_command(TARGET _libsbol64_3 PRE_BUILD
                               COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/test/SBOLTestSuite ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR}/test)
            add_custom_command(TARGET _libsbol64_3 POST_BUILD
                               COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SWIG_OUTDIR}/libsbol.py ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR})
            add_custom_command(TARGET _libsbol64_3 POST_BUILD
                               COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SWIG_OUTDIR}/Release/_libsbol.pyd ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR})
			add_custom_command(TARGET _libsbol64_3 POST_BUILD
							   COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_SWIG_OUTDIR}/libsbol.py)
			add_custom_command(TARGET _libsbol64_3 POST_BUILD
							   COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_SWIG_OUTDIR}/libsbolPYTHON_wrap.cxx)
			add_custom_command(TARGET _libsbol64_3 POST_BUILD
							   COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_SWIG_OUTDIR}/Release)
        endif()
    endif()
endif()

#unset( PYTHON_LIBRARIES CACHE  )
#unset( PYTHONLIBS_FOUND CACHE  )
#unset(PYTHON_INCLUDE_DIRS CACHE  )
#unset(PYTHON_INCLUDE_DIR CACHE  )
#unset(PYTHONLIBS_VERSION_STRING CACHE )
#unset(PYTHON_INCLUDE_PATH CACHE)
#unset( PYTHON_LIBRARIES   )
#unset( PYTHONLIBS_FOUND   )
#unset(PYTHON_INCLUDE_DIRS   )
#unset(PYTHON_INCLUDE_DIR   )
#unset(PYTHONLIBS_VERSION_STRING  )
#unset(PYTHON_INCLUDE_PATH )

IF (SBOL_BUILD_PYTHON2)
    find_package( PythonLibs 2)

    message( "FOUND PYTHON = ${PYTHONLIBS_FOUND} at ${PYTHON_LIBRARIES}")
    message( "PYTHON INCLUDE DIRS = ${PYTHON_INCLUDE_DIRS}")
    message( "FOUND PYTHON VERSION ${PYTHONLIBS_VERSION_STRING}")

    INCLUDE_DIRECTORIES( ${PYTHON_INCLUDE_DIRS} )
    ADD_DEFINITIONS(-DSBOL_BUILD_PYTHON2)
    set(CMAKE_SWIG_FLAGS -DSBOL_BUILD_PYTHON2)
    if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
         ##### Python 2 wrappers for Mac 32x #####
        if (SBOL_BUILD_32)
            set(PYSBOL_TARGET_DIR "Mac_32_2/sbol")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -m32")

            # build the SWIG wrapper
            if (${CMAKE_VERSION} VERSION_LESS "3.8.0")
                swig_add_module( libsbol32_2
                python
                libsbol.i )
            else()
                SWIG_ADD_LIBRARY( libsbol32_2
                    LANGUAGE python
                    SOURCES libsbol.i )
            endif()

            # Do not link in the Python libraries on MacOSX....
            if(SBOL_BUILD_SHARED)
                swig_link_libraries( libsbol32_2
                    ${RAPTOR_LIBRARY}
                    ${CURL_LIBRARY}
                    ${LIBXSLT_LIBRARIES}
                    sbol32-shared)
            else()
                swig_link_libraries( libsbol32_2
                    ${RAPTOR_LIBRARY}
                    ${CURL_LIBRARY}
                    ${LIBXSLT_LIBRARIES}
                    sbol32)
            ENDIF()

            ### ...rather, resolve Python symbols dynamically due to differing runtime env
            set_target_properties(_libsbol32_2 PROPERTIES LINK_FLAGS "-undefined dynamic_lookup")

            ### Move target to a new directory and rename it, so the SWIG libraries can be directly copied into the pySBOL project
            set_target_properties(_libsbol32_2 PROPERTIES OUTPUT_NAME "${PYSBOL_TARGET_DIR}/_libsbol")

            file(MAKE_DIRECTORY ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR})
            file(MAKE_DIRECTORY ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR}/test)
            add_custom_command(TARGET _libsbol32_2 PRE_BUILD
                               COMMAND cp -r ${PROJECT_SOURCE_DIR}/test/SBOLTestSuite/* ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR}/test)
            add_custom_command(TARGET _libsbol32_2 PRE_BUILD
                               COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/__init__.py ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR}/__init__.py)
            add_custom_command(TARGET _libsbol32_2 PRE_BUILD
                               COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/sbol.py ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR}/sbol.py)
            add_custom_command(TARGET _libsbol32_2 PRE_BUILD
                               COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/CRISPR_example.py ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR}/CRISPR_example.py)
            add_custom_command(TARGET _libsbol32_2 PRE_BUILD
                               COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/crispr_example.xml ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR}/crispr_example.xml)
            add_custom_command(TARGET _libsbol32_2 PRE_BUILD
                               COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/unit_tests.py ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR}/unit_tests.py)
            add_custom_command(TARGET _libsbol32_2 PRE_BUILD
                               COMMAND cp ${CMAKE_SWIG_OUTDIR}/libsbol.py ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR}/libsbol.py)
            add_custom_command(TARGET _libsbol32_2 POST_BUILD
                               COMMAND mv ${CMAKE_SWIG_OUTDIR}/libsbol* ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR})
        endif()
        ##### Python 2 for Mac 64x ######
        if(SBOL_BUILD_64)
            set(PYSBOL_TARGET_DIR "Mac_64_2/sbol")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -m64")

            # build the SWIG wrapper
            if (${CMAKE_VERSION} VERSION_LESS "3.8.0")
                swig_add_module( libsbol64_2
                python
                libsbol.i )
            else()
                SWIG_ADD_LIBRARY( libsbol64_2
                    LANGUAGE python
                    SOURCES libsbol.i )
            endif()

            # Do not link in the Python libraries on MacOSX....
            if(SBOL_BUILD_SHARED)
                swig_link_libraries( libsbol64_2
                    ${RAPTOR_LIBRARY}
                    ${CURL_LIBRARY}
                    ${LIBXSLT_LIBRARIES}
                    sbol64-shared)
            else()
                swig_link_libraries( libsbol64_2
                    ${RAPTOR_LIBRARY}
                    ${CURL_LIBRARY}
                    ${LIBXSLT_LIBRARIES}
                    sbol64)
            ENDIF()

            # ...rather, resolve Python symbols dynamically due to differing runtime env
            set_target_properties(_libsbol64_2 PROPERTIES LINK_FLAGS "-undefined dynamic_lookup")

            ### Move target to a new directory and rename it, so the SWIG libraries can be directly copied into the pySBOL project
            set_target_properties(_libsbol64_2 PROPERTIES OUTPUT_NAME "${PYSBOL_TARGET_DIR}/_libsbol")
            file(MAKE_DIRECTORY ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR})
            file(MAKE_DIRECTORY ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR}/test)
            add_custom_command(TARGET _libsbol64_2 PRE_BUILD
                               COMMAND cp -r ${PROJECT_SOURCE_DIR}/test/SBOLTestSuite/* ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR}/test)
            add_custom_command(TARGET _libsbol64_2 PRE_BUILD
                               COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/__init__.py ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR}/__init__.py)
            add_custom_command(TARGET _libsbol64_2 PRE_BUILD
                               COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/sbol.py ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR}/sbol.py)
            add_custom_command(TARGET _libsbol64_2 PRE_BUILD
                               COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/CRISPR_example.py ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR}/CRISPR_example.py)
            add_custom_command(TARGET _libsbol64_2 PRE_BUILD
                               COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/crispr_example.xml ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR}/crispr_example.xml)
            add_custom_command(TARGET _libsbol64_2 PRE_BUILD
                               COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/unit_tests.py ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR}/unit_tests.py)
            add_custom_command(TARGET _libsbol64_2 PRE_BUILD
                               COMMAND cp ${CMAKE_SWIG_OUTDIR}/libsbol.py ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR}/libsbol.py)
            add_custom_command(TARGET _libsbol64_2 POST_BUILD
                               COMMAND mv ${CMAKE_SWIG_OUTDIR}/libsbol* ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR})
        endif()
    elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
        ##### Python 2 for Linux 32x ######
        if (SBOL_BUILD_32)
            set(PYSBOL_TARGET_DIR "Linux_32_2/sbol")  # target directory is synced with target directory for setup.py script
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -m32")

            if (${CMAKE_VERSION} VERSION_LESS "3.8.0")
                swig_add_module( libsbol
                python
                libsbol.i )
            else()
                SWIG_ADD_LIBRARY( libsbol
                    LANGUAGE python
                    SOURCES libsbol.i )
            endif()
                    
            if(SBOL_BUILD_SHARED)
                swig_link_libraries( libsbol
                    ${PYTHON_LIBRARIES}
                    ${RAPTOR_LIBRARY}
                    ${CURL_LIBRARY}
                    ${LIBXSLT_LIBRARIES}
                    sbol32-shared)
            else()
                swig_link_libraries( libsbol
                    ${PYTHON_LIBRARIES}
                    ${RAPTOR_LIBRARY}
                    ${CURL_LIBRARY}
		    ${OPENSSL_LIBRARY}  # linux only
		    ${CRYPTO_LIBRARY}   # linux only
                    ${LIBXSLT_LIBRARIES}
                    sbol32)
            ENDIF()

            file(MAKE_DIRECTORY ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR})
            file(MAKE_DIRECTORY ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR}/test)
            set_target_properties(_libsbol PROPERTIES OUTPUT_NAME "_libsbol")
            add_custom_command(TARGET _libsbol PRE_BUILD
                               COMMAND cp -r ${CMAKE_CURRENT_SOURCE_DIR}/__init__.py ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR})
            add_custom_command(TARGET _libsbol PRE_BUILD
                               COMMAND cp -r ${CMAKE_CURRENT_SOURCE_DIR}/CRISPR_example.py ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR})
            add_custom_command(TARGET _libsbol PRE_BUILD
                               COMMAND cp -r ${CMAKE_CURRENT_SOURCE_DIR}/crispr_example.xml ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR})
            add_custom_command(TARGET _libsbol PRE_BUILD
                               COMMAND cp -r ${CMAKE_CURRENT_SOURCE_DIR}/sbol.py ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR})
            add_custom_command(TARGET _libsbol PRE_BUILD
                               COMMAND cp -r ${CMAKE_CURRENT_SOURCE_DIR}/unit_tests.py ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR})
            add_custom_command(TARGET _libsbol PRE_BUILD
                               COMMAND cp -r ${PROJECT_SOURCE_DIR}/test/SBOLTestSuite/* ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR}/test)
            add_custom_command(TARGET _libsbol POST_BUILD
                               COMMAND cp -r ${CMAKE_SWIG_OUTDIR}/libsbol.py ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR})
            add_custom_command(TARGET _libsbol POST_BUILD
                               COMMAND mv ${CMAKE_SWIG_OUTDIR}/_libsbol.so ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR})
            add_custom_command(TARGET _libsbol POST_BUILD
                               COMMAND mv ${CMAKE_SWIG_OUTDIR}/libsbol* ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR})
        endif()
        ##### Python 2 for Linux 64x ######
        if (SBOL_BUILD_64)
            set(PYSBOL_TARGET_DIR "Linux_64_2/sbol")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -m64")
            
            if (${CMAKE_VERSION} VERSION_LESS "3.8.0")
                swig_add_module( libsbol
                python
                libsbol.i )
            else()
                SWIG_ADD_LIBRARY( libsbol
                    LANGUAGE python
                    SOURCES libsbol.i )
            endif()
                    
            if(SBOL_BUILD_SHARED)
                swig_link_libraries( libsbol
                    ${PYTHON_LIBRARIES}
                    ${RAPTOR_LIBRARY}
                    ${CURL_LIBRARY}
                    ${LIBXSLT_LIBRARIES}
                    sbol64-shared)
            else()
                swig_link_libraries( libsbol
                    ${PYTHON_LIBRARIES}
                    ${RAPTOR_LIBRARY}
                    ${CURL_LIBRARY}
		    ${OPENSSL_LIBRARY}  # linux only
		    ${CRYPTO_LIBRARY}   # linux only
                    ${LIBXSLT_LIBRARIES}
                    sbol64)
            ENDIF()

            file(MAKE_DIRECTORY ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR})
            file(MAKE_DIRECTORY ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR}/test)
            set_target_properties(_libsbol PROPERTIES OUTPUT_NAME "_libsbol")
            add_custom_command(TARGET _libsbol PRE_BUILD
                               COMMAND cp -r ${CMAKE_CURRENT_SOURCE_DIR}/__init__.py ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR})
            add_custom_command(TARGET _libsbol PRE_BUILD
                               COMMAND cp -r ${CMAKE_CURRENT_SOURCE_DIR}/CRISPR_example.py ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR})
            add_custom_command(TARGET _libsbol PRE_BUILD
                               COMMAND cp -r ${CMAKE_CURRENT_SOURCE_DIR}/crispr_example.xml ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR})
            add_custom_command(TARGET _libsbol PRE_BUILD
                               COMMAND cp -r ${CMAKE_CURRENT_SOURCE_DIR}/sbol.py ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR})
            add_custom_command(TARGET _libsbol PRE_BUILD
                               COMMAND cp -r ${CMAKE_CURRENT_SOURCE_DIR}/unit_tests.py ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR})
            add_custom_command(TARGET _libsbol PRE_BUILD
                               COMMAND cp -r ${PROJECT_SOURCE_DIR}/test/SBOLTestSuite/* ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR}/test)
            add_custom_command(TARGET _libsbol POST_BUILD
                               COMMAND cp -r ${CMAKE_SWIG_OUTDIR}/libsbol.py ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR})
            add_custom_command(TARGET _libsbol POST_BUILD
                               COMMAND mv ${CMAKE_SWIG_OUTDIR}/_libsbol.so ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR})
            add_custom_command(TARGET _libsbol POST_BUILD
                               COMMAND mv ${CMAKE_SWIG_OUTDIR}/libsbol* ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR})
        endif()
    else()
        ##### Python 2 for Win 32x ######
        include_directories( ${JSONCPP_INCLUDE_DIR}/..)
        include_directories( ${CURL_INCLUDE_DIR}/..)
        if (SBOL_BUILD_32)
            set(PYSBOL_TARGET_DIR "Win_32_2/sbol")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj")
            
            if (${CMAKE_VERSION} VERSION_LESS "3.8.0")
                swig_add_module( libsbol32_2
                python
                libsbol.i )
            else()
                SWIG_ADD_LIBRARY( libsbol32_2
                    LANGUAGE python
                    SOURCES libsbol.i )
            endif()
            
            swig_link_libraries( libsbol32_2
                ${raptor2}
                ${PYTHON_LIBRARIES}
                ${curl}
                ${xml2}
                ${zlib}
                ${iconv}
                ${jsoncpp}
                ${LIBXSLT_LIBRARIES}
                sbol32)

            set_target_properties(_libsbol32_2 PROPERTIES OUTPUT_NAME "_libsbol")
 			file(MAKE_DIRECTORY ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR})
            file(MAKE_DIRECTORY ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR}/test)
            add_custom_command(TARGET _libsbol32_2 PRE_BUILD
                               COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/__init__.py ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR})
            add_custom_command(TARGET _libsbol32_2 PRE_BUILD
                               COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/CRISPR_example.py ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR})
            add_custom_command(TARGET _libsbol32_2 PRE_BUILD
                               COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/crispr_example.xml ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR})
            add_custom_command(TARGET _libsbol32_2 PRE_BUILD
                               COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/sbol.py ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR})
            add_custom_command(TARGET _libsbol32_2 PRE_BUILD
                               COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/unit_tests.py ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR})
            add_custom_command(TARGET _libsbol32_2 PRE_BUILD
                               COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/test/SBOLTestSuite ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR}/test)
            add_custom_command(TARGET _libsbol32_2 POST_BUILD
                               COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SWIG_OUTDIR}/libsbol.py ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR})
            add_custom_command(TARGET _libsbol32_2 POST_BUILD
                               COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SWIG_OUTDIR}/Release/_libsbol.pyd ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR})
			add_custom_command(TARGET _libsbol32_2 POST_BUILD
							   COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_SWIG_OUTDIR}/libsbol.py)
			add_custom_command(TARGET _libsbol32_2 POST_BUILD
							   COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_SWIG_OUTDIR}/libsbolPYTHON_wrap.cxx)
			add_custom_command(TARGET _libsbol32_2 POST_BUILD
							   COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_SWIG_OUTDIR}/Release)
   		endif()
         ##### Python 2 for Win 64x ######
        if (SBOL_BUILD_64)
            set(PYSBOL_TARGET_DIR "Win_64_2/sbol")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj")
            
            if (${CMAKE_VERSION} VERSION_LESS "3.8.0")
                swig_add_module( libsbol64_2
                python
                libsbol.i )
            else()
                SWIG_ADD_LIBRARY( libsbol64_2
                    LANGUAGE python
                    SOURCES libsbol.i )
            endif()
                    
            swig_link_libraries( libsbol64_2
                ${raptor2}
                ${PYTHON_LIBRARIES}
                ${curl}
                ${xml2}
                ${zlib}
                ${iconv}
                ${jsoncpp}
                ${LIBXSLT_LIBRARIES}
                sbol64)

            set_target_properties(_libsbol64_2 PROPERTIES OUTPUT_NAME "_libsbol")
 			file(MAKE_DIRECTORY ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR})
            file(MAKE_DIRECTORY ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR}/test)
            add_custom_command(TARGET _libsbol64_2 PRE_BUILD
                               COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/__init__.py ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR})
            add_custom_command(TARGET _libsbol64_2 PRE_BUILD
                               COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/CRISPR_example.py ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR})
            add_custom_command(TARGET _libsbol64_2 PRE_BUILD
                               COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/crispr_example.xml ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR})
            add_custom_command(TARGET _libsbol64_2 PRE_BUILD
                               COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/sbol.py ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR})
            add_custom_command(TARGET _libsbol64_2 PRE_BUILD
                               COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/unit_tests.py ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR})
            add_custom_command(TARGET _libsbol64_2 PRE_BUILD
                               COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/test/SBOLTestSuite ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR}/test)
            add_custom_command(TARGET _libsbol64_2 POST_BUILD
                               COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SWIG_OUTDIR}/libsbol.py ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR})
            add_custom_command(TARGET _libsbol64_2 POST_BUILD
                               COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SWIG_OUTDIR}/Release/_libsbol.pyd ${CMAKE_SWIG_OUTDIR}/${PYSBOL_TARGET_DIR})
			add_custom_command(TARGET _libsbol64_2 POST_BUILD
							   COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_SWIG_OUTDIR}/libsbol.py)
			add_custom_command(TARGET _libsbol64_2 POST_BUILD
							   COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_SWIG_OUTDIR}/libsbolPYTHON_wrap.cxx)
			add_custom_command(TARGET _libsbol64_2 POST_BUILD
							   COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_SWIG_OUTDIR}/Release)
        endif()
    endif()
    if(SBOL_BUILD_MANYLINUX)
        set_target_properties(_libsbol PROPERTIES LINK_FLAGS "-Wl,-lrt")
    endif(SBOL_BUILD_MANYLINUX)
endif()



ELSE()

    MESSAGE( "SWIG not found; unable to generate Python bindings" )

ENDIF()

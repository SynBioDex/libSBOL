
add_subdirectory( raptor )

# gather headers
if( RASQAL_LIBRARY AND SBOL_BUILD_RASQAL )
    include_directories( ${RASQAL_INCLUDE_DIR})
    ADD_DEFINITIONS(-DHAVE_LIBRASQAL)
    SET(RASQAL_HEADERS RasqalDataGraph.hh RasqalQueryResults.hh
                      PtrWrapper.hh SharedPtrWrapper.hh)
    SET(RASQAL_SOURCES RasqalDataGraph.cc RasqalQueryResults.cc)
endif()

include_directories( ${RAPTOR_INCLUDE_DIR})
include_directories( ${JsonCpp_INCLUDE_DIR})
include_directories( ${CURL_INCLUDE_DIR})
include_directories( ${OPENSSL_INCLUDE_DIR})
if( SBOL_BUILD_PYTHON2 )
    find_package( SWIG REQUIRED )
    find_package( PythonLibs 2)
    include_directories( ${PYTHON_INCLUDE_DIR} )
    ADD_DEFINITIONS(-DSBOL_BUILD_PYTHON2)
endif()
if( SBOL_BUILD_PYTHON3 )
    find_package( SWIG REQUIRED )
    find_package( PythonLibs 3)
    include_directories( ${PYTHON_INCLUDE_DIR} )
    ADD_DEFINITIONS(-DSBOL_BUILD_PYTHON3)
endif()
if( SBOL_BUILD_MANYLINUX )
    add_definitions(-DSBOL_BUILD_MANYLINUX)
endif()

# gather source files
FILE(GLOB SBOL_HEADER_FILES
    constants.h
    sbolerror.h
    config.h
    validation.h
	property.h
    properties.h
    object.h
	identified.h
    measure.h
	toplevel.h
	sequenceannotation.h
	component.h
	componentdefinition.h
	sequence.h
	document.h
	interaction.h
	participation.h
	location.h
	sequenceconstraint.h
	moduledefinition.h
	module.h
	mapsto.h
	model.h
  collection.h
  assembly.h
  provo.h
  partshop.h
    combinatorialderivation.h
    dbtl.h
    attachment.h
    implementation.h
    experiment.h
	sbol.h
        ${RASQAL_HEADERS}
        )

FILE(GLOB SBOL_SOURCE_FILES
	sbolerror.cpp
  config.cpp
  validation.cpp
  properties.cpp
	object.cpp
  identified.cpp
	toplevel.cpp
	document.cpp
  assembly.cpp
  partshop.cpp
    dbtl.cpp
    ${RASQAL_SOURCES})



FILE(COPY ${SBOL_HEADER_FILES} DESTINATION  ${HEADER_OUTPUT_PATH} )


#ADD_EXECUTABLE(sbol ${SBOL_SOURCE_FILES})



# build static library for release

# by default, GCC exports everything;
# this tells it to stick to SBOLAPIEXPORTS functions
IF(CMAKE_COMPILER_IS_GNUCC)
	SET_TARGET_PROPERTIES( PROPERTIES COMPILE_FLAGS -fvisibility=hidden)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
ENDIF()

# link against raptor
if(${CMAKE_SYSTEM_NAME} MATCHES "Linux" OR "Darwin")
    if(NOT SBOL_BUILD_SHARED)
        ADD_DEFINITIONS(-DRAPTOR_STATIC)
    endif()
endif()

get_directory_property( DirDefs COMPILE_DEFINITIONS )
#message( "COMPILE_DEFINITIONS = ${DirDefs}" )

message("${INCLUDE_DIRECTORIES}")

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    ADD_DEFINITIONS(-DLIBXML_STATIC -DRAPTOR_STATIC -DLIBXSLT_STATIC -DCURL_STATIC -DCURL_STATICLIB)
    add_definitions(-DSBOL_WIN)
    include_directories( ${JSONCPP_INCLUDE_DIR}/..)
    include_directories( ${CURL_INCLUDE_DIR}/..)
    if(SBOL_BUILD_32)
        message("Configuring for x86")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj /EHsc")
        #Always build static
        if(SBOL_BUILD_SHARED)
            add_library( sbol32-shared
                SHARED
                ${SBOL_HEADER_FILES}
                ${SBOL_SOURCE_FILES})
            target_link_libraries( sbol32-shared
                ${raptor2}
                ${xml2}
                ${zlib}
                ${iconv}
                ${jsoncpp}
                ${libcurl}
                Ws2_32.lib )
            set_target_properties (sbol32-shared PROPERTIES COMPILE_DEFINITIONS "SBOL_SHAREDLIB")
            set_target_properties(sbol32-shared PROPERTIES  
                ARCHIVE_OUTPUT_DIRECTORY "${SBOL_LIBRARY_OUTPUT_PATH}/bin"
                LIBRARY_OUTPUT_DIRECTORY "${SBOL_LIBRARY_OUTPUT_PATH}/bin"
                RUNTIME_OUTPUT_DIRECTORY "${SBOL_LIBRARY_OUTPUT_PATH}/bin")
            install(TARGETS sbol32-shared DESTINATION bin)   # Installs to C:\Program Files (x86)\SBOL\bin            
            set_target_properties(sbol32-shared PROPERTIES OUTPUT_NAME "sbol")
        endif()
        add_library( sbol32
                STATIC
                ${SBOL_HEADER_FILES}
                ${SBOL_SOURCE_FILES})
        target_link_libraries( sbol32
            ${raptor2}
            ${xml2}
            ${zlib}
            ${iconv}
            ${jsoncpp}
            ${libcurl}
            Ws2_32.lib )
        set_target_properties(sbol32 PROPERTIES  
            ARCHIVE_OUTPUT_DIRECTORY "${SBOL_LIBRARY_OUTPUT_PATH}"
            LIBRARY_OUTPUT_DIRECTORY "${SBOL_LIBRARY_OUTPUT_PATH}"
            RUNTIME_OUTPUT_DIRECTORY "${SBOL_LIBRARY_OUTPUT_PATH}")
        install(DIRECTORY ${HEADER_OUTPUT_PATH} DESTINATION ${CMAKE_INSTALL_PREFIX})
        if(NOT SBOL_BUILD_SHARED)
            install(TARGETS sbol32 DESTINATION lib)   # Installs to C:\Program Files (x86)\SBOL\lib
            set_target_properties(sbol32 PROPERTIES OUTPUT_NAME "sbol")
        endif()
    endif()
    if(SBOL_BUILD_64)
        message("Configuring for x64")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj /EHsc")
        #Always build static
        if(SBOL_BUILD_SHARED)
            add_library( sbol64-shared
                SHARED
                ${SBOL_HEADER_FILES}
                ${SBOL_SOURCE_FILES})
            target_link_libraries( sbol64-shared
                ${raptor2}
                ${xml2}
                ${zlib}
                ${iconv}
                ${jsoncpp}
                ${libcurl}
                Ws2_32.lib )
            set_target_properties(sbol64-shared PROPERTIES COMPILE_DEFINITIONS "SBOL_SHAREDLIB")
            set_target_properties(sbol64-shared PROPERTIES  
                ARCHIVE_OUTPUT_DIRECTORY "${SBOL_LIBRARY_OUTPUT_PATH}/bin"
                LIBRARY_OUTPUT_DIRECTORY "${SBOL_LIBRARY_OUTPUT_PATH}/bin"
                RUNTIME_OUTPUT_DIRECTORY "${SBOL_LIBRARY_OUTPUT_PATH}/bin")
            install(TARGETS sbol64-shared DESTINATION bin)   # Installs to C:\Program Files (x86)\SBOL\bin
            set_target_properties(sbol64-shared PROPERTIES OUTPUT_NAME "sbol")
        endif()
        add_library( sbol64
                STATIC
                ${SBOL_HEADER_FILES}
                ${SBOL_SOURCE_FILES})
        target_link_libraries( sbol64
            ${raptor2}
            ${xml2}
            ${zlib}
            ${iconv}
            ${jsoncpp}
            ${libcurl}
            Ws2_32.lib )
        set_target_properties(sbol64 PROPERTIES  
            ARCHIVE_OUTPUT_DIRECTORY "${SBOL_LIBRARY_OUTPUT_PATH}"
            LIBRARY_OUTPUT_DIRECTORY "${SBOL_LIBRARY_OUTPUT_PATH}"
            RUNTIME_OUTPUT_DIRECTORY "${SBOL_LIBRARY_OUTPUT_PATH}")
        install(DIRECTORY ${HEADER_OUTPUT_PATH} DESTINATION ${CMAKE_INSTALL_PREFIX})
        if(NOT SBOL_BUILD_SHARED)
            install(TARGETS sbol64 DESTINATION lib)   # Installs to C:\Program Files (x86)\SBOL\lib
            set_target_properties(sbol64 PROPERTIES OUTPUT_NAME "sbol")
        endif()
    endif()

else ()  # If Mac OSX or Linux
    if(SBOL_BUILD_32)
        message("Configuring for x86")
        set(CMAKE_OSX_ARCHITECTURES "i386")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -m32")
        if(SBOL_BUILD_SHARED)
            add_library( sbol32-shared
                SHARED
                ${SBOL_HEADER_FILES}
                ${SBOL_SOURCE_FILES})
            set_target_properties(sbol32-shared PROPERTIES LINKER_LANGUAGE CXX)
            target_link_libraries(sbol32-shared
                ${RAPTOR_LIBRARY}
                ${CURL_LIBRARY}
                ${LIBXSLT_LIBRARIES}
                ${JsonCpp_LIBRARY})
            set_target_properties(sbol32-shared PROPERTIES
                ARCHIVE_OUTPUT_DIRECTORY "${SBOL_LIBRARY_OUTPUT_PATH}/lib"
                LIBRARY_OUTPUT_DIRECTORY "${SBOL_LIBRARY_OUTPUT_PATH}/lib"
                RUNTIME_OUTPUT_DIRECTORY "${SBOL_LIBRARY_OUTPUT_PATH}/lib")
            install(TARGETS sbol32-shared DESTINATION lib)  # Installs to /usr/local/lib
            install(DIRECTORY ${HEADER_OUTPUT_PATH} DESTINATION ${CMAKE_INSTALL_PREFIX}/include)
            set_target_properties(sbol32-shared PROPERTIES OUTPUT_NAME "sbol")
        else()
            add_library( sbol32
                STATIC
                ${SBOL_HEADER_FILES}
                ${SBOL_SOURCE_FILES})        
            set_target_properties(sbol32 PROPERTIES LINKER_LANGUAGE CXX)
            target_link_libraries(sbol32
                ${RAPTOR_LIBRARY}
                ${CURL_LIBRARY}
		${OPENSSL_LIBRARY}  # linux only
		${CRYPTO_LIBRARY}   # linux only
                ${LIBXSLT_LIBRARIES}
                ${JsonCpp_LIBRARY})
            set_target_properties(sbol32 PROPERTIES
                ARCHIVE_OUTPUT_DIRECTORY "${SBOL_LIBRARY_OUTPUT_PATH}/lib"
                LIBRARY_OUTPUT_DIRECTORY "${SBOL_LIBRARY_OUTPUT_PATH}/lib"
                RUNTIME_OUTPUT_DIRECTORY "${SBOL_LIBRARY_OUTPUT_PATH}/lib")
            install(DIRECTORY ${HEADER_OUTPUT_PATH} DESTINATION ${CMAKE_INSTALL_PREFIX}/include)
            install(TARGETS sbol32 DESTINATION lib)  # Installs to /usr/local/lib
            set_target_properties(sbol32 PROPERTIES OUTPUT_NAME "sbol")
        endif()
    endif()
    if(SBOL_BUILD_64)
        message("Configuring for x64")
        set(CMAKE_OSX_ARCHITECTURES "x86_64")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -m64")
        get_directory_property( DirDefs COMPILE_DEFINITIONS )
        message( "COMPILE_DEFINITIONS = ${DirDefs}" )
        if(SBOL_BUILD_SHARED)
            add_library( sbol64-shared
                SHARED
                ${SBOL_HEADER_FILES}
                ${SBOL_SOURCE_FILES})
            set_target_properties(sbol64-shared PROPERTIES LINKER_LANGUAGE CXX)
            target_link_libraries(sbol64-shared
                ${RAPTOR_LIBRARY}
                ${CURL_LIBRARY}
                ${LIBXSLT_LIBRARIES}
                ${JsonCpp_LIBRARY})
            set_target_properties(sbol64-shared PROPERTIES
                ARCHIVE_OUTPUT_DIRECTORY "${SBOL_LIBRARY_OUTPUT_PATH}/lib"
                LIBRARY_OUTPUT_DIRECTORY "${SBOL_LIBRARY_OUTPUT_PATH}/lib"
                RUNTIME_OUTPUT_DIRECTORY "${SBOL_LIBRARY_OUTPUT_PATH}/lib")
            install(TARGETS sbol64-shared DESTINATION lib)  # Installs to /usr/local/lib
            install(DIRECTORY ${HEADER_OUTPUT_PATH} DESTINATION ${CMAKE_INSTALL_PREFIX}/include)
            set_target_properties(sbol64-shared PROPERTIES OUTPUT_NAME "sbol")
        else()
            add_library( sbol64
                STATIC
                ${SBOL_HEADER_FILES}
                ${SBOL_SOURCE_FILES})
            set_target_properties(sbol64 PROPERTIES LINKER_LANGUAGE CXX)
            target_link_libraries(sbol64
                ${RAPTOR_LIBRARY}
                ${CURL_LIBRARY}
		${OPENSSL_LIBRARY}  # linux only
		${CRYPTO_LIBRARY}   # linux only
                ${LIBXSLT_LIBRARIES}
                ${JsonCpp_LIBRARY})
            set_target_properties(sbol64 PROPERTIES
                ARCHIVE_OUTPUT_DIRECTORY "${SBOL_LIBRARY_OUTPUT_PATH}/lib"
                LIBRARY_OUTPUT_DIRECTORY "${SBOL_LIBRARY_OUTPUT_PATH}/lib"
                RUNTIME_OUTPUT_DIRECTORY "${SBOL_LIBRARY_OUTPUT_PATH}/lib")
            install(TARGETS sbol64 DESTINATION lib)  # Installs to /usr/local/lib
            install(DIRECTORY ${HEADER_OUTPUT_PATH} DESTINATION ${CMAKE_INSTALL_PREFIX}/include)
            set_target_properties(sbol64 PROPERTIES OUTPUT_NAME "sbol")
        endif()
    endif(SBOL_BUILD_64)
ENDIF ()


# Print include directories
#get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
#foreach(dir ${dirs})
#message(STATUS "dir='${dir}'")
#endforeach()

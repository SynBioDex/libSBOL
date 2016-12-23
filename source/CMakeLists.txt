
#ADD_SUBDIRECTORY( libxml2 )
ADD_SUBDIRECTORY( raptor )

# gather headers
include_directories( ${RAPTOR_INCLUDE_DIR})

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
    assembly.h
	sbol.h)
FILE(GLOB SBOL_SOURCE_FILES
	sbolerror.cpp
    config.cpp
    validation.cpp
    properties.cpp
	object.cpp
    identified.cpp
	toplevel.cpp
	componentdefinition.cpp
	document.cpp
    assembly.cpp)
	

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
#ADD_DEFINITIONS( -DRAPTOR_STATIC -DLIBXML_STATIC)
ADD_DEFINITIONS(-DLIBXML_STATIC -DRAPTOR_STATIC -DLIBXSLT_STATIC -DCURL_STATIC)

get_directory_property( DirDefs COMPILE_DEFINITIONS )
#message( "COMPILE_DEFINITIONS = ${DirDefs}" )



if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    if(SBOL_BUILD_32)
        message("Configuring for x86")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc")
        if(SBOL_BUILD_STATIC)
            add_library( sbol32
                STATIC
                ${SBOL_HEADER_FILES}
                ${SBOL_SOURCE_FILES})
        elseif(SBOL_BUILD_SHARED)
            add_library( sbol32
                SHARED
                ${SBOL_HEADER_FILES}
                ${SBOL_SOURCE_FILES})
        endif()
        target_link_libraries( sbol32
            ${RAPTOR_LIBRARY}
            ${LIBXML2_LIBRARIES}
            ${zlib}
            ${iconv}
            Ws2_32.lib )
        install(TARGETS sbol32 DESTINATION lib)   # Installs to C:\Program Files (x86)\SBOL\lib
        install(DIRECTORY ${HEADER_OUTPUT_PATH} DESTINATION ${CMAKE_INSTALL_PREFIX}/include)
        set_target_properties(sbol32 PROPERTIES OUTPUT_NAME "sbol")
    endif()
    if(SBOL_BUILD_64)
        message("Configuring for x64")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc")
        if(SBOL_BUILD_STATIC)
            add_library( sbol64
                STATIC
                ${SBOL_HEADER_FILES}
                ${SBOL_SOURCE_FILES})
        elseif(SBOL_BUILD_SHARED)
            add_library( sbol64
                SHARED
                ${SBOL_HEADER_FILES}
                ${SBOL_SOURCE_FILES})
        endif()
        target_link_libraries( sbol64
            ${RAPTOR_LIBRARY}
            ${LIBXML2_LIBRARIES}
            ${zlib}
            ${iconv}
            Ws2_32.lib )
        install(TARGETS sbol64 DESTINATION lib)   # Installs to C:\Program Files (x86)\SBOL\lib
        install(DIRECTORY ${HEADER_OUTPUT_PATH} DESTINATION ${CMAKE_INSTALL_PREFIX}/include)
        set_target_properties(sbol64 PROPERTIES OUTPUT_NAME "sbol")
    endif()

else ()  # If Mac OSX or Linux
    if(SBOL_BUILD_32)
        message("Configuring for x86")
        set(CMAKE_OSX_ARCHITECTURES "i386")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -m32")
        if(SBOL_BUILD_STATIC)
            add_library( sbol32
                STATIC
                ${SBOL_HEADER_FILES}
                ${SBOL_SOURCE_FILES})
        elseif(SBOL_BUILD_SHARED)
            add_library( sbol32
                SHARED
                ${SBOL_HEADER_FILES}
                ${SBOL_SOURCE_FILES})
        endif()
        set_target_properties(sbol32 PROPERTIES LINKER_LANGUAGE CXX)
        target_link_libraries( sbol32
            ${RAPTOR_LIBRARY}
            ${CURL_LIBRARY}
            ${LIBXSLT_LIBRARIES}
            ${JsonCpp_LIBRARY})
        install(TARGETS sbol32 DESTINATION lib)  # Installs to /usr/local/lib
        install(DIRECTORY ${HEADER_OUTPUT_PATH} DESTINATION ${CMAKE_INSTALL_PREFIX}/include)
        set_target_properties(sbol32 PROPERTIES OUTPUT_NAME "sbol")
    endif()
    if(SBOL_BUILD_64)
        message("Configuring for x64")
        set(CMAKE_OSX_ARCHITECTURES "x86_64")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -m64")
        if(SBOL_BUILD_STATIC)
            #add_definitions(-DLIBXML_STATIC -DRAPTOR_STATIC)
            get_directory_property( DirDefs COMPILE_DEFINITIONS )
            message( "COMPILE_DEFINITIONS = ${DirDefs}" )

            if (NOT SBOL_BUILD_COMBINED)
                add_library( sbol64 STATIC ${SBOL_HEADER_FILES} ${SBOL_SOURCE_FILES})
            endif(NOT SBOL_BUILD_COMBINED)

            if (SBOL_BUILD_COMBINED)  # Import Raptor to build into a combined archive.  This works, but dynamic dependencies are not linked properly
                #add_library( __raptor STATIC IMPORTED )
                #set_property(TARGET __raptor PROPERTY IMPORTED_LOCATION ${RAPTOR_LIBRARY})
                set(dummyfile ${CMAKE_CURRENT_BINARY_DIR}/${outlib}_dummy.cpp)
                file(WRITE ${dummyfile} "const char * dummy = \"${dummyfile}\";")
                add_library( _raptor STATIC ${dummyfile} )
                target_link_libraries( _raptor
                    ${RAPTOR_LIBRARY}
                    ${CURL_LIBRARY}
                    ${LIBXSLT_LIBRARIES}
                    ${JsonCpp_LIBRARY})
                #add_library( _raptor STATIC IMPORTED )
                #set_property(TARGET _raptor PROPERTY IMPORTED_LOCATION ${RAPTOR_LIBRARY})

                add_library( _sbol64
                    STATIC
                    ${SBOL_HEADER_FILES}
                    ${SBOL_SOURCE_FILES})

                include(mergestaticlibs.cmake)
                merge_static_libs(sbol64 _sbol64 _raptor)
            endif(SBOL_BUILD_COMBINED)

        elseif(SBOL_BUILD_SHARED)
            add_library( sbol64
                SHARED
                ${SBOL_HEADER_FILES}
                ${SBOL_SOURCE_FILES})
        endif()
        set_target_properties(sbol64 PROPERTIES LINKER_LANGUAGE CXX)
        target_link_libraries( sbol64
            ${RAPTOR_LIBRARY}
            ${CURL_LIBRARY}
            ${LIBXSLT_LIBRARIES}
            ${JsonCpp_LIBRARY})
        install(TARGETS sbol64 DESTINATION lib)  # Installs to /usr/local/lib
        install(DIRECTORY ${HEADER_OUTPUT_PATH} DESTINATION ${CMAKE_INSTALL_PREFIX}/include)
        set_target_properties(sbol64 PROPERTIES OUTPUT_NAME "sbol")
    endif(SBOL_BUILD_64)
ENDIF ()


# Print include directories
#get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
#foreach(dir ${dirs})
#message(STATUS "dir='${dir}'")
#endforeach()

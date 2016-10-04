
#ADD_SUBDIRECTORY( libxml2 )
ADD_SUBDIRECTORY( raptor )

# gather headers
INCLUDE_DIRECTORIES( ${HEADER_DIR} )
INCLUDE_DIRECTORIES( ${XML2_HEADER_DIR})
INCLUDE_DIRECTORIES( ${RAPTOR_HEADER_DIR})

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
	SET_TARGET_PROPERTIES( sbol
		PROPERTIES COMPILE_FLAGS -fvisibility=hidden
	)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
ENDIF()

# link against raptor




if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    if(SBOL_GENERATE_32)
        target_link_libraries( sbol
            ${raptor2}
            ${xml2}
            ${zlib}
            ${iconv}
            Ws2_32.lib )
        install(TARGETS sbol DESTINATION lib)   # Installs to C:\Program Files (x86)\SBOL\lib
        install(DIRECTORY ${HEADER_OUTPUT_PATH} DESTINATION ${CMAKE_INSTALL_PREFIX})
    endif()
    if(SBOL_GENERATE_64)
    endif()
else ()
    if(SBOL_GENERATE_32)
        message("Configuring for x86")

        set(CMAKE_OSX_ARCHITECTURES "i386")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -m32")
        if(SBOL_BUILD_STATIC)
            add_definitions(-DLIBXML_STATIC -DRAPTOR_STATIC)
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
            ${raptor2}
            ${xml2}
            ${zlib}
            ${iconv})
        install(TARGETS sbol32 DESTINATION lib)  # Installs to /usr/local/lib
        install(DIRECTORY ${HEADER_OUTPUT_PATH} DESTINATION ${CMAKE_INSTALL_PREFIX}/include)
    endif()
    if(SBOL_GENERATE_64)
        message("Configuring for x64")
        set(CMAKE_OSX_ARCHITECTURES "x86_64")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -m64")
        if(SBOL_BUILD_STATIC)
            add_definitions(-DLIBXML_STATIC -DRAPTOR_STATIC)
            add_library( sbol64
                STATIC
                ${SBOL_HEADER_FILES}
                ${SBOL_SOURCE_FILES})
        elseif(SBOL_BUILD_SHARED)
            add_library( sbol64
                STATIC
                ${SBOL_HEADER_FILES}
                ${SBOL_SOURCE_FILES})
        endif()
        set_target_properties(sbol64 PROPERTIES LINKER_LANGUAGE CXX)
        target_link_libraries( sbol64
            ${raptor2}
            ${xml2}
            ${zlib}
            ${iconv} )
        install(TARGETS sbol64 DESTINATION lib)  # Installs to /usr/local/lib
        install(TARGETS sbol64 DESTINATION lib)  # Installs to /usr/local/lib
        install(DIRECTORY ${HEADER_OUTPUT_PATH} DESTINATION ${CMAKE_INSTALL_PREFIX}/include)
    endif()
ENDIF ()





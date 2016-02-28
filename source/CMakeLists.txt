
ADD_SUBDIRECTORY( libxml2 )
ADD_SUBDIRECTORY( raptor )

# gather headers
INCLUDE_DIRECTORIES( ${HEADER_DIR} )
INCLUDE_DIRECTORIES( ${XML2_HEADER_DIR})
INCLUDE_DIRECTORIES( ${RAPTOR_HEADER_DIR})
# gather source files
FILE(GLOB SBOL_HEADER_FILES
    constants.h
	validation.h
	sbolerror.h
	property.h
    properties.h
    object.h
	identified.h
	toplevel.h
	generictoplevel.h
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
	sbol.h)
FILE(GLOB SBOL_SOURCE_FILES
	validation.cpp
	sbolerror.cpp
	object.cpp
	identified.cpp
	toplevel.cpp
	componentdefinition.cpp
	document.cpp
	serializer.cpp)
	

FILE(COPY ${SBOL_HEADER_FILES} DESTINATION  ${HEADER_OUTPUT_PATH} )


#ADD_EXECUTABLE(sbol ${SBOL_SOURCE_FILES})
ADD_LIBRARY( sbol
		STATIC
		${SBOL_HEADER_FILES}
		${SBOL_SOURCE_FILES}
	)


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
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
SET_TARGET_PROPERTIES(sbol PROPERTIES LINKER_LANGUAGE CXX)
ADD_DEFINITIONS(-DLIBXML_STATIC -DRAPTOR_STATIC)



IF (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    TARGET_LINK_LIBRARIES( sbol
        ${raptor2}
        ${xml2}
        ${zlib}
        ${iconv}
        Ws2_32.lib )
	INSTALL(TARGETS sbol DESTINATION lib)  # Installs to /usr/local/lib
	INSTALL(DIRECTORY ${HEADER_OUTPUT_PATH} DESTINATION ${CMAKE_INSTALL_PREFIX}/include)  
ELSE ()
    TARGET_LINK_LIBRARIES( sbol
        ${raptor2}
        ${xml2}
        ${zlib}
        ${iconv} )
	INSTALL(TARGETS sbol DESTINATION lib)  # Installs to C:\Program Files (x86)\SBOL\lib
	INSTALL(DIRECTORY ${HEADER_OUTPUT_PATH} DESTINATION ${CMAKE_INSTALL_PREFIX}/include)  
ENDIF ()





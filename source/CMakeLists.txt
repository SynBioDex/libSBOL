# set variables in source code
#CONFIGURE_FILE(
#	${SBOL_SOURCE_DIR}/constants.h.in
#	${SBOL_SOURCE_DIR}/constants.h
#)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        MESSAGE(64)
    else()
        MESSAGE(32)
    endif()

# set up folder structure
SET( PROJECT_DIR      ${CMAKE_CURRENT_SOURCE_DIR} )
SET( LINK_DIR	${PROJECT_DIR}/raptor/lib )
SET( HEADER_DIR	${PROJECT_DIR}/raptor/include/raptor2 )
SET( SBOL_RELEASE_DIR       ${SBOL_RELEASE_DIR}/library )
SET( LIBRARY_OUTPUT_PATH    ${SBOL_RELEASE_DIR} )
SET( HEADER_OUTPUT_PATH		${SBOL_RELEASE_DIR}/include )

# gather headers
INCLUDE_DIRECTORIES( ${HEADER_DIR} )

# gather source files
FILE(GLOB SBOL_HEADER_FILES 
	validation.h
	sbolerror.h
	property.h
	identified.h
	toplevel.h
	generictoplevel.h
	sequenceannotation.h
	componentdefinition.h
	sequence.h
	document.h)
FILE(GLOB SBOL_SOURCE_FILES	
	validation.cpp
	sbolerror.cpp
	property.cpp
	identified.cpp
	toplevel.cpp
	componentdefinition.cpp
	document.cpp
	serializer.cpp)
	
# copy header files to release/library/include for out-of-source build
# TODO: remove a couple of Makefiles contaminating the HEADER_OUTPUT_PATH
FILE(COPY ${LIBXML2_HEADER_FILES} DESTINATION  ${HEADER_OUTPUT_PATH} )
FILE(COPY ${SBOL_HEADER_FILES} DESTINATION  ${HEADER_OUTPUT_PATH} )

ADD_EXECUTABLE(sbol ${SBOL_SOURCE_FILES})

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
FIND_LIBRARY(raptor2
    NAME raptor2.lib
	PATHS ${LINK_DIR}
    )
MESSAGE(${raptor2})


TARGET_LINK_LIBRARIES( sbol
	${raptor2}
	${LINK_DIR}/libxml2_a.lib
	${LINK_DIR}/zlib.lib
	${LINK_DIR}/iconv_a.lib
	Ws2_32.lib )
	



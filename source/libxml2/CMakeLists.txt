# copy  libXML2 header files to release/library/include for out-of-source build
# TODO: remove a couple of Makefiles contaminating the HEADER_OUTPUT_PATH
SET( LIBXML2_HEADER_DIR		${CMAKE_CURRENT_SOURCE_DIR}/include CACHE PATH "libxml2 path")
FILE(GLOB LIBXML2_HEADER_FILES 
	${LIBXML2_HEADER_DIR}/*.h)
FILE(COPY ${LIBXML2_HEADER_FILES} DESTINATION  ${HEADER_OUTPUT_PATH} )

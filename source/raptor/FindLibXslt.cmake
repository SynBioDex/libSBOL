#.rst:
# FindLibXslt
# -----------
#
# Try to find the LibXslt library
#
# Once done this will define
#
# ::
#
#   LIBXSLT_FOUND - system has LibXslt
#   LIBXSLT_INCLUDE_DIR - the LibXslt include directory
#   LIBXSLT_LIBRARIES - Link these to LibXslt
#   LIBXSLT_DEFINITIONS - Compiler switches required for using LibXslt
#   LIBXSLT_VERSION_STRING - version of LibXslt found (since CMake 2.8.8)
#
# Additionally, the following two variables are set (but not required
# for using xslt):
#
# ``LIBXSLT_EXSLT_LIBRARIES``
#   Link to these if you need to link against the exslt library.
# ``LIBXSLT_XSLTPROC_EXECUTABLE``
#   Contains the full path to the xsltproc executable if found.

#=============================================================================
# Copyright 2006-2009 Kitware, Inc.
# Copyright 2006 Alexander Neundorf <neundorf@kde.org>
#
# Distributed under the OSI-approved BSD License (the "License");
# see accompanying file Copyright.txt for details.
#
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the License for more information.
#=============================================================================
# (To distribute this file outside of CMake, substitute the full
#  License text for the above reference.)

# search Homebrew directories first

find_path(LIBXSLT_INCLUDE_DIR 
          NAMES xslt.h 
          PATHS /usr/local/opt/libxslt/include/libxslt 
                /usr/include/libxslt # Linux
                )
#find_path(LIBXSLT_EXSLT_INCLUDE_DIR NAMES exslt.h HINTS /usr/local/opt/libxslt/include/libexslt)

# if(SBOL_BUILD_SHARED)
# if(LIBXSLT_LIBRARIES MATCHES "(.*).(a|lib)")
# unset(LIBXSLT_LIBRARIES CACHE)
# endif()
# else()
# if(LIBXSLT_LIBRARIES MATCHES "(.*).(so|dylib|dll)")
# unset(LIBXSLT_LIBRARIES CACHE)
# endif()
# endif()

find_library(LIBXSLT_LIBRARIES 
             NAMES xslt libxslt 
             PATHS /usr/local/opt/libxslt/lib
                   /usr/lib/i386-linux-gnu
                   /usr/lib/x86_64-linux-gnu
                   )
message("LIBXSLT_INCLUDE_DIR: ${LIBXSLT_INCLUDE_DIR}")
#find_library(LIBXSLT_EXSLT_LIBRARY NAMES exslt libexslt
#HINTS
#${PC_LIBXSLT_LIBDIR}
#${PC_LIBXSLT_LIBRARY_DIRS}
#)

#set(LIBXSLT_EXSLT_LIBRARIES ${LIBXSLT_EXSLT_LIBRARY} )

#find_program(LIBXSLT_XSLTPROC_EXECUTABLE xsltproc)

if(NOT LIBXSLT_LIBRARIES)
    message( "LibXslt: ${LIBXSLT_LIBRARIES}")

    # use pkg-config to get the directories and then use these values
    # in the find_path() and find_library() calls
    find_package(PkgConfig QUIET)
    PKG_CHECK_MODULES(PC_LIBXSLT QUIET libxslt)
    set(LIBXSLT_DEFINITIONS ${PC_LIBXSLT_CFLAGS_OTHER})

    find_path(LIBXSLT_INCLUDE_DIR NAMES libxslt/xslt.h
        HINTS
        ${PC_LIBXSLT_INCLUDEDIR}
        ${PC_LIBXSLT_INCLUDE_DIRS})

    find_library(LIBXSLT_LIBRARIES NAMES xslt libxslt
        HINTS
        ${PC_LIBXSLT_LIBDIR}
        ${PC_LIBXSLT_LIBRARY_DIRS})

    find_library(LIBXSLT_EXSLT_LIBRARY NAMES exslt libexslt
        HINTS
        ${PC_LIBXSLT_LIBDIR}
        ${PC_LIBXSLT_LIBRARY_DIRS}
     )


    set(LIBXSLT_EXSLT_LIBRARIES ${LIBXSLT_EXSLT_LIBRARY} )

    find_program(LIBXSLT_XSLTPROC_EXECUTABLE xsltproc)

    if(PC_LIBXSLT_VERSION)
        set(LIBXSLT_VERSION_STRING ${PC_LIBXSLT_VERSION})
    elseif(LIBXSLT_INCLUDE_DIR AND EXISTS "${LIBXSLT_INCLUDE_DIR}/libxslt/xsltconfig.h")
        file(STRINGS "${LIBXSLT_INCLUDE_DIR}/libxslt/xsltconfig.h" libxslt_version_str
            REGEX "^#define[\t ]+LIBXSLT_DOTTED_VERSION[\t ]+\".*\"")
        string(REGEX REPLACE "^#define[\t ]+LIBXSLT_DOTTED_VERSION[\t ]+\"([^\"]*)\".*" "\\1"
            LIBXSLT_VERSION_STRING "${libxslt_version_str}")
        unset(libxslt_version_str)
    endif()
endif(NOT LIBXSLT_LIBRARIES)

#include(${CMAKE_CURRENT_LIST_DIR}/FindPackageHandleStandardArgs.cmake)
include(${CMAKE_ROOT}/Modules/FindPackageHandleStandardArgs.cmake)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(LibXslt
                                  REQUIRED_VARS LIBXSLT_LIBRARIES LIBXSLT_INCLUDE_DIR
                                  VERSION_VAR LIBXSLT_VERSION_STRING)

mark_as_advanced(LIBXSLT_INCLUDE_DIR
                 LIBXSLT_LIBRARIES
                 LIBXSLT_EXSLT_LIBRARY
                 LIBXSLT_XSLTPROC_EXECUTABLE)



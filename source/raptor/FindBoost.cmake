#.rst:
# FindLIBBOOST
# --------
#
# Find boost
#
# Find the native LIBBOOST headers and libraries.
#
# ::
#
#   LIBBOOST_INCLUDE_DIR   - where to find boost/boost.h, etc.
#   LIBBOOST_LIBRARIES      - List of libraries when using boost.
#   LIBBOOST_FOUND          - True if boost found.
#   LIBBOOST_VERSION_STRING - the version of boost found (since CMake 2.8.8)

#=============================================================================
# Copyright 2006-2009 Kitware, Inc.
# Copyright 2012 Rolf Eike Beer <eike@sf-mail.de>
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

# Look for the header file in Homebrew directory
find_path(LIBBOOST_INCLUDE_DIR NAMES regex.hpp
    PATHS
    /usr/local/opt/boost/include/boost  # Homebrew
    ~/.linuxbrew/include/boost  # Linuxbrew
    /usr/include/boost  # Linux
    NO_DEFAULT_PATH )

mark_as_advanced(LIBBOOST_INCLUDE_DIR)

if(SBOL_BUILD_SHARED)
if(LIBBOOST_LIBRARY MATCHES "(.*).(a|lib)")
unset(LIBBOOST_LIBRARY CACHE)
endif()
else()
if(LIBBOOST_LIBRARY MATCHES "(.*).(so|dylib|dll)")
unset(LIBBOOST_LIBRARY CACHE)
endif()
endif()

# Look for the library (sorted from most current/relevant entry to least).
find_library(LIBBOOST_LIBRARY NAMES 
    boost_regex

    PATHS
    /usr/local/opt/boost/lib # Homebrew path
    ~/.linuxbrew/lib
    /usr/lib/i386-linux-gnu  #Linux 32
    /usr/lib/x86_64-linux-gnu #Linux 64
    NO_DEFAULT_PATH )

mark_as_advanced(LIBBOOST_LIBRARY)

if(LIBBOOST_INCLUDE_DIR)
  foreach(_boost_version_header regex.h)
    if(EXISTS "${LIBBOOST_INCLUDE_DIR}/boost/${_boost_version_header}")
      file(STRINGS "${LIBBOOST_INCLUDE_DIR}/boost/${_boost_version_header}" boost_version_str REGEX "^#define[\t ]+LIBLIBBOOST_VERSION[\t ]+\".*\"")

      string(REGEX REPLACE "^#define[\t ]+LIBLIBBOOST_VERSION[\t ]+\"([^\"]*)\".*" "\\1" LIBBOOST_VERSION_STRING "${boost_version_str}")
      unset(boost_version_str)
      break()
    endif()
  endforeach()
endif()

# handle the QUIETLY and REQUIRED arguments and set LIBBOOST_FOUND to TRUE if
# all listed variables are TRUE
include(${CMAKE_ROOT}/Modules/FindPackageHandleStandardArgs.cmake)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(LIBBOOST
                                  REQUIRED_VARS LIBBOOST_LIBRARY LIBBOOST_INCLUDE_DIR
                                  VERSION_VAR LIBBOOST_VERSION_STRING)

if(LIBBOOST_FOUND)
  set(LIBBOOST_LIBRARY ${LIBBOOST_LIBRARY})
  set(LIBBOOST_INCLUDE_DIR ${LIBBOOST_INCLUDE_DIR})
endif()

# Copyright (C) 2012 - 2013 by Pedro Mendes, Virginia Tech Intellectual
# Properties, Inc., University of Heidelberg, and The University
# of Manchester.
# All rights reserved.

# - Try to find the Rasqal RDF query library (http://librdf.org/rasqal)
# Once done this will define
#
#  RASQAL_FOUND       - system has Rasqal
#  RASQAL_LIBRARIES   - Link these to use Rasqal
#  RASQAL_INCLUDE_DIR - Include directory for using Rasqal
#  RASQAL_DEFINITIONS - Compiler switches required for using Rasqal
#

# (c) 2007-2011 Sebastian Trueg <trueg@kde.org>
# (c) 2011 Artem Serebriyskiy <v.for.vandal@gmail.com>
# (c) 2011 Michael Jansen <kde@michael-jansen.biz>
#
# Based on FindFontconfig Copyright (c) 2006,2007 Laurent Montel, <montel@kde.org>
#
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.


MACRO (FIND_RASQAL)

ENDMACRO ()

# Check if we have cached results in case the last round was successful.
if (NOT (RASQAL_INCLUDE_DIR AND RASQAL_LIBRARIES) OR NOT RASQAL_FOUND)

    set(RASQAL_LDFLAGS)

    find_path(RASQAL_INCLUDE_DIR rasqal.h
        PATHS $ENV{RASQAL_DIR}/include
              $ENV{RASQAL_DIR}
              ~/Library/Frameworks
              /Library/Frameworks
              /sw/include        # Fink
              /opt/local/include/rasqal # MacPorts
              /opt/csw/include   # Blastwave
              /opt/include
              /usr/freeware/include
              /usr/local/include/rasqal    # Homebrew
              $ENV{HOME}/.linuxbrew/include/rasqal  # linuxbrew
              $ENV{LINUXBREW}/include/rasqal
              /home/linuxbrew/.linuxbrew/include/rasqal
              /usr/include/rasqal
             NO_DEFAULT_PATH)

    find_path(RASQAL_INCLUDE_DIR rasqal.h)

    if(SBOL_BUILD_SHARED)
    if(RASQAL_LIBRARY MATCHES "(.*).(a|lib)")
    unset(RASQAL_LIBRARY CACHE)
    endif()
    else()
    if(RASQAL_LIBRARY MATCHES "(.*).(so|dylib|dll)")
    unset(RASQAL_LIBRARY CACHE)
    endif()
    endif()

    find_library(RASQAL_LIBRARY
        NAMES rasqal librasqal
        PATHS $ENV{RASQAL_DIR}/lib
              $ENV{RASQAL_DIR}/lib-dbg
              $ENV{RASQAL_DIR}
              ~/Library/Frameworks
              /Library/Frameworks
              /sw/lib        # Fink
              /opt/local/lib # MacPorts
              /opt/csw/lib   # Blastwave
              /opt/lib
              /usr/freeware/lib64
              /usr/local/lib # Homebrew
              /usr/local/opt/rasqal/lib # Homebrew
              ~/.linuxbrew/lib          # linuxbrew
              /usr/lib/i386-linux-gnu
              /usr/lib/x86_64-linux-gnu
             NO_DEFAULT_PATH)

    if (NOT RASQAL_LIBRARY)
    find_library(RASQAL_LIBRARY NAMES rasqal librasqal)
    endif ()
    ### Homebrew debugging output
    #message("Found Rasqal at ${RASQAL_LIBRARY}")
    #message("home: $ENV{LINUXBREW}")
    #message("user: $ENV{USER}")
    #file(GLOB_RECURSE include_files LIST_DIRECTORIES true $ENV{LINUXBREW}/include/*)
    #message("${include_files}")

    if (NOT WIN32)
        find_package(PkgConfig)
        pkg_check_modules(PC_RASQAL QUIET rasqal)

        if (PC_RASQAL_FOUND)
            set(RASQAL_DEFINITIONS ${PC_RASQAL_CFLAGS_OTHER})
            set(RASQAL_VERSION ${PC_RASQAL_VERSION} CACHE STRING "Rasqal Version found" )
            string( REGEX REPLACE "^.*-lrasqal;" "" RASQAL_LDFLAGS "${PC_RASQAL_STATIC_LDFLAGS}")
            string( REGEX REPLACE "-lexpat[;]*" "" RASQAL_LDFLAGS "${RASQAL_LDFLAGS}")
        endif (PC_RASQAL_FOUND)
    endif (NOT WIN32)

    if (RASQAL_LDFLAGS)
        set(RASQAL_LIBRARY ${RASQAL_LIBRARY} ${RASQAL_LDFLAGS})
    endif (RASQAL_LDFLAGS)

    mark_as_advanced(RASQAL_INCLUDE_DIR RASQAL_LIBRARY)

endif () # Check for cached values

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(
    Rasqal
    VERSION_VAR   RASQAL_VERSION
    REQUIRED_VARS RASQAL_LIBRARY RASQAL_INCLUDE_DIR)

mark_as_advanced(RASQAL_VERSION)

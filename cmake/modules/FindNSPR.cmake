# - FindNSPR.cmake
# This module checks for NSPR library.
#
# The following variables will be defined:
#
#   NSPR_FOUND - Was NSPR found?
#   NSPR_INCLUDE_DIRS - All include directories
#   NSPR_LIBRARIES - All libraries

#=============================================================================
# Copyright 2010 Guillaume Duhamel <guillaume.duhamel@gmail.com>
#
# Distributed under the OSI-approved BSD License (the "License");
# see accompanying file Copyright.txt for details.
#
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the License for more information.
#=============================================================================
find_package(PkgConfig)

if(PKG_CONFIG_FOUND)
    pkg_check_modules(_NSPR_PKG xulrunner-nspr)
endif()

find_path(NSPR_INCLUDE_DIR nspr.h PATHS ${_NSPR_PKG_INCLUDE_DIRS} "${XUL_SDK_DIR}/include/nspr")

find_library(_NSPR_PLDS4_LIBRARY plds4 PATHS ${_NSPR_PKG_LIBRARY_DIRS} "${XUL_SDK_DIR}/lib")
find_library(_NSPR_PLC4_LIBRARY plc4 PATHS ${_NSPR_PKG_LIBRARY_DIRS} "${XUL_SDK_DIR}/lib")
find_library(_NSPR_NSPR4_LIBRARY nspr4 PATHS ${_NSPR_PKG_LIBRARY_DIRS} "${XUL_SDK_DIR}/lib")

set(NSPR_FOUND false)

if(NSPR_INCLUDE_DIR AND _NSPR_PLDS4_LIBRARY AND _NSPR_PLC4_LIBRARY AND _NSPR_NSPR4_LIBRARY)
    set(NSPR_FOUND true)

    set(NSPR_LIBRARIES ${_NSPR_PLDS4_LIBRARY} ${_NSPR_PLC4_LIBRARY} ${_NSPR_NSPR4_LIBRARY})
    set(NSPR_INCLUDE_DIRS ${NSPR_INCLUDE_DIR})
    message(STATUS "Found NSPR")
elseif(NSPR_FIND_REQUIRED)
    message(FATAL_ERROR "NSPR not found")
endif()


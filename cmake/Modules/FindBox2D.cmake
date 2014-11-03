# Locate Box2D library
#
# This module defines the following variables:
# - BOX2D_LIBRARY
# - BOX2D_INCLUDE_DIR
# - BOX2D_FOUND
#
# It also set the following variables:
# - BOX2D_LIBRARY_RELEASE
# - BOX2D_LIBRARY_DEBUG
#
# Usage example:
#   find_package(Box2D REQUIRED)
#   include_directories(${BOX2D_INCLUDE_DIR})
#   target_link_libraries(MyProject ${BOX2D_LIBRARY})

#=============================================================================
# The MIT License (MIT)
#
# Copyright (c) 2014 Manuel Sabogal
#
# Permission is hereby granted, free of charge, to any person obtaining a copy of
# this software and associated documentation files (the "Software"), to deal in
# the Software without restriction, including without limitation the rights to
# use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
# the Software, and to permit persons to whom the Software is furnished to do so,
# subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
# FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
# COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
# IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
# CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#=============================================================================

# Find the Box2D include directory
find_path(BOX2D_INCLUDE_DIR Box2D/Box2D.h
    PATH_SUFFIXES include
    PATHS
        /usr/local/
        /usr/
        /sw          # Fink
        /opt/local/  # DarwinPorts
        /opt/csw/    # Blastwave
        /opt/
)

# Find the Box2D library
find_library(BOX2D_LIBRARY_RELEASE
    NAMES Box2D
    PATH_SUFFIXES lib64 lib
    PATHS
        /usr/local
        /usr
        /sw         # Fink
        /opt/local  # DarwinPorts
        /opt/csw    # Blastwave
        /opt
)

# Find the Box2D library
find_library(BOX2D_LIBRARY_DEBUG
    NAMES Box2D-d
    PATH_SUFFIXES lib64 lib
    PATHS
        /usr/local
        /usr
        /sw         # Fink
        /opt/local  # DarwinPorts
        /opt/csw    # Blastwave
        /opt
)

if(BOX2D_LIBRARY_DEBUG OR BOX2D_LIBRARY_RELEASE)
    if(BOX2D_LIBRARY_DEBUG AND BOX2D_LIBRARY_RELEASE)
        set(BOX2D_LIBRARY debug ${BOX2D_LIBRARY_DEBUG}
                          optimized ${BOX2D_LIBRARY_RELEASE})
    elseif(BOX2D_LIBRARY_DEBUG AND NOT BOX2D_LIBRARY_RELEASE)
        set(BOX2D_LIBRARY ${BOX2D_LIBRARY_DEBUG})
    elseif(BOX2D_LIBRARY_RELEASE AND NOT BOX2D_LIBRARY_DEBUG)
        set(BOX2D_LIBRARY ${BOX2D_LIBRARY_RELEASE})
    endif()
endif()

# handle the QUIETLY and REQUIRED arguments and set BOX2D_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(Box2D DEFAULT_MSG
                                  BOX2D_LIBRARY BOX2D_INCLUDE_DIR)

mark_as_advanced(BOX2D_LIBRARY_DEBUG BOX2D_LIBRARY_RELEASE
                 BOX2D_INCLUDE_DIR BOX2D_LIBRARY)
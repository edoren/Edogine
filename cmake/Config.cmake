# Configuration module that set some useful variables to detect OS, compiler
# and compiler architecture

# It defines the following variables:
# +===========================================================================+
# |       Variable       |      Values      |           Description           |
# +===========================================================================+
# |  OS                  |  Windows         |  Microsoft Windows              |
# |                      |  OSX             |  Mac OSX                        |
# |                      |  Linux           |  Linux OS                       |
# |                      |  FreeBSD         |  FreeBSD OS                     |
# +---------------------------------------------------------------------------+
# |  COMPILER            |  MSVC            |  Microsoft Visual C++           |
# |                      |  MinGW           |  MinGW compiler                 |
# |                      |  Clang           |  Clang compiler                 |
# |                      |  GCC             |  GNU Compiler Collection        |
# +---------------------------------------------------------------------------+
# |  COMPILER_ARCH       |  32              |  32 bits architecture           |
# |                      |  64              |  64 bits architecture           |
# +===========================================================================+

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

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    SET(OS "Windows")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    SET(OS "OSX")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    SET(OS "Linux")
elseif(CMAKE_SYSTEM_NAME STREQUAL "FreeBSD")
    SET(OS "FreeBSD")
else()
    message(FATAL_ERROR "Unsupported operating system.")
endif()

if(MSVC)
    set(COMPILER "MSVC")
    if(MSVC_VERSION EQUAL 1500)
        set(COMPILER_VERSION 9.0)  # Visual Studio 2008
    elseif(MSVC_VERSION EQUAL 1600)
        set(COMPILER_VERSION 10.0)  # Visual Studio 2010
    elseif(MSVC_VERSION EQUAL 1700)
        set(COMPILER_VERSION 11.0)  # Visual Studio 2012
    elseif(MSVC_VERSION EQUAL 1800)
        set(COMPILER_VERSION 12.0)  # Visual Studio 2013
    endif()
elseif(MINGW)
    set(COMPILER "MINGW")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(COMPILER "Clang")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(COMPILER "GCC")
else()
    message(FATAL_ERROR "Unsupported compiler.")
endif()

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(COMPILER_ARCH 64)
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
    set(COMPILER_ARCH 32)
else()
    message(FATAL_ERROR "Unsupported compiler architecture.")
endif()
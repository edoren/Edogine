# define cmake version
cmake_minimum_required(VERSION 2.8)

macro(set_option var default type docstring)
    if(NOT DEFINED ${var})
        set(${var} ${default})
    endif()
    set(${var} ${${var}} CACHE ${type} ${docstring} FORCE)
endmacro()

# Specify default build type if none provided (before project() command)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Limited configurations" FORCE)
mark_as_advanced(CMAKE_CONFIGURATION_TYPES)

# project name
project(EDOGINE)

# Predefined configuration options
set_option(EDOGINE_SHARED_LIB TRUE BOOL "Build shared libraries")
set_option(EDOGINE_BUILD_EXAMPLES FALSE BOOL "Build example projects")
# set_option(EDOGINE_BUILD_DOC FALSE BOOL "Create HTML documentation (requires Doxygen)")

# Include the config module
include(${PROJECT_SOURCE_DIR}/cmake/Config.cmake)

# set CMAKE_MODULE_PATH
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/Modules)

# Enable the folders in the projects
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMake")

# If compiler is GNU GCC based it enable the warnings
if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions("-Wall")
endif()

# Compiler language
if(${COMPILER} STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "-std=c++0x -stdlib=libc++")
elseif(${COMPILER} STREQUAL "GCC")
    set(CMAKE_CXX_FLAGS "-std=c++0x")
endif()

# Set the static macro for static library
if(NOT EDOGINE_SHARED_LIB)
    add_definitions(-DEDOGINE_STATIC)
endif()

add_subdirectory(${PROJECT_SOURCE_DIR}/src)

if(EDOGINE_BUILD_EXAMPLES)
    add_subdirectory(${PROJECT_SOURCE_DIR}/examples)
endif()
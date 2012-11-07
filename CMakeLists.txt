# Copyright (C) by Josh Blum. See LICENSE.txt for licensing information.

########################################################################
# Project setup
########################################################################
cmake_minimum_required(VERSION 2.6)
project(Apology CXX)
enable_testing()

#select the release build type by default to get optimization flags
if(NOT CMAKE_BUILD_TYPE)
   set(CMAKE_BUILD_TYPE "Release")
   message(STATUS "Build type not specified: defaulting to release.")
endif(NOT CMAKE_BUILD_TYPE)
set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING "")

if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-Wall)
endif()

add_definitions(-DAPOLOGY_DLL=1) #this test project builds a dll

########################################################################
# Setup Theron Deps
########################################################################
set(THERON_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Theron)
include(${THERON_SOURCE_DIR}/TheronSetup.cmake)
include_directories(${THERON_INCLUDE_DIRS})
link_directories(${THERON_LIBRARY_DIRS})
add_definitions(${THERON_DEFINES})

########################################################################
# Local Include Dir
########################################################################
include_directories(${CMAKE_SOURCE_DIR}/include)

########################################################################
# Do subdirectories
########################################################################
add_subdirectory(Theron)
add_subdirectory(lib)
add_subdirectory(tests)

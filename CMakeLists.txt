#
# Copyright 2011-2012 Josh Blum
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

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

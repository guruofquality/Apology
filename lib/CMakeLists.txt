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
# Compiler specific setup
########################################################################
if(CMAKE_COMPILER_IS_GNUCXX AND NOT WIN32)
    #http://gcc.gnu.org/wiki/Visibility
    add_definitions(-fvisibility=hidden)
    add_definitions(-fvisibility-inlines-hidden)
endif()

if(CMAKE_COMPILER_IS_GNUCXX AND "${CMAKE_SYSTEM_PROCESSOR}" STREQUAL "x86_64")
    add_definitions("-fPIC")
endif()

if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-Wall)
endif()

########################################################################
# Setup Theron
########################################################################
include_directories(${CMAKE_SOURCE_DIR}/Theron/Include)
include_directories(${CMAKE_SOURCE_DIR}/Theron/Include/External)

if(MSVC)
    include_directories(${CMAKE_SOURCE_DIR}/Theron/Include/External/Standard)
endif(MSVC)

if (NOT WIN32) #not on windows? tell theron headers to use boost
    add_definitions(-DTHERON_USE_BOOST_THREADS)
endif()

file(GLOB theron_sources
    "${CMAKE_SOURCE_DIR}/Theron/Theron/*.cpp"
    "${CMAKE_SOURCE_DIR}/Theron/Source/*.cpp"
)

########################################################################
# Check for support
########################################################################
if(NOT Boost_FOUND)
    message(FATAL_ERROR "no boost found!")
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

########################################################################
# The sources
########################################################################
list(APPEND libapology_sources
    Worker.cpp
    ${theron_sources}
)

list(APPEND libapology_libs
    ${Boost_LIBRARIES}
)

########################################################################
# Build the library
########################################################################
add_library(apology STATIC ${libapology_sources})
target_link_libraries(apology ${libapology_libs})
#uncomment for SHARED library
#set_target_properties(apology PROPERTIES DEFINE_SYMBOL "APOLOGY_DLL_EXPORTS")
#set_target_properties(apology PROPERTIES COMPILE_DEFINITIONS "APOLOGY_DLL=1")

########################################################################
# Install the library
########################################################################
install(TARGETS apology
    LIBRARY DESTINATION lib/${LIB_SUFFIX} COMPONENT "devel" # .so file
    ARCHIVE DESTINATION lib/${LIB_SUFFIX} COMPONENT "runtime" # .lib file
    RUNTIME DESTINATION bin COMPONENT "runtime" # .dll file
)

# Copyright (C) by Josh Blum. See LICENSE.txt for licensing information.

########################################################################
# Compiler specific setup
########################################################################
if(CMAKE_COMPILER_IS_GNUCXX AND NOT WIN32)
    #http://gcc.gnu.org/wiki/Visibility
    #add_definitions(-fvisibility=hidden)
    #add_definitions(-fvisibility-inlines-hidden)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

########################################################################
# The sources
########################################################################
list(APPEND libapology_sources
    Worker.cpp
    Topology.cpp
    Executor.cpp
    Port.cpp
    Flow.cpp
)

########################################################################
# Build the library
########################################################################
add_library(apology SHARED ${libapology_sources})
target_link_libraries(apology ${THERON_LIBRARIES} theron)
set_target_properties(apology PROPERTIES DEFINE_SYMBOL "APOLOGY_DLL_EXPORTS")

########################################################################
# Install the library
########################################################################
install(TARGETS apology
    LIBRARY DESTINATION lib/${LIB_SUFFIX} COMPONENT "devel" # .so file
    ARCHIVE DESTINATION lib/${LIB_SUFFIX} COMPONENT "runtime" # .lib file
    RUNTIME DESTINATION bin COMPONENT "runtime" # .dll file
)

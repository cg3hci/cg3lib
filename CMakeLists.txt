#
# This file is part of cg3lib: https://github.com/cg3hci/cg3lib
# This Source Code Form is subject to the terms of the GNU GPL 3.0
#
# @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
# @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
#

cmake_minimum_required(VERSION 3.9)
project(cg3lib)

## Build options ##

option(CG3_STATIC "Build cg3lib statically. All the selected modules will be built first, and then linked." ON)
option(CG3_VIEWER_STATIC "Build just what is necessary to be built in the viewer, leaving the rest of the library header only." OFF)

option(CG3_BUILD_EXAMPLES "" OFF)

option(CG3_CGAL "Enable the CGAL module (requires CGAL)" OFF)
option(CG3_CINOLIB "Enable the CinoLib module (requires CinoLib)" OFF)
option(CG3_LIBIGL "Enable the LibIGL module (requires LibIGL)" OFF)
option(CG3_VCGLIB "Enable the VCGLib module (requires VCGLib)" OFF)
option(CG3_VORO++ "Enable the Voro++ module (requires Voro++)" OFF) # todo
option(CG3_VIEWER "Enable the Viewer module (requires QGLViewer)" OFF)
option(CG3_DEVELOPEMENT "" OFF)

add_definitions(-DCG3_QMAKE) #todo: remove this

if (CG3_STATIC)
	set(CG3_TARGET_MOD PUBLIC)
	message(STATUS "Using static build cg3lib")
else()
	if (CG3_VIEWER_STATIC)
		message(STATUS "Using header only cg3lib with static viewer module")
	else()
		message(STATUS "Using header only cg3lib")
	endif()
	set(CG3_TARGET_MOD INTERFACE)
endif()

#this variable will contain all the linkable target modules that will be built
set(CG3_LINK_LIBRARIES "")

#this variable will contain all the macros defined by the built modules
set(CG3_MODULE_DEFINITIONS "")

set(CG3_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

include(${CMAKE_CURRENT_SOURCE_DIR}/external/external.cmake)

include(${CMAKE_CURRENT_SOURCE_DIR}/cg3/core.cmake)

if (CG3_CGAL AND TARGET CGAL::CGAL)
	include(${CMAKE_CURRENT_SOURCE_DIR}/cg3/cgal.cmake)
endif()

if (CG3_CINOLIB)
	include(${CMAKE_CURRENT_SOURCE_DIR}/cg3/cinolib.cmake)
endif()

if (CG3_LIBIGL)
	include(${CMAKE_CURRENT_SOURCE_DIR}/cg3/libigl.cmake)
endif()

if (CG3_VCGLIB)
	include(${CMAKE_CURRENT_SOURCE_DIR}/cg3/vcglib.cmake)
endif()

if (CG3_VORO++)
	include(${CMAKE_CURRENT_SOURCE_DIR}/cg3/voro++.cmake)
endif()

if (CG3_VIEWER)
	include(${CMAKE_CURRENT_SOURCE_DIR}/cg3/viewer.cmake)
endif()

if (CG3_DEVELOPEMENT)
	#include(${CMAKE_CURRENT_SOURCE_DIR}/cg3/libigl.cmake)
endif()

# this cmake script will associate all the macros needed to all the built modules
include(${CMAKE_CURRENT_SOURCE_DIR}/cg3/post.cmake)

add_library(cg3lib INTERFACE)
target_link_libraries(cg3lib INTERFACE ${CG3_LINK_LIBRARIES})
target_include_directories(cg3lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_compile_definitions(cg3lib INTERFACE ${CG3_MODULE_DEFINITIONS})

if (CG3_BUILD_EXAMPLES)
	add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/examples)
endif()

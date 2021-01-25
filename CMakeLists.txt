#
# This file is part of cg3lib: https://github.com/cg3hci/cg3lib
# This Source Code Form is subject to the terms of the GNU GPL 3.0
#
# @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
# @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
#

cmake_minimum_required(VERSION 3.9)
project(cg3lib)

option(CG3_STATIC "Build cg3lib statically. All the selected modules will be built first, and then linked." OFF)
option(CG3_VIEWER_STATIC "Build just what is necessary to be built in the viewer, leaving the rest of the library header only." ON)

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

add_definitions(-DCG3_QMAKE) #todo: remove this

option(CG3_DATA_STRUCTURES "Enable the data structures module" ON)
option(CG3_MESHES "Enable the meshes module" ON)
option(CG3_ALGORITHMS "Enable the algorithms module" ON)
option(CG3_CGAL "Enable the CGAL module (requires CGAL)" ON)
option(CG3_CINOLIB "Enable the CinoLib module (requires CinoLib)" ON)
option(CG3_LIBIGL "Enable the LibIGL module (requires LibIGL)" ON)
option(CG3_VCGLIB "Enable the VCGLib module (requires VCGLib)" ON)
option(CG3_VORO++ "Enable the Voro++ module (requires Voro++)" ON)
option(CG3_VIEWER "Enable the Viewer module (requires QGLViewer)" ON)
option(CG3_DEVELOPEMENT "" OFF)

#this variable will contain all the linkable target modules that will be built
set(CG3_LINK_LIBRARIES "")

#this variable will contain all the macros defined by the built modules
set(CG3_MODULE_DEFINITIONS "")

set(CG3_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

include(${CMAKE_CURRENT_SOURCE_DIR}/external/external.cmake)

include(${CMAKE_CURRENT_SOURCE_DIR}/cg3/core.cmake)

if (CG3_DATA_STRUCTURES)
	include(${CMAKE_CURRENT_SOURCE_DIR}/cg3/data_structures.cmake)
endif()

if (CG3_MESHES)
	include(${CMAKE_CURRENT_SOURCE_DIR}/cg3/meshes.cmake)
endif()

if (CG3_ALGORITHMS)
	include(${CMAKE_CURRENT_SOURCE_DIR}/cg3/algorithms.cmake)
endif()

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

#set(CG3_LINK_LIBRARIES ${CG3_LINK_LIBRARIES} PARENT_SCOPE)

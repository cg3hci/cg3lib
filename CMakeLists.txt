#
# This file is part of cg3lib: https://github.com/cg3hci/cg3lib
# This Source Code Form is subject to the terms of the GNU GPL 3.0
#
# @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
# @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
#

cmake_minimum_required(VERSION 3.9)
project(cg3lib)

option(CG3_STATIC "" ON)

if (CG3_STATIC)
	add_definitions(-DCG3_STATIC)
	add_definitions(-DCG3_QMAKE) #todo: reomve this
endif()

option(CG3_CORE "" ON)
option(CG3_DATA_STRUCTURES "" ON)
option(CG3_MESHES "" ON)
option(CG3_ALGORITHMS "" ON)
option(CG3_CGAL "" ON)
option(CG3_CINOLIB "" ON)
option(CG3_LIBIGL "" ON)
option(CG3_VCGLIB "" ON)
option(CG3_VORO++ "" ON)
option(CG3_VIEWER "" ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

include(${CMAKE_CURRENT_SOURCE_DIR}/external/external.cmake)

if (CG3_CORE)
	include(${CMAKE_CURRENT_SOURCE_DIR}/cg3/core.cmake)
endif()

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

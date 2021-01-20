#
# This file is part of cg3lib: https://github.com/cg3hci/cg3lib
# This Source Code Form is subject to the terms of the GNU GPL 3.0
#
# @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
# @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
#

set(CMAKE_CXX_STANDARD 14)

option(CG3_STATIC "" ON)

if (CG3_STATIC)
	add_definitions(-DCG3_STATIC)
	add_definitions(-DCG3_QMAKE) #todo: remove this
endif()

include(${CMAKE_CURRENT_LIST_DIR}/external/external.cmake)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/cg3)
include_directories(${CMAKE_CURRENT_LIST_DIR})

if (TARGET cg3-viewer)
	set(CMAKE_AUTOMOC ON)
	set(CMAKE_AUTOUIC ON)
	set(CMAKE_AUTORCC ON)
endif()

if (CG3_CORE)
	add_definitions(-DCG3_CORE_DEFINED)
endif()

if(CG3_DATA_STRUCTURES)
	add_definitions(-DCG3_DATA_STRUCTURES_DEFINED)
endif()

if(CG3_MESHES)
	add_definitions(-DCG3_DCEL_DEFINED)
	add_definitions(-DCG3_EIGENMESH_DEFINED)
endif()

if(CG3_ALGORITHMS)
	add_definitions(-DCG3_ALGORITHMS_DEFINED)
endif()

if(CG3_CGAL)
	add_definitions(-DCG3_CGAL_DEFINED)
endif()

if(CG3_CINOLIB)
	add_definitions(-DCG3_CINOLIB_DEFINED)
endif()

if(CG3_LIBIGL)
	add_definitions(-DCG3_LIBIGL_DEFINED)
endif()

if(CG3_VCGLIB)
	add_definitions(-DCG3_VCGLIB_DEFINED)
endif()

if(CG3_VORO++)
	add_definitions(-DCG3_VOROPLUSPLUS_DEFINED)
endif()

if(CG3_VIEWER)
	add_definitions(-DCG3_VIEWER_DEFINED)
endif()


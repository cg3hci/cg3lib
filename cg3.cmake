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

add_definitions(-DCG3_ALGORITHMS_DEFINED)

add_definitions(-DCG3_LIBIGL_DEFINED)
add_definitions(-DCG3_EIGENMESH_DEFINED)
add_definitions(-DCG3_CGAL_DEFINED)
add_definitions(-DCG3_CINOLIB_DEFINED)
add_definitions(-DCG3_CORE_DEFINED)
add_definitions(-DCG3_DATA_STRUCTURES_DEFINED)
add_definitions(-DCG3_DCEL_DEFINED)
add_definitions(-DCG3_VCGLIB_DEFINED)
add_definitions(-DCG3_VIEWER_DEFINED)




#
# This file is part of cg3lib: https://github.com/cg3hci/cg3lib
# This Source Code Form is subject to the terms of the GNU GPL 3.0
#
# @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
# @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
#

if (CG3_STATIC)
	list(APPEND CG3_MODULE_DEFINITIONS CG3_VCGLIB_DEFINED)

	set(CG3_VCGLIB_HEADERS
		${CMAKE_CURRENT_LIST_DIR}/vcglib/convert.h
		${CMAKE_CURRENT_LIST_DIR}/vcglib/convert.inl
		${CMAKE_CURRENT_LIST_DIR}/vcglib/curve_on_manifold.h
		${CMAKE_CURRENT_LIST_DIR}/vcglib/curve_on_manifold.inl
		${CMAKE_CURRENT_LIST_DIR}/vcglib/meshes/triangleedgemeshtype.h 
		${CMAKE_CURRENT_LIST_DIR}/vcglib/smoothing.h
		${CMAKE_CURRENT_LIST_DIR}/vcglib/smoothing.inl
		${CMAKE_CURRENT_LIST_DIR}/vcglib/meshes/polygonmeshtype.h 
		${CMAKE_CURRENT_LIST_DIR}/vcglib/meshes/trianglemeshtype.h)
	
	#used just for visualization of the module in IDEs
	set(CG3_VCGLIB_SOURCES
		${CMAKE_CURRENT_LIST_DIR}/vcglib/dummy_source.cpp)

	add_library(
		cg3-vcglib SHARED
		${CG3_VCGLIB_HEADERS} ${CG3_VCGLIB_SOURCES})
	
	list(APPEND CG3_LINK_LIBRARIES cg3-vcglib)
endif()

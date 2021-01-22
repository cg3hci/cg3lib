#
# This file is part of cg3lib: https://github.com/cg3hci/cg3lib
# This Source Code Form is subject to the terms of the GNU GPL 3.0
#
# @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
# @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
#


list(APPEND CG3_MODULE_DEFINITIONS CG3_CINOLIB_DEFINED)

set(CG3_CINOLIB_HEADERS
	${CMAKE_CURRENT_LIST_DIR}/cinolib/cinolib_mesh_conversions.h)

set(CG3_CINOLIB_SOURCES
	${CMAKE_CURRENT_LIST_DIR}/cinolib/cinolib_mesh_conversions.cpp)

if (CG3_STATIC)
	add_library(
		cg3-cinolib SHARED 
		${CG3_CINOLIB_HEADERS} ${CG3_CINOLIB_SOURCES})
else()
	add_library(cg3-cinolib INTERFACE)
endif()

target_include_directories(cg3-cinolib ${CG3_TARGET_MOD} ${CG3_INCLUDE_DIR})

target_link_libraries(
	cg3-cinolib
	${CG3_TARGET_MOD}
		cinolib
		cg3-core)

list(APPEND CG3_LINK_LIBRARIES cg3-cinolib)


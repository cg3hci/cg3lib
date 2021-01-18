#
# This file is part of cg3lib: https://github.com/cg3hci/cg3lib
# This Source Code Form is subject to the terms of the GNU GPL 3.0
#
# @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
# @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
#
if (CG3_STATIC)
	SET(CG3_DATA_STRUCTURES_HEADERS
		${CMAKE_CURRENT_LIST_DIR}/data_structures/arrays/array_.h #arrays
		${CMAKE_CURRENT_LIST_DIR}/data_structures/arrays/arrays.h
		${CMAKE_CURRENT_LIST_DIR}/data_structures/arrays/array2d.h
		${CMAKE_CURRENT_LIST_DIR}/data_structures/arrays/array3d.h
		${CMAKE_CURRENT_LIST_DIR}/data_structures/arrays/array4d.h
		${CMAKE_CURRENT_LIST_DIR}/data_structures/arrays/array_bool.h)
	
	SET(CG3_DATA_STRUCTURES_SOURCES
		${CMAKE_CURRENT_LIST_DIR}/data_structures/arrays/array_.cpp #arrays
		${CMAKE_CURRENT_LIST_DIR}/data_structures/arrays/array2d.cpp
		${CMAKE_CURRENT_LIST_DIR}/data_structures/arrays/array3d.cpp
		${CMAKE_CURRENT_LIST_DIR}/data_structures/arrays/array4d.cpp
		${CMAKE_CURRENT_LIST_DIR}/data_structures/arrays/array_bool.cpp)
	
	add_library(
		cg3-data-structures SHARED 
		${CG3_DATA_STRUCTURES_HEADERS} ${CG3_DATA_STRUCTURES_SOURCES})
	
	target_link_libraries(cg3-data-structures PUBLIC cg3-core)
endif()

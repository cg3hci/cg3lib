#
# This file is part of cg3lib: https://github.com/cg3hci/cg3lib
# This Source Code Form is subject to the terms of the GNU GPL 3.0
#
# @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
# @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
#

if (CG3_STATIC)
	list(APPEND CG3_MODULE_DEFINITIONS CG3_ALGORITHMS_DEFINED)
	
	set(CG3_ALGORITHMS_HEADERS
		${CMAKE_CURRENT_LIST_DIR}/algorithms/convex_hull2.h 
		${CMAKE_CURRENT_LIST_DIR}/algorithms/convex_hull2.inl
		${CMAKE_CURRENT_LIST_DIR}/algorithms/convex_hull2_incremental.h
		${CMAKE_CURRENT_LIST_DIR}/algorithms/convex_hull2_incremental.inl
		${CMAKE_CURRENT_LIST_DIR}/algorithms/convex_hull3.h
		${CMAKE_CURRENT_LIST_DIR}/algorithms/convex_hull3.inl
		${CMAKE_CURRENT_LIST_DIR}/algorithms/graph_algorithms.h 
		${CMAKE_CURRENT_LIST_DIR}/algorithms/graph_algorithms.inl
		${CMAKE_CURRENT_LIST_DIR}/algorithms/laplacian_smoothing.h 
		${CMAKE_CURRENT_LIST_DIR}/algorithms/marching_cubes.h 
		${CMAKE_CURRENT_LIST_DIR}/algorithms/mesh_function_smoothing.h 
		${CMAKE_CURRENT_LIST_DIR}/algorithms/mesh_function_smoothing.inl
		${CMAKE_CURRENT_LIST_DIR}/algorithms/normalization.h 
		${CMAKE_CURRENT_LIST_DIR}/algorithms/saliency.h 
		${CMAKE_CURRENT_LIST_DIR}/algorithms/sphere_coverage.h
		${CMAKE_CURRENT_LIST_DIR}/algorithms/sphere_coverage.inl
		${CMAKE_CURRENT_LIST_DIR}/algorithms/global_optimal_rotation_matrix.h)
	
	set(CG3_ALGORITHMS_SOURCES
		${CMAKE_CURRENT_LIST_DIR}/algorithms/global_optimal_rotation_matrix.cpp  
		${CMAKE_CURRENT_LIST_DIR}/algorithms/marching_cubes.cpp  
		${CMAKE_CURRENT_LIST_DIR}/algorithms/normalization.cpp 
		${CMAKE_CURRENT_LIST_DIR}/algorithms/saliency.cpp 
		${CMAKE_CURRENT_LIST_DIR}/algorithms/laplacian_smoothing.cpp)
	
	add_library(
		cg3-algorithms SHARED 
		${CG3_ALGORITHMS_HEADERS} ${CG3_ALGORITHMS_SOURCES})
	
	target_link_libraries(
		cg3-algorithms
		PUBLIC 
			cg3-core)
		
	list(APPEND CG3_LINK_LIBRARIES cg3-algorithms)
endif()

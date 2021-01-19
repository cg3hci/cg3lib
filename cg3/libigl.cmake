if (CG3_STATIC)
	add_definitions(-DCG3_LIBIGL_DEFINED)

	SET(CG3_LIBIGL_HEADERS
		${CMAKE_CURRENT_LIST_DIR}/libigl/libigl.h 
		${CMAKE_CURRENT_LIST_DIR}/libigl/booleans.h 
		${CMAKE_CURRENT_LIST_DIR}/libigl/connected_components.h 
		${CMAKE_CURRENT_LIST_DIR}/libigl/curvature.h 
		${CMAKE_CURRENT_LIST_DIR}/libigl/decimate.h 
		${CMAKE_CURRENT_LIST_DIR}/libigl/extract_manifold_patches.h 
		${CMAKE_CURRENT_LIST_DIR}/libigl/geodesics.h 
		${CMAKE_CURRENT_LIST_DIR}/libigl/is_edge_manifold.h 
		${CMAKE_CURRENT_LIST_DIR}/libigl/is_vertex_manifold.h 
		${CMAKE_CURRENT_LIST_DIR}/libigl/mesh_adjacencies.h 
		${CMAKE_CURRENT_LIST_DIR}/libigl/mesh_distance.h 
		${CMAKE_CURRENT_LIST_DIR}/libigl/remove_duplicate_vertices.h 
		${CMAKE_CURRENT_LIST_DIR}/libigl/remove_unreferenced_vertices.h 
		${CMAKE_CURRENT_LIST_DIR}/libigl/internal/booleans_algorithms.h 
		${CMAKE_CURRENT_LIST_DIR}/libigl/internal/eigenmesh_libigl_algorithms.h)

	SET(CG3_LIBIGL_SOURCES
		${CMAKE_CURRENT_LIST_DIR}/libigl/internal/booleans_algorithms.cpp 
		${CMAKE_CURRENT_LIST_DIR}/libigl/internal/eigenmesh_libigl_algorithms_booleans.cpp 
		${CMAKE_CURRENT_LIST_DIR}/libigl/internal/eigenmesh_libigl_algorithms_adjacencies.cpp 
		${CMAKE_CURRENT_LIST_DIR}/libigl/internal/eigenmesh_libigl_algorithms_curvature.cpp 
		${CMAKE_CURRENT_LIST_DIR}/libigl/internal/eigenmesh_libigl_algorithms_decimation.cpp 
		${CMAKE_CURRENT_LIST_DIR}/libigl/internal/eigenmesh_libigl_algorithms_distances.cpp 
		${CMAKE_CURRENT_LIST_DIR}/libigl/internal/eigenmesh_libigl_algorithms_geodesics.cpp 
		${CMAKE_CURRENT_LIST_DIR}/libigl/internal/eigenmesh_libigl_algorithms_manifoldutilities.cpp 
		${CMAKE_CURRENT_LIST_DIR}/libigl/internal/eigenmesh_libigl_algorithms_verticesremoval.cpp 
		${CMAKE_CURRENT_LIST_DIR}/libigl/booleans.cpp 
		${CMAKE_CURRENT_LIST_DIR}/libigl/connected_components.cpp 
		${CMAKE_CURRENT_LIST_DIR}/libigl/curvature.cpp 
		${CMAKE_CURRENT_LIST_DIR}/libigl/decimate.cpp 
		${CMAKE_CURRENT_LIST_DIR}/libigl/extract_manifold_patches.cpp 
		${CMAKE_CURRENT_LIST_DIR}/libigl/geodesics.cpp 
		${CMAKE_CURRENT_LIST_DIR}/libigl/is_edge_manifold.cpp 
		${CMAKE_CURRENT_LIST_DIR}/libigl/is_vertex_manifold.cpp 
		${CMAKE_CURRENT_LIST_DIR}/libigl/mesh_adjacencies.cpp 
		${CMAKE_CURRENT_LIST_DIR}/libigl/mesh_distance.cpp 
		${CMAKE_CURRENT_LIST_DIR}/libigl/remove_duplicate_vertices.cpp 
		${CMAKE_CURRENT_LIST_DIR}/libigl/remove_unreferenced_vertices.cpp)
	
	add_library(
		cg3-libigl SHARED
		${CG3_LIBIGL_HEADERS} ${CG3_LIBIGL_SOURCES})

	target_link_libraries(
		cg3-libigl
		PUBLIC
			cg3-core cg3-data-structures cg3-meshes)
endif()

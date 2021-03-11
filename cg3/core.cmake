#
# This file is part of cg3lib: https://github.com/cg3hci/cg3lib
# This Source Code Form is subject to the terms of the GNU GPL 3.0
#
# @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
# @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
#

## module definitions
list(APPEND CG3_MODULE_DEFINITIONS CG3_CORE_DEFINED) # this should be mandatory

set(CG3_CORE_HEADERS
	#core
	${CMAKE_CURRENT_LIST_DIR}/cg3lib.h

	#geometry
	${CMAKE_CURRENT_LIST_DIR}/geometry/bounding_box2.h
	${CMAKE_CURRENT_LIST_DIR}/geometry/bounding_box3.h
	${CMAKE_CURRENT_LIST_DIR}/geometry/cylinder.h
	${CMAKE_CURRENT_LIST_DIR}/geometry/intersections2.h
	${CMAKE_CURRENT_LIST_DIR}/geometry/line2.h
	${CMAKE_CURRENT_LIST_DIR}/geometry/line3.h
	${CMAKE_CURRENT_LIST_DIR}/geometry/plane.h
	${CMAKE_CURRENT_LIST_DIR}/geometry/point2.h
	${CMAKE_CURRENT_LIST_DIR}/geometry/point2.inl
	${CMAKE_CURRENT_LIST_DIR}/geometry/point3.h
	${CMAKE_CURRENT_LIST_DIR}/geometry/point3.inl
	${CMAKE_CURRENT_LIST_DIR}/geometry/polygon2.h
	${CMAKE_CURRENT_LIST_DIR}/geometry/quaternion.h
	${CMAKE_CURRENT_LIST_DIR}/geometry/segment.h
	${CMAKE_CURRENT_LIST_DIR}/geometry/segment.inl
	${CMAKE_CURRENT_LIST_DIR}/geometry/segment2.h
	${CMAKE_CURRENT_LIST_DIR}/geometry/segment3.h
	${CMAKE_CURRENT_LIST_DIR}/geometry/sphere.h
	${CMAKE_CURRENT_LIST_DIR}/geometry/transformations3.h
	${CMAKE_CURRENT_LIST_DIR}/geometry/triangle.h
	${CMAKE_CURRENT_LIST_DIR}/geometry/triangle.inl
	${CMAKE_CURRENT_LIST_DIR}/geometry/triangle2.h
	${CMAKE_CURRENT_LIST_DIR}/geometry/triangle2_utils.h
	${CMAKE_CURRENT_LIST_DIR}/geometry/triangle2_utils.inl
	${CMAKE_CURRENT_LIST_DIR}/geometry/triangle3.h
	${CMAKE_CURRENT_LIST_DIR}/geometry/utils2.h
	${CMAKE_CURRENT_LIST_DIR}/geometry/utils2.inl
	${CMAKE_CURRENT_LIST_DIR}/geometry/utils3.h
	${CMAKE_CURRENT_LIST_DIR}/geometry/utils3.inl

	#io
	${CMAKE_CURRENT_LIST_DIR}/io/file_commons.h
	${CMAKE_CURRENT_LIST_DIR}/io/load_save_obj.h
	${CMAKE_CURRENT_LIST_DIR}/io/load_save_obj.inl
	${CMAKE_CURRENT_LIST_DIR}/io/load_save_ply.h
	${CMAKE_CURRENT_LIST_DIR}/io/load_save_ply.inl
	${CMAKE_CURRENT_LIST_DIR}/io/load_save_file.h
	${CMAKE_CURRENT_LIST_DIR}/io/serializable_object.h
	${CMAKE_CURRENT_LIST_DIR}/io/serialize.h
	${CMAKE_CURRENT_LIST_DIR}/io/serialize.inl
	${CMAKE_CURRENT_LIST_DIR}/io/serialize_eigen.h
	${CMAKE_CURRENT_LIST_DIR}/io/serialize_eigen.inl
	${CMAKE_CURRENT_LIST_DIR}/io/serialize_qt.h
	${CMAKE_CURRENT_LIST_DIR}/io/serialize_qt.inl
	${CMAKE_CURRENT_LIST_DIR}/io/serialize_std.h
	${CMAKE_CURRENT_LIST_DIR}/io/serialize_std.inl
	${CMAKE_CURRENT_LIST_DIR}/io/ply/ply.h
	${CMAKE_CURRENT_LIST_DIR}/io/ply/ply.inl
	${CMAKE_CURRENT_LIST_DIR}/io/ply/ply_header.h
	${CMAKE_CURRENT_LIST_DIR}/io/ply/ply_edge.h
	${CMAKE_CURRENT_LIST_DIR}/io/ply/ply_edge.inl
	${CMAKE_CURRENT_LIST_DIR}/io/ply/ply_face.h
	${CMAKE_CURRENT_LIST_DIR}/io/ply/ply_face.inl
	${CMAKE_CURRENT_LIST_DIR}/io/ply/ply_vertex.h
	${CMAKE_CURRENT_LIST_DIR}/io/ply/ply_vertex.inl

	#utilities
	${CMAKE_CURRENT_LIST_DIR}/utilities/cg3_config_folder.h
	${CMAKE_CURRENT_LIST_DIR}/utilities/color.h
	${CMAKE_CURRENT_LIST_DIR}/utilities/command_line_argument_manager.h
	${CMAKE_CURRENT_LIST_DIR}/utilities/command_line_argument_manager.inl
	${CMAKE_CURRENT_LIST_DIR}/utilities/comparators.h
	${CMAKE_CURRENT_LIST_DIR}/utilities/const.h
	${CMAKE_CURRENT_LIST_DIR}/utilities/eigen.h
	${CMAKE_CURRENT_LIST_DIR}/utilities/eigen.inl
	${CMAKE_CURRENT_LIST_DIR}/utilities/hash.h
	${CMAKE_CURRENT_LIST_DIR}/utilities/hash.inl
	${CMAKE_CURRENT_LIST_DIR}/utilities/map.h
	${CMAKE_CURRENT_LIST_DIR}/utilities/map.inl
	${CMAKE_CURRENT_LIST_DIR}/utilities/nested_initializer_lists.h
	${CMAKE_CURRENT_LIST_DIR}/utilities/nested_initializer_lists.inl
	${CMAKE_CURRENT_LIST_DIR}/utilities/pair.h
	${CMAKE_CURRENT_LIST_DIR}/utilities/pair.inl
	${CMAKE_CURRENT_LIST_DIR}/utilities/set.h
	${CMAKE_CURRENT_LIST_DIR}/utilities/set.inl
	${CMAKE_CURRENT_LIST_DIR}/utilities/string.h
	${CMAKE_CURRENT_LIST_DIR}/utilities/string.inl
	${CMAKE_CURRENT_LIST_DIR}/utilities/system.h
	${CMAKE_CURRENT_LIST_DIR}/utilities/system.inl
	${CMAKE_CURRENT_LIST_DIR}/utilities/timer.h
	${CMAKE_CURRENT_LIST_DIR}/utilities/timer.inl
	${CMAKE_CURRENT_LIST_DIR}/utilities/tokenizer.h
	${CMAKE_CURRENT_LIST_DIR}/utilities/tokenizer.inl
	${CMAKE_CURRENT_LIST_DIR}/utilities/vector.h
	${CMAKE_CURRENT_LIST_DIR}/utilities/vector.inl
	${CMAKE_CURRENT_LIST_DIR}/utilities/utils.h
	${CMAKE_CURRENT_LIST_DIR}/utilities/utils.inl

	#arrays
	${CMAKE_CURRENT_LIST_DIR}/data_structures/arrays/array_.h
	${CMAKE_CURRENT_LIST_DIR}/data_structures/arrays/array_.inl
	${CMAKE_CURRENT_LIST_DIR}/data_structures/arrays/arrays.h
	${CMAKE_CURRENT_LIST_DIR}/data_structures/arrays/array2d.h
	${CMAKE_CURRENT_LIST_DIR}/data_structures/arrays/array2d.inl
	${CMAKE_CURRENT_LIST_DIR}/data_structures/arrays/array3d.h
	${CMAKE_CURRENT_LIST_DIR}/data_structures/arrays/array3d.inl
	${CMAKE_CURRENT_LIST_DIR}/data_structures/arrays/array4d.h
	${CMAKE_CURRENT_LIST_DIR}/data_structures/arrays/array4d.inl
	${CMAKE_CURRENT_LIST_DIR}/data_structures/arrays/array_bool.h
	${CMAKE_CURRENT_LIST_DIR}/data_structures/arrays/array_bool.inl

	#graphs
	${CMAKE_CURRENT_LIST_DIR}/data_structures/graphs/graph.h
	${CMAKE_CURRENT_LIST_DIR}/data_structures/graphs/graph.inl
	${CMAKE_CURRENT_LIST_DIR}/data_structures/graphs/includes/nodes/graph_node.h
	${CMAKE_CURRENT_LIST_DIR}/data_structures/graphs/includes/nodes/graph_node.inl
	${CMAKE_CURRENT_LIST_DIR}/data_structures/graphs/includes/iterators/graph_genericnodeiterator.h
	${CMAKE_CURRENT_LIST_DIR}/data_structures/graphs/includes/iterators/graph_genericnodeiterator.inl
	${CMAKE_CURRENT_LIST_DIR}/data_structures/graphs/includes/iterators/graph_nodeiterator.h
	${CMAKE_CURRENT_LIST_DIR}/data_structures/graphs/includes/iterators/graph_nodeiterator.inl
	${CMAKE_CURRENT_LIST_DIR}/data_structures/graphs/includes/iterators/graph_adjacentiterator.h
	${CMAKE_CURRENT_LIST_DIR}/data_structures/graphs/includes/iterators/graph_adjacentiterator.inl
	${CMAKE_CURRENT_LIST_DIR}/data_structures/graphs/includes/iterators/graph_edgeiterator.h
	${CMAKE_CURRENT_LIST_DIR}/data_structures/graphs/includes/iterators/graph_edgeiterator.inl
	${CMAKE_CURRENT_LIST_DIR}/data_structures/graphs/bipartite_graph.h #bipartite graph
	${CMAKE_CURRENT_LIST_DIR}/data_structures/graphs/bipartite_graph.inl
	${CMAKE_CURRENT_LIST_DIR}/data_structures/graphs/bipartite_graph_iterators.h
	${CMAKE_CURRENT_LIST_DIR}/data_structures/graphs/bipartite_graph_iterators.inl
	${CMAKE_CURRENT_LIST_DIR}/data_structures/graphs/undirected_node.h

	#lattices
	${CMAKE_CURRENT_LIST_DIR}/data_structures/lattices/regular_lattice.h
	${CMAKE_CURRENT_LIST_DIR}/data_structures/lattices/regular_lattice.inl
	${CMAKE_CURRENT_LIST_DIR}/data_structures/lattices/regular_lattice_iterators.h
	${CMAKE_CURRENT_LIST_DIR}/data_structures/lattices/regular_lattice_iterators.inl

	#trees
	${CMAKE_CURRENT_LIST_DIR}/data_structures/trees/includes/tree_common.h  #tree common
	${CMAKE_CURRENT_LIST_DIR}/data_structures/trees/includes/iterators/tree_genericiterator.h
	${CMAKE_CURRENT_LIST_DIR}/data_structures/trees/includes/iterators/tree_insertiterator.h
	${CMAKE_CURRENT_LIST_DIR}/data_structures/trees/includes/iterators/tree_insertiterator.inl
	${CMAKE_CURRENT_LIST_DIR}/data_structures/trees/includes/iterators/tree_iterator.h
	${CMAKE_CURRENT_LIST_DIR}/data_structures/trees/includes/iterators/tree_iterator.inl
	${CMAKE_CURRENT_LIST_DIR}/data_structures/trees/includes/iterators/tree_reverseiterator.h
	${CMAKE_CURRENT_LIST_DIR}/data_structures/trees/includes/iterators/tree_reverseiterator.inl
	${CMAKE_CURRENT_LIST_DIR}/data_structures/trees/includes/iterators/tree_rangebased_iterators.h
	${CMAKE_CURRENT_LIST_DIR}/data_structures/trees/includes/iterators/tree_rangebased_iterators.inl
	${CMAKE_CURRENT_LIST_DIR}/data_structures/trees/includes/bst_helpers.h
	${CMAKE_CURRENT_LIST_DIR}/data_structures/trees/includes/bst_helpers.inl
	${CMAKE_CURRENT_LIST_DIR}/data_structures/trees/includes/bstinner_helpers.h
	${CMAKE_CURRENT_LIST_DIR}/data_structures/trees/includes/bstinner_helpers.inl
	${CMAKE_CURRENT_LIST_DIR}/data_structures/trees/includes/bstleaf_helpers.h
	${CMAKE_CURRENT_LIST_DIR}/data_structures/trees/includes/bstleaf_helpers.inl
	${CMAKE_CURRENT_LIST_DIR}/data_structures/trees/includes/avl_helpers.h  #bst trees
	${CMAKE_CURRENT_LIST_DIR}/data_structures/trees/includes/avl_helpers.inl
	${CMAKE_CURRENT_LIST_DIR}/data_structures/trees/bst.h
	${CMAKE_CURRENT_LIST_DIR}/data_structures/trees/bstinner.h
	${CMAKE_CURRENT_LIST_DIR}/data_structures/trees/bstinner.inl
	${CMAKE_CURRENT_LIST_DIR}/data_structures/trees/bstleaf.h
	${CMAKE_CURRENT_LIST_DIR}/data_structures/trees/bstleaf.inl
	${CMAKE_CURRENT_LIST_DIR}/data_structures/trees/includes/nodes/bst_node.h  # avl trees
	${CMAKE_CURRENT_LIST_DIR}/data_structures/trees/includes/nodes/bst_node.inl
	${CMAKE_CURRENT_LIST_DIR}/data_structures/trees/avlinner.h
	${CMAKE_CURRENT_LIST_DIR}/data_structures/trees/avlinner.inl
	${CMAKE_CURRENT_LIST_DIR}/data_structures/trees/avlleaf.h
	${CMAKE_CURRENT_LIST_DIR}/data_structures/trees/avlleaf.inl
	${CMAKE_CURRENT_LIST_DIR}/data_structures/trees/includes/nodes/avl_node.h  # range tree
	${CMAKE_CURRENT_LIST_DIR}/data_structures/trees/includes/nodes/avl_node.inl
	${CMAKE_CURRENT_LIST_DIR}/data_structures/trees/rangetree.h
	${CMAKE_CURRENT_LIST_DIR}/data_structures/trees/rangetree.inl
	${CMAKE_CURRENT_LIST_DIR}/data_structures/trees/includes/nodes/rangetree_node.h
	${CMAKE_CURRENT_LIST_DIR}/data_structures/trees/includes/nodes/rangetree_node.inl
	${CMAKE_CURRENT_LIST_DIR}/data_structures/trees/includes/rangetree_types.h  #aabb tree
	${CMAKE_CURRENT_LIST_DIR}/data_structures/trees/aabbtree.h
	${CMAKE_CURRENT_LIST_DIR}/data_structures/trees/aabbtree.inl
	${CMAKE_CURRENT_LIST_DIR}/data_structures/trees/includes/nodes/aabb_node.h
	${CMAKE_CURRENT_LIST_DIR}/data_structures/trees/includes/nodes/aabb_node.inl

	#algorithms
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
	${CMAKE_CURRENT_LIST_DIR}/algorithms/sphere_coverage.h
	${CMAKE_CURRENT_LIST_DIR}/algorithms/sphere_coverage.inl
	${CMAKE_CURRENT_LIST_DIR}/algorithms/global_optimal_rotation_matrix.h

	#meshes
	${CMAKE_CURRENT_LIST_DIR}/meshes/mesh.h
	${CMAKE_CURRENT_LIST_DIR}/meshes/dcel/dcel.h
	${CMAKE_CURRENT_LIST_DIR}/meshes/dcel/dcel_data.h
	${CMAKE_CURRENT_LIST_DIR}/meshes/dcel/dcel_face.h
	${CMAKE_CURRENT_LIST_DIR}/meshes/dcel/dcel_face_iterators.h
	${CMAKE_CURRENT_LIST_DIR}/meshes/dcel/dcel_half_edge.h
	${CMAKE_CURRENT_LIST_DIR}/meshes/dcel/dcel_iterators.h
	${CMAKE_CURRENT_LIST_DIR}/meshes/dcel/dcel_struct.h
	${CMAKE_CURRENT_LIST_DIR}/meshes/dcel/dcel_struct.inl
	${CMAKE_CURRENT_LIST_DIR}/meshes/dcel/dcel_vertex.h
	${CMAKE_CURRENT_LIST_DIR}/meshes/dcel/dcel_vertex_iterators.h
	${CMAKE_CURRENT_LIST_DIR}/meshes/dcel/algorithms/dcel_algorithms.h
	${CMAKE_CURRENT_LIST_DIR}/meshes/dcel/algorithms/dcel_bounding_boxes.h
	${CMAKE_CURRENT_LIST_DIR}/meshes/dcel/algorithms/dcel_bounding_boxes.inl
	${CMAKE_CURRENT_LIST_DIR}/meshes/dcel/algorithms/dcel_cgal_triangulation.h
	${CMAKE_CURRENT_LIST_DIR}/meshes/dcel/algorithms/dcel_edge_flip.h
	${CMAKE_CURRENT_LIST_DIR}/meshes/dcel/algorithms/dcel_flooding.inl
	${CMAKE_CURRENT_LIST_DIR}/meshes/dcel/algorithms/dcel_to_vectors.h
	${CMAKE_CURRENT_LIST_DIR}/meshes/dcel/algorithms/dcel_flooding.h
	${CMAKE_CURRENT_LIST_DIR}/meshes/dcel/algorithms/dcel_coloring.h
	${CMAKE_CURRENT_LIST_DIR}/meshes/dcel/algorithms/dcel_connected_components.h
	${CMAKE_CURRENT_LIST_DIR}/meshes/dcel/algorithms/dcel_connected_components.inl
	${CMAKE_CURRENT_LIST_DIR}/meshes/dcel/algorithms/dcel_robustness.h
	${CMAKE_CURRENT_LIST_DIR}/meshes/dcel/dcel_builder.h
	${CMAKE_CURRENT_LIST_DIR}/meshes/eigenmesh/simpleeigenmesh.h
	${CMAKE_CURRENT_LIST_DIR}/meshes/eigenmesh/eigenmesh.h
	${CMAKE_CURRENT_LIST_DIR}/meshes/eigenmesh/algorithms/eigenmesh_algorithms.h
	)

set(CG3_CORE_SOURCES
	#geometry
	${CMAKE_CURRENT_LIST_DIR}/geometry/bounding_box3.cpp
	${CMAKE_CURRENT_LIST_DIR}/geometry/bounding_box2.cpp
	${CMAKE_CURRENT_LIST_DIR}/geometry/cylinder.cpp
	${CMAKE_CURRENT_LIST_DIR}/geometry/intersections2.cpp
	${CMAKE_CURRENT_LIST_DIR}/geometry/line2.cpp
	${CMAKE_CURRENT_LIST_DIR}/geometry/line3.cpp
	${CMAKE_CURRENT_LIST_DIR}/geometry/plane.cpp
	${CMAKE_CURRENT_LIST_DIR}/geometry/polygon2.cpp
	${CMAKE_CURRENT_LIST_DIR}/geometry/quaternion.cpp
	${CMAKE_CURRENT_LIST_DIR}/geometry/sphere.cpp
	${CMAKE_CURRENT_LIST_DIR}/geometry/transformations3.cpp
	#io
	${CMAKE_CURRENT_LIST_DIR}/io/ply/ply_header.cpp
	#utilities
	${CMAKE_CURRENT_LIST_DIR}/utilities/color.cpp

	#trees
	${CMAKE_CURRENT_LIST_DIR}/data_structures/trees/includes/rangetree_types.cpp  # aabb tree

	#algorithms
	${CMAKE_CURRENT_LIST_DIR}/algorithms/global_optimal_rotation_matrix.cpp
	${CMAKE_CURRENT_LIST_DIR}/algorithms/marching_cubes.cpp
	${CMAKE_CURRENT_LIST_DIR}/algorithms/normalization.cpp
	${CMAKE_CURRENT_LIST_DIR}/algorithms/laplacian_smoothing.cpp

	#meshes
	${CMAKE_CURRENT_LIST_DIR}/meshes/dcel/algorithms/dcel_cgal_triangulation.cpp
	${CMAKE_CURRENT_LIST_DIR}/meshes/dcel/algorithms/dcel_coloring.cpp
	${CMAKE_CURRENT_LIST_DIR}/meshes/dcel/algorithms/dcel_edge_flip.cpp
	${CMAKE_CURRENT_LIST_DIR}/meshes/dcel/algorithms/dcel_robustness.cpp
	${CMAKE_CURRENT_LIST_DIR}/meshes/dcel/algorithms/dcel_to_vectors.cpp
	${CMAKE_CURRENT_LIST_DIR}/meshes/dcel/dcel_builder.cpp
	${CMAKE_CURRENT_LIST_DIR}/meshes/dcel/dcel_face.cpp
	${CMAKE_CURRENT_LIST_DIR}/meshes/dcel/dcel_half_edge.cpp
	${CMAKE_CURRENT_LIST_DIR}/meshes/dcel/dcel_vertex.cpp
	${CMAKE_CURRENT_LIST_DIR}/meshes/eigenmesh/simpleeigenmesh.cpp
	${CMAKE_CURRENT_LIST_DIR}/meshes/eigenmesh/eigenmesh.cpp
	${CMAKE_CURRENT_LIST_DIR}/meshes/eigenmesh/algorithms/eigenmesh_algorithms.cpp
	)

if (CG3_STATIC)
	add_library(cg3-core SHARED ${CG3_CORE_HEADERS} ${CG3_CORE_SOURCES})
else()
	add_library(cg3-core INTERFACE)
endif()

target_include_directories(cg3-core ${CG3_TARGET_MOD} ${CG3_INCLUDE_DIR})
target_compile_definitions(cg3-core ${CG3_TARGET_MOD} CG3_QMAKE)

target_link_libraries(cg3-core ${CG3_TARGET_MOD} Eigen)
if (TARGET Qt5::Gui)
	target_link_libraries(cg3-core ${CG3_TARGET_MOD} Qt5::Gui)
endif()
if (TARGET cinolib)
	target_link_libraries(cg3-core ${CG3_TARGET_MOD} cinolib)
endif()
if (TARGET CGAL::CGAL)
	target_compile_definitions(cg3-core ${CG3_TARGET_MOD} CGAL_EIGEN3_ENABLED)
	target_link_libraries(cg3-core ${CG3_TARGET_MOD} 
		CGAL::CGAL)
endif()

list(APPEND CG3_LINK_LIBRARIES cg3-core)

#
# This file is part of cg3lib: https://github.com/cg3hci/cg3lib
# This Source Code Form is subject to the terms of the GNU GPL 3.0
#
# @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
# @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
#

DEFINES += CG3_CORE_DEFINED

CONFIG += CG3_OPENMP

include(find_boost.pri)
include(find_eigen.pri)

win32 {
	DEFINES += _USE_MATH_DEFINES
	DEFINES+=NOMINMAX
}

CG3_OPENMP {
	unix:!macx{
		QMAKE_CXXFLAGS += -fopenmp
		QMAKE_LFLAGS += -fopenmp
	}
}

macx{
	DEFINES += GL_SILENCE_DEPRECATION
}

#core
HEADERS += \
	$$PWD/cg3lib.h \ #core
	$$PWD/geometry/bounding_box2.h \ #geometry
	$$PWD/geometry/bounding_box3.h \
	$$PWD/geometry/cylinder.h \
	$$PWD/geometry/intersections2.h \
	$$PWD/geometry/line2.h \
	$$PWD/geometry/line3.h \
	$$PWD/geometry/plane.h \
	$$PWD/geometry/point2.h \
	$$PWD/geometry/point2.inl \
	$$PWD/geometry/point3.h \
	$$PWD/geometry/point3.inl \
	$$PWD/geometry/polygon2.h \
	$$PWD/geometry/quaternion.h \
	$$PWD/geometry/segment.h \
	$$PWD/geometry/segment.inl \
	$$PWD/geometry/segment2.h \
	$$PWD/geometry/segment3.h \
	$$PWD/geometry/sphere.h \
	$$PWD/geometry/transformations3.h \
	$$PWD/geometry/triangle.h \
	$$PWD/geometry/triangle.inl \
	$$PWD/geometry/triangle2.h \
	$$PWD/geometry/triangle2_utils.h \
	$$PWD/geometry/triangle2_utils.inl \
	$$PWD/geometry/triangle3.h \
	$$PWD/geometry/utils2.h \
	$$PWD/geometry/utils2.inl \
	$$PWD/geometry/utils3.h \
	$$PWD/geometry/utils3.inl \
	$$PWD/io/file_commons.h \ #io
	$$PWD/io/load_save_obj.h \
	$$PWD/io/load_save_obj.inl \
	$$PWD/io/load_save_ply.h \
	$$PWD/io/load_save_ply.inl \ 
	$$PWD/io/load_save_file.h \
	$$PWD/io/serializable_object.h \
	$$PWD/io/serialize.h \
	$$PWD/io/serialize.inl \
	$$PWD/io/serialize_eigen.h \
	$$PWD/io/serialize_eigen.inl \
	$$PWD/io/serialize_qt.h \
	$$PWD/io/serialize_qt.inl \
	$$PWD/io/serialize_std.h \
	$$PWD/io/serialize_std.inl \
	$$PWD/io/ply/ply.h \
	$$PWD/io/ply/ply.inl \
	$$PWD/io/ply/ply_header.h \
	$$PWD/io/ply/ply_edge.h \
	$$PWD/io/ply/ply_edge.inl \
	$$PWD/io/ply/ply_face.h \
	$$PWD/io/ply/ply_face.inl \
	$$PWD/io/ply/ply_vertex.h \
	$$PWD/io/ply/ply_vertex.inl \
	$$PWD/utilities/cg3_config_folder.h \ #utilities
	$$PWD/utilities/color.h \
	$$PWD/utilities/command_line_argument_manager.h \
	$$PWD/utilities/command_line_argument_manager.inl \
	$$PWD/utilities/comparators.h \
	$$PWD/utilities/const.h \
	$$PWD/utilities/eigen.h \
	$$PWD/utilities/eigen.inl \
	$$PWD/utilities/hash.h \
	$$PWD/utilities/hash.inl \
	$$PWD/utilities/map.h \
	$$PWD/utilities/map.inl \
	$$PWD/utilities/nested_initializer_lists.h \
	$$PWD/utilities/nested_initializer_lists.inl \
	$$PWD/utilities/pair.h \
	$$PWD/utilities/pair.inl \
	$$PWD/utilities/set.h \
	$$PWD/utilities/set.inl \
	$$PWD/utilities/string.h \
	$$PWD/utilities/string.inl \
	$$PWD/utilities/system.h \
	$$PWD/utilities/system.inl \
	$$PWD/utilities/timer.h \
	$$PWD/utilities/timer.inl \
	$$PWD/utilities/tokenizer.h \
	$$PWD/utilities/tokenizer.inl \
	$$PWD/utilities/vector.h \
	$$PWD/utilities/vector.inl \
	$$PWD/utilities/utils.h \
	$$PWD/utilities/utils.inl

#data_structures
HEADERS += \
	$$PWD/data_structures/graphs/graph.h \ #graphs
	$$PWD/data_structures/graphs/graph.inl \
	$$PWD/data_structures/graphs/includes/nodes/graph_node.h \
	$$PWD/data_structures/graphs/includes/nodes/graph_node.inl \
	$$PWD/data_structures/graphs/includes/iterators/graph_genericnodeiterator.h \
	$$PWD/data_structures/graphs/includes/iterators/graph_genericnodeiterator.inl \
	$$PWD/data_structures/graphs/includes/iterators/graph_nodeiterator.h \
	$$PWD/data_structures/graphs/includes/iterators/graph_nodeiterator.inl \
	$$PWD/data_structures/graphs/includes/iterators/graph_adjacentiterator.h \
	$$PWD/data_structures/graphs/includes/iterators/graph_adjacentiterator.inl \
	$$PWD/data_structures/graphs/includes/iterators/graph_edgeiterator.h \ #bipartite graph
	$$PWD/data_structures/graphs/includes/iterators/graph_edgeiterator.inl \
	$$PWD/data_structures/graphs/bipartite_graph.h \
	$$PWD/data_structures/graphs/bipartite_graph.inl \
	$$PWD/data_structures/graphs/bipartite_graph_iterators.h \
	$$PWD/data_structures/graphs/bipartite_graph_iterators.inl \
	$$PWD/data_structures/graphs/undirected_node.h \
	$$PWD/data_structures/lattices/regular_lattice.h \ #lattices
	$$PWD/data_structures/lattices/regular_lattice.inl \
	$$PWD/data_structures/lattices/regular_lattice_iterators.h \
	$$PWD/data_structures/lattices/regular_lattice_iterators.inl \
	$$PWD/data_structures/trees/includes/tree_common.h \ #tree common
	$$PWD/data_structures/trees/includes/iterators/tree_genericiterator.h \
	$$PWD/data_structures/trees/includes/iterators/tree_insertiterator.h \
	$$PWD/data_structures/trees/includes/iterators/tree_insertiterator.inl \
	$$PWD/data_structures/trees/includes/iterators/tree_iterator.h \
	$$PWD/data_structures/trees/includes/iterators/tree_iterator.inl \
	$$PWD/data_structures/trees/includes/iterators/tree_reverseiterator.h \
	$$PWD/data_structures/trees/includes/iterators/tree_reverseiterator.inl \
	$$PWD/data_structures/trees/includes/iterators/tree_rangebased_iterators.h \
	$$PWD/data_structures/trees/includes/iterators/tree_rangebased_iterators.inl \
	$$PWD/data_structures/trees/includes/bst_helpers.h \
	$$PWD/data_structures/trees/includes/bst_helpers.inl \
	$$PWD/data_structures/trees/includes/bstinner_helpers.h \
	$$PWD/data_structures/trees/includes/bstinner_helpers.inl \
	$$PWD/data_structures/trees/includes/bstleaf_helpers.h \
	$$PWD/data_structures/trees/includes/bstleaf_helpers.inl \
	$$PWD/data_structures/trees/includes/avl_helpers.h \ #bst trees
	$$PWD/data_structures/trees/includes/avl_helpers.inl \
	$$PWD/data_structures/trees/bst.h \
	$$PWD/data_structures/trees/bstinner.h \
	$$PWD/data_structures/trees/bstinner.inl \
	$$PWD/data_structures/trees/bstleaf.h \
	$$PWD/data_structures/trees/bstleaf.inl \
	$$PWD/data_structures/trees/includes/nodes/bst_node.h \ # avl trees
	$$PWD/data_structures/trees/includes/nodes/bst_node.inl \
	$$PWD/data_structures/trees/avlinner.h \
	$$PWD/data_structures/trees/avlinner.inl \
	$$PWD/data_structures/trees/avlleaf.h \
	$$PWD/data_structures/trees/avlleaf.inl \
	$$PWD/data_structures/trees/includes/nodes/avl_node.h \ # range tree
	$$PWD/data_structures/trees/includes/nodes/avl_node.inl \
	$$PWD/data_structures/trees/rangetree.h \
	$$PWD/data_structures/trees/rangetree.inl \
	$$PWD/data_structures/trees/includes/nodes/rangetree_node.h \
	$$PWD/data_structures/trees/includes/nodes/rangetree_node.inl \
	$$PWD/data_structures/trees/includes/rangetree_types.h \ #aabb tree
	$$PWD/data_structures/trees/aabbtree.h \
	$$PWD/data_structures/trees/aabbtree.inl \
	$$PWD/data_structures/trees/includes/nodes/aabb_node.h \
	$$PWD/data_structures/trees/includes/nodes/aabb_node.inl

#algorithms
HEADERS += \
	$$PWD/algorithms/convex_hull2.h \
	$$PWD/algorithms/convex_hull2.inl \
	$$PWD/algorithms/convex_hull2_incremental.h \
	$$PWD/algorithms/convex_hull2_incremental.inl \
	$$PWD/algorithms/convex_hull3.h \
	$$PWD/algorithms/convex_hull3.inl \
	$$PWD/algorithms/graph_algorithms.h \
	$$PWD/algorithms/graph_algorithms.inl \
	$$PWD/algorithms/laplacian_smoothing.h \
	$$PWD/algorithms/marching_cubes.h \
	$$PWD/algorithms/mesh_function_smoothing.h \
	$$PWD/algorithms/mesh_function_smoothing.inl \
	$$PWD/algorithms/normalization.h \
	$$PWD/algorithms/saliency.h \
	$$PWD/algorithms/sphere_coverage.h \
	$$PWD/algorithms/sphere_coverage.inl \
	$$PWD/algorithms/global_optimal_rotation_matrix.h

#meshes
HEADERS += \
	$$PWD/meshes/mesh.h \
	$$PWD/meshes/dcel/dcel.h \
	$$PWD/meshes/dcel/dcel_data.h \
	$$PWD/meshes/dcel/dcel_face.h \
	$$PWD/meshes/dcel/dcel_face_iterators.h \
	$$PWD/meshes/dcel/dcel_half_edge.h \
	$$PWD/meshes/dcel/dcel_iterators.h \
	$$PWD/meshes/dcel/dcel_struct.h \
	$$PWD/meshes/dcel/dcel_struct.inl \
	$$PWD/meshes/dcel/dcel_vertex.h \
	$$PWD/meshes/dcel/dcel_vertex_iterators.h \
	$$PWD/meshes/dcel/algorithms/dcel_algorithms.h  \
	$$PWD/meshes/dcel/algorithms/dcel_bounding_boxes.h \
	$$PWD/meshes/dcel/algorithms/dcel_bounding_boxes.inl \
	$$PWD/meshes/dcel/algorithms/dcel_edge_flip.h \
	$$PWD/meshes/dcel/algorithms/dcel_to_vectors.h \
	$$PWD/meshes/dcel/algorithms/dcel_flooding.h \
	$$PWD/meshes/dcel/algorithms/dcel_flooding.inl \
	$$PWD/meshes/dcel/algorithms/dcel_coloring.h \
	$$PWD/meshes/dcel/algorithms/dcel_connected_components.h \
	$$PWD/meshes/dcel/algorithms/dcel_connected_components.inl \
	$$PWD/meshes/dcel/algorithms/dcel_robustness.h \
	$$PWD/meshes/dcel/dcel_builder.h \
	$$PWD/meshes/eigenmesh/simpleeigenmesh.h \
	$$PWD/meshes/eigenmesh/eigenmesh.h \
	$$PWD/meshes/eigenmesh/algorithms/eigenmesh_algorithms.h

CG3_STATIC {
SOURCES += \
	$$PWD/geometry/bounding_box3.cpp \ #geometry
	$$PWD/geometry/bounding_box2.cpp \
	$$PWD/geometry/cylinder.cpp \
	$$PWD/geometry/intersections2.cpp \
	$$PWD/geometry/line2.cpp \
	$$PWD/geometry/line3.cpp \
	$$PWD/geometry/plane.cpp \
	$$PWD/geometry/polygon2.cpp \
	$$PWD/geometry/quaternion.cpp \
	$$PWD/geometry/sphere.cpp \
	$$PWD/geometry/transformations3.cpp \
	$$PWD/io/ply/ply_header.cpp \ #io
	$$PWD/utilities/color.cpp #utilities

#data_structures
SOURCES += \
	$$PWD/data_structures/trees/includes/rangetree_types.cpp  # aabb tree

#algorithms
SOURCES += \
	$$PWD/algorithms/global_optimal_rotation_matrix.cpp \
	$$PWD/algorithms/marching_cubes.cpp \
	$$PWD/algorithms/normalization.cpp \
	$$PWD/algorithms/saliency.cpp \
	$$PWD/algorithms/laplacian_smoothing.cpp

#meshes
SOURCES += \
	$$PWD/meshes/dcel/algorithms/dcel_coloring.cpp \
	$$PWD/meshes/dcel/algorithms/dcel_edge_flip.cpp \
	$$PWD/meshes/dcel/algorithms/dcel_robustness.cpp \
	$$PWD/meshes/dcel/algorithms/dcel_to_vectors.cpp \
	$$PWD/meshes/dcel/dcel_builder.cpp \
	$$PWD/meshes/dcel/dcel_face.cpp \
	$$PWD/meshes/dcel/dcel_half_edge.cpp \
	$$PWD/meshes/dcel/dcel_vertex.cpp


# unneeded?
unix:!macx {
	LIBS += -lboost_system -DBOOST_LOG_DYN_LINK -lboost_log -lboost_thread -lpthread
}

}

# todo: make these inline!!
SOURCES += \
	$$PWD/meshes/eigenmesh/simpleeigenmesh.cpp \
	$$PWD/meshes/eigenmesh/eigenmesh.cpp \
	$$PWD/meshes/eigenmesh/algorithms/eigenmesh_algorithms.cpp

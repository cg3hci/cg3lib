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

		${CMAKE_CURRENT_LIST_DIR}/data_structures/graphs/graph.h  #graphs
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

		${CMAKE_CURRENT_LIST_DIR}/data_structures/lattices/regular_lattice.h #lattices
		${CMAKE_CURRENT_LIST_DIR}/data_structures/lattices/regular_lattice.inl
		${CMAKE_CURRENT_LIST_DIR}/data_structures/lattices/regular_lattice_iterators.h
		${CMAKE_CURRENT_LIST_DIR}/data_structures/lattices/regular_lattice_iterators.inl

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
		${CMAKE_CURRENT_LIST_DIR}/data_structures/trees/includes/nodes/aabb_node.inl)

	SET(CG3_DATA_STRUCTURES_SOURCES
		#graphs 
		${CMAKE_CURRENT_LIST_DIR}/data_structures/trees/includes/rangetree_types.cpp  # aabb tree
		)

	add_library(
		cg3-data-structures SHARED 
		${CG3_DATA_STRUCTURES_HEADERS} ${CG3_DATA_STRUCTURES_SOURCES})

	target_link_libraries(cg3-data-structures PUBLIC cg3-core)
endif()

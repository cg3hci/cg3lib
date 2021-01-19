#
# This file is part of cg3lib: https://github.com/cg3hci/cg3lib
# This Source Code Form is subject to the terms of the GNU GPL 3.0
#
# @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
# @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
#

!contains(DEFINES, CG3_CORE_DEFINED){
	error(DataStructures module requires Core module)
}

DEFINES += CG3_DATA_STRUCTURES_DEFINED
MODULES += CG3_DATA_SRUCTURES


# ----- Arrays -----

HEADERS += \
	$$PWD/data_structures/arrays/array_.h \ #arrays
	$$PWD/data_structures/arrays/array_.inl \ 
	$$PWD/data_structures/arrays/arrays.h \
	$$PWD/data_structures/arrays/array2d.h \
	$$PWD/data_structures/arrays/array2d.inl \
	$$PWD/data_structures/arrays/array3d.h \
	$$PWD/data_structures/arrays/array3d.inl \
	$$PWD/data_structures/arrays/array4d.h \
	$$PWD/data_structures/arrays/array4d.inl \
	$$PWD/data_structures/arrays/array_bool.h \
	$$PWD/data_structures/arrays/array_bool.inl \
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

CG3_STATIC {
SOURCES += \
	#graphs
	$$PWD/data_structures/trees/includes/rangetree_types.cpp  # aabb tree
}

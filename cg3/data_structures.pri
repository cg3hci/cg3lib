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
    $$PWD/data_structures/arrays/arrays.h \
    $$PWD/data_structures/arrays/array2d.h \
    $$PWD/data_structures/arrays/array3d.h \
    $$PWD/data_structures/arrays/array4d.h \
    $$PWD/data_structures/arrays/array_bool.h \ #graphs
    $$PWD/data_structures/graphs/graph.h \
    $$PWD/data_structures/graphs/includes/nodes/graph_node.h \
    $$PWD/data_structures/graphs/includes/iterators/graph_genericnodeiterator.h \
    $$PWD/data_structures/graphs/includes/iterators/graph_nodeiterator.h \
    $$PWD/data_structures/graphs/includes/iterators/graph_adjacentiterator.h \
    $$PWD/data_structures/graphs/includes/iterators/graph_edgeiterator.h \ #bipartite graph
    $$PWD/data_structures/graphs/bipartite_graph.h \
    $$PWD/data_structures/graphs/bipartite_graph_iterators.h \
    $$PWD/data_structures/graphs/undirected_node.h \
    $$PWD/data_structures/lattices/regular_lattice.h \ #lattices
    $$PWD/data_structures/lattices/regular_lattice_iterators.h \
    $$PWD/data_structures/trees/includes/tree_common.h \ #tree common
    $$PWD/data_structures/trees/includes/iterators/tree_genericiterator.h \
    $$PWD/data_structures/trees/includes/iterators/tree_insertiterator.h \
    $$PWD/data_structures/trees/includes/iterators/tree_iterator.h \
    $$PWD/data_structures/trees/includes/iterators/tree_reverseiterator.h \
    $$PWD/data_structures/trees/includes/iterators/tree_rangebased_iterators.h \
    $$PWD/data_structures/trees/includes/bst_helpers.h \
    $$PWD/data_structures/trees/includes/bstinner_helpers.h \
    $$PWD/data_structures/trees/includes/bstleaf_helpers.h \
    $$PWD/data_structures/trees/includes/avl_helpers.h \ #bst trees
    $$PWD/data_structures/trees/bst.h \
    $$PWD/data_structures/trees/bstinner.h \
    $$PWD/data_structures/trees/bstleaf.h \
    $$PWD/data_structures/trees/includes/nodes/bst_node.h \ # avl trees
    $$PWD/data_structures/trees/avlinner.h \
    $$PWD/data_structures/trees/avlleaf.h \
    $$PWD/data_structures/trees/includes/nodes/avl_node.h \ # range tree
    $$PWD/data_structures/trees/rangetree.h \
    $$PWD/data_structures/trees/includes/nodes/rangetree_node.h \
    $$PWD/data_structures/trees/includes/rangetree_types.h \ #aabb tree
    $$PWD/data_structures/trees/aabbtree.h \
    $$PWD/data_structures/trees/includes/nodes/aabb_node.h

CG3_STATIC {
SOURCES += \
    $$PWD/data_structures/arrays/array_.cpp \ #arrays
    $$PWD/data_structures/arrays/array2d.cpp \
    $$PWD/data_structures/arrays/array3d.cpp \
    $$PWD/data_structures/arrays/array4d.cpp \
    $$PWD/data_structures/arrays/array_bool.cpp \
    $$PWD/data_structures/graphs/bipartite_graph.cpp \
    $$PWD/data_structures/graphs/bipartite_graph_iterators.cpp \
    $$PWD/data_structures/graphs/graph.cpp \ #graphs
    $$PWD/data_structures/graphs/includes/iterators/graph_adjacentiterator.cpp \
    $$PWD/data_structures/graphs/includes/iterators/graph_edgeiterator.cpp \
    $$PWD/data_structures/graphs/includes/iterators/graph_genericnodeiterator.cpp \
    $$PWD/data_structures/graphs/includes/iterators/graph_nodeiterator.cpp \
    $$PWD/data_structures/graphs/includes/nodes/graph_node.cpp \
    $$PWD/data_structures/lattices/regular_lattice.cpp \ #lattices
    $$PWD/data_structures/lattices/regular_lattice_iterators.cpp \
    $$PWD/data_structures/trees/aabbtree.cpp \
    $$PWD/data_structures/trees/avlinner.cpp \
    $$PWD/data_structures/trees/avlleaf.cpp \
    $$PWD/data_structures/trees/bstinner.cpp \
    $$PWD/data_structures/trees/bstleaf.cpp \
    $$PWD/data_structures/trees/includes/avl_helpers.cpp \
    $$PWD/data_structures/trees/includes/bst_helpers.cpp \
    $$PWD/data_structures/trees/includes/bstinner_helpers.cpp \
    $$PWD/data_structures/trees/includes/bstleaf_helpers.cpp \
    $$PWD/data_structures/trees/includes/iterators/tree_insertiterator.cpp \
    $$PWD/data_structures/trees/includes/iterators/tree_iterator.cpp \
    $$PWD/data_structures/trees/includes/iterators/tree_rangebased_iterators.cpp \
    $$PWD/data_structures/trees/rangetree.cpp \
    $$PWD/data_structures/trees/includes/iterators/tree_reverseiterator.cpp \
    $$PWD/data_structures/trees/includes/nodes/aabb_node.cpp \
    $$PWD/data_structures/trees/includes/nodes/avl_node.cpp \
    $$PWD/data_structures/trees/includes/nodes/bst_node.cpp \
    $$PWD/data_structures/trees/includes/nodes/rangetree_node.cpp \
    $$PWD/data_structures/trees/includes/rangetree_types.cpp  # aabb tree
}

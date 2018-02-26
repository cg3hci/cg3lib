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
CONFIG += CG3_DATA_STRUCTURES
MODULES += CG3_DATA_SRUCTURES


# ----- Arrays -----

HEADERS += \
    $$PWD/data_structures/arrays/arrays.h \
    $$PWD/data_structures/arrays/array2d.h \
    $$PWD/data_structures/arrays/array3d.h \
    $$PWD/data_structures/arrays/array4d.h \
    $$PWD/data_structures/arrays/array.h

SOURCES += \
    $$PWD/data_structures/arrays/array2d.tpp \
    $$PWD/data_structures/arrays/array3d.tpp \
    $$PWD/data_structures/arrays/array4d.tpp \
    $$PWD/data_structures/arrays/array.tpp

# ----- Graphs -----

HEADERS += \
    $$PWD/data_structures/graphs/graph.h \
    $$PWD/data_structures/graphs/includes/nodes/graph_node.h \
    $$PWD/data_structures/graphs/includes/iterators/graph_nodeiterator.h \
    $$PWD/data_structures/graphs/includes/iterators/graph_edgeiterator.h \
    $$PWD/data_structures/graphs/includes/iterators/graph_adjacentnodeiterator.h \
    $$PWD/data_structures/graphs/includes/iterators/graph_genericnodeiterator.h

SOURCES += \
    $$PWD/data_structures/graphs/graph.tpp \
    $$PWD/data_structures/graphs/includes/nodes/graph_node.tpp \
    $$PWD/data_structures/graphs/includes/iterators/graph_nodeiterator.tpp \
    $$PWD/data_structures/graphs/includes/iterators/graph_edgeiterator.tpp \
    $$PWD/data_structures/graphs/includes/iterators/graph_adjacentnodeiterator.tpp \
    $$PWD/data_structures/graphs/includes/iterators/graph_genericnodeiterator.tpp

# ----- Bipartite graph -----

HEADERS += \
    $$PWD/data_structures/graphs/bipartite_graph.h \
    $$PWD/data_structures/graphs/bipartite_graph_iterators.h \
    $$PWD/data_structures/graphs/undirected_node.h

SOURCES += \
    $$PWD/data_structures/graphs/bipartite_graph.tpp \
    $$PWD/data_structures/graphs/bipartite_graph_iterators.tpp

# ----- Lattices -----

HEADERS += \
    $$PWD/data_structures/lattices/regular_lattice.h \
    $$PWD/data_structures/lattices/regular_lattice_iterators.h

SOURCES += \
    $$PWD/data_structures/lattices/regular_lattice.cpp

# ----- Trees -----


# Tree common includes
HEADERS +=  \
    $$PWD/data_structures/trees/includes/tree_common.h \
    $$PWD/data_structures/trees/includes/iterators/tree_genericiterator.h \
    $$PWD/data_structures/trees/includes/iterators/tree_insertiterator.h \
    $$PWD/data_structures/trees/includes/iterators/tree_iterator.h \
    $$PWD/data_structures/trees/includes/iterators/tree_reverseiterator.h \
    $$PWD/data_structures/trees/includes/iterators/tree_rangebased_iterators.h \
    $$PWD/data_structures/trees/includes/bst_helpers.h \
    $$PWD/data_structures/trees/includes/bstinner_helpers.h \
    $$PWD/data_structures/trees/includes/bstleaf_helpers.h \
    $$PWD/data_structures/trees/includes/avl_helpers.h

SOURCES += \
    $$PWD/data_structures/trees/includes/iterators/tree_insertiterator.tpp \
    $$PWD/data_structures/trees/includes/iterators/tree_iterator.tpp \
    $$PWD/data_structures/trees/includes/iterators/tree_reverseiterator.tpp \
    $$PWD/data_structures/trees/includes/iterators/tree_rangebased_iterators.tpp \
    $$PWD/data_structures/trees/includes/bst_helpers.tpp \
    $$PWD/data_structures/trees/includes/bstinner_helpers.tpp \
    $$PWD/data_structures/trees/includes/bstleaf_helpers.tpp \
    $$PWD/data_structures/trees/includes/avl_helpers.tpp



# BST trees
HEADERS +=  \    
    $$PWD/data_structures/trees/bst.h \
    $$PWD/data_structures/trees/bstinner.h \
    $$PWD/data_structures/trees/bstleaf.h \
    $$PWD/data_structures/trees/includes/nodes/bst_node.h

SOURCES += \
    $$PWD/data_structures/trees/bstinner.tpp \
    $$PWD/data_structures/trees/bstleaf.tpp \
    $$PWD/data_structures/trees/includes/nodes/bst_node.tpp



# AVL trees
HEADERS += \
    $$PWD/data_structures/trees/avlinner.h \
    $$PWD/data_structures/trees/avlleaf.h \
    $$PWD/data_structures/trees/includes/nodes/avl_node.h

SOURCES += \
    $$PWD/data_structures/trees/avlinner.tpp \
    $$PWD/data_structures/trees/avlleaf.tpp \
    $$PWD/data_structures/trees/includes/nodes/avl_node.tpp


# Range tree
HEADERS += \
    $$PWD/data_structures/trees/rangetree.h \
    $$PWD/data_structures/trees/includes/nodes/rangetree_node.h \
    $$PWD/data_structures/trees/includes/rangetree_types.h

SOURCES += \
    $$PWD/data_structures/trees/rangetree.tpp \
    $$PWD/data_structures/trees/includes/nodes/rangetree_node.tpp \
    $$PWD/data_structures/trees/includes/rangetree_types.cpp


# AABB tree
HEADERS += \
    $$PWD/data_structures/trees/aabbtree.h \
    $$PWD/data_structures/trees/includes/nodes/aabb_node.h

SOURCES += \
    $$PWD/data_structures/trees/aabbtree.tpp \
    $$PWD/data_structures/trees/includes/nodes/aabb_node.tpp

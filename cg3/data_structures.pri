DEFINES += CG3_DATA_STRUCTURES_DEFINED
CONFIG += CG3_DATA_STRUCTURES
MODULES += CG3_DATA_SRUCTURES

!contains(DEFINES, CG3_CORE_DEFINED){
    error(DataStructures module requires cg3_core!)
}


# ----- Graphs -----

HEADERS += \
    $$PWD/data_structures/graphs/bipartite_graph.h \
    $$PWD/data_structures/graphs/bipartite_graph_iterators.h \
    $$PWD/data_structures/graphs/undirected_node.h



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
    $$PWD/data_structures/trees/includes/bst_helpers.h

SOURCES += \
    $$PWD/data_structures/trees/includes/iterators/tree_genericiterator.tpp \
    $$PWD/data_structures/trees/includes/iterators/tree_insertiterator.tpp \
    $$PWD/data_structures/trees/includes/iterators/tree_iterator.tpp \
    $$PWD/data_structures/trees/includes/iterators/tree_reverseiterator.tpp \
    $$PWD/data_structures/trees/includes/bst_helpers.tpp



# BST trees
HEADERS +=  \    
    $$PWD/data_structures/trees/bst.h \
    $$PWD/data_structures/trees/bstinner.h \
    $$PWD/data_structures/trees/bstleaf.h \
    $$PWD/data_structures/trees/includes/nodes/bst_node.h \
    $$PWD/data_structures/trees/includes/bstinner_helpers.h \
    $$PWD/data_structures/trees/includes/bstleaf_helpers.h

SOURCES += \
    $$PWD/data_structures/trees/bstinner.tpp \
    $$PWD/data_structures/trees/bstleaf.tpp \
    $$PWD/data_structures/trees/includes/nodes/bst_node.tpp \
    $$PWD/data_structures/trees/includes/bstinner_helpers.tpp \
    $$PWD/data_structures/trees/includes/bstleaf_helpers.tpp



# AVL trees
HEADERS += \
    $$PWD/data_structures/trees/avlinner.h \
    $$PWD/data_structures/trees/avlleaf.h \
    $$PWD/data_structures/trees/includes/nodes/avl_node.h \
    $$PWD/data_structures/trees/includes/avl_helpers.h

SOURCES += \
    $$PWD/data_structures/trees/avlinner.tpp \
    $$PWD/data_structures/trees/avlleaf.tpp \
    $$PWD/data_structures/trees/includes/nodes/avl_node.tpp \
    $$PWD/data_structures/trees/includes/avl_helpers.tpp



# Range tree
HEADERS += \
    $$PWD/data_structures/trees/rangetree.h \
    $$PWD/data_structures/trees/includes/nodes/rangetree_node.h \
    $$PWD/data_structures/trees/includes/rangetree_helpers.h \
    $$PWD/data_structures/trees/includes/rangetree_types.h

SOURCES += \
    $$PWD/data_structures/trees/rangetree.tpp \
    $$PWD/data_structures/trees/includes/rangetree_types.cpp \
    $$PWD/data_structures/trees/includes/nodes/rangetree_node.tpp \
    $$PWD/data_structures/trees/includes/rangetree_helpers.tpp


# AABB tree
HEADERS += \
    $$PWD/data_structures/trees/aabbtree.h \
    $$PWD/data_structures/trees/includes/aabb_helpers.h \
    $$PWD/data_structures/trees/includes/nodes/aabb_node.h \
    $$PWD/data_structures/trees/includes/nodes/aabb.h

SOURCES += \
    $$PWD/data_structures/trees/aabbtree.tpp \
    $$PWD/data_structures/trees/includes/aabb_helpers.tpp \
    $$PWD/data_structures/trees/includes/nodes/aabb_node.tpp \
    $$PWD/data_structures/trees/includes/nodes/aabb.tpp

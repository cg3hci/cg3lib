DEFINES += CG3_DATA_STRUCTURES_DEFINED
CONFIG += CG3_DATA_STRUCTURES
MODULES += CG3_DATA_SRUCTURES

!contains(DEFINES, CG3_CORE_DEFINED){
    error(DataStructures module requires cg3_core!)
}


# Graphs
HEADERS += \
    $$PWD/data_structures/graphs/bipartite_graph.h \
    $$PWD/data_structures/graphs/bipartite_graph_iterators.h \
    $$PWD/data_structures/graphs/undirected_node.h



# Lattices
HEADERS += \
    $$PWD/data_structures/lattices/regular_lattice.h \
    $$PWD/data_structures/lattices/regular_lattice_iterators.h

SOURCES += \
    $$PWD/data_structures/lattices/regular_lattice.cpp



# BST
HEADERS += \
    $$PWD/data_structures/trees/bst.h



# Basic BST
HEADERS += \
    $$PWD/data_structures/trees/bst/bstinner.h \
    $$PWD/data_structures/trees/bst/bstinner/bstinnernode.h \
    $$PWD/data_structures/trees/bst/bstinner/bstinneriterator.h \
    $$PWD/data_structures/trees/bst/bstleaf.h \
    $$PWD/data_structures/trees/bst/bstleaf/bstleafiterator.h \
    $$PWD/data_structures/trees/bst/bstleaf/bstleafnode.h

SOURCES += \
    $$PWD/data_structures/trees/bst/bstinner.tpp \
    $$PWD/data_structures/trees/bst/bstinner/bstinnernode.tpp \
    $$PWD/data_structures/trees/bst/bstinner/bstinneriterator.tpp \
    $$PWD/data_structures/trees/bst/bstleaf.tpp \
    $$PWD/data_structures/trees/bst/bstleaf/bstleafiterator.tpp \
    $$PWD/data_structures/trees/bst/bstleaf/bstleafnode.tpp




# AVL tree
HEADERS += \
    $$PWD/data_structures/trees/bst/avlinner.h \
    $$PWD/data_structures/trees/bst/avlinner/avlinneriterator.h \
    $$PWD/data_structures/trees/bst/avlinner/avlinnernode.h \
    $$PWD/data_structures/trees/bst/avlleaf.h \
    $$PWD/data_structures/trees/bst/avlleaf/avlleafiterator.h \
    $$PWD/data_structures/trees/bst/avlleaf/avlleafnode.h

SOURCES += \
    $$PWD/data_structures/trees/bst/avlinner.tpp \
    $$PWD/data_structures/trees/bst/avlinner/avlinneriterator.tpp \
    $$PWD/data_structures/trees/bst/avlinner/avlinnernode.tpp \
    $$PWD/data_structures/trees/bst/avlleaf.tpp \
    $$PWD/data_structures/trees/bst/avlleaf/avlleafiterator.tpp \
    $$PWD/data_structures/trees/bst/avlleaf/avlleafnode.tpp



# Range tree
HEADERS += \
    $$PWD/data_structures/trees/rangetree.h \
    $$PWD/data_structures/trees/rangetree/rangetreeiterator.h \
    $$PWD/data_structures/trees/rangetree/rangetreenode.h

SOURCES += \
    $$PWD/data_structures/trees/rangetree.tpp \
    $$PWD/data_structures/trees/rangetree/rangetreeiterator.tpp \
    $$PWD/data_structures/trees/rangetree/rangetreenode.tpp




# AABB tree
HEADERS += \
    $$PWD/data_structures/trees/aabbtree.h \
    $$PWD/data_structures/trees/aabbtree/aabbtreeiterator.h \
    $$PWD/data_structures/trees/aabbtree/aabbtreenode.h \
    $$PWD/data_structures/trees/aabbtree/aabbtreeaabb.h

SOURCES += \
    $$PWD/data_structures/trees/aabbtree.tpp \
    $$PWD/data_structures/trees/aabbtree/aabbtreeiterator.tpp \
    $$PWD/data_structures/trees/aabbtree/aabbtreenode.tpp \
    $$PWD/data_structures/trees/aabbtree/aabbtreeaabb.tpp

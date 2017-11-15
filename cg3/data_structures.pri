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
    $$PWD/data_structures/trees/includes/treecommon.h \
    $$PWD/data_structures/trees/includes/iterators/treegenericiterator.h \
    $$PWD/data_structures/trees/includes/iterators/treeinsertiterator.h \
    $$PWD/data_structures/trees/includes/iterators/treeiterator.h \
    $$PWD/data_structures/trees/includes/iterators/treereverseiterator.h \
    $$PWD/data_structures/trees/includes/bsthelpers.h

SOURCES += \
    $$PWD/data_structures/trees/includes/iterators/treegenericiterator.tpp \
    $$PWD/data_structures/trees/includes/iterators/treeinsertiterator.tpp \
    $$PWD/data_structures/trees/includes/iterators/treeiterator.tpp \
    $$PWD/data_structures/trees/includes/iterators/treereverseiterator.tpp \
    $$PWD/data_structures/trees/includes/bsthelpers.tpp



# BST trees
HEADERS +=  \    
    $$PWD/data_structures/trees/bst.h \
    $$PWD/data_structures/trees/bstinner.h \
    $$PWD/data_structures/trees/bstleaf.h \
    $$PWD/data_structures/trees/avlleaf.h \
    $$PWD/data_structures/trees/includes/nodes/bstnode.h \
    $$PWD/data_structures/trees/includes/bstinnerhelpers.h \
    $$PWD/data_structures/trees/includes/bstleafhelpers.h

SOURCES += \
    $$PWD/data_structures/trees/bstinner.tpp \
    $$PWD/data_structures/trees/bstleaf.tpp \
    $$PWD/data_structures/trees/avlleaf.tpp \
    $$PWD/data_structures/trees/includes/nodes/bstnode.tpp \
    $$PWD/data_structures/trees/includes/bstinnerhelpers.tpp \
    $$PWD/data_structures/trees/includes/bstleafhelpers.tpp



# AVL trees
HEADERS += \
    $$PWD/data_structures/trees/avlinner.h \
    $$PWD/data_structures/trees/includes/nodes/avlnode.h \
    $$PWD/data_structures/trees/includes/avlhelpers.h

SOURCES += \
    $$PWD/data_structures/trees/avlinner.tpp \
    $$PWD/data_structures/trees/includes/nodes/avlnode.tpp \
    $$PWD/data_structures/trees/includes/avlhelpers.tpp



# Range tree
HEADERS += \
    $$PWD/data_structures/trees/rangetree.h \
    $$PWD/data_structures/trees/includes/nodes/rangetreenode.h \
    $$PWD/data_structures/trees/includes/rangetreehelpers.h

SOURCES += \
    $$PWD/data_structures/trees/rangetree.tpp \
    $$PWD/data_structures/trees/includes/nodes/rangetreenode.tpp \
    $$PWD/data_structures/trees/includes/rangetreehelpers.tpp


# AABB tree
HEADERS += \
    $$PWD/data_structures/trees/aabbtree.h \
    $$PWD/data_structures/trees/includes/aabbhelpers.h \
    $$PWD/data_structures/trees/includes/nodes/aabbnode.h \
    $$PWD/data_structures/trees/includes/nodes/aabb.h

SOURCES += \
    $$PWD/data_structures/trees/aabbtree.tpp \
    $$PWD/data_structures/trees/includes/aabbhelpers.tpp \
    $$PWD/data_structures/trees/includes/nodes/aabbnode.tpp \
    $$PWD/data_structures/trees/includes/nodes/aabb.tpp

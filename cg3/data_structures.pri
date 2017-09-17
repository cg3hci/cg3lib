DEFINES += CG3_DATA_STRUCTURES_DEFINED
CONFIG += CG3_DATA_STRUCTURES
MODULES += CG3_DATA_SRUCTURES

!contains(DEFINES, CG3_CORE_DEFINED){
    error(DataStructures module requires cg3_core!)
}

HEADERS += \
    $$PWD/data_structures/graphs/bipartite_graph.h \
    $$PWD/data_structures/graphs/bipartite_graph_iterators.h \
    $$PWD/data_structures/graphs/undirected_node.h \
    $$PWD/data_structures/lattices/regular_lattice.h \
    $$PWD/data_structures/lattices/regular_lattice_iterators.h

SOURCES += \
    $$PWD/data_structures/lattices/regular_lattice.cpp

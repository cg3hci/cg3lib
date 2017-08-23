DEFINES += CG3_DATA_STRUCTURES_DEFINED
CONFIG += CG3_DATA_STRUCTURES
MODULES += CG3_DATA_SRUCTURES

!contains(DEFINES, CG3_CORE_DEFINED){
    error(Cgal module requires cg3_core!)
}

HEADERS += \
    $$PWD/data_structures/graphs/bipartitegraph.h \
    $$PWD/data_structures/graphs/bipartitegraphiterators.h \
    $$PWD/data_structures/graphs/undirectednode.h

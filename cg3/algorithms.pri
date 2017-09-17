DEFINES += CG3_ALGORITHMS_DEFINED
CONFIG += CG3_ALGORITHMS
MODULES += CG3_ALGORITHMS

!contains(DEFINES, CG3_CORE_DEFINED){
    error(Algorithms module requires cg3_core!)
}

HEADERS += \
    $$PWD/algorithms/marching_cubes.h

SOURCES += \
    $$PWD/algorithms/marching_cubes.cpp

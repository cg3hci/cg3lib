#
# This file is part of cg3lib: https://github.com/cg3hci/cg3lib
# This Source Code Form is subject to the terms of the GNU GPL 3.0
#
# @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
# @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
#

!contains(DEFINES, CG3_CORE_DEFINED){
    error(Algorithms module requires Core module!)
}

DEFINES += CG3_ALGORITHMS_DEFINED
MODULES += CG3_ALGORITHMS

HEADERS += \
    $$PWD/algorithms/convex_hull2.h \
    $$PWD/algorithms/convex_hull2_incremental.h \
    $$PWD/algorithms/convex_hull3.h \
    $$PWD/algorithms/graph_algorithms.h \
    $$PWD/algorithms/laplacian_smoothing.h \
    $$PWD/algorithms/marching_cubes.h \
    $$PWD/algorithms/sphere_coverage.h \
    $$PWD/algorithms/global_optimal_rotation_matrix.h

CG3_STATIC {
SOURCES += \
    $$PWD/algorithms/convex_hull2.cpp \
    $$PWD/algorithms/convex_hull2_incremental.cpp \
    $$PWD/algorithms/convex_hull3.cpp \
    $$PWD/algorithms/global_optimal_rotation_matrix.cpp \
    $$PWD/algorithms/graph_algorithms.cpp \
    $$PWD/algorithms/marching_cubes.cpp \
    $$PWD/algorithms/laplacian_smoothing.cpp \
    $$PWD/algorithms/sphere_coverage.cpp
}

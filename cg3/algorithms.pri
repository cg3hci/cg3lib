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
    $$PWD/algorithms/sphere_coverage.h \
    $$PWD/algorithms/global_optimal_rotation_matrix.h

SOURCES += \
    $$PWD/algorithms/convex_hull2.tpp \
    $$PWD/algorithms/convex_hull2_incremental.tpp \
    $$PWD/algorithms/convex_hull3.tpp \
    $$PWD/algorithms/graph_algorithms.tpp \
    $$PWD/algorithms/sphere_coverage.tpp \
    $$PWD/algorithms/global_optimal_rotation_matrix.cpp

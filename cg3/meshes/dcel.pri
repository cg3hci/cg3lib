#
# This file is part of cg3lib: https://github.com/cg3hci/cg3lib
# This Source Code Form is subject to the terms of the GNU GPL 3.0
#
# @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
# @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
#

!contains(DEFINES, CG3_CORE_DEFINED){
    error(Dcel module requires the Core module!)
}

DEFINES += CG3_DCEL_DEFINED
MODULES += CG3_DCEL

HEADERS += \
    $$PWD/dcel/dcel.h \
    $$PWD/dcel/dcel_face.h \
    $$PWD/dcel/dcel_face_iterators.h \
    $$PWD/dcel/dcel_half_edge.h \
    $$PWD/dcel/dcel_iterators.h \
    $$PWD/dcel/dcel_struct.h \
    $$PWD/dcel/dcel_vertex.h \
    $$PWD/dcel/dcel_vertex_iterators.h \
    $$PWD/dcel/algorithms/dcel_algorithms.h


SOURCES += \
    $$PWD/dcel/dcel_face.cpp \
    $$PWD/dcel/dcel_half_edge.cpp \
    $$PWD/dcel/dcel_vertex.cpp \
    $$PWD/dcel/dcel_struct.cpp \
    $$PWD/dcel/algorithms/dcel_algorithms.cpp \
    $$PWD/dcel/dcel_inline.tpp \
    $$PWD/dcel/dcel_half_edge_inline.tpp \
    $$PWD/dcel/dcel_face_iterators_inline.tpp \
    $$PWD/dcel/dcel_iterators_inline.tpp \
    $$PWD/dcel/dcel_vertex_inline.tpp \
    $$PWD/dcel/dcel_vertex_iterators_inline.tpp \
    $$PWD/dcel/dcel_face_inline.tpp

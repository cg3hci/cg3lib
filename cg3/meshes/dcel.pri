!contains(DEFINES, CG3_CORE_DEFINED){
    error(Dcel module requires the Core module!)
}

DEFINES += CG3_DCEL_DEFINED
CONFIG += CG3_DCEL
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

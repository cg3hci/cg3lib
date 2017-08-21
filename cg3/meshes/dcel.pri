DEFINES += CG3_DCEL_DEFINED
CONFIG += CG3_DCEL
MODULES += CG3_DCEL

!contains(DEFINES, CG3_CORE_DEFINED){
    error(dcel module requires cg3_core!)
}

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
    $$PWD/dcel/dcel_iterators_inline.cpp \
    $$PWD/dcel/dcel_vertex_iterators_inline.cpp \
    $$PWD/dcel/dcel_inline.cpp \
    $$PWD/dcel/dcel_face_iterators_inline.cpp \
    $$PWD/dcel/dcel_vertex_inline.cpp \
    $$PWD/dcel/dcel_face_inline.cpp \
    $$PWD/dcel/dcel_half_edge_inline.cpp \
    $$PWD/dcel/algorithms/dcel_algorithms.cpp

#Note: QtCreator always shows this module included, however files included in it are compiled only if Viewer module is included
#CG3_VIEWER{
#    include ($$PWD/dcel/gui/dcelmanager.pri)
#}

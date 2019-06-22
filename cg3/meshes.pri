#
# This file is part of cg3lib: https://github.com/cg3hci/cg3lib
# This Source Code Form is subject to the terms of the GNU GPL 3.0
#
# @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
# @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
#

!contains(DEFINES, CG3_CORE_DEFINED){
    error(Meshes module requires the Core module!)
}

DEFINES += CG3_DCEL_DEFINED
MODULES += CG3_MESHES

HEADERS += \
    $$PWD/meshes/dcel/dcel.h \
    $$PWD/meshes/dcel/dcel_data.h \
    $$PWD/meshes/dcel/dcel_face.h \
    $$PWD/meshes/dcel/dcel_face_iterators.h \
    $$PWD/meshes/dcel/dcel_half_edge.h \
    $$PWD/meshes/dcel/dcel_iterators.h \
    $$PWD/meshes/dcel/dcel_struct.h \
    $$PWD/meshes/dcel/dcel_vertex.h \
    $$PWD/meshes/dcel/dcel_vertex_iterators.h \
    $$PWD/meshes/dcel/algorithms/dcel_algorithms.h  \
    $$PWD/meshes/dcel/algorithms/dcel_bounding_boxes.h \
    $$PWD/meshes/dcel/algorithms/dcel_edge_flip.h \
    $$PWD/meshes/dcel/algorithms/dcel_to_vectors.h \
    $$PWD/meshes/dcel/algorithms/dcel_flooding.h \
    $$PWD/meshes/dcel/algorithms/dcel_coloring.h \
    $$PWD/meshes/dcel/algorithms/dcel_connected_components.h \
    $$PWD/meshes/dcel/algorithms/dcel_robustness.h \
    $$PWD/meshes/dcel/dcel_builder.h \
    $$PWD/meshes/mesh.h

CG3_STATIC {
SOURCES += \
    $$PWD/meshes/dcel/algorithms/dcel_bounding_boxes.cpp \
    $$PWD/meshes/dcel/algorithms/dcel_coloring.cpp \
    $$PWD/meshes/dcel/algorithms/dcel_connected_components.cpp \
    $$PWD/meshes/dcel/algorithms/dcel_edge_flip.cpp \
    $$PWD/meshes/dcel/algorithms/dcel_flooding.cpp \
    $$PWD/meshes/dcel/algorithms/dcel_robustness.cpp \
    $$PWD/meshes/dcel/algorithms/dcel_to_vectors.cpp \
    $$PWD/meshes/dcel/dcel_builder.cpp \
    $$PWD/meshes/dcel/dcel_face.cpp \
    $$PWD/meshes/dcel/dcel_half_edge.cpp \
    $$PWD/meshes/dcel/dcel_struct.cpp \
    $$PWD/meshes/dcel/dcel_vertex.cpp
}

contains(DEFINES, CG3_WITH_EIGEN) {

DEFINES += CG3_EIGENMESH_DEFINED

unix:!macx {
    LIBS += -lboost_system -DBOOST_LOG_DYN_LINK -lboost_log -lboost_thread -lpthread
}

HEADERS += \
    $$PWD/meshes/eigenmesh/simpleeigenmesh.h \
    $$PWD/meshes/eigenmesh/eigenmesh.h \
    $$PWD/meshes/eigenmesh/algorithms/eigenmesh_algorithms.h


SOURCES += \
    $$PWD/meshes/eigenmesh/simpleeigenmesh.cpp \
    $$PWD/meshes/eigenmesh/eigenmesh.cpp \
    $$PWD/meshes/eigenmesh/algorithms/eigenmesh_algorithms.cpp

}

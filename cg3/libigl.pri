#
# This file is part of cg3lib: https://github.com/cg3hci/cg3lib
# This Source Code Form is subject to the terms of the GNU GPL 3.0
#
# @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
# @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
#

LIBIGL_ENV_VARIABLE = $$(LIBIGL_HOME)

isEmpty(LIBIGL_PATH):!isEmpty(LIBIGL_ENV_VARIABLE):exists($$LIBIGL_ENV_VARIABLE) {
    LIBIGL_PATH = $$LIBIGL_ENV_VARIABLE
}

!isEmpty(LIBIGL_PATH):exists($$LIBIGL_PATH) {
    !contains(DEFINES, CG3_EIGENMESH_DEFINED){
        error(Igl module requires Meshes module!)
    }

    DEFINES += CG3_LIBIGL_DEFINED
    MODULES += CG3_LIBIGL

    unix{
        linux:LIBS += -lboost_system -DBOOST_LOG_DYN_LINK -lboost_log -lboost_thread -lpthread
        macx:LIBS += -L/usr/local/lib/ -lboost_system -DBOOST_LOG_DYN_LINK -lboost_log -lboost_thread-mt
        INCLUDEPATH += $$LIBIGL_PATH/include/

        QMAKE_CXXFLAGS += -isystem $$LIBIGL_PATH/include/
    }

    win32{
        #CONFIG += LIBIGL_STATIC #???

        INCLUDEPATH += $$LIBIGL_PATH/include/
        QMAKE_CXXFLAGS += -bigobj
    }

    HEADERS += \
        $$PWD/libigl/libigl.h \
        $$PWD/libigl/booleans.h \
        $$PWD/libigl/connected_components.h \
        $$PWD/libigl/decimate.h \
        $$PWD/libigl/mesh_adjacencies.h \
        $$PWD/libigl/extract_manifold_patches.h \
        $$PWD/libigl/is_edge_manifold.h \
        $$PWD/libigl/is_vertex_manifold.h \
        $$PWD/libigl/remove_duplicate_vertices.h \
        $$PWD/libigl/remove_unreferenced_vertices.h \
        $$PWD/libigl/mesh_distance.h \
        $$PWD/libigl/internal/eigenmesh_libigl_algorithms.h \
        $$PWD/libigl/internal/booleans_algorithms.h

    CG3_STATIC {
    SOURCES += \
        $$PWD/libigl/internal/booleans_algorithms.cpp \
        $$PWD/libigl/internal/eigenmesh_libigl_algorithms_decimation.cpp \
        $$PWD/libigl/internal/eigenmesh_libigl_algorithms_verticesremoval.cpp \
        $$PWD/libigl/internal/eigenmesh_libigl_algorithms_manifoldutilities.cpp \
        $$PWD/libigl/internal/eigenmesh_libigl_algorithms_adjacencies.cpp \
        $$PWD/libigl/internal/eigenmesh_libigl_algorithms_booleans.cpp \
        $$PWD/libigl/internal/eigenmesh_libigl_algorithms_distances.cpp \
        $$PWD/libigl/booleans.cpp \
        $$PWD/libigl/connected_components.cpp \
        $$PWD/libigl/decimate.cpp \
        $$PWD/libigl/extract_manifold_patches.cpp \
        $$PWD/libigl/is_edge_manifold.cpp \
        $$PWD/libigl/is_vertex_manifold.cpp \
        $$PWD/libigl/mesh_adjacencies.cpp \
        $$PWD/libigl/mesh_distance.cpp \
        $$PWD/libigl/remove_duplicate_vertices.cpp \
        $$PWD/libigl/remove_unreferenced_vertices.cpp
    }
}
else {
    message(LibIGL not installed properly!)
}


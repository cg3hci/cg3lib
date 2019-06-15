#
# This file is part of cg3lib: https://github.com/cg3hci/cg3lib
# This Source Code Form is subject to the terms of the GNU GPL 3.0
#
# @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
# @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
#
isEmpty(LIBIGL_PATH) {
    exists($$(LIBIGL_HOME)) {
        LIBIGL_PATH = $$(LIBIGL_HOME)
    }
}

exists($$LIBIGL_PATH) {
    !contains(DEFINES, CG3_EIGENMESH_DEFINED){
        error(Igl module requires Eigenmesh module!)
    }

    DEFINES += CG3_LIBIGL_DEFINED
    MODULES += CG3_LIBIGL

    exists($$(LIBIGL_STATIC_HOME)){
        #comment next line if libigl is not used in static mode
        #CONFIG += LIBIGL_STATIC
    }

    unix:!macx{
        LIBS += -lboost_system -DBOOST_LOG_DYN_LINK -lboost_log -lboost_thread -lpthread
        INCLUDEPATH += $$LIBIGL_PATH/include/

        QMAKE_CXXFLAGS += -isystem $$LIBIGL_PATH/include/

        #newest versions of eigen are not supported by libigl
        USE_LIBIGL_EIGEN {
            INCLUDEPATH -= /usr/include/eigen3
            INCLUDEPATH += $$LIBIGL_PATH/external/eigen/
        }

        LIBIGL_STATIC {
            DEFINES += IGL_STATIC_LIBRARY
            LIBS += -L$$(LIBIGL_STATIC_HOME) -ligl_cgal -ligl
        }
    }

    win32{
        CONFIG += LIBIGL_STATIC

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

    SOURCES += \
        $$PWD/libigl/booleans.tpp\
        $$PWD/libigl/connected_components.tpp \
        $$PWD/libigl/decimate.tpp \
        $$PWD/libigl/mesh_adjacencies.tpp \
        $$PWD/libigl/extract_manifold_patches.tpp \
        $$PWD/libigl/is_edge_manifold.tpp \
        $$PWD/libigl/is_vertex_manifold.tpp \
        $$PWD/libigl/remove_duplicate_vertices.tpp \
        $$PWD/libigl/remove_unreferenced_vertices.tpp \
        $$PWD/libigl/mesh_distance.tpp \
        $$PWD/libigl/internal/booleans_algorithms.cpp \
        $$PWD/libigl/internal/eigenmesh_libigl_algorithms_decimation.cpp \
        $$PWD/libigl/internal/eigenmesh_libigl_algorithms_verticesremoval.cpp \
        $$PWD/libigl/internal/eigenmesh_libigl_algorithms_manifoldutilities.cpp \
        $$PWD/libigl/internal/eigenmesh_libigl_algorithms_adjacencies.cpp \
        $$PWD/libigl/internal/eigenmesh_libigl_algorithms_booleans.cpp \
        $$PWD/libigl/internal/eigenmesh_libigl_algorithms_distances.cpp
}

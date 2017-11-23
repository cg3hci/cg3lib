exists($$(LIBIGL_HOME)){
    DEFINES += CG3_LIBIGL_DEFINED
    CONFIG += CG3_LIBIGL
    MODULES += CG3_LIBIGL

    exists($$(LIBIGL_STATIC_HOME)){
        #comment next line if libigl is not used in static mode
        #CONFIG += LIBIGL_STATIC
    }

    !contains(DEFINES, CG3_CORE_DEFINED){
        error(Igl module requires cg3_core!)
    }

    unix:!macx{
        LIBS += -lboost_system -DBOOST_LOG_DYN_LINK -lboost_log -lboost_thread -lpthread
        INCLUDEPATH += $$(LIBIGL_HOME)/include/

        QMAKE_CXXFLAGS += -isystem $$(LIBIGL_HOME)/include/

        #newest versions of eigen are not supported by libigl
        USE_LIBIGL_EIGEN {
            INCLUDEPATH -= /usr/include/eigen3
            INCLUDEPATH += $$(LIBIGL_HOME)/external/nanogui/ext/eigen/
        }

        LIBIGL_STATIC {
            DEFINES += IGL_STATIC_LIBRARY
            LIBS += -L$$(LIBIGL_STATIC_HOME) -ligl_cgal -ligl
        }
    }

    HEADERS += \
        $$PWD/libigl/libigl.h \
        $$PWD/libigl/booleans.h \
        $$PWD/libigl/connected_components.h \
        $$PWD/libigl/decimate.h \
        $$PWD/libigl/extract_manifold_patches.h \
        $$PWD/libigl/face_adjacences.h \
        $$PWD/libigl/is_edge_manifold.h \
        $$PWD/libigl/is_vertex_manifold.h \
        $$PWD/libigl/remove_duplicate_vertices.h \
        $$PWD/libigl/remove_unreferenced_vertices.h \
        $$PWD/libigl/internal/eigenmesh_libigl_algorithms.h

    SOURCES += \
        $$PWD/libigl/booleans.tpp\
        $$PWD/libigl/connected_components.tpp \
        $$PWD/libigl/decimate.tpp \
        $$PWD/libigl/extract_manifold_patches.tpp \
        $$PWD/libigl/face_adjacences.tpp \
        $$PWD/libigl/is_edge_manifold.tpp \
        $$PWD/libigl/is_vertex_manifold.tpp \
        $$PWD/libigl/remove_duplicate_vertices.tpp \
        $$PWD/libigl/remove_unreferenced_vertices.tpp \
        $$PWD/libigl/internal/eigenmesh_libigl_algorithms.cpp
}







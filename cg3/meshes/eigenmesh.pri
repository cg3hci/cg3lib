DEFINES += CG3_EIGENMESH_DEFINED
CONFIG += CG3_EIGENMESH
MODULES += CG3_EIGENMESH

!contains(DEFINES, CG3_CORE_DEFINED){
    error(EigenMesh module requires cg3_core with eigen!)
}

unix:!macx{
    LIBS += -lboost_system -DBOOST_LOG_DYN_LINK -lboost_log -lboost_thread -lpthread
}

exists($$(LIBIGL_HOME)){
    DEFINES += CG3_LIBIGL_DEFINED
    CONFIG += CG3_LIBIGL
    MODULES += CG3_LIBIGL

    exists($$(LIBIGL_STATIC_HOME)){
        #comment next line if libigl is not used in static mode
        #CONFIG += LIBIGL_STATIC
    }

    !contains(DEFINES, CG3_CORE_DEFINED){
        error(Igl module requires common module!)
    }

    unix:!macx{
        LIBS += -lboost_system -DBOOST_LOG_DYN_LINK -lboost_log -lboost_thread -lpthread
        INCLUDEPATH += $$(LIBIGL_HOME)/include/

        #newest versions of eigen are not supported by libigl
        #INCLUDEPATH -= /usr/include/eigen3
        #INCLUDEPATH += $$(LIBIGL_HOME)/external/nanogui/ext/eigen/

        LIBIGL_STATIC {
            DEFINES += IGL_STATIC_LIBRARY
            LIBS += -L$$(LIBIGL_STATIC_HOME) -ligl_cgal -ligl
        }
    }
}

HEADERS += \
    $$PWD/eigenmesh/simpleeigenmesh.h \
    $$PWD/eigenmesh/eigenmesh.h \
    $$PWD/eigenmesh/algorithms/eigenmesh_algorithms.h


SOURCES += \
    $$PWD/eigenmesh/simpleeigenmesh.cpp \
    $$PWD/eigenmesh/eigenmesh.cpp \
    $$PWD/eigenmesh/algorithms/eigenmesh_algorithms.cpp


#Note: QtCreator always shows this module included, however files included in it are compiled only if Viewer module is included
CG3_VIEWER {
    include ($$PWD/eigenmesh/gui/eigenmeshmanager.pri)
    CG3_CGAL {
        CG3_LIBIGL {
            include ($$PWD/eigenmesh/gui/booleansmanager.pri)
        }
    }
}

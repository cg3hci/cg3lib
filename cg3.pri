CONFIG(debug, debug|release){
    DEFINES += DEBUG
}
CONFIG(release, debug|release){
    DEFINES -= DEBUG
    #just uncomment next lines if you want to ignore asserts and got a more optimized binary
    #CONFIG += FINAL_RELEASE
}

CONFIG += c++11

CG3_ALL {
    CONFIG += CG3_CORE CG3_DATA_STRUCTURES CG3_DCEL CG3_EIGENMESH CG3_ALGORITHMS CG3_CGAL CG3_CINOLIB CG3_LIBIGL CG3_VIEWER
}

CG3_CORE {
    include (cg3/core.pri)
}

CG3_DATA_STRUCTURES {
    include (cg3/data_structures.pri)
}

CG3_DCEL {
    include (cg3/meshes/dcel.pri)
}

CG3_EIGENMESH {
    include (cg3/meshes/eigenmesh.pri)
}

CG3_ALGORITHMS {
    include (cg3/algorithms.pri)
}

CG3_CGAL {
    include (cg3/cgal.pri)
}

CG3_CINOLIB {
    include (cg3/cinolib.pri)
}

CG3_LIBIGL {
    include (cg3/libigl.pri)
}

qt {
    CG3_VIEWER {
        include (cg3/viewer.pri)
    }
}

FINAL_RELEASE {
    unix:!macx{
        QMAKE_CXXFLAGS_RELEASE -= -g -O2
        QMAKE_CXXFLAGS += -O3 -DNDEBUG
    }
}

DISTFILES += \
    $$PWD/LICENSE \
    $$PWD/README.md


INCLUDEPATH += $$PWD

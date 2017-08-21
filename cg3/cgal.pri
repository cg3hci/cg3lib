DEFINES += CG3_CGAL_DEFINED
CONFIG += CG3_CGAL
MODULES += CG3_CGAL

!contains(DEFINES, CG3_CORE_DEFINED){
    error(Cgal module requires cg3_core!)
}

PROFILER{
    message(Profiling Configuration)
    DEFINES+=CGAL_DISABLE_ROUNDING_MATH_CHECK=ON
}

unix:!macx{
    LIBS += -lmpfr -lgmp -lCGAL -frounding-math
    LIBS += -lboost_system -DBOOST_LOG_DYN_LINK -lboost_log -lboost_thread -lpthread
}

macx{
    INCLUDEPATH += -I /libs/include/CGAL/
    INCLUDEPATH += -I /libs/include/boost/

    LIBS += -frounding-math
    LIBS += -L/libs/lib/gmp -lgmp
    LIBS += -L/libs/lib/CGAL -lCGAL
    LIBS += -L/libs/lib/boost -lboost_system-mt -DBOOST_LOG_DYN_LINK -lboost_log-mt -lboost_thread-mt -lpthread
    LIBS += -L/libs/lib/mpfr -lmpfr
}

win32{
    INCLUDEPATH += -I "C:/dev/CGAL/include"
    INCLUDEPATH += -I "C:/dev/CGAL/auxiliary/gmp/include"

    INCLUDEPATH += -I "C:/dev/boost/include/boost-1_55/"

    LIBS += -L"C:/dev/CGAL/bin" -lCGAL
    LIBS += -L"C:/dev/CGAL/auxiliary/gmp/lib" -lgmp-10
    LIBS += -L"C:/dev/CGAL/auxiliary/gmp/lib" -lmpfr-4
    LIBS += -frounding-math

    LIBS += -L"C:/dev/boost/lib" -lboost_system-mgw53-mt-1_55
    LIBS += -DBOOST_LOG_DYN_LINK
    LIBS += -L"C:/dev/boost/lib" -lboost_log-mgw53-mt-1_55
    LIBS += -L"C:/dev/boost/lib" -lboost_thread-mgw53-mt-1_55
    LIBS += -lpthread
}

contains(DEFINES, CG3_WITH_EIGEN){
    DEFINES += CGAL_EIGEN3_ENABLED
}

HEADERS += \
    $$PWD/cgal/booleans2d.h \
    $$PWD/cgal/cgal.h \
    $$PWD/cgal/hole_filling.h \
    $$PWD/cgal/sdf.h \
    $$PWD/cgal/signed_distances.h \
    $$PWD/cgal/slicer.h \
    $$PWD/cgal/triangulation.h \
    $$PWD/cgal/polyhedron.h \
    $$PWD/cgal/aabb_tree.h

SOURCES += \
    $$PWD/cgal/booleans2d.cpp \
    $$PWD/cgal/hole_filling.cpp \
    $$PWD/cgal/sdf.cpp \
    $$PWD/cgal/signed_distances.cpp \
    $$PWD/cgal/slicer.cpp \
    $$PWD/cgal/triangulation.cpp \
    $$PWD/cgal/polyhedron.cpp \
    $$PWD/cgal/aabb_tree.cpp


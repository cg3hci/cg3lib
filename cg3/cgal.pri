#
# This file is part of cg3lib: https://github.com/cg3hci/cg3lib
# This Source Code Form is subject to the terms of the GNU GPL 3.0
#
# @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
# @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
#

!contains(DEFINES, CG3_CORE_DEFINED){
    error(Cgal module requires Core module!)
}

unix{
    DEFINES += CG3_CGAL_DEFINED
    MODULES += CG3_CGAL

    macx{
        CONFIG += c++14
        INCLUDEPATH += -I/usr/local/include/
        LIBS += -L/usr/local/lib/
        LIBS += -lboost_system -DBOOST_LOG_DYN_LINK -lboost_log -lboost_thread-mt
    }

    LIBS += -lmpfr -lgmp -frounding-math
    !macx:LIBS += -lCGAL -lCGAL_Core -lboost_system -DBOOST_LOG_DYN_LINK -lboost_log -lboost_thread -lpthread
}

win32{
    contains(DEFINES, CG3_WITH_BOOST){
        CGAL_PATH = C:/libs/CGAL

        CGAL_ENV_VARIABLE = $$(CGAL_HOME)

        !isEmpty(CGAL_ENV_VARIABLE):exists($$CGAL_ENV_VARIABLE) {
            CGAL_PATH = $$CGAL_ENV_VARIABLE
        }

        !isEmpty(BOOST_PATH):exists($$BOOST_PATH) {
            !isEmpty(CGAL_PATH):exists($$CGAL_PATH) {
                DEFINES += CG3_CGAL_DEFINED
                CONFIG += CG3_CGAL
                MODULES += CG3_CGAL

                INCLUDEPATH += -I $$quote($$CGAL_PATH/include)
                INCLUDEPATH += -I $$quote($$CGAL_PATH/auxiliary/gmp/include)



#               ------------- MSVC2017 compiler -------------
#               Library names could change when using different
#               version of MSVC/Boost/CGAL
                CG3_WIN_MSVC {
                    CONFIG(debug, debug|release){
                        LIBS += -L$$quote($$CGAL_PATH/lib) -lCGAL-vc140-mt-gd-4.*
                    }
                    CONFIG(release, debug|release){
                        LIBS += -L$$quote($$CGAL_PATH/lib) -lCGAL-vc140-mt-4.*
                    }

                    LIBS += -L$$quote($$CGAL_PATH/auxiliary/gmp/lib) -llibgmp-10
                    LIBS += -L$$quote($$CGAL_PATH/auxiliary/gmp/lib) -llibmpfr-4

                    CONFIG(debug, debug|release){
                        LIBS += -L$$quote($$BOOST_PATH/lib64-msvc-14.1) -l$$BOOST_PATH/lib64-msvc-14.1/boost_system-vc141-mt-gd-x64*
                        LIBS += -L$$quote($$BOOST_PATH/lib64-msvc-14.1) -l$$BOOST_PATH/lib64-msvc-14.1/boost_log-vc141-mt-gd-x64*
                        LIBS += -L$$quote($$BOOST_PATH/lib64-msvc-14.1) -l$$BOOST_PATH/lib64-msvc-14.1/boost_thread-vc141-mt-gd-x64*
                    }
                    CONFIG(release, debug|release){
                        LIBS += -L$$quote($$BOOS_TPATH/lib64-msvc-14.1) -l$$BOOST_PATH/lib64-msvc-14.1/boost_system-vc141-mt-x64*
                        LIBS += -L$$quote($$BOOST_PATH/lib64-msvc-14.1) -l$$BOOST_PATH/lib64-msvc-14.1/boost_log-vc141-mt-x64*
                        LIBS += -L$$quote($$BOOST_PATH/lib64-msvc-14.1) -l$$BOOST_PATH/lib64-msvc-14.1/boost_thread-vc141-mt-x64*
                    }

                    LIBS += -DBOOST_LOG_DYN_LINK
                    # Cannot find the following libraries in MSVC. TODO: check if they
                    # are required by Windows/MSVC environment
                    #LIBS += -frounding-math
                    #LIBS += -lpthread
                }

#               ------------- MinGW compiler -------------
#               Library names could change when using different version
#               of MinGW/Boost/CGAL
                CG3_WIN_MINGW {
                    LIBS += -L$$quote($$CGAL_PATH/bin) -lCGAL
                    LIBS += -L$$quote($$CGAL_PATH/auxiliary/gmp/lib) -lgmp-10
                    LIBS += -L$$quote($$CGAL_PATH/auxiliary/gmp/lib) -lmpfr-4
                    LIBS += -frounding-math

                    LIBS += -L$$quote($$BOOST_PATH/lib) -lboost_system
                    LIBS += -DBOOST_LOG_DYN_LINK
                    LIBS += -L$$quote($$BOOST_PATH/lib) -lboost_log
                    LIBS += -L$$quote($$BOOST_PATH/lib) -lboost_thread
                    LIBS += -lpthread
                }
            }
        }
    }
}

contains(DEFINES, CG3_CGAL_DEFINED) { #if CGAL was found, depending on the architecture:

    PROFILER{
        message(Profiling Configuration)
        DEFINES+=CGAL_DISABLE_ROUNDING_MATH_CHECK=ON
    }

    contains(DEFINES, CG3_WITH_EIGEN){
        DEFINES += CGAL_EIGEN3_ENABLED
    }

    HEADERS += \
        $$PWD/cgal/cgal.h \
        $$PWD/cgal/aabb_tree3.h \
        $$PWD/cgal/booleans2.h \
        $$PWD/cgal/convex_hull2.h \
        $$PWD/cgal/delaunay_triangulation3.h \
        $$PWD/cgal/hole_filling.h \
        $$PWD/cgal/minimum_bbox2.h \
        $$PWD/cgal/polyhedron.h \
        $$PWD/cgal/sdf.h \
        $$PWD/cgal/segment_intersections2.h \
        $$PWD/cgal/slicer.h \
        $$PWD/cgal/surface_mesh.h \
        $$PWD/cgal/triangulation2.h \
        $$PWD/cgal/triangulation3.h \
        $$PWD/cgal/voronoi2.h \
        $$PWD/cgal/sdf_segmentation.h \
        $$PWD/cgal/skeleton.h

    CG3_STATIC {
    SOURCES += \
        $$PWD/cgal/aabb_tree3.cpp \
        $$PWD/cgal/booleans2.cpp \
        $$PWD/cgal/convex_hull2.cpp \
        $$PWD/cgal/delaunay_triangulation3.cpp \
        $$PWD/cgal/hole_filling.cpp \
        $$PWD/cgal/minimum_bbox2.cpp \
        $$PWD/cgal/polyhedron.cpp \
        $$PWD/cgal/sdf.cpp \
        $$PWD/cgal/segment_intersections2.cpp \
        $$PWD/cgal/slicer.cpp \
        $$PWD/cgal/surface_mesh.cpp \
        $$PWD/cgal/triangulation2.cpp \
        $$PWD/cgal/triangulation3.cpp \
        $$PWD/cgal/voronoi2.cpp \
        $$PWD/cgal/sdf_segmentation.cpp \
        $$PWD/cgal/skeleton.cpp
    }
}
else {
    message(CGAL not installed properly!)
}

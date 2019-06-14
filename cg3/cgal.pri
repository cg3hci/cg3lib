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

unix:!macx{
    DEFINES += CG3_CGAL_DEFINED
    MODULES += CG3_CGAL

    LIBS += -lmpfr -lgmp -lCGAL -frounding-math -lCGAL_Core
    LIBS += -lboost_system -DBOOST_LOG_DYN_LINK -lboost_log -lboost_thread -lpthread
}

macx{
    exists(/libs/include/CGAL/) {
        DEFINES += CG3_CGAL_DEFINED
        CONFIG += CG3_CGAL
        MODULES += CG3_CGAL

        INCLUDEPATH += -I /libs/include/CGAL/

        LIBS += -frounding-math
        LIBS += -L/libs/lib/gmp -lgmp
        LIBS += -L/libs/lib/CGAL -lCGAL -lCGAL_Core
        LIBS += -L/libs/lib/boost -lboost_system-mt -DBOOST_LOG_DYN_LINK -lboost_log-mt -lboost_thread-mt -lpthread
        LIBS += -L/libs/lib/mpfr -lmpfr
    }
}

win32{
    contains(DEFINES, CG3_WITH_BOOST){
        CGALPATH = C:/libs/CGAL
        exists($$(CGAL_HOME)){
            CGALPATH = $$(CGAL_HOME)
        }

        exists($$BOOSTPATH){
            exists($$CGALPATH){
                DEFINES += CG3_CGAL_DEFINED
                CONFIG += CG3_CGAL
                MODULES += CG3_CGAL

                INCLUDEPATH += -I $$quote($$CGALPATH/include)
                INCLUDEPATH += -I $$quote($$CGALPATH/auxiliary/gmp/include)



#               ------------- MSVC2017 compiler -------------
#               Library names could change when using different
#               version of MSVC/Boost/CGAL

#                CONFIG(debug, debug|release){
#                    LIBS += -L$$quote($$CGALPATH/lib) -lCGAL-vc140-mt-gd-4.*
#                }
#                CONFIG(release, debug|release){
#                    LIBS += -L$$quote($$CGALPATH/lib) -lCGAL-vc140-mt-4.*
#                }

#                LIBS += -L$$quote($$CGALPATH/auxiliary/gmp/lib) -llibgmp-10
#                LIBS += -L$$quote($$CGALPATH/auxiliary/gmp/lib) -llibmpfr-4

#                CONFIG(debug, debug|release){
#                    LIBS += -L$$quote($$BOOSTPATH/lib64-msvc-14.1) -l$$BOOSTPATH/lib64-msvc-14.1/boost_system-vc141-mt-gd-x64*
#                    LIBS += -L$$quote($$BOOSTPATH/lib64-msvc-14.1) -l$$BOOSTPATH/lib64-msvc-14.1/boost_log-vc141-mt-gd-x64*
#                    LIBS += -L$$quote($$BOOSTPATH/lib64-msvc-14.1) -l$$BOOSTPATH/lib64-msvc-14.1/boost_thread-vc141-mt-gd-x64*
#                }
#                CONFIG(release, debug|release){
#                    LIBS += -L$$quote($$BOOSTPATH/lib64-msvc-14.1) -l$$BOOSTPATH/lib64-msvc-14.1/boost_system-vc141-mt-x64*
#                    LIBS += -L$$quote($$BOOSTPATH/lib64-msvc-14.1) -l$$BOOSTPATH/lib64-msvc-14.1/boost_log-vc141-mt-x64*
#                    LIBS += -L$$quote($$BOOSTPATH/lib64-msvc-14.1) -l$$BOOSTPATH/lib64-msvc-14.1/boost_thread-vc141-mt-x64*
#                }

#                LIBS += -DBOOST_LOG_DYN_LINK
#               Cannot find the following libraries in MSVC. TODO: check if they
#               are required by Windows/MSVC environment
#                LIBS += -frounding-math
#                LIBS += -lpthread




#               ------------- MinGW compiler -------------
#               Library names could change when using different version
#               of MinGW/Boost/CGAL

                LIBS += -L$$quote($$CGALPATH/bin) -lCGAL
                LIBS += -L$$quote($$CGALPATH/auxiliary/gmp/lib) -lgmp-10
                LIBS += -L$$quote($$CGALPATH/auxiliary/gmp/lib) -lmpfr-4
                LIBS += -frounding-math

                LIBS += -L$$quote($$BOOSTPATH/lib) -lboost_system
                LIBS += -DBOOST_LOG_DYN_LINK
                LIBS += -L$$quote($$BOOSTPATH/lib) -lboost_log
                LIBS += -L$$quote($$BOOSTPATH/lib) -lboost_thread
                LIBS += -lpthread
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
        $$PWD/cgal/voronoi2.h

    SOURCES += \
        $$PWD/cgal/aabb_tree3.cpp \
        $$PWD/cgal/convex_hull2.tpp \
        $$PWD/cgal/booleans2.cpp \
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
        $$PWD/cgal/voronoi2.cpp
}
else {
    message(CGAL not installed properly!)
}

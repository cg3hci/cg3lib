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

    LIBS += -lmpfr -lgmp -lCGAL -frounding-math
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
        LIBS += -L/libs/lib/CGAL -lCGAL
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

                CONFIG(debug, debug|release){
                    LIBS += -L$$quote($$CGALPATH/lib) -lCGAL-vc140-mt-gd-4.10.2
                }
                CONFIG(release, debug|release){
                    LIBS += -L$$quote($$CGALPATH/lib) -lCGAL-vc140-mt-4.10.2
                }

                LIBS += -L$$quote($$CGALPATH/auxiliary/gmp/lib) -llibgmp-10
                LIBS += -L$$quote($$CGALPATH/auxiliary/gmp/lib) -llibmpfr-4

                CONFIG(debug, debug|release){
                    LIBS += -L$$quote($$BOOSTPATH/lib64-msvc-14.1) -lboost_system-vc141-mt-gd-x64-1_66
                    LIBS += -L$$quote($$BOOSTPATH/lib64-msvc-14.1) -lboost_log-vc141-mt-gd-x64-1_66
                    LIBS += -L$$quote($$BOOSTPATH/lib64-msvc-14.1) -lboost_thread-vc141-mt-gd-x64-1_66
                }
                CONFIG(release, debug|release){
                    LIBS += -L$$quote($$BOOSTPATH/lib64-msvc-14.1) -lboost_system-vc141-mt-x64-1_66
                    LIBS += -L$$quote($$BOOSTPATH/lib64-msvc-14.1) -lboost_log-vc141-mt-x64-1_66
                    LIBS += -L$$quote($$BOOSTPATH/lib64-msvc-14.1) -lboost_thread-vc141-mt-x64-1_66
                }

                LIBS += -DBOOST_LOG_DYN_LINK
#               Cannot find the following libraries in MSVC. TODO: check if they
#               are required by Windows/MSVC environment
#                LIBS += -frounding-math
#                LIBS += -lpthread




#               ------------- MinGW compiler -------------
#               Library names could change when using different version
#               of MinGW/Boost/CGAL

#                LIBS += -L$$quote($$CGALPATH/bin) -lCGAL
#                LIBS += -L$$quote($$CGALPATH/auxiliary/gmp/lib) -lgmp-10
#                LIBS += -L$$quote($$CGALPATH/auxiliary/gmp/lib) -lmpfr-4
#                LIBS += -frounding-math

#                LIBS += -L$$quote($$BOOSTPATH/lib) -lboost_system-mgw53-mt-1_55
#                LIBS += -DBOOST_LOG_DYN_LINK
#                LIBS += -L$$quote($$BOOSTPATH/lib) -lboost_log-mgw53-mt-1_55
#                LIBS += -L$$quote($$BOOSTPATH/lib) -lboost_thread-mgw53-mt-1_55
#                LIBS += -lpthread
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
        $$PWD/cgal/cgal_aabbtree.h \
        $$PWD/cgal/cgal_holefilling.h \
        $$PWD/cgal/cgal_polyhedron.h \
        $$PWD/cgal/cgal_sdf.h \
        $$PWD/cgal/cgal_signeddistances.h \
        $$PWD/cgal/cgal_slicer.h \
        $$PWD/cgal/cgal_triangulation.h \
        $$PWD/cgal/2d/cgal_booleans2d.h \
        $$PWD/cgal/2d/cgal_convexhull2d.h \
        $$PWD/cgal/2d/cgal_intersections2d.h \
        $$PWD/cgal/2d/cgal_minimumbbox2d.h \
        $$PWD/cgal/2d/cgal_voronoi2d.h \
        $$PWD/cgal/2d/cgal_triangulation2d.h

    SOURCES += \
        $$PWD/cgal/cgal_aabbtree.cpp \
        $$PWD/cgal/cgal_holefilling.cpp \
        $$PWD/cgal/cgal_polyhedron.cpp \
        $$PWD/cgal/cgal_sdf.cpp \
        $$PWD/cgal/cgal_signeddistances.cpp \
        $$PWD/cgal/cgal_slicer.cpp \
        $$PWD/cgal/cgal_triangulation.cpp \
        $$PWD/cgal/2d/cgal_booleans2d.cpp \
        $$PWD/cgal/2d/cgal_convexhull2d.tpp \
        $$PWD/cgal/2d/cgal_intersections2d.cpp \
        $$PWD/cgal/2d/cgal_minimumbbox2d.cpp \
        $$PWD/cgal/2d/cgal_voronoi2d.cpp \
        $$PWD/cgal/2d/cgal_triangulation2d.cpp
}
else {
    message(CGAL not installed properly!)
}

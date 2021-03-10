CONFIG += CG3_CORE CG3_MESHES CG3_CGAL CG3_LIBIGL CG3_VIEWER_STATIC CG3_VIEWER

#use these on ubuntu 20.04, which has new cgal version
DEFINES += CGAL_HEADER_ONLY
CONFIG += c++14

include(../../cg3.pri)

DEFINES += SOURCE_PATH=$$PWD

SOURCES += main.cpp

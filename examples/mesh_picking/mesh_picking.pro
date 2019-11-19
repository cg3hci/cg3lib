CONFIG += CG3_CORE CG3_MESHES CG3_CGAL CG3_LIBIGL CG3_VIEWER

include(../../cg3.pri)

DEFINES += SOURCE_PATH=$$PWD

SOURCES +=	main.cpp \
    picker.cpp

HEADERS += \
    picker.h


CONFIG += CG3_CORE CG3_VIEWER_STATIC CG3_VIEWER

include(../../cg3.pri)

DEFINES += SOURCE_PATH=$$PWD

SOURCES +=	main.cpp \
    picker.cpp

HEADERS += \
    picker.h


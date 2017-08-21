TEMPLATE         = app
CONFIG          += c++11
CONFIG          += qt opengl
CONFIG          -= app_bundle
MODULES += CINOLIB

macx{
    QMAKE_CXXFLAGS   = -Wno-c++11-extensions
}
INCLUDEPATH     += $$(CINOLIB_HOME) #-> link to cinolib
DEFINES += CINOLIB_DEFINED

HEADERS += \
    $$PWD/cinolib_interface/mesh_conversions.h

SOURCES += \
    $$PWD/cinolib_interface/mesh_conversions.cpp


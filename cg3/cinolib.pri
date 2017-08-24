exists($$(CINOLIB_HOME)){
    DEFINES += CG3_CINOLIB_DEFINED
    CONFIG += CG3_CINOLIB
    MODULES += CG3_CINOLIB

    macx{
        QMAKE_CXXFLAGS   = -Wno-c++11-extensions
    }
    INCLUDEPATH     += $$(CINOLIB_HOME) #-> link to cinolib

    QMAKE_CXXFLAGS += -isystem $$(CINOLIB_HOME) #-> link to cinolib

    HEADERS += \
        $$PWD/cinolib/mesh_conversions.h

    SOURCES += \
        $$PWD/cinolib/mesh_conversions.cpp

}

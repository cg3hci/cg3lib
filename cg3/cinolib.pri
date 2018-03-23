#
# This file is part of cg3lib: https://github.com/cg3hci/cg3lib
# This Source Code Form is subject to the terms of the GNU GPL 3.0
#
# @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
# @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
#

exists($$(CINOLIB_HOME)){
    DEFINES += CG3_CINOLIB_DEFINED
    MODULES += CG3_CINOLIB

    macx{
        QMAKE_CXXFLAGS   = -Wno-c++11-extensions
    }
    INCLUDEPATH     += $$(CINOLIB_HOME)/include/ #-> link to cinolib

    QMAKE_CXXFLAGS += -isystem $$(CINOLIB_HOME) #-> link to cinolib

    HEADERS += \
        $$PWD/cinolib/cinolib_mesh_conversions.h

    SOURCES += \
        $$PWD/cinolib/cinolib_mesh_conversions.cpp

}



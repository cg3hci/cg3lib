#
# This file is part of cg3lib: https://github.com/cg3hci/cg3lib
# This Source Code Form is subject to the terms of the GNU GPL 3.0
#
# @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
# @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
#

CINOLIB_ENV_VARIABLE = $$(CINOLIB_HOME)

isEmpty(CINOLIB_PATH):!isEmpty(CINOLIB_ENV_VARIABLE):exists($$CINOLIB_ENV_VARIABLE) {
    CINOLIB_PATH = $$CINOLIB_ENV_VARIABLE
}

!isEmpty(CINOLIB_PATH):exists($$CINOLIB_PATH) {
    DEFINES += CG3_CINOLIB_DEFINED
    MODULES += CG3_CINOLIB

    macx{
        QMAKE_CXXFLAGS   = -Wno-c++11-extensions
    }
    INCLUDEPATH     += $$CINOLIB_PATH/include/ #-> link to cinolib

    QMAKE_CXXFLAGS += -isystem $$CINOLIB_PATH #-> link to cinolib

    HEADERS += \
        $$PWD/cinolib/cinolib_mesh_conversions.h

    CG3_STATIC {
        SOURCES += \
            $$PWD/cinolib/cinolib_mesh_conversions.cpp
    }
}

#
# This file is part of cg3lib: https://github.com/cg3hci/cg3lib
# This Source Code Form is subject to the terms of the GNU GPL 3.0
#
# @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
# @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
#

VCGLIB_ENV_VARIABLE = $$(VCGLIB_HOME)

isEmpty(VCGLIB_PATH):!isEmpty(VCGLIB_ENV_VARIABLE):exists($$VCGLIB_ENV_VARIABLE) {
    VCGLIB_PATH = $$VCGLIB_ENV_VARIABLE
}

!isEmpty(VCGLIB_PATH):exists($$VCGLIB_PATH) {
    win32{
        QMAKE_CXXFLAGS += -bigobj
    }

    INCLUDEPATH += $$VCGLIB_PATH

    DEFINES += CG3_VCGLIB_DEFINED
    MODULES += CG3_VCGLIB

    HEADERS += \
        $$PWD/vcglib/convert.h \
        $$PWD/vcglib/curve_on_manifold.h \
        $$PWD/vcglib/meshes/triangleedgemeshtype.h \
        $$PWD/vcglib/smoothing.h \
        $$PWD/vcglib/meshes/polygonmeshtype.h \
        $$PWD/vcglib/meshes/trianglemeshtype.h

    CG3_STATIC {
    SOURCES += \
        $$PWD/vcglib/convert.cpp \
        $$PWD/vcglib/curve_on_manifold.cpp \
        $$PWD/vcglib/smoothing.cpp
    }
}
else {
    message("The vcglib folder (variable VCGLIB_PATH) does not exist!")
}

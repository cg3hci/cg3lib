#
# This file is part of cg3lib: https://github.com/cg3hci/cg3lib
# This Source Code Form is subject to the terms of the GNU GPL 3.0
#
# @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
# @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
#
!isEmpty(VCGLIBPATH) {
    exists($$VCGLIBPATH) {
	win32{
	    QMAKE_CXXFLAGS += -bigobj
	}

        INCLUDEPATH += $$VCGLIBPATH

	DEFINES += CG3_VCGLIB_DEFINED
	MODULES += CG3_VCGLIB

        HEADERS += \
            $$PWD/vcglib/meshes/polygonmeshtype.h \
            $$PWD/vcglib/meshes/trianglemeshtype.h

        SOURCES +=
    }
    else {
        message("The vcglib folder (variable VCGLIBPATH) does not exist!")
    }
}
else {
    message("Cannot find vcglib path (variable VCGLIBPATH)!")
}

HEADERS += \
    $$PWD/vcglib/convert.h \
    $$PWD/vcglib/curve_on_manifold.h \
    $$PWD/vcglib/meshes/triangleedgemeshtype.h \
    $$PWD/vcglib/smoothing.h

SOURCES += \
    $$PWD/vcglib/convert.tpp \
    $$PWD/vcglib/curve_on_manifold.tpp \
    $$PWD/vcglib/smoothing.tpp



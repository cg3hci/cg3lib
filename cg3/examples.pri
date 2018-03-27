#
# This file is part of cg3lib: https://github.com/cg3hci/cg3lib
# This Source Code Form is subject to the terms of the GNU GPL 3.0
#
# @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
# @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
#

DEFINES += CG3_EXAMPLES_DEFINED
MODULES += CG3_EXAMPLES

HEADERS += \
    $$PWD/examples/tutorials.h \
    $$PWD/examples/algorithms/convex_hull_3d.h \
    $$PWD/examples/viewer/example_manager.h \
    $$PWD/examples/viewer/adding_manager.h


SOURCES += \
    $$PWD/examples/viewer/example_manager.cpp

FORMS += \
    $$PWD/examples/viewer/example_manager.ui

DISTFILES += \
    $$PWD/examples/algorithms/convex_hull_3d.cpp \
    $$PWD/examples/viewer/adding_manager.cpp



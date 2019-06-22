#
# This file is part of cg3lib: https://github.com/cg3hci/cg3lib
# This Source Code Form is subject to the terms of the GNU GPL 3.0
#
# @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
# @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
#

DEFINES += CG3_DEVELOPMENT_DEFINED
MODULES += CG3_DEVELOPMENT

HEADERS += \
    $$PWD/development/algorithms/marching_cubes.h \
    $$PWD/development/data_structures/lattices/regular_lattice.h \
    $$PWD/development/data_structures/lattices/regular_lattice_iterators.h \
    $$PWD/development/viewer/managers/debugobjects_manager.h

CG3_STATIC {
SOURCES += \
    $$PWD/development/algorithms/marching_cubes.cpp \
    $$PWD/development/data_structures/lattices/regular_lattice.cpp \
    $$PWD/development/data_structures/lattices/regular_lattice_iterators.cpp \
    $$PWD/development/viewer/managers/debugobjects_manager.cpp
}

FORMS += \
    $$PWD/development/viewer/managers/debugobjects_manager.ui

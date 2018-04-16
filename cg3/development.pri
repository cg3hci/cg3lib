#
# This file is part of cg3lib: https://github.com/cg3hci/cg3lib
# This Source Code Form is subject to the terms of the GNU GPL 3.0
#
# @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
# @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
#

DEFINES += CG3_DEVELOPMENT_DEFINED
MODULES += CG3_DEVELOPMENT

# ----- Algorithms -----

HEADERS += \
    $$PWD/development/algorithms/marching_cubes.h

SOURCES += \
    $$PWD/development/algorithms/marching_cubes.cpp

# ----- Lattices -----

HEADERS += \
    $$PWD/development/data_structures/lattices/regular_lattice.h \
    $$PWD/development/data_structures/lattices/regular_lattice_iterators.h

SOURCES += \
    $$PWD/development/data_structures/lattices/regular_lattice.tpp

# ----- Viewer -----
HEADERS += \
    $$PWD/development/viewer/managers/debugobjects_manager.h \
    $$PWD/development/viewer/interfaces/drawable_container.h \

SOURCES += \
    $$PWD/development/viewer/managers/debugobjects_manager.cpp \
    $$PWD/development/viewer/interfaces/drawable_container.tpp

FORMS += \
    $$PWD/development/viewer/managers/debugobjects_manager.ui

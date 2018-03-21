#
# This file is part of cg3lib: https://github.com/cg3hci/cg3lib
# This Source Code Form is subject to the terms of the GNU GPL 3.0
#
# @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
# @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
#

DEFINES += CG3_DEVELOPMENT_DEFINED
CONFIG += CG3_DEVELOPMENT
MODULES += CG3_DEVELOPMENT

HEADERS += \
    $$PWD/development/algorithms/marching_cubes.h

SOURCES += \
    $$PWD/development/algorithms/marching_cubes.cpp

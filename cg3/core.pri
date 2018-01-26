#
# This file is part of cg3lib: https://github.com/cg3hci/cg3lib
# This Source Code Form is subject to the terms of the GNU GPL 3.0
#
# @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
# @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
#

DEFINES += CG3_CORE_DEFINED
CONFIG += CG3_CORE

CONFIG += CG3_OPENMP

include(core/find_boost.pri)
include(core/find_eigen.pri)

win32 {
    DEFINES += _USE_MATH_DEFINES
}

CG3_OPENMP {
    unix:!macx{
        QMAKE_CXXFLAGS += -fopenmp
        QMAKE_LFLAGS += -fopenmp
    }
}

#core
HEADERS += \
    $$PWD/core/cg3/cg3lib.h

#geometry
HEADERS += \
    $$PWD/core/cg3/geometry/bounding_box.h \
    $$PWD/core/cg3/geometry/line.h \
    $$PWD/core/cg3/geometry/plane.h \
    $$PWD/core/cg3/geometry/point.h \
    $$PWD/core/cg3/geometry/segment.h \
    $$PWD/core/cg3/geometry/transformations.h \
    $$PWD/core/cg3/geometry/triangle.h \
    $$PWD/core/cg3/geometry/utils3d.h \
    $$PWD/core/cg3/geometry/2d/bounding_box2d.h \
    $$PWD/core/cg3/geometry/2d/intersections2d.h \
    $$PWD/core/cg3/geometry/2d/line2d.h \
    $$PWD/core/cg3/geometry/2d/point2d.h \
    $$PWD/core/cg3/geometry/2d/segment2d.h \
    $$PWD/core/cg3/geometry/2d/triangle2d.h \
    $$PWD/core/cg3/geometry/2d/utils2d.h

SOURCES += \
    $$PWD/core/cg3/geometry/bounding_box.tpp \
    $$PWD/core/cg3/geometry/line.cpp \
    $$PWD/core/cg3/geometry/plane.cpp \
    $$PWD/core/cg3/geometry/point.tpp \
    $$PWD/core/cg3/geometry/segment.tpp \
    $$PWD/core/cg3/geometry/transformations.cpp \
    $$PWD/core/cg3/geometry/triangle.tpp \
    $$PWD/core/cg3/geometry/utils3d.tpp \
    $$PWD/core/cg3/geometry/2d/bounding_box2d.tpp \
    $$PWD/core/cg3/geometry/2d/intersections2d.cpp \
    $$PWD/core/cg3/geometry/2d/line2d.cpp \
    $$PWD/core/cg3/geometry/2d/point2d.tpp \
    $$PWD/core/cg3/geometry/2d/utils2d.tpp

#io
HEADERS += \
    $$PWD/core/cg3/io/load_save_file.h \
    $$PWD/core/cg3/io/serializable_object.h \
    $$PWD/core/cg3/io/serialize.h \
    $$PWD/core/cg3/io/serialize_eigen.h \
    $$PWD/core/cg3/io/serialize_qt.h

SOURCES += \
    $$PWD/core/cg3/io/load_save_file.tpp \
    $$PWD/core/cg3/io/serialize.tpp \
    $$PWD/core/cg3/io/serialize_eigen.tpp \
    $$PWD/core/cg3/io/serialize_qt.tpp

#utilities
HEADERS += \
    $$PWD/core/cg3/utilities/color.h \
    $$PWD/core/cg3/utilities/comparators.h \
    $$PWD/core/cg3/utilities/const.h \
    $$PWD/core/cg3/utilities/eigen.h \
    $$PWD/core/cg3/utilities/hash.h \
    $$PWD/core/cg3/utilities/map.h \
    $$PWD/core/cg3/utilities/pair.h \
    $$PWD/core/cg3/utilities/set.h \
    $$PWD/core/cg3/utilities/string.h \
    $$PWD/core/cg3/utilities/system.h \
    $$PWD/core/cg3/utilities/timer.h \
    $$PWD/core/cg3/utilities/tokenizer.h \
    $$PWD/core/cg3/utilities/vector.h \
    $$PWD/core/cg3/utilities/utils.h

SOURCES += \
    $$PWD/core/cg3/utilities/color.tpp \
    $$PWD/core/cg3/utilities/eigen.tpp \
    $$PWD/core/cg3/utilities/hash.tpp \
    $$PWD/core/cg3/utilities/map.tpp \
    $$PWD/core/cg3/utilities/pair.tpp \
    $$PWD/core/cg3/utilities/set.tpp \
    $$PWD/core/cg3/utilities/string.tpp \
    $$PWD/core/cg3/utilities/system.tpp \
    $$PWD/core/cg3/utilities/timer.tpp \
    $$PWD/core/cg3/utilities/tokenizer.tpp \
    $$PWD/core/cg3/utilities/vector.tpp \
    $$PWD/core/cg3/utilities/utils.tpp

INCLUDEPATH += $$PWD/core/



#
# This file is part of cg3lib: https://github.com/cg3hci/cg3lib
# This Source Code Form is subject to the terms of the GNU GPL 3.0
#
# @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
# @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
#

DEFINES += CG3_CORE_DEFINED

CONFIG += CG3_OPENMP

include(find_boost.pri)
include(find_eigen.pri)

win32 {
    DEFINES += _USE_MATH_DEFINES
    DEFINES+=NOMINMAX
}

CG3_OPENMP {
    unix:!macx{
        QMAKE_CXXFLAGS += -fopenmp
        QMAKE_LFLAGS += -fopenmp
    }
}

#core
HEADERS += \
    $$PWD/cg3lib.h

#geometry
HEADERS += \
    $$PWD/geometry/bounding_box.h \
    $$PWD/geometry/cylinder.h \
    $$PWD/geometry/line.h \
    $$PWD/geometry/plane.h \
    $$PWD/geometry/point.h \
    $$PWD/geometry/quaternion.h \
    $$PWD/geometry/segment.h \
    $$PWD/geometry/sphere.h \
    $$PWD/geometry/transformations.h \
    $$PWD/geometry/triangle.h \
    $$PWD/geometry/utils3d.h \
    $$PWD/geometry/2d/bounding_box2d.h \
    $$PWD/geometry/2d/intersections2d.h \
    $$PWD/geometry/2d/line2d.h \
    $$PWD/geometry/2d/point2d.h \
    $$PWD/geometry/2d/polygon2d.h \
    $$PWD/geometry/2d/segment2d.h \
    $$PWD/geometry/2d/triangle2d.h \
    $$PWD/geometry/2d/utils2d.h \
    $$PWD/geometry/2d/triangle2d_utils.h

SOURCES += \
    $$PWD/geometry/bounding_box.tpp \
    $$PWD/geometry/cylinder.cpp \
    $$PWD/geometry/line.cpp \
    $$PWD/geometry/plane.cpp \
    $$PWD/geometry/point.tpp \
    $$PWD/geometry/quaternion.cpp \
    $$PWD/geometry/segment.tpp \
    $$PWD/geometry/sphere.cpp \
    $$PWD/geometry/transformations.cpp \
    $$PWD/geometry/triangle.tpp \
    $$PWD/geometry/utils3d.tpp \
    $$PWD/geometry/2d/bounding_box2d.tpp \
    $$PWD/geometry/2d/intersections2d.cpp \
    $$PWD/geometry/2d/line2d.cpp \
    $$PWD/geometry/2d/point2d.tpp \
    $$PWD/geometry/2d/polygon2d.cpp \
    $$PWD/geometry/2d/utils2d.tpp \
    $$PWD/geometry/2d/triangle2d_utils.tpp

#io
HEADERS += \
    $$PWD/io/load_save_file.h \
    $$PWD/io/serializable_object.h \
    $$PWD/io/serialize.h \
    $$PWD/io/serialize_eigen.h \
    $$PWD/io/serialize_qt.h \
    $$PWD/io/serialize_std.h

SOURCES += \
    $$PWD/io/load_save_file.tpp \
    $$PWD/io/serialize.tpp \
    $$PWD/io/serialize_eigen.tpp \
    $$PWD/io/serialize_qt.tpp \
    $$PWD/io/serialize_std.tpp

#utilities
HEADERS += \
    $$PWD/utilities/cg3config.h \
    $$PWD/utilities/color.h \
    $$PWD/utilities/comparators.h \
    $$PWD/utilities/const.h \
    $$PWD/utilities/eigen.h \
    $$PWD/utilities/hash.h \
    $$PWD/utilities/map.h \
    $$PWD/utilities/nested_initializer_lists.h \
    $$PWD/utilities/pair.h \
    $$PWD/utilities/set.h \
    $$PWD/utilities/string.h \
    $$PWD/utilities/system.h \
    $$PWD/utilities/timer.h \
    $$PWD/utilities/tokenizer.h \
    $$PWD/utilities/vector.h \
    $$PWD/utilities/utils.h

SOURCES += \
    $$PWD/utilities/color.tpp \
    $$PWD/utilities/eigen.tpp \
    $$PWD/utilities/hash.tpp \
    $$PWD/utilities/map.tpp \
    $$PWD/utilities/nested_initializer_lists.tpp \
    $$PWD/utilities/pair.tpp \
    $$PWD/utilities/set.tpp \
    $$PWD/utilities/string.tpp \
    $$PWD/utilities/system.tpp \
    $$PWD/utilities/timer.tpp \
    $$PWD/utilities/tokenizer.tpp \
    $$PWD/utilities/vector.tpp \
    $$PWD/utilities/utils.tpp


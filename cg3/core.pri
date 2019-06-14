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
    $$PWD/cg3lib.h \
    $$PWD/geometry/segment3.h \
    $$PWD/geometry/triangle3.h

#geometry
HEADERS += \
    $$PWD/geometry/bounding_box2.h \
    $$PWD/geometry/bounding_box3.h \
    $$PWD/geometry/cylinder.h \
    $$PWD/geometry/intersections2.h \
    $$PWD/geometry/line2.h \
    $$PWD/geometry/line3.h \
    $$PWD/geometry/plane.h \
    $$PWD/geometry/point2.h \
    $$PWD/geometry/point3.h \
    $$PWD/geometry/polygon2.h \
    $$PWD/geometry/quaternion.h \
    $$PWD/geometry/segment.h \
    $$PWD/geometry/segment2.h \
    $$PWD/geometry/sphere.h \
    $$PWD/geometry/transformations3.h \
    $$PWD/geometry/triangle.h \
    $$PWD/geometry/triangle2.h \
    $$PWD/geometry/triangle2_utils.h \
    $$PWD/geometry/utils2.h \
    $$PWD/geometry/utils3.h

SOURCES += \
    $$PWD/geometry/bounding_box2.tpp \
    $$PWD/geometry/bounding_box3.tpp \
    $$PWD/geometry/cylinder.cpp \
    $$PWD/geometry/intersections2.cpp \
    $$PWD/geometry/line2.cpp \
    $$PWD/geometry/line3.cpp \
    $$PWD/geometry/plane.cpp \
    $$PWD/geometry/point2.tpp \
    $$PWD/geometry/point3.tpp \
    $$PWD/geometry/polygon2.cpp \
    $$PWD/geometry/quaternion.cpp \
    $$PWD/geometry/segment.tpp \
    $$PWD/geometry/sphere.cpp \
    $$PWD/geometry/transformations3.cpp \
    $$PWD/geometry/triangle.tpp \
    $$PWD/geometry/triangle2_utils.tpp \
    $$PWD/geometry/utils2.tpp \
    $$PWD/geometry/utils3.tpp

#io
HEADERS += \
    $$PWD/io/file_commons.h \
    $$PWD/io/load_save_obj.h \
    $$PWD/io/load_save_ply.h \
    $$PWD/io/load_save_file.h \
    $$PWD/io/serializable_object.h \
    $$PWD/io/serialize.h \
    $$PWD/io/serialize_eigen.h \
    $$PWD/io/serialize_qt.h \
    $$PWD/io/serialize_std.h \
    $$PWD/io/ply/ply.h \
    $$PWD/io/ply/ply_header.h \
    $$PWD/io/ply/ply_vertex.h \
    $$PWD/io/ply/ply_face.h

SOURCES += \
    $$PWD/io/load_save_obj.tpp \
    $$PWD/io/load_save_ply.tpp \
    $$PWD/io/serialize.tpp \
    $$PWD/io/serialize_eigen.tpp \
    $$PWD/io/serialize_qt.tpp \
    $$PWD/io/serialize_std.tpp \
    $$PWD/io/ply/ply.tpp \
    $$PWD/io/ply/ply_header.cpp \
    $$PWD/io/ply/ply_vertex.tpp \
    $$PWD/io/ply/ply_face.tpp

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


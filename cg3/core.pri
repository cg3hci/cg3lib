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

macx{
	DEFINES += GL_SILENCE_DEPRECATION
}

#core
HEADERS += \
	$$PWD/cg3lib.h \ #core
	$$PWD/geometry/bounding_box2.h \ #geometry
	$$PWD/geometry/bounding_box3.h \
	$$PWD/geometry/cylinder.h \
	$$PWD/geometry/intersections2.h \
	$$PWD/geometry/line2.h \
	$$PWD/geometry/line3.h \
	$$PWD/geometry/plane.h \
	$$PWD/geometry/point2.h \
	$$PWD/geometry/point2.inl \
	$$PWD/geometry/point3.h \
	$$PWD/geometry/point3.inl \
	$$PWD/geometry/polygon2.h \
	$$PWD/geometry/quaternion.h \
	$$PWD/geometry/segment.h \
	$$PWD/geometry/segment.inl \
	$$PWD/geometry/segment2.h \
	$$PWD/geometry/segment3.h \
	$$PWD/geometry/sphere.h \
	$$PWD/geometry/transformations3.h \
	$$PWD/geometry/triangle.h \
	$$PWD/geometry/triangle.inl \
	$$PWD/geometry/triangle2.h \
	$$PWD/geometry/triangle2_utils.h \
	$$PWD/geometry/triangle2_utils.inl \
	$$PWD/geometry/triangle3.h \
	$$PWD/geometry/utils2.h \
	$$PWD/geometry/utils2.inl \
	$$PWD/geometry/utils3.h \
	$$PWD/geometry/utils3.inl \
	$$PWD/io/file_commons.h \ #io
	$$PWD/io/load_save_obj.h \
	$$PWD/io/load_save_obj.inl \
	$$PWD/io/load_save_ply.h \
	$$PWD/io/load_save_ply.inl \ 
	$$PWD/io/load_save_file.h \
	$$PWD/io/serializable_object.h \
	$$PWD/io/serialize.h \
	$$PWD/io/serialize.inl \
	$$PWD/io/serialize_eigen.h \
	$$PWD/io/serialize_eigen.inl \
	$$PWD/io/serialize_qt.h \
	$$PWD/io/serialize_qt.inl \
	$$PWD/io/serialize_std.h \
	$$PWD/io/serialize_std.inl \
	$$PWD/io/ply/ply.h \
	$$PWD/io/ply/ply.inl \
	$$PWD/io/ply/ply_header.h \
	$$PWD/io/ply/ply_edge.h \
	$$PWD/io/ply/ply_edge.inl \
	$$PWD/io/ply/ply_face.h \
	$$PWD/io/ply/ply_face.inl \
	$$PWD/io/ply/ply_vertex.h \
	$$PWD/io/ply/ply_vertex.inl \
	$$PWD/utilities/cg3_config_folder.h \ #utilities
	$$PWD/utilities/color.h \
	$$PWD/utilities/command_line_argument_manager.h \
	$$PWD/utilities/command_line_argument_manager.inl \
	$$PWD/utilities/comparators.h \
	$$PWD/utilities/const.h \
	$$PWD/utilities/eigen.h \
	$$PWD/utilities/hash.h \
	$$PWD/utilities/hash.inl \
	$$PWD/utilities/map.h \
	$$PWD/utilities/map.inl \
	$$PWD/utilities/nested_initializer_lists.h \
	$$PWD/utilities/nested_initializer_lists.inl \
	$$PWD/utilities/pair.h \
	$$PWD/utilities/pair.inl \
	$$PWD/utilities/set.h \
	$$PWD/utilities/set.inl \
	$$PWD/utilities/string.h \
	$$PWD/utilities/string.inl \
	$$PWD/utilities/system.h \
	$$PWD/utilities/system.inl \
	$$PWD/utilities/timer.h \
	$$PWD/utilities/timer.inl \
	$$PWD/utilities/tokenizer.h \
	$$PWD/utilities/tokenizer.inl \
	$$PWD/utilities/vector.h \
	$$PWD/utilities/vector.inl \
	$$PWD/utilities/utils.h \
	$$PWD/utilities/utils.inl

CG3_STATIC {
SOURCES += \
	$$PWD/geometry/bounding_box3.cpp \ #geometry
	$$PWD/geometry/bounding_box2.cpp \
	$$PWD/geometry/cylinder.cpp \
	$$PWD/geometry/intersections2.cpp \
	$$PWD/geometry/line2.cpp \
	$$PWD/geometry/line3.cpp \
	$$PWD/geometry/plane.cpp \
	$$PWD/geometry/polygon2.cpp \
	$$PWD/geometry/quaternion.cpp \
	$$PWD/geometry/sphere.cpp \
	$$PWD/geometry/transformations3.cpp \ #io
	$$PWD/io/ply/ply_header.cpp \
	$$PWD/utilities/color.cpp \ #utilities
	$$PWD/utilities/eigen.cpp 
}

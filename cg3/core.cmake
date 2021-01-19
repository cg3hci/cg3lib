#
# This file is part of cg3lib: https://github.com/cg3hci/cg3lib
# This Source Code Form is subject to the terms of the GNU GPL 3.0
#
# @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
# @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
#

if (CG3_STATIC)
	SET(CG3_CORE_HEADERS
		${CMAKE_CURRENT_LIST_DIR}/cg3lib.h #core
		${CMAKE_CURRENT_LIST_DIR}/geometry/bounding_box2.h #geometry
		${CMAKE_CURRENT_LIST_DIR}/geometry/bounding_box3.h
		${CMAKE_CURRENT_LIST_DIR}/geometry/cylinder.h
		${CMAKE_CURRENT_LIST_DIR}/geometry/intersections2.h
		${CMAKE_CURRENT_LIST_DIR}/geometry/line2.h
		${CMAKE_CURRENT_LIST_DIR}/geometry/line3.h
		${CMAKE_CURRENT_LIST_DIR}/geometry/plane.h
		${CMAKE_CURRENT_LIST_DIR}/geometry/point2.h
		${CMAKE_CURRENT_LIST_DIR}/geometry/point2.inl
		${CMAKE_CURRENT_LIST_DIR}/geometry/point3.h
		${CMAKE_CURRENT_LIST_DIR}/geometry/point3.inl
		${CMAKE_CURRENT_LIST_DIR}/geometry/polygon2.h
		${CMAKE_CURRENT_LIST_DIR}/geometry/quaternion.h
		${CMAKE_CURRENT_LIST_DIR}/geometry/segment.h
		${CMAKE_CURRENT_LIST_DIR}/geometry/segment.inl
		${CMAKE_CURRENT_LIST_DIR}/geometry/segment2.h
		${CMAKE_CURRENT_LIST_DIR}/geometry/segment3.h
		${CMAKE_CURRENT_LIST_DIR}/geometry/sphere.h
		${CMAKE_CURRENT_LIST_DIR}/geometry/transformations3.h
		${CMAKE_CURRENT_LIST_DIR}/geometry/triangle.h
		${CMAKE_CURRENT_LIST_DIR}/geometry/triangle.inl
		${CMAKE_CURRENT_LIST_DIR}/geometry/triangle2.h
		${CMAKE_CURRENT_LIST_DIR}/geometry/triangle2_utils.h
		${CMAKE_CURRENT_LIST_DIR}/geometry/triangle2_utils.inl
		${CMAKE_CURRENT_LIST_DIR}/geometry/triangle3.h
		${CMAKE_CURRENT_LIST_DIR}/geometry/utils2.h
		${CMAKE_CURRENT_LIST_DIR}/geometry/utils2.inl
		${CMAKE_CURRENT_LIST_DIR}/geometry/utils3.h
		${CMAKE_CURRENT_LIST_DIR}/geometry/utils3.inl
		${CMAKE_CURRENT_LIST_DIR}/io/file_commons.h #io
		${CMAKE_CURRENT_LIST_DIR}/io/load_save_obj.h
		${CMAKE_CURRENT_LIST_DIR}/io/load_save_obj.inl
		${CMAKE_CURRENT_LIST_DIR}/io/load_save_ply.h
		${CMAKE_CURRENT_LIST_DIR}/io/load_save_ply.inl
		${CMAKE_CURRENT_LIST_DIR}/io/load_save_file.h
		${CMAKE_CURRENT_LIST_DIR}/io/serializable_object.h
		${CMAKE_CURRENT_LIST_DIR}/io/serialize.h
		${CMAKE_CURRENT_LIST_DIR}/io/serialize.inl
		${CMAKE_CURRENT_LIST_DIR}/io/serialize_eigen.h
		${CMAKE_CURRENT_LIST_DIR}/io/serialize_eigen.inl
		${CMAKE_CURRENT_LIST_DIR}/io/serialize_qt.h
		${CMAKE_CURRENT_LIST_DIR}/io/serialize_qt.inl
		${CMAKE_CURRENT_LIST_DIR}/io/serialize_std.h
		${CMAKE_CURRENT_LIST_DIR}/io/serialize_std.inl
		${CMAKE_CURRENT_LIST_DIR}/io/ply/ply.h
		${CMAKE_CURRENT_LIST_DIR}/io/ply/ply.inl
		${CMAKE_CURRENT_LIST_DIR}/io/ply/ply_header.h
		${CMAKE_CURRENT_LIST_DIR}/io/ply/ply_edge.h
		${CMAKE_CURRENT_LIST_DIR}/io/ply/ply_edge.inl
		${CMAKE_CURRENT_LIST_DIR}/io/ply/ply_face.h
		${CMAKE_CURRENT_LIST_DIR}/io/ply/ply_face.inl
		${CMAKE_CURRENT_LIST_DIR}/io/ply/ply_vertex.h
		${CMAKE_CURRENT_LIST_DIR}/io/ply/ply_vertex.inl
		${CMAKE_CURRENT_LIST_DIR}/utilities/cg3_config_folder.h #utilities
		${CMAKE_CURRENT_LIST_DIR}/utilities/color.h
		${CMAKE_CURRENT_LIST_DIR}/utilities/command_line_argument_manager.h
		${CMAKE_CURRENT_LIST_DIR}/utilities/command_line_argument_manager.inl
		${CMAKE_CURRENT_LIST_DIR}/utilities/comparators.h
		${CMAKE_CURRENT_LIST_DIR}/utilities/const.h
		${CMAKE_CURRENT_LIST_DIR}/utilities/eigen.h
		${CMAKE_CURRENT_LIST_DIR}/utilities/eigen.inl
		${CMAKE_CURRENT_LIST_DIR}/utilities/hash.h
		${CMAKE_CURRENT_LIST_DIR}/utilities/hash.inl
		${CMAKE_CURRENT_LIST_DIR}/utilities/map.h
		${CMAKE_CURRENT_LIST_DIR}/utilities/map.inl
		${CMAKE_CURRENT_LIST_DIR}/utilities/nested_initializer_lists.h
		${CMAKE_CURRENT_LIST_DIR}/utilities/nested_initializer_lists.inl
		${CMAKE_CURRENT_LIST_DIR}/utilities/pair.h
		${CMAKE_CURRENT_LIST_DIR}/utilities/pair.inl
		${CMAKE_CURRENT_LIST_DIR}/utilities/set.h
		${CMAKE_CURRENT_LIST_DIR}/utilities/set.inl
		${CMAKE_CURRENT_LIST_DIR}/utilities/string.h
		${CMAKE_CURRENT_LIST_DIR}/utilities/string.inl
		${CMAKE_CURRENT_LIST_DIR}/utilities/system.h
		${CMAKE_CURRENT_LIST_DIR}/utilities/system.inl
		${CMAKE_CURRENT_LIST_DIR}/utilities/timer.h
		${CMAKE_CURRENT_LIST_DIR}/utilities/timer.inl
		${CMAKE_CURRENT_LIST_DIR}/utilities/tokenizer.h
		${CMAKE_CURRENT_LIST_DIR}/utilities/tokenizer.inl
		${CMAKE_CURRENT_LIST_DIR}/utilities/vector.h
		${CMAKE_CURRENT_LIST_DIR}/utilities/vector.inl
		${CMAKE_CURRENT_LIST_DIR}/utilities/utils.h
		${CMAKE_CURRENT_LIST_DIR}/utilities/utils.inl)

	SET(CG3_CORE_SOURCES
		${CMAKE_CURRENT_LIST_DIR}/geometry/bounding_box3.cpp #geometry
		${CMAKE_CURRENT_LIST_DIR}/geometry/bounding_box2.cpp
		${CMAKE_CURRENT_LIST_DIR}/geometry/cylinder.cpp
		${CMAKE_CURRENT_LIST_DIR}/geometry/intersections2.cpp
		${CMAKE_CURRENT_LIST_DIR}/geometry/line2.cpp
		${CMAKE_CURRENT_LIST_DIR}/geometry/line3.cpp
		${CMAKE_CURRENT_LIST_DIR}/geometry/plane.cpp
		${CMAKE_CURRENT_LIST_DIR}/geometry/polygon2.cpp
		${CMAKE_CURRENT_LIST_DIR}/geometry/quaternion.cpp
		${CMAKE_CURRENT_LIST_DIR}/geometry/sphere.cpp
		${CMAKE_CURRENT_LIST_DIR}/geometry/transformations3.cpp #io
		${CMAKE_CURRENT_LIST_DIR}/io/ply/ply_header.cpp
		${CMAKE_CURRENT_LIST_DIR}/utilities/color.cpp #utilities
		)

add_library(cg3-core SHARED ${CG3_CORE_HEADERS} ${CG3_CORE_SOURCES})

endif()

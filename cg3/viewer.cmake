#
# This file is part of cg3lib: https://github.com/cg3hci/cg3lib
# This Source Code Form is subject to the terms of the GNU GPL 3.0
#
# @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
# @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
#

if (CG3_STATIC)
	set(CMAKE_AUTOMOC ON)
	set(CMAKE_AUTOUIC ON)
	set(CMAKE_AUTORCC ON)
	
	add_definitions(-DCG3_VIEWER_DEFINED)

	set(CG3_VIEWER_HEADERS
		${CMAKE_CURRENT_LIST_DIR}/viewer/viewer.h
		${CMAKE_CURRENT_LIST_DIR}/viewer/glcanvas.h
		${CMAKE_CURRENT_LIST_DIR}/viewer/mainwindow.h
		${CMAKE_CURRENT_LIST_DIR}/viewer/drawable_objects/drawable_arrow3.h
		${CMAKE_CURRENT_LIST_DIR}/viewer/drawable_objects/drawable_bounding_box2.h
		${CMAKE_CURRENT_LIST_DIR}/viewer/drawable_objects/drawable_bounding_box3.h
		${CMAKE_CURRENT_LIST_DIR}/viewer/drawable_objects/drawable_cylinder.h
		${CMAKE_CURRENT_LIST_DIR}/viewer/drawable_objects/drawable_mixed_objects.h
		${CMAKE_CURRENT_LIST_DIR}/viewer/drawable_objects/drawable_objects_container.h
		${CMAKE_CURRENT_LIST_DIR}/viewer/drawable_objects/drawable_objects_container.inl
		${CMAKE_CURRENT_LIST_DIR}/viewer/drawable_objects/drawable_point2.h
		${CMAKE_CURRENT_LIST_DIR}/viewer/drawable_objects/drawable_point3.h
		${CMAKE_CURRENT_LIST_DIR}/viewer/drawable_objects/drawable_polygon2.h
		${CMAKE_CURRENT_LIST_DIR}/viewer/drawable_objects/drawable_segment2.h
		${CMAKE_CURRENT_LIST_DIR}/viewer/drawable_objects/drawable_segment3.h
		${CMAKE_CURRENT_LIST_DIR}/viewer/drawable_objects/drawable_sphere.h
		${CMAKE_CURRENT_LIST_DIR}/viewer/drawable_objects/drawable_plane.h
		${CMAKE_CURRENT_LIST_DIR}/viewer/drawable_objects/drawable_triangle3.h
		${CMAKE_CURRENT_LIST_DIR}/viewer/interfaces/abstract_mainwindow.h
		${CMAKE_CURRENT_LIST_DIR}/viewer/interfaces/drawable_container.h
		${CMAKE_CURRENT_LIST_DIR}/viewer/interfaces/drawable_object.h
		${CMAKE_CURRENT_LIST_DIR}/viewer/interfaces/manipulable_object.h
		${CMAKE_CURRENT_LIST_DIR}/viewer/interfaces/pickable_object.h
		${CMAKE_CURRENT_LIST_DIR}/viewer/interfaces/drawable_mesh.h
		${CMAKE_CURRENT_LIST_DIR}/viewer/opengl_objects/opengl_objects2.h
		${CMAKE_CURRENT_LIST_DIR}/viewer/opengl_objects/opengl_objects2.inl
		${CMAKE_CURRENT_LIST_DIR}/viewer/opengl_objects/opengl_objects3.h
		${CMAKE_CURRENT_LIST_DIR}/viewer/opengl_objects/opengl_objects3.inl
		${CMAKE_CURRENT_LIST_DIR}/viewer/utilities/loadersaver.h
		${CMAKE_CURRENT_LIST_DIR}/viewer/utilities/console_stream.h
		${CMAKE_CURRENT_LIST_DIR}/viewer/utilities/utils.h
		${CMAKE_CURRENT_LIST_DIR}/viewer/widgets/qclickablelabel.h
		${CMAKE_CURRENT_LIST_DIR}/viewer/internal/drawable_mesh_drawlist_manager.h
		${CMAKE_CURRENT_LIST_DIR}/viewer/internal/drawable_container_drawlist_manager.h
		${CMAKE_CURRENT_LIST_DIR}/viewer/internal/drawable_object_drawlist_manager.h
		${CMAKE_CURRENT_LIST_DIR}/viewer/internal/manipulable_object_drawlist_manager.h
		${CMAKE_CURRENT_LIST_DIR}/viewer/internal/submanager.h)

	set(CG3_VIEWER_SOURCES
		${CMAKE_CURRENT_LIST_DIR}/viewer/glcanvas.cpp
		${CMAKE_CURRENT_LIST_DIR}/viewer/mainwindow.cpp
		${CMAKE_CURRENT_LIST_DIR}/viewer/drawable_objects/drawable_arrow3.cpp
		${CMAKE_CURRENT_LIST_DIR}/viewer/drawable_objects/drawable_bounding_box2.cpp
		${CMAKE_CURRENT_LIST_DIR}/viewer/drawable_objects/drawable_bounding_box3.cpp
		${CMAKE_CURRENT_LIST_DIR}/viewer/drawable_objects/drawable_cylinder.cpp
		${CMAKE_CURRENT_LIST_DIR}/viewer/drawable_objects/drawable_mixed_objects.cpp
		${CMAKE_CURRENT_LIST_DIR}/viewer/drawable_objects/drawable_plane.cpp
		${CMAKE_CURRENT_LIST_DIR}/viewer/drawable_objects/drawable_point2.cpp
		${CMAKE_CURRENT_LIST_DIR}/viewer/drawable_objects/drawable_point3.cpp
		${CMAKE_CURRENT_LIST_DIR}/viewer/drawable_objects/drawable_polygon2.cpp
		${CMAKE_CURRENT_LIST_DIR}/viewer/drawable_objects/drawable_segment2.cpp
		${CMAKE_CURRENT_LIST_DIR}/viewer/drawable_objects/drawable_segment3.cpp
		${CMAKE_CURRENT_LIST_DIR}/viewer/drawable_objects/drawable_sphere.cpp
		${CMAKE_CURRENT_LIST_DIR}/viewer/drawable_objects/drawable_triangle3.cpp
		${CMAKE_CURRENT_LIST_DIR}/viewer/interfaces/drawable_container.cpp
		${CMAKE_CURRENT_LIST_DIR}/viewer/interfaces/drawable_mesh.cpp
		${CMAKE_CURRENT_LIST_DIR}/viewer/interfaces/manipulable_object.cpp
		${CMAKE_CURRENT_LIST_DIR}/viewer/interfaces/pickable_object.cpp
		${CMAKE_CURRENT_LIST_DIR}/viewer/internal/drawable_container_drawlist_manager.cpp
		${CMAKE_CURRENT_LIST_DIR}/viewer/internal/drawable_mesh_drawlist_manager.cpp
		${CMAKE_CURRENT_LIST_DIR}/viewer/internal/drawable_object_drawlist_manager.cpp
		${CMAKE_CURRENT_LIST_DIR}/viewer/internal/manipulable_object_drawlist_manager.cpp
		${CMAKE_CURRENT_LIST_DIR}/viewer/utilities/console_stream.cpp
		${CMAKE_CURRENT_LIST_DIR}/viewer/utilities/loadersaver.cpp
		${CMAKE_CURRENT_LIST_DIR}/viewer/utilities/utils.cpp
		${CMAKE_CURRENT_LIST_DIR}/viewer/widgets/qclickablelabel.cpp
		)

	set(CG3_VIEWER_FORMS
		${CMAKE_CURRENT_LIST_DIR}/viewer/mainwindow.ui
		${CMAKE_CURRENT_LIST_DIR}/viewer/internal/drawable_mesh_drawlist_manager.ui
		${CMAKE_CURRENT_LIST_DIR}/viewer/internal/drawable_container_drawlist_manager.ui
		${CMAKE_CURRENT_LIST_DIR}/viewer/internal/drawable_object_drawlist_manager.ui
		${CMAKE_CURRENT_LIST_DIR}/viewer/internal/manipulable_object_drawlist_manager.ui)

	set(CG3_VIEWER_RESOURCES
		${CMAKE_CURRENT_LIST_DIR}/viewer/internal/icons/icons.qrc)
	
	set(CG3_VIEWER_LINK_LIBS
		cg3-core 
		${QGLVIEWER_LIBRARY}
		Qt5::Core
		Qt5::OpenGL
		Qt5::Widgets
		Qt5::Xml)
	
	if (TARGET cg3-meshes)
		list(APPEND CG3_VIEWER_HEADERS
			${CMAKE_CURRENT_LIST_DIR}/viewer/drawable_objects/drawable_dcel.h
			${CMAKE_CURRENT_LIST_DIR}/viewer/pickable_objects/pickable_dcel.h
			${CMAKE_CURRENT_LIST_DIR}/viewer/managers/dcel_manager.h)

		list(APPEND CG3_VIEWER_SOURCES
			${CMAKE_CURRENT_LIST_DIR}/viewer/drawable_objects/drawable_dcel.cpp
			${CMAKE_CURRENT_LIST_DIR}/viewer/managers/dcel_manager.cpp
			${CMAKE_CURRENT_LIST_DIR}/viewer/pickable_objects/pickable_dcel.cpp)

		list(APPEND CG3_VIEWER_FORMS
			${CMAKE_CURRENT_LIST_DIR}/viewer/managers/dcel_manager.ui)
		
		if(TARGET Eigen3::Eigen)
			list(APPEND CG3_VIEWER_HEADERS
				${CMAKE_CURRENT_LIST_DIR}/viewer/drawable_objects/drawable_eigenmesh.h
				${CMAKE_CURRENT_LIST_DIR}/viewer/pickable_objects/pickable_eigenmesh.h
				${CMAKE_CURRENT_LIST_DIR}/viewer/managers/eigenmesh_manager.h)
	
			list(APPEND CG3_VIEWER_SOURCES
				${CMAKE_CURRENT_LIST_DIR}/viewer/drawable_objects/drawable_eigenmesh.cpp
				${CMAKE_CURRENT_LIST_DIR}/viewer/managers/eigenmesh_manager.cpp
				${CMAKE_CURRENT_LIST_DIR}/viewer/pickable_objects/pickable_eigenmesh.cpp)
	
			list(APPEND CG3_VIEWER_FORMS
				${CMAKE_CURRENT_LIST_DIR}/viewer/managers/eigenmesh_manager.ui)
			
			if (TARGET cg3-cgal AND TARGET cg3-libigl)
				list(APPEND CG3_VIEWER_HEADERS
					${CMAKE_CURRENT_LIST_DIR}/viewer/managers/booleans_manager.h)
				
				list(APPEND CG3_VIEWER_SOURCES
					${CMAKE_CURRENT_LIST_DIR}/viewer/managers/booleans_manager.cpp)
				
				list(APPEND CG3_VIEWER_FORMS
					${CMAKE_CURRENT_LIST_DIR}/viewer/managers/booleans_manager.ui)
				
				list(APPEND CG3_VIEWER_LINK_LIBS cg3-cgal cg3-libigl)
			endif()
		endif()
		
		list(APPEND CG3_VIEWER_LINK_LIBS cg3-meshes)
	endif()
	
	if (TARGET cg3-cinolib)
		add_definitions(-DCINOLIB_USES_OPENGL)
		add_definitions(-DCINOLIB_USES_QT)
		add_definitions(-DGL_GLEXT_PROTOTYPES)
		
		list(APPEND CG3_VIEWER_HEADERS
			${CMAKE_CURRENT_LIST_DIR}/viewer/drawable_objects/drawable_tetmesh.h)
		
		list(APPEND CG3_VIEWER_SOURCES
			${CMAKE_CURRENT_LIST_DIR}/viewer/drawable_objects/drawable_tetmesh.cpp)
		
		list(APPEND CG3_VIEWER_LINK_LIBS GL GLU cg3-cinolib)
	endif()
	
	add_library(
		cg3-viewer SHARED 
		${CG3_VIEWER_HEADERS} ${CG3_VIEWER_SOURCES} ${CG3_VIEWER_FORMS} ${CG3_VIEWER_RESOURCES})
	
	target_link_libraries(
		cg3-viewer PUBLIC 
			${CG3_VIEWER_LINK_LIBS})
endif()

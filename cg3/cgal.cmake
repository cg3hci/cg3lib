#
# This file is part of cg3lib: https://github.com/cg3hci/cg3lib
# This Source Code Form is subject to the terms of the GNU GPL 3.0
#
# @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
# @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
#

if (TARGET Eigen3::Eigen)
	add_definitions(-DCGAL_EIGEN3_ENABLED)
endif()

if (CG3_STATIC)
	add_definitions(-DCG3_CGAL_DEFINED)
	
	set(CG3_CGAL_HEADERS
		${CMAKE_CURRENT_LIST_DIR}/cgal/cgal.h 
		${CMAKE_CURRENT_LIST_DIR}/cgal/aabb_tree3.h 
		${CMAKE_CURRENT_LIST_DIR}/cgal/booleans2.h 
		${CMAKE_CURRENT_LIST_DIR}/cgal/convex_hull2.h
		${CMAKE_CURRENT_LIST_DIR}/cgal/convex_hull2.inl
		${CMAKE_CURRENT_LIST_DIR}/cgal/delaunay_triangulation3.h 
		${CMAKE_CURRENT_LIST_DIR}/cgal/hole_filling.h 
		${CMAKE_CURRENT_LIST_DIR}/cgal/minimum_bbox2.h 
		${CMAKE_CURRENT_LIST_DIR}/cgal/polyhedron.h 
		${CMAKE_CURRENT_LIST_DIR}/cgal/polyhedron.inl
		${CMAKE_CURRENT_LIST_DIR}/cgal/sdf.h 
		${CMAKE_CURRENT_LIST_DIR}/cgal/segment_intersections2.h 
		${CMAKE_CURRENT_LIST_DIR}/cgal/slicer.h 
		${CMAKE_CURRENT_LIST_DIR}/cgal/surface_mesh.h 
		${CMAKE_CURRENT_LIST_DIR}/cgal/triangulation2.h 
		${CMAKE_CURRENT_LIST_DIR}/cgal/triangulation3.h 
		${CMAKE_CURRENT_LIST_DIR}/cgal/voronoi2.h 
		${CMAKE_CURRENT_LIST_DIR}/cgal/sdf_segmentation.h 
		${CMAKE_CURRENT_LIST_DIR}/cgal/skeleton.h)
	
	set(CG3_CGAL_SOURCES
		${CMAKE_CURRENT_LIST_DIR}/cgal/aabb_tree3.cpp 
		${CMAKE_CURRENT_LIST_DIR}/cgal/booleans2.cpp 
		${CMAKE_CURRENT_LIST_DIR}/cgal/delaunay_triangulation3.cpp 
		${CMAKE_CURRENT_LIST_DIR}/cgal/hole_filling.cpp 
		${CMAKE_CURRENT_LIST_DIR}/cgal/minimum_bbox2.cpp 
		${CMAKE_CURRENT_LIST_DIR}/cgal/sdf.cpp 
		${CMAKE_CURRENT_LIST_DIR}/cgal/segment_intersections2.cpp 
		${CMAKE_CURRENT_LIST_DIR}/cgal/slicer.cpp 
		${CMAKE_CURRENT_LIST_DIR}/cgal/surface_mesh.cpp 
		${CMAKE_CURRENT_LIST_DIR}/cgal/triangulation2.cpp 
		${CMAKE_CURRENT_LIST_DIR}/cgal/triangulation3.cpp 
		${CMAKE_CURRENT_LIST_DIR}/cgal/voronoi2.cpp 
		${CMAKE_CURRENT_LIST_DIR}/cgal/sdf_segmentation.cpp 
		${CMAKE_CURRENT_LIST_DIR}/cgal/skeleton.cpp)
	
	add_library(
		cg3-cgal SHARED 
		${CG3_CGAL_HEADERS} ${CG3_CGAL_SOURCES})
	
	target_link_libraries(
		cg3-cgal
		PUBLIC 
			cg3-core cg3-data-structures cg3-meshes mpfr gmp)
	
	list(APPEND CG3_LINK_LIBRARIES cg3-cgal gmp)
endif()


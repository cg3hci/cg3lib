if (CG3_STATIC)
	add_definitions(-DCG3_CINOLIB_DEFINED)
	
	SET(CG3_CINOLIB_HEADERS
		${CMAKE_CURRENT_LIST_DIR}//cinolib/cinolib_mesh_conversions.h)
	
	SET(CG3_CINOLIB_SOURCES
		${CMAKE_CURRENT_LIST_DIR}//cinolib/cinolib_mesh_conversions.cpp)
	
	add_library(
		cg3-cinolib SHARED 
		${CG3_CINOLIB_HEADERS} ${CG3_CINOLIB_SOURCES})
	
	target_link_libraries(
		cg3-cinolib
		PUBLIC 
			cg3-core cg3-data-structures cg3-meshes)
endif()

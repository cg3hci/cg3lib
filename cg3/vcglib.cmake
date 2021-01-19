if (CG3_STATIC)
	add_definitions(-DCG3_VCGLIB_DEFINED)

	SET(CG3_VCGLIB_HEADERS
		)

	SET(CG3_VCGLIB_SOURCES
		)

	add_library(
		cg3-vcglib SHARED
		${CG3_VCGLIB_HEADERS} ${CG3_VCGLIB_SOURCES})

	target_link_libraries(
		cg3-vcglib
		PUBLIC
			cg3-core cg3-data-structures cg3-meshes)
endif()

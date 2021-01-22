if (CG3_STATIC)
	list(APPEND CG3_MODULE_DEFINITIONS CG3_STATIC)
endif()

if (TARGET cg3-core)
	target_compile_definitions(cg3-core ${CG3_TARGET_MOD} ${CG3_MODULE_DEFINITIONS})
endif()

if (TARGET cg3-cgal)
	target_compile_definitions(cg3-cgal ${CG3_TARGET_MOD} ${CG3_MODULE_DEFINITIONS})
endif()

if (TARGET cg3-cinolib)
	target_compile_definitions(cg3-cinolib ${CG3_TARGET_MOD} ${CG3_MODULE_DEFINITIONS})
endif()

if (TARGET cg3-data-structures)
	target_compile_definitions(cg3-data-structures ${CG3_TARGET_MOD} ${CG3_MODULE_DEFINITIONS})
endif()

if (TARGET cg3-libigl)
	target_compile_definitions(cg3-libigl ${CG3_TARGET_MOD} ${CG3_MODULE_DEFINITIONS})
endif()

if (TARGET cg3-meshes)
	target_compile_definitions(cg3-meshes ${CG3_TARGET_MOD} ${CG3_MODULE_DEFINITIONS})
endif()

if (TARGET cg3-vcglib)
	target_compile_definitions(cg3-vcglib ${CG3_TARGET_MOD} ${CG3_MODULE_DEFINITIONS})
endif()

if (TARGET cg3-viewer)
	target_compile_definitions(cg3-viewer PUBLIC ${CG3_MODULE_DEFINITIONS})
endif()

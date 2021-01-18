cmake_minimum_required(VERSION 3.9)
project(cg3lib)

find_package(Qt5
	COMPONENTS
	Core)
find_package(Eigen3)

option(CG3_STATIC "" ON)

option(CG3_CORE "" ON)
option(CG3_DATA_STRUCTURES "" ON)
option(CG3_MESHES "" ON)
option(CG3_ALGORITHMS "" ON)
option(CG3_CGAL "" ON)
option(CG3_CINOLIB "" ON)
option(CG3_LIBIGL "" ON)
option(CG3_VCGLIB "" ON)
option(CG3_VORO++ "" ON)
option(CG3_VIEWER "" ON)

if (CG3_CORE)
	include(${CMAKE_CURRENT_SOURCE_DIR}/cg3/core.cmake)
endif()

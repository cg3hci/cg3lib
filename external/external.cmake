list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules/")

##### Looking for libraries that may be used with cg3lib
##### and may be already installed

#Eigen
find_package(Eigen3)

#QGLViewer (will look also for Qt)
find_package(QGLViewer)

#CGAL
set(CGAL_DO_NOT_WARN_ABOUT_CMAKE_BUILD_TYPE TRUE)
find_package(CGAL)


#Eigen
if (TARGET Eigen3::Eigen)
	add_definitions(-DCG3_WITH_EIGEN)
	message(STATUS "- Eigen - using system-provided library")
	set(CG3_EIGEN_FOUND TRUE)
elseif(EXISTS "${CMAKE_CURRENT_LIST_DIR}/eigen/Eigen")
	add_definitions(-DCG3_WITH_EIGEN)
	add_library(Eigen3::Eigen INTERFACE)
	target_include_directories(Eigen3::Eigen INTERFACE ${CMAKE_CURRENT_LIST_DIR}/eigen/Eigen)
	message(STATUS "- Eigen - using bundled library")
	set(CG3_EIGEN_FOUND TRUE)
else()
	message(STATUS "- Eigen not found.")
	message(STATUS "  - Eigen is required by cg3lib. Install Eigen library or")
	message(STATUS "  - clone cg3lib recursively.")
	return()
endif()

#CGAL
if (TARGET CGAL::CGAL)
	message(STATUS "- CGAL - using system-provided library")
	set(CG3_CGAL_FOUND TRUE)
else()
	message(STATUS "- CGAL not found.")
	message(STATUS "  - To use the CGAL module of cg3lib, you first neeed to install CGAL.")
	message(STATUS "  - CGAL module will not be built.")
endif()

#CinoLib
if (DEFINED ENV{CINOLIB_HOME})
	message(STATUS "- cinolib - using CINOLIB_HOME env variable")
	set(CINOLIB_DIR "$ENV{CINOLIB_HOME}/include/")
	set(CG3_CINOLIB_FOUND TRUE)
elseif(EXISTS "${CMAKE_CURRENT_LIST_DIR}/cinolib/include")
	message(STATUS "- cinolib - using bundled source")
	set(CINOLIB_DIR ${CMAKE_CURRENT_LIST_DIR}/cinolib/include)
	set(CG3_CINOLIB_FOUND TRUE)
else()
	message(STATUS "- cinolib not found.")
	message(STATUS "  - To use the cinolib module of cg3lib, clone cg3lib recursively.")
endif()
if (CG3_CINOLIB_FOUND)
	add_library(cinolib INTERFACE)
	target_include_directories(cinolib INTERFACE ${CINOLIB_DIR})
	target_link_libraries(cinolib INTERFACE GL GLU)
endif()

#LibIGL
if (DEFINED ENV{LIBIGL_HOME})
	message(STATUS "- LibIGL - using LIBIGL_HOME env variable")
	set(LIBIGL_DIR "$ENV{LIBIGL_HOME}/include/")
	set(CG3_LIBIGL_FOUND TRUE)
elseif(EXISTS "${CMAKE_CURRENT_LIST_DIR}/libigl/include")
	message(STATUS "- LibIGL - using bundled source")
	set(LIBIGL_DIR ${CMAKE_CURRENT_LIST_DIR}/libigl/include)
	set(CG3_LIBIGL_FOUND TRUE)
else()
	message(STATUS "- libigl not found.")
	message(STATUS "  - To use the libigl module of cg3lib, clone cg3lib recursively.")
endif()
if (CG3_LIBIGL_FOUND)
	add_library(libigl INTERFACE)
	target_include_directories(libigl INTERFACE ${LIBIGL_DIR})
endif()

#VCGLib
if (DEFINED ENV{VCGLIB_HOME})
	message(STATUS "- VCGLib - using VCGLIB_HOME env variable")
	set(VCGLIB_DIR $ENV{VCGLIB_HOME})
	set(CG3_VCGLIB_FOUND TRUE)
elseif(EXISTS "${CMAKE_CURRENT_LIST_DIR}/vcglib/vcg")
	message(STATUS "- VCGLib - using bundled source")
	set(VCGLIB_DIR${CMAKE_CURRENT_LIST_DIR}/vcglib)
	set(CG3_VCGLIB_FOUND TRUE)
else()
	message(STATUS "- VCGLib not found.")
	message(STATUS "  - To use the VCGLib module of cg3lib, clone cg3lib recursively.")
endif()
if (CG3_VCGLIB_FOUND)
	add_library(vcglib INTERFACE)
	target_include_directories(vcglib INTERFACE ${VCGLIB_DIR})
endif()

#QGLViewer
if (DEFINED QGLVIEWER_LIBRARY_RELEASE)
	add_library(QGLViewer INTERFACE)
	target_link_libraries(QGLViewer INTERFACE ${QGLVIEWER_LIBRARY})
	message(STATUS "- QGLViewer - using system-provided library")
	set(CG3_QGLVIEWER_FOUND TRUE)
else()
	message(STATUS "- QGLViewer not found.")
	message(STATUS "  - To use the viewer module of cg3lib, you first neeed to install QGLViewer.")
	#todo
endif()

#Voro++
if (DEFINED ENV{VOROPLUSPLUS_HOME})
	message(STATUS "- Voro++ - using VOROPLUSPLUS_HOME env variable")
	include_directories($ENV{VOROPLUSPLUS_HOME})
	set(CG3_VORO_FOUND TRUE)
else()
	message(STATUS "- Voro++ not found.")
	#todo
endif()

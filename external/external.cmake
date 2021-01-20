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


##### Setting libraries to be used with cg3lib

#Eigen
if (TARGET Eigen3::Eigen)
	add_definitions(-DCG3_WITH_EIGEN)
	include_directories(${EIGEN3_INCLUDE_DIR})
	message(STATUS "- Eigen - using system-provided library")
elseif(EXISTS "${CMAKE_CURRENT_LIST_DIR}/eigen/Eigen")
	add_definitions(-DCG3_WITH_EIGEN)
	include_directories(${CMAKE_CURRENT_LIST_DIR}/eigen/Eigen)
	message(STATUS "- Eigen - using bundled library")
else()
	message(STATUS "- Eigen not found.")
	message(STATUS "  - Eigen is not required by cg3lib, but strongly suggested.")
	message(STATUS "  - Clone cg3lib recursively to use eigen features with cg3lib.")
endif()

#CGAL
if (TARGET CGAL::CGAL)
	message(STATUS "- CGAL - using system-provided library")
else()
	message(STATUS "- CGAL not found.")
	message(STATUS "  - To use the CGAL module of cg3lib, you first neeed to install CGAL.")
	message(STATUS "  - CGAL module will not be built.")
endif()

#CinoLib
if (DEFINED ENV{CINOLIB_HOME})
	message(STATUS "- cinolib - using CINOLIB_HOME env variable")
	include_directories("$ENV{CINOLIB_HOME}/include/")
elseif(EXISTS "${CMAKE_CURRENT_LIST_DIR}/cinolib/include")
	message(STATUS "- cinolib - using bundled source")
	include_directories(${CMAKE_CURRENT_LIST_DIR}/cinolib/include)
else()
	message(STATUS "- cinolib not found.")
	message(STATUS "  - To use the cinolib module of cg3lib, clone cg3lib recursively.")
endif()

#LibIGL
if (DEFINED ENV{LIBIGL_HOME})
	message(STATUS "- LibIGL - using LIBIGL_HOME env variable")
	include_directories("$ENV{LIBIGL_HOME}/include/")
elseif(EXISTS "${CMAKE_CURRENT_LIST_DIR}/libigl/include")
	message(STATUS "- LibIGL - using bundled source")
	include_directories(${CMAKE_CURRENT_LIST_DIR}/libigl/include)
else()
	message(STATUS "- libigl not found.")
	message(STATUS "  - To use the libigl module of cg3lib, clone cg3lib recursively.")
endif()

#VCGLib
if (DEFINED ENV{VCGLIB_HOME})
	message(STATUS "- VCGLib - using VCGLIB_HOME env variable")
	include_directories($ENV{VCGLIB_HOME})
elseif(EXISTS "${CMAKE_CURRENT_LIST_DIR}/vcglib/vcg")
	message(STATUS "- VCGLib - using bundled source")
	include_directories(${CMAKE_CURRENT_LIST_DIR}/vcglib)
else()
	message(STATUS "- VCGLib not found.")
	message(STATUS "  - To use the VCGLib module of cg3lib, clone cg3lib recursively.")
endif()

#QGLViewer
if (DEFINED QGLVIEWER_LIBRARY_RELEASE)
	message(STATUS "- QGLViewer - using system-provided library")
else()
	message(STATUS "- QGLViewer not found.")
	message(STATUS "  - To use the viewer module of cg3lib, you first neeed to install QGLViewer.")
	#todo
endif()

#Voro++
if (DEFINED ENV{VOROPLUSPLUS_HOME})
	message(STATUS "- Voro++ - using VOROPLUSPLUS_HOME env variable")
	include_directories($ENV{VOROPLUSPLUS_HOME})
else()
	message(STATUS "- Voro++ not found.")
	#todo
endif()

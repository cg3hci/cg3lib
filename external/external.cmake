list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules/")

##### Looking for libraries that may be used with cg3lib
##### and may be already installed

#Eigen
find_package(Eigen3)

#Qt
find_package(Qt5 COMPONENTS Core Xml OpenGL Gui Widgets)

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
endif()

#CGAL
if (TARGET CGAL::CGAL)
	message(STATUS "- CGAL - using system-provided library")
else()
	#todo
endif()

#CinoLib
if (DEFINED ENV{CINOLIB_HOME})
	message(STATUS "- cinolib - using CINOLIB_HOME env variable")
	include_directories("$ENV{CINOLIB_HOME}/include/")
else()
	message(STATUS "- cinolib - using bundled source")
	#todo
endif()

#LibIGL
if (DEFINED ENV{LIBIGL_HOME})
	message(STATUS "- LibIGL - using LIBIGL_HOME env variable")
	include_directories("$ENV{LIBIGL_HOME}/include/")
else()
	message(STATUS "- LibIGL - using bundled source")
	#todo
endif()

#VCGLib
if (DEFINED ENV{VCGLIB_HOME})
	message(STATUS "- VCGLib - using VCGLIB_HOME env variable")
	include_directories($ENV{VCGLIB_HOME})
else()
	message(STATUS "- VCGLib - using bundled source")
	#todo
endif()

#QGLViewer
if (DEFINED QGLVIEWER_LIBRARY_RELEASE)
	message(STATUS "- QGLViewer - using system-provided library")
else()
	message(STATUS "- QGLViewer - using bundled source")
	#todo
endif()

#Voro++
if (DEFINED ENV{VOROPLUSPLUS_HOME})
	message(STATUS "- Voro++ - using VOROPLUSPLUS_HOME env variable")
	include_directories($ENV{VOROPLUSPLUS_HOME})
else()
	message(STATUS "- Voro++ - using bundled source")
	#todo
endif()

#Qt
find_package(Qt5
	COMPONENTS
	Core
	Gui
	OpenGL
	Xml
	Widgets)

#Eigen
find_package(Eigen3)
if (TARGET Eigen3::Eigen)
	add_definitions(-DCG3_WITH_EIGEN)
	include_directories(${EIGEN3_INCLUDE_DIR})
endif()

#CGAL
set(CGAL_DO_NOT_WARN_ABOUT_CMAKE_BUILD_TYPE TRUE)
find_package(CGAL)
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

#OpenGL
find_package(OpenGL)
find_package(QGLViewer)

#Voro++
if (DEFINED ENV{VOROPLUSPLUS_HOME})
	message(STATUS "- Voro++ - using VOROPLUSPLUS_HOME env variable")
	include_directories($ENV{VOROPLUSPLUS_HOME})
else()
	message(STATUS "- Voro++ - using bundled source")
	#todo
endif()

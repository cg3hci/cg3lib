/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_CG3LIB_H
#define CG3_CG3LIB_H

/**
  * @link: https://stackoverflow.com/questions/11124895/suppress-compiler-warning-function-declared-never-referenced
  * @def CG3_SUPPRESS_WARNING(a)
  * @brief CG3_SUPPRESS_WARNING allows to suppress an "unused variable" warning.
  */
#define CG3_SUPPRESS_WARNING(a) (void)a

/**
  * @link: https://stackoverflow.com/questions/20631922/expand-macro-inside-string-literal
  * @def CG3_STRINGIFY(X)
  * @brief CG3_STRINGIFY expands a macro inside a literal string.
  * Example:\n
  * \code{.cpp}
  * CG3_STRINGIFY(M_PI); //-> "3.14159265358979323846"
  * \endcode
  */
#define CG3_STRINGIFY2(X) #X
#define CG3_STRINGIFY(X) CG3_STRINGIFY2(X)

/**
  * @mainpage cg3lib
  *
  * # Introduction
  *
  * Cg3Lib is a C++ geometry processing library developed by the CG3HCI Group
  * of the University of Cagliari. It is composed of different modules:
  *
  * - Core: it provides some basic data structures (Point, BoundingBox...),
  * parsers for saving and loading multiple mesh formats and utilities;
  * - Meshes: some Mesh data structures which help to manage easily 3D meshes;
  * - Data Structures: some generic (not necessarily geometric) data structures
  * like arrays, trees, graphs;
  * - Algorithms: a collection of geometry processing and computetional geometry
  * algorithms;
  * - Viewer: a 3D viewer developed with Qt and based on libQGLViewer
  * (https://libqglviewer.com/): it allows to render easily mesh data
  * structures and to create easyly guis (drag&drop with QtCreator);
  * - Cgal: a simple interface which allows to use some CGAL functionalities
  * (https://www.cgal.org/);
  * - LibIGL: a simple interface which allows to use some LibIGL functionalities
  * (https://libigl.github.io/libigl/);
  * - CinoLib: a simple interface which allows to use some CinoLib functionalities
  * (https://github.com/maxicino/cinolib);
  *
  * All these modules are optional (except of the core module) and the project can
  * be compiled on Windows, MacOS and Linux.
  */

/**
  * @defgroup cg3core Core Module
  *
  * @brief The cg3lib Core module provides some basic functions and data structures
  */

#if __cplusplus >= 201300
#define CG3_CPP14
#endif

#ifdef CG3_STATIC
#define CG3_INLINE
#else //CG3_STATIC
#define CG3_INLINE inline
#endif //CG3_STATIC


//try to include libraries iff the library is purely header only (no qmake)
#ifndef CG3_QMAKE

#define CG3_CORE_DEFINED
#define CG3_ALGORITHMS_DEFINED
#define CG3_DATA_STRUCTURES_DEFINED
#define CG3_DCEL_DEFINED

#ifdef __has_include //try to include libraries that can be included in CG3

#if __has_include("Eigen/Core")
#define CG3_WITH_EIGEN
#define CG3_EIGENMESH_DEFINED
#endif //has include eigen

#if __has_include("boost/version.hpp")
#define CG3_WITH_BOOST
#endif //has include boost

#if __has_include("igl/igl_inline.h")
#define CG3_LIBIGL_DEFINED
#endif //has include libigl

#if __has_include("cinolib/cino_inline.h")
#define CG3_CINOLIB_DEFINED
#endif //has include cinolib

#if __has_include("vcg/complex/complex.h")
#define CG3_VCGLIB_DEFINED
#endif //has include vcg

#endif //__has_include
#endif //CG3_QMAKE

#endif // CG3_CG3LIB_H

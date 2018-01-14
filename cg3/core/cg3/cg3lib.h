/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_CG3LIB_H
#define CG3_CG3LIB_H

#if __cplusplus >= 201300
#define CG3_CPP14
#endif

/**
  * @mainpage cg3lib
  *
  * Cg3Lib is a C++ geometry processing library developed by the CG3HCI Group of the University of Cagliari. It is composed of different modules:
  *
  * - Core: it provides some basic data structures (Point, BoundingBox...), parsers for saving and loading multiple mesh formats, utilities and generic data structures;
  * - Meshes: some Mesh data structures which help to manage easily 3D meshes;
  * - Viewer: a 3D viewer developed with Qt and based on libQGLViewer (https://libqglviewer.com/): it allows to render easily mesh data structures and to create easyly guis (drag&drop with QtCreator);
  * - Cgal: a simple interface which allows to use some CGAL functionalities (https://www.cgal.org/);
  * - LibIGL: a simple interface which allows to use some LibIGL functionalities (https://libigl.github.io/libigl/);
  * - CinoLib: a simple interface which allows to use some CinoLib functionalities (https://github.com/maxicino/cinolib);
  *
  * All these modules are optional (except of the core module) and the project can be compiled on Windows, MacOS and Linux.
  * To install all the necessary libraries on ubuntu based linux distributions just exectute "install.sh".
  */

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

#endif // CG3_CG3LIB_H

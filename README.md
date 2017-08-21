# cg3lib

Cg3Lib is a C++ geometry processing library developed by the CG3HCI Group of the University of Cagliari.
It is composed of different modules:
- Core: it provides some basic data structures (Point, BoundingBox...), parsers for saving and loading multiple mesh formats, utilities and generic data structures;
- Meshes: some Mesh data structures which help to manage easily 3D meshes;
- Viewer: a 3D viewer developed with Qt and based on libQGLViewer (http://libqglviewer.com/): it allows to render easily mesh data structures and to create easyly guis (drag&drop with QtCreator);
- Cgal: a simple interface which allows to use some CGAL functionalities (https://www.cgal.org/);
- LibIGL: a simple interface which allows to use some LibIGL functionalities (http://libigl.github.io/libigl/);
- CinoLib: a simple interface which allows to use some CinoLib functionalities (https://bitbucket.org/maxicino/cinolib/overview);

All these modules are optional (except of the core module) and the project can be compiled on Windows, MacOS and Linux.
To install all the necessary libraries on ubuntu based linux distributions just exectute "install.sh".



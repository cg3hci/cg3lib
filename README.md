# cg3lib

[![Actions Status](https://github.com/cg3hci/cg3lib/workflows/UbuntuExamples/badge.svg)](https://github.com/cg3hci/cg3lib/actions)

[![Actions Status](https://github.com/cg3hci/cg3lib/workflows/MacOSExamples/badge.svg)](https://github.com/cg3hci/cg3lib/actions)

Cg3Lib is a C++ geometry processing library developed by the CG3HCI Group of the University of Cagliari.
It is composed of different modules:
- Core: it provides some basic data structures (Point, BoundingBox...), parsers for saving and loading multiple mesh formats and utilities;
- Meshes: some Mesh data structures which help to manage easily 3D meshes;
- Data Structures: some generic (not necessarily geometric) data structures like arrays, trees, graphs;
- Algorithms: a collection of geometry processing and computetional geometry algorithms;
- Viewer: a 3D viewer developed with Qt and based on libQGLViewer (http://libqglviewer.com/): it allows to render easily mesh data structures and to create easyly guis (drag&drop with QtCreator);
- Cgal: a simple interface which allows to use some CGAL functionalities (https://www.cgal.org/);
- Voro++: a simple 3D Voronoi Data structures computed using the voro++ library (http://math.lbl.gov/voro++/)
- LibIGL: a simple interface which allows to use some LibIGL functionalities (http://libigl.github.io/libigl/);
- CinoLib: a simple interface which allows to use some CinoLib functionalities (https://github.com/mlivesu/cinolib);
- VCGLib: a simple interface which allows to use some VCGLib functionalities (https://github.com/cnr-isti-vclab/vcglib)

All these modules are optional (except of the core module) and the project can be compiled on Windows, MacOS and Linux.
The documentation can be found at the following link: https://cg3hci.github.io/index.html.


## Installation
### MacOS
```
git clone https://github.com/cg3hci/cg3lib.git
bash cg3lib/install_macos.sh
```

### Ubuntu
```
git clone https://github.com/cg3hci/cg3lib.git
bash cg3lib/install_ubuntu.sh
```
## Usage
Look at the examples in the "examples" folder inside the repo.

Compiling the examples:
```
cd cg3lib/examples
qmake
make
```

## Citation

If you use cg3lib in your research projects, please cite the our library using this BibTeX entry:

```
@misc{cg3lib,
	title  = {{CG3Lib}: A {C++} geometry processing library.},
	author = {Alessandro Muntoni and Stefano Nuvoli and others},
	note   = {https://github.com/cg3hci/cg3lib},
	year   = {2018},
}
```

[ToDo list](TODO.md)

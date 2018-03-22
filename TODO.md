# Major
- [ ] Complete this ToDo list :sweat_smile:
- [ ] Make the library header only (at least for modules without dependencies)
- [ ] Create CMake configuration files in order to double support qmake and cmake
- [ ] Improve MainWindow GUI
- [ ] Manage multiple pickable objects drawn in the Canvas
- [ ] Unify Meshes data structures under single abstract class
- [ ] Add a brief explanation of the content of headers containing functions (no classes)
- [ ] Support LibIGL module with MSVC

# Minor
- All
  - [ ] Replace Triangle area formulas with Heron's formula
- Style
  - [ ] Naming of files which are interface to an external library: keep the name of the library (i.e. cgal) or remove it (i.e. libigl)
  - [ ] Follow the linux kernel coding style everywhere (https://www.kernel.org/doc/html/v4.10/process/coding-style.html)
- Data Structure:
  - [ ] BipartiteGraph inherits from Graph (can it?)
- Meshes:
  - [ ] Reorganize EigenMeshAlgorithms
  - [ ] Put Dcel and EigenMesh under a module called Meshes
  - [ ] viewer/interfaces becames viewer/abstract_classes
  - [ ] viewer/renderable_objects becames viewer/opengl_functions

# To Implement
- Algorithms:
  - [ ] Marching Cubes
  - [ ] Taubin Smoothing
  - [ ] Extract SubGraph from Graphs

# Missing Abstract Classes Inheritance
- Data Structures:
  - [ ] graphs/graph from SerializableObject
  - [ ] all the trees from SerializableObject

# Missing Documentation
- All:
  - [ ] Examples of usages of the classes
- Core:
  - [ ] geometry/2d/line2d
  - [ ] geometry/line
  - [ ] geometry/plane
  - [ ] geometry/segment
  - [ ] geometry/triangle

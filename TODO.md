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
  - [ ] Naming of files which are interface to an external library: remove the name of the library (cgal)
  - [ ] Follow the linux kernel coding style everywhere (https://www.kernel.org/doc/html/v4.10/process/coding-style.html)
- Data Structure:
  - [ ] BipartiteGraph inherits from Graph (can it?)
- Meshes:
  - [ ] Reorganize EigenMeshAlgorithms
  - [ ] Put Dcel and EigenMesh under a module called Meshes
  - [ ] viewer/interfaces becames viewer/abstract_classes
  - [ ] viewer/renderable_objects becames viewer/opengl_functions
- Viewer:
  - [ ] GLCanvas becames a private class of the MainWindow
- CGAL:
  - [ ] Booleans 2D: transform vector of point in container of point for polygons
  - [ ] Voronoi 2D: insert on the diagram the inf edges (intersections with a built bounding box)

# To Implement
- Algorithms:
  - [ ] Marching Cubes
  - [ ] Taubin Smoothing
  - [ ] Extract SubGraph from Graphs
  - [ ] Johnson's Algorithm for Circuit enumeraiton
- Cgal:
  - [ ] Polyhedron to Dcel conversion
  - [ ] SurfaceMesh to Dcel conversion
  - [ ] SurfaceMesh from/to EigenMesh conversion

# Missing Abstract Classes Inheritance
- Data Structures:
  - [ ] graphs/graph from SerializableObject
  - [ ] all the trees from SerializableObject

# Missing Documentation
- All:
  - [ ] Examples of usages of the classes
  - [ ] Organize Module pages
    - [ ] Core Module
    - [ ] Algorithms Module
    - [ ] CGAL Module
    - [ ] CinoLib Module
    - [ ] Data Structures Module
    - [ ] Meshes Module
    - [ ] LibIGL Module
    - [ ] Viewer Module
  - [ ] Write example of creation of a Manager for the mainWindow
- Core:
  - [ ] geometry/2d/line2d
  - [ ] geometry/line
  - [ ] geometry/plane
  - [ ] geometry/segment
  - [ ] geometry/triangle
- Data Structures:
  - [ ] arrays/array
- LibIGL:
  - [ ] connected components
  - [ ] decimate
  - [ ] extract manifold patches
  - [ ] face adjacences
  - [ ] is edge manifold
  - [ ] is vertex manifold
  - [ ] mesh distance
  - [ ] remove duplicate vertices
  - [ ] remove unreferenced vertices
  - [ ] vertex adjacences

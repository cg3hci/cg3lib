/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_EIGENMESH_LIBIGL_ALGORITHMS_H
#define CG3_EIGENMESH_LIBIGL_ALGORITHMS_H

#include <cg3/meshes/eigenmesh/eigenmesh.h>

#include "booleans_algorithms.h"

namespace cg3 {
namespace libigl {
namespace internal {

class EigenMeshLibIglAlgorithms {

public:

    /* Decimation */
    static SimpleEigenMesh decimateMesh(const SimpleEigenMesh& m, int numberDesiredFaces, Eigen::VectorXi &mapping);
    static EigenMesh decimateMesh(const EigenMesh& m, int numberDesiredFaces, Eigen::VectorXi &mapping);
    static void decimateMesh(SimpleEigenMesh& m, int numberDesiredFaces, Eigen::VectorXi &mapping);
    static void decimateMesh(EigenMesh& m, int numberDesiredFaces, Eigen::VectorXi &mapping);

    /* Vertices removal */
    static void removeUnreferencedVertices(SimpleEigenMesh &input, Eigen::Matrix<int, Eigen::Dynamic, 1> &I);
    static void removeDuplicateVertices(SimpleEigenMesh &input, double epsilon);
    static void removeDuplicateVertices(SimpleEigenMesh &input, Eigen::Matrix<int, Eigen::Dynamic, 1> &I, double epsilon);

    static void removeDuplicateVertices(EigenMesh &input, double epsilon);
    static void removeDuplicateVertices(EigenMesh &input, Eigen::Matrix<int, Eigen::Dynamic, 1> &I, double epsilon);

    /* Manifold utilities */
    static bool isEdgeManifold(const SimpleEigenMesh& input);
    static bool isVertexManifold(const SimpleEigenMesh& input, Eigen::Matrix<bool, Eigen::Dynamic, 1>& B);
    static unsigned int extractManifoldPatches(const SimpleEigenMesh &m, Eigen::Matrix<int, Eigen::Dynamic, 1> &I);

    /* Adjacencies */
    static std::vector<SimpleEigenMesh> connectedComponents(const SimpleEigenMesh &m);
    static std::vector<std::vector<int>> vertexToVertexAdjacencies(const SimpleEigenMesh &m);
    static std::vector<std::vector<int>> vertexToFaceIncidences(const SimpleEigenMesh &m);
    static Eigen::MatrixXi faceToFaceAdjacencies(const SimpleEigenMesh &m);

    /* Mesh distances */
    static double hausdorffDistance(const SimpleEigenMesh& m1, const SimpleEigenMesh& m2);

    #ifdef CG3_CGAL_DEFINED

    /* CSG conversions */
    static CSGTree eigenMeshToCSGTree(const SimpleEigenMesh& m);
    static SimpleEigenMesh CSGTreeToEigenMesh(const CSGTree& tree);

    /* Mesh intersections */
    static SimpleEigenMesh intersection(const SimpleEigenMesh &m1, const SimpleEigenMesh &m2, std::vector<uint>& birthFaces = dummyVector);
    static EigenMesh intersection(const EigenMesh &m1, const EigenMesh &m2, std::vector<uint>& birthFaces = dummyVector);

    /* Mesh differences */
    static SimpleEigenMesh difference(const SimpleEigenMesh &m1, const SimpleEigenMesh &m2, std::vector<uint>& birthFaces = dummyVector);
    static EigenMesh difference(const EigenMesh &m1, const EigenMesh &m2, std::vector<uint>& birthFaces = dummyVector);

    /* Mesh unions */
    static SimpleEigenMesh union_(const SimpleEigenMesh &m1, const SimpleEigenMesh &m2, std::vector<uint>& birthFaces = dummyVector);
    static EigenMesh union_(const EigenMesh &m1, const EigenMesh &m2, std::vector<uint>& birthFaces = dummyVector);

    #endif

private:

    static std::vector<uint> dummyVector;

    EigenMeshLibIglAlgorithms() {};


};

} //namespace cg3::libigl::internal
} //namespace cg3::libigl
} //namespace cg3

#ifndef CG3_STATIC
#define CG3_EIGENMESH_LIBIGL_ALGORITHMS_ADJACENCIES_CPP "eigenmesh_libigl_algorithms_adjacencies.cpp"
#define CG3_EIGENMESH_LIBIGL_ALGORITHMS_BOOLEANS_CPP "eigenmesh_libigl_algorithms_booleans.cpp"
#define CG3_EIGENMESH_LIBIGL_ALGORITHMS_DECIMATION_CPP "eigenmesh_libigl_algorithms_decimation.cpp"
#define CG3_EIGENMESH_LIBIGL_ALGORITHMS_DISTANCES_CPP "eigenmesh_libigl_algorithms_distances.cpp"
#define CG3_EIGENMESH_LIBIGL_ALGORITHMS_MANIFOLDUTILITIES_CPP "eigenmesh_libigl_algorithms_manifoldutilities.cpp"
#define CG3_EIGENMESH_LIBIGL_ALGORITHMS_VERTICESREMOVAL_CPP "eigenmesh_libigl_algorithms_verticesremoval.cpp"
#include CG3_EIGENMESH_LIBIGL_ALGORITHMS_ADJACENCIES_CPP
#include CG3_EIGENMESH_LIBIGL_ALGORITHMS_BOOLEANS_CPP
#include CG3_EIGENMESH_LIBIGL_ALGORITHMS_DECIMATION_CPP
#include CG3_EIGENMESH_LIBIGL_ALGORITHMS_DISTANCES_CPP
#include CG3_EIGENMESH_LIBIGL_ALGORITHMS_MANIFOLDUTILITIES_CPP
#include CG3_EIGENMESH_LIBIGL_ALGORITHMS_VERTICESREMOVAL_CPP
#undef CG3_EIGENMESH_LIBIGL_ALGORITHMS_ADJACENCIES_CPP
#undef CG3_EIGENMESH_LIBIGL_ALGORITHMS_BOOLEANS_CPP
#undef CG3_EIGENMESH_LIBIGL_ALGORITHMS_DECIMATION_CPP
#undef CG3_EIGENMESH_LIBIGL_ALGORITHMS_DISTANCES_CPP
#undef CG3_EIGENMESH_LIBIGL_ALGORITHMS_MANIFOLDUTILITIES_CPP
#undef CG3_EIGENMESH_LIBIGL_ALGORITHMS_VERTICESREMOVAL_CPP
#endif //CG3_STATIC

#endif // CG3_EIGENMESH_LIBIGL_ALGORITHMS_H

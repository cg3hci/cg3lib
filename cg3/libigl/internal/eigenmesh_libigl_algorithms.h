/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_EIGENMESH_LIBIGL_ALGORITHMS_H
#define CG3_EIGENMESH_LIBIGL_ALGORITHMS_H

#include <cg3/meshes/eigenmesh/eigenmesh.h>

#ifdef  CG3_CGAL_DEFINED
#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wnon-template-friend"
#include <igl/copyleft/cgal/CSGTree.h>
#pragma GCC diagnostic pop
#else //__GNUC__
#include <igl/copyleft/cgal/CSGTree.h>
#endif //__GNUC__
#endif //CGAL_DEFINED

namespace cg3 {

namespace libigl {

namespace internal {

class EigenMeshLibIglAlgorithms {
public:
    static SimpleEigenMesh decimateMesh(const SimpleEigenMesh& m, int numberDesiredFaces, Eigen::VectorXi &mapping);
    static EigenMesh decimateMesh(const EigenMesh& m, int numberDesiredFaces, Eigen::VectorXi &mapping);

    static void decimateMesh(SimpleEigenMesh& m, int numberDesiredFaces, Eigen::VectorXi &mapping);
    static void decimateMesh(EigenMesh& m, int numberDesiredFaces, Eigen::VectorXi &mapping);

    static void removeUnreferencedVertices(SimpleEigenMesh &input, Eigen::Matrix<int, Eigen::Dynamic, 1> &I);
    static void removeDuplicateVertices(SimpleEigenMesh &input, double epsilon);
    static void removeDuplicateVertices(SimpleEigenMesh &input, Eigen::Matrix<int, Eigen::Dynamic, 1> &I, double epsilon);
    static void removeDuplicateVertices(EigenMesh &input, double epsilon);
    static void removeDuplicateVertices(EigenMesh &input, Eigen::Matrix<int, Eigen::Dynamic, 1> &I, double epsilon);
    static bool isEdgeManifold(const SimpleEigenMesh& input);
    static bool isVertexManifold(const SimpleEigenMesh& input, Eigen::Matrix<bool, Eigen::Dynamic, 1>& B);
    static std::vector<SimpleEigenMesh> getConnectedComponents(const SimpleEigenMesh &m);
    static std::vector<std::vector<int>> getVertexAdjacencies(const SimpleEigenMesh &m);
    static Eigen::MatrixXi getFaceAdjacences(const SimpleEigenMesh &m);
    static unsigned int extractManifoldPatches(const SimpleEigenMesh &m, Eigen::Matrix<int, Eigen::Dynamic, 1> &I);

    #ifdef  CG3_CGAL_DEFINED
    static igl::copyleft::cgal::CSGTree eigenMeshToCSGTree(const SimpleEigenMesh& m);
    static SimpleEigenMesh CSGTreeToEigenMesh(const igl::copyleft::cgal::CSGTree& tree);

    static void intersection(SimpleEigenMesh &result, const SimpleEigenMesh &m1, const SimpleEigenMesh &m2);
    static void intersection(EigenMesh &result, const EigenMesh &m1, const EigenMesh &m2);
    static SimpleEigenMesh intersection(const SimpleEigenMesh &m1, const SimpleEigenMesh &m2);
    static EigenMesh intersection(const EigenMesh &m1, const EigenMesh &m2);
    static void intersection(igl::copyleft::cgal::CSGTree& result, const igl::copyleft::cgal::CSGTree& m1, const SimpleEigenMesh& m2);
    static igl::copyleft::cgal::CSGTree intersection(const igl::copyleft::cgal::CSGTree& m1, const SimpleEigenMesh& m2);
    static void intersection(SimpleEigenMesh& result, const igl::copyleft::cgal::CSGTree& m1, const SimpleEigenMesh& m2);

    static void difference(SimpleEigenMesh &result, const SimpleEigenMesh &m1, const SimpleEigenMesh &m2);
    static void difference(EigenMesh &result, const EigenMesh &m1, const EigenMesh &m2);
    static SimpleEigenMesh difference(const SimpleEigenMesh &m1, const SimpleEigenMesh &m2);
    static EigenMesh difference(const EigenMesh &m1, const EigenMesh &m2);
    static void difference(igl::copyleft::cgal::CSGTree& result, const igl::copyleft::cgal::CSGTree& m1, const SimpleEigenMesh& m2);
    static igl::copyleft::cgal::CSGTree difference(const igl::copyleft::cgal::CSGTree& m1, const SimpleEigenMesh& m2);


    static void union_(SimpleEigenMesh &result, const SimpleEigenMesh &m1, const SimpleEigenMesh &m2);
    static void union_(EigenMesh &result, const EigenMesh &m1, const EigenMesh &m2);
    static SimpleEigenMesh union_(const SimpleEigenMesh &m1, const SimpleEigenMesh &m2);
    static EigenMesh union_(const EigenMesh &m1, const EigenMesh &m2);
    static void union_(igl::copyleft::cgal::CSGTree& result, const igl::copyleft::cgal::CSGTree& m1, const SimpleEigenMesh& m2);
    static igl::copyleft::cgal::CSGTree union_(const igl::copyleft::cgal::CSGTree& m1, const SimpleEigenMesh& m2);
    #endif

    static double hausdorffDistance(const SimpleEigenMesh& m1, const SimpleEigenMesh& m2);

private:
    EigenMeshLibIglAlgorithms() {}
};

}

}


}
#endif // CG3_EIGENMESH_LIBIGL_ALGORITHMS_H

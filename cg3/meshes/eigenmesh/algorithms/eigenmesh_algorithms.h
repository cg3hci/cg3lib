#ifndef CG3_EIGENMESH_ALGORITHMS_H
#define CG3_EIGENMESH_ALGORITHMS_H

#include <cg3/meshes/eigenmesh/eigenmesh.h>

#ifdef  CG3_LIBIGL_DEFINED
#ifdef  CG3_CGAL_DEFINED
#include <igl/copyleft/cgal/CSGTree.h>
#endif //CGAL_DEFINED
#endif //IGL_DEFINED

namespace cg3 {

class EigenMeshAlgorithms {
    public:
        static SimpleEigenMesh makeBox(const BoundingBox &bb, double minimumEdge = -1);
        static SimpleEigenMesh makeBox(const Pointd &min, const Pointd &max, double minimumEdge = -1);

        static SimpleEigenMesh makeSphere(const Pointd& center, float radius, unsigned nLatitude = 20);

        static SimpleEigenMesh makeCylinder(const Pointd& p1, const Pointd& p2, float radius, unsigned int subd = 10);

        static bool isABox(const SimpleEigenMesh& mesh);

        #ifdef  CG3_LIBIGL_DEFINED
        static SimpleEigenMesh decimateMesh(const SimpleEigenMesh& m, int numberDesiredFaces, Eigen::VectorXi &mapping = dummyEigenVectorXi);
        static EigenMesh decimateMesh(const EigenMesh& m, int numberDesiredFaces, Eigen::VectorXi &mapping = dummyEigenVectorXi);

        static void decimateMesh(SimpleEigenMesh& m, int numberDesiredFaces, Eigen::VectorXi &mapping = dummyEigenVectorXi);
        static void decimateMesh(EigenMesh& m, int numberDesiredFaces, Eigen::VectorXi &mapping = dummyEigenVectorXi);

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

        static void removeUnreferencedVertices(SimpleEigenMesh &input, Eigen::Matrix<int, Eigen::Dynamic, 1> &I = dummyEigenVectorXi);
        static void removeDuplicateVertices(SimpleEigenMesh &input, double epsilon = CG3_EPSILON);
        static void removeDuplicateVertices(SimpleEigenMesh &input, Eigen::Matrix<int, Eigen::Dynamic, 1> &I, double epsilon = CG3_EPSILON);
        static void removeDuplicateVertices(EigenMesh &input, double epsilon = CG3_EPSILON);
        static void removeDuplicateVertices(EigenMesh &input, Eigen::Matrix<int, Eigen::Dynamic, 1> &I, double epsilon = CG3_EPSILON);
        static bool isEdgeManifold(const SimpleEigenMesh& input);
        static bool isVertexManifold(const SimpleEigenMesh& input, Eigen::Matrix<bool, Eigen::Dynamic, 1>& B = dummyEigenVectorXb);
        static std::vector<SimpleEigenMesh> getConnectedComponents(const SimpleEigenMesh &m);
        static Eigen::MatrixXi getFaceAdjacences(const SimpleEigenMesh &m);
        static unsigned int extractManifoldPatches(const SimpleEigenMesh &m, Eigen::Matrix<int, Eigen::Dynamic, 1> &I = dummyEigenVectorXi);
        #endif

     private:
        EigenMeshAlgorithms() {}
        static Eigen::VectorXi dummyEigenVectorXi;
        static Eigen::Matrix<bool, Eigen::Dynamic, 1> dummyEigenVectorXb;
};

inline SimpleEigenMesh EigenMeshAlgorithms::makeBox(const Pointd &min, const Pointd &max, double minimumEdge){
    return makeBox(BoundingBox(min, max), minimumEdge);
}

}

#endif // CG3_EIGENMESH_ALGORITHMS_H

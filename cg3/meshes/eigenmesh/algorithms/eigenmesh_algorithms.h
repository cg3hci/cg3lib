#ifndef CG3_EIGENMESH_ALGORITHMS_H
#define CG3_EIGENMESH_ALGORITHMS_H

#include <cg3/meshes/eigenmesh/eigenmesh.h>

namespace cg3 {

class EigenMeshAlgorithms {
    public:
        static SimpleEigenMesh makeBox(const BoundingBox &bb, double minimumEdge = -1);
        static SimpleEigenMesh makeBox(const Pointd &min, const Pointd &max, double minimumEdge = -1);

        static SimpleEigenMesh makeSphere(const Pointd& center, float radius, unsigned nLatitude = 20);

        static SimpleEigenMesh makeCylinder(const Pointd& p1, const Pointd& p2, float radius, unsigned int subd = 10);

        static bool isABox(const SimpleEigenMesh& mesh);

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

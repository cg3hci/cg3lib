/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_EIGENMESH_ALGORITHMS_H
#define CG3_EIGENMESH_ALGORITHMS_H

#include <cg3/meshes/eigenmesh/eigenmesh.h>

namespace cg3 {

class EigenMeshAlgorithms
{
public:
    static SimpleEigenMesh makeBox(const BoundingBox3 &bb, double minimumEdge = -1);
    static SimpleEigenMesh makeBox(const Point3d &min, const Point3d &max, double minimumEdge = -1);

    static SimpleEigenMesh makeSphere(const Point3d& center, float radius, unsigned nLatitude = 20);

    static SimpleEigenMesh makeCylinder(const Point3d& p1, const Point3d& p2, float radius, unsigned int subd = 10);

    static bool isABox(const SimpleEigenMesh& mesh);

 private:
    EigenMeshAlgorithms() {}
    static Eigen::VectorXi dummyEigenVectorXi;
    static Eigen::Matrix<bool, Eigen::Dynamic, 1> dummyEigenVectorXb;
};

inline SimpleEigenMesh EigenMeshAlgorithms::makeBox(const Point3d &min, const Point3d &max, double minimumEdge)
{
    return makeBox(BoundingBox3(min, max), minimumEdge);
}

} //namespace cg3

#endif // CG3_EIGENMESH_ALGORITHMS_H

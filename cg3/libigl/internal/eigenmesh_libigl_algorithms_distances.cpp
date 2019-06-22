/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "eigenmesh_libigl_algorithms.h"

#include <igl/hausdorff.h>

namespace cg3 {
namespace libigl {
namespace internal {


/* ----- DISTANCES ----- */

CG3_INLINE double EigenMeshLibIglAlgorithms::hausdorffDistance(
        const SimpleEigenMesh& m1,
        const SimpleEigenMesh& m2)
{
    Eigen::MatrixXd VA = m1.V, VB = m2.V;
    Eigen::MatrixXi FA = m1.F, FB = m2.F;

    double hDistance;
    igl::hausdorff(VA, FA, VB, FB, hDistance);
    return hDistance;
}

} //namespace cg3::libigl::internal
} //namespace cg3::libigl
} //namespace cg3

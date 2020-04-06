/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */

#include "eigenmesh_libigl_algorithms.h"

#include <igl/principal_curvature.h>

namespace cg3 {
namespace libigl {
namespace internal {

/* ----- VERTEX CURVATURE ----- */

/**
 * @ingroup cg3libigl
 * @brief Get principal curvature
 * @param m Input mesh
 * @param minDirection Minimum principal curvature direction for each vertex
 * @param maxDirection Minimum principal curvature direction for each vertex
 * @param minValue Minimum principal curvature magnitude for each vertex
 * @param maxValue Minimum principal curvature magnitude for each vertex
 * @param maxValue Minimum principal curvature magnitude  for each vertex
 * @param nRing Controls the size of the neighbourhood used, 1 = average edge length
 */
CG3_INLINE void EigenMeshLibIglAlgorithms::vertexCurvature(
        const SimpleEigenMesh& m,
        std::vector<Vec3d>& minDirection,
        std::vector<Vec3d>& maxDirection,
        std::vector<double>& minValue,
        std::vector<double>& maxValue,
        const unsigned int nRing)
{
    Eigen::MatrixXd V = m.V;
    Eigen::MatrixXi F = m.F;

    Eigen::MatrixXd PD1, PD2, PV1, PV2;
    igl::principal_curvature(V,F,PD1,PD2,PV1,PV2,nRing,true);

    minDirection.resize(PD2.rows());
    maxDirection.resize(PD1.rows());
    minValue.resize(PV2.rows());
    maxValue.resize(PV1.rows());

    for (int i = 0; i < PD2.rows(); ++i) {
        minDirection[i] = Vec3d(PD1(i, 0), PD1(i, 1), PD1(i, 2));
    }
    for (int i = 0; i < PD1.rows(); ++i) {
        maxDirection[i] = Vec3d(PD2(i, 0), PD2(i, 1), PD2(i, 2));
    }
    for (int i = 0; i < PD1.rows(); ++i) {
        minValue[i] = PV1(i);
    }
    for (int i = 0; i < PD2.rows(); ++i) {
        maxValue[i] = PV2(i);
    }
}

} //namespace cg3::libigl::internal
} //namespace cg3::libigl
} //namespace cg3

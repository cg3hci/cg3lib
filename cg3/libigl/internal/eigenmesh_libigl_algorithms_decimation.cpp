/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "eigenmesh_libigl_algorithms.h"

#include <igl/decimate.h>

namespace cg3 {
namespace libigl {
namespace internal {

/* ----- DECIMATION ----- */

CG3_INLINE SimpleEigenMesh EigenMeshLibIglAlgorithms::decimateMesh(
        const SimpleEigenMesh& m,
        int numberDesiredFaces,
        Eigen::VectorXi& mapping)
{
    SimpleEigenMesh output;

    /**
     * @todo Pull request
     */
    Eigen::MatrixXd VV;
    Eigen::MatrixXi FF;
    igl::decimate(m.V, m.F, numberDesiredFaces, VV, FF, mapping);

    output.V = VV;
    output.F = FF;
    return output;
}

CG3_INLINE EigenMesh EigenMeshLibIglAlgorithms::decimateMesh(
        const EigenMesh& m,
        int numberDesiredFaces,
        Eigen::VectorXi& mapping)
{
    EigenMesh output;

    /**
     * @todo Pull request
     */
    Eigen::MatrixXd VV;
    Eigen::MatrixXi FF;
    igl::decimate(m.V, m.F, numberDesiredFaces, VV, FF, mapping);

    output.V = VV;
    output.F = FF;
    output.updateFaceNormals();
    output.updateVerticesNormals();
    output.CV = Eigen::MatrixXf::Constant(output.V.rows(), 3, 0.5);
    output.CF.resize(output.F.rows(), 3);
    for (unsigned int i = 0; i < output.F.rows(); i++){
        output.CF(i,0) = m.CF(mapping(i), 0);
        output.CF(i,1) = m.CF(mapping(i), 1);
        output.CF(i,2) = m.CF(mapping(i), 2);
    }
    output.updateBoundingBox();

    return output;
}

CG3_INLINE void EigenMeshLibIglAlgorithms::decimateMesh(
        SimpleEigenMesh& m,
        int numberDesiredFaces,
        Eigen::VectorXi& mapping)
{
    /**
     * @todo Pull request
     */
    Eigen::MatrixXd VV;
    Eigen::MatrixXi FF;
    igl::decimate(m.V, m.F, numberDesiredFaces, VV, FF, mapping);
    m.V = VV;
    m.F = FF;
}

CG3_INLINE void EigenMeshLibIglAlgorithms::decimateMesh(
        EigenMesh& m,
        int numberDesiredFaces,
        Eigen::VectorXi& mapping)
{
    Eigen::MatrixXd VV;
    Eigen::MatrixXi FF;
    igl::decimate(m.V, m.F, numberDesiredFaces, VV, FF, mapping);
    m.V = VV;
    m.F = FF;

    m.CV = Eigen::MatrixXf::Constant(m.V.rows(), 3, 0.5);
    Eigen::MatrixXf tmp = m.CF;
    m.CF.resize(m.F.rows(), 3);
    for (int i = FF.rows()-1; i>= 0; i--){
        m.CF(i,0) = tmp(mapping(i), 0);
        m.CF(i,1) = tmp(mapping(i), 1);
        m.CF(i,2) = tmp(mapping(i), 2);
    }

    m.updateBoundingBox();
}

} //namespace cg3::libigl::internal
} //namespace cg3::libigl
} //namespace cg3

/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "eigenmesh_libigl_algorithms.h"

#include <igl/remove_unreferenced.h>
#include <igl/remove_duplicates.h>

namespace cg3 {

namespace libigl {

namespace internal {


/* ----- VERTICES REMOVAL ----- */

CG3_INLINE void EigenMeshLibIglAlgorithms::removeUnreferencedVertices(
        SimpleEigenMesh& input,
        Eigen::Matrix<int, Eigen::Dynamic, 1> &I)
{
    //Eigen::Matrix<double, Eigen::Dynamic, 3, Eigen::RowMajor> NV;
    //Eigen::Matrix<int, Eigen::Dynamic, 3, Eigen::RowMajor> NF;
    //igl::remove_unreferenced(V,F, NV, NF, I);

    /**
      @todo Pull request
    */
    ///
    /// If IGL Static (pull request problem)
    Eigen::MatrixXd VV = input.V, NV;
    Eigen::MatrixXi FF = input.F, NF;
    igl::remove_unreferenced(VV,FF, NV, NF, I);
    ///

    input.V = NV;
    input.F = NF;
}

CG3_INLINE void EigenMeshLibIglAlgorithms::removeDuplicateVertices(
        SimpleEigenMesh& input,
        double epsilon)
{
    Eigen::VectorXi I;
    removeDuplicateVertices(input, I, epsilon);
}

CG3_INLINE void EigenMeshLibIglAlgorithms::removeDuplicateVertices(
        SimpleEigenMesh& input,
        Eigen::Matrix<int, Eigen::Dynamic, 1>& I,
        double epsilon)
{
    /**
      @todo Pull request
    */
    ///
    /// If IGL Static (pull request problem)
    Eigen::MatrixXd VV = input.V, NV;
    Eigen::MatrixXi FF = input.F, NF;
    igl::remove_duplicates( VV,FF, NV, NF, I,epsilon );
    ///

    input.V = NV;
    input.F = NF;
}

CG3_INLINE void EigenMeshLibIglAlgorithms::removeDuplicateVertices(
        EigenMesh& input,
        double epsilon)
{
    Eigen::VectorXi I;
    removeDuplicateVertices(input, I, epsilon);
}

CG3_INLINE void EigenMeshLibIglAlgorithms::removeDuplicateVertices(
        EigenMesh& input,
        Eigen::Matrix<int, Eigen::Dynamic, 1>& I,
        double epsilon)
{
    /**
      @todo Reimplement this WITHOUT LBIGL (see resizing color faces)
    */
    ///
    /// If IGL Static (pull request problem)
    Eigen::MatrixXd VV = input.V, NV;
    Eigen::MatrixXi FF = input.F, NF;
    igl::remove_duplicates( VV,FF, NV, NF, I,epsilon );
    ///

    input.V = NV;
    input.F = NF;

    Eigen::MatrixXd NNV(NV.rows(), 3);
    Eigen::MatrixXf NCV(NV.rows(), 3);
    for (unsigned int i = 0; i < VV.rows(); i++){
        NNV.row(I(i)) = input.NV.row(i);
        NCV.row(I(i)) = input.CV.row(i);
    }
    input.NV = NNV;
    input.CV = NCV;
    input.CF.conservativeResize(input.F.rows(), Eigen::NoChange);
    input.updateFaceNormals();
    //input.updateFacesAndVerticesNormals();
    //input.updateColorSizes();
}

} //namespace cg3::libigl::internal
} //namespace cg3::libigl
} //namespace cg3

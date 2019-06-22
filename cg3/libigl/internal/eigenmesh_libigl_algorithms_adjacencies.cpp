/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "eigenmesh_libigl_algorithms.h"

#include <igl/facet_components.h>
#include <igl/triangle_triangle_adjacency.h>
#include <igl/vertex_triangle_adjacency.h>
#include <igl/adjacency_list.h>

namespace cg3 {
namespace libigl {
namespace internal {


/* ----- ADJACENCIES ----- */

CG3_INLINE std::vector<SimpleEigenMesh> EigenMeshLibIglAlgorithms::connectedComponents(
        const SimpleEigenMesh& mm)
{
    std::vector<SimpleEigenMesh> connectedComponents;
    Eigen::VectorXi C;
    //igl::facet_components(F, C);

    /**
      @todo Pull request
    */
    ///If IGL Static (pull request problem)
    Eigen::MatrixXi FF = mm.F;
    igl::facet_components(FF, C);
    ///
    for (unsigned int i = 0; i < C.size(); i++){
        if (C(i) >= (int)connectedComponents.size()){
            assert(C(i) == (int)connectedComponents.size());
            SimpleEigenMesh m;
            m.V = mm.V;
            connectedComponents.push_back(m);
        }
        connectedComponents[C(i)].addFace(mm.F.row(i));
    }
    for (unsigned int i = 0; i < connectedComponents.size(); i++){
        Eigen::Matrix<int, Eigen::Dynamic, 1> I;
        removeUnreferencedVertices(connectedComponents[i], I);
    }
    return connectedComponents;
}

CG3_INLINE std::vector<std::vector<int>> EigenMeshLibIglAlgorithms::vertexToVertexAdjacencies(
        const SimpleEigenMesh &m)
{
    std::vector<std::vector<int>> result;

    Eigen::MatrixXi FF = m.F;
    igl::adjacency_list(FF, result);

    //Libigl algorithm takes only the max value in m.F
    //so we resize the vector to be of the same size of
    //the vertex matrix
    result.resize(m.V.rows());

    return result;
}

CG3_INLINE std::vector<std::vector<int>> EigenMeshLibIglAlgorithms::vertexToFaceIncidences(
        const SimpleEigenMesh &m)
{
    std::vector<std::vector<int>> VF;
    std::vector<std::vector<int>> VFi;

    Eigen::MatrixXi FF = m.F;
    Eigen::MatrixXd VV = m.V;
    igl::vertex_triangle_adjacency(VV, FF, VF, VFi);

    return VF;
}

CG3_INLINE Eigen::MatrixXi EigenMeshLibIglAlgorithms::faceToFaceAdjacencies(
        const SimpleEigenMesh& m)
{
    Eigen::MatrixXi eigenResult;
    Eigen::MatrixXi FF = m.F;
    igl::triangle_triangle_adjacency(FF, eigenResult);

    return eigenResult;
}


} //namespace cg3::libigl::internal
} //namespace cg3::libigl
} //namespace cg3

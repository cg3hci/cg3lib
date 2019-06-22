/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "mesh_adjacencies.h"

#include "internal/eigenmesh_libigl_algorithms.h"

namespace cg3 {
namespace libigl {

/**
 * @ingroup cg3libigl
 * @brief Get vertex to vertex adjacencies
 * @param m Input mesh
 * @return Vector of vector of indices
 */
CG3_INLINE std::vector<std::vector<int>> vertexToVertexAdjacencies(const SimpleEigenMesh& m)
{
    return internal::EigenMeshLibIglAlgorithms::vertexToVertexAdjacencies(m);
}

/**
 * @ingroup cg3libigl
 * @brief Get vertex to face incidences
 * @param m Input mesh
 * @return Vector of vector of indices
 */
CG3_INLINE std::vector<std::vector<int>> vertexToFaceIncidences(const SimpleEigenMesh& m)
{
    return internal::EigenMeshLibIglAlgorithms::vertexToFaceIncidences(m);
}

/**
 * @ingroup cg3libigl
 * @brief Get faceto face adjacencies
 * @param m Input mesh
 * @return Vector of vector of indices
 */
CG3_INLINE std::vector<std::vector<int>> faceToFaceAdjacencies(const SimpleEigenMesh &m)
{
    Eigen::MatrixXi eigenResult =
            internal::EigenMeshLibIglAlgorithms::faceToFaceAdjacencies(m);
    std::vector<std::vector<int>> result(eigenResult.rows());
    for (int i = 0; i < eigenResult.rows(); i++) {
        result[i].resize(eigenResult.cols());
        for (int j = 0; j < eigenResult.cols(); j++) {
            result[i][j] = eigenResult(i,j);
        }
    }

    return result;
}

/**
 * @ingroup cg3libigl
 * @brief Get faceto face adjacencies
 * @param m Input mesh
 * @param adjacences Output Adjacency Matrix
 */
CG3_INLINE void faceToFaceAdjacencies(const SimpleEigenMesh& m, Eigen::MatrixXi& adjacences)
{
    adjacences = internal::EigenMeshLibIglAlgorithms::faceToFaceAdjacencies(m);
}

} //namespace cg3::libigl
} //namespace cg3



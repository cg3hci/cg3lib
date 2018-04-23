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
 * @brief Get vertex-vertex adjacencies
 * @param m Input mesh
 * @return Vector of vector of indices
 */
inline std::vector<std::vector<int>> getVertexVertexAdjacencies(const SimpleEigenMesh& m)
{
    return internal::EigenMeshLibIglAlgorithms::getVertexVertexAdjacencies(m);
}

/**
 * @ingroup cg3libigl
 * @brief Get vertex-face adjacencies
 * @param m Input mesh
 * @return Vector of vector of indices
 */
inline std::vector<std::vector<int>> getVertexFaceAdjacencies(const SimpleEigenMesh& m)
{
    return internal::EigenMeshLibIglAlgorithms::getVertexFaceAdjacencies(m);
}

/**
 * @ingroup cg3libigl
 * @brief Get face-face adjacencies
 * @param m Input mesh
 * @return Vector of vector of indices
 */
inline std::vector<std::vector<int>> getFaceFaceAdjacencies(const SimpleEigenMesh &m)
{
    return internal::EigenMeshLibIglAlgorithms::getFaceFaceAdjacencies(m);
}

} //namespace cg3::libigl
} //namespace cg3



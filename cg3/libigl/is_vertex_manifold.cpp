/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "is_vertex_manifold.h"

#include "internal/eigenmesh_libigl_algorithms.h"

namespace cg3 {
namespace libigl {

/**
 * @ingroup cg3libigl
 * @brief isVertexManifold
 * @param input
 * @param B
 * @return
 */
CG3_INLINE bool isVertexManifold(
        const SimpleEigenMesh &input,
        Eigen::Matrix<bool, Eigen::Dynamic, 1> &B)
{
    return internal::EigenMeshLibIglAlgorithms::isVertexManifold(input, B);
}

/**
 * @ingroup cg3libigl
 * @brief isVertexManifold
 * @param input
 * @return
 */
CG3_INLINE bool isVertexManifold(const SimpleEigenMesh &input)
{
    Eigen::Matrix<bool, Eigen::Dynamic, 1> B;
    return internal::EigenMeshLibIglAlgorithms::isVertexManifold(input, B);
}

} //namespace cg3::libigl
} //namespace cg3

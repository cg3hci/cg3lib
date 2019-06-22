/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "extract_manifold_patches.h"

#include "internal/eigenmesh_libigl_algorithms.h"

namespace cg3 {
namespace libigl {

/**
 * @ingroup cg3libigl
 * @brief extractManifoldPatches
 * @param m
 * @param I
 * @return
 */
CG3_INLINE int extractManifoldPatches(
        const SimpleEigenMesh &m,
        Eigen::Matrix<int, Eigen::Dynamic, 1> &I)
{
    return internal::EigenMeshLibIglAlgorithms::extractManifoldPatches(m, I);
}

/**
 * @ingroup cg3libigl
 * @brief extractManifoldPatches
 * @param m
 * @return
 */
CG3_INLINE int extractManifoldPatches(const SimpleEigenMesh &m)
{
    Eigen::VectorXi I;
    return internal::EigenMeshLibIglAlgorithms::extractManifoldPatches(m, I);
}

} //namespace cg3::libigl
} //namespace cg3

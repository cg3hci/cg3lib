/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "eigenmesh_libigl_algorithms.h"

#include <igl/is_edge_manifold.h>
#include <igl/is_vertex_manifold.h>
#include <igl/extract_manifold_patches.h>

namespace cg3 {
namespace libigl {
namespace internal {


/* ----- MANIFOLD UTILITIES ----- */

CG3_INLINE bool EigenMeshLibIglAlgorithms::isEdgeManifold(const SimpleEigenMesh& input)
{
    return igl::is_edge_manifold(input.F);
}

CG3_INLINE bool EigenMeshLibIglAlgorithms::isVertexManifold(
        const SimpleEigenMesh& input,
        Eigen::Matrix<bool, Eigen::Dynamic, 1>& B)
{
    return igl::is_vertex_manifold(input.V, B);
}


CG3_INLINE unsigned int EigenMeshLibIglAlgorithms::extractManifoldPatches(
        const SimpleEigenMesh& m,
        Eigen::Matrix<int, Eigen::Dynamic, 1>& I)
{
    return igl::extract_manifold_patches(m.F, I);
}

} //namespace cg3::libigl::internal
} //namespace cg3::libigl
} //namespace cg3

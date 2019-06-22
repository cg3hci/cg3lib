/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "is_edge_manifold.h"

#include "internal/eigenmesh_libigl_algorithms.h"

namespace cg3 {
namespace libigl {

/**
 * @ingroup cg3libigl
 * @brief isEdgeManifold
 * @param input
 * @return
 */
CG3_INLINE bool isEdgeManifold(const SimpleEigenMesh &input)
{
    return internal::EigenMeshLibIglAlgorithms::isEdgeManifold(input);
}

} //namespace cg3::libigl
} //namespace cg3

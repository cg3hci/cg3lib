/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "mesh_distance.h"

#include "internal/eigenmesh_libigl_algorithms.h"

namespace cg3 {
namespace libigl {

/**
 * @ingroup cg3libigl
 * @brief hausdorffDistance
 * @param m1
 * @param m2
 * @return
 */
CG3_INLINE double hausdorffDistance(const SimpleEigenMesh& m1, const SimpleEigenMesh& m2)
{
    return internal::EigenMeshLibIglAlgorithms::hausdorffDistance(m1, m2);
}

} //namespace cg3::libigl
} //namespace cg3::l



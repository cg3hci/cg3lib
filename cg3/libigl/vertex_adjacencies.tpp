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

inline std::vector<std::vector<int>> getVertexAdjacencies(const SimpleEigenMesh &m) {
    return internal::EigenMeshLibIglAlgorithms::getVertexAdjacencies(m);
}

}

}



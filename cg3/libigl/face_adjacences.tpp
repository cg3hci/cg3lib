/**
  * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
  * This Source Code Form is subject to the terms of the GNU GPL 3.0
  *
  * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
  */

#include "face_adjacences.h"

#include "internal/eigenmesh_libigl_algorithms.h"

namespace cg3 {

namespace libigl {

/**
 * @ingroup cg3libigl
 * @brief getFaceAdjacences
 * @param m
 * @return
 */
inline Eigen::MatrixXi getFaceAdjacences(const SimpleEigenMesh &m) {
    return internal::EigenMeshLibIglAlgorithms::getFaceAdjacences(m);
}

}

}

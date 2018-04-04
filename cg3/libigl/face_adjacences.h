/**
  * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
  * This Source Code Form is subject to the terms of the GNU GPL 3.0
  *
  * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
  */

#ifndef CG3_LIBIGL_FACE_ADJACENCES_H
#define CG3_LIBIGL_FACE_ADJACENCES_H

#include <cg3/meshes/eigenmesh/eigenmesh.h>

namespace cg3 {
namespace libigl {

Eigen::MatrixXi getFaceAdjacences(const SimpleEigenMesh &m);

} //namespace cg3::libigl
} //namespace cg3

#include "face_adjacences.tpp"

#endif // CG3_LIBIGL_FACE_ADJACENCES_H

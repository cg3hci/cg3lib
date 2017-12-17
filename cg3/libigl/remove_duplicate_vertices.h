/**
  * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
  * This Source Code Form is subject to the terms of the GNU GPL 3.0
  *
  * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
  */

#ifndef CG3_LIBIGL_REMOVE_DUPLICATE_VERTICES_H
#define CG3_LIBIGL_REMOVE_DUPLICATE_VERTICES_H

#include <cg3/meshes/eigenmesh/eigenmesh.h>

namespace cg3 {

namespace libigl {

void removeDuplicateVertices(SimpleEigenMesh &input, double epsilon = CG3_EPSILON);
void removeDuplicateVertices(SimpleEigenMesh &input, Eigen::Matrix<int, Eigen::Dynamic, 1> &I, double epsilon = CG3_EPSILON);
void removeDuplicateVertices(EigenMesh &input, double epsilon = CG3_EPSILON);
void removeDuplicateVertices(EigenMesh &input, Eigen::Matrix<int, Eigen::Dynamic, 1> &I, double epsilon = CG3_EPSILON);

}

}

#include "remove_duplicate_vertices.tpp"

#endif // REMOVE_LIBIGL_DUPLICATE_VERTICES_H

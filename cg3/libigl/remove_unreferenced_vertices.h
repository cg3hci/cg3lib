/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_LIBIGL_REMOVE_UNREFERENCED_VERTICES_H
#define CG3_LIBIGL_REMOVE_UNREFERENCED_VERTICES_H

#include <cg3/meshes/eigenmesh/eigenmesh.h>

namespace cg3 {

namespace libigl {

void removeUnreferencedVertices(SimpleEigenMesh &input, Eigen::Matrix<int, Eigen::Dynamic, 1> &I);
void removeUnreferencedVertices(SimpleEigenMesh &input);

}

}

#include "remove_unreferenced_vertices.tpp"

#endif // CG3_REMOVE_UNREFERENCED_VERTICES_H

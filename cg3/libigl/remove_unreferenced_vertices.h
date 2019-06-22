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

void removeUnreferencedVertices(
        SimpleEigenMesh &input,
        Eigen::Matrix<int, Eigen::Dynamic, 1> &I);

void removeUnreferencedVertices(SimpleEigenMesh &input);

} //namespace cg3::libigl
} //namespace cg3

#ifndef CG3_STATIC
#define CG3_REMOVE_UNREFERENCED_VERTICES_CPP "remove_unreferenced_vertices.cpp"
#include CG3_REMOVE_UNREFERENCED_VERTICES_CPP
#undef CG3_REMOVE_UNREFERENCED_VERTICES_CPP
#endif //CG3_STATIC

#endif // CG3_REMOVE_UNREFERENCED_VERTICES_H

/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_LIBIGL_IS_VERTEX_MANIFOLD_H
#define CG3_LIBIGL_IS_VERTEX_MANIFOLD_H

#include <cg3/meshes/eigenmesh/eigenmesh.h>

namespace cg3 {
namespace libigl {

bool isVertexManifold(
        const SimpleEigenMesh& input,
        Eigen::Matrix<bool, Eigen::Dynamic, 1>& B);

bool isVertexManifold(const SimpleEigenMesh& input);

} //namespace cg3::libigl
} //namespace cg3

#ifndef CG3_STATIC
#define CG3_LIBIGL_IS_VERTEX_MANIFOLD_CPP "is_vertex_manifold.cpp"
#include CG3_LIBIGL_IS_VERTEX_MANIFOLD_CPP
#undef CG3_LIBIGL_IS_VERTEX_MANIFOLD_CPP
#endif //CG3_STATIC

#endif // CG3_LIBIGL_IS_VERTEX_MANIFOLD_H

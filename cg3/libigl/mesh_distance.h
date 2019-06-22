/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_LIBIGL_MESH_DISTANCE_H
#define CG3_LIBIGL_MESH_DISTANCE_H

#include <cg3/meshes/eigenmesh/eigenmesh.h>

namespace cg3 {
namespace libigl {

double hausdorffDistance(const SimpleEigenMesh& m1, const SimpleEigenMesh& m2);

} //namespace cg3::libigl
} //namespace cg3

#ifndef CG3_STATIC
#define CG3_LIBIGL_MESH_DISTANCE_CPP "mesh_distance.cpp"
#include CG3_LIBIGL_MESH_DISTANCE_CPP
#undef CG3_LIBIGL_MESH_DISTANCE_CPP
#endif //CG3_STATIC

#endif // CG3_LIBIGL_MESH_DISTANCE_H

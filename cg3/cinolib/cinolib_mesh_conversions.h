/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_CINOLIB_MESH_CONVERSIONS_H
#define CG3_CINOLIB_MESH_CONVERSIONS_H

#include <cinolib/meshes/trimesh.h>

namespace cg3 {

class SimpleEigenMesh;
void eigenMeshToTrimesh(cinolib::Trimesh<>& m, const cg3::SimpleEigenMesh& simpleEigenMesh);

class Dcel;
void dcelToTrimesh(cinolib::Trimesh<>& m, const cg3::Dcel &d);

} //namespace cg3

#ifndef CG3_STATIC
#define CG3_CINOLIB_MESH_CONVERSIONS_CPP "cinolib_mesh_conversions.cpp"
#include CG3_CINOLIB_MESH_CONVERSIONS_CPP
#undef CG3_CINOLIB_MESH_CONVERSIONS_CPP
#endif

#endif // CG3_CINOLIB_MESH_CONVERSIONS_H

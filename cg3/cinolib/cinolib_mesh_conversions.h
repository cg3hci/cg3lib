/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_CINOLIB_MESH_CONVERSIONS_H
#define CG3_CINOLIB_MESH_CONVERSIONS_H

#include <cinolib/meshes/trimesh.h>

#ifdef CG3_EIGENMESH_DEFINED
#include <cg3/meshes/eigenmesh/eigenmesh.h>
#endif //CG3_EIGENMESH_DEFINED

#ifdef CG3_DCEL_DEFINED
#include <cg3/meshes/dcel/dcel.h>
#endif //CG3_DCEL_DEFINED

namespace cg3 {
    #ifdef CG3_EIGENMESH_DEFINED
    void eigenMeshToTrimesh(cinolib::Trimesh<>& m, const cg3::SimpleEigenMesh& simpleEigenMesh);
    #endif //CG3_EIGENMESH_DEFINED

    #ifdef CG3_DCEL_DEFINED
    void dcelToTrimesh(cinolib::Trimesh<>& m, const cg3::Dcel &d);
    #endif //CG3_DCEL_DEFINED
}

#endif // CG3_CINOLIB_MESH_CONVERSIONS_H

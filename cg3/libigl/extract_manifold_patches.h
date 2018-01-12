/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_LIBIGL_EXTRACT_MANIFOLD_PATCHES_H
#define CG3_LIBIGL_EXTRACT_MANIFOLD_PATCHES_H

#include <cg3/meshes/eigenmesh/eigenmesh.h>

namespace cg3 {

namespace libigl {

int extractManifoldPatches(const SimpleEigenMesh& m, Eigen::Matrix<int, Eigen::Dynamic, 1>& I);
int extractManifoldPatches(const SimpleEigenMesh& m);

}

}

#include "extract_manifold_patches.tpp"

#endif // CG3_LIBIGL_EXTRACT_MANIFOLD_PATCHES_H

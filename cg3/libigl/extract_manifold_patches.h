#ifndef CG3_LIBIGL_EXTRACT_MANIFOLD_PATCHES_H
#define CG3_LIBIGL_EXTRACT_MANIFOLD_PATCHES_H

#include <cg3/meshes/eigenmesh/eigenmesh.h>

namespace cg3 {

namespace libigl {

int extractManifoldPatches(const SimpleEigenMesh& m, Eigen::Matrix<int, Eigen::Dynamic, 1>& I);
int extractManifoldPatches(const SimpleEigenMesh& m);

}

}

#include "extract_manifold_patches.ipp"

#endif // CG3_LIBIGL_EXTRACT_MANIFOLD_PATCHES_H

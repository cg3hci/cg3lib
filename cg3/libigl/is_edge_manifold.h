/**
  * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
  * This Source Code Form is subject to the terms of the GNU GPL 3.0
  *
  * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
  */

#ifndef CG3_LIBIGL_IS_EDGE_MANIFOLD_H
#define CG3_LIBIGL_IS_EDGE_MANIFOLD_H

#include <cg3/meshes/eigenmesh/eigenmesh.h>

namespace cg3 {

namespace libgil {

inline bool isEdgeManifold(const SimpleEigenMesh& input);

}

}

#include "is_edge_manifold.tpp"

#endif // CG3_LIBIGL_IS_EDGE_MANIFOLD_H

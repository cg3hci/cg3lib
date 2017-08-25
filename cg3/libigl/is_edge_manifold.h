#ifndef CG3_LIBIGL_IS_EDGE_MANIFOLD_H
#define CG3_LIBIGL_IS_EDGE_MANIFOLD_H

#include <cg3/meshes/eigenmesh/eigenmesh.h>

namespace cg3 {

namespace libgil {

inline bool isEdgeManifold(const SimpleEigenMesh& input);

}

}

#include "is_edge_manifold.ipp"

#endif // CG3_LIBIGL_IS_EDGE_MANIFOLD_H

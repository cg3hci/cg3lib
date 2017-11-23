#ifndef CG3_LIBIGL_CONNECTED_COMPONENTS_H
#define CG3_LIBIGL_CONNECTED_COMPONENTS_H

#include <cg3/meshes/eigenmesh/eigenmesh.h>

namespace cg3 {

namespace libigl {

std::vector<SimpleEigenMesh> getConnectedComponents(const SimpleEigenMesh &m);

}

}

#include "connected_components.tpp"

#endif // CG3_LIBIGL_CONNECTED_COMPONENTS_H

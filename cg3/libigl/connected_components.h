#ifndef CG3_CONNECTED_COMPONENTS_H
#define CG3_CONNECTED_COMPONENTS_H

#include <cg3/meshes/eigenmesh/eigenmesh.h>

namespace cg3 {

namespace libigl {

std::vector<SimpleEigenMesh> getConnectedComponents(const SimpleEigenMesh &m);

}

}

#endif // CG3_CONNECTED_COMPONENTS_H

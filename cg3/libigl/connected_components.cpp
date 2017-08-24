#include "connected_components.h"

#include "internal/eigenmesh_libigl_algorithms.h"

std::vector<cg3::SimpleEigenMesh> cg3::libigl::getConnectedComponents(const cg3::SimpleEigenMesh &m) {
    return internal::EigenMeshLibIglAlgorithms::getConnectedComponents(m);
}

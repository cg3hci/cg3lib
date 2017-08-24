#include "is_edge_manifold.h"

#include "internal/eigenmesh_libigl_algorithms.h"

namespace cg3 {

namespace libigl {

bool isEdgeManifold(const SimpleEigenMesh &input) {
    return internal::EigenMeshLibIglAlgorithms::isEdgeManifold(input);
}

}

}

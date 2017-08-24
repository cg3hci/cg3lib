#include "remove_unreferenced_vertices.h"

#include "internal/eigenmesh_libigl_algorithms.h"

namespace cg3 {

namespace libigl {

void removeUnreferencedVertices(SimpleEigenMesh &input, Eigen::Matrix<int, Eigen::Dynamic, 1> &I) {
    internal::EigenMeshLibIglAlgorithms::removeUnreferencedVertices(input, I);
}

void removeUnreferencedVertices(SimpleEigenMesh &input) {
    Eigen::VectorXi I;
    internal::EigenMeshLibIglAlgorithms::removeUnreferencedVertices(input, I);
}

}

}

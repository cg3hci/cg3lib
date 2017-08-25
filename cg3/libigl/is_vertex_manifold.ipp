#include "is_vertex_manifold.h"

#include "internal/eigenmesh_libigl_algorithms.h"

namespace cg3 {

namespace libigl {

inline bool isVertexManifold(const SimpleEigenMesh &input, Eigen::Matrix<bool, Eigen::Dynamic, 1> &B) {
    return internal::EigenMeshLibIglAlgorithms::isVertexManifold(input, B);
}

inline bool isVertexManifold(const SimpleEigenMesh &input) {
    Eigen::Matrix<bool, Eigen::Dynamic, 1> B;
    return internal::EigenMeshLibIglAlgorithms::isVertexManifold(input, B);
}

}

}

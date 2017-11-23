#include "remove_duplicate_vertices.h"

#include "internal/eigenmesh_libigl_algorithms.h"

namespace cg3 {

namespace libigl {

inline void removeDuplicateVertices(SimpleEigenMesh &input, double epsilon) {
    internal::EigenMeshLibIglAlgorithms::removeDuplicateVertices(input, epsilon);
}

inline void removeDuplicateVertices(SimpleEigenMesh &input, Eigen::Matrix<int, Eigen::Dynamic, 1> &I, double epsilon) {
    internal::EigenMeshLibIglAlgorithms::removeDuplicateVertices(input, I, epsilon);
}

inline void removeDuplicateVertices(EigenMesh &input, double epsilon) {
    internal::EigenMeshLibIglAlgorithms::removeDuplicateVertices(input, epsilon);
}

inline void removeDuplicateVertices(EigenMesh &input, Eigen::Matrix<int, Eigen::Dynamic, 1> &I, double epsilon) {
    internal::EigenMeshLibIglAlgorithms::removeDuplicateVertices(input, I, epsilon);
}

}

}

#include "decimate.h"

#include "internal/eigenmesh_libigl_algorithms.h"

namespace cg3 {

namespace libigl {

inline SimpleEigenMesh decimateMesh(const SimpleEigenMesh &m, int numberDesiredFaces, Eigen::VectorXi &mapping) {
    return internal::EigenMeshLibIglAlgorithms::decimateMesh(m, numberDesiredFaces, mapping);
}

inline SimpleEigenMesh decimateMesh(const SimpleEigenMesh &m, int numberDesiredFaces) {
    Eigen::VectorXi mapping;
    return internal::EigenMeshLibIglAlgorithms::decimateMesh(m, numberDesiredFaces, mapping);
}

inline EigenMesh decimateMesh(const EigenMesh &m, int numberDesiredFaces, Eigen::VectorXi &mapping) {
    return internal::EigenMeshLibIglAlgorithms::decimateMesh(m, numberDesiredFaces, mapping);
}

inline EigenMesh decimateMesh(const EigenMesh &m, int numberDesiredFaces) {
    Eigen::VectorXi mapping;
    return internal::EigenMeshLibIglAlgorithms::decimateMesh(m, numberDesiredFaces, mapping);
}

inline void decimateMesh(SimpleEigenMesh &m, int numberDesiredFaces, Eigen::VectorXi &mapping) {
    internal::EigenMeshLibIglAlgorithms::decimateMesh(m, numberDesiredFaces, mapping);
}

inline void decimateMesh(SimpleEigenMesh &m, int numberDesiredFaces) {
    Eigen::VectorXi mapping;
    internal::EigenMeshLibIglAlgorithms::decimateMesh(m, numberDesiredFaces, mapping);
}

inline void decimateMesh(EigenMesh &m, int numberDesiredFaces, Eigen::VectorXi &mapping) {
    internal::EigenMeshLibIglAlgorithms::decimateMesh(m, numberDesiredFaces, mapping);
}

inline void decimateMesh(EigenMesh &m, int numberDesiredFaces) {
    Eigen::VectorXi mapping;
    internal::EigenMeshLibIglAlgorithms::decimateMesh(m, numberDesiredFaces, mapping);
}

}

}



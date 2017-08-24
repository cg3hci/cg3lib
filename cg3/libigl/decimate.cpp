#include "decimate.h"

#include "internal/eigenmesh_libigl_algorithms.h"

namespace cg3 {

namespace libigl {

SimpleEigenMesh decimateMesh(const SimpleEigenMesh &m, int numberDesiredFaces, Eigen::VectorXi &mapping) {
    return internal::EigenMeshLibIglAlgorithms::decimateMesh(m, numberDesiredFaces, mapping);
}

SimpleEigenMesh decimateMesh(const SimpleEigenMesh &m, int numberDesiredFaces) {
    Eigen::VectorXi mapping;
    return internal::EigenMeshLibIglAlgorithms::decimateMesh(m, numberDesiredFaces, mapping);
}

EigenMesh decimateMesh(const EigenMesh &m, int numberDesiredFaces, Eigen::VectorXi &mapping) {
    return internal::EigenMeshLibIglAlgorithms::decimateMesh(m, numberDesiredFaces, mapping);
}

EigenMesh decimateMesh(const EigenMesh &m, int numberDesiredFaces) {
    Eigen::VectorXi mapping;
    return internal::EigenMeshLibIglAlgorithms::decimateMesh(m, numberDesiredFaces, mapping);
}

void decimateMesh(SimpleEigenMesh &m, int numberDesiredFaces, Eigen::VectorXi &mapping) {
    internal::EigenMeshLibIglAlgorithms::decimateMesh(m, numberDesiredFaces, mapping);
}

void decimateMesh(SimpleEigenMesh &m, int numberDesiredFaces) {
    Eigen::VectorXi mapping;
    internal::EigenMeshLibIglAlgorithms::decimateMesh(m, numberDesiredFaces, mapping);
}

void decimateMesh(EigenMesh &m, int numberDesiredFaces, Eigen::VectorXi &mapping) {
    internal::EigenMeshLibIglAlgorithms::decimateMesh(m, numberDesiredFaces, mapping);
}

void decimateMesh(EigenMesh &m, int numberDesiredFaces) {
    Eigen::VectorXi mapping;
    internal::EigenMeshLibIglAlgorithms::decimateMesh(m, numberDesiredFaces, mapping);
}

}

}



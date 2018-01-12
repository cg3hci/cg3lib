/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

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



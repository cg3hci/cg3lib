#include "face_adjacences.h"

#include "internal/eigenmesh_libigl_algorithms.h"

namespace cg3 {

namespace libigl {

Eigen::MatrixXi getFaceAdjacences(const SimpleEigenMesh &m) {
    return internal::EigenMeshLibIglAlgorithms::getFaceAdjacences(m);
}

}

}

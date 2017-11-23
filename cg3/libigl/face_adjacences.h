#ifndef CG3_LIBIGL_FACE_ADJACENCES_H
#define CG3_LIBIGL_FACE_ADJACENCES_H

#include <cg3/meshes/eigenmesh/eigenmesh.h>

namespace cg3 {

namespace libigl {

Eigen::MatrixXi getFaceAdjacences(const SimpleEigenMesh &m);

}

}

#include "face_adjacences.tpp"

#endif // CG3_LIBIGL_FACE_ADJACENCES_H

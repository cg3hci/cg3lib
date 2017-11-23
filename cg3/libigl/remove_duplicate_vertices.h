#ifndef CG3_LIBIGL_REMOVE_DUPLICATE_VERTICES_H
#define CG3_LIBIGL_REMOVE_DUPLICATE_VERTICES_H

#include <cg3/meshes/eigenmesh/eigenmesh.h>

namespace cg3 {

namespace libigl {

void removeDuplicateVertices(SimpleEigenMesh &input, double epsilon = CG3_EPSILON);
void removeDuplicateVertices(SimpleEigenMesh &input, Eigen::Matrix<int, Eigen::Dynamic, 1> &I, double epsilon = CG3_EPSILON);
void removeDuplicateVertices(EigenMesh &input, double epsilon = CG3_EPSILON);
void removeDuplicateVertices(EigenMesh &input, Eigen::Matrix<int, Eigen::Dynamic, 1> &I, double epsilon = CG3_EPSILON);

}

}

#include "remove_duplicate_vertices.tpp"

#endif // REMOVE_LIBIGL_DUPLICATE_VERTICES_H

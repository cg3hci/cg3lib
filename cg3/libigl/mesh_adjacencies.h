/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_LIBIGL_VERTEXADJACENCIES_H
#define CG3_LIBIGL_VERTEXADJACENCIES_H

#include <cg3/meshes/eigenmesh/eigenmesh.h>

namespace cg3 {
namespace libigl {

std::vector<std::vector<int>> vertexToVertexAdjacencies(const SimpleEigenMesh& m);

std::vector<std::vector<int>> vertexToFaceIncidences(const SimpleEigenMesh& m);

std::vector<std::vector<int>> faceToFaceAdjacencies(const SimpleEigenMesh &m);
void faceToFaceAdjacencies(const SimpleEigenMesh &m, Eigen::MatrixXi& adjacences);

} //namespace cg3::libigl
} //namespace cg3

#ifndef CG3_STATIC
#define CG3_LIBIGL_VERTEXADJACENCIES_CPP "mesh_adjacencies.cpp"
#include CG3_LIBIGL_VERTEXADJACENCIES_CPP
#undef CG3_LIBIGL_VERTEXADJACENCIES_CPP
#endif //CG3_STATIC

#endif // CG3_LIBIGL_VERTEXADJACENCIES_H

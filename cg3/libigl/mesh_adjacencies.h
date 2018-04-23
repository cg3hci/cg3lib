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

std::vector<std::vector<int>> getVertexVertexAdjacencies(const SimpleEigenMesh& m);
std::vector<std::vector<int>> getVertexFaceAdjacencies(const SimpleEigenMesh& m);
std::vector<std::vector<int>> getFaceFaceAdjacencies(const SimpleEigenMesh &m);

} //namespace cg3::libigl
} //namespace cg3

#include "mesh_adjacencies.tpp"

#endif // CG3_LIBIGL_VERTEXADJACENCIES_H

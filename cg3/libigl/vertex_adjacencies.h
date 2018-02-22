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

std::vector<std::vector<int>> getVertexAdjacencies(const SimpleEigenMesh &m);

}

}

#include "vertex_adjacencies.tpp"

#endif // CG3_LIBIGL_VERTEXADJACENCIES_H

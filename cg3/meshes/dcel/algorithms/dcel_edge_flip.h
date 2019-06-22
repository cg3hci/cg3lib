/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_DCEL_EDGE_FLIP_H
#define CG3_DCEL_EDGE_FLIP_H

#include <cg3/meshes/dcel/dcel.h>

namespace cg3 {
namespace dcelAlgorithms {

bool edgeFlip(Dcel& d, const cg3::Dcel::HalfEdge* he);

} //namespace cg3::dcelAlgorithms
} //namespace cg3

#ifndef CG3_STATIC
#define CG3_DCEL_EDGE_FLIP_CPP "dcel_edge_flip.cpp"
#include CG3_DCEL_EDGE_FLIP_CPP
#undef CG3_DCEL_EDGE_FLIP_CPP
#endif

#endif // CG3_DCEL_EDGE_FLIP_H

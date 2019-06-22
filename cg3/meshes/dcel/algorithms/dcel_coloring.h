/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_DCEL_COLORING_H
#define CG3_DCEL_COLORING_H

#include <cg3/meshes/dcel/dcel.h>

namespace cg3 {
namespace dcelAlgorithms {

void smartColoring(Dcel &d);

} //namespace cg3::dcelAlgorithms
} //namespace cg3

#ifndef CG3_STATIC
#define CG3_DCEL_COLORING_CPP "dcel_coloring.cpp"
#include CG3_DCEL_COLORING_CPP
#undef CG3_DCEL_COLORING_CPP
#endif

#endif // CG3_DCEL_COLORING_H

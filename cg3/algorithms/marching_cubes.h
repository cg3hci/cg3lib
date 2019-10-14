/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_MARCHING_CUBES_H
#define CG3_MARCHING_CUBES_H

#include <cg3/data_structures/lattices/regular_lattice.h>
#include <cg3/meshes/dcel/dcel_builder.h>

namespace cg3 {

cg3::Dcel marchingCubes(const cg3::RegularLattice3D<bool>& l);

} //namespace cg3

#ifndef CG3_STATIC
#define CG3_MARCHING_CUBES_CPP "marching_cubes.cpp"
#include CG3_MARCHING_CUBES_CPP
#undef CG3_MARCHING_CUBES_CPP
#endif

#endif // CG3_MARCHING_CUBES_H

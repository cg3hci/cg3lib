/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_DCEL_FLOODING_H
#define CG3_DCEL_FLOODING_H

#include <cg3/meshes/dcel/dcel.h>

namespace cg3 {
namespace dcelAlgorithms {

template <typename Comp>
std::set<const Dcel::Face*> floodDFS(const Dcel::Face* seed, Comp c);

template <typename Comp>
std::set<unsigned int> floodDFS(const Dcel& d, unsigned int seed, Comp c);


template <typename Comp>
std::set<const Dcel::Face*> floodBFS(const Dcel::Face* seed, Comp c);

template <typename Comp>
std::set<unsigned int> floodBFS(const Dcel& d, unsigned int seed, Comp c);

} //namespace cg3::dcelAlgorithms
} //namespace cg3

#include "dcel_flooding.tpp"

#endif // CG3_DCEL_FLOODING_H

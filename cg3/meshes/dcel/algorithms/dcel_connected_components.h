/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_DCEL_CONNECTED_COMPONENTS_H
#define CG3_DCEL_CONNECTED_COMPONENTS_H

#include <cg3/meshes/dcel/dcel.h>

namespace cg3 {
namespace dcelAlgorithms {

template <typename InputIterator>
std::vector< std::set<const Dcel::Face*> > connectedComponents(
        InputIterator first,
        InputIterator last);

#ifdef CG3_OLD_NAMES_COMPATIBILITY
template <typename InputIterator>
inline std::vector< std::set<const Dcel::Face*> > getConnectedComponents(
        InputIterator first,
        InputIterator last) {return connectedComponents(first, last);}
#endif

} //namespace cg3::dcelAlgorithms
} //namespace cg3

#include "dcel_connected_components.tpp"

#endif // CG3_DCEL_CONNECTED_COMPONENTS_H

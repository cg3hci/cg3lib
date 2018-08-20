/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "dcel_connected_components.h"
#include "dcel_flooding.h"

#include <cg3/utilities/set.h>

namespace cg3 {
namespace dcelAlgorithms {

template <typename InputIterator>
std::vector< std::set<const Dcel::Face*> > connectedComponents(
        InputIterator first,
        InputIterator last)
{
    struct Comp{
        const std::set<const Dcel::Face*> &cf;
        Comp(const std::set<const Dcel::Face*> &cf) : cf(cf) {}
        bool operator()(const Dcel::Face* f) {
            return cf.find(f) != cf.end();
        }
    };

    std::vector< std::set<const Dcel::Face*> > connectedComp;
    std::set<const Dcel::Face*> containedFaces(first, last);

    while (containedFaces.size() > 0){
        Comp comp(containedFaces);
        const Dcel::Face* f = *(containedFaces.begin());
        std::set<const Dcel::Face*> cc = floodBFS(f, comp);
        connectedComp.push_back(cc);
        containedFaces = difference(containedFaces, cc);
    }
    return connectedComp;
}

} //namespace cg3::dcelAlgorithms
} //namesoace cg3

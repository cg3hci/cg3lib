/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef DCEL_ALGORITHMS_H
#define DCEL_ALGORITHMS_H

#include <cg3/meshes/dcel/dcel.h>
#include <cg3/utilities/set.h>

#include "dcel_to_vectors.h"
#include "dcel_flooding.h"

namespace cg3 {
namespace dcelAlgorithms {

template <typename InputIterator>
BoundingBox getBoundingBoxOfFaces(InputIterator first, InputIterator last);

template <typename InputIterator>
std::vector< std::set<const Dcel::Face*> > getConnectedComponents(
        InputIterator first,
        InputIterator last);

}

template <typename InputIterator>
BoundingBox dcelAlgorithms::getBoundingBoxOfFaces(
        InputIterator first,
        InputIterator last)
{
    BoundingBox bb;
    const Dcel::Face* f = *first;
    bb.setMin(f->getOuterHalfEdge()->getFromVertex()->getCoordinate());
    bb.setMax(f->getOuterHalfEdge()->getFromVertex()->getCoordinate());

    while (first != last){
        f = *first;
        for (const Dcel::Vertex* v : f->incidentVertexIterator()){
            bb.min() = bb.min().min(v->getCoordinate());
            bb.max() = bb.max().max(v->getCoordinate());
        }
        ++first;
    }
    return bb;
}

template <typename InputIterator>
std::vector< std::set<const Dcel::Face*> > dcelAlgorithms::getConnectedComponents(
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

    std::vector< std::set<const Dcel::Face*> > connectedComponents;
    std::set<const Dcel::Face*> containedFaces(first, last);

    while (containedFaces.size() > 0){
        Comp comp(containedFaces);
        const Dcel::Face* f = *(containedFaces.begin());
        std::set<const Dcel::Face*> cc = floodDFS(f, comp);
        connectedComponents.push_back(cc);
        containedFaces = difference(containedFaces, cc);
    }
    return connectedComponents;
}

} //namespace cg3

#endif // DCEL_ALGORITHMS_H

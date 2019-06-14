/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "dcel_bounding_boxes.h"

namespace cg3 {
namespace dcelAlgorithms {

template <typename InputIterator>
BoundingBox3 boundingBoxOfFaces(
        InputIterator first,
        InputIterator last)
{
    BoundingBox3 bb;
    const Dcel::Face* f = *first;
    bb.setMin(f->outerHalfEdge()->fromVertex()->coordinate());
    bb.setMax(f->outerHalfEdge()->fromVertex()->coordinate());

    while (first != last){
        f = *first;
        for (const Dcel::Vertex* v : f->incidentVertexIterator()){
            bb.min() = bb.min().min(v->coordinate());
            bb.max() = bb.max().max(v->coordinate());
        }
        ++first;
    }
    return bb;
}

} //namespace cg3::dcelAlgorithms
} //namesoace cg3

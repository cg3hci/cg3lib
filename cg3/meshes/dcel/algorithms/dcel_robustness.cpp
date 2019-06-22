/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "dcel_robustness.h"
#include <cg3/geometry/utils3.h>

CG3_INLINE bool cg3::dcelAlgorithms::isWaterTight(const cg3::Dcel& mesh)
{
    for (const cg3::Dcel::HalfEdge* he : mesh.halfEdgeIterator())
        if (he->twin() == nullptr)
            return false;
    return true;
}

CG3_INLINE bool cg3::dcelAlgorithms::hasDegenerateFaces(const cg3::Dcel& mesh)
{

    for (const cg3::Dcel::Face* f : mesh.faceIterator()){
        const cg3::Dcel::Vertex* a = f->vertex1(), *b = f->vertex2(), *c = f->vertex3();
        if (f->isTriangle()){
            if (a->coordinate() == b->coordinate() || a->coordinate() == c->coordinate() || b->coordinate() == c->coordinate())
                return true;
        }
        else {
            //looking for the first non-collinear edges
            const cg3::Dcel::HalfEdge* edge = f->outerHalfEdge()->next()->next();
            const cg3::Dcel::Vertex* first = a;
            while (areCollinear(a->coordinate(), b->coordinate(), c->coordinate())){
                a = b;
                b = c;
                c = edge->toVertex();
                edge = edge->next();
                if (a == first) //if I reach the beginning, there are no non-collinear edges... degenerate polygon
                    return true;
            }
        }
    }
    return false;
}


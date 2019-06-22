/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "dcel_edge_flip.h"

namespace cg3 {
namespace dcelAlgorithms {

CG3_INLINE bool edgeFlip(Dcel& d, const Dcel::HalfEdge* che)
{
    if (!d.contains(che) || che->twin() == nullptr)
        return false;
    Dcel::HalfEdge* he = d.halfEdge(che->id());
    Dcel::HalfEdge* the = he->twin();
    Dcel::HalfEdge* phe = he->prev();
    Dcel::HalfEdge* nhe = he->next();
    Dcel::HalfEdge* pthe = the->prev();
    Dcel::HalfEdge* nthe = the->next();
    Dcel::Vertex* v1 = he->fromVertex();
    Dcel::Vertex* v2 = he->toVertex();
    Dcel::Vertex* v3 = nhe->toVertex();
    Dcel::Vertex* v4 = pthe->fromVertex();
    Dcel::Face* f1 = he->face();
    Dcel::Face* f2 = the->face();

    he->setFromVertex(v4);
    he->setToVertex(v3);
    the->setFromVertex(v3);
    the->setToVertex(v4);

    v1->setIncidentHalfEdge(nthe);
    v2->setIncidentHalfEdge(nhe);
    v3->setIncidentHalfEdge(phe);
    v4->setIncidentHalfEdge(pthe);
    v1->setCardinality(v1->cardinality()-1);
    v2->setCardinality(v2->cardinality()-1);
    v3->setCardinality(v3->cardinality()+1);
    v4->setCardinality(v4->cardinality()+1);

    nhe->setFace(f2);
    nthe->setFace(f1);
    f1->setOuterHalfEdge(he);
    f2->setOuterHalfEdge(nhe);

    he->setPrev(nthe);
    nthe->setNext(he);
    he->setNext(phe);
    phe->setPrev(he);
    phe->setNext(nthe);
    nthe->setPrev(phe);

    nhe->setPrev(pthe);
    pthe->setNext(nhe);
    nhe->setNext(the);
    the->setPrev(nhe);
    the->setNext(pthe);
    pthe->setPrev(the);

    f1->updateArea();
    f2->updateArea();
    v1->updateNormal();
    v2->updateNormal();
    v3->updateNormal();
    v4->updateNormal();
    return true;
}

} //namespace cg3::dcelAlgorithms
} //namespace cg3

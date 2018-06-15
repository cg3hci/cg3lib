/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "dcel_builder.h"

namespace cg3 {

DcelBuilder::DcelBuilder(Dcel startingDcel) : d(startingDcel)
{
    for (cg3::Dcel::Vertex* v : d.vertexIterator()) {
        mapVertices[v->getCoordinate()] = v->getId();
    }
    //maybe initializa also edges?
}

Dcel& DcelBuilder::dcel()
{
    return d;
}

unsigned int DcelBuilder::addVertex(const Pointd& p, const Vec3& n, const Color &c)
{
    if (mapVertices.find(p) == mapVertices.end()){
        cg3::Dcel::Vertex* v = d.addVertex(p, n, c);
        mapVertices[p] = v->getId();
        return v->getId();
    }
    else
        return mapVertices[p];
}

int DcelBuilder::addFace(
        unsigned int vid1,
        unsigned int vid2,
        unsigned int vid3,
        const Color& c)
{
    //one of the three ids does not exist in the dcel
    if (d.getVertex(vid1) == nullptr ||
            d.getVertex(vid2) == nullptr ||
            d.getVertex(vid3) == nullptr)
        return -1;

    std::pair<unsigned int, unsigned int> pe1(vid1, vid2);
    std::pair<unsigned int, unsigned int> pe2(vid2, vid3);
    std::pair<unsigned int, unsigned int> pe3(vid3, vid1);

    // one of the three edges already exists in the dcel ->
    // bad orientation of face or non edge-manifold mesh
    if (mapHalfEdges.find(pe1) != mapHalfEdges.end() ||
            mapHalfEdges.find(pe2) != mapHalfEdges.end() ||
            mapHalfEdges.find(pe3) != mapHalfEdges.end())
        return -1;

    std::pair<unsigned int, unsigned int> tpe1(vid2, vid1);
    std::pair<unsigned int, unsigned int> tpe2(vid3, vid2);
    std::pair<unsigned int, unsigned int> tpe3(vid1, vid3);

    cg3::Dcel::HalfEdge* te1 = nullptr, *te2 = nullptr, *te3 = nullptr;
    std::map<std::pair<unsigned int, unsigned int>, unsigned int>::iterator it =
            mapHalfEdges.find(tpe1);
    if (it != mapHalfEdges.end())
        te1 = d.getHalfEdge(it->second);
    it = mapHalfEdges.find(tpe2);
    if (it != mapHalfEdges.end())
        te2 = d.getHalfEdge(it->second);
    it = mapHalfEdges.find(tpe3);
    if (it != mapHalfEdges.end())
        te3 = d.getHalfEdge(it->second);

    //get vertices
    cg3::Dcel::Vertex* v1 = d.getVertex(vid1);
    cg3::Dcel::Vertex* v2 = d.getVertex(vid2);
    cg3::Dcel::Vertex* v3 = d.getVertex(vid3);

    //add half edges
    cg3::Dcel::HalfEdge* he1 = d.addHalfEdge();
    cg3::Dcel::HalfEdge* he2 = d.addHalfEdge();
    cg3::Dcel::HalfEdge* he3 = d.addHalfEdge();

    //from and to vertex
    he1->setFromVertex(v1); he1->setToVertex(v2);
    he2->setFromVertex(v2); he2->setToVertex(v3);
    he3->setFromVertex(v3); he3->setToVertex(v1);

    //prev and next
    he1->setPrev(he3); he1->setNext(he2);
    he2->setPrev(he1); he2->setNext(he3);
    he3->setPrev(he2); he3->setNext(he1);

    //twin
    he1->setTwin(te1);
    if (te1)
        te1->setTwin(he1);
    he2->setTwin(te2);
    if (te2)
        te2->setTwin(he2);
    he3->setTwin(te3);
    if (te3)
        te3->setTwin(he3);

    //vertex incident
    v1->setIncidentHalfEdge(he1);
    v2->setIncidentHalfEdge(he2);
    v3->setIncidentHalfEdge(he3);

    //face
    cg3::Dcel::Face* f = d.addFace();
    he1->setFace(f);
    he2->setFace(f);
    he3->setFace(f);
    f->setColor(c);
    f->setOuterHalfEdge(he1);

    mapHalfEdges.insert(std::make_pair(std::make_pair(vid1, vid2), he1->getId()));
    mapHalfEdges.insert(std::make_pair(std::make_pair(vid2, vid3), he2->getId()));
    mapHalfEdges.insert(std::make_pair(std::make_pair(vid3, vid1), he3->getId()));

    f->updateNormal();
    return f->getId();
}

int DcelBuilder::addFace(
        const Pointd& p1,
        const Pointd& p2,
        const Pointd& p3,
        const Color& c)
{
    unsigned int vid1, vid2, vid3;

    //setting vids
    std::map<cg3::Pointd, unsigned int>::iterator it;
    it = mapVertices.find(p1);
    if (it == mapVertices.end())
        vid1 = addVertex(p1);
    else
        vid1 = it->second;

    it = mapVertices.find(p2);
    if (it == mapVertices.end())
        vid2 = addVertex(p2);
    else
        vid2 = it->second;

    it = mapVertices.find(p3);
    if (it == mapVertices.end())
        vid3 = addVertex(p3);
    else
        vid3 = it->second;

    return addFace(vid1, vid2, vid3, c);
}

void DcelBuilder::finalize()
{
    d.updateBoundingBox();
    d.updateVertexNormals();
}

}

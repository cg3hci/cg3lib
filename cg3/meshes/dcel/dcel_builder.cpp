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
    vectorVertices.resize(d.getNumberVertices(), nullptr);
    for (cg3::Dcel::Vertex* v : d.vertexIterator()) {
        if (v->getId() >= vectorVertices.size()){
            unsigned int oldsize = vectorVertices.size();
            vectorVertices.resize(v->getId()+1);
            for (unsigned int i = oldsize; i < v->getId(); i++)
                vectorVertices[i] = nullptr;
        }
        vectorVertices[v->getId()] = v;
        mapVertices[v->getCoordinate()] = v;
    }
}

Dcel& DcelBuilder::dcel()
{
    return d;
}

unsigned int DcelBuilder::addVertex(const Pointd& p, const Vec3& n, const Color &c)
{
    if (mapVertices.find(p) == mapVertices.end()){
        cg3::Dcel::Vertex* v = d.addVertex(p, n, c);
        mapVertices[p] = v;
        return v->getId();
    }
    else
        return mapVertices[p]->getId();
}

int DcelBuilder::addFace(
        unsigned int vid1,
        unsigned int vid2,
        unsigned int vid3,
        const Color& c)
{
    //one of the three ids does not exist in the dcel
    if (vid1 >= vectorVertices.size() ||
            vid2 >= vectorVertices.size() ||
            vid3 >= vectorVertices.size())
        return -1;
    if (vectorVertices[vid1] == nullptr ||
            vectorVertices[vid2] == nullptr ||
            vectorVertices[vid3] == nullptr)
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
    std::unordered_map<std::pair<unsigned int, unsigned int>, cg3::Dcel::HalfEdge*>::iterator it =
            mapHalfEdges.find(tpe1);
    if (it != mapHalfEdges.end())
        te1 = it->second;
    it = mapHalfEdges.find(tpe2);
    if (it != mapHalfEdges.end())
        te2 = it->second;
    it = mapHalfEdges.find(tpe3);
    if (it != mapHalfEdges.end())
        te3 = it->second;

    //get vertices
    cg3::Dcel::Vertex* v1 = vectorVertices[vid1];
    cg3::Dcel::Vertex* v2 = vectorVertices[vid2];
    cg3::Dcel::Vertex* v3 = vectorVertices[vid3];

    //add half edges
    cg3::Dcel::HalfEdge* he1 = d.addHalfEdge();
    cg3::Dcel::HalfEdge* he2 = d.addHalfEdge();
    cg3::Dcel::HalfEdge* he3 = d.addHalfEdge();

    //from and to vertex
    he1->setFromVertex(v1); he1->setToVertex(v2);
    he2->setFromVertex(v2); he1->setToVertex(v3);
    he3->setFromVertex(v3); he1->setToVertex(v1);

    //prev and next
    he1->setPrev(he3); he1->setNext(he2);
    he2->setPrev(he1); he2->setNext(he3);
    he3->setPrev(he2); he3->setNext(he1);

    //twin
    he1->setTwin(te1);
    he2->setTwin(te2);
    he3->setTwin(te3);

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

    mapHalfEdges.insert(std::make_pair(std::make_pair(vid1, vid2), he1));
    mapHalfEdges.insert(std::make_pair(std::make_pair(vid2, vid3), he2));
    mapHalfEdges.insert(std::make_pair(std::make_pair(vid3, vid1), he3));

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
    std::unordered_map<cg3::Pointd, cg3::Dcel::Vertex*>::iterator it;
    it = mapVertices.find(p1);
    if (it == mapVertices.end())
        vid1 = addVertex(p1);
    else
        vid1 = it->second->getId();

    it = mapVertices.find(p2);
    if (it == mapVertices.end())
        vid2 = addVertex(p2);
    else
        vid2 = it->second->getId();

    it = mapVertices.find(p3);
    if (it == mapVertices.end())
        vid3 = addVertex(p3);
    else
        vid3 = it->second->getId();

    return addFace(vid1, vid2, vid3, c);
}

void DcelBuilder::finalize()
{
    d.updateBoundingBox();
    d.updateVertexNormals();
}

}

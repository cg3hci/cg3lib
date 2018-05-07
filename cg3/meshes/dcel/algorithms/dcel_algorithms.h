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

namespace cg3 {

namespace dcelAlgorithms {

void getVectorFaces(std::vector<const Dcel::Face*> &vector, const Dcel& d);
void getVectorFaces(std::vector<Dcel::Face*> &vector, Dcel& d);

static std::vector<const Dcel::Vertex*> dummymv;
static std::vector<const Dcel::Face*> dummymf;
void getVectorMesh(
        std::vector< Pointd > &coords,
        std::vector< std::vector<int>> &faces,
        const Dcel &d,
        std::vector<const Dcel::Vertex*> &mappingVertices = dummymv,
        std::vector<const Dcel::Face*> &mappingFaces = dummymf);

void smartColoring(Dcel &d);

template <typename InputIterator>
BoundingBox getBoundingBoxOfFaces(InputIterator first, InputIterator last);

template <typename Comp>
std::set<const Dcel::Face*> flood(const Dcel::Face* seed, Comp c);

template <typename Comp>
std::set<unsigned int> flood(const Dcel& d, unsigned int seed, Comp c);

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

/**
 * @brief DcelAlgorithms::flood
 * executes a flood starting from the seed face and inserts in the returnes sets
 * all the faces f such that c(f) returns true
 * @param seed: start face
 * @param c: a structure which contains a single parameter operator () that takes a face
 * and returns a bool
 */
template <typename Comp>
std::set<const Dcel::Face*> dcelAlgorithms::flood(const Dcel::Face* seed, Comp c)
{
    std::set<const Dcel::Face*> faces;
    std::vector<const Dcel::Face *> stack_faces; // only triangles with same label of
                                                 //the patch will stay on the stack

    faces.insert(seed);

    for (const Dcel::Face* adjacent : seed->adjacentFaceIterator()){
        // adding neighbor triangles (if comp returns true) to the stack
        if (c(adjacent)) stack_faces.push_back(adjacent);
    }

    // while there aren't other triangles on the stack
    while (stack_faces.size() > 0) {
        const Dcel::Face* fi = stack_faces[stack_faces.size()-1];
        stack_faces.pop_back(); //pop
        faces.insert(fi);
        for (const Dcel::Face* adjacent : fi->adjacentFaceIterator()) {
            if (c(adjacent)) {
                if (faces.find(adjacent) == faces.end())
                    stack_faces.push_back(adjacent);
            }
        }
    }
    return faces;
}

template<typename Comp>
std::set<unsigned int> dcelAlgorithms::flood(const Dcel& d, unsigned int seed, Comp c)
{
    std::set<unsigned int> faces;
    std::vector<const Dcel::Face *> stack_faces; // only triangles with same label of
                                                 //the patch will stay on the stack

    faces.insert(seed);

    for (const Dcel::Face* adjacent : d.getFace(seed)->adjacentFaceIterator()){
        // adding neighbor triangles (if comp returns true) to the stack
        if (c(adjacent)) stack_faces.push_back(adjacent);
    }

    // while there aren't other triangles on the stack
    while (stack_faces.size() > 0) {
        const Dcel::Face* fi = stack_faces[stack_faces.size()-1];
        stack_faces.pop_back(); //pop
        faces.insert(fi->getId());
        for (const Dcel::Face* adjacent : fi->adjacentFaceIterator()) {
            if (c(adjacent)) {
                if (faces.find(adjacent->getId()) == faces.end())
                    stack_faces.push_back(adjacent);
            }
        }
    }
    return faces;
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
        std::set<const Dcel::Face*> cc = flood(f, comp);
        connectedComponents.push_back(cc);
        containedFaces = difference(containedFaces, cc);
    }
    return connectedComponents;
}

} //namespace cg3

#endif // DCEL_ALGORITHMS_H

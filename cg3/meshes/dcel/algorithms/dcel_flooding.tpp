/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "dcel_flooding.h"

namespace cg3 {

/**
 * @brief DcelAlgorithms::flood
 * executes a flood starting from the seed face and inserts in the returnes sets
 * all the faces f such that c(f) returns true, using a DFS approach
 * @param seed: start face
 * @param c: a structure which contains a single parameter operator () that takes a face
 * and returns a bool
 */
template <typename Comp>
std::set<const Dcel::Face*> dcelAlgorithms::floodDFS(const Dcel::Face* seed, Comp c)
{
    std::set<const Dcel::Face*> faces;
    std::vector<const Dcel::Face *> stack_faces; // only triangles with same label of
                                                 //the patch will stay on the stack
    if (!c(seed))
        return  faces;

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
std::set<unsigned int> dcelAlgorithms::floodDFS(const Dcel& d, unsigned int seed, Comp c)
{
    std::set<unsigned int> faces;
    std::vector<const Dcel::Face *> stack_faces; // only triangles with same label of
                                                 //the patch will stay on the stack
    if (!c(d.face(seed)))
        return  faces;

    faces.insert(seed);

    for (const Dcel::Face* adjacent : d.face(seed)->adjacentFaceIterator()){
        // adding neighbor triangles (if comp returns true) to the stack
        if (c(adjacent)) stack_faces.push_back(adjacent);
    }

    // while there aren't other triangles on the stack
    while (stack_faces.size() > 0) {
        const Dcel::Face* fi = stack_faces[stack_faces.size()-1];
        stack_faces.pop_back(); //pop
        faces.insert(fi->id());
        for (const Dcel::Face* adjacent : fi->adjacentFaceIterator()) {
            if (c(adjacent)) {
                if (faces.find(adjacent->id()) == faces.end())
                    stack_faces.push_back(adjacent);
            }
        }
    }
    return faces;
}

/**
 * @brief DcelAlgorithms::floodBFS
 * executes a flood starting from the seed face and inserts in the returnes sets
 * all the faces f such that c(f) returns true, using a BFS approach
 * @param seed: start face
 * @param c: a structure which contains a single parameter operator () that takes a face
 * and returns a bool
 */
template <typename Comp>
std::set<const Dcel::Face*> dcelAlgorithms::floodBFS(const Dcel::Face* seed, Comp c)
{
    std::set<const cg3::Dcel::Face*> set;

    if (!c(seed))
        return  set;

    set.insert(seed);
    std::list<const cg3::Dcel::Face *> queue_faces; // only triangles with same label of
                                                     //the patch will stay on the queue
    for (const cg3::Dcel::Face* adjacent : seed->adjacentFaceIterator()){
        if (c(adjacent))
            queue_faces.push_back(adjacent);
    }

    // while there aren't other triangles on the stack
    while (queue_faces.size() > 0) {
        const cg3::Dcel::Face* fi = queue_faces.front();
        queue_faces.pop_front(); //pop
        if (set.find(fi) == set.end()){
            set.insert(fi);
            for (const cg3::Dcel::Face* adjacent : fi->adjacentFaceIterator()) {
                if (c(adjacent) &&
                        set.find(adjacent) == set.end()) {
                    queue_faces.push_back(adjacent);
                }
            }
        }
    }
    return set;
}

template<typename Comp>
std::set<unsigned int> dcelAlgorithms::floodBFS(const Dcel& d, unsigned int seed, Comp c)
{
    std::set<unsigned int> set;

    if (!c(d.face(seed)))
        return  set;

    set.insert(seed);
    const cg3::Dcel::Face* fseed = d.face(seed);
    std::list<const cg3::Dcel::Face *> queue_faces; // only triangles with same label of
                                                     //the patch will stay on the queue
    for (const cg3::Dcel::Face* adjacent : fseed->adjacentFaceIterator()){
        if (c(adjacent))
            queue_faces.push_back(adjacent);
    }

    // while there aren't other triangles on the stack
    while (queue_faces.size() > 0) {
        const cg3::Dcel::Face* fi = queue_faces.front();
        queue_faces.pop_front(); //pop
        if (set.find(fi->id()) == set.end()){
            set.insert(fi->id());
            for (const cg3::Dcel::Face* adjacent : fi->adjacentFaceIterator()) {
                if (c(adjacent) &&
                        set.find(adjacent->id()) == set.end()) {
                    queue_faces.push_back(adjacent);
                }
            }
        }
    }
    return set;
}

} //namespace cg3

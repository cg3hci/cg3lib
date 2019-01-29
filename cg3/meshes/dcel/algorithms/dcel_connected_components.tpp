/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "dcel_connected_components.h"
#include "dcel_flooding.h"

#include <cg3/utilities/set.h>
#include "../dcel_builder.h"

namespace cg3 {
namespace dcelAlgorithms {

inline bool isAConnectedComponent(const cg3::Dcel& inputMesh) {
    return isAConnectedComponent(inputMesh.faceBegin(), inputMesh.faceEnd());
}

template <typename InputIterator>
bool isAConnectedComponent(InputIterator first,
                           InputIterator last)
{
    struct Comp{
        const std::set<const Dcel::Face*> &cf;
        Comp(const std::set<const Dcel::Face*> &cf) : cf(cf) {}
        bool operator()(const Dcel::Face* f) {
            return cf.find(f) != cf.end();
        }
    };

    std::set<const Dcel::Face*> containedFaces(first, last);
    Comp comp(containedFaces);
    const Dcel::Face* f = *(containedFaces.begin());
    std::set<const Dcel::Face*> cc = floodBFS(f, comp);

    return cc.size() == containedFaces.size();
}

inline std::vector<Dcel> connectedComponents(const Dcel &inputMesh)
{
    std::vector<Dcel> cc;

    std::vector< std::set<const Dcel::Face*> > cci = connectedComponents(inputMesh.faceBegin(), inputMesh.faceEnd());

    if (cci.size() > 1) {
        for (const std::set<const Dcel::Face*> &s : cci){
            DcelBuilder builder;
            for (const Dcel::Face* f : s){
                builder.addFace(f->vertex1()->coordinate(), f->vertex2()->coordinate(), f->vertex3()->coordinate(), f->color(), f->id());
            }
            builder.finalize();
            cc.push_back(builder.dcel());
        }
    }
    else cc.push_back(inputMesh);

    return cc;
}

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

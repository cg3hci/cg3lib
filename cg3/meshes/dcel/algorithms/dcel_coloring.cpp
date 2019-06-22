/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "dcel_coloring.h"
#include "dcel_to_vectors.h"
#include <cg3/utilities/set.h>
#include <cg3/utilities/utils.h>

namespace cg3 {

CG3_INLINE void dcelAlgorithms::smartColoring(Dcel& d)
{
    struct adjComp {
        std::set<Dcel::Face*> getAdjacences(Dcel::Face* f){
            std::set<Dcel::Face*> adjacents;
            for (Dcel::Face* adj : f->adjacentFaceIterator()){
                adjacents.insert(adj);
            }
            return adjacents;
        }
    };

    std::vector<Dcel::Face*> vectorF;
    vectorFaces(vectorF, d);
    std::map<Dcel::Face*, Color> mapColors = cg3::smartColoring(vectorF, adjComp());

    for (std::pair<Dcel::Face*, Color> p : mapColors){
        (p.first)->setColor(p.second);
    }
}

} //namespace cg3

/**
  * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
  * This Source Code Form is subject to the terms of the GNU GPL 3.0
  *
  * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
  */

#include "cgal_signeddistances.h"

namespace cg3 {

std::vector<double> cgal::signedDistances::getUnsignedDistances(
        const std::vector<Pointd>& points, const AABBTree& tree) {

    std::vector<double> distances(points.size(), 0);
    size_t size = distances.size();

    #pragma omp parallel for
    for (unsigned int i = 0; i < size; i++){
        distances[i] = tree.getSquaredDistance(points[i]);
    }

    return distances;
}

}

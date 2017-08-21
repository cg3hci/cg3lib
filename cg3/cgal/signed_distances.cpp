#include "signed_distances.h"

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

#ifndef CG3_CGAL_SIGNED_DISTANCES_H
#define CG3_CGAL_SIGNED_DISTANCES_H

#include <cg3/utilities/utils.h>
#include <cg3/geometry/point.h>
#include <cg3/geometry/2d/point2d.h>

#include "aabb_tree.h"

#include <vector>

namespace cg3 {

namespace cgal {
    namespace signedDistances {
        std::vector<double> getUnsignedDistances(const std::vector<Pointd> &points, const AABBTree &tree);
    }
}

}

#endif // CG3_CGAL_SIGNED_DISTANCES_H

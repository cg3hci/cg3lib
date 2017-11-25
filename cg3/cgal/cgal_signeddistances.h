/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * @author    Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_CGAL_SIGNEDDISTANCES_H
#define CG3_CGAL_SIGNEDDISTANCES_H

#include <cg3/utilities/utils.h>
#include <cg3/geometry/point.h>
#include <cg3/geometry/2d/point2d.h>

#include "cgal_aabbtree.h"

#include <vector>

namespace cg3 {

namespace cgal {
    namespace signedDistances {
        std::vector<double> getUnsignedDistances(const std::vector<Pointd> &points, const AABBTree &tree);
    }
}

}

#endif // CG3_CGAL_SIGNEDDISTANCES_H

#ifndef CG3_SIGNEDDISTANCES_H
#define CG3_SIGNEDDISTANCES_H

#include <cg3/utilities/utils.h>
#include <cg3/geometry/point.h>
#include <cg3/geometry/2d/point2d.h>

#include "aabbtree.h"

#include <vector>

namespace cg3 {

namespace CGALInterface {
    namespace SignedDistances {
        std::vector<double> getUnsignedDistances(const std::vector<Pointd> &points, const AABBTree &tree);
    }
}

}

#endif // CG3_SIGNEDDISTANCES_H

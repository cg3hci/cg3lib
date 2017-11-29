#ifndef CG3_INTERSECTIONS2D_H
#define CG3_INTERSECTIONS2D_H

#include "cg3/utilities/utils.h"

#include "cg3/geometry/segment.h"

namespace cg3 {

namespace internal {

static Point2Dd point2DDummy;

}

bool checkSegmentIntersection(
        const Segment2Dd& seg1, const Segment2Dd& seg2,
        const bool ignoreEndPoints);

void checkSegmentIntersection(
        const Segment2Dd& seg1, const Segment2Dd& seg2,
        char& code,
        const double eps = cg3::CG3_EPSILON,
        Point2Dd& intersectionPoint = internal::point2DDummy);

}

#endif // CG3_INTERSECTIONS2D_H
#ifndef CG3_INTERSECTIONS_H
#define CG3_INTERSECTIONS_H

#include "cg3/utilities/utils.h"

#include "segment.h"

namespace cg3 {


static Point2Dd point2DDummy;

bool checkSegmentIntersection(
        const Segment2Dd& seg1, const Segment2Dd& seg2,
        const bool ignoreEndPoints);

void checkSegmentIntersection(
        const Segment2Dd& seg1, const Segment2Dd& seg2,
        char& code,
        const double eps = cg3::CG3_EPSILON,
        Point2Dd& intersectionPoint = point2DDummy);

}

#endif // CG3_INTERSECTIONS_H

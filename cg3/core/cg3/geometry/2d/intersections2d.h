/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */

#ifndef CG3_INTERSECTIONS2D_H
#define CG3_INTERSECTIONS2D_H

#include "cg3/utilities/utils.h"

#include "cg3/geometry/2d/segment2d.h"

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

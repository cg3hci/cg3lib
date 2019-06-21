/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */

#ifndef CG3_INTERSECTIONS2_H
#define CG3_INTERSECTIONS2_H

#include <cg3/utilities/const.h>
#include "segment2.h"

namespace cg3 {
namespace internal {

static Point2d point2DDummy;

} //namespace cg3::internal

bool checkSegmentIntersection2(
        const Segment2d& seg1,
        const Segment2d& seg2,
        const bool ignoreEndPoints);

void checkSegmentIntersection2(
        const Segment2d& seg1,
        const Segment2d& seg2,
        char& code,
        const double eps = cg3::CG3_EPSILON,
        Point2d& intersectionPoint = internal::point2DDummy);

} //namespace cg3

#ifndef CG3_STATIC
#define CG3_INTERSECTIONS2_CPP "intersections2.cpp"
#include CG3_INTERSECTIONS2_CPP
#undef CG3_INTERSECTIONS2_CPP
#endif

#endif // CG3_INTERSECTIONS2_H

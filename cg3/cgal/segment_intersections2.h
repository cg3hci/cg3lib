/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */
#ifndef CG3_CGAL_SEGMENT_INTERSECTIONS2_H
#define CG3_CGAL_SEGMENT_INTERSECTIONS2_H

#include <cg3/geometry/segment2.h>

namespace cg3 {
namespace cgal {

bool checkSegmentIntersection2D(
        const Segment2d& seg1, const Segment2d& seg2,
        const bool& ignoreEndPoints);

std::vector<Segment2d> segmentIntersection2D(
        const Segment2d& seg1, const Segment2d& seg2,
        const bool& ignoreEndPoints);

} //namespace cg3::cgal
} //namespace cg3

#endif // CG3_CGAL_SEGMENT_INTERSECTIONS2_H

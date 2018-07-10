/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */
#ifndef CG3_CGAL_INTERSECTIONS2D_H
#define CG3_CGAL_INTERSECTIONS2D_H

#include <cg3/geometry/2d/segment2d.h>

namespace cg3 {
namespace cgal {

bool checkSegmentIntersection2D(
        const Segment2Dd& seg1, const Segment2Dd& seg2,
        const bool& ignoreEndPoints);

std::vector<Segment2Dd> segmentIntersection2D(
        const Segment2Dd& seg1, const Segment2Dd& seg2,
        const bool& ignoreEndPoints);

#ifdef CG3_OLD_NAMES_COMPATIBILITY
inline std::vector<Segment2Dd> getSegmentIntersection2D(
        const Segment2Dd& seg1, const Segment2Dd& seg2,
        const bool& ignoreEndPoints)
{
    return segmentIntersection2D(seg1, seg2, ignoreEndPoints);
}
#endif

} //namespace cg3::cgal
} //namespace cg3

#endif // CG3_CGAL_INTERSECTIONS_H

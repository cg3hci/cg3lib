#ifndef CG3_CGAL_INTERSECTIONS_H
#define CG3_CGAL_INTERSECTIONS_H

#include "cg3/geometry/segment.h"


namespace cg3 {
namespace cgal {

bool checkSegmentIntersection2D(
        const Segment2Dd& seg1, const Segment2Dd& seg2,
        const bool& ignoreEndPoints);
std::vector<Segment2Dd> getSegmentIntersection2D(
        const Segment2Dd& seg1, const Segment2Dd& seg2,
        const bool& ignoreEndPoints);

}
}

#endif // CG3_CGAL_INTERSECTIONS_H

#include "cgal_convexhull.h"

#include <CGAL/ch_graham_andrew.h>

#include <CGAL/Simple_cartesian.h>

namespace cg3 {
namespace cgal {

typedef CGAL::Simple_cartesian<double>                          CK;
typedef CK::Point_2                                             CK_Point_2;

std::vector<Point2Dd> getConvexHull2D(
        const std::vector<Point2Dd>& points)
{
    std::vector<CK_Point_2> cgalPoints;

    for (const Point2Dd p : points) {
        CK_Point_2 point(p.x(), p.y());
        cgalPoints.push_back(point);
    }

    //Compute convex hull
    std::vector<CK_Point_2> convexHullPoints;
    CGAL::ch_graham_andrew(cgalPoints.begin(), cgalPoints.end(), std::back_inserter(convexHullPoints));

    std::vector<Point2Dd> result;
    for (const CK_Point_2 p : convexHullPoints) {
        result.push_back(Point2Dd(p.x(), p.y()));
    }

    return result;
}

}
}

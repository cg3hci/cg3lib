/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * @author    Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */

#include "cgal_convexhull2d.h"

#include <CGAL/ch_graham_andrew.h>

#include <CGAL/Simple_cartesian.h>

namespace cg3 {
namespace cgal {


template <class T = double, class InputContainer, class OutputContainer>
void getConvexHull2D(
        const InputContainer& points,
        OutputContainer& convexHull)
{

    typedef CGAL::Simple_cartesian<T>                               CK;
    typedef typename CK::Point_2                                    CK_Point_2;

    std::vector<CK_Point_2> cgalPoints;

    for (const Point2D<T> p : points) {
        CK_Point_2 point(p.x(), p.y());
        cgalPoints.push_back(point);
    }

    //Compute convex hull
    std::vector<CK_Point_2> cgalCHPoints;
    CGAL::ch_graham_andrew(cgalPoints.begin(), cgalPoints.end(), std::back_inserter(cgalCHPoints));

    for (const CK_Point_2 p : cgalCHPoints) {
        convexHull.push_back(Point2D<T>(p.x(), p.y()));
    }
}

}
}

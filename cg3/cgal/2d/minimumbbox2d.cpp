/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */

#include "minimumbbox2d.h"

#include <CGAL/Polygon_2.h>
#include <CGAL/min_quadrilateral_2.h>
#include <CGAL/ch_graham_andrew.h>

#include <CGAL/Simple_cartesian.h>

namespace cg3 {
namespace cgal {

typedef CGAL::Simple_cartesian<double>                          CK;
typedef CK::Point_2                                             CK_Point_2;
typedef CGAL::Polygon_2<CK>                                     CK_Polygon_2;

#ifdef  CG3_DCEL_DEFINED
std::vector<Point2Dd> getMinRectangle2D(const Dcel* dcel) {
    std::vector<Point2Dd> points;

    for (const Dcel::Vertex* v : dcel->vertexIterator())
        points.push_back(Point2Dd(v->getCoordinate().x(),v->getCoordinate().y()));

    return getMinRectangle2D(points);
}
#endif

std::vector<Point2Dd> getMinRectangle2D(
        const std::vector<Point2Dd>& points, bool isConvexHull)
{
    std::vector<CK_Point_2> cgalCHPoints;

    if (isConvexHull) {
        for (const Point2Dd p : points) {
            CK_Point_2 point(p.x(), p.y());
            cgalCHPoints.push_back(point);
        }
    }
    else {
        std::vector<CK_Point_2> cgalPoints;

        for (const Point2Dd p : points) {
            CK_Point_2 point(p.x(), p.y());
            cgalPoints.push_back(point);
        }

        //Compute convex hull
        CGAL::ch_graham_andrew(cgalPoints.begin(), cgalPoints.end(), std::back_inserter(cgalCHPoints));
    }

    //Compute the minimal enclosing rectangle p_m
    CK_Polygon_2 p_m;
    CGAL::min_rectangle_2(
        cgalCHPoints.begin(), cgalCHPoints.end(), std::back_inserter(p_m));

    std::vector<Point2Dd> rectanglePoints;
    for (CK_Polygon_2::Vertex_const_iterator it = p_m.vertices_begin(); it != p_m.vertices_end(); it++) {
        const CK_Point_2 p = *it;
        rectanglePoints.push_back(Point2Dd(p.x(), p.y()));
    }


    return rectanglePoints;
}


}
}

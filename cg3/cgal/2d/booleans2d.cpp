/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "booleans2d.h"

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Boolean_set_operations_2.h>
#include <CGAL/Polygon_2.h>

namespace cg3 {

namespace cgal {

namespace internal {

typedef CGAL::Exact_predicates_exact_constructions_kernel Kernel;
typedef Kernel::Point_2                                   Point_2;
typedef CGAL::Polygon_2<Kernel>                           Polygon_2;
typedef CGAL::Polygon_with_holes_2<Kernel>                Polygon_with_holes_2;
typedef std::list<Polygon_with_holes_2>                   Pwh_list_2;

void getCoordinates(const internal::Point_2& p, double& x, double& y);
}

}

void cgal::internal::getCoordinates(
        const internal::Point_2& p, double& x, double& y) {

    std::stringstream ss1;
    ss1 << std::setprecision(std::numeric_limits<double>::digits10+1);
    ss1 << p.x();
    ss1 >> x;
    std::stringstream ss2;
    ss2 << std::setprecision(std::numeric_limits<double>::digits10+1);
    ss2 << p.y();
    ss2 >> y;
}

std::vector<std::vector<Point2Dd> > cgal::difference(
        const std::vector<Point2Dd>& polygon1, const std::vector<Point2Dd>& polygon2) {

    std::vector<std::vector<Point2Dd> > result;

    internal::Polygon_2 P1;
    for (unsigned int i = 0; i < polygon1.size(); ++i){
        P1.push_back(internal::Point_2(polygon1[i].x(), polygon1[i].y()));
    }
    internal::Polygon_2 P2;
    for (unsigned int i = 0; i < polygon2.size(); ++i){
        P2.push_back(internal::Point_2(polygon2[i].x(), polygon2[i].y()));
    }

    internal::Polygon_with_holes_2 D;
    internal::Pwh_list_2 diffR;
    CGAL::difference(P1, P2, std::back_inserter(diffR));
    result.reserve(diffR.size());
    for (internal::Pwh_list_2::const_iterator it = diffR.begin(); it != diffR.end(); ++it) {

        D = *it;
        assert (! D.is_unbounded());
        assert (D.number_of_holes() == 0);

        std::vector<Point2Dd> polygon;

        CGAL::Polygon_2<internal::Kernel> P = D.outer_boundary();
        polygon.reserve(P.size());
        for ( CGAL::Polygon_2<internal::Kernel>::Vertex_const_iterator it = P.vertices_begin(); it != P.vertices_end(); ++it){
            internal::Point_2 p = *it;
            double x, y;
            internal::getCoordinates(p,x,y);
            Point2Dd point(x, y);
            polygon.push_back(point);
        }
        result.push_back(polygon);
    }
    return result;

}

std::vector<std::vector<Point2Dd> > cgal::intersection(
        const std::vector<Point2Dd>& polygon1, const std::vector<Point2Dd>& polygon2) {

    std::vector<std::vector<Point2Dd> > result;

    internal::Polygon_2 P1;
    for (unsigned int i = 0; i < polygon1.size(); ++i){
        P1.push_back(internal::Point_2(polygon1[i].x(), polygon1[i].y()));
    }
    internal::Polygon_2 P2;
    for (unsigned int i = 0; i < polygon2.size(); ++i){
        P2.push_back(internal::Point_2(polygon2[i].x(), polygon2[i].y()));
    }

    internal::Polygon_with_holes_2 D;
    internal::Pwh_list_2 intR;
    CGAL::intersection(P1, P2, std::back_inserter(intR));
    result.reserve(intR.size());
    for (internal::Pwh_list_2::const_iterator it = intR.begin(); it != intR.end(); ++it) {

        D = *it;
        assert (! D.is_unbounded());
        assert (D.number_of_holes() == 0);

        std::vector<Point2Dd> polygon;

        CGAL::Polygon_2<internal::Kernel> P = D.outer_boundary();
        polygon.reserve(P.size());
        for ( CGAL::Polygon_2<internal::Kernel>::Vertex_const_iterator it = P.vertices_begin(); it != P.vertices_end(); ++it){
            internal::Point_2 p = *it;
            double x, y;
            internal::getCoordinates(p,x,y);
            Point2Dd point(x, y);
            polygon.push_back(point);
        }
        result.push_back(polygon);
    }
    return result;
}


bool cgal::doIntersect(const std::vector<Point2Dd> &polygon1, const std::vector<Point2Dd> &polygon2) {
    internal::Polygon_2 P1;
    for (unsigned int i = 0; i < polygon1.size(); ++i){
        P1.push_back(internal::Point_2(polygon1[i].x(), polygon1[i].y()));
    }
    internal::Polygon_2 P2;
    for (unsigned int i = 0; i < polygon2.size(); ++i){
        P2.push_back(internal::Point_2(polygon2[i].x(), polygon2[i].y()));
    }

    return CGAL::do_intersect(P1, P2);
}

}

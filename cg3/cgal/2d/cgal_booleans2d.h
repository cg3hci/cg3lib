/**
  * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
  * This Source Code Form is subject to the terms of the GNU GPL 3.0
  *
  * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
  */

#ifndef CG3_CGAL_BOOLEANS2D_H
#define CG3_CGAL_BOOLEANS2D_H

#include <cg3/utilities/utils.h>
#include <cg3/geometry/point.h>
#include <cg3/geometry/2d/point2d.h>

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Boolean_set_operations_2.h>
#include <CGAL/Polygon_2.h>

namespace cg3 {

namespace cgal {
    namespace booleans2d {

        typedef CGAL::Exact_predicates_exact_constructions_kernel Kernel;
        typedef Kernel::Point_2                                   Point_2;
        typedef CGAL::Polygon_2<Kernel>                           Polygon_2;
        typedef CGAL::Polygon_with_holes_2<Kernel>                Polygon_with_holes_2;
        typedef std::list<Polygon_with_holes_2>                   Pwh_list_2;

        void getCoordinates(const Point_2&p, double &x, double &y);

        std::vector< std::vector<Point2Dd > > difference(
                const std::vector<Point2Dd > &polygon1,
                const std::vector<Point2Dd > &polygon2);

        std::vector<std::vector<Point2Dd > > intersection(
                const std::vector<Point2Dd >& polygon1,
                const std::vector<Point2Dd >& polygon2);

        bool doIntersect(
                const std::vector<Point2Dd >& polygon1,
                const std::vector<Point2Dd >& polygon2);
    }
}

}

#endif // CG3_CGAL_BOOLEANS2D_H

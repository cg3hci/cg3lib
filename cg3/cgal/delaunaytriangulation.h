/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_CGAL_DELAUNAYTRIANGULATION_H
#define CG3_CGAL_DELAUNAYTRIANGULATION_H

#include <cg3/geometry/point.h>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_3.h>
#include <CGAL/Random.h>

namespace cg3 {
namespace cgal {

class DelaunayTriangulation
{
public:

    DelaunayTriangulation();

    void pushPoint(const cg3::Pointd& p);

private:
    typedef CGAL::Exact_predicates_inexact_constructions_kernel     K;
    typedef CGAL::Delaunay_triangulation_3<K, CGAL::Fast_location>  Delaunay;
    typedef Delaunay::Point                                         CGALPoint;

    Delaunay triangulation;
};

}
}

#endif // CG3_CGAL_DELAUNAYTRIANGULATION_H

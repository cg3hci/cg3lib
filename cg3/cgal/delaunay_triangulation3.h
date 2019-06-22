/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_CGAL_DELAUNAY_TRIANGULATION3_H
#define CG3_CGAL_DELAUNAY_TRIANGULATION3_H

#include <cg3/geometry/point3.h>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_3.h>
#include <CGAL/Random.h>

namespace cg3 {
namespace cgal {

class DelaunayTriangulation3
{
public:

	DelaunayTriangulation3();

    void pushPoint(const cg3::Point3d& p);

private:
    typedef CGAL::Exact_predicates_inexact_constructions_kernel     K;
    typedef CGAL::Delaunay_triangulation_3<K, CGAL::Fast_location>  Delaunay;
    typedef Delaunay::Point                                         CGALPoint;

    Delaunay triangulation;
};

} //namespace cg3::cgal
} //namespace cg3

#ifndef CG3_STATIC
#define CG3_CGAL_DELAUNAY_TRIANGULATION3_CPP "delaunay_triangulation3.cpp"
#include CG3_CGAL_DELAUNAY_TRIANGULATION3_CPP
#undef BOUNDINGBOX2_CPP
#endif

#endif // CG3_CGAL_DELAUNAY_TRIANGULATION3_H

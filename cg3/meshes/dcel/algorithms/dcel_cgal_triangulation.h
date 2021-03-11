/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_DCEL_CGAL_TRIANGULATION_H
#define CG3_DCEL_CGAL_TRIANGULATION_H

#ifdef CG3_CGAL_DEFINED

#include <cg3/geometry/point3.h>

namespace cg3 {
namespace internal {

static bool dummy;
static std::vector< std::vector<Point3d> > dummy_holes;

std::vector<std::array<Point3d, 3> > triangulate3(
        const Vec3d &normal,
        const std::vector<Point3d>& polygon,
        const std::vector<std::vector<Point3d> >& holes = internal::dummy_holes,
        bool& nonRegularPolygon = internal::dummy);

}
}

#ifndef CG3_STATIC
#define CG3_DCEL_CGAL_TRIANGULATION_CPP "dcel_cgal_triangulation.cpp"
#include CG3_DCEL_CGAL_TRIANGULATION_CPP
#undef CG3_DCEL_CGAL_TRIANGULATION_CPP
#endif //CG3_STATIC

#endif // CG3_CGAL_DEFINED

#endif // CG3_DCEL_CGAL_TRIANGULATION_H

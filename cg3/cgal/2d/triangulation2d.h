/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_CGAL_TRIANGULATION2D_H
#define CG3_CGAL_TRIANGULATION2D_H

#include <cg3/geometry/2d/point2d.h>

namespace cg3 {
namespace cgal {
namespace internal {

static std::vector< std::vector<Point2Dd > > dummy_holes2D;

} //namespace cg3::cgal::internal

std::vector<std::array<Point2Dd , 3> > triangulate(
        const std::vector<Point2Dd >& polygon,
        const std::vector<std::vector<Point2Dd > >& holes = internal::dummy_holes2D);

} //namespace cg3::cgal
} //namespace cg3

#endif // CG3_CGAL_TRIANGULATION_H

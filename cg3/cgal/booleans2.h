/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_CGAL_BOOLEANS2_H
#define CG3_CGAL_BOOLEANS2_H

#include <cg3/geometry/point2.h>

namespace cg3 {
namespace cgal {

std::vector< std::vector<Point2d > > difference(
        const std::vector<Point2d > &polygon1,
        const std::vector<Point2d > &polygon2);

std::vector<std::vector<Point2d > > intersection(
        const std::vector<Point2d >& polygon1,
        const std::vector<Point2d >& polygon2);

bool doIntersect(
        const std::vector<Point2d >& polygon1,
        const std::vector<Point2d >& polygon2);

} //namespace cg3::cgal
} //namespace cg3

#ifndef CG3_STATIC
#define CG3_CGAL_BOOLEANS2_CPP "booleans2.cpp"
#include CG3_CGAL_BOOLEANS2_CPP
#undef BOUNDINGBOX2_CPP
#endif

#endif // CG3_CGAL_BOOLEANS2_H

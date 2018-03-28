/*
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

namespace cg3 {
namespace cgal {

std::vector< std::vector<Point2Dd > > difference(
        const std::vector<Point2Dd > &polygon1,
        const std::vector<Point2Dd > &polygon2);

std::vector<std::vector<Point2Dd > > intersection(
        const std::vector<Point2Dd >& polygon1,
        const std::vector<Point2Dd >& polygon2);

bool doIntersect(
        const std::vector<Point2Dd >& polygon1,
        const std::vector<Point2Dd >& polygon2);

} //namespace cg3::cgal
} //namespace cg3

#endif // CG3_CGAL_BOOLEANS2D_H

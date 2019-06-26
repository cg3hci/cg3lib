/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */
#ifndef CG3_CGAL_MINIMUM_BBOX2_H
#define CG3_CGAL_MINIMUM_BBOX2_H

#include <vector>
#include <cg3/geometry/point2.h>

namespace cg3 {
class Dcel;
namespace cgal {

#ifdef  CG3_DCEL_DEFINED
std::vector<Point2d> minRectangle2D(const Dcel &dcel);
#endif

std::vector<Point2d> minRectangle2D(
        const std::vector<Point2d>& pointVec,
        bool isConvexHull = false);

} //namespace cg3::cgal
} //namespace cg3

#ifndef CG3_STATIC
#define CG3_CGAL_MINIMUMBBOX2_CPP "minimum_bbox2.cpp"
#include CG3_CGAL_MINIMUMBBOX2_CPP
#undef CG3_CGAL_MINIMUMBBOX2_CPP
#endif //CG3_STATIC

#endif // CG3_CGAL_MINIMUMBBOX2_H

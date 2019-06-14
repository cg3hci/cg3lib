/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_CGAL_VORONOI2_H
#define CG3_CGAL_VORONOI2_H

#include <cg3/geometry/point2.h>

namespace cg3 {
namespace cgal {

std::vector<std::vector<cg3::Point2d>> voronoiDiagram2(
        const std::vector<cg3::Point2d>& sites);

void voronoiDiagram2(
        const std::vector<Point2d> &sites,
        std::vector<cg3::Point2d>& vl,
        std::vector<std::vector<unsigned int> >&fl);

} //namespace cg3::cgal
} //namespace cg3

#endif // CG3_CGAL_VORONOI2_H

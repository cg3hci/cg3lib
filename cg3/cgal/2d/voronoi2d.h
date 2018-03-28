/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_CGAL_VORONOI2D_H
#define CG3_CGAL_VORONOI2D_H

#include <cg3/geometry/2d/point2d.h>

namespace cg3 {
namespace cgal {

std::vector<std::vector<cg3::Point2Dd>> computeVoronoiDiagram2d(
        const std::vector<cg3::Point2Dd>& sites);

void computeVoronoiDiagram2d(
        const std::vector<Point2Dd> &sites,
        std::vector<cg3::Point2Dd>& vl,
        std::vector<std::vector<unsigned int> >&fl);

} //namespace cg3::cgal
} //namespace cg3

#endif // CG3_CGAL_VORONOI2D_H

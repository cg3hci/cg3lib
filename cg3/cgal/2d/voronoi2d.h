/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_CGAL_VORONOI2D_H
#define CG3_CGAL_VORONOI2D_H

// standard includes
#include <iostream>
#include <fstream>
#include <cassert>
// includes for defining the Voronoi diagram adaptor
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Voronoi_diagram_2.h>
#include <CGAL/Delaunay_triangulation_adaptation_traits_2.h>
#include <CGAL/Delaunay_triangulation_adaptation_policies_2.h>
// typedefs for defining the adaptor

#include <cg3/geometry/2d/point2d.h>

namespace cg3 {

namespace cgal {

std::vector<std::vector<cg3::Point2Dd>> computeVoronoiDiagram(const std::vector<cg3::Point2Dd>& sites);
void computeVoronoiDiagram(const std::vector<Point2Dd> &sites, std::vector<cg3::Point2Dd>& vl, std::vector<std::vector<unsigned int> >&fl);


}

}

#endif // CG3_CGAL_VORONOI2D_H

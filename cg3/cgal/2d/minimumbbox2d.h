/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */

#ifndef CG3_CGAL_MINIMUMBBOX2D_H
#define CG3_CGAL_MINIMUMBBOX2D_H

#include <vector>
#include "cg3/geometry/2d/point2d.h"
#include "cg3/meshes/dcel/dcel.h"

namespace cg3 {
namespace cgal {

#ifdef  CG3_DCEL_DEFINED
std::vector<Point2Dd> getMinRectangle2D(const Dcel* dcel);
#endif

std::vector<Point2Dd> getMinRectangle2D(
        const std::vector<Point2Dd>& pointVec,
        bool isConvexHull = false);

} //namespace cg3::cgal
} //namespace cg3

#endif // CG3_CGAL_MINIMUMBBOX2D_H

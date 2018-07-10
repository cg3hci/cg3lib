/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */

#ifndef CG3_CGAL_MINIMUMBBOX2D_H
#define CG3_CGAL_MINIMUMBBOX2D_H

#include <vector>
#include <cg3/geometry/2d/point2d.h>

namespace cg3 {
class Dcel;
namespace cgal {

#ifdef  CG3_DCEL_DEFINED
std::vector<Point2Dd> minRectangle2D(const Dcel* dcel);
#endif

std::vector<Point2Dd> minRectangle2D(
        const std::vector<Point2Dd>& pointVec,
        bool isConvexHull = false);

#ifdef CG3_OLD_NAMES_COMPATIBILITY
#ifdef  CG3_DCEL_DEFINED
inline std::vector<Point2Dd> getMinRectangle2D(const Dcel* dcel) {return minRectangle2D(dcel);}
#endif

inline std::vector<Point2Dd> getMinRectangle2D(
        const std::vector<Point2Dd>& pointVec,
        bool isConvexHull = false)
{
    return minRectangle2D(pointVec, isConvexHull);
}
#endif

} //namespace cg3::cgal
} //namespace cg3

#endif // CG3_CGAL_MINIMUMBBOX2D_H

#ifndef CG3_GEOMETRYUTILS_H
#define CG3_GEOMETRYUTILS_H

#include "cg3/geometry/2d/point2d.h"
#include "cg3/geometry/segment.h"

namespace cg3 {

    inline double determinant3x3(double (*m)[3]);

    template<typename T>
    inline bool isPointAtRight(const Segment<Point2D<T>>& segment, const Point2D<T>& point);

    inline bool isPointLyingInTriangle(
            const Point2Dd& a,
            const Point2Dd& b,
            const Point2Dd& c,
            const Point2Dd& p,
            bool includeEndpoints);

    inline bool isPointLyingInCircle(
            const Point2Dd& a,
            const Point2Dd& b,
            const Point2Dd& c,
            const Point2Dd& p,
            bool includeEndpoints);

    inline bool isDeulaunayTriangulation(
            const std::vector<Point2Dd>& points,
            const std::vector<std::vector<Point2Dd>>& triangles);
}

#include "geometryutils.ipp"

#endif // CG3_GEOMETRYUTILS_H

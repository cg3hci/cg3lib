#ifndef CG3_UTILS2D_H
#define CG3_UTILS2D_H

#include "cg3/geometry/2d/point2d.h"
#include "cg3/geometry/segment.h"

namespace cg3 {

    template<typename T>
    inline bool isPointAtLeft(const Segment<Point2D<T>>& segment, const Point2D<T>& point);
    template<typename T>
    inline bool isPointAtLeft(const Point2D<T>& s1, const Point2D<T>& s2, const Point2D<T>& point);

    template<typename T>
    inline bool isPointAtRight(const Segment<Point2D<T>>& segment, const Point2D<T>& point);
    template<typename T>
    inline bool isPointAtRight(const Point2D<T>& s1, const Point2D<T>& s2, const Point2D<T>& point);

    template<typename T>
    inline bool areCollinear(const Segment<Point2D<T>>& segment, const Point2D<T>& point);
    template<typename T>
    inline bool areCollinear(const Point2D<T>& s1, const Point2D<T>& s2, const Point2D<T>& point);


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

#include "utils2d.ipp"

#endif // CG3_UTILS2D_H

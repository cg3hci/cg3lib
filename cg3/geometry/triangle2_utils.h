/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */

#ifndef CG3_TRIANGLE2_UTILS_H
#define CG3_TRIANGLE2_UTILS_H

#include "triangle2.h"

namespace cg3 {

/* Triangles */

template<class T>
inline void reorderCounterClockwiseTriangle2(cg3::Triangle<Point2<T>>& triangle);

template<class T>
inline void sortTriangle2Points(cg3::Triangle<Point2<T>>& triangle);

template<class T>
inline void sortTrianglePointsAndReorderCounterClockwise(
        cg3::Triangle<Point2<T>>& triangle);

template<class T>
inline bool isPointLyingInTriangle(
        const Triangle<Point2<T>>& triangle,
        const Point2<T>& p,
        const bool includeEdges = true);

template<class T>
inline bool isPointLyingInTriangle(
        const Point2<T>& a,
        const Point2<T>& b,
        const Point2<T>& c,
        const Point2<T>& p,
        const bool includeEdges = true);

template<class T>
inline bool isDeulaunayTriangulation(
        const std::vector<Point2<T>>& points,
        const std::vector<std::vector<Point2<T>>>& triangles);

template<class T>
bool areTriangleOverlapping(
        const cg3::Triangle<Point2<T>>& t1,
        const cg3::Triangle<Point2<T>>& t2);

} //namespace cg3

#include "triangle2_utils.cpp"

#endif // CG3_TRIANGLE2_UTILS_H

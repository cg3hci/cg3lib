/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */

#ifndef CG3_TRIANGLE2D_UTILS_H
#define CG3_TRIANGLE2D_UTILS_H

#include "triangle2d.h"

namespace cg3 {

/* Triangles */

template<class T>
inline void reorderCounterClockwiseTriangle2D(cg3::Triangle<Point2D<T>>& triangle);

template<class T>
inline void sortTriangle2DPoints(cg3::Triangle<Point2D<T>>& triangle);

template<class T>
inline void sortTrianglePointsAndReorderCounterClockwise(
        cg3::Triangle<Point2D<T>>& triangle);

template<class T>
inline bool isPointLyingInTriangle(
        const Triangle<Point2D<T>>& triangle,
        const Point2D<T>& p,
        const bool includeEdges = true);

template<class T>
inline bool isPointLyingInTriangle(
        const Point2D<T>& a,
        const Point2D<T>& b,
        const Point2D<T>& c,
        const Point2D<T>& p,
        const bool includeEdges = true);

template<class T>
inline bool isDeulaunayTriangulation(
        const std::vector<Point2D<T>>& points,
        const std::vector<std::vector<Point2D<T>>>& triangles);

template<class T>
bool areTriangleOverlapping(
        const cg3::Triangle<Point2D<T>>& t1,
        const cg3::Triangle<Point2D<T>>& t2);

} //namespace cg3

#include "triangle2d_utils.tpp"

#endif // CG3_TRIANGLE2D_UTILS_H

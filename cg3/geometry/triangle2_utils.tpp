/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */

#include "triangle2_utils.h"

#include <cg3/utilities/utils.h>
#include "intersections2.h"

#include <numeric>


namespace cg3 {

/* ----- TRIANGLES 2D UTILITIES ----- */

/**
 * @ingroup cg3core
 * @brief Reorder vertices of a 2D triangle in counter-clockwise order
 *
 * @link https://stackoverflow.com/questions/1165647/how-to-determine-if-a-list-of-polygon-points-are-in-clockwise-order
 *
 * @param[out] triangle Triangle to be reordered counter-clockwise. It must be a 2D triangle.
 */
template<class T>
inline void reorderCounterClockwiseTriangle2D(cg3::Triangle<Point2<T>>& triangle)
{
    const Point2<T>& p1 = triangle.v1();
    Point2<T>& p2 = triangle.v2();
    Point2<T>& p3 = triangle.v3();

    double area =
            (p2.x()-p1.x()) * (p2.y()+p1.y()) +
            (p3.x()-p2.x()) * (p3.y()+p2.y()) +
            (p1.x()-p3.x()) * (p1.y()+p3.y());

    //If it is clockwise
    if (area >= 0) {
        //Swap second and last vertex
        std::swap(triangle.v2(), triangle.v3());
    }
}

/**
 * @ingroup cg3core
 * @brief Sort the points of a triangle. Useful for comparators.
 *
 * @param[out] triangle Triangle with points to be sorted.
 */
template<class T>
inline void sortTriangle2DPoints(cg3::Triangle<Point2<T>>& triangle)
{
    Point2<T>& p1 = triangle.v1();
    Point2<T>& p2 = triangle.v2();
    Point2<T>& p3 = triangle.v3();

    if (p2 < p1) {
        std::swap(p1, p2);
    }
    if (p1 < p3) {
        std::swap(p1, p3);
    }
    if (p2 < p3) {
        std::swap(p2, p3);
    }
}


/**
 * @ingroup cg3core
 * @brief Sort the points of a triangle and reorder them.
 *
 * @param[out] triangle Triangle with points to be sorted and reordered counter-clockwise.
 */
template<class T>
inline void sortTriangle2DPointsAndReorderCounterClockwise(
        cg3::Triangle<Point2<T>>& triangle)
{
    sortTriangle2DPoints(triangle);
    reorderCounterClockwiseTriangle2D(triangle);
}


/**
 * @ingroup cg3core
 * @brief Check if two triangles have an overlap.
 * Intersections of segments with same endpoints are not included.
 *
 * Note also that CGAL intersection checker could report as intersection
 * the segments having a vertex which lie in the other segment line.
 *
 * @param[in] t1 Triangle 1
 * @param[in] t2 Triangle 2
 * @return True if the triangles have an overlap.
 */
template<class T>
bool triangleOverlap(
        const cg3::Triangle<Point2<T>>& t1, const cg3::Triangle<Point2<T>>& t2)
{
    //TODO more efficient with left/right turns

    //Triangle data
    std::vector<cg3::Segment2<T>> sides1 = t1.sides();
    std::vector<cg3::Segment2<T>> sides2 = t2.sides();
    std::vector<cg3::Point2<T>> vertices1 = t1.vertices();
    std::vector<cg3::Point2<T>> vertices2 = t2.vertices();

    //Check edges intersections
    for (cg3::Segment2<T>& s1 : sides1) {
        for (cg3::Segment2<T>& s2 : sides2) {
            if (cg3::checkSegmentIntersection2(s1, s2, true))
                return true;
        }
    }

    //Check if a point of a triangle is inside the other triangle
    for (cg3::Point2<T>& v : vertices1) {
        if (cg3::isPointLyingInTriangle(t2, v, false)) {
            return true;
        }
    }
    for (cg3::Point2<T>& v : vertices2) {
        if (cg3::isPointLyingInTriangle(t1, v, false)) {
            return true;
        }
    }

    return false;
}


/**
 * @ingroup cg3core
 * @brief Check if a point lies in a 2D triangle
 *
 * @link https://stackoverflow.com/questions/13300904/determine-whether-point-lies-inside-triangle
 *
 * @param[in] triangle Triangle
 * @param[in] p Input point
 * @param[in] includeEdges True if we want to consider the edges
 * belonging to the triangle inside region
 * @return True if the point lies inside the triangle
 */
template<class T>
inline bool isPointLyingInTriangle(
        const Triangle<Point2<T>>& triangle,
        const Point2<T>& p,
        const bool includeEdges)
{
    return isPointLyingInTriangle(triangle.v1(), triangle.v2(), triangle.v3(), p, includeEdges);
}


/**
 * @ingroup cg3core
 * @brief Check if a point lies in a 2D triangle (endpoints included)
 *
 * @link https://stackoverflow.com/questions/13300904/determine-whether-point-lies-inside-triangle
 *
 * Points must be in counter-clockwise order.
 *
 * @param[in] a First vertex coordinate of the triangle
 * @param[in] b Second vertex coordinate of the triangle
 * @param[in] c Third vertex coordinate of the triangle
 * @param[in] p Input point
 * @param[in] includeEdges True if we want to consider the edges
 * belonging to the triangle inside region
 * @return True if the point lies inside the triangle
 */
template<class T>
inline bool isPointLyingInTriangle(
        const Point2<T>& a,
        const Point2<T>& b,
        const Point2<T>& c,
        const Point2<T>& p,
        const bool includeEdges)
{
    double det = (b.y() - c.y()) * (a.x() - c.x()) + (c.x() - b.x()) * (a.y() - c.y());

    double alpha = ((b.y() - c.y())*(p.x() - c.x()) + (c.x() - b.x())*(p.y() - c.y())) / det;
    double beta = ((c.y() - a.y())*(p.x() - c.x()) + (a.x() - c.x())*(p.y() - c.y())) / det;
    double gamma = 1.0f - alpha - beta;

    //If edges are included in the inside region
    if (includeEdges) {
        if (alpha >= -std::numeric_limits<double>::epsilon() &&
            beta >= -std::numeric_limits<double>::epsilon() &&
            gamma >= -std::numeric_limits<double>::epsilon())
        {
            return true;
        }
    }

    //If edges are not included in the inside region
    else {
        if (alpha > 0 &&
            beta > 0 &&
            gamma > 0)
        {
            return true;
        }
    }

    return false;
}

/**
 * @ingroup cg3core
 * @brief Check if the triangulation is a Delaunay triangulation (brute force, O(n^2))
 * @param points Vector of points
 * @param triangles Vector of triangles (represented by a vector of three points)
 * @return
 */
template<class T>
inline bool isDeulaunayTriangulation(
        const std::vector<Point2<T>>& points,
        const std::vector<std::vector<Point2<T>>>& trianglePoints)
{
    for (const std::vector<Point2<T>>& triangle : trianglePoints) {
        const Point2<T>& a = triangle.at(0);
        const Point2<T>& b = triangle.at(1);
        const Point2<T>& c = triangle.at(2);

        for (const Point2<T>& p : points) {
            if (p != a && p != b && p != c) {
                if (isPointLyingInCircle(a,b,c,p,false)) {
                    return false;
                }
            }
        }
    }
    return true;
}

} //namespace cg3

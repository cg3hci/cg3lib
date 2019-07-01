/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */

#include "utils2.h"

#include <cg3/utilities/utils.h>

#include <numeric>
#ifdef CG3_WITH_EIGEN
#include <Eigen/Dense>
#endif

namespace cg3 {

/* ----- INTERNAL FUNCTION DECLARATION ----- */

namespace internal {

template<typename T>
inline double positionOfPointWithRespectToSegment(
        const Point2<T>& s1,
        const Point2<T>& s2,
        const Point2<T>& p);

} //namespace cg3::internal


/* ----- POINT/SEGMENT POSITION ----- */

/**
 * @ingroup cg3core
 * @brief Check if a point is at the left of the line passing through the segment
 *
 * @param[in] s1 First point of the segment
 * @param[in] s2 Second point of the segment
 * @param[in] point Input point
 * @return True if the point is at the left of the line passing through
 * the segment, false otherwise
 *
 */
template<typename T>
inline bool isPointAtLeft(
        const Point2<T>& s1,
        const Point2<T>& s2,
        const Point2<T>& p)
{
    double det = internal::positionOfPointWithRespectToSegment(s1, s2, p);
    return det > std::numeric_limits<double>::epsilon();
}

/**
 * @ingroup cg3core
 * @brief Check if a point is at the left of the line passing through the segment
 *
 * @param[in] segment Input segment
 * @param[in] point Input point
 * @return True if the point is at the left of the line passing through
 * the segment, false otherwise
 *
 */
template<typename T>
inline bool isPointAtLeft(
        const Segment<Point2<T>>& segment,
        const Point2<T>& point)
{
    return isPointAtLeft<T>(segment.p1(), segment.p2(), point);
}

/**
 * @ingroup cg3core
 * @brief Check if a point is at the right of the line passing through the segment
 *
 * @param[in] s1 First point of the segment
 * @param[in] s2 Second point of the segment
 * @param[in] point Input point
 * @return True if the point is at the right of the line passing through
 * the segment, false otherwise
 *
 */
template<typename T>
inline bool isPointAtRight(
        const Point2<T>& s1,
        const Point2<T>& s2,
        const Point2<T>& p)
{
    double det = internal::positionOfPointWithRespectToSegment(s1, s2, p);
    return det < -std::numeric_limits<double>::epsilon();
}

/**
 * @ingroup cg3core
 * @brief Check if a point is at the right of the line passing through the segment
 *
 * @param[in] segment Input segment
 * @param[in] point Input point
 * @return True if the point is at the right of the line passing through
 * the segment, false otherwise
 *
 */
template<typename T>
inline bool isPointAtRight(
        const Segment<Point2<T>>& segment,
        const Point2<T>& point)
{
    return isPointAtRight<T>(segment.p1(), segment.p2(), point);
}


/**
 * @ingroup cg3core
 * @brief Check if a point is collinear to the line passing through the segment
 * or if the points are collinear
 *
 * @param[in] s1 First point of the segment
 * @param[in] s2 Second point of the segment
 * @param[in] point Input point
 * @return True if the point is collinear to the line passing through
 * the segment, false otherwise
 *
 */
template<typename T>
inline bool areCollinear(
        const Point2<T>& s1,
        const Point2<T>& s2,
        const Point2<T>& p,
        double epsilon)
{
    double det = internal::positionOfPointWithRespectToSegment(s1, s2, p);
    return cg3::epsilonEqual(det, 0.0, epsilon);
}

/**
 * @ingroup cg3core
 * @brief Check if a point is collinear to the line passing through the segment
 *
 * @param[in] segment Input segment
 * @param[in] point Input point
 * @return True if the point is collinear to the line passing through
 * the segment, false otherwise
 *
 */
template<typename T>
inline bool areCollinear(
        const Segment<Point2<T>>& segment,
        const Point2<T>& point,
        double epsilon)
{
    return areCollinear<T>(segment.p1(), segment.p2(), point, epsilon);
}


/* ----- OTHERS ----- */

#ifdef CG3_WITH_EIGEN
/**
 * @ingroup cg3core
 * @brief Check if a point lies inside a circle passing for three points
 * @param[in] a First coordinate of the circle
 * @param[in] b Third coordinate of the circle
 * @param[in] c Second coordinate of the circle
 * @param[in] p Input point
 * @param[in] includeBorders True if we want to consider the borders
 * belonging to the circle inside region
 * @return True if the point lies inside the circle
 */
template <class T>
inline bool isPointLyingInCircle(
        const Point2<T>& a,
        const Point2<T>& b,
        const Point2<T>& c,
        const Point2<T>& p,
        const bool includeBorders)
{
    Eigen::Matrix4d A;

    A << a.x(), a.y(), a.x()*a.x() + a.y()*a.y(), 1,
            b.x(), b.y(), b.x()*b.x() + b.y()*b.y(), 1,
            c.x(), c.y(), c.x()*c.x() + c.y()*c.y(), 1,
            p.x(), p.y(), p.x()*p.x() + p.y()*p.y(), 1;

    if (includeBorders) {
        return (A.determinant() >= -std::numeric_limits<double>::epsilon());
    }
    else {
        return (A.determinant() > 0);
    }
}
#endif

/**
 * @ingroup cg3core
 * @brief isPolygonCounterClockwise
 * @param polygon: a container of Point2D representing a regular 2D polygon
 * @return true if the points of the polygon are stored in counterclockwise order
 */
template <template < class ... > class Container, class T, class ... Args>
inline bool isPolygonCounterClockwise(const Container<Point2<T>, Args...>& polygon)
{
    double sum = 0;
    for (typename Container<Point2<T>, Args...>::const_iterator it = polygon.begin(); it != polygon.end(); ++it) {
        typename Container<Point2<T>, Args...>::const_iterator next = it;
        next++;
        if (next == polygon.end())
            next = polygon.begin();
        const Point2<T>& p1 = *it;
        const Point2<T>& p2 = *next;
        sum += (p2.x() - p1.x()) * (p2.y()+p1.y());
    }
    if (sum > 0)
        return false;
    else
        return true;
}

/**
 * @ingroup cg3core
 * @brief polygonArea
 * @param polygon: a container of Point2D representing a regular 2D polygon
 * @return the area of the polygon (negative if it is not counterclockwise)
 * @link https://www.mathopenref.com/coordpolygonarea2.html
 */
template <template < class ... > class Container, class T, class ... Args>
inline double polygonArea(const Container<Point2<T>, Args...>& polygon)
{
    double area = 0;
    for (typename Container<Point2<T>, Args...>::const_iterator it = polygon.begin(); it != polygon.end(); ++it) {
        typename Container<Point2<T>, Args...>::const_iterator next = it;
        next++;
        if (next == polygon.end())
            next = polygon.begin();
        const Point2<T>& p1 = *it;
        const Point2<T>& p2 = *next;
        area += (p2.x() - p1.x()) * (p2.y()+p1.y());
    }
    return area / 2;

}

/* ----- INTERNAL FUNCTION DEFINITION ----- */

namespace internal {

/**
 * @ingroup cg3core
 * @brief Check if a point is at the left of the line passing through the segment
 *
 * @param[in] s1 First point of the segment
 * @param[in] s2 Second point of the segment
 * @param[in] point Input point
 * @return 0 if segment lies on the same line of the segment, 1 if points is at the
 * right of the segment, -1 if points
 *
 */
template<typename T>
inline double positionOfPointWithRespectToSegment(
        const Point2<T>& s1,
        const Point2<T>& s2,
        const Point2<T>& p)
{
    return ((s2.x() - s1.x())*(p.y() - s1.y()) - (s2.y() - s1.y())*(p.x() - s1.x()));
}

} //namespace cg3::internal
} //namespace cg3

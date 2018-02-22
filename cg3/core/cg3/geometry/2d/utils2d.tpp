/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */

#include "utils2d.h"

#include "cg3/utilities/utils.h"

#include <numeric>

namespace cg3 {

/* ----- INTERNAL FUNCTION DECLARATION ----- */

namespace internal {

template<typename T>
inline double positionOfPointWithRespectToSegment(const Point2D<T>& s1, const Point2D<T>& s2, const Point2D<T>& p);

}



/* ----- POINT/SEGMENT POSITION ----- */

/**
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
inline bool isPointAtLeft(const Point2D<T>& s1, const Point2D<T>& s2, const Point2D<T>& p) {
    double det = internal::positionOfPointWithRespectToSegment(s1, s2, p);
    return det > std::numeric_limits<double>::epsilon();
}

/**
 * @brief Check if a point is at the left of the line passing through the segment
 *
 * @param[in] segment Input segment
 * @param[in] point Input point
 * @return True if the point is at the left of the line passing through
 * the segment, false otherwise
 *
 */
template<typename T>
inline bool isPointAtLeft(const Segment<Point2D<T>>& segment, const Point2D<T>& point) {
    return isPointAtLeft<T>(segment.getP1(), segment.getP2(), point);
}

/**
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
inline bool isPointAtRight(const Point2D<T>& s1, const Point2D<T>& s2, const Point2D<T>& p) {
    double det = internal::positionOfPointWithRespectToSegment(s1, s2, p);
    return det < -std::numeric_limits<double>::epsilon();
}

/**
 * @brief Check if a point is at the right of the line passing through the segment
 *
 * @param[in] segment Input segment
 * @param[in] point Input point
 * @return True if the point is at the right of the line passing through
 * the segment, false otherwise
 *
 */
template<typename T>
inline bool isPointAtRight(const Segment<Point2D<T>>& segment, const Point2D<T>& point) {
    return isPointAtRight<T>(segment.getP1(), segment.getP2(), point);
}


/**
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
inline bool areCollinear(const Point2D<T>& s1, const Point2D<T>& s2, const Point2D<T>& p) {
    double det = internal::positionOfPointWithRespectToSegment(s1, s2, p);
    return cg3::epsilonEqual(det, 0.0);
}

/**
 * @brief Check if a point is collinear to the line passing through the segment
 *
 * @param[in] segment Input segment
 * @param[in] point Input point
 * @return True if the point is collinear to the line passing through
 * the segment, false otherwise
 *
 */
template<typename T>
inline bool areCollinear(const Segment<Point2D<T>>& segment, const Point2D<T>& point) {
    return areCollinear<T>(segment.getP1(), segment.getP2(), point);
}






/* ----- OTHERS ----- */

/**
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
        const Point2D<T>& a,
        const Point2D<T>& b,
        const Point2D<T>& c,
        const Point2D<T>& p,
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

/**
 * @brief isPolygonCounterClockwise
 * @param polygon: a container of Point2D representing a regular polygon
 * @return true if the points of the polygon are stored in counterclockwise order
 */
template <typename Container>
inline bool isPolygonCounterClockwise(const Container& polygon) {
    double sum = 0;
    for (typename Container::const_iterator it = polygon.begin(); it != polygon.end(); ++it) {
        typename Container::const_iterator next = it;
        next++;
        if (next == polygon.end())
            next = polygon.begin();
        const Point2Dd& p1 = *it;
        const Point2Dd& p2 = *next;
        sum += (p2.x() - p1.x()) * (p2.y()+p1.y());
    }
    if (sum > 0)
        return false;
    else
        return true;
}




/* ----- INTERNAL FUNCTION DEFINITION ----- */

namespace internal {

/**
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
inline double positionOfPointWithRespectToSegment(const Point2D<T>& s1, const Point2D<T>& s2, const Point2D<T>& p) {
    return ((s2.x() - s1.x())*(p.y() - s1.y()) - (s2.y() - s1.y())*(p.x() - s1.x()));
}

}

}

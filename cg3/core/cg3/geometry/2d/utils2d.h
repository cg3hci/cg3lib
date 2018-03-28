/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */

#ifndef CG3_UTILS2D_H
#define CG3_UTILS2D_H

#include "cg3/geometry/2d/point2d.h"
#include "cg3/geometry/2d/segment2d.h"

namespace cg3 {

/* Point/Segment position */
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

/* Others */
template<class T>
inline bool isPointLyingInCircle(
        const Point2D<T>& a,
        const Point2D<T>& b,
        const Point2D<T>& c,
        const Point2D<T>& p,
        const bool includeBorders);

template <typename Container>
inline bool isPolygonCounterClockwise(const Container& polygon);

} //namespace cg3

#include "utils2d.tpp"

#endif // CG3_UTILS2D_H

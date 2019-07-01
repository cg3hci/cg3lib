/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */

#ifndef CG3_UTILS2_H
#define CG3_UTILS2_H

#include "point2.h"
#include "segment2.h"
#include <cg3/utilities/const.h>

namespace cg3 {

/* Point/Segment position */
template<typename T>
inline bool isPointAtLeft(
        const Segment<Point2<T>>& segment,
        const Point2<T>& point);

template<typename T>
inline bool isPointAtLeft(
        const Point2<T>& s1,
        const Point2<T>& s2,
        const Point2<T>& point);

template<typename T>
inline bool isPointAtRight(
        const Segment<Point2<T>>& segment,
        const Point2<T>& point);

template<typename T>
inline bool isPointAtRight(
        const Point2<T>& s1,
        const Point2<T>& s2,
        const Point2<T>& point);

template<typename T>
inline bool areCollinear(
        const Segment<Point2<T>>& segment,
        const Point2<T>& point,
        double epsilon = CG3_EPSILON);

template<typename T>
inline bool areCollinear(
        const Point2<T>& s1,
        const Point2<T>& s2,
        const Point2<T>& point,
        double epsilon = CG3_EPSILON);

/* Others */
#ifdef CG3_WITH_EIGEN
template<class T>
inline bool isPointLyingInCircle(
        const Point2<T>& a,
        const Point2<T>& b,
        const Point2<T>& c,
        const Point2<T>& p,
        const bool includeBorders);
#endif

template <template < class ... > class Container, class T, class ... Args>
inline bool isPolygonCounterClockwise(const Container<Point2<T>, Args...>& polygon);

template <template < class ... > class Container, class T, class ... Args>
inline double polygonArea(const Container<Point2<T>, Args...>& polygon);

} //namespace cg3

#include "utils2.cpp"

#endif // CG3_UTILS2_H

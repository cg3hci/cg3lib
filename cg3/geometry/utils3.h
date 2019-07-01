/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */

#ifndef CG3_UTILS3_H
#define CG3_UTILS3_H

#include <cg3/geometry/point3.h>
#include <cg3/geometry/plane.h>
#include <cg3/utilities/const.h>

namespace cg3 {

template <class Vector>
inline double angle(const Vector& v1, const Vector& v2);

inline double internalAngle(
        const Vec3d& v1,
        const Vec3d& v2,
        const Vec3d& direction);

inline Point3d orthogonalProjectionOnAPlane(
        const Plane& plane,
        const Point3d& point);

inline Point3d orthogonalProjectionOnAPlane(
        const Vec3d& planeNormal,
        const Point3d& planePoint,
        const Point3d& point);

template <typename T>
inline bool areCollinear(
        const cg3::Point3<T>& p1,
        const cg3::Point3<T>& p2,
        const cg3::Point3<T>& p3,
        double epsilon = CG3_EPSILON);

template <template < class ... > class Container, class T, class ... Args>
inline bool isPolygonCounterClockwise(
        const Container<Point3<T>, Args...>& polygon,
        const Vec3d& normal);

} //namespace cg3

#include "utils3.cpp"

#endif // CG3_UTILS3_H

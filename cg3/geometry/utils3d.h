/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */

#ifndef CG3_UTILS3D_H
#define CG3_UTILS3D_H

#include <cg3/geometry/point.h>
#include <cg3/geometry/plane.h>
#include <cg3/utilities/const.h>

namespace cg3 {

template <class Vector>
inline double angle(const Vector& v1, const Vector& v2);

inline double internalAngle(
        const Vec3& v1,
        const Vec3& v2,
        const Vec3& direction);

inline Pointd orthogonalProjectionOnAPlane(
        const Plane& plane,
        const Pointd& point);

inline Pointd orthogonalProjectionOnAPlane(
        const Vec3& planeNormal,
        const Pointd& planePoint,
        const Pointd& point);

template <typename T>
inline bool areCollinear(
        const cg3::Point<T>& p1,
        const cg3::Point<T>& p2,
        const cg3::Point<T>& p3,
        double epsilon = CG3_EPSILON);

template <template < class ... > class Container, class T, class ... Args>
inline bool isPolygonCounterClockwise(
        const Container<Point<T>>& polygon,
        const Vec3& normal);

#ifdef CG3_OLD_NAMES_COMPATIBILITY
template <class Vector>
inline double getAngle(const Vector& v1, const Vector& v2) {return angle(v1, v2);}
inline double getInternalAngle(
        const Vec3& v1,
        const Vec3& v2,
        const Vec3& direction) {return internalAngle(v1, v2, direction);}
#endif

} //namespace cg3

#include "utils3d.tpp"

#endif // CG3_UTILS3D_H

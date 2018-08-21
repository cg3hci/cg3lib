/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */

#include "utils3d.h"

#include <cg3/utilities/utils.h>

namespace cg3 {

/* ----- UTILS IMPLEMENTATION ----- */

/**
 * @ingroup cg3core
 * @brief Calculate angle between 2 vectors
 * @param v1 First vector
 * @param v2 Second vector
 * @return Angle in radians
 */
template <class Vector>
inline double angle(const Vector& v1, const Vector& v2)
{
    double dot = v1.dot(v2);
    return acos(dot);
}

/**
 * @ingroup cg3core
 * @brief Get internal (clockwise) angle between two 3D vector
 * @param v1 First vector
 * @param v2 Second vector
 * @param direction Axis
 * @return Angle in radians
 */
inline double internalAngle(
        const Vec3& v1, const Vec3& v2,
        const Vec3& direction)
{
    if (cg3::epsilonEqual(v1,v2))
        return 0;
    if (cg3::epsilonEqual(v1,-v2))
        return M_PI;

    double ang = cg3::angle(v1,v2);

    Vec3 cross = v1.cross(v2);
    cross.normalize();

    int sign = cross.dot(direction) >= 0 ? 1 : -1;

    return sign*ang;
}


/**
 * @ingroup cg3core
 * @brief Get orthogonal projection of a point in a plane
 * @param plane Projection plane
 * @param point Point to be projected
 * @return Projected point
 */
inline Pointd orthogonalProjectionOnAPlane(
        const Plane& plane,
        const Pointd& point)
{
    //TO BE TESTED

    const Vec3& planeNormal = plane.normal();
    const double d = plane.d();

    cg3::Pointd planePoint = planeNormal*d;

    return orthogonalProjectionOnAPlane(planeNormal, planePoint, point);
}

/**
 * @ingroup cg3core
 * @brief Get orthogonal projection of a point in a plane given a plane point
 * @param planeNormal Projection plane normal
 * @param planePoint Projection plane point
 * @param point Point to be projected
 * @return Projected point
 */
inline Pointd orthogonalProjectionOnAPlane(
        const Vec3& planeNormal,
        const Pointd& planePoint,
        const Pointd& point)
{
    //TO BE TESTED

    double t = - planeNormal.dot(point) + planeNormal.dot(planePoint);

    Pointd projectedPoint = point + (planeNormal * t);

    return projectedPoint;
}

} //namespace cg3

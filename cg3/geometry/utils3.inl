/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */

#include "utils3.h"
#include <cg3/utilities/utils.h>
#include "utils2.h"
#include "transformations3.h"

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
        const Vec3d& v1, const Vec3d& v2,
        const Vec3d& direction)
{
    if (cg3::epsilonEqual(v1,v2))
        return 0;
    if (cg3::epsilonEqual(v1,-v2))
        return M_PI;

    double ang = cg3::angle(v1,v2);

    Vec3d cross = v1.cross(v2);
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
inline Point3d orthogonalProjectionOnAPlane(
        const Plane& plane,
		const Point3d& point)
{
    //TO BE TESTED

    const Vec3d& planeNormal = plane.normal();
    const double d = plane.d();

	cg3::Point3d planePoint = planeNormal*d;

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
inline Point3d orthogonalProjectionOnAPlane(
        const Vec3d& planeNormal,
		const Point3d& planePoint,
		const Point3d& point)
{
    //TO BE TESTED

    double t = - planeNormal.dot(point) + planeNormal.dot(planePoint);

	Point3d projectedPoint = point + (planeNormal * t);

    return projectedPoint;
}

/**
 * @ingroup cg3core
 * @brief Checks if three 3D points are collinear
 * @param p1
 * @param p2
 * @param p3
 * @return
 */
template<typename T>
inline bool areCollinear(
        const cg3::Point3<T>& p1,
        const cg3::Point3<T>& p2,
        const cg3::Point3<T>& p3,
        double epsilon)
{
    return epsilonEqual((p3 - p1).cross(p2 - p1).length(), 0.0, epsilon);
}


/**
 * @ingroup cg3core
 * @brief isPolygonCounterClockwise
 * @param polygon: a container of Pointd representing a regular 3D polygon
 * @param normal: the normal of the 3D polygon
 * @return true if the points of the polygon are stored in counterclockwise order w.r the
 *         given normal
 */
template <template < class ... > class Container, class T, class ... Args>
bool isPolygonCounterClockwise(const Container<Point3<T>, Args...>& polygon, const Vec3d& normal)
{
    Vec3d zAxis(0,0,1);
    Vec3d v = -(normal.cross(zAxis));
    v.normalize();
    double dot = normal.dot(zAxis);
    double angle = acos(dot);

    double r[3][3] = {{0}};
    if (normal != zAxis){
        if (normal == -zAxis){
            v = Vec3d(1,0,0);
        }
        rotationMatrix(v, angle, r);
    }
    else {
        r[0][0] = r[1][1] = r[2][2] = 1;
    }

	std::vector<Point2<T>> points;
    for (const Point3<T>& p : polygon){
		Point3d pr(p.x() * r[0][0] + p.y() * r[1][0] +p.z() * r[2][0], p.x() * r[0][1] + p.y() * r[1][1] +p.z() * r[2][1], p.x() * r[0][2] + p.y() * r[1][2] +p.z() * r[2][2]);
		points.push_back(Point2<T>(pr.x(), pr.y()));
    }
    return isPolygonCounterClockwise(points);
}

} //namespace cg3

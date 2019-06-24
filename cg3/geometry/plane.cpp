/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 * @author Andreas Scalas (andreasscalas@gmail.com)
 */

#include "plane.h"

#include "line3.h"
#include <cg3/utilities/utils.h>
#ifdef CG3_WITH_EIGEN
#include <Eigen/QR>
#endif

namespace cg3 {

CG3_INLINE Plane::Plane(const Vec3d& normal, double d) :
    _normal(normal),
    _d(d)
{
    normalize();
}

CG3_INLINE Plane::Plane(double a, double b, double c, double d) :
    _normal(a, b, c),
    _d(d)
{
    normalize();
}

CG3_INLINE Plane::Plane(const Point3d& p1, const Point3d& p2, const Point3d& p3)
{
    Vec3d v1 (p2 - p1);
    Vec3d v2 (p3 - p1);
    _normal = v1.cross(v2);
    _normal.normalize();
    _d = -(_normal.x() * p1.x() + _normal.y() * p1.y() + _normal.z() * p1.z());
}

CG3_INLINE double Plane::a() const
{
    return _normal.x();
}

CG3_INLINE double Plane::b() const
{
    return _normal.y();
}

CG3_INLINE double Plane::c() const
{
    return _normal.z();
}

CG3_INLINE double Plane::d() const
{
    return _d;
}

CG3_INLINE Vec3d Plane::normal() const
{
    return _normal;
}

CG3_INLINE void Plane::normalize()
{
    double oldLength = _normal.normalize();
    _d /= oldLength;
}

/**
 * @brief Plane::pointLiesOnPlane checks if a point lies on the plane.
 * @param p
 * @return true if the point lies on the plane, false otherwise
 */
CG3_INLINE bool Plane::pointLiesOnPlane(const Point3d &p, double epsilon) const
{
    double sum = _normal.x()*p.x() + _normal.y()*p.y() + _normal.z()*p.z() + _d;
    if(cg3::epsilonEqual(sum, 0.0, epsilon))
        return true;
    else
        return false;

}

#ifdef CG3_WITH_EIGEN
CG3_INLINE bool Plane::intersection(Point3d& inters, const Line3& l) const
{
    Vec3d n(_normal);
    n.normalize();
    Vec3d dir = l.dir();
    dir.normalize();
    if (n.dot(dir) == 0) return false;

    Eigen::Matrix<double, 3, 3> A;
    A(0,0) = _normal.x(); A(0,1) = _normal.y(); A(0,2) = _normal.z();
    A(1,0) = dir.z();    A(1,1) = 0;          A(1,2) = -(dir.x());
    A(2,0) = dir.y();    A(2,1) = -(dir.x()); A(2,2) = 0;

    Eigen::Matrix<double, 3, 1> B;
    B(0) = _d;
    B(1) = (dir.z()*l.startingPoint().x())-(dir.x()*l.startingPoint().z());
    B(2) = (dir.y()*l.startingPoint().x())-(dir.x()*l.startingPoint().y());

    Eigen::Matrix<double, 3, 1> x = A.colPivHouseholderQr().solve(B);

    inters.set(x[0], x[1], x[2]);

    return true;
}
#endif

CG3_INLINE double Plane::pointDistance(const Point3d& p) const
{
    return (_normal.dot(p - (_normal*_d)));
}

CG3_INLINE void Plane::serialize(std::ofstream& binaryFile) const
{
    serializeObjectAttributes("cg3Plane", binaryFile, _normal, _d);
}

CG3_INLINE void Plane::deserialize(std::ifstream& binaryFile)
{
    deserializeObjectAttributes("cg3Plane", binaryFile, _normal, _d);
}

} //namespace cg3

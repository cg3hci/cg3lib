/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "cylinder.h"

#include <cmath>

namespace cg3 {

CG3_INLINE Cylinder::Cylinder() :
    a(), b(), _radius(0)
{
}

CG3_INLINE Cylinder::Cylinder(const Point3d &a, const Point3d &b, double radius) :
    a(a), b(b), _radius(radius)
{
}

CG3_INLINE const Point3d &Cylinder::topCenter() const
{
    return b;
}

CG3_INLINE const Point3d &Cylinder::bottomCenter() const
{
    return a;
}

CG3_INLINE double Cylinder::radius() const
{
    return _radius;
}

CG3_INLINE const Point3d Cylinder::center() const
{
    return (a+b)/2;
}

CG3_INLINE double Cylinder::length() const
{
    return a.dist(b);
}

CG3_INLINE double Cylinder::surfaceArea() const
{
    return 2 * M_PI * _radius * (_radius + length());
}

CG3_INLINE double Cylinder::volume() const
{
    return _radius * _radius * M_PI * length();
}

CG3_INLINE void Cylinder::setTopCenter(const Point3d &tc)
{
    b = tc;
}

CG3_INLINE void Cylinder::setBottomCenter(const Point3d &bc)
{
    a = bc;
}

CG3_INLINE void Cylinder::setRadius(double radius)
{
    _radius = radius;
}

CG3_INLINE void Cylinder::serialize(std::ofstream &binaryFile) const
{
    cg3::serializeObjectAttributes("cg3Cylinder", binaryFile, a, b, _radius);
}

CG3_INLINE void Cylinder::deserialize(std::ifstream &binaryFile)
{
    cg3::deserializeObjectAttributes("cg3Cylinder", binaryFile, a, b, _radius);
}

} //namespace cg3

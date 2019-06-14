/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "cylinder.h"

#include <cmath>

namespace cg3 {

Cylinder::Cylinder() :
    a(), b(), _radius(0)
{
}

Cylinder::Cylinder(const Point3d &a, const Point3d &b, double radius) :
    a(a), b(b), _radius(radius)
{
}

const Point3d &Cylinder::topCenter() const
{
    return b;
}

const Point3d &Cylinder::bottomCenter() const
{
    return a;
}

double Cylinder::radius() const
{
    return _radius;
}

const Point3d Cylinder::center() const
{
    return (a+b)/2;
}

double Cylinder::length() const
{
    return a.dist(b);
}

double Cylinder::surfaceArea() const
{
    return 2 * M_PI * _radius * (_radius + length());
}

double Cylinder::volume() const
{
    return _radius * _radius * M_PI * length();
}

void Cylinder::setTopCenter(const Point3d &tc)
{
    b = tc;
}

void Cylinder::setBottomCenter(const Point3d &bc)
{
    a = bc;
}

void Cylinder::setRadius(double radius)
{
    _radius = radius;
}

void Cylinder::serialize(std::ofstream &binaryFile) const
{
    cg3::serializeObjectAttributes("cg3Cylinder", binaryFile, a, b, _radius);
}

void Cylinder::deserialize(std::ifstream &binaryFile)
{
    cg3::deserializeObjectAttributes("cg3Cylinder", binaryFile, a, b, _radius);
}

} //namespace cg3

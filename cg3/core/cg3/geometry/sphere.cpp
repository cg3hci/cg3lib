/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "sphere.h"
#include <cmath>

namespace cg3 {

/**
 * @brief Default constructor, creates a Sphere with center (0,0,0) and radius 0.
 */
Sphere::Sphere() :
    _center(),
    _radius(0)
{
}

Sphere::Sphere(const Pointd &center, double radius) :
    _center(center),
    _radius(radius)
{
}

const Pointd& Sphere::center() const
{
    return _center;
}

const double& Sphere::radius() const
{
    return _radius;
}

double Sphere::diameter() const
{
    return 2*_radius;
}

double Sphere::circumference() const
{
    return 2 * M_PI * _radius;
}

double Sphere::surfaceArea() const
{
    return 4 * M_PI * _radius * _radius;
}

double Sphere::volume() const
{
    return (4/3) * M_PI * _radius * _radius * _radius;
}

void Sphere::setCenter(const Pointd &center)
{
    _center = center;
}

void Sphere::setRadius(double radius)
{
    _radius = radius;
}

void Sphere::serialize(std::ofstream &binaryFile) const
{
    cg3::serializeObjectAttributes("cg3Sphere", binaryFile, _center, _radius);
}

void Sphere::deserialize(std::ifstream &binaryFile)
{
    cg3::deserializeObjectAttributes("cg3Sphere", binaryFile, _center, _radius);
}

} //namespace cg3

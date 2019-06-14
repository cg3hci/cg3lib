/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_SPHERE_H
#define CG3_SPHERE_H

#include "point3.h"

namespace cg3 {

/**
 * @ingroup cg3core
 * @brief The Sphere class
 *
 * Represents a 3D sphere with a center and a radius,
 * and provides some general formulas of the sphere.
 */
class Sphere : public SerializableObject
{
public:
    Sphere();
    Sphere(const Point3d& _center, double _radius);

    const Point3d& center() const;
    const double &radius() const;
    double diameter() const;
    double circumference() const;
    double surfaceArea() const;
    double volume() const;

    void setCenter(const Point3d& center);
    void setRadius(double radius);

    // SerializableObject interface
    void serialize(std::ofstream &binaryFile) const;
    void deserialize(std::ifstream &binaryFile);

protected:
    Point3d _center;
    double _radius;
};

}

#endif // CG3_SPHERE_H

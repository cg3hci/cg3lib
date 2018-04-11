/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_SPHERE_H
#define CG3_SPHERE_H

#include "point.h"

namespace cg3 {

/**
 * @brief The Sphere class
 *
 * Represents a 3D sphere with a center and a radius,
 * and provides some general formulas of the sphere.
 */
class Sphere : public SerializableObject
{
public:
    Sphere();
    Sphere(const Pointd& _center, double _radius);

    const Pointd& center() const;
    const double &radius() const;
    double diameter() const;
    double circumference() const;
    double surfaceArea() const;
    double volume() const;

    void setCenter(const Pointd& center);
    void setRadius(double radius);

    // SerializableObject interface
    void serialize(std::ofstream &binaryFile) const;
    void deserialize(std::ifstream &binaryFile);

protected:
    Pointd _center;
    double _radius;
};

}

#endif // CG3_SPHERE_H

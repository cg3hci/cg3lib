/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_CYLINDER_H
#define CG3_CYLINDER_H

#include "point3.h"

namespace cg3 {

/**
 * @brief The Cylinder class
 *
 * Represents a 3D cylinder with a bottom center, a top center and the
 * radius of the two circumferences. It provides some general formulas of
 * the cylinder.
 */
class Cylinder : public SerializableObject
{
public:
    Cylinder();
    Cylinder(
        const Point3d& a,
        const Point3d& b,
        double _radius);

    const Point3d& topCenter() const;
    const Point3d& bottomCenter() const;
    double radius() const;

    const Point3d center() const;
    double length() const;
    double surfaceArea() const;
    double volume() const;

    void setTopCenter(const Point3d& tc);
    void setBottomCenter(const Point3d& bc);
    void setRadius(double radius);

    // SerializableObject interface
    void serialize(std::ofstream &binaryFile) const;
    void deserialize(std::ifstream &binaryFile);

protected:
    Point3d a;
    Point3d b;
    double _radius;
};

} //namespace cg3

#ifndef CG3_STATIC
#define CG3_CYLINDER_CPP "cylinder.cpp"
#include CG3_CYLINDER_CPP
#undef CG3_CYLINDER_CPP
#endif

#endif // CG3_CYLINDER_H

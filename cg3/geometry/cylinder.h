/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_CYLINDER_H
#define CG3_CYLINDER_H

#include "point.h"

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
        const Pointd& a,
        const Pointd& b,
        double _radius);

    const Pointd& topCenter() const;
    const Pointd& bottomCenter() const;
    double radius() const;

    const Pointd center() const;
    double length() const;
    double surfaceArea() const;
    double volume() const;

    void setTopCenter(const Pointd& tc);
    void setBottomCenter(const Pointd& bc);
    void setRadius(double radius);

    // SerializableObject interface
    void serialize(std::ofstream &binaryFile) const;
    void deserialize(std::ifstream &binaryFile);

protected:
    Pointd a;
    Pointd b;
    double _radius;
};

} //namespace cg3

#endif // CG3_CYLINDER_H

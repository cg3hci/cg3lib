/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 * @author Andreas Scalas (andreasscalas@gmail.com)
 */

#ifndef CG3_PLANE_H
#define CG3_PLANE_H

#include "point3.h"
#include <cg3/utilities/const.h>

namespace cg3 {

class Line3;

/**
 * @ingroup cg3core
 * @brief The Plane class
 * Stores a plane on the form \f$ax + by + cz + d = 0\f$.
 */
class Plane : public SerializableObject
{
public:
    Plane(const Vec3d& normal, double d);
    Plane(double a, double b, double c, double d);
    Plane(const Point3d &p1, const Point3d &p2, const Point3d &p3);

    double a() const;
    double b() const;
    double c() const;
    double d() const;
    Vec3d normal() const;

    void normalize();

    bool pointLiesOnPlane(const Point3d& p, double epsilon = cg3::CG3_EPSILON) const;
    #ifdef CG3_WITH_EIGEN
    bool intersection(Point3d& inters, const Line3 &l) const;
    #endif
    double pointDistance(const Point3d& p) const;

    // SerializableObject interface
    void serialize(std::ofstream& binaryFile) const;
    void deserialize(std::ifstream& binaryFile);

protected:
    Vec3d _normal;
    double _d;
};

} //namespace cg3

#ifndef CG3_STATIC
#define CG3_PLANE_CPP "plane.cpp"
#include CG3_PLANE_CPP
#undef CG3_PLANE_CPP
#endif

#endif // CG3_PLANE_H

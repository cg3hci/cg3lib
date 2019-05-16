/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 * @author Andreas Scalas (andreasscalas@gmail.com)
 */

#ifndef CG3_PLANE_H
#define CG3_PLANE_H

#include "point.h"
#include <cg3/utilities/const.h>

namespace cg3 {

class Line;

/**
 * @ingroup cg3core
 * @brief The Plane class
 * Stores a plane on the form \f$ax + by + cz + d = 0\f$.
 */
class Plane : public SerializableObject
{
public:
    Plane(const Vec3& normal, double d);
    Plane(double a, double b, double c, double d);
    Plane(const Pointd &p1, const Pointd &p2, const Pointd &p3);

    double a() const;
    double b() const;
    double c() const;
    double d() const;
    Vec3 normal() const;

    void normalize();

    bool pointLiesOnPlane(const Pointd& p, double epsilon = cg3::CG3_EPSILON) const;
    #ifdef CG3_WITH_EIGEN
    bool intersection(Pointd& inters, const Line &l) const;
    #endif
    double pointDistance(const Pointd& p) const;

    // SerializableObject interface
    void serialize(std::ofstream& binaryFile) const;
    void deserialize(std::ifstream& binaryFile);

    #ifdef CG3_OLD_NAMES_COMPATIBILITY
    inline double getA() const {return a();}
    inline double getB() const {return b();}
    inline double getC() const {return c();}
    inline double getD() const {return d();}
    inline Vec3 getNormal() const {return normal();}
    #ifdef CG3_WITH_EIGEN
    inline bool getIntersection(Pointd& i, const Line &l) const {return intersection(i, l);}
    #endif
    #endif

protected:
    Vec3 _normal;
    double _d;
};

} //namespace cg3

#endif // CG3_PLANE_H

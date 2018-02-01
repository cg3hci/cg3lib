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
#include "line.h"
#include <cg3/utilities/const.h>

namespace cg3 {

/**
 * @brief The Plane class
 * Stores a plane on the form \f$ax + by + cz + d = 0\f$.
 */
class Plane : SerializableObject {
    public:
        Plane(const Vec3& normal, double d);
        Plane(double a, double b, double c, double d);
        Plane(const Pointd &p1, const Pointd &p2, const Pointd &p3);

        double getA() const;
        double getB() const;
        double getC() const;
        double getD() const;
        Vec3 getNormal() const;

        void normalize();

        bool pointLiesOnPlane(const Pointd& p, double epsilon = CG3_EPSILON) const;
        #ifdef CG3_WITH_EIGEN
        bool getIntersection(Pointd&intersection, const Line &l) const;
        #endif
        double pointDistance(const Pointd& p) const;

        // SerializableObject interface
        void serialize(std::ofstream& binaryFile) const;
        void deserialize(std::ifstream& binaryFile);

    protected:
        Vec3 normal;
        double d;
};

}

#endif // CG3_PLANE_H

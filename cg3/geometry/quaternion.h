/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_QUATERNION_H
#define CG3_QUATERNION_H

#include "point3.h"

namespace cg3 {

class Quaternion
{
public:
    Quaternion();
    Quaternion(const Vec3d& axis, double angle);
    Quaternion(const Vec3d& fromVector, const Vec3d& toVector);
    Quaternion(double q1, double q2, double q3, double q4);

    Vec3d axis() const;
    double angle() const;
    Quaternion inverse() const;
    void matrix4x4(double m[4][4]) const;
    const double* matrix4x4() const;
    void rotationMatrix(double m[3][3]) const;
    #ifdef CG3_WITH_EIGEN
    Eigen::Matrix3d rotationMatrix() const;
    #endif

    void setAxisAngle(const Vec3d& axis, double angle);
    void setValue(double q1, double q2, double q3, double q4);
    void invert();
    void negate();
    double normalize();

    static Quaternion identity();

private:
    std::array<double, 4> q;
};

} //namespace cg3

#ifndef CG3_STATIC
#define CG3_QUATERNION_CPP "quaternion.cpp"
#include CG3_QUATERNION_CPP
#undef CG3_QUATERNION_CPP
#endif

#endif // CG3_QUATERNION_H

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
    Quaternion(const Vec3& axis, double angle);
    Quaternion(const Vec3& fromVector, const Vec3& toVector);
    Quaternion(double q1, double q2, double q3, double q4);

    Vec3 axis() const;
    double angle() const;
    Quaternion inverse() const;
    void matrix4x4(double m[4][4]) const;
    const double* matrix4x4() const;
    void rotationMatrix(double m[3][3]) const;
    #ifdef CG3_WITH_EIGEN
    Eigen::Matrix3d rotationMatrix() const;
    #endif

    void setAxisAngle(const Vec3& axis, double angle);
    void setValue(double q1, double q2, double q3, double q4);
    void invert();
    void negate();
    double normalize();

    static Quaternion identity();

private:
    std::array<double, 4> q;
};

} //namespace cg3

#endif // CG3_QUATERNION_H

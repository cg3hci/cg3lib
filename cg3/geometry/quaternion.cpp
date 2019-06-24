/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "quaternion.h"

#include <cg3/utilities/const.h>

namespace cg3 {

/**
 * @brief Default constructor: identity rotation
 */
CG3_INLINE Quaternion::Quaternion() :
    q{0.0, 0.0, 0.0, 1.0}
{
}

CG3_INLINE Quaternion::Quaternion(const Vec3d& axis, double angle)
{
    setAxisAngle(axis, angle);
}

CG3_INLINE Quaternion::Quaternion(const Vec3d& fromVector, const Vec3d& toVector)
{
    double fromSqNorm = fromVector.lengthSquared();
    double toSqNorm = toVector.lengthSquared();
    // Identity Quaternion
    if ((fromSqNorm < CG3_EPSILON) || (toSqNorm < CG3_EPSILON)) {
        q[0] = q[1] = q[2] = 0.0;
        q[3] = 1.0;
    }
    else {
        Vec3d axis = fromVector.cross(toVector);
        double axisSqNorm = axis.lengthSquared();

        // Aligned vectors
        if (axisSqNorm < CG3_EPSILON)
            axis = fromVector.orthogonalVector();

        double angle = std::asin(std::sqrt(axisSqNorm / (fromSqNorm * toSqNorm)));

        if (fromVector.dot(toVector) < 0.0)
            angle = M_PI - angle;

        setAxisAngle(axis, angle);
    }
}

CG3_INLINE Quaternion::Quaternion(double q1, double q2, double q3, double q4) :
    q{q1, q2, q3, q4}
{
}

CG3_INLINE Vec3d Quaternion::axis() const
{
    Vec3d res = Vec3d(q[0], q[1], q[2]);
    double s = res.length();
    if (s > CG3_EPSILON)
        res /= s;
    return (std::acos(q[3]) <= M_PI / 2.0) ? res : -res;
}

CG3_INLINE double Quaternion::angle() const
{
    double a = 2.0 * std::acos(q[3]);
    return (a <= M_PI) ? a : 2.0 * M_PI - a;
}

CG3_INLINE Quaternion Quaternion::inverse() const
{
    return Quaternion(-q[0], -q[1], -q[2], q[3]);
}

/**
 * @brief Computes a 4x4 OpenGL Matrix for rotations.
 * @param[in] m: a 4x4 matrix of double.
 */
CG3_INLINE void Quaternion::matrix4x4(double m[][4]) const
{
    double q00 = 2.0 * q[0] * q[0];
    double q11 = 2.0 * q[1] * q[1];
    double q22 = 2.0 * q[2] * q[2];

    double q01 = 2.0 * q[0] * q[1];
    double q02 = 2.0 * q[0] * q[2];
    double q03 = 2.0 * q[0] * q[3];

    double q12 = 2.0 * q[1] * q[2];
    double q13 = 2.0 * q[1] * q[3];

    double q23 = 2.0 * q[2] * q[3];

    m[0][0] = 1.0 - q11 - q22;
    m[1][0] = q01 - q23;
    m[2][0] = q02 + q13;

    m[0][1] = q01 + q23;
    m[1][1] = 1.0 - q22 - q00;
    m[2][1] = q12 - q03;

    m[0][2] = q02 - q13;
    m[1][2] = q12 + q03;
    m[2][2] = 1.0 - q11 - q00;

    m[0][3] = 0.0;
    m[1][3] = 0.0;
    m[2][3] = 0.0;

    m[3][0] = 0.0;
    m[3][1] = 0.0;
    m[3][2] = 0.0;
    m[3][3] = 1.0;
}

CG3_INLINE const double* Quaternion::matrix4x4() const
{
    static double m[4][4];
    matrix4x4(m);
    return (const double *)(m);
}

CG3_INLINE void Quaternion::rotationMatrix(double m[][3]) const
{
    double mat[4][4];
    matrix4x4(mat);
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            m[i][j] = mat[j][i];
}

#ifdef CG3_WITH_EIGEN
CG3_INLINE Eigen::Matrix3d Quaternion::rotationMatrix() const
{
    Eigen::Matrix3d m;
    double mat[4][4];
    matrix4x4(mat);
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            m(i,j) = mat[j][i];
    return m;
}
#endif

CG3_INLINE void Quaternion::setAxisAngle(const Vec3d& axis, double angle)
{
    double norm = axis.length();
    if (norm < CG3_EPSILON) {
        *this = Quaternion::identity();
    }
    else {
        double sha = std::sin(angle / 2.0);
        q[0] = sha * axis.x() / norm;
        q[1] = sha * axis.y() / norm;
        q[2] = sha * axis.z() / norm;
        q[3] = std::cos(angle / 2.0);
    }
}

CG3_INLINE void Quaternion::setValue(double q1, double q2, double q3, double q4)
{
    q[0] = q1;
    q[1] = q2;
    q[2] = q3;
    q[3] = q4;
}

CG3_INLINE void Quaternion::invert()
{
    q[0] = -q[0];
    q[1] = -q[1];
    q[2] = -q[2];
}

CG3_INLINE void Quaternion::negate()
{
    invert();
    q[3] = -q[3];
}

CG3_INLINE double Quaternion::normalize()
{
    double norm = std::sqrt(q[0]*q[0] + q[1]*q[1] + q[2]*q[2] + q[3]*q[3]);
    for (unsigned int i = 0; i < 4; i++)
        q[i] /= norm;
    return norm;
}

CG3_INLINE Quaternion Quaternion::identity()
{
    return Quaternion();
}

} //namespace cg3

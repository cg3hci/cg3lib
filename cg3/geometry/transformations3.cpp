/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "transformations3.h"

namespace cg3 {

#ifdef CG3_WITH_EIGEN
/**
 * @ingroup cg3core
 * @brief this function computes a rotation matrix given the axis of the rotation and the angle
 * @param[in] axis
 * @param[in] angle
 * @param[out] m
 */
CG3_INLINE void rotationMatrix(Vec3d axis, double angle, Eigen::Matrix3d &m)
{
    axis.normalize();
    double cosa = cos(angle);
    double sina = sin(angle);
    m(0,0) = cosa + (axis.x() * axis.x())*(1-cosa);
    m(0,1) = axis.x() * axis.y() * (1-cosa) - axis.z() * sina;
    m(0,2) = axis.x() * axis.z() * (1-cosa) + axis.y() * sina;
    m(1,0) = axis.y() * axis.x() * (1-cosa) + axis.z() * sina;
    m(1,1) = cosa + (axis.y() * axis.y())*(1-cosa);
    m(1,2) = axis.y() * axis.z() * (1-cosa) - axis.x() * sina;
    m(2,0) = axis.z() * axis.x() * (1-cosa) - axis.y() * sina;
    m(2,1) = axis.z() * axis.y() * (1-cosa) + axis.x() * sina;
    m(2,2) = cosa + (axis.z() * axis.z())*(1-cosa);
}

/**
 * @ingroup cg3core
 * @brief this function computes a rotation matrix given the axis of the rotation and the angle
 * @param[in] axis
 * @param[out] angle
 * @return the rotation matrix
 */
CG3_INLINE Eigen::Matrix3d rotationMatrix(Vec3d axis, double angle)
{
    Eigen::Matrix3d m;
    axis.normalize();
    double cosa = cos(angle);
    double sina = sin(angle);
    m(0,0) = cosa + (axis.x() * axis.x())*(1-cosa);
    m(0,1) = axis.x() * axis.y() * (1-cosa) - axis.z() * sina;
    m(0,2) = axis.x() * axis.z() * (1-cosa) + axis.y() * sina;
    m(1,0) = axis.y() * axis.x() * (1-cosa) + axis.z() * sina;
    m(1,1) = cosa + (axis.y() * axis.y())*(1-cosa);
    m(1,2) = axis.y() * axis.z() * (1-cosa) - axis.x() * sina;
    m(2,0) = axis.z() * axis.x() * (1-cosa) - axis.y() * sina;
    m(2,1) = axis.z() * axis.y() * (1-cosa) + axis.x() * sina;
    m(2,2) = cosa + (axis.z() * axis.z())*(1-cosa);
    return m;
}
#endif

/**
 * @ingroup cg3core
 * @brief this function computes a rotation matrix given the axis of the rotation and the angle
 * @param[in] axis
 * @param[in] angle
 * @param[out] m
 */
CG3_INLINE void rotationMatrix(Vec3d axis, double angle, double m[][3])
{
    axis.normalize();
    double cosa = cos(angle);
    double sina = sin(angle);
    m[0][0] = cosa + (axis.x() * axis.x())*(1-cosa);
    m[0][1] = axis.x() * axis.y() * (1-cosa) - axis.z() * sina;
    m[0][2] = axis.x() * axis.z() * (1-cosa) + axis.y() * sina;
    m[1][0] = axis.y() * axis.x() * (1-cosa) + axis.z() * sina;
    m[1][1] = cosa + (axis.y() * axis.y())*(1-cosa);
    m[1][2] = axis.y() * axis.z() * (1-cosa) - axis.x() * sina;
    m[2][0] = axis.z() * axis.x() * (1-cosa) - axis.y() * sina;
    m[2][1] = axis.z() * axis.y() * (1-cosa) + axis.x() * sina;
    m[2][2] = cosa + (axis.z() * axis.z())*(1-cosa);
}

} //namespace cg3

/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_TRANSFORMATIONS_H
#define CG3_TRANSFORMATIONS_H

#include "point.h"

namespace cg3 {

#ifdef CG3_WITH_EIGEN
void rotationMatrix(Vec3 axis, double angle, Eigen::Matrix3d &m);

Eigen::Matrix3d rotationMatrix(Vec3 axis, double angle);
#endif

void rotationMatrix(Vec3 axis, double angle, double m[][3]);

#ifdef CG3_OLD_NAMES_COMPATIBILITY
#ifdef CG3_WITH_EIGEN
inline void getRotationMatrix(Vec3 axis, double angle, Eigen::Matrix3d &m)
{
    rotationMatrix(axis, angle, m);
}
inline Eigen::Matrix3d getRotationMatrix(Vec3 axis, double angle)
{
    return rotationMatrix(axis, angle);
}
#endif
inline void getRotationMatrix(Vec3 axis, double angle, double m[][3])
{
    return rotationMatrix(axis, angle, m);
}
#endif

}

#endif // CG3_TRANSFORMATIONS_H

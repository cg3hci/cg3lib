/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_TRANSFORMATIONS_H
#define CG3_TRANSFORMATIONS_H

#include "point.h"

#ifdef CG3_WITH_EIGEN
#include <Eigen/Core>
#endif

namespace cg3 {

#ifdef CG3_WITH_EIGEN
void getRotationMatrix(Vec3 axis, double angle, Eigen::Matrix3d &m);

Eigen::Matrix3d getRotationMatrix(Vec3 axis, double angle);
#endif

void getRotationMatrix(Vec3 axis, double angle, double m[][3]);

}

#endif // CG3_TRANSFORMATIONS_H

/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_TRANSFORMATIONS3_H
#define CG3_TRANSFORMATIONS3_H

#include "point3.h"

namespace cg3 {

#ifdef CG3_WITH_EIGEN
void rotationMatrix(Vec3d axis, double angle, Eigen::Matrix3d &m);

Eigen::Matrix3d rotationMatrix(Vec3d axis, double angle);
#endif

void rotationMatrix(Vec3d axis, double angle, double m[][3]);

}

#ifndef CG3_STATIC
#define CG3_TRANSFORMATIONS3_CPP "transformations3.cpp"
#include CG3_TRANSFORMATIONS3_CPP
#undef CG3_TRANSFORMATIONS3_CPP
#endif

#endif // CG3_TRANSFORMATIONS3_H

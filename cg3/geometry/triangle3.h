/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_TRIANGLE3_H
#define CG3_TRIANGLE3_H

#include "triangle.h"
#include "point3.h"

namespace cg3 {

template <class T>
using Triangle3 = Triangle<Point3<T>>;

typedef Triangle3<double> Triangle3d;
typedef Triangle3<float> Triangle3f;
typedef Triangle3<int> Triangle3i;

}

#endif // CG3_TRIANGLE3_H

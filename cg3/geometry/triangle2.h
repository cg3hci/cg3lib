/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_TRIANGLE2_H
#define CG3_TRIANGLE2_H

#include "triangle.h"
#include "point2.h"

namespace cg3 {

template <class T>
using Triangle2 = Triangle<Point2<T>>;

typedef Triangle2<double> Triangle2d;
typedef Triangle2<float> Triangle2f;
typedef Triangle2<int> Triangle2i;

} //namespace cg3

#endif // CG3_TRIANGLE2_H

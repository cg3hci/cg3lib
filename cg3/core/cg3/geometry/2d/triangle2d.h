/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_TRIANGLE2D_H
#define CG3_TRIANGLE2D_H

#include "../triangle.h"
#include "point2d.h"

namespace cg3 {

template <class T>
using Triangle2D = Triangle<Point2D<T>>;

typedef Triangle2D<double> Triangle2Dd;
typedef Triangle2D<float> Triangle2Df;
typedef Triangle2D<int> Triangle2Di;


}
#endif // CG3_TRIANGLE2D_H

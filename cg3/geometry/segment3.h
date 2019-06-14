/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_SEGMENT3_H
#define CG3_SEGMENT3_H

#include "segment.h"
#include "point3.h"

namespace cg3 {

template <class T>
using Segment3 = Segment<Point3<T>>;

typedef Segment3<double> Segment3d;
typedef Segment3<float> Segment3f;
typedef Segment3<int> Segment3i;

}

#endif // CG3_SEGMENT3_H

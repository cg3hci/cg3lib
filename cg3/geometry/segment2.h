/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */
#ifndef CG3_SEGMENT2_H
#define CG3_SEGMENT2_H

#include "segment.h"
#include "point2.h"

namespace cg3 {

template <class T>
using Segment2 = Segment<Point2<T>>;

typedef Segment2<double> Segment2d;
typedef Segment2<float> Segment2f;
typedef Segment2<int> Segment2i;

} //namespace cg3

#endif // CG3_SEGMENT2_H

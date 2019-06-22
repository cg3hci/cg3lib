/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */

#ifndef CG3_CGAL_CONVEX_HULL2_H
#define CG3_CGAL_CONVEX_HULL2_H

#include <vector>
#include <cg3/geometry/point2.h>

namespace cg3 {
namespace cgal {

template <class T = double, class InputContainer, class OutputContainer>
void convexHull2D(
        const InputContainer& points,
        OutputContainer& outputContainer);

template <class T = double, class InputIterator, class OutputIterator>
void convexHull2D(
        InputIterator first,
        InputIterator end,
        OutputIterator outIt);

} //namespace cg3::cgal
} //namespace cg3

#include "convex_hull2.cpp"

#endif // CG3_CGAL_CONVEX_HULL2D_H

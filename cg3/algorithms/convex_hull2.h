/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */
#ifndef CG3_CONVEXHULL2D_H
#define CG3_CONVEXHULL2D_H

namespace cg3 {

/* Graham scan */

template <class T = double, class InputContainer, class OutputContainer>
void convexHull2D(const InputContainer& container, OutputContainer& convexHull);

template <class T = double, class InputIterator, class OutputIterator>
OutputIterator convexHull2D(const InputIterator first, const InputIterator end, OutputIterator outIt);

} //namespace cg3

#include "convex_hull2.cpp"


#endif // CG3_CONVEXHULL2D_H

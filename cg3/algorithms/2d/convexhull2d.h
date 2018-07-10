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

#ifdef CG3_OLD_NAMES_COMPATIBILITY
template <class T = double, class InputContainer, class OutputContainer>
inline void getConvexHull2D(const InputContainer& container, OutputContainer& convexHull)
{
    return convexHull2D(container, convexHull);
}

template <class T = double, class InputIterator, class OutputIterator>
inline OutputIterator getConvexHull2D(const InputIterator first, const InputIterator end, OutputIterator outIt)
{
    return convexHull2D(first, end, outIt);
}
#endif

} //namespace cg3

#include "convexhull2d.tpp"


#endif // CG3_CONVEXHULL2D_H

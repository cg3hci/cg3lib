/**
  * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
  * This Source Code Form is subject to the terms of the GNU GPL 3.0
  *
  * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
  */

#ifndef CG3_CGAL_CONVEXHULL2D_H
#define CG3_CGAL_CONVEXHULL2D_H


#include <vector>

#include "cg3/geometry/2d/point2d.h"

#include "cg3/meshes/dcel/dcel.h"



namespace cg3 {
namespace cgal {

template <class T = double, class InputContainer, class OutputContainer>
void getCGALConvexHull2D(
        const InputContainer& points,
        OutputContainer& outputContainer);

template <class T = double, class InputIterator, class OutputIterator>
void getCGALConvexHull2D(
        InputIterator first,
        InputIterator end,
        OutputIterator outIt);

}
}


#include "cgal_convexhull2d.tpp"

#endif // CG3_CGAL_CONVEXHULL2D_H

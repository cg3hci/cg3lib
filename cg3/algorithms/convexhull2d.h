#ifndef CG3_CONVEXHULL2D_H
#define CG3_CONVEXHULL2D_H

#include <vector>
#include <set>

#include "cg3/geometry/2d/point2d.h"

namespace cg3 {


template <class Container, class T>
void convexHull2D(const Container& container, std::list<Point2D<T>>& convexHull);


}

#include "convexhull2d.tpp"


#endif // CG3_CONVEXHULL2D_H

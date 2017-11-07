#ifndef CG3_CGAL_CONVEXHULL_H
#define CG3_CGAL_CONVEXHULL_H


#include <vector>

#include "cg3/geometry/2d/point2d.h"

#include "cg3/meshes/dcel/dcel.h"



namespace cg3 {
namespace cgal {

template <class T = double, class InputContainer, class OutputContainer>
void getConvexHull2D(
        const InputContainer& points,
        OutputContainer& convexHull);

}
}


#include "cgal_convexhull.tpp"

#endif // CG3_CGAL_CONVEXHULL_H

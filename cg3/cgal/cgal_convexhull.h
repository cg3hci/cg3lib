#ifndef CG3_CGAL_CONVEXHULL_H
#define CG3_CGAL_CONVEXHULL_H


#include <vector>

#include "cg3/geometry/2d/point2d.h"

#include "cg3/meshes/dcel/dcel.h"



namespace cg3 {
namespace cgal {

std::vector<Point2Dd> getConvexHull2D(
        const std::vector<Point2Dd>& pointVec);

}
}


#endif // CG3_CGAL_CONVEXHULL_H

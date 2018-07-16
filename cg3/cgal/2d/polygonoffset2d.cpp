#include "polygonoffset2d.h"

#include <vector>

#include <boost/shared_ptr.hpp>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/create_offset_polygons_2.h>

namespace cg3 {
namespace cgal {

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point_2;
typedef CGAL::Polygon_2<K> Polygon_2;
typedef CGAL::Straight_skeleton_2<K> Ss;
typedef boost::shared_ptr<Polygon_2> PolygonPtr;
typedef boost::shared_ptr<Ss> SsPtr;
typedef std::vector<PolygonPtr> PolygonPtrVector;
typedef Polygon_2::Vertex_iterator VertexIterator;

/**
 * @brief Given a polygon, return the offset 2D polygon.
 * @param polygon Input polygon
 * @param offset Offset value
 * @return Offset 2D polygon
 */
cg3::Polygon2D offsetPolygon(const cg3::Polygon2D& polygon, double offset) {
    Polygon_2 cgalPolygon;
    for (const cg3::Point2Dd& p : polygon) {
        cgalPolygon.push_back(Point_2(p.x(), p.y()));
    }

    SsPtr straightSkeleton = CGAL::create_interior_straight_skeleton_2(cgalPolygon);
    PolygonPtrVector offset_polygons = CGAL::create_offset_polygons_2<Polygon_2>(offset, *straightSkeleton);

    assert(offset_polygons.size() == 1);

    cg3::Polygon2D result;
    const Polygon_2& offsetPolygon = *(offset_polygons[0]);
    for (VertexIterator vi = offsetPolygon.vertices_begin(); vi != offsetPolygon.vertices_end(); ++vi) {
        result.pushBack(cg3::Point2Dd(vi->x(), vi->y()));
    }

    return result;
}

} //namespace cgal
} //namespace cg3

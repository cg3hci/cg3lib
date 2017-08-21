#ifndef CG3_SLICER_H
#define CG3_SLICER_H

#include <cg3/utilities/utils.h>
#include <cg3/geometry/point.h>
#include <cg3/geometry/2d/point2d.h>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

#include <CGAL/Surface_mesh.h>
#include <CGAL/boost/graph/graph_traits_Surface_mesh.h>
#include <CGAL/AABB_halfedge_graph_segment_primitive.h>
#include <CGAL/AABB_tree.h>
#include <CGAL/AABB_traits.h>
#include <CGAL/Polygon_mesh_slicer.h>

namespace cg3 {

namespace CGALInterface {
    namespace Slicer {
        typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
        typedef CGAL::Surface_mesh<K::Point_3> Mesh;
        typedef std::vector<K::Point_3> Polyline_type;
        typedef std::list< Polyline_type > Polylines;
        typedef CGAL::AABB_halfedge_graph_segment_primitive<Mesh> HGSP;
        typedef CGAL::AABB_traits<K, HGSP>    AABB_traits;
        typedef CGAL::AABB_tree<AABB_traits>  AABB_tree;

        std::vector<std::vector<Pointd> > getPolylines(const std::string& inputOffFile, const Vec3& norm, double d);
        std::vector<std::vector<Pointd> > getPolylines2(const Mesh& mesh, const Vec3& norm, double d);
    }
}

}


#endif // CG3_SLICER_H

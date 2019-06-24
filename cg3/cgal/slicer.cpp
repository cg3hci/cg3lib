/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "slicer.h"

#include <cg3/geometry/plane.h>
#include <cg3/utilities/utils.h>

#include <CGAL/boost/graph/graph_traits_Surface_mesh.h>
#include <CGAL/AABB_halfedge_graph_segment_primitive.h>
#include <CGAL/AABB_tree.h>
#include <CGAL/AABB_traits.h>
#include <CGAL/Polygon_mesh_slicer.h>

namespace cg3 {
namespace cgal {
namespace internal {

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Surface_mesh<K::Point_3> Mesh;
typedef std::vector<K::Point_3> Polyline_type;
typedef std::list< Polyline_type > Polylines;
typedef CGAL::AABB_halfedge_graph_segment_primitive<Mesh> HGSP;
typedef CGAL::AABB_traits<K, HGSP>    AABB_traits;
typedef CGAL::AABB_tree<AABB_traits>  AABB_tree;

} //namespace cg3::cgal::internal

/**
 * @ingroup cg3cgal
 * @brief getPolylines
 * @param inputOffFile
 * @param norm
 * @param d
 * @return
 */
CG3_INLINE std::vector<std::vector<Point3d>> polylines(
        const std::string& inputOffFile,
        const Vec3d& norm,
        double d)
{
    std::ifstream input(inputOffFile.c_str());
    SurfaceMesh mesh;
    if (!input || !(input >> mesh) || mesh.is_empty()) {
        std::cerr << "Not a valid off file." << std::endl;
        exit(1);
    }
    return polylines(mesh, norm, d);
}

/**
 * @ingroup cg3cgal
 * @brief getPolylines
 * @param mesh
 * @param norm
 * @param d
 * @return
 */
CG3_INLINE std::vector<std::vector<Point3d>> polylines(
        const SurfaceMesh &mesh,
        const Vec3d& norm,
        double d)
{
    // Slicer constructor from the mesh
    internal::Polylines polylines;
    internal::AABB_tree tree(edges(mesh).first, edges(mesh).second, mesh);
    CGAL::Polygon_mesh_slicer<SurfaceMesh, internal::K> slicer_aabb(mesh, tree);
    slicer_aabb(internal::K::Plane_3(norm.x(), norm.y(), norm.z(), d), std::back_inserter(polylines));
    std::vector< std::vector<Point3d> > result;
    for (std::vector<internal::K::Point_3> singlePolyline : polylines){
        std::vector<Point3d> v;
        for (internal::K::Point_3 point : singlePolyline){
            Point3d pres(point.x(), point.y(), point.z());
            v.push_back(pres);
        }
        result.push_back(v);
    }
    return result;
}

#ifdef CG3_DCEL_DEFINED
/**
 * @ingroup cg3cgal
 * @brief getPolylines
 * @param mesh
 * @param p
 * @return
 */
CG3_INLINE std::vector<std::vector<Point3d> > polylines(
        const Dcel &mesh,
        const Plane &p)
{
    return polylines(mesh, p.normal(), p.d());
}

/**
 * @ingroup cg3cgal
 * @brief getPolylines
 * @param mesh
 * @param norm
 * @param d
 * @return
 */
CG3_INLINE std::vector<std::vector<Point3d> > polylines(
        const Dcel &mesh,
        const Vec3d &norm,
        double d)
{
    SurfaceMesh m = cgal::surfaceMeshFromDcel(mesh);
    return polylines(m, norm, d);
}
#endif

} //namespace cg3::cgal
} //namespace cg3

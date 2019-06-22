/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "hole_filling.h"

#include <fstream>
#include <CGAL/IO/Polyhedron_iostream.h>
#include <CGAL/boost/graph/graph_traits_Polyhedron_3.h>
#include <CGAL/Polygon_mesh_processing/triangulate_hole.h>

#ifdef CGAL_EIGEN3_ENABLED

namespace cg3 {
namespace cgal {
namespace internal {

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef Polyhedron::Halfedge_handle    Halfedge_handle;
typedef Polyhedron::Facet_handle       Facet_handle;
typedef Polyhedron::Vertex_handle      Vertex_handle;

} //namespace cg3::cgal::internal

/**
 * @ingroup cg3cgal
 * @brief cgal::holeFilling::holeFillingFileOff
 * @param input
 * @param output
 */
CG3_INLINE void holeFillingFileOff(const std::string& input, const std::string& output)
{
    std::ifstream sinput(input);
    Polyhedron poly;
    if ( !sinput || !(sinput >> poly) || poly.empty() ) {
        std::cerr << "Not a valid off file." << std::endl;
        assert(0);
    }

    holeFilling(poly);

    std::ofstream out(output);
    out.precision(17);
    out << poly << std::endl;
}

/**
 * @ingroup cg3cgal
 * @brief cgal::holeFilling::holeFilling
 * @param poly
 */
CG3_INLINE void holeFilling(cgal::Polyhedron& poly)
{
    // Incrementally fill the holes
    unsigned int nb_holes = 0;
    for(internal::Halfedge_handle h : halfedges(poly)) {
        if(h->is_border()) {
            std::vector<internal::Facet_handle>  patch_facets;
            std::vector<internal::Vertex_handle> patch_vertices;
            bool success = CGAL::cpp11::get<0>(
                        CGAL::Polygon_mesh_processing::triangulate_refine_and_fair_hole(
                            poly,
                            h,
                            std::back_inserter(patch_facets),
                            std::back_inserter(patch_vertices),
                            CGAL::Polygon_mesh_processing::parameters::vertex_point_map(get(CGAL::vertex_point, poly)).
                            geom_traits(internal::Kernel())) );
            std::cout << " Number of facets in constructed patch: " << patch_facets.size() << std::endl;
            std::cout << " Number of vertices in constructed patch: " << patch_vertices.size() << std::endl;
            std::cout << " Fairing : " << (success ? "succeeded" : "failed") << std::endl;
            ++nb_holes;
        }
    }
    std::cout << std::endl;
    std::cout << nb_holes << " holes have been filled" << std::endl;
}

/**
 * @ingroup cg3cgal
 * @brief cgal::holeFilling::holeFilling
 * @param poly
 */
CG3_INLINE void holeFillingTriangulation(cgal::Polyhedron& poly)
{
    // Incrementally fill the holes
    unsigned int nb_holes = 0;
    for(internal::Halfedge_handle h : halfedges(poly)) {
        if(h->is_border()) {
            std::vector<internal::Facet_handle> patch_facets;

            CGAL::Polygon_mesh_processing::triangulate_hole(
                poly,
                h,
                std::back_inserter(patch_facets),
                CGAL::Polygon_mesh_processing::parameters::vertex_point_map(get(CGAL::vertex_point, poly)).
                geom_traits(internal::Kernel()));

            std::cout << "Number of facets in constructed patch: " << patch_facets.size() << std::endl;

            ++nb_holes;
        }
    }
    std::cout << nb_holes << " holes have been filled" << std::endl;
}

#ifdef CG3_DCEL_DEFINED
/**
 * @ingroup cg3cgal
 * @brief holeFilling
 * @param d
 */
CG3_INLINE void holeFilling(Dcel& d)
{
    Polyhedron p = cgal::polyhedronFromDcel(d);
    holeFilling(p);
    d = cgal::dcelFromPolyhedron(p);
}
#endif //CG3_DCEL_DEFINED

#ifdef CG3_EIGENMESH_DEFINED
CG3_INLINE SimpleEigenMesh holeFilling(const SimpleEigenMesh& d)
{
    Polyhedron p = cgal::polyhedronFromEigenMesh(d);
    holeFilling(p);
    return cgal::eigenMeshFromPolyhedron(p);
}

CG3_INLINE SimpleEigenMesh holeFillingTriangulation(const SimpleEigenMesh& d)
{
    Polyhedron p = cgal::polyhedronFromEigenMesh(d);
    holeFillingTriangulation(p);
    return cgal::eigenMeshFromPolyhedron(p);
}
#endif //CG3_EIGENMESH_DEFINED

} //namespace cg3::cgal
} //namespace cg3

#endif //CGAL_EIGEN3_ENABLED

#include "hole_filling.h"

#ifdef CGAL_EIGEN3_ENABLED
namespace cg3 {

void cgal::holeFilling::holeFillingFileOff(const std::string& input, const std::string& output) {
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

void cgal::holeFilling::holeFilling(cgal::holeFilling::Polyhedron& poly) {
    // Incrementally fill the holes
    unsigned int nb_holes = 0;
    for(Halfedge_handle h : halfedges(poly))
    {
      if(h->is_border())
      {
        std::vector<Facet_handle>  patch_facets;
        std::vector<Vertex_handle> patch_vertices;
        bool success = CGAL::cpp11::get<0>(
          CGAL::Polygon_mesh_processing::triangulate_refine_and_fair_hole(
                    poly,
                    h,
                    std::back_inserter(patch_facets),
                    std::back_inserter(patch_vertices),
       CGAL::Polygon_mesh_processing::parameters::vertex_point_map(get(CGAL::vertex_point, poly)).
                    geom_traits(Kernel())) );
        std::cout << " Number of facets in constructed patch: " << patch_facets.size() << std::endl;
        std::cout << " Number of vertices in constructed patch: " << patch_vertices.size() << std::endl;
        std::cout << " Fairing : " << (success ? "succeeded" : "failed") << std::endl;
        ++nb_holes;
      }
    }
    std::cout << std::endl;
    std::cout << nb_holes << " holes have been filled" << std::endl;
}

#ifdef CG3_DCEL_DEFINED
void cgal::holeFilling::holeFilling(Dcel& d) {
    Polyhedron p = cgal::polyhedron::getPolyhedronFromDcel(d);
    holeFilling(p);
    /** @todo p to d */
}
#endif

}

#endif

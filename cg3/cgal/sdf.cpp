#include "sdf.h"

namespace cg3 {

std::vector<double> cgal::sdf::getSDFMap(const cgal::polyhedron::Polyhedron_3 &mesh) {
    typedef std::map<polyhedron::Polyhedron_3::Facet_const_handle, double> Facet_double_map;
    Facet_double_map internal_map;
    boost::associative_property_map<Facet_double_map> sdf_property_map(internal_map);

    // compute SDF values
    std::pair<double, double> min_max_sdf = CGAL::sdf_values(mesh, sdf_property_map);

    // It is possible to compute the raw SDF values and post-process them using
    // the following lines:
    // const std::size_t number_of_rays = 25;  // cast 25 rays per facet
    // const double cone_angle = 2.0 / 3.0 * CGAL_PI; // set cone opening-angle
    // CGAL::sdf_values(mesh, sdf_property_map, cone_angle, number_of_rays, false);
    // std::pair<double, double> min_max_sdf =
    //  CGAL::sdf_values_postprocessing(mesh, sdf_property_map);

    // print minimum & maximum SDF values
    std::cout << "minimum SDF: " << min_max_sdf.first
              << " maximum SDF: " << min_max_sdf.second << std::endl;


    // save SDF values
    std::vector<double> sdfMap;
    sdfMap.reserve(mesh.size_of_facets());
    for (polyhedron::Polyhedron_3::Facet_const_iterator facet_it = mesh.facets_begin();
         facet_it != mesh.facets_end(); ++facet_it) {

        // get SDF value
        double sdfValue = sdf_property_map[facet_it];

        // save on the result sdf map
        sdfMap.push_back(sdfValue);

    }

    return sdfMap;
}

#ifdef  CG3_DCEL_DEFINED
//USAGE EXAMPLE:
//std::map<const Dcel::Face*, double> sdfMap = CGALInterface::SDF::getSDFMap(drawableDcel);
//for (Dcel::Face* face : drawableDcel->faceIterator()) {
//    face->setColor(Color(255*sdfMap.at(face), 255*sdfMap.at(face), 255*sdfMap.at(face)));
//}

std::map<const Dcel::Face*, double> cgal::sdf::getSDFMap(const Dcel& dcel) {
    std::map<const Dcel::Face*, int> faceMap;
    std::map<const Dcel::Vertex*, int> vertexMap;
    polyhedron::Polyhedron_3 mesh = polyhedron::getPolyhedronFromDcel(dcel, vertexMap, faceMap);

    // compute inverse map
    std::map<int, const Dcel::Face*> invFaceMap;
    for (const Dcel::Face* face : dcel.faceIterator()) {
         invFaceMap.insert(std::make_pair(faceMap.at(face), face));
    }

    std::vector<double> sdf = getSDFMap(mesh);

    // save SDF values
    std::map<const Dcel::Face*, double> sdfMap;

    int fIndex = 0;
    for (polyhedron::Polyhedron_3::Facet_const_iterator facet_it = mesh.facets_begin();
         facet_it != mesh.facets_end(); ++facet_it) {

        // get SDF value
        double sdfValue = sdf[fIndex];

        // save on the result sdf map
        const Dcel::Face* face = invFaceMap.at(fIndex);
        sdfMap.insert(std::make_pair(face, sdfValue));

        fIndex++;
    }

    return sdfMap;
}

#endif

#ifdef  CG3_EIGENMESH_DEFINED
std::vector<double> cgal::sdf::getSDFMap(const SimpleEigenMesh &m) {
    polyhedron::Polyhedron_3 mesh = polyhedron::getPolyhedronFromEigenMesh(m);
    return getSDFMap(mesh);
}
#endif

}

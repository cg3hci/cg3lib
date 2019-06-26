/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */
#include "sdf.h"

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/boost/graph/graph_traits_Polyhedron_3.h>
#include <CGAL/IO/Polyhedron_iostream.h>
#include <CGAL/mesh_segmentation.h>
#include <CGAL/property_map.h>

namespace cg3 {
namespace cgal {

/**
 * @ingroup cg3cgal
 * @brief cgal::sdf::getSDFMap
 * @param mesh
 * @return
 */
CG3_INLINE std::vector<double> SDFMap(const Polyhedron &mesh)
{
    typedef std::map<Polyhedron::Facet_const_handle, double> Facet_double_map;
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
    for (Polyhedron::Facet_const_iterator facet_it = mesh.facets_begin();
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

/**
 * @ingroup cg3cgal
 * @brief cgal::sdf::getSDFMap
 * @param dcel
 * @return
 */
CG3_INLINE std::map<const Dcel::Face*, double> SDFMap(const Dcel& dcel)
{
    std::map<const Dcel::Face*, int> faceMap;
    std::map<const Dcel::Vertex*, int> vertexMap;
    Polyhedron mesh = polyhedronFromDcel(dcel, vertexMap, faceMap);

    // compute inverse map
    std::map<int, const Dcel::Face*> invFaceMap;
    for (const Dcel::Face* face : dcel.faceIterator()) {
         invFaceMap.insert(std::make_pair(faceMap.at(face), face));
    }

    std::vector<double> sdf = SDFMap(mesh);

    // save SDF values
    std::map<const Dcel::Face*, double> sdfMap;

    int fIndex = 0;
    for (Polyhedron::Facet_const_iterator facet_it = mesh.facets_begin();
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
/**
 * @ingroup cg3cgal
 * @brief cgal::sdf::getSDFMap
 * @param m
 * @return
 */
CG3_INLINE std::vector<double> SDFMap(const SimpleEigenMesh &m)
{
    Polyhedron mesh = polyhedronFromEigenMesh(m);
    return SDFMap(mesh);
}
#endif

} //namespace cg3::cgal
} //namespace cg3

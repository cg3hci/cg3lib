/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */
#include "sdf_segmentation.h"

#if BOOST_VERSION > 106501

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/boost/graph/graph_traits_Polyhedron_3.h>
#include <CGAL/IO/Polyhedron_iostream.h>
#include <CGAL/mesh_segmentation.h>
#include <CGAL/property_map.h>
#include <CGAL/extract_mean_curvature_flow_skeleton.h>

namespace cg3 {
namespace cgal {

CG3_INLINE std::vector<int> sdfSegmentation(const Polyhedron &mesh)
{
    typedef std::map<Polyhedron::Facet_const_handle, double> Facet_double_map;
    Facet_double_map internal_sdf_map;
    boost::associative_property_map<Facet_double_map> sdf_property_map(internal_sdf_map);

    // compute SDF values using default parameters for number of rays, and cone angle
    CGAL::sdf_values(mesh, sdf_property_map);

    // create a property-map for segment-ids
    typedef std::map<Polyhedron::Facet_const_handle, std::size_t> Facet_int_map;
    Facet_int_map internal_segment_map;
    boost::associative_property_map<Facet_int_map> segment_property_map(internal_segment_map);

    // segment the mesh using default parameters for number of levels, and smoothing lambda
    // Any other scalar values can be used instead of using SDF values computed using the CGAL function
    CGAL::segmentation_from_sdf_values(mesh, sdf_property_map, segment_property_map);

    //save labels
    std::vector<int> association;
    association.resize(mesh.size_of_facets());
    size_t fIndex = 0;
    for (Polyhedron::Facet_const_iterator facet_it = mesh.facets_begin();
         facet_it != mesh.facets_end(); ++facet_it) {

        // get SDF value
        size_t label = segment_property_map[facet_it];

        association[fIndex] = static_cast<int>(label);

        fIndex++;
    }

    return association;
}

#ifdef  CG3_EIGENMESH_DEFINED

CG3_INLINE std::vector<int> sdfSegmentation(const SimpleEigenMesh &m)
{
    Polyhedron mesh = polyhedronFromEigenMesh(m);
    return sdfSegmentation(mesh);
}
#endif


template<class ValueType>
struct Facet_with_id_pmap
    : public boost::put_get_helper<ValueType&,
             Facet_with_id_pmap<ValueType> >
{

    typedef boost::graph_traits<PolyhedronWithId>::vertex_descriptor     vertex_descriptor;
    typedef boost::graph_traits<PolyhedronWithId>::halfedge_descriptor   halfedge_descriptor;
    typedef boost::graph_traits<PolyhedronWithId>::face_descriptor       face_descriptor;
    typedef CGAL::Mean_curvature_flow_skeletonization<PolyhedronWithId>        Skeletonization;
    typedef Skeletonization::Skeleton                                    Skeleton;
    typedef Skeleton::vertex_descriptor                                  Skeleton_vertex;

    typedef face_descriptor key_type;
    typedef ValueType value_type;
    typedef value_type& reference;
    typedef boost::lvalue_property_map_tag category;
    Facet_with_id_pmap(
      std::vector<ValueType>& internal_vector
    ) : internal_vector(internal_vector) { }
    reference operator[](key_type key) const
    { return internal_vector[key->id()]; }
private:
    std::vector<ValueType>& internal_vector;
};

CG3_INLINE std::vector<int> skeletonSdfSegmentation(PolyhedronWithId& mesh)
{
    typedef boost::graph_traits<PolyhedronWithId>::vertex_descriptor     vertex_descriptor;
    typedef boost::graph_traits<PolyhedronWithId>::halfedge_descriptor   halfedge_descriptor;
    typedef boost::graph_traits<PolyhedronWithId>::face_descriptor       face_descriptor;
    typedef CGAL::Mean_curvature_flow_skeletonization<PolyhedronWithId>        Skeletonization;
    typedef Skeletonization::Skeleton                                    Skeleton;
    typedef Skeleton::vertex_descriptor                                  Skeleton_vertex;

    // extract the skeleton
    Skeleton skeleton;
    CGAL::extract_mean_curvature_flow_skeleton(mesh, skeleton);

    // init the polyhedron simplex indices
    CGAL::set_halfedgeds_items_id(mesh);

    //for each input vertex compute its distance to the skeleton
    std::vector<double> distances(num_vertices(mesh));
    BOOST_FOREACH(Skeleton_vertex v, vertices(skeleton) )
    {
        const PolyhedronWithId::Point& skel_pt = skeleton[v].point;
        BOOST_FOREACH(vertex_descriptor mesh_v, skeleton[v].vertices)
        {
            const PolyhedronWithId::Point& mesh_pt = mesh_v->point();
            distances[mesh_v->id()] = std::sqrt(CGAL::squared_distance(skel_pt, mesh_pt));
        }
    }

    // create a property-map for sdf values
    std::vector<double> sdf_values( num_faces(mesh) );
    Facet_with_id_pmap<double> sdf_property_map(sdf_values);

    // compute sdf values with skeleton
    BOOST_FOREACH(face_descriptor f, faces(mesh))
    {
        double dist = 0;
        BOOST_FOREACH(halfedge_descriptor hd, halfedges_around_face(halfedge(f, mesh), mesh))
                dist+=distances[target(hd, mesh)->id()];
        sdf_property_map[f] = dist / 3.;
    }

    // post-process the sdf values
    CGAL::sdf_values_postprocessing(mesh, sdf_property_map);

    // create a property-map for segment-ids (it is an adaptor for this case)
    std::vector<std::size_t> segment_ids( num_faces(mesh) );
    Facet_with_id_pmap<std::size_t> segment_property_map(segment_ids);

    // segment the mesh using default parameters
    std::size_t number_of_segments = CGAL::segmentation_from_sdf_values(mesh, sdf_property_map, segment_property_map);

    //save labels
    std::vector<int> association;
    association.resize(mesh.size_of_facets());
    size_t fIndex = 0;
    BOOST_FOREACH(face_descriptor f, faces(mesh))
    {
        // get segmentation value
        size_t label = segment_property_map[f];

        association[fIndex] = static_cast<int>(label);

        fIndex++;
    }

    return association;
}

#ifdef  CG3_EIGENMESH_DEFINED

CG3_INLINE std::vector<int> skeletonSdfSegmentation(const SimpleEigenMesh &mesh)
{
    PolyhedronWithId pmesh = polyhedronFromEigenMesh<PolyhedronWithId>(mesh);
    return skeletonSdfSegmentation(pmesh);
}

#endif

} //namespace cg3::cgal
} //namespace cg3

#endif //BOOST_VERSION

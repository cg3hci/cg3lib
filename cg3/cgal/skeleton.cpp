/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */
#include "skeleton.h"

#include <CGAL/boost/graph/split_graph_into_polylines.h>

namespace cg3 {
namespace cgal {

CG3_INLINE CGAL::Mean_curvature_flow_skeletonization<PolyhedronWithId>::Skeleton skeleton(const PolyhedronWithId& mesh)
{
    typedef boost::graph_traits<PolyhedronWithId>::vertex_descriptor    vertex_descriptor;
    typedef CGAL::Mean_curvature_flow_skeletonization<PolyhedronWithId> Skeletonization;
    typedef Skeletonization::Skeleton                                   Skeleton;
    typedef Skeleton::vertex_descriptor                                 Skeleton_vertex;
    typedef Skeleton::edge_descriptor                                   Skeleton_edge;

    Skeleton skeleton;
    Skeletonization skeletonization(mesh);
    skeletonization(skeleton);

//    std::cout << "Number of vertices of the skeleton: " << boost::num_vertices(skeleton) << "\n";
//    std::cout << "Number of edges of the skeleton: " << boost::num_edges(skeleton) << "\n";

    return skeleton;
}

#ifdef  CG3_EIGENMESH_DEFINED
namespace internal {
static std::vector<std::vector<size_t>> dummyBirthVertices;
static std::vector<std::vector<size_t>> dummyPolylines;
}
CG3_INLINE std::vector<cg3::Point3d> skeleton(
        const SimpleEigenMesh &mesh,
        std::vector<std::vector<size_t>>& birthVertices = internal::dummyBirthVertices,
        std::vector<std::vector<size_t>>& polylines = internal::dummyPolylines)
{
    typedef boost::graph_traits<PolyhedronWithId>::vertex_descriptor    vertex_descriptor;
    typedef CGAL::Mean_curvature_flow_skeletonization<PolyhedronWithId> Skeletonization;
    typedef Skeletonization::Skeleton                                   Skeleton;
    typedef Skeleton::vertex_descriptor                                 Skeleton_vertex;
    typedef Skeleton::edge_descriptor                                   Skeleton_edge;
    typedef boost::graph_traits<PolyhedronWithId>::vertex_descriptor     vertex_descriptor;
    typedef boost::graph_traits<PolyhedronWithId>::halfedge_descriptor   halfedge_descriptor;
    typedef boost::graph_traits<PolyhedronWithId>::face_descriptor       face_descriptor;

    PolyhedronWithId pmesh = polyhedronFromEigenMesh<PolyhedronWithId>(mesh);
    std::vector<cg3::Point3d> skeletonPoints;

    CGAL::set_halfedgeds_items_id(pmesh);

    Skeleton cgalSkel = skeleton(pmesh);

    std::map<cg3::Point3d, size_t> vMap;

    BOOST_FOREACH(Skeleton_vertex v, vertices(cgalSkel)) {
        const PolyhedronWithId::Point& point = cgalSkel[v].point;
        cg3::Point3d p(point.x(), point.y(), point.z());

        skeletonPoints.push_back(p);
        vMap.insert(std::make_pair(p, skeletonPoints.size() - 1));
    }

    birthVertices.resize(skeletonPoints.size());
    BOOST_FOREACH(Skeleton_vertex v, vertices(cgalSkel)) {
        const PolyhedronWithId::Point& point = cgalSkel[v].point;
        const size_t& vertexId = vMap.at(cg3::Point3d(point.x(), point.y(), point.z()));
        BOOST_FOREACH(const vertex_descriptor& vd, cgalSkel[v].vertices) {
            const size_t& id = vd->id();
            birthVertices[vertexId].push_back(id);
        }
    }

    struct PolylineVisitor{
        const Skeleton& skeleton;

        std::vector<std::vector<size_t>>& polylines;
        const std::map<cg3::Point3d, size_t>& vMap;
        size_t size;

        PolylineVisitor(
                    const Skeleton& skeleton,
                    std::vector<std::vector<size_t>>& polylines,
                    const std::map<cg3::Point3d, size_t>& vMap)
            : skeleton(skeleton), polylines(polylines), vMap(vMap), size(0)
        {

        }
        void start_new_polyline(){
            polylines.push_back(std::vector<size_t>());
        }
        void add_node(Skeleton_vertex v){
            const PolyhedronWithId::Point& point = skeleton[v].point;
            polylines[size].push_back(vMap.at(cg3::Point3d(point.x(), point.y(), point.z())));
        }
        void end_polyline()
        {
            size++;
        }
    };

    PolylineVisitor visitor(cgalSkel, polylines, vMap);
    CGAL::split_graph_into_polylines(cgalSkel, visitor);

    return skeletonPoints;
}
#endif

} //namespace cg3::cgal
} //namespace cg3

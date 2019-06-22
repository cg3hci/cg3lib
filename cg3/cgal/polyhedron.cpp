/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */

#include "polyhedron.h"

#include <CGAL/Simple_cartesian.h>
#include <CGAL/Polyhedron_incremental_builder_3.h>

#include <vector>
#include <string>
#include <algorithm>

namespace cg3 {
namespace cgal {
namespace internal {

typedef Polyhedron::HalfedgeDS  HalfedgeDS;

} //namespace cg3::cgal::internal

#ifdef  CG3_DCEL_DEFINED
/**
 * @ingroup cg3cgal
 * @brief cgal::polyhedron::getPolyhedronFromDcel
 * @param dcel
 * @param vertexMap
 * @param faceMap
 * @return
 */
CG3_INLINE cgal::Polyhedron polyhedronFromDcel(
        const Dcel& dcel,
        std::map<const Dcel::Vertex*, int>& vertexMap,
        std::map<const Dcel::Face*, int>& faceMap)
{

    class PolyhedronBuilder : public CGAL::Modifier_base<internal::HalfedgeDS>
    {
    public:
        const Dcel* mesh;
        std::map<const Dcel::Vertex*, int>* vertexMap;
        std::map<const Dcel::Face*, int>* faceMap;

        PolyhedronBuilder(const Dcel* dcel,
                              std::map<const Dcel::Vertex*, int>& vertexMap,
                              std::map<const Dcel::Face*, int>& faceMap) :
            mesh(dcel), vertexMap(&vertexMap), faceMap(&faceMap)
        {}

        void operator()( internal::HalfedgeDS& hds)
        {
            vertexMap->clear();
            faceMap->clear();

            // Postcondition: hds is a valid polyhedral surface.
            CGAL::Polyhedron_incremental_builder_3<internal::HalfedgeDS> B( hds, true);
            B.begin_surface(mesh->numberVertices(), mesh->numberFaces(), mesh->numberHalfEdges());

            typedef typename internal::HalfedgeDS::Vertex   PolyhedronVertex;
            typedef typename PolyhedronVertex::Point        PolyhedronPoint;

            int vIndex = 0;
            for (const Dcel::Vertex* v : mesh->vertexIterator()) {
				Point3d coordinate = v->coordinate();

                B.add_vertex(PolyhedronPoint(coordinate.x(), coordinate.y(), coordinate.z()));
                vertexMap->insert(std::make_pair(v,vIndex));
                vIndex++;
            }

            int fIndex = 0;
            for (const Dcel::Face* f : mesh->faceIterator()) {
                B.begin_facet();
                for (const Dcel::Vertex* v : f->incidentVertexIterator()) {
                    B.add_vertex_to_facet(vertexMap->at(v));
                }
                B.end_facet();
                faceMap->insert(std::make_pair(f, fIndex));
                fIndex++;
            }
            B.end_surface();
        }
    };

    Polyhedron mesh;
    PolyhedronBuilder polyhedronDcelBuilder(&dcel, vertexMap, faceMap);
    mesh.delegate(polyhedronDcelBuilder);

    return mesh;
}

/**
 * @ingroup cg3cgal
 * @brief cgal::polyhedron::getDcelFromPolyhedron
 * @param poly
 * @return
 */
CG3_INLINE Dcel dcelFromPolyhedron(const cgal::Polyhedron& poly)
{
    typedef typename internal::HalfedgeDS::Vertex  PolyhedronVertex;
    typedef typename PolyhedronVertex::Point       PolyhedronPoint;
    Dcel d;
    for (Polyhedron::Vertex_const_iterator vit = poly.vertices_begin(); vit != poly.vertices_end(); ++vit){
        PolyhedronPoint p = (*vit).point();
		Point3d point(p.x(), p.y(), p.z());
        d.addVertex(point);
    }

    //add faces to dcel

    return d;
}
#endif

#ifdef  CG3_EIGENMESH_DEFINED
/**
 * @ingroup cg3cgal
 * @brief cgal::polyhedron::getPolyhedronFromEigenMesh
 * @param mesh
 * @return
 */
CG3_INLINE cgal::Polyhedron polyhedronFromEigenMesh(const SimpleEigenMesh& mesh)
{
    class PolyhedronBuilder : public CGAL::Modifier_base<internal::HalfedgeDS>
    {
    public:
        const SimpleEigenMesh* mesh;

        PolyhedronBuilder(const SimpleEigenMesh* mesh) : mesh(mesh)
        {}

        void operator()( internal::HalfedgeDS& hds)
        {
            // Postcondition: hds is a valid polyhedral surface.
            CGAL::Polyhedron_incremental_builder_3<internal::HalfedgeDS> B( hds, true);
            B.begin_surface(mesh->numberVertices(), mesh->numberFaces());

            typedef typename internal::HalfedgeDS::Vertex   PolyhedronVertex;
            typedef typename PolyhedronVertex::Point        PolyhedronPoint;

            for (unsigned int vIndex = 0; vIndex < mesh->numberVertices(); vIndex++){
				Point3d coordinate = mesh->vertex(vIndex);
                B.add_vertex(PolyhedronPoint(coordinate.x(), coordinate.y(), coordinate.z()));
            }

            for (unsigned int fIndex = 0; fIndex < mesh->numberFaces(); fIndex++){
                B.begin_facet();
				Point3i face = mesh->face(fIndex);
                for (unsigned int vi = 0; vi < 3; vi++) {
                    B.add_vertex_to_facet(face[vi]);
                }
                B.end_facet();
            }
            B.end_surface();
        }
    };

    Polyhedron pmesh;
    PolyhedronBuilder polyhedronEigenMeshBuilder(&mesh);
    pmesh.delegate(polyhedronEigenMeshBuilder);

    return pmesh;
}


CG3_INLINE SimpleEigenMesh eigenMeshFromPolyhedron(const cgal::Polyhedron& poly)
{
    typedef typename internal::HalfedgeDS::Vertex  PolyhedronVertex;
    typedef typename PolyhedronVertex::Point       PolyhedronPoint;
    typedef typename Polyhedron::Halfedge_around_facet_const_circulator Halfedge_facet_circulator;

    SimpleEigenMesh d;

    std::map<PolyhedronPoint, unsigned int> map;

    for (Polyhedron::Vertex_const_iterator vit = poly.vertices_begin(); vit != poly.vertices_end(); ++vit) {
        PolyhedronPoint p = (*vit).point();
		Point3d point(p.x(), p.y(), p.z());
        map.insert(std::make_pair(p, d.addVertex(point)));
    }

    for (Polyhedron::Facet_const_iterator fit = poly.facets_begin(); fit != poly.facets_end(); ++fit) {
        Halfedge_facet_circulator circulator = fit->facet_begin();

        unsigned int v[3];
        int i = 0;
        do {
            v[i] = map.at(circulator->vertex()->point());
            i++;
        } while (++circulator != fit->facet_begin());

        d.addFace(v[0], v[1], v[2]);
    }

    return d;
}

#endif

} //namespace cg3::cgal
} //namespace cg3



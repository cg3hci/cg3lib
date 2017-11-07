#include "cgal_polyhedron.h"

namespace cg3 {

#ifdef  CG3_DCEL_DEFINED
cgal::polyhedron::Polyhedron_3 cgal::polyhedron::getPolyhedronFromDcel(
        const Dcel& dcel,
        std::map<const Dcel::Vertex*, int>& vertexMap,
        std::map<const Dcel::Face*, int>& faceMap) {

    class PolyhedronBuilder : public CGAL::Modifier_base<HalfedgeDS> {
    public:
        const Dcel* mesh;
        std::map<const Dcel::Vertex*, int>* vertexMap;
        std::map<const Dcel::Face*, int>* faceMap;

        PolyhedronBuilder(const Dcel* dcel,
                              std::map<const Dcel::Vertex*, int>& vertexMap,
                              std::map<const Dcel::Face*, int>& faceMap) :
            mesh(dcel), vertexMap(&vertexMap), faceMap(&faceMap) {
        }

        void operator()( HalfedgeDS& hds) {
            vertexMap->clear();
            faceMap->clear();

            // Postcondition: hds is a valid polyhedral surface.
            CGAL::Polyhedron_incremental_builder_3<HalfedgeDS> B( hds, true);

            B.begin_surface(mesh->getNumberVertices(), mesh->getNumberFaces(), mesh->getNumberHalfEdges());

            typedef typename HalfedgeDS::Vertex                PolyhedronVertex;
            typedef typename PolyhedronVertex::Point    PolyhedronPoint;

            int vIndex = 0;
            for (const Dcel::Vertex* v : mesh->vertexIterator()) {
                Pointd coordinate = v->getCoordinate();

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

    Polyhedron_3 mesh;
    PolyhedronBuilder polyhedronDcelBuilder(&dcel, vertexMap, faceMap);
    mesh.delegate(polyhedronDcelBuilder);

    return mesh;
}

Dcel cgal::polyhedron::getDcelFromPolyhedron(const cgal::polyhedron::Polyhedron_3& poly) {
    typedef typename HalfedgeDS::Vertex                PolyhedronVertex;
    typedef typename PolyhedronVertex::Point    PolyhedronPoint;
    Dcel d;
    for (Polyhedron_3::Vertex_const_iterator vit = poly.vertices_begin(); vit != poly.vertices_end(); ++vit){
        PolyhedronPoint p = (*vit).point();
        Pointd point(p.x(), p.y(), p.z());
        d.addVertex(point);
    }

    //add faces to dcel


    return d;
}
#endif

#ifdef  CG3_EIGENMESH_DEFINED
cgal::polyhedron::Polyhedron_3 cgal::polyhedron::getPolyhedronFromEigenMesh(const SimpleEigenMesh& mesh) {
    class PolyhedronBuilder : public CGAL::Modifier_base<HalfedgeDS> {
    public:
        const SimpleEigenMesh* mesh;

        PolyhedronBuilder(const SimpleEigenMesh* mesh) : mesh(mesh){
        }

        void operator()( HalfedgeDS& hds) {

            // Postcondition: hds is a valid polyhedral surface.
            CGAL::Polyhedron_incremental_builder_3<HalfedgeDS> B( hds, true);

            B.begin_surface(mesh->getNumberVertices(), mesh->getNumberFaces());

            typedef typename HalfedgeDS::Vertex                PolyhedronVertex;
            typedef typename PolyhedronVertex::Point    PolyhedronPoint;

            for (unsigned int vIndex = 0; vIndex < mesh->getNumberVertices(); vIndex++){
                Pointd coordinate = mesh->getVertex(vIndex);
                B.add_vertex(PolyhedronPoint(coordinate.x(), coordinate.y(), coordinate.z()));
            }

            for (unsigned int fIndex = 0; fIndex < mesh->getNumberFaces(); fIndex++){
                B.begin_facet();

                Pointi face = mesh->getFace(fIndex);
                for (unsigned int vi = 0; vi < 3; vi++) {
                    B.add_vertex_to_facet(face[vi]);
                }

                B.end_facet();
            }

            B.end_surface();
        }
    };

    Polyhedron_3 pmesh;
    PolyhedronBuilder polyhedronEigenMeshBuilder(&mesh);
    pmesh.delegate(polyhedronEigenMeshBuilder);

    return pmesh;
}
#endif

}



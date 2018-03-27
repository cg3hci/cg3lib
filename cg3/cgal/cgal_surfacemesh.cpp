/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "cgal_surfacemesh.h"

namespace cg3 {
namespace cgal {
#ifdef CG3_DCEL_DEFINED
surfaceMesh::SurfaceMesh surfaceMesh::getSurfaceMeshFromDcel(const Dcel &d)
{
    SurfaceMesh mesh;
    std::map<const Dcel::Vertex*, VertexDescriptor> mapV;
    for(const Dcel::Vertex* v : d.vertexIterator()){
        VertexDescriptor vd = mesh.add_vertex((K::Point_3(v->getCoordinate().x(),v->getCoordinate().y(),v->getCoordinate().z())));
        mapV[v] = vd;
    }
    for (const Dcel::Face* f : d.faceIterator()){
        std::list<VertexDescriptor> lv;
        for (const Dcel::Vertex* v : f->incidentVertexIterator()){
            lv.push_back(mapV.at(v));
        }
        mesh.add_face(lv);
    }
    return mesh;
}

#endif

}
}


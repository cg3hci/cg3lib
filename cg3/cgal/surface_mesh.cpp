/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "surface_mesh.h"

#ifdef  CG3_DCEL_DEFINED
#include <cg3/meshes/dcel/dcel.h>
#endif

#ifdef  CG3_EIGENMESH_DEFINED
#include <cg3/meshes/eigenmesh/eigenmesh.h>
#endif

namespace cg3 {
namespace cgal {
namespace internal {

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef SurfaceMesh::Vertex_index VertexDescriptor;

} //namespace cg3::cgal::internal

#ifdef CG3_DCEL_DEFINED
/**
 * @ingroup cg3cgal
 * @brief getSurfaceMeshFromDcel
 * @param d
 * @return
 */
CG3_INLINE SurfaceMesh surfaceMeshFromDcel(const Dcel &d)
{
    SurfaceMesh mesh;
    std::map<const Dcel::Vertex*, internal::VertexDescriptor> mapV;
    for(const Dcel::Vertex* v : d.vertexIterator()){
        internal::VertexDescriptor vd = mesh.add_vertex((internal::K::Point_3(v->coordinate().x(),v->coordinate().y(),v->coordinate().z())));
        mapV[v] = vd;
    }
    for (const Dcel::Face* f : d.faceIterator()){
        std::list<internal::VertexDescriptor> lv;
        for (const Dcel::Vertex* v : f->incidentVertexIterator()){
            lv.push_back(mapV.at(v));
        }
        mesh.add_face(lv);
    }
    return mesh;
}
#endif

} //namespace cg3::cgal
} //namespace cg3


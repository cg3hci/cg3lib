/**
  * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
  * This Source Code Form is subject to the terms of the GNU GPL 3.0
  *
  * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
  */

#include "cinolib_mesh_conversions.h"

#ifdef CG3_EIGENMESH_DEFINED
#include <cg3/meshes/eigenmesh/eigenmesh.h>
#endif //CG3_EIGENMESH_DEFINED

#ifdef CG3_DCEL_DEFINED
#include <cg3/meshes/dcel/dcel.h>
#endif //CG3_DCEL_DEFINED

namespace cg3 {

#ifdef CG3_EIGENMESH_DEFINED
CG3_INLINE void eigenMeshToTrimesh(cinolib::Trimesh<>& m, const SimpleEigenMesh& simpleEigenMesh)
{
    unsigned int nVertices=simpleEigenMesh.numberVertices();
    unsigned int nFaces=simpleEigenMesh.numberFaces();

    std::vector<double> coords;
    std::vector<unsigned int> tris;

    coords.resize(nVertices*3);
    tris.resize(nFaces*3);

    for(unsigned int i=0;i<nVertices;++i) {
        unsigned int j=i*3;
        coords[j]=simpleEigenMesh.vertex(i).x();
        coords[j+1]=simpleEigenMesh.vertex(i).y();
        coords[j+2]=simpleEigenMesh.vertex(i).z();

    }
    for(unsigned int i=0;i<nFaces;++i) {
        unsigned int j=i*3;
        tris[j]=simpleEigenMesh.face(i).x();
        tris[j+1]=simpleEigenMesh.face(i).y();
        tris[j+2]=simpleEigenMesh.face(i).z();
    }
    m = cinolib::Trimesh<>(coords, tris);
}
#endif

#ifdef CG3_DCEL_DEFINED
CG3_INLINE void dcelToTrimesh(cinolib::Trimesh<>& m, const Dcel& d)
{
    unsigned int nVertices=d.numberVertices();
    unsigned int nFaces=d.numberFaces();

    std::vector<double> coords;
    std::vector<unsigned int> tris;

    std::map<const Dcel::Vertex*, int> map;

    coords.resize(nVertices*3);
    tris.resize(nFaces*3);

    unsigned int i = 0;
    for(const Dcel::Vertex* v : d.vertexIterator()) {
		Point3d coord = v->coordinate();
        unsigned int j=i*3;
        coords[j]=coord.x();
        coords[j+1]=coord.y();
        coords[j+2]=coord.z();
        map[v] = i;
        i++;
    }

    i = 0;
    for(const Dcel::Face* f : d.faceIterator()) {
        unsigned int j=i*3;
        for (const Dcel::Vertex* v : f->incidentVertexIterator()){
            if (j < (i+1)*3){
                tris[j] = map[v];
                j++;
            }
        }
        i++;
    }
    m = cinolib::Trimesh<>(coords, tris);
}
#endif

}

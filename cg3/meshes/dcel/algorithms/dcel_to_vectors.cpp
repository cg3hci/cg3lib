/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "dcel_to_vectors.h"

namespace cg3 {

/**
 * @brief dcelAlgorithms::vectorFaces
 * @param vector
 * @param d
 */
CG3_INLINE void dcelAlgorithms::vectorFaces(std::vector<const Dcel::Face*>& vector, const Dcel& d)
{
    int i = 0;
    vector.resize(d.numberFaces());
    for (const Dcel::Face* f : d.faceIterator()){
        vector[i++] = f;
    }
}

CG3_INLINE void dcelAlgorithms::vectorFaces(std::vector<Dcel::Face*>& vector, Dcel& d)
{
    int i = 0;
    vector.resize(d.numberFaces());
    for (Dcel::Face* f : d.faceIterator()){
        vector[i++] = f;
    }
}

CG3_INLINE void dcelAlgorithms::vectorMesh(
        std::vector<Point3d>& coords,
        std::vector<std::vector<int> >& faces,
        const Dcel& d,
        std::vector<const Dcel::Vertex*>& mappingVertices,
        std::vector<const Dcel::Face*>& mappingFaces)
{
    std::map<const Dcel::Vertex*, int> vertices;
    int nv = 0, nf = 0;
    coords.resize(d.numberVertices());
    mappingVertices.resize(d.numberVertices());
    faces.resize(d.numberFaces());
    mappingFaces.resize(d.numberFaces());

    for (const Dcel::Vertex* v : d.vertexIterator()) {
        coords[nv] = v->coordinate();
        mappingVertices[nv] = v;
        vertices[v] = nv++;
    }

    for (const Dcel::Face* f : d.faceIterator()) {
        std::vector<int> face;
        for (const Dcel::Vertex* inc : f->incidentVertexIterator()){
            face.push_back(vertices[inc]);
        }
        faces[nf] = face;
        mappingFaces[nf++] = f;
    }
}

}

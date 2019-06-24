/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "dcel_builder.h"

namespace cg3 {

CG3_INLINE DcelBuilder::DcelBuilder(Dcel startingDcel) : d(startingDcel), updateNormalOnInsertion(true)
{
    for (cg3::Dcel::Vertex* v : d.vertexIterator()) {
        mapVertices[v->coordinate()] = v->id();
    }
    for (cg3::Dcel::HalfEdge* he : d.halfEdgeIterator()){
        mapHalfEdges[std::make_pair(he->fromVertex()->id(), he->toVertex()->id())] = he->id();
    }
}

CG3_INLINE Dcel& DcelBuilder::dcel()
{
    return d;
}

CG3_INLINE unsigned int DcelBuilder::addVertex(const Point3d& p, const Vec3d& n, const Color &c, int flag)
{
    if (mapVertices.find(p) == mapVertices.end()){
        cg3::Dcel::Vertex* v = d.addVertex(p, n, c);
        mapVertices[p] = v->id();
        v->setFlag(flag);
        return v->id();
    }
    else
        return mapVertices[p];
}

CG3_INLINE int DcelBuilder::addFace(
        unsigned int vid1,
        unsigned int vid2,
        unsigned int vid3,
        const Color& c,
        int flag)
{
    std::vector<uint> vids(3);
    vids[0] = vid1;
    vids[1] = vid2;
    vids[2] = vid3;
    return addFace(vids, c, flag);
}

CG3_INLINE int DcelBuilder::addFace(
        unsigned int vid1,
        unsigned int vid2,
        unsigned int vid3,
        unsigned int vid4,
        const Color& c,
        int flag)
{
    std::vector<uint> vids(4);
    vids[0] = vid1;
    vids[1] = vid2;
    vids[2] = vid3;
    vids[3] = vid4;
    return addFace(vids, c, flag);
}

CG3_INLINE int DcelBuilder::addFace(const std::vector<uint>& vids, const Color& c, int flag)
{
    //one of the ids does not exist in the dcel
    for (const uint& vid : vids)
        if (d.vertex(vid) == nullptr)
            return -1;

    std::vector<std::pair<uint, uint>> pes;
    for (uint i = 0; i < vids.size(); ++i){
        pes.push_back(std::make_pair(vids[i], vids[(i+1)%vids.size()]));
    }

    // one of the three edges already exists in the dcel ->
    // bad orientation of face or non edge-manifold mesh
    for (const std::pair<uint, uint>& pe : pes)
        if (mapHalfEdges.find(pe) != mapHalfEdges.end())
            return -1;

    //looking for twins...
    std::vector<std::pair<uint, uint>>  tpes;
    for (const std::pair<uint, uint>& pe : pes)
        tpes.push_back(std::make_pair(pe.second, pe.first));

    std::vector<cg3::Dcel::HalfEdge*> tes(tpes.size(), nullptr);

    std::map<std::pair<unsigned int, unsigned int>, unsigned int>::iterator it;
    for (uint i = 0; i < tpes.size(); ++i){
        it = mapHalfEdges.find(tpes[i]);
        if (it != mapHalfEdges.end()){
            tes[i] = d.halfEdge(it->second);
            if (tes[i]->twin() != nullptr){
                std::cerr << "Warning Dcel Builder: Half Edge has already a twin! "
                             "Possible Non-Manifold Mesh\n";
            }
        }
    }

    //add face
    cg3::Dcel::Face* f = d.addFace();

    std::vector<cg3::Dcel::Vertex*> vs;
    std::vector<cg3::Dcel::HalfEdge*> hes(vids.size());

    //get vertices
    for (uint vid : vids)
        vs.push_back(d.vertex(vid));

    //add half edges
    for (uint i = 0; i < hes.size(); i++)
        hes[i] = d.addHalfEdge();


    for (uint i = 0; i < hes.size(); i++){
        //from and to vertex
        hes[i]->setFromVertex(vs[i]);
        hes[i]->setToVertex(vs[(i+1)%hes.size()]);

        //twin
        hes[i]->setTwin(tes[i]);
        if (tes[i])
            tes[i]->setTwin(hes[i]);

        //vertex incident
        vs[i]->setIncidentHalfEdge(hes[i]);

        //face
        hes[i]->setFace(f);

        //prev and next
        if (i > 0){
            hes[i]->setPrev(hes[i-1]);
            hes[i-1]->setNext(hes[i]);
        }

        //mapHalfEdges
        mapHalfEdges.insert(std::make_pair(
                                std::make_pair(vids[i], vids[(i+1)%vids.size()]),
                                hes[i]->id()));

    }

    //prev and next
    hes[0]->setPrev(hes[hes.size()-1]);
    hes[hes.size()-1]->setNext(hes[0]);

    //other settings f
    f->setOuterHalfEdge(hes[0]);
    f->setColor(c);
    f->setFlag(flag);

    if (updateNormalOnInsertion) f->updateArea();
    return f->id();
}

CG3_INLINE int DcelBuilder::addFace(
        const Point3d& p1,
        const Point3d& p2,
        const Point3d& p3,
        const Color& c,
        int flag)
{
    unsigned int vid1, vid2, vid3;

    //setting vids
    std::map<cg3::Point3d, unsigned int>::iterator it;
    it = mapVertices.find(p1);
    if (it == mapVertices.end())
        vid1 = addVertex(p1);
    else
        vid1 = it->second;

    it = mapVertices.find(p2);
    if (it == mapVertices.end())
        vid2 = addVertex(p2);
    else
        vid2 = it->second;

    it = mapVertices.find(p3);
    if (it == mapVertices.end())
        vid3 = addVertex(p3);
    else
        vid3 = it->second;

    return addFace(vid1, vid2, vid3, c, flag);
}

CG3_INLINE int DcelBuilder::addFace(
        const Point3d& p1,
        const Point3d& p2,
        const Point3d& p3,
        const Point3d& p4,
        const Color& c,
        int flag)
{
    unsigned int vid1, vid2, vid3, vid4;

    //setting vids
    std::map<cg3::Point3d, unsigned int>::iterator it;
    it = mapVertices.find(p1);
    if (it == mapVertices.end())
        vid1 = addVertex(p1);
    else
        vid1 = it->second;

    it = mapVertices.find(p2);
    if (it == mapVertices.end())
        vid2 = addVertex(p2);
    else
        vid2 = it->second;

    it = mapVertices.find(p3);
    if (it == mapVertices.end())
        vid3 = addVertex(p3);
    else
        vid3 = it->second;

    it = mapVertices.find(p4);
    if (it == mapVertices.end())
        vid4 = addVertex(p4);
    else
        vid4 = it->second;

    return addFace(vid1, vid2, vid3, vid4, c, flag);
}

CG3_INLINE int DcelBuilder::addFace(const std::vector<Point3d>& ps, const Color& c, int flag)
{
    std::vector<uint> vids(ps.size());
    std::map<cg3::Point3d, unsigned int>::iterator it;
    for (uint i = 0; i < ps.size(); i++){
        it = mapVertices.find(ps[i]);
        if (it == mapVertices.end())
            vids[i] = addVertex(ps[i]);
        else
            vids[i] = it->second;
    }
    return addFace(vids, c, flag);
}

CG3_INLINE void DcelBuilder::finalize()
{
    d.updateBoundingBox();
    if (updateNormalOnInsertion)
        d.updateVertexNormals();
}

CG3_INLINE void DcelBuilder::setUpdateNormalOnInsertion(bool b)
{
    updateNormalOnInsertion = b;
}

}

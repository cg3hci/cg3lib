/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */

#include "aabbtree.h"

#include <random>

namespace cg3 {
namespace cgal {

/**
 * @brief  Creates an empty AABBTree. This object cannot be used.
 */
AABBTree::AABBTree() {
}

/**
 * @brief Copy constructor.
 * @param[in] other: another AABBTree
 */
AABBTree::AABBTree(const AABBTree& other) :
    forDistanceQueries(other.forDistanceQueries),
    treeType(other.treeType),
    triangles(other.triangles),
    bb(other.bb)
{
    #ifdef  CG3_DCEL_DEFINED
    mapDcelVerticesToCgalPoints = other.mapDcelVerticesToCgalPoints;
    mapCgalPointsToDcelVertices = other.mapCgalPointsToDcelVertices;
    mapCgalTrianglesToDcelFaces = other.mapCgalTrianglesToDcelFaces;
    #endif
    #if defined(TRIMESH_DEFINED) || defined( CG3_EIGENMESH_DEFINED)
    mapIdVerticesToCgalPoints = other.mapIdVerticesToCgalPoints;
    mapCgalTrianglesToIdTriangles = other.mapCgalTrianglesToIdTriangles;
    #endif
    tree.insert(triangles.begin(), triangles.end());

    if (forDistanceQueries)
        tree.accelerate_distance_queries();
}

/**
 * @brief Move constructor.
 * @param[in] other: another AABBTree
 */
AABBTree::AABBTree(AABBTree &&other) :
    forDistanceQueries(other.forDistanceQueries),
    treeType(other.treeType),
    triangles(other.triangles),
    bb(other.bb)
{
    #ifdef  CG3_DCEL_DEFINED
    mapDcelVerticesToCgalPoints = std::move(other.mapDcelVerticesToCgalPoints);
    mapCgalPointsToDcelVertices = std::move(other.mapCgalPointsToDcelVertices);
    mapCgalTrianglesToDcelFaces = std::move(other.mapCgalTrianglesToDcelFaces);
    #endif
    #if defined(TRIMESH_DEFINED) || defined( CG3_EIGENMESH_DEFINED)
    mapIdVerticesToCgalPoints = std::move(other.mapIdVerticesToCgalPoints);
    mapCgalTrianglesToIdTriangles = std::move(other.mapCgalTrianglesToIdTriangles);
    #endif
    tree.insert(triangles.begin(), triangles.end());

    if (forDistanceQueries)
        tree.accelerate_distance_queries();
}

#ifdef TRIMESH_DEFINED
/**
 * @brief Constructor that creates an AABBTree with the triangles of the input mesh.
 * @param[in] t: the trimesh on which is constructed the tree.
 * @param[in] forDistanceQueries: use this parameter to optimize the tree for distance queries.
 */
AABBTree::AABBTree(const Trimesh<double>& t, bool forDistanceQueries)
{
    treeType = TRIMESH;
    for (int i = 0; i < t.numVertices(); i++){
        Pointd p = t.vertex(i);
        CGALPoint pp(p.x(), p.y(), p.z());
        mapIdVerticesToCgalPoints[i] = pp;
    }
    for (int i = 0; i < t.numTriangles(); ++i){
        int i1 = t.tri_vertex_id(i, 0), i2 = t.tri_vertex_id(i, 1), i3 = t.tri_vertex_id(i, 2);
        assert(mapIdVerticesToCgalPoints.find(i1) != mapIdVerticesToCgalPoints.end());
        assert(mapIdVerticesToCgalPoints.find(i2) != mapIdVerticesToCgalPoints.end());
        assert(mapIdVerticesToCgalPoints.find(i3) != mapIdVerticesToCgalPoints.end());
        CGALTriangle tr(mapIdVerticesToCgalPoints.at(i1), mapIdVerticesToCgalPoints.at(i2), mapIdVerticesToCgalPoints.at(i3));
        mapCgalTrianglesToIdTriangles[tr] = i;
        triangles.push_back(tr);
    }
    tree.insert(triangles.begin(), triangles.end());

    if (forDistanceQueries)
        tree.accelerate_distance_queries();

    bb  = t.getBoundingBox();
}
#endif

#ifdef  CG3_EIGENMESH_DEFINED
/**
 * @brief Constructor that creates an AABBTree with the triangles of the input mesh.
 * @param[in] m: the eigenmesh on which is constructed the tree.
 * @param[in] forDistanceQueries: use this parameter to optimize the tree for distance queries.
 */
AABBTree::AABBTree(const SimpleEigenMesh& m, bool forDistanceQueries)
{
    treeType = EIGENMESH;
    for (unsigned int i = 0; i < m.getNumberVertices(); i++){
        Pointd p = m.getVertex(i);
        CGALPoint pp(p.x(), p.y(), p.z());
        mapIdVerticesToCgalPoints[i] = pp;
    }
    for (unsigned int i = 0; i < m.getNumberFaces(); ++i){
        if (! m.isDegenerateTriangle(i)){
            Pointi f = m.getFace(i);
            int i1 = f(0), i2 = f(1), i3 = f(2);
            assert(mapIdVerticesToCgalPoints.find(i1) != mapIdVerticesToCgalPoints.end());
            assert(mapIdVerticesToCgalPoints.find(i2) != mapIdVerticesToCgalPoints.end());
            assert(mapIdVerticesToCgalPoints.find(i3) != mapIdVerticesToCgalPoints.end());
            CGALTriangle tr(mapIdVerticesToCgalPoints.at(i1), mapIdVerticesToCgalPoints.at(i2), mapIdVerticesToCgalPoints.at(i3));
            mapCgalTrianglesToIdTriangles[tr] = i;
            triangles.push_back(tr);
        }
    }
    tree.insert(triangles.begin(), triangles.end());

    if (forDistanceQueries)
        tree.accelerate_distance_queries();

    bb  = m.getBoundingBox();
}
#endif

#ifdef  CG3_DCEL_DEFINED
/**
 * @brief Constructor that creates an AABBTree with the triangles of the input mesh.
 * @param[in] d: the Dcel on which is constructed the tree.
 * @param[in] forDistanceQueries: use this parameter to optimize the tree for distance queries.
 */
AABBTree::AABBTree(const Dcel& d, bool forDistanceQueries) :
    forDistanceQueries(forDistanceQueries)
{
    treeType = DCEL;
    for (Dcel::ConstVertexIterator vit = d.vertexBegin(); vit != d.vertexEnd(); ++vit){
        const Dcel::Vertex* v = *vit;
        CGALPoint pp(v->getCoordinate().x(), v->getCoordinate().y(), v->getCoordinate().z());
        mapDcelVerticesToCgalPoints[v] = pp;
        mapCgalPointsToDcelVertices[pp] = v;
    }
    for (Dcel::ConstFaceIterator fit = d.faceBegin(); fit != d.faceEnd(); ++fit){
        const Dcel::Face* f = *fit;
        const Dcel::HalfEdge* he = f->getOuterHalfEdge();
        const Dcel::Vertex* v1 = he->getFromVertex();
        const Dcel::Vertex* v2 = he->getToVertex();
        const Dcel::Vertex* v3 = he->getNext()->getToVertex();
        CGALTriangle t(mapDcelVerticesToCgalPoints.at(v1), mapDcelVerticesToCgalPoints.at(v2), mapDcelVerticesToCgalPoints.at(v3));
        mapCgalTrianglesToDcelFaces[t] = f;
        triangles.push_back(t);
    }
    tree.insert(triangles.begin(), triangles.end());

    if (forDistanceQueries)
        tree.accelerate_distance_queries();

    bb = d.getBoundingBox();
}
#endif

/**
 * @brief Assignment operator.
 * @param[in] other: the tree which is assigned
 * @return the assigned tree
 */
AABBTree& AABBTree::operator=(const cgal::AABBTree& other)
{
    forDistanceQueries = other.forDistanceQueries;
    treeType = other.treeType;
    triangles = other.triangles;
    #ifdef  CG3_DCEL_DEFINED
    mapDcelVerticesToCgalPoints = other.mapDcelVerticesToCgalPoints;
    mapCgalPointsToDcelVertices = other.mapCgalPointsToDcelVertices;
    mapCgalTrianglesToDcelFaces = other.mapCgalTrianglesToDcelFaces;
    #endif
    #if defined(TRIMESH_DEFINED) || defined( CG3_EIGENMESH_DEFINED)
    mapIdVerticesToCgalPoints = other.mapIdVerticesToCgalPoints;
    mapCgalTrianglesToIdTriangles = other.mapCgalTrianglesToIdTriangles;
    #endif
    tree.clear();
    tree.insert(triangles.begin(), triangles.end());

    if (forDistanceQueries)
        tree.accelerate_distance_queries();

    bb = other.bb;
    return *this;
}

/**
 * @brief Returns the number of triangles which are intersected by the segment given by the two points p1 and p2.
 * @param[in] p1: starting point of the segment query
 * @param[in] p2: ending point of the segment query
 * @return the number of triangles intersected by the segment
 */
int AABBTree::getNumberIntersectedPrimitives(const Pointd& p1, const Pointd& p2) const
{
    CGALPoint pa(p1.x(), p1.y(), p1.z());
    CGALPoint pb(p2.x(), p2.y(), p2.z());
    CGALRay ray_query(pa,pb);
    return (int) tree.number_of_intersected_primitives(ray_query);
}

/**
 * @brief AABBTree::getNumberIntersectedPrimitives
 * @param b
 * @return
 */
int AABBTree::getNumberIntersectedPrimitives(const BoundingBox& b) const
{
    CGALBoundingBox bb(b.getMinX(), b.getMinY(), b.getMinZ(), b.getMaxX(), b.getMaxY(), b.getMaxZ());
    return (int) tree.number_of_intersected_primitives(bb);
}

/**
 * @brief AABBTree::getSquaredDistance
 * @param p
 * @return
 */
double AABBTree::getSquaredDistance(const Pointd& p) const
{
    CGALPoint query(p.x(), p.y(), p.z());
    return tree.squared_distance(query);
}

/**
 * @brief AABBTree::getNearestPoint
 * @param p
 * @return
 */
Pointd AABBTree::getNearestPoint(const Pointd& p) const
{
    CGALPoint query(p.x(), p.y(), p.z());
    CGALPoint closest = tree.closest_point(query);
    return Pointd(closest.x(), closest.y(), closest.z());
}

/**
 * @brief AABBTree::isInside
 * @param p
 * @param numberOfChecks
 * @return
 */
bool AABBTree::isInside(const Pointd& p, int numberOfChecks) const
{
    static std::random_device rd;
    static std::mt19937 e2(rd());
    assert(numberOfChecks % 2 == 1);
    int inside = 0, outside = 0;
    std::uniform_real_distribution<> dist(0, 6);
    std::uniform_real_distribution<> distx(bb.getMinX(), bb.getMaxX());
    std::uniform_real_distribution<> disty(bb.getMinY(), bb.getMaxY());
    std::uniform_real_distribution<> distz(bb.getMinZ(), bb.getMaxZ());
    for (int i = 0; i < numberOfChecks; i++) {
        Pointd boundingPoint;
        double n1, n2;
        int side = std::floor(dist(e2));
        switch(side % 3){
            case 0: // x
                n1 = disty(e2);
                n2 = distz(e2);
                boundingPoint.setY(n1);
                boundingPoint.setZ(n2);
                if (side == 0)
                    boundingPoint.setX(bb.getMinX());
                else
                    boundingPoint.setX(bb.getMaxX());
                break;
            case 1: // y
                n1 = distx(e2);
                n2 = distz(e2);
                boundingPoint.setX(n1);
                boundingPoint.setZ(n2);
                if (side == 1)
                    boundingPoint.setY(bb.getMinY());
                else
                    boundingPoint.setY(bb.getMaxY());
                break;
            case 2: // z
                n1 = distx(e2);
                n2 = disty(e2);
                boundingPoint.setX(n1);
                boundingPoint.setY(n2);
                if (side == 2)
                    boundingPoint.setZ(bb.getMinZ());
                else
                    boundingPoint.setZ(bb.getMaxZ());
                break;
        }

        int numberIntersected = getNumberIntersectedPrimitives(p, boundingPoint);
        if (numberIntersected % 2 == 1)
            inside++;
        else
            outside++;
    }
    return inside > outside;
}

/**
 * @brief AABBTree::isInsidePseudoRandom
 * @param p
 * @param numberOfChecks
 * @return
 */
bool AABBTree::isInsidePseudoRandom(const Pointd& p, int numberOfChecks) const
{
    assert(numberOfChecks % 2 == 1);
    int inside = 0, outside = 0;
    double distx = bb.getMaxX() - bb.getMinX();
    double disty = bb.getMaxY() - bb.getMinY();
    double distz = bb.getMaxZ() - bb.getMinZ();
    for (int i = 0; i < numberOfChecks; i++) {
        Pointd boundingPoint;
        double n1, n2;
        int side = rand()%6;
        switch(side % 3){
            case 0: // x
                n1 = (double)rand()/((double)RAND_MAX/disty) + bb.getMinY();
                //n1 = disty(e2);
                n2 = (double)rand()/((double)RAND_MAX/distz) + bb.getMinZ();
                //n2 = distz(e2);
                boundingPoint.setY(n1);
                boundingPoint.setZ(n2);
                if (side == 0)
                    boundingPoint.setX(bb.getMinX());
                else
                    boundingPoint.setX(bb.getMaxX());
                break;
            case 1: // y
                n1 = (double)rand()/((double)RAND_MAX/distx) + bb.getMinX();
                //n1 = distx(e2);
                n2 = (double)rand()/((double)RAND_MAX/distz) + bb.getMinZ();
                //n2 = distz(e2);
                boundingPoint.setX(n1);
                boundingPoint.setZ(n2);
                if (side == 1)
                    boundingPoint.setY(bb.getMinY());
                else
                    boundingPoint.setY(bb.getMaxY());
                break;
            case 2: // z
                n1 = (double)rand()/((double)RAND_MAX/distx) + bb.getMinX();
                //n1 = distx(e2);
                n2 = (double)rand()/((double)RAND_MAX/disty) + bb.getMinY();
                //n2 = disty(e2);
                boundingPoint.setX(n1);
                boundingPoint.setY(n2);
                if (side == 2)
                    boundingPoint.setZ(bb.getMinZ());
                else
                    boundingPoint.setZ(bb.getMaxZ());
                break;
        }

        int numberIntersected = getNumberIntersectedPrimitives(p, boundingPoint);
        if (numberIntersected % 2 == 1)
            inside++;
        else
            outside++;
    }
    return inside > outside;
}

#ifdef  CG3_DCEL_DEFINED
/**
 * @brief AABBTree::getContainedDcelFaces
 * @param outputList
 * @param b
 */
void AABBTree::getContainedDcelFaces(
        std::list<const Dcel::Face*>& outputList,
        const BoundingBox& b) const
{
    assert(treeType == DCEL);
    CGALBoundingBox bb(b.getMinX(), b.getMinY(), b.getMinZ(), b.getMaxX(), b.getMaxY(), b.getMaxZ());
    std::list< Tree::Primitive_id > trianglesIds;
    tree.all_intersected_primitives(bb, std::back_inserter(trianglesIds));
    for (std::list< Tree::Primitive_id >::const_iterator it = trianglesIds.begin(); it != trianglesIds.end(); ++it){
        const Tree::Primitive_id id = *it;
        const CGALTriangle t = *id;
        std::map<CGALTriangle, const Dcel::Face*, cmpCGALTriangle>::const_iterator mit = mapCgalTrianglesToDcelFaces.find(t);
        assert(mit != mapCgalTrianglesToDcelFaces.end());
        outputList.push_back(mit->second);
    }
}

/**
 * @brief AABBTree::getContainedDcelFaces
 * @param b
 * @return
 */
std::list<const Dcel::Face*> AABBTree::getContainedDcelFaces(const BoundingBox& b) const
{
    std::list<const Dcel::Face*> outputList;
    getContainedDcelFaces(outputList, b);
    return outputList;
}

/**
 * @brief AABBTree::getCompletelyContainedDcelFaces
 * @param outputList
 * @param b
 */
void AABBTree::getCompletelyContainedDcelFaces(
        std::list<const Dcel::Face*>& outputList,
        const BoundingBox& b) const
{
    assert(treeType == DCEL);
    getContainedDcelFaces(outputList, b);

    std::list<const Dcel::Face*>::iterator i = outputList.begin();
    while (i != outputList.end()) {
        const Dcel::Face* f = *i;
        Pointd p1 = f->getVertex1()->getCoordinate(),
               p2 = f->getVertex2()->getCoordinate(),
               p3 = f->getVertex3()->getCoordinate();

        if (!b.isIntern(p1) || !b.isIntern(p2) || !b.isIntern(p3)) {
            i =outputList.erase(i);
        }
        else ++i;
    }
}

/**
 * @brief AABBTree::getCompletelyContainedDcelFaces
 * @param outputList
 * @param b
 */
void AABBTree::getCompletelyContainedDcelFaces(
        std::list<unsigned int>& outputList,
        const BoundingBox& b) const
{
    std::list<const Dcel::Face*> output;
    getCompletelyContainedDcelFaces(output, b);
    outputList.clear();
    for (const Dcel::Face* f : output)
        outputList.push_back(f->getId());
}

/**
 * @brief AABBTree::getCompletelyContainedDcelFaces
 * @param b
 * @return
 */
std::list<const Dcel::Face*> AABBTree::getCompletelyContainedDcelFaces(const BoundingBox& b) const
{
    assert(treeType == DCEL);
    std::list<const Dcel::Face*> output;
    getCompletelyContainedDcelFaces(output, b);
    return output;
}

/**
 * @brief AABBTree::getNearestDcelFace
 * @param p
 * @return
 */
const Dcel::Face* AABBTree::getNearestDcelFace(const Pointd& p) const
{
    assert(treeType == DCEL);
    CGALPoint query(p.x(), p.y(), p.z());
    AABB_triangle_traits::Point_and_primitive_id ppid = tree.closest_point_and_primitive(query);
    const Tree::Primitive_id tp = ppid.second;
    const CGALTriangle t = *tp;
    std::map<CGALTriangle, const Dcel::Face*, cmpCGALTriangle>::const_iterator mit = mapCgalTrianglesToDcelFaces.find(t);
    assert(mit != mapCgalTrianglesToDcelFaces.end());
    return mit->second;

}

/**
 * @brief AABBTree::getNearestDcelVertex
 * @param p
 * @return
 */
const Dcel::Vertex* AABBTree::getNearestDcelVertex(const Pointd& p) const
{
    assert(treeType == DCEL);
    const Dcel::Face* closestFace = getNearestDcelFace(p);
    const Dcel::Vertex* closest = nullptr;
    double dist = std::numeric_limits<double>::max();
    for (const Dcel::Vertex* v : closestFace->incidentVertexIterator()){
        if (dist > p.dist(v->getCoordinate())){
            closest = v;
            dist = p.dist(v->getCoordinate());
        }
    }
    assert(closest != nullptr);
    return closest;
}
#endif

#ifdef  CG3_EIGENMESH_DEFINED
/**
 * @brief AABBTree::getIntersectEigenFaces
 * @param p1
 * @param p2
 * @param outputList
 */
void AABBTree::getIntersectEigenFaces(const Pointd& p1, const Pointd &p2, std::vector<int> &outputList)
{
    assert(treeType == EIGENMESH);
    CGALPoint pa(p1.x(), p1.y(), p1.z());
    CGALPoint pb(p2.x(), p2.y(), p2.z());
    //CGALRay ray_query(pa,pb);
    K::Segment_3 ray_query(pa,pb);
    std::list< Tree::Primitive_id > trianglesIds;
    tree.all_intersected_primitives(ray_query, std::back_inserter(trianglesIds));
    for (std::list< Tree::Primitive_id >::const_iterator it = trianglesIds.begin(); it != trianglesIds.end(); ++it){
        const Tree::Primitive_id id = *it;
        const CGALTriangle t = *id;
        std::map<CGALTriangle, int, cmpCGALTriangle>::const_iterator mit = mapCgalTrianglesToIdTriangles.find(t);
        outputList.push_back(mit->second);
    }
}

/**
 * @brief AABBTree::getNearestEigenFace
 * @param p
 * @return
 */
unsigned int AABBTree::getNearestEigenFace(const Pointd& p) const
{
    assert(treeType == EIGENMESH);
    CGALPoint query(p.x(), p.y(), p.z());
    AABB_triangle_traits::Point_and_primitive_id ppid = tree.closest_point_and_primitive(query);
    const Tree::Primitive_id tp = ppid.second;
    const CGALTriangle t = *tp;
    std::map<CGALTriangle, int, cmpCGALTriangle>::const_iterator mit = mapCgalTrianglesToIdTriangles.find(t);
    assert(mit != mapCgalTrianglesToIdTriangles.end());
    return mit->second;
}
#endif

/**
 * @brief AABBTree::isDegeneratedTriangle
 * @param t
 * @return
 */
bool AABBTree::isDegeneratedTriangle(const AABBTree::CGALTriangle& t)
{
    return (t[0] == t[1] || t[0] == t[2] || t[1] == t[2]);
}

} //namespace cg3::cgal
} //namespace cg3

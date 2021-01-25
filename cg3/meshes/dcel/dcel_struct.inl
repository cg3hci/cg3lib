/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "dcel_struct.h"
#include <cg3/utilities/comparators.h>
#include <cg3/utilities/utils.h>
#include <cg3/utilities/const.h>
#include <cg3/io/serialize.h>
#include <cg3/io/load_save_file.h>
#include <cg3/geometry/transformations3.h>

#ifdef  CG3_CGAL_DEFINED
#include <cg3/cgal/triangulation3.h>
#endif //CGAL_DEFINED

#ifdef  CG3_EIGENMESH_DEFINED
#include <cg3/meshes/eigenmesh/eigenmesh.h>
#endif //EIGENMESH_DEFINED

#ifdef CG3_CINOLIB_DEFINED
#include <cinolib/meshes/trimesh.h>
#endif //CG3_CINOLIB_DEFINED

namespace cg3 {

/****
 * Range Based Iterators
 *****/

template <class V, class HE, class F>
class TemplatedDcel<V, HE, F>::ConstVertexRangeBasedIterator
{
    friend class TemplatedDcel;
public:
    typename TemplatedDcel::ConstVertexIterator begin() const {return d->vertexBegin();}
    typename TemplatedDcel::ConstVertexIterator end() const {return d->vertexEnd();}
private:
    ConstVertexRangeBasedIterator(const TemplatedDcel *d) : d(d) {}
    const TemplatedDcel *d;
};

template <class V, class HE, class F>
class TemplatedDcel<V, HE, F>::ConstHalfEdgeRangeBasedIterator
{
    friend class TemplatedDcel;
public:
    typename TemplatedDcel::ConstHalfEdgeIterator
    begin() const {return d->halfEdgeBegin();}
    typename TemplatedDcel::ConstHalfEdgeIterator end() const {return d->halfEdgeEnd();}
private:
    ConstHalfEdgeRangeBasedIterator(const TemplatedDcel *d) : d(d) {}
    const TemplatedDcel *d;
};

template <class V, class HE, class F>
class TemplatedDcel<V, HE, F>::ConstFaceRangeBasedIterator
{
    friend class TemplatedDcel;
public:
    typename TemplatedDcel::ConstFaceIterator begin() const {return d->faceBegin();}
    typename TemplatedDcel::ConstFaceIterator end() const {return d->faceEnd();}
private:
    ConstFaceRangeBasedIterator(const TemplatedDcel *d) : d(d) {}
    const TemplatedDcel *d;
};

template <class V, class HE, class F>
class TemplatedDcel<V, HE, F>::VertexRangeBasedIterator
{
    friend class TemplatedDcel;
public:
    typename TemplatedDcel::VertexIterator begin() {return d->vertexBegin();}
    typename TemplatedDcel::VertexIterator end() {return d->vertexEnd();}
private:
    VertexRangeBasedIterator(TemplatedDcel *d) : d(d) {}
    TemplatedDcel *d;
};

template <class V, class HE, class F>
class TemplatedDcel<V, HE, F>::HalfEdgeRangeBasedIterator
{
    friend class TemplatedDcel;
public:
    typename TemplatedDcel::HalfEdgeIterator begin() {return d->halfEdgeBegin();}
    typename TemplatedDcel::HalfEdgeIterator end() {return d->halfEdgeEnd();}
private:
    HalfEdgeRangeBasedIterator(TemplatedDcel *d) : d(d) {}
    TemplatedDcel *d;
};

template <class V, class HE, class F>
class TemplatedDcel<V, HE, F>::FaceRangeBasedIterator
{
    friend class TemplatedDcel;
public:
    typename TemplatedDcel::FaceIterator begin() {return d->faceBegin();}
    typename TemplatedDcel::FaceIterator end() {return d->faceEnd();}
private:
    FaceRangeBasedIterator(TemplatedDcel *d) : d(d) {}
    TemplatedDcel *d;
};

/***
 * Dcel Constructors
 ***/

/**
 * @brief Empty constructor
 *
 * Creates an empty Dcel: 0 vertices, 0 half edges and 0 faces.
 */
template <class V, class HE, class F>
TemplatedDcel<V, HE, F>::TemplatedDcel() :
    nVertices(0),
    nHalfEdges(0),
    nFaces(0)
{
}

template <class V, class HE, class F>
inline TemplatedDcel<V, HE, F>::TemplatedDcel(const char *filename) :
	nVertices(0),
	nHalfEdges(0),
	nFaces(0)
{
	if (!loadFromFile(std::string(filename)))
		std::cerr << filename << " not found or not valid.\n";
}

template <class V, class HE, class F>
inline TemplatedDcel<V, HE, F>::TemplatedDcel(const std::string& filename) :
	nVertices(0),
	nHalfEdges(0),
	nFaces(0)
{
	if (!loadFromFile(std::string(filename)))
		std::cerr << filename << " not found or not valid.\n";
}

/**
 * @brief Dcel's Copy Constructor.
 *
 * Creates a new Dcel starting from the input Dcel, creating new instances of
 * vertices, half edges and faces and setting all the relations between them.
 *
 * @param[in] dcel.
 */
template <class V, class HE, class F>
TemplatedDcel<V, HE, F>::TemplatedDcel(const TemplatedDcel<V, HE, F>& dcel)
{
    unusedVids = dcel.unusedVids;
    unusedHeids = dcel.unusedHeids;
    unusedFids = dcel.unusedFids;
    nVertices = dcel.nVertices;
    nHalfEdges = dcel.nHalfEdges;
    nFaces = dcel.nFaces;
    bBox = dcel.bBox;
    std::map<const TemplatedDcel::Vertex*, TemplatedDcel::Vertex*> mapVertices;
	std::map<const TemplatedDcel::HalfEdge*, TemplatedDcel::HalfEdge*>
			mapHalfEdges;
    std::map<const TemplatedDcel::Face*, TemplatedDcel::Face*> mapFaces;
    vertices.resize(dcel.vertices.size(), nullptr);
    #ifdef NDEBUG
	vertexCoordinates.resize(dcel.vertexCoordinates.size(), Point3d());
	vertexNormals.resize(dcel.vertexNormals.size(), Vec3d());
    vertexColors.resize(dcel.vertexColors.size(), Color());
    #endif
    for (const TemplatedDcel::Vertex* ov : dcel.vertexIterator()) {
        TemplatedDcel::Vertex* v = addVertex(ov->id());
        v->setId(ov->id());
        v->setCoordinate(ov->coordinate());
        v->setFlag(ov->flag());
        v->setCardinality(ov->cardinality());
        v->setNormal(ov->normal());
        v->setColor(ov->color());
        mapVertices[ov] = v;
    }

    halfEdges.resize(dcel.halfEdges.size(), nullptr);
    for (const TemplatedDcel::HalfEdge* ohe : dcel.halfEdgeIterator()) {
        TemplatedDcel::HalfEdge* he = addHalfEdge(ohe->id());
        he->setId(ohe->id());
        he->setFlag(ohe->flag());
        he->setFromVertex(mapVertices[ohe->fromVertex()]);
        he->setToVertex(mapVertices[ohe->toVertex()]);
        mapHalfEdges[ohe] = he;
    }

    faces.resize(dcel.faces.size(), nullptr);
    #ifdef NDEBUG
	faceNormals.resize(dcel.faceNormals.size(), Vec3d());
    faceColors.resize(dcel.faceColors.size(), Color());
    #endif
    for (const Face* of : dcel.faceIterator()){
        TemplatedDcel::Face* f = addFace(of->id());
        f->setId(of->id());
        f->setColor(of->color());
        f->setFlag(of->flag());
        f->setNormal(of->normal());
        f->setArea(of->area());
        f->setOuterHalfEdge(mapHalfEdges[of->outerHalfEdge()]);
		for (typename TemplatedDcel<V, HE, F>::Face::ConstInnerHalfEdgeIterator
			 heit = of->innerHalfEdgeBegin();
			 heit != of->innerHalfEdgeEnd();
			 ++heit){
            f->addInnerHalfEdge(mapHalfEdges[*heit]);
        }
        mapFaces[of] = f;
    }

    for (const TemplatedDcel::HalfEdge* ohe : dcel.halfEdgeIterator()) {
        TemplatedDcel::HalfEdge* he = mapHalfEdges[ohe];
        he->setNext(mapHalfEdges[ohe->next()]);
        he->setPrev(mapHalfEdges[ohe->prev()]);
        he->setTwin(mapHalfEdges[ohe->twin()]);
        he->setFace(mapFaces[ohe->face()]);
    }

    for (const TemplatedDcel::Vertex* ov : dcel.vertexIterator()) {
        TemplatedDcel::Vertex * v = mapVertices[ov];
        v->setIncidentHalfEdge(mapHalfEdges[ov->incidentHalfEdge()]);
    }
}

/**
 * @brief Dcel's Move Constructor.
 * @param[in] dcel
 */
template <class V, class HE, class F>
TemplatedDcel<V, HE, F>::TemplatedDcel(TemplatedDcel<V, HE, F>&& dcel)
{
    vertices = std::move(dcel.vertices);
    faces = std::move(dcel.faces);
    halfEdges = std::move(dcel.halfEdges);
    unusedVids = std::move(dcel.unusedVids);
    unusedHeids = std::move(dcel.unusedHeids);
    unusedFids = std::move(dcel.unusedFids);
    nVertices = std::move(dcel.nVertices);
    nHalfEdges = std::move(dcel.nHalfEdges);
    nFaces = std::move(dcel.nFaces);
    bBox = std::move(dcel.bBox);
    #ifdef NDEBUG
    vertexCoordinates = std::move(dcel.vertexCoordinates);
    vertexNormals = std::move(dcel.vertexNormals);
    vertexColors = std::move(dcel.vertexColors);
    faceNormals = std::move(dcel.faceNormals);
    faceColors = std::move(dcel.faceColors);
    for (Vertex* v : vertexIterator()){
        v->parent = this;
    }
    for (HalfEdge* he : halfEdgeIterator()){
        he->parent = this;
    }
    for (Face* f : faceIterator()){
        f->parent = this;
    }
    #endif

}

#ifdef  CG3_EIGENMESH_DEFINED
template <class V, class HE, class F>
TemplatedDcel<V, HE, F>::TemplatedDcel(const cg3::SimpleEigenMesh& eigenMesh)
{
    copyFrom(eigenMesh);
    updateVertexNormals();
}

template <class V, class HE, class F>
TemplatedDcel<V, HE, F>::TemplatedDcel(const cg3::EigenMesh& eigenMesh)
{
    copyFrom(eigenMesh);
}
#endif // CG3_EIGNEMESH_DEFINED

#ifdef CG3_CINOLIB_DEFINED
template <class V, class HE, class F>
TemplatedDcel<V, HE, F>::TemplatedDcel(const cinolib::Trimesh<> &trimesh)
{
    copyFrom(trimesh);
}
#endif //CG3_CINOLIB_DEFINED

/**
 * @brief Dcel's Destructor.
 *
 * Deletes all the elements of the Dcel.
 */
template <class V, class HE, class F>
TemplatedDcel<V, HE, F>::~TemplatedDcel()
{
    for (unsigned int i=0; i<vertices.size(); i++)
        if (vertices[i]!= nullptr)
            delete vertices[i];
    for (unsigned int i=0; i<halfEdges.size(); i++)
        if (halfEdges[i] != nullptr)
            delete halfEdges[i];
    for (unsigned int i=0; i<faces.size(); i++)
        if (faces[i] != nullptr)
            delete faces[i];
}

/***
 * Dcel Member Functions
 **/

/**
 * @param[in] idVertex: id of the vertex that will be returned
 * @return Const pointer to the vertex if the id exists, nullptr otherwise
 * @par Complexity:
 *      \e O(1)
 */
template <class V, class HE, class F>
inline const typename TemplatedDcel<V, HE, F>::Vertex*
TemplatedDcel<V, HE, F>::vertex(unsigned int idVertex) const
{
    if (idVertex>= vertices.size()) return nullptr;
    return vertices[idVertex];
}

/**
 * @param[in] idHalfEdge: id of the half edge that will be returned
 * @return Const pointer to the half edge if the id exists, nullptr otherwise
 * @par Complexity:
 *      \e O(1)
 */
template <class V, class HE, class F>
inline const typename TemplatedDcel<V, HE, F>::HalfEdge*
TemplatedDcel<V, HE, F>::halfEdge(unsigned int idHalfEdge) const
{
    if (idHalfEdge>= halfEdges.size()) return nullptr;
    return halfEdges[idHalfEdge];
}

/**
 * @param[in] idFace: id of the face that will be returned
 * @return Const pointer to the face if the id exists, nullptr otherwise
 * @par Complexity:
 *      \e O(1)
 */
template <class V, class HE, class F>
inline const typename TemplatedDcel<V, HE, F>::Face*
TemplatedDcel<V, HE, F>::face(unsigned int idFace) const
{
    if (idFace>= faces.size()) return nullptr;
    return faces[idFace];
}

/**
 * @note Does not calculate the bounding box,
 * it just return the last computed one.
 * @see updateBoundingBox()
 * @return The bounding box of the mesh after its last update
 * @par Complexity:
 *      \e O(1)
 */
template <class V, class HE, class F>
inline BoundingBox3 TemplatedDcel<V, HE, F>::boundingBox() const
{
    return bBox;
}

/**
 * @return The number of vertices contained in the Dcel.
 */
template <class V, class HE, class F>
inline unsigned int TemplatedDcel<V, HE, F>::numberVertices () const
{
    return nVertices;
}

/**
 * @return The number of half edges contained in the Dcel.
 */
template <class V, class HE, class F>
inline unsigned int TemplatedDcel<V, HE, F>::numberHalfEdges () const
{
    return nHalfEdges;
}

/**
 * @return The number of faces contained in the Dcel.
 */
template <class V, class HE, class F>
inline unsigned int TemplatedDcel<V, HE, F>::numberFaces () const
{
    return nFaces;
}

/**
 * @param[in] v: a pointer to a Vertex
 * @return true if the vertex belongs to this Dcel, false otherwise
 * @see vertexBelongsToThis
 */
template <class V, class HE, class F>
inline bool
TemplatedDcel<V, HE, F>::contains(const typename TemplatedDcel::Vertex* v) const
{
    return vertexBelongsToThis(v);
}

/**
 * @param[in] he: a pointer to a HalfEdge
 * @return true if the half edge belongs to this Dcel, false otherwise
 * @see halfEdgeBelongsToThis
 */
template <class V, class HE, class F>
inline bool
TemplatedDcel<V, HE, F>::contains(const typename TemplatedDcel::HalfEdge* he) const
{
    return halfEdgeBelongsToThis(he);
}

/**
 * @param[in] he: a pointer to a Face
 * @return true if the face belongs to this Dcel, false otherwise
 * @see faceBelongsToThis
 */
template <class V, class HE, class F>
inline bool
TemplatedDcel<V, HE, F>::contains(const typename TemplatedDcel::Face* f) const
{
    return  faceBelongsToThis(f);
}

/**
 * @return An iterator that points to the first vertex of the Dcel
 */
template <class V, class HE, class F>
inline typename TemplatedDcel<V, HE, F>::ConstVertexIterator
TemplatedDcel<V, HE, F>::vertexBegin() const
{
    unsigned int i = 0;
    while (i < vertices.size() && vertices[i] == nullptr) ++i;
    return ConstVertexIterator(i, vertices);
}

/**
 * @return An iterator that points after the last vertex of the Dcel
 */
template <class V, class HE, class F>
inline typename TemplatedDcel<V, HE, F>::ConstVertexIterator
TemplatedDcel<V, HE, F>::vertexEnd() const
{
    return ConstVertexIterator((unsigned int)vertices.size(), vertices);
}

/**
 * @return An iterator that points to the first half edge of the Dcel
 */
template <class V, class HE, class F>
inline typename TemplatedDcel<V, HE, F>::ConstHalfEdgeIterator
TemplatedDcel<V, HE, F>::halfEdgeBegin() const
{
    unsigned int i = 0;
    while (i < halfEdges.size() && halfEdges[i] == nullptr) ++i;
    return ConstHalfEdgeIterator(i, halfEdges);
}

/**
 * @return An iterator that points after the last half edge of the Dcel
 */
template <class V, class HE, class F>
inline typename TemplatedDcel<V, HE, F>::ConstHalfEdgeIterator
TemplatedDcel<V, HE, F>::halfEdgeEnd() const
{
    return ConstHalfEdgeIterator((unsigned int)halfEdges.size(), halfEdges);
}

/**
 * @return An iterator that points to the first face of the Dcel
 */
template <class V, class HE, class F>
inline typename TemplatedDcel<V, HE, F>::ConstFaceIterator
TemplatedDcel<V, HE, F>::faceBegin() const
{
    unsigned int i = 0;
    while (i < faces.size() && faces[i] == nullptr) ++i;
    return ConstFaceIterator(i, faces);
}

/**
 * @return An iterator that points after the last face of the Dcel
 */
template <class V, class HE, class F>
inline typename TemplatedDcel<V, HE, F>::ConstFaceIterator
TemplatedDcel<V, HE, F>::faceEnd() const
{
    return ConstFaceIterator((unsigned int)faces.size(), faces);
}

/**
 * @param[in] idVertex: id of the vertex that will be returned
 * @return The pointer to the vertex if the id exists, nullptr otherwise
 * @par Complexity:
 *      \e O(1)
 */
template <class V, class HE, class F>
inline typename TemplatedDcel<V, HE, F>::Vertex*
TemplatedDcel<V, HE, F>::vertex(unsigned int idVertex)
{
    if (idVertex>= vertices.size()) return nullptr;
    return vertices[idVertex];
}

/**
 * @param[in] idHalfEdge: id of the half edge that will be returned
 * @return The pointer to the half edge if the id exists, nullptr otherwise
 * @par Complexity:
 *      \e O(1)
 */
template <class V, class HE, class F>
inline typename TemplatedDcel<V, HE, F>::HalfEdge*
TemplatedDcel<V, HE, F>::halfEdge(unsigned int idHalfEdge)
{
    if (idHalfEdge>= halfEdges.size()) return nullptr;
    return halfEdges[idHalfEdge];
}

/**
 * @param[in] idFace: id of the face that will be returned
 * @return The pointer to the face if the id exists, nullptr otherwise
 * @par Complexity:
 *      \e O(1)
 */
template <class V, class HE, class F>
inline typename TemplatedDcel<V, HE, F>::Face*
TemplatedDcel<V, HE, F>::face(unsigned int idFace)
{
    if (idFace>= faces.size()) return nullptr;
    return faces[idFace];
}

/**
 * @brief Removes the vertex pointed by the input iterator.
 *
 * Afther the execution of this function, the input iterator cannot be used anymore.
 *
 * Sets to nullptr all the following fields if they contains a reference to the deleted vertex:
 *
 * for every outgoing half edge he:
 * - he->fromVertex
 * - he->twin->toVertex
 *
 * @param[in] vit: the iterator that points to the vertex
 * @return the iterator that points to the next vertex in the list of vertices
 * @par Complexity:
 *      \e O(nIncidentHalfEdges) -> \e ~O(1)
 */
template <class V, class HE, class F>
inline typename TemplatedDcel<V, HE, F>::VertexIterator
TemplatedDcel<V, HE, F>::deleteVertex(
        const typename TemplatedDcel<V, HE, F>::VertexIterator& vit)
{
    TemplatedDcel::VertexIterator nv = vit;
    TemplatedDcel::Vertex* v = *vit;

    deleteVertex(v);
    return ++nv;
}

/**
 * @brief Removes the half edge pointed by the input iterator.
 *
 * Afther the execution of this function, the input iterator cannot be
 * used anymore.
 *
 * Sets to nullptr all the following fields if they contains a reference to the
 * deleted half edge:
 * - he->twin->twin
 * - he->next->prev
 * - he->prev->next
 * - he->fromVertex->incidentHalfEdge
 * - he->face->outerHalfEdge
 * any inner half edge of he->face
 *
 * @param[in] heit: the iterator that points to the half edge
 * @return the iterator that points to the next half edge in the list of half
 * edges
 * @par Complexity:
 *      \e O(1)
 */
template <class V, class HE, class F>
inline typename TemplatedDcel<V, HE, F>::HalfEdgeIterator
TemplatedDcel<V, HE, F>::deleteHalfEdge(
        const typename TemplatedDcel<V, HE, F>::HalfEdgeIterator& heit)
{
    TemplatedDcel::HalfEdgeIterator nhe = heit;
    HalfEdge* he = *heit;

    deleteHalfEdge(he);

    return ++nhe;
}

/**
 * @brief Removes the face pointed by the input iterator.
 *
 * Afther the execution of this function, the input iterator cannot be used anymore.
 *
 * Sets to nullptr all the following fields if they contains a reference to the deleted face:
 * - he->face (and their nexts)
 * - inner he->face (and their next)
 *
 * @param[in] fit: the iterator that points to the face
 * @return the iterator that points to the next face in the list of faces
 * @par Complexity:
 *      \e O(nIncidentHalfEdges) -> \e ~O(1)
 */
template <class V, class HE, class F>
inline typename TemplatedDcel<V, HE, F>::FaceIterator
TemplatedDcel<V, HE, F>::deleteFace(
        const typename TemplatedDcel<V, HE, F>::FaceIterator& fit)
{
    TemplatedDcel::FaceIterator nf = fit;
    TemplatedDcel::Face* f = *fit;
    deleteFace(f);
    return ++nf;
}

/**
 * @brief Initialization function of Dcel::VertexIterator
 * @return An iterator that points to the first vertex of the Dcel
 */
template <class V, class HE, class F>
inline typename TemplatedDcel<V, HE, F>::VertexIterator
TemplatedDcel<V, HE, F>::vertexBegin()
{
    unsigned int i = 0;
    while (i < vertices.size() && vertices[i] == nullptr) ++i;
    return VertexIterator(i, vertices);
}

/**
 * @brief Finitialization function of Dcel::VertexIterator
 * @return An iterator that points after the last vertex of the Dcel
 */
template <class V, class HE, class F>
inline typename TemplatedDcel<V, HE, F>::VertexIterator
TemplatedDcel<V, HE, F>::vertexEnd()
{
    return VertexIterator((unsigned int)vertices.size(), vertices);
}

/**
 * @brief Initialization function of Dcel::HalfEdgeIterator
 * @return An iterator that points to the first half edge of the Dcel
 */
template <class V, class HE, class F>
inline typename TemplatedDcel<V, HE, F>::HalfEdgeIterator
TemplatedDcel<V, HE, F>::halfEdgeBegin()
{
    unsigned int i = 0;
    while (i < halfEdges.size() && halfEdges[i] == nullptr) ++i;
    return HalfEdgeIterator(i, halfEdges);
}

/**
 * @brief Finitialization function of Dcel::HalfEdgeIterator
 * @return An iterator that points after the last half edge of the Dcel
 */
template <class V, class HE, class F>
inline typename TemplatedDcel<V, HE, F>::HalfEdgeIterator
TemplatedDcel<V, HE, F>::halfEdgeEnd()
{
    return HalfEdgeIterator((unsigned int)halfEdges.size(), halfEdges);
}

/**
 * @brief Initialization function of Dcel::FaceIterator
 * @return An iterator that points to the first face of the Dcel
 */
template <class V, class HE, class F>
inline typename TemplatedDcel<V, HE, F>::FaceIterator
TemplatedDcel<V, HE, F>::faceBegin()
{
    unsigned int i = 0;
    while (i < faces.size() && faces[i] == nullptr) ++i;
    return FaceIterator(i, faces);
}

/**
 * @brief Finitialization function of Dcel::FaceIterator
 * @return An iterator that points after the last face of the Dcel
 */
template <class V, class HE, class F>
inline typename TemplatedDcel<V, HE, F>::FaceIterator
TemplatedDcel<V, HE, F>::faceEnd()
{
    return FaceIterator((unsigned int)faces.size(), faces);
}

/**
 * @return a const range based iterator on the vertices of the Dcel
 */
template <class V, class HE, class F>
inline const typename TemplatedDcel<V, HE, F>::ConstVertexRangeBasedIterator
TemplatedDcel<V, HE, F>::vertexIterator() const
{
    return ConstVertexRangeBasedIterator(this);
}

/**
 * @return a range based iterator on the vertices of the Dcel
 */
template <class V, class HE, class F>
inline typename TemplatedDcel<V, HE, F>::VertexRangeBasedIterator
TemplatedDcel<V, HE, F>::vertexIterator()
{
    return VertexRangeBasedIterator(this);
}

/**
 * @return a const range based iterator on the half edges of the Dcel
 */
template <class V, class HE, class F>
inline const typename TemplatedDcel<V, HE, F>::ConstHalfEdgeRangeBasedIterator
TemplatedDcel<V, HE, F>::halfEdgeIterator() const
{
    return ConstHalfEdgeRangeBasedIterator(this);
}

/**
 * @return a range based iterator on the half edges of the Dcel
 */
template <class V, class HE, class F>
inline typename TemplatedDcel<V, HE, F>::HalfEdgeRangeBasedIterator
TemplatedDcel<V, HE, F>::halfEdgeIterator()
{
    return HalfEdgeRangeBasedIterator(this);
}

/**
 * @return a const range based iterator on the faces of the Dcel
 */
template <class V, class HE, class F>
inline const typename TemplatedDcel<V, HE, F>::ConstFaceRangeBasedIterator
TemplatedDcel<V, HE, F>::faceIterator() const
{
    return ConstFaceRangeBasedIterator(this);
}

/**
 * @return a range based iterator on the faces of the Dcel
 */
template <class V, class HE, class F>
inline typename TemplatedDcel<V, HE, F>::FaceRangeBasedIterator
TemplatedDcel<V, HE, F>::faceIterator()
{
    return FaceRangeBasedIterator(this);
}

template <class V, class HE, class F>
bool TemplatedDcel<V, HE, F>::vertexBelongsToThis(
        const typename TemplatedDcel<V, HE, F>::Vertex* v) const
{
    if (!v) return false;
    #ifdef NDEBUG
    return v->parent == this;
    #else
    return v->id() < vertices.size() && vertices[v->id()] == v;
    #endif
}

template <class V, class HE, class F>
bool TemplatedDcel<V, HE, F>::halfEdgeBelongsToThis(
        const typename TemplatedDcel<V, HE, F>::HalfEdge* he) const
{
    if (!he) return false;
    #ifdef NDEBUG
    return he->parent == this;
    #else
    return he->id() < halfEdges.size() && halfEdges[he->id()] == he;
    #endif
}

template <class V, class HE, class F>
bool TemplatedDcel<V, HE, F>::faceBelongsToThis(
        const typename TemplatedDcel<V, HE, F>::Face* f) const
{
    if (!f) return false;
    #ifdef NDEBUG
    return f->parent == this;
    #else
    return f->id() < faces.size() && faces[f->id()] == f;
    #endif
}

/**
 * @brief Checks if a the Dcel is composed only of triangles
 * @return True if the Dcel is composed only of triangles, false otherwise
 * @par Complexity:
 *      \e O(numFaces)
 */
template <class V, class HE, class F>
bool TemplatedDcel<V, HE, F>::isTriangleMesh() const
{
    if (numberFaces() == 0) return false;
    for (const Face* f : faceIterator())
        if (! f->isTriangle()) return false;
    return true;
}

/**
 * @brief Computes the Surface area of the mesh, summing all the areas of
 * the Faces contained.
 * @return The Surface Area of the mesh
 * @par Complexity:
 *      \e O(numFaces)
 */
template <class V, class HE, class F>
double TemplatedDcel<V, HE, F>::surfaceArea() const
{
    double area = 0;
    for (const Face* f : faceIterator()){
        area += f->area();
    }
    return area;
}

/**
 * @brief Computes the Volume of the Mesh.
 *
 * It sums all the *signed* tet volumes, where every tet is made linking a
 * surface triangle and a fixed point in the space.
 *
 * @link https://stackoverflow.com/questions/1406029/how-to-calculate-the-
 * volume-of-a-3d-mesh-object-the-surface-of-which-is-made-up
 * @return The volume of the mesh.
 * @par Complexity:
 *      \e O(numFaces)
 */
template <class V, class HE, class F>
double TemplatedDcel<V, HE, F>::volume() const
{
    double sum = 0;
    for (const TemplatedDcel::Face* f : faceIterator())
        sum += f->signedVolume();
    return std::abs(sum);
}

template <class V, class HE, class F>
Point3d TemplatedDcel<V, HE, F>::barycenter() const
{
    Point3d bc;
    for (const TemplatedDcel::Vertex* v : vertexIterator()){
        bc += v->coordinate();
    }
    bc /= numberVertices();
    return bc;
}

template <class V, class HE, class F>
double TemplatedDcel<V, HE, F>::averageHalfEdgesLength() const
{
    double average = 0;
    for (const HalfEdge* he : halfEdgeIterator()){
        average += he->length();
    }
    average /= nHalfEdges;
    return average;
}

/**
 * @brief Saves the mesh in a Wavefront OBJ file.
 *
 * @param[in] fileNameObj: the file name, \b with \b obj \b extension.
 *
 * @par Complexity:
 *      \e O(numVertices) + \e O(numFaces) + \e O(numHalfEdges)
 */
template <class V, class HE, class F>
bool TemplatedDcel<V, HE, F>::saveOnObj(const std::string& fileNameObj) const
{
    return saveOnObj(fileNameObj, true);
}

/**
 * @brief Saves the mesh in a Wavefront OBJ file.
 *
 * @warning Holes of faces are not supported. Faces with holes will be closed
 * creating dummy edges.
 *
 * @param[in] fileNameObj: the file name, \b with \b obj \b extension.
 * @param[in] saveProperites: true if you want to save colors and normals of
 * the mesh.
 *
 * @par Complexity:
 *      \e O(numVertices) + \e O(numFaces) + \e O(numHalfEdges)
 */
template <class V, class HE, class F>
bool TemplatedDcel<V, HE, F>::saveOnObj(const std::string& fileNameObj, bool saveProperties) const
{
    std::vector<double> vertices;
    std::vector<double> verticesNormals;
	std::vector<float> vertexColors;
    std::vector<int> faces;
	std::vector<double> faceNormals;
    std::vector<unsigned int> faceSizes;
    std::vector<float> faceColors;

	toStdVectors(vertices, verticesNormals, vertexColors, faces, faceNormals,
				 faceSizes, faceColors);

	io::FileMeshMode fm;
	fm.setPolygonMesh();
    if (saveProperties) {
		fm.setFaceColors();
		fm.setVertexNormals();
	}
	return saveMeshOnObj(fileNameObj, numberVertices(), numberFaces(),
						 vertices.data(),faces.data(), fm,
						 verticesNormals.data(), io::RGB, vertexColors.data(),
						 faceColors.data(), faceSizes.data());

}

/**
 * @brief Saves the mesh in a PLY file.
 *
 * Default mode: saves only vertex normals and face colors.
 * To personalize the mode, use saveOnPly(const std::string&, bool, cg3::io::FileMeshMode).
 *
 * @warning Holes of faces are not supported. Faces with holes will be closed
 * creating dummy edges.
 *
 * @param[in] fileNamePly: the file name
 * @param[in] binary: boolen for saving the file in binary mode, default is true
 *
 * @par Complexity:
 *      \e O(numVertices) + \e O(numFaces) + \e O(numHalfEdges)
 */
template <class V, class HE, class F>
bool TemplatedDcel<V, HE, F>::saveOnPly(const std::string& fileNamePly, bool binary) const
{
	io::FileMeshMode fm(io::POLYGON_MESH, true, false, false, true);
	return saveOnPly(fileNamePly, binary, fm);
}

/**
 * @brief Saves the mesh in a PLY file.
 *
 * @warning Holes of faces are not supported. Faces with holes will be closed
 * creating dummy edges.
 *
 * @param[in] fileNamePly: the file name, \b with \b ply \b extension
 * @param[in] binary: boolen for saving the file in binary mode, default is true
 * @param[in] meshMode: controls what properties are going to be saves.
 * Check the cg3::io::FileMeshMode class.
 *
 * @par Complexity:
 *      \e O(numVertices) + \e O(numFaces) + \e O(numHalfEdges)
 */
template <class V, class HE, class F>
bool TemplatedDcel<V, HE, F>::saveOnPly(
		const std::string& fileNamePly,
		bool binary,
		io::FileMeshMode fm) const
{
    std::vector<double> vertices;
    std::vector<double> verticesNormals;
	std::vector<float> verticesColors;
    std::vector<int> faces;
	std::vector<double> faceNormals;
    std::vector<unsigned int> faceSizes;
    std::vector<float> faceColors;

	toStdVectors(vertices, verticesNormals, verticesColors,
				 faces, faceNormals, faceSizes, faceColors);

	return saveMeshOnPly(fileNamePly, numberVertices(), numberFaces(),
						 vertices.data(), faces.data(), binary, fm,
						 verticesNormals.data(), faceNormals.data(), io::RGB,
						 verticesColors.data(), faceColors.data(),
						 faceSizes.data());
}

/**
 * @brief Saves the mesh in the cg3's format "dcel".
 * Allows to explicitly save the holes of the faces.
 *
 * @param[in] fileNameDcel: the file name, \b with \b dcel \b extension
 *
 * @par Complexity:
 *      \e O(numVertices) + \e O(numFaces) + \e O(numHalfEdges)
 */
template <class V, class HE, class F>
void TemplatedDcel<V, HE, F>::saveOnDcelFile(
		const std::string& fileNameDcel) const
{
    std::ofstream myfile;
    myfile.open (fileNameDcel, std::ios::out | std::ios::binary);
    if (myfile.is_open()) {
        serialize(myfile);
    }
    myfile.close();
}

/**
 * @brief Adds a Vertex in the Dcel, returning its pointer.
 *
 * @param[in] p: coords of the vertex to add
 * @return Pointer to the Vertex added in the Dcel.
 * @par Complexity:
 *      \e O(1)
 */
template <class V, class HE, class F>
typename TemplatedDcel<V, HE, F>::Vertex *TemplatedDcel<V, HE, F>::addVertex(
		const Point3d& p,
		const Vec3d& n,
		const Color& c)
{
    #ifdef NDEBUG
    Vertex* last= new Vertex(*this);
    #else
    Vertex* last= new Vertex();
    #endif
    if (unusedVids.size() == 0) {
        last->setId(nVertices);
        vertices.push_back(last);
        #ifdef NDEBUG
        vertexCoordinates.push_back(p);
        vertexNormals.push_back(n);
        vertexColors.push_back(c);
        #else
        last->setCoordinate(p);
        last->setNormal(n);
        last->setColor(c);
        #endif
    }
    else {
        int vid = *(unusedVids.begin());
        last->setId(vid);
        vertices[vid] = last;
        unusedVids.erase(vid);
        #ifdef NDEBUG
        vertexCoordinates[vid] = p;
        vertexNormals[vid] = n;
        vertexColors[vid] = c;
        #else
        last->setCoordinate(p);
        last->setNormal(n);
        last->setColor(c);
        #endif

    }
    nVertices++;
    return last;
}

/**
 * @brief Adds a Half Edge in the Dcel, returning its pointer.
 *
 * @return Pointer to the Half Edge added in the Dcel.
 * @par Complessità:
 *      \e O(1)
 */
template <class V, class HE, class F>
typename TemplatedDcel<V, HE, F>::HalfEdge*
TemplatedDcel<V, HE, F>::addHalfEdge()
{
    #ifdef NDEBUG
    HalfEdge* last = new HalfEdge(*this);
    #else
    HalfEdge* last = new HalfEdge();
    #endif
    if (unusedHeids.size() == 0){
        last->setId(nHalfEdges);
        halfEdges.push_back(last);
        //halfEdgeLinks.push_back({-1, -1, -1, -1, -1, -1});
    }
    else {
        int heid = *(unusedHeids.begin());
        last->setId(heid);
        halfEdges[heid] = last;
        //halfEdgeLinks[heid] = {-1, -1, -1, -1, -1, -1};
        unusedHeids.erase(heid);
    }
    nHalfEdges++;
    return last;
}

/**
 * \~Italian
 * @brief Aggiunge una faccia alla Dcel e ne restituisce il puntatore.
 *
 * La Dcel::Face è inizializzata col costruttore vuoto, e successivamente
 * viene settato un id univoco.
 *
 * @return Il puntatore alla faccia appena inserita nella Dcel
 * @par Complessità:
 *      \e O(1)
 */
template <class V, class HE, class F>
typename TemplatedDcel<V, HE, F>::Face*
TemplatedDcel<V, HE, F>::addFace(const Vec3d& n, const Color& c)
{
    #ifdef NDEBUG
    Face* last = new Face(*this);
    #else
    Face* last = new Face();
    #endif
    if (unusedFids.size() == 0){
        last->setId(nFaces);
        faces.push_back(last);
        #ifdef NDEBUG
        faceNormals.push_back(n);
        faceColors.push_back(c);
        #else
        last->setNormal(n);
        last->setColor(c);
        #endif
    }
    else {
        int fid = *(unusedFids.begin());
        last->setId(fid);
        faces[fid] = last;
        unusedFids.erase(fid);
        #ifdef NDEBUG
        faceNormals[fid] = n;
        faceColors[fid] = c;
        #else
        last->setNormal(n);
        last->setColor(c);
        #endif
    }
    nFaces++;
    return last;
}

/**
 * \~Italian
 * @brief Funzione che elimina il vertice passato in input.
 *
 * Una volta eliminato, il vertice passato in input non è più utilizzabile.
 *
 * Setta a nullptr tutti i seguenti campi se contengono un riferimento al
 * vertice eliminato v:
 * per ogni half edge uscente he:
 * - he->fromVertex
 * - he->twin->toVertex
 *
 * @param[in] v: vertice da eliminare
 * @return True se il vertice è stato eliminato correttamente (ossia è stato
 * trovato un vertice con lo stesso id all'interno della lista di vertici),
 * false altrimenti
 * @par Complessità:
 *      \e O(nIncidentHalfEdges) ->  \e ~O(1)
 */
template <class V, class HE, class F>
bool TemplatedDcel<V, HE, F>::deleteVertex(typename TemplatedDcel::Vertex* v)
{
    if (v != nullptr){
        if (v->_incidentHalfEdge != nullptr){
            HalfEdge* he = v->_incidentHalfEdge;
            do {
                if (he != nullptr){
                    if (he->_fromVertex == v) he->_fromVertex = nullptr;
                    if (he->_twin != nullptr) {
                        he = he->_twin;
                        if (he->_toVertex == v) he->_toVertex = nullptr;
                        he = he->_next;
                    }
                    else he = v->_incidentHalfEdge;
                }
                else he = v->_incidentHalfEdge;
            } while (he != v->_incidentHalfEdge);
        }
        vertices[v->_id]=nullptr;
        unusedVids.insert(v->_id);
        nVertices--;

        delete v;
        return true;
    }
    else
        return false;
}

template <class V, class HE, class F>
bool TemplatedDcel<V, HE, F>::deleteVertex(unsigned int vid)
{
    return deleteVertex(vertex((vid)));
}

/**
 * \~Italian
 * @brief Funzione che elimina l'half edge passato in input.
 *
 * Una volta eliminato, il'half edge passato in input non è più utilizzabile.
 *
 * Setta a nullptr tutti i seguenti campi se contengono un riferimento all'half edge eliminato he:
 * - he->twin->twin
 * - he->next->prev
 * - he->prev->next
 * - he->fromVertex->incidentHalfEdge
 * - he->face->outerHalfEdge
 * eventuali inner half edge di he->face
 *
 * @param[in] he: half edge da eliminare
 * @return True se l'half edge è stato eliminato correttamente (ossia è stato trovato un half edge con
 * lo stesso id all'interno della lista degli half edge), false altrimenti
 * @par Complessità:
 *      \e O(1)
 */
template <class V, class HE, class F>
bool TemplatedDcel<V, HE, F>::deleteHalfEdge(HalfEdge* he)
{
    if (he != nullptr) {
        if (he->_twin != nullptr)
            if (he->_twin->_twin == he) he->_twin->_twin = nullptr;
        if (he->_next != nullptr)
            if (he->_next->_prev == he) he->_next->_prev = nullptr;
        if (he->_prev != nullptr)
            if(he->_prev->_next == he) he->_prev->_next = nullptr;
        if (he->_face != nullptr){
			if (he->_face->_outerHalfEdge == he)
				he->_face->_outerHalfEdge = nullptr;
            else if (he->_face->hasHoles()) {
				for (unsigned int i = 0;
					 i < he->_face->_innerHalfEdges.size(); i++){
                    if (he->_face->_innerHalfEdges[i] == he)
						he->_face->_innerHalfEdges.erase(
									he->_face->_innerHalfEdges.begin() + i--);
                }
            }
        }
        if (he->_fromVertex != nullptr)
			if (he->_fromVertex->_incidentHalfEdge == he)
				he->_fromVertex->_incidentHalfEdge = nullptr;
        halfEdges[he->_id] = nullptr;
        unusedHeids.insert(he->_id);
        nHalfEdges--;

        delete he;
        return true;
    }
    else
        return false;
}

template <class V, class HE, class F>
bool TemplatedDcel<V, HE, F>::deleteHalfEdge(unsigned int heid)
{
    return deleteHalfEdge(halfEdge(heid));
}

/**
 * \~Italian
 * @brief Funzione che elimina la faccia passata in input.
 *
 * Una volta eliminata, la faccia passata in input non è più utilizzabile.
 *
 * Setta a nullptr tutti i seguenti campi se contengono un riferimento alla
 * faccia eliminata f:
 * per ogni half edge incidente he:
 * - he->face
 *
 * @param[in] f: faccia da eliminare
 * @return True se la faccia è stata eliminata correttamente (ossia è stato
 * trovata una faccia con lo stesso id all'interno della lista delle facce),
 * false altrimenti
 * @par Complessità:
 *      \e O(nIncidentHalfEdges) -> \e ~O(1)
 */
template <class V, class HE, class F>
bool TemplatedDcel<V, HE, F>::deleteFace(Face* f)
{
    if (f != nullptr) {
        if (f->_outerHalfEdge != nullptr){
            HalfEdge* he = f->_outerHalfEdge;
            do {
                if (he->_face == f) he->_face = nullptr;
                he = he->_next;
            } while (he != f->_outerHalfEdge);
        }
        for (unsigned int i = 0; i < f->_innerHalfEdges.size(); i++){
            HalfEdge* he = f->_innerHalfEdges[i];
            do {
                if (he->_face == f) he->_face = nullptr;
                he = he->_next;
            } while (he != f->_innerHalfEdges[i]);
        }
        faces[f->id()]=nullptr;
        unusedFids.insert(f->id());
        nFaces--;
        delete f;
        return true;
    }
    else
        return false;
}

template <class V, class HE, class F>
bool TemplatedDcel<V, HE, F>::deleteFace(unsigned int fid)
{
    return deleteFace(face(fid));
}

template <class V, class HE, class F>
void TemplatedDcel<V, HE, F>::invertFaceOrientations()
{
    for (Face* f : faceIterator())
        f->invertOrientation();
    updateVertexNormals();
}

template <class V, class HE, class F>
void TemplatedDcel<V, HE, F>::deleteUnreferencedVertices()
{
    std::vector<bool> ref(vertices.size(), false);
    for (Face* f : faceIterator()){
        for (Vertex* v : f->incidentVertexIterator()){
            ref[v->id()] = true;
        }
    }
    for (uint i = 0; i < ref.size(); i++){
        if (!ref[i] && vertices[i] != nullptr)
            deleteVertex(i);
    }
}

template <class V, class HE, class F>
void TemplatedDcel<V, HE, F>::deleteDuplicatedVertices()
{
    std::vector<std::pair<uint, uint>> duplicated;
    for (uint i = 0; i < vertices.size(); ++i){
        for (uint j = i+1; j < vertices.size(); ++j) {
            if (vertices[i] && vertices[j] && vertices[i]->coordinate() == vertices[j]->coordinate()){
                duplicated.push_back(std::make_pair(i, j));
            }
        }
    }

    for (uint i = 0; i < duplicated.size(); ++i){
        //duplicated[i].second becomes duplicated[i].first
        for (HalfEdge* he : halfEdgeIterator()){
            if (he->fromVertex()->id() == duplicated[i].second){
                he->setFromVertex(vertices[duplicated[i].first]);
            }
            if (he->toVertex()->id() == duplicated[i].second){
                he->setToVertex(vertices[duplicated[i].first]);
            }
        }
        vertices[duplicated[i].second]->setIncidentHalfEdge(nullptr);
        deleteVertex(duplicated[i].second);

        //adjusting next duplicates: duplicated[i].second should not exists also in the next duplicated pairs!
        for (uint j = i+1; j < duplicated.size(); ++j){
            if (duplicated[j].first == duplicated[i].second){
                duplicated[j].first = duplicated[i].first;
            }
        }
    }

    //removing edges with from == to
    for (HalfEdge* he : halfEdgeIterator()){
        if (he->fromVertex() == he->toVertex()){
            he->prev()->setNext(he->next());
            he->next()->setPrev(he->prev());
            if (he->fromVertex()->incidentHalfEdge() == he)
                he->fromVertex()->setIncidentHalfEdge(he->next());
            if (he->face()->outerHalfEdge() == he)
                he->face()->setOuterHalfEdge(he->next());
            for (HalfEdge*& ihe : he->face()->innerHalfEdgeIterator()){
                if (ihe == he)
                    ihe = he->next();
            }
        }
    }
}

template<class V, class HE, class F>
void TemplatedDcel<V, HE, F>::updateFaceAreas()
{
    for (Face* f : faceIterator()){
        f->updateArea();
    }
}

/**
 * \~Italian
 * @brief Funzione che ricalcola e aggiorna le normali delle facce presenti nella Dcel.
 *
 * Richiama il metodo \c updateNormal() della classe Dcel::Face, per cui non aggiorna
 * le normali delle facce che non sono triangoli.
 *
 * @warning Funziona solo sulle facce che sono triangoli
 * @warning Utilizza Dcel::Face::constIncidentVertexIterator
 * @par Complessità:
 *      \e O(numFaces)
 */
template <class V, class HE, class F>
void TemplatedDcel<V, HE, F>::updateFaceNormals()
{
    for (Face* f : faceIterator()){
        f->updateNormal();
    }
}

/**
 * \~Italian
 * @brief Funzione che ricalcola e aggiorna le normali e le cardinalità dei vertici presenti nella Dcel.
 *
 * Richiama il metodo \c updateNormal() della classe Dcel::Vertex.
 *
 * @warning Utilizza Dcel::Vertex::ConstIncidentFaceIterator
 * @par Complessità:
 *      \e O(numVertices)
 */
template <class V, class HE, class F>
void TemplatedDcel<V, HE, F>::updateVertexNormals()
{
    for (Vertex* v : vertexIterator())
        v->updateNormal();
}

/**
 * \~Italian
 * @brief Funzione che ricalcola il bounding box più piccolo contenete la mesh
 * @return Il bounding box appena calcolato
 * @par Complessità:
 *      \e O(numVertices)
 */
template <class V, class HE, class F>
BoundingBox3 TemplatedDcel<V, HE, F>::updateBoundingBox()
{
    bBox.reset();
    for (const Vertex* v : vertexIterator()){
        const Point3d& coord = v->coordinate();

        bBox.setMinX(std::min(bBox.minX(), coord.x()));
        bBox.setMinY(std::min(bBox.minY(), coord.y()));
        bBox.setMinZ(std::min(bBox.minZ(), coord.z()));

        bBox.setMaxX(std::max(bBox.maxX(), coord.x()));
        bBox.setMaxY(std::max(bBox.maxY(), coord.y()));
        bBox.setMaxZ(std::max(bBox.maxZ(), coord.z()));
    }
    return bBox;
}

template <class V, class HE, class F>
void TemplatedDcel<V, HE, F>::setFaceColors(const Color& c)
{
    for (Face* f : faceIterator())
        f->setColor(c);
}

template <class V, class HE, class F>
void TemplatedDcel<V, HE, F>::setFaceFlags(int flag)
{
	for (Face* f : faceIterator())
		f->setFlag(flag);
}

template <class V, class HE, class F>
void TemplatedDcel<V, HE, F>::setVertexColors(const Color& c)
{
	for (Vertex* v : vertexIterator())
		v->setColor(c);
}

template <class V, class HE, class F>
void TemplatedDcel<V, HE, F>::setVertexFlags(int flag)
{
	for (Vertex* v : vertexIterator())
		v->setFlag(flag);
}

template <class V, class HE, class F>
void TemplatedDcel<V, HE, F>::scale(double scaleFactor)
{
    scale(Vec3d(scaleFactor, scaleFactor, scaleFactor));
}

template <class V, class HE, class F>
void TemplatedDcel<V, HE, F>::scale(const Vec3d& scaleVector)
{
    for (Vertex* v : vertexIterator()){
        Point3d p = v->coordinate();
        p *= scaleVector;
        v->setCoordinate(p);
    }
    updateBoundingBox();
}

template <class V, class HE, class F>
void TemplatedDcel<V, HE, F>::scale(const BoundingBox3& newBoundingBox)
{
    Point3d oldCenter = bBox.center();
    Point3d newCenter = newBoundingBox.center();
    Point3d deltaOld = bBox.max() - bBox.min();
    Point3d deltaNew = newBoundingBox.max() - newBoundingBox.min();
    for (Vertex* v : vertexIterator()) {
        v->setCoordinate(v->coordinate() - oldCenter);
        v->setCoordinate(v->coordinate() * (deltaNew / deltaOld));
        v->setCoordinate(v->coordinate() + newCenter);
    }
    bBox = newBoundingBox;
}

#ifdef CG3_WITH_EIGEN
template <class V, class HE, class F>
void TemplatedDcel<V, HE, F>::rotate(const Eigen::Matrix3d& matrix)
{
    Point3d c;
    rotate(matrix, c);
}

template <class V, class HE, class F>
void TemplatedDcel<V, HE, F>::rotate(const Eigen::Matrix3d &matrix, const Point3d& centroid)
{
    for (Vertex* v : vertexIterator()){
        Point3d r = v->coordinate();
        r.rotate(matrix, centroid);
        v->setCoordinate(r);
    }
    updateFaceNormals();
    updateVertexNormals();
    updateBoundingBox();
}
#endif

template <class V, class HE, class F>
void TemplatedDcel<V, HE, F>::rotate(const Vec3d& axis, double angle, const Point3d& centroid)
{
    double matrix[3][3];
    cg3::rotationMatrix(axis, angle, matrix);
    rotate(matrix, centroid);
}

template <class V, class HE, class F>
void TemplatedDcel<V, HE, F>::rotate(double matrix[3][3], const Point3d& centroid)
{
    for (Vertex* v : vertexIterator()){
        Point3d r = v->coordinate();
        r.rotate(matrix, centroid);
        v->setCoordinate(r);
        Vec3d n = v->normal();
        n.rotate(matrix, centroid);
        v->setNormal(n);
    }
    updateFaceNormals();
    updateBoundingBox();
}

template <class V, class HE, class F>
void TemplatedDcel<V, HE, F>::translate(const cg3::Vec3d& c)
{
    for (Vertex* v : vertexIterator()){
        v->setCoordinate(v->coordinate() + c);
    }
    updateBoundingBox();
}

/**
 * \~Italian
 * @brief Funzione che ricalcola gli id di vertici, half edge e facce della Dcel.
 *
 * Ricompatta gli id all'interno delle liste contenute della Dcel.
 * Può essere utile richiamare questa funzione se sono state effettuate diverse cancellazioni
 * di componenti, e soprattutto se non si sono memorizzati riferimenti alle componenti mediante
 * vecchi id.
 *
 * @par Complessità:
 *      \e O(numVertices \e + \e NumHalfEdges \e + \e NumFaces)
 */
template <class V, class HE, class F>
void TemplatedDcel<V, HE, F>::recalculateIds()
{
    nVertices = 0;
    for (unsigned int i = 0; i < vertices.size(); i++){
        vertices[nVertices] = vertices[i];
        if (vertices[i] != nullptr) {
            vertices[i]->setId(nVertices);
            nVertices++;
        }
    }
    unusedVids.clear();
    vertices.resize(nVertices);

    nHalfEdges = 0;
    for (unsigned int i = 0; i < halfEdges.size(); i++){
        halfEdges[nHalfEdges] = halfEdges[i];
        if (halfEdges[i] != nullptr) {
            halfEdges[i]->setId(nHalfEdges);
            nHalfEdges++;
        }
    }
    unusedHeids.clear();
    halfEdges.resize(nHalfEdges);

    nFaces = 0;
    for (unsigned int i = 0; i < faces.size(); i++){
        faces[nFaces] = faces[i];
        if (faces[i] != nullptr) {
            faces[i]->setId(nFaces);
            nFaces++;
        }
    }
    unusedFids.clear();
    faces.resize(nFaces);
}

/**
 * \~Italian
 * @brief Funzione che cancella tutti i dati contenuti nella Dcel.
 *
 * Per cancellazione si intende la rimozione di tutti i vertici,
 * gli half-edge e le facce precedentemente create, con relativa
 * perdita di tutte le informazioni in esse contenute.
 *
 * @par Complessità:
 *      \e O(numVertices \e + \e NumHalfEdges \e + \e NumFaces)
 */
template <class V, class HE, class F>
void TemplatedDcel<V, HE, F>::clear()
{
    for (unsigned int i=0; i<vertices.size(); i++)
        if (vertices[i] != nullptr)
            delete vertices[i];
    for (unsigned int i=0; i<halfEdges.size(); i++)
        if (halfEdges[i] != nullptr)
            delete halfEdges[i];
    for (unsigned int i=0; i<faces.size(); i++)
        if (faces[i] != nullptr)
            delete faces[i];
    vertices.clear();
    halfEdges.clear();
    faces.clear();
    unusedVids.clear();
    unusedHeids.clear();
    unusedFids.clear();
    nVertices = 0;
    nFaces = 0;
    nHalfEdges = 0;
    #ifdef NDEBUG
    vertexCoordinates.clear();
    vertexNormals.clear();
    vertexColors.clear();
    faceNormals.clear();
    faceColors.clear();
    #endif
}

#ifdef  CG3_CGAL_DEFINED
/**
 * \~Italian
 * @brief Funzione che, presa in ingresso una faccia, ne crea una triangolazione.
 *
 * La faccia in ingresso diventa un triangolo (se se lo era già rimarrà un triangolo),
 * e inserisce nella Dcel tanti altri triangoli che comporranno la faccia triangolata.
 *
 * Utilizza CGAL.
 * Utilizzabile SOLAMENTE se è definita la costante letterale CGAL_DEFINED
 * @param[in] f: la faccia che verrà triangolata
 * @return Il numero di triangoli che compone la faccia appena triangolata.
 */
template <class V, class HE, class F>
unsigned int TemplatedDcel<V, HE, F>::triangulateFace(uint idf)
{
    int count=0;
    Face* f = face(idf);
    if (f == nullptr)
        return 0;
    if (f->isTriangle())
        return 1;
    else {
        // Taking all the coordinates on vectors
        HalfEdge* firstHalfEdge = *(f->incidentHalfEdgeBegin());
        std::vector<Point3d> borderCoordinates;
        std::vector< std::vector<Point3d> > innerBorderCoordinates;
        std::map<std::pair<Vertex*, Vertex*>, HalfEdge*> verticesEdgeMap;
        std::map<std::pair<Vertex*, Vertex*>, HalfEdge*> twinsEdgeMap;
        std::map<Point3d, Vertex*> pointsVerticesMap;
        for (HalfEdge* he : f->incidentHalfEdgeIterator()){
            borderCoordinates.push_back(he->fromVertex()->coordinate());
            std::pair<Vertex*, Vertex*> pp;
            pp.first = he->fromVertex();
            pp.second = he->toVertex();
            verticesEdgeMap[pp] = he;
            pointsVerticesMap[he->fromVertex()->coordinate()] = he->fromVertex();
        }

        if (f->hasHoles()){
            innerBorderCoordinates.reserve(f->numberInnerHalfEdges());
            for (HalfEdge* he : f->innerHalfEdgeIterator()){
                std::vector<Point3d> inner;
                for (typename Face::IncidentHalfEdgeIterator heit = f->incidentHalfEdgeBegin(he); heit != f->incidentHalfEdgeEnd(); ++heit){
                    inner.push_back((*heit)->fromVertex()->coordinate());
                    std::pair<Vertex*, Vertex*> pp;
                    pp.first = (*heit)->fromVertex();
                    pp.second = (*heit)->toVertex();
                    verticesEdgeMap[pp] = *heit;
                }
                innerBorderCoordinates.push_back(inner);
            }
        }

        ///TRIANGULATION

        std::vector<std::array<Point3d, 3> > triangulation = cgal::triangulate3(f->normal(), borderCoordinates, innerBorderCoordinates);
        ///


        ///RECONSTRUCTION
        for (unsigned int i = 0; i < triangulation.size(); i++) {
            std::array<Point3d, 3> triangle = triangulation[i];

            Point3d p1 = triangle[0];
            Point3d p2 = triangle[1];
            Point3d p3 = triangle[2];

            HalfEdge* e1, *e2, *e3;
            std::pair<Vertex*, Vertex*> pp;
            bool b = false;
            pp.first = pointsVerticesMap[p1];
            pp.second = pointsVerticesMap[p2];
            if (verticesEdgeMap.find(pp) != verticesEdgeMap.end()){
                e1 = verticesEdgeMap[pp];
                if (e1 == firstHalfEdge) b = true;
            }
            else {
                e1 = addHalfEdge();
                e1->setFromVertex(pp.first);
                e1->setToVertex(pp.second);
                if (twinsEdgeMap.find(pp) == twinsEdgeMap.end()){
                    Vertex* tmp = pp.first;
                    pp.first = pp.second;
                    pp.second = tmp;
                    twinsEdgeMap[pp] = e1;
                }
                else {
                    HalfEdge* twin = twinsEdgeMap[pp];
                    twin->setTwin(e1);
                    e1->setTwin(twin);
                    twinsEdgeMap.erase(pp);
                }
            }
            pp.first = pointsVerticesMap[p2];
            pp.second = pointsVerticesMap[p3];
            if (verticesEdgeMap.find(pp) != verticesEdgeMap.end()){
                e2 = verticesEdgeMap[pp];
                if (e2 == firstHalfEdge) b = true;
            }
            else {
                e2 = addHalfEdge();
                e2->setFromVertex(pp.first);
                e2->setToVertex(pp.second);
                if (twinsEdgeMap.find(pp) == twinsEdgeMap.end()){
                    Vertex* tmp = pp.first;
                    pp.first = pp.second;
                    pp.second = tmp;
                    twinsEdgeMap[pp] = e2;
                }
                else {
                    HalfEdge* twin = twinsEdgeMap[pp];
                    twin->setTwin(e2);
                    e2->setTwin(twin);
                    twinsEdgeMap.erase(pp);
                }
            }
            pp.first = pointsVerticesMap[p3];
            pp.second = pointsVerticesMap[p1];
            if (verticesEdgeMap.find(pp) != verticesEdgeMap.end()){
                e3 = verticesEdgeMap[pp];
                if (e3 == firstHalfEdge) b = true;
            }
            else {
                e3 = addHalfEdge();
                e3->setFromVertex(pp.first);
                e3->setToVertex(pp.second);
                if (twinsEdgeMap.find(pp) == twinsEdgeMap.end()){
                    Vertex* tmp = pp.first;
                    pp.first = pp.second;
                    pp.second = tmp;
                    twinsEdgeMap[pp] = e3;
                }
                else {
                    HalfEdge* twin = twinsEdgeMap[pp];
                    twin->setTwin(e3);
                    e3->setTwin(twin);
                    twinsEdgeMap.erase(pp);
                }
            }

            Face* f;
            if (!b)
                f = addFace();
            else
                f = firstHalfEdge->face();

            e1->setNext(e2);
            e2->setNext(e3);
            e3->setNext(e1);
            e1->setPrev(e3);
            e2->setPrev(e1);
            e3->setPrev(e2);
            e1->setFace(f);
            e2->setFace(f);
            e3->setFace(f);
            f->setOuterHalfEdge(e1);
            f->setNormal(firstHalfEdge->face()->normal());
            f->setColor(firstHalfEdge->face()->color());

            ++count;
        }

    }
    return count;
}


/**
 * \~Italian
 * @brief Funzione che trasforma una Dcel composta da poligoni generici in una Dcel di triangoli.
 *
 * Per ogni faccia, ne viene creata una triangolazione. I triangoli presenti non vengono modificati.
 * Vengono tuttavia aggiornate le normali ai vertici.
 *
 * Utilizza CGAL.
 * Utilizzabile SOLAMENTE se è definita la costante letterale CGAL_DEFINED
 */
template <class V, class HE, class F>
void TemplatedDcel<V, HE, F>::triangulate()
{
    for (Face* f : faceIterator()) {
        triangulateFace(f->id());
    }
    updateVertexNormals();
}
#endif

/**
 * \~Italian
 * @brief Funzione che resetta i colori delle facce della Dcel.
 *
 * Setta ad ogni faccia un Color(128,128,128), ossia il colore grigio.
 *
 * @par Complessità:
 *      \e O(NumFaces)
 */
template <class V, class HE, class F>
void TemplatedDcel<V, HE, F>::resetFaceColors()
{
    for (Face* f: faceIterator())
        f->setColor(Color(128,128,128));
}

template <class V, class HE, class F>
bool TemplatedDcel<V, HE, F>::loadFromFile(const std::string& filename)
{
    std::string ext = filename.substr(filename.find_last_of(".") + 1);
    if(ext == "obj" || ext == "OBJ") { //obj file
		return loadFromObj(filename);
    }
    else if(ext == "ply" || ext == "PLY") { //ply file
		return loadFromPly(filename);
    }
    else if (ext == "dcel" || ext == "DCEL") {
		return loadFromDcelFile(filename);
    }
    else
        return false;
}


/**
 * \~Italian
 * @brief Funzione che carica una mesh salvta su file OBJ nella Dcel.
 *
 * Prima di caricare la mesh, viene chiamata la Dcel::reset().
 * Se, mediante il parametro regular, viene indicato che la mesh è chiusa e senza buchi (ossia
 * ogni vertice ha una \e star completa), una volta caricata la mesh, vengono anche calcolate
 * le normali ai vertici e le cardinalità.
 *
 * @param[in] filename: nome del file su cui è salvata la mesh, comprensivo di estensione
 * @param[in] regular: se true (default), indica che la mesh è chiusa e priva di buchi
 * @warning Se regular, utilizza Dcel::Vertex::ConstIncidentFaceIterator
 * @return Una stringa indicante da quanti vertici, half edge e facce è composta la mesh caricata
 */
template <class V, class HE, class F>
bool TemplatedDcel<V, HE, F>::loadFromObj(const std::string& filename)
{
    std::list<double> coords, vnorm;
    std::list<unsigned int> faces, fsizes;
	io::FileMeshMode fm;
    std::list<Color> vcolor, fcolor;

	if (loadMeshFromObj(filename, coords, faces, fm, vnorm, vcolor, fcolor, fsizes)){
        clear();
		afterLoadFile(coords, faces, fm, vnorm, vcolor, fcolor, fsizes);
        return true;
    }
    else
        return false;
}

/**
 * \~Italian
 * @brief Funzione che carica una mesh salvta su file PLY nella Dcel.
 *
 * Prima di caricare la mesh, viene chiamata la Dcel::reset().
 * Se, mediante il parametro regular, viene indicato che la mesh è chiusa e senza buchi (ossia
 * ogni vertice ha una \e star completa), una volta caricata la mesh, vengono anche calcolate
 * le normali ai vertici e le cardinalità.
 *
 * @param[in] filename: nome del file su cui è salvata la mesh, comprensivo di estensione
 * @param[in] regular: se true (default), indica che la mesh è chiusa e priva di buchi
 * @warning Se regular, utilizza Dcel::Vertex::ConstIncidentFaceIterator
 * @todo Gestione colori vertici
 * @return Una stringa indicante da quanti vertici, half edge e facce è composta la mesh caricata
 */
template <class V, class HE, class F>
bool TemplatedDcel<V, HE, F>::loadFromPly(const std::string& filename)
{
	std::list<double> coords, vnorm;
    std::list<unsigned int> faces, fsizes;
	io::FileMeshMode mode;
    std::list<Color> vcolor, fcolor;

	if (loadMeshFromPly(filename, coords, faces, mode, vnorm, vcolor, fcolor, fsizes)){
        clear();
		afterLoadFile(coords, faces, mode, vnorm, vcolor, fcolor, fsizes);
        return true;
    }
    else
		return false;


	/*io::FileMeshMode fm;

	std::vector<double> vcoords, vvnorm;
	std::vector<unsigned int> vfaces, vfsizes;
	std::vector<Color> vvcolor, vfcolor;

	if (loadMeshFromPly(filename, vcoords, vfaces, fm, vvnorm, vvcolor, vfcolor, vfsizes)){
		clear();
		std::list<double> coords(vcoords.begin(), vcoords.end()), vnorm(vvnorm.begin(), vvnorm.end());
		std::list<unsigned int> faces(vfaces.begin(), vfaces.end()), fsizes(vfsizes.begin(), vfsizes.end());
		std::list<Color> vcolor(vfcolor.begin(), vfcolor.end()), fcolor(vfcolor.begin(), vfcolor.end());

		afterLoadFile(coords, faces, fm, vnorm,vcolor, fcolor, fsizes);
		return true;
	}
	else
		return false;*/
}

template <class V, class HE, class F>
bool TemplatedDcel<V, HE, F>::loadFromDcelFile(const std::string& filename)
{
    std::ifstream myfile;
    myfile.open (filename, std::ios::in | std::ios::binary);
    if (myfile.is_open()) {
        try {
            deserialize(myfile);
        }
        catch(...){
            myfile.close();
            return false;
        }
    }
    myfile.close();
    return true;
}

template <class V, class HE, class F>
void TemplatedDcel<V, HE, F>::swap(TemplatedDcel& d)
{
    std::swap(vertices, d.vertices);
    std::swap(halfEdges, d.halfEdges);
    std::swap(faces, d.faces);
    std::swap(unusedVids, d.unusedVids);
    std::swap(unusedHeids, d.unusedHeids);
    std::swap(unusedFids, d.unusedFids);
    std::swap(nVertices, d.nVertices);
    std::swap(nHalfEdges, d.nHalfEdges);
    std::swap(nFaces, d.nFaces);
    std::swap(bBox, d.bBox);

    #ifdef NDEBUG
    std::swap(vertexCoordinates, d.vertexCoordinates);
    std::swap(vertexNormals, d.vertexNormals);
    std::swap(vertexColors, d.vertexColors);
    std::swap(faceNormals, d.faceNormals);
    std::swap(faceColors, d.faceColors);
    for (Vertex* v: vertexIterator())
        v->parent = this;
    for (HalfEdge* he: halfEdgeIterator())
        he->parent = this;
    for (Face* f: faceIterator())
        f->parent = this;
    for (Vertex* v: d.vertexIterator())
        v->parent = &d;
    for (HalfEdge* he: d.halfEdgeIterator())
        he->parent = &d;
    for (Face* f: d.faceIterator())
        f->parent = &d;
    #endif
}

/**
 * @brief Merges the input Dcel with this Dcel.
 * @param d: a Dcel
 */
template <class V, class HE, class F>
void TemplatedDcel<V, HE, F>::merge(const TemplatedDcel<V, HE, F>& d)
{
    std::vector<int> mapV(d.vertices.size(), -1); //map from d vertex to this vertex
    std::vector<int> mapHE(d.halfEdges.size(), -1); //map from d halfEdge to this halfEdge
    std::vector<int> mapF(d.faces.size(), -1); //map from d face to this face

    for (const Vertex* v : d.vertexIterator()) {
        Vertex* nv = addVertex(v->coordinate(), v->normal(), v->color());
        nv->setFlag(v->flag());
        nv->setCardinality(v->cardinality());
        mapV[v->id()] = nv->id();
    }

    for (const HalfEdge* he : d.halfEdgeIterator()) {
        HalfEdge* nhe = addHalfEdge();
        nhe->setFlag(he->flag());
        mapHE[he->id()] = nhe->id();
    }

    for (const Face* f : d.faceIterator()) {
        Face* nf = addFace(f->normal(), f->color());
        nf->setFlag(f->flag());
        nf->setArea(f->area());
        mapF[f->id()] = nf->id();
    }

    for (uint vid = 0; vid < mapV.size(); ++vid) {
        int nvid = mapV[vid];
        if (nvid >= 0) {
            const HalfEdge* he = d.vertex(vid)->incidentHalfEdge();
			if (he != nullptr)
				vertices[nvid]->setIncidentHalfEdge(halfEdges[mapHE[he->id()]]);
        }
    }

    for (uint heid = 0; heid < mapHE.size(); ++heid){
        int nheid = mapHE[heid];
        if (nheid >= 0) {
            const HalfEdge* the = d.halfEdge(heid)->twin();
			if (the != nullptr)
				halfEdges[nheid]->setTwin(halfEdges[mapHE[the->id()]]);

            const HalfEdge* nhe = d.halfEdge(heid)->next();
			if (nhe != nullptr)
				halfEdges[nheid]->setNext(halfEdges[mapHE[nhe->id()]]);

            const HalfEdge* phe = d.halfEdge(heid)->prev();
			if (phe != nullptr)
				halfEdges[nheid]->setPrev(halfEdges[mapHE[phe->id()]]);

            const Vertex* fv = d.halfEdge(heid)->fromVertex();
			if (fv != nullptr)
				halfEdges[nheid]->setFromVertex(vertices[mapV[fv->id()]]);

            const Vertex* pv = d.halfEdge(heid)->toVertex();
			if (pv != nullptr)
				halfEdges[nheid]->setToVertex(vertices[mapV[pv->id()]]);

            const Face* f = d.halfEdge(heid)->face();
			if (f != nullptr)
				halfEdges[nheid]->setFace(faces[mapF[f->id()]]);
        }
    }

    for (uint fid = 0; fid < mapF.size(); ++fid) {
        int nfid = mapF[fid];
        if (nfid >= 0) {
            const HalfEdge* he = d.face(fid)->outerHalfEdge();
			if (he != nullptr)
				faces[nfid]->setOuterHalfEdge(halfEdges[mapHE[he->id()]]);

            for (const HalfEdge* ihe : d.face(fid)->innerHalfEdgeIterator()){
				if (ihe != nullptr)
					faces[nfid]->addInnerHalfEdge(halfEdges[mapHE[ihe->id()]]);
            }
        }
    }
}

/**
 * @brief Merges the input Dcel with this Dcel. At the end, the input Dcel d will be empty.
 * @param d: a rvalue reference of a Dcel
 */
template <class V, class HE, class F>
void TemplatedDcel<V, HE, F>::merge(TemplatedDcel&& d)
{
    uint nv = vertices.size();
    uint nhe = halfEdges.size();
    uint nf = faces.size();
    vertices.insert(vertices.end(), d.vertices.begin(), d.vertices.end());
    halfEdges.insert(halfEdges.end(), d.halfEdges.begin(), d.halfEdges.end());
    faces.insert(faces.end(), d.faces.begin(), d.faces.end());
    for (uint v = nv;  v < vertices.size(); ++v){
        if (vertices[v])
            vertices[v]->setId(v);
        else
            unusedVids.insert(v);
    }
    for (uint he = nhe;  he < halfEdges.size(); ++he){
        if (halfEdges[he])
            halfEdges[he]->setId(he);
        else
            unusedHeids.insert(he);
    }
    for (uint f = nf;  f < faces.size(); ++f){
        if (faces[f])
            faces[f]->setId(f);
        else
            unusedFids.insert(f);
    }
    nVertices += d.nVertices;
    nHalfEdges += d.nHalfEdges;
    nFaces += d.nFaces;

    d.vertices.clear();
    d.halfEdges.clear();
    d.faces.clear();
    d.unusedVids.clear();
    d.unusedHeids.clear();
    d.unusedFids.clear();
    d.nVertices = 0;
    d.nHalfEdges = 0;
    d.nFaces = 0;
}

template <class V, class HE, class F>
void TemplatedDcel<V, HE, F>::serialize(std::ofstream& binaryFile) const
{
    cg3::serialize("cg3Dcel", binaryFile);
    //BB
    bBox.serialize(binaryFile);
    //N
    cg3::serialize(nVertices, binaryFile);
    cg3::serialize(nHalfEdges, binaryFile);
    cg3::serialize(nFaces, binaryFile);
    //Sets
    cg3::serialize(unusedVids, binaryFile);
    cg3::serialize(unusedHeids, binaryFile);
    cg3::serialize(unusedFids, binaryFile);
    //Vertices
    for (const TemplatedDcel::Vertex* v : vertexIterator()){
        int heid = -1;
        if (v->incidentHalfEdge() != nullptr) heid = v->incidentHalfEdge()->id();

        cg3::serialize(v->id(), binaryFile);
        v->coordinate().serialize(binaryFile);
        v->normal().serialize(binaryFile);
        cg3::serialize(v->color(), binaryFile);
        cg3::serialize(heid, binaryFile);
        cg3::serialize(v->cardinality(), binaryFile);
        cg3::serialize(v->flag(), binaryFile);
    }
    //HalfEdges
    for (const HalfEdge* he : halfEdgeIterator()){
        int fv = -1; if (he->fromVertex() != nullptr) fv = he->fromVertex()->id();
        int tv = -1; if (he->toVertex() != nullptr) tv = he->toVertex()->id();
        int tw = -1; if (he->twin() != nullptr) tw = he->twin()->id();
        int prev = -1; if (he->prev() != nullptr) prev = he->prev()->id();
        int next = -1; if (he->next() != nullptr) next = he->next()->id();
        int face = -1; if (he->face() != nullptr) face = he->face()->id();

        cg3::serialize(he->id(), binaryFile);
        cg3::serialize(fv, binaryFile);
        cg3::serialize(tv, binaryFile);
        cg3::serialize(tw, binaryFile);
        cg3::serialize(prev, binaryFile);
        cg3::serialize(next, binaryFile);
        cg3::serialize(face, binaryFile);
        cg3::serialize(he->flag(), binaryFile);
    }
    //Faces
    for (const Face* f : faceIterator()){
        int ohe = -1; if (f->outerHalfEdge() != nullptr) ohe = f->outerHalfEdge()->id();
        cg3::serialize(f->id(), binaryFile);
        cg3::serialize(ohe, binaryFile);
        f->normal().serialize(binaryFile);
        cg3::serialize(f->color(), binaryFile);
        cg3::serialize(f->area(), binaryFile);
        cg3::serialize(f->flag(), binaryFile);
        cg3::serialize(f->numberInnerHalfEdges(), binaryFile);

        for (typename Face::ConstInnerHalfEdgeIterator heit = f->innerHalfEdgeBegin(); heit != f->innerHalfEdgeEnd(); ++heit){
            const HalfEdge* he = *heit;
            int idhe = -1; if (he != nullptr) idhe = he->id();
            cg3::serialize(idhe, binaryFile);
        }
    }

    //serialization of other infos contained in Vertices, Half Edges and Faces
    for (const Vertex* v: vertexIterator())
        v->serialize(binaryFile);
    for (const HalfEdge* he: halfEdgeIterator())
        he->serialize(binaryFile);
    for (const Face* f: faceIterator())
        f->serialize(binaryFile);
}

template <class V, class HE, class F>
void TemplatedDcel<V, HE, F>::deserialize(std::ifstream& binaryFile)
{
    int begin = binaryFile.tellg();
    TemplatedDcel tmp;
    try {
        std::string s;
        cg3::deserialize(s, binaryFile);

        if (s != "cg3Dcel")
            throw std::ios_base::failure("Mismatching String: " + s + " != cg3Dcel");
        //BB

        tmp.bBox.deserialize(binaryFile);
        cg3::deserialize(tmp.nVertices, binaryFile);
        cg3::deserialize(tmp.nHalfEdges, binaryFile);
        cg3::deserialize(tmp.nFaces, binaryFile);
        cg3::deserialize(tmp.unusedVids, binaryFile);
        cg3::deserialize(tmp.unusedHeids, binaryFile);
        cg3::deserialize(tmp.unusedFids, binaryFile);

        //Vertices
        tmp.vertices.resize(tmp.nVertices+tmp.unusedVids.size(), nullptr);
        #ifdef NDEBUG
		tmp.vertexCoordinates.resize(tmp.nVertices+tmp.unusedVids.size(), Point3d());
		tmp.vertexNormals.resize(tmp.nVertices+tmp.unusedVids.size(), Vec3d());
        tmp.vertexColors.resize(tmp.nVertices+tmp.unusedVids.size(), Color());
        #endif
        std::map<int, int> vert;

        for (unsigned int i = 0; i < tmp.nVertices; i++){
            int id, heid;
            Point3d coord; Vec3d norm; Color color;
            int c, f;
            cg3::deserialize(id, binaryFile);
            coord.deserialize(binaryFile);
            norm.deserialize(binaryFile);
            cg3::deserialize(color, binaryFile);
            cg3::deserialize(heid, binaryFile);
            cg3::deserialize(c, binaryFile);
            cg3::deserialize(f, binaryFile);

            Vertex* v = tmp.addVertex(id);
            v->setCardinality(c);
            v->setCoordinate(coord);
            v->setNormal(norm);
            v->setFlag(f);
            vert[id] = heid;
        }
        //HalfEdges
        tmp.halfEdges.resize(tmp.nHalfEdges+tmp.unusedHeids.size(), nullptr);
        std::map<int, std::array<int, 6> > edges;

        for (unsigned int i = 0; i < tmp.nHalfEdges; i++){
            int id, fv, tv, tw, prev, next, face, flag;
            cg3::deserialize(id, binaryFile);
            cg3::deserialize(fv, binaryFile);
            cg3::deserialize(tv, binaryFile);
            cg3::deserialize(tw, binaryFile);
            cg3::deserialize(prev, binaryFile);
            cg3::deserialize(next, binaryFile);
            cg3::deserialize(face, binaryFile);
            cg3::deserialize(flag, binaryFile);
            HalfEdge* he = tmp.addHalfEdge(id);
            he->setFlag(flag);
            edges[id] = {fv, tv, tw, prev, next, face};
        }

        //Faces
        tmp.faces.resize(tmp.nFaces+tmp.unusedFids.size(), nullptr);
        #ifdef NDEBUG
		tmp.faceNormals.resize(tmp.nFaces+tmp.unusedFids.size(), Vec3d());
        tmp.faceColors.resize(tmp.nFaces+tmp.unusedFids.size(), Color());
        #endif
        for (unsigned int i = 0; i < tmp.nFaces; i++){
            int id, ohe, /*cr, cg, cb,*/ flag, nihe;
            double /*nx, ny, nz,*/ area;
            Color color;
            Vec3d norm;
            cg3::deserialize(id, binaryFile);
            cg3::deserialize(ohe, binaryFile);
            norm.deserialize(binaryFile);
            cg3::deserialize(color, binaryFile);
            cg3::deserialize(area, binaryFile);
            cg3::deserialize(flag, binaryFile);
            cg3::deserialize(nihe, binaryFile);


            Face* f = tmp.addFace(id);
            f->setColor(color);
            f->setNormal(norm);
            f->setArea(area);
            f->setFlag(flag);
            f->setOuterHalfEdge(tmp.halfEdge(ohe));
            for (int j = 0; j < nihe; j++){
                int idhe;
                cg3::deserialize(idhe, binaryFile);
                f->addInnerHalfEdge(tmp.halfEdge(idhe));
            }
        }

        for (Vertex* v : tmp.vertexIterator()){
            v->setIncidentHalfEdge(tmp.halfEdge(vert[v->id()]));
        }
        for (HalfEdge* he : tmp.halfEdgeIterator()){
            std::array<int, 6> a = edges[he->id()];
            he->setFromVertex(tmp.vertex(a[0]));
            he->setToVertex(tmp.vertex(a[1]));
            he->setTwin(tmp.halfEdge(a[2]));
            he->setPrev(tmp.halfEdge(a[3]));
            he->setNext(tmp.halfEdge(a[4]));
            he->setFace(tmp.face(a[5]));
        }

        //deserialization of other infos contained in Vertices, Half Edges and Faces
        for (Vertex* v: tmp.vertexIterator())
            v->deserialize(binaryFile);
        for (HalfEdge* he: tmp.halfEdgeIterator())
            he->deserialize(binaryFile);
        for (Face* f: tmp.faceIterator())
            f->deserialize(binaryFile);

        *this = std::move(tmp);
    }
    catch(std::ios_base::failure& e){
        cg3::restoreFilePosition(binaryFile, begin);
        throw std::ios_base::failure(e.what() + std::string("\nFrom cg3::Dcel"));
    }
    catch(...){
        cg3::restoreFilePosition(binaryFile, begin);
        throw std::ios_base::failure("Deserialization failed of cg3::Dcel");
    }
}

/**
 * \~Italian
 * @brief Operatore di assegnamento della Dcel.
 *
 * Assegna alla Dcel this un'altra Dcel dcel.
 * Elimina la dcel precedentemente contenuta e successivamente ne fa una copia, che funziona
 * esattamente come il costruttore di copia Dcel(Dcel d):
 * crea una nuova Dcel a partire dalla Dcel passata in input, creando nuove istanze
 * di tutti i vertici, gli half edge e le facce contenute in dcel, e settando di conseguenza
 * tutte le relazioni tra essi.
 * @param[in] dcel: dcel da cui verrà creata la Dcel this
 * @return La Dcel appena assegnata
 */
template <class V, class HE, class F>
TemplatedDcel<V, HE, F>& TemplatedDcel<V, HE, F>::operator = (TemplatedDcel<V, HE, F> dcel)
{
    swap(dcel);
    return *this;
}

/*********************
 * Protected Methods *
 ********************/

/**
 * \~Italian
 * @brief Aggiunge un vertice avente l'id passato come parametro alla Dcel e ne restituisce il puntatore.
 *
 * Il Dcel::Vertex è inizializzato col costruttore vuoto, e viene settato l'id passato come parametro.
 *
 * @param[in] id: l'id del vertice che verrà creato.
 * @return Il puntatore al vertice appena inserito nella Dcel
 */
template <class V, class HE, class F>
typename TemplatedDcel<V, HE, F>::Vertex* TemplatedDcel<V, HE, F>::addVertex(int id)
{
    #ifdef NDEBUG
    Vertex* last= new Vertex((DcelData&)*this);
    #else
    Vertex* last= new Vertex();
    #endif
    last->setId(id);
    vertices[id] = last;
    return last;
}

/**
 * \~Italian
 * @brief Aggiunge un half edge avente l'id passato come parametro alla Dcel e ne restituisce il puntatore.
 *
 * Il Dcel::HalfEdge è inizializzato col costruttore vuoto, e viene settato l'id passato come parametro.
 *
 * @param[in] id: l'id dell'half edge che verrà creato.
 * @return Il puntatore all'half edge appena inserito nella Dcel
 */
template <class V, class HE, class F>
typename TemplatedDcel<V, HE, F>::HalfEdge* TemplatedDcel<V, HE, F>::addHalfEdge(int id)
{
    #ifdef NDEBUG
    HalfEdge* last = new HalfEdge(*this);
    #else
    HalfEdge* last = new HalfEdge();
    #endif
    last->setId(id);
    halfEdges[id] = last;
    return last;
}

/**
 * \~Italian
 * @brief Aggiunge una faccia avente l'id passato come parametro alla Dcel e ne restituisce il puntatore.
 *
 * La Dcel::Face è inizializzata col costruttore vuoto, e viene settato l'id passato come parametro.
 *
 * @param[in] id: l'id della faccia che verrà creata.
 * @return Il puntatore alla faccia appena inserita nella Dcel
 */
template <class V, class HE, class F>
typename TemplatedDcel<V, HE, F>::Face* TemplatedDcel<V, HE, F>::addFace(int id)
{
    #ifdef NDEBUG
    Face* last = new Face(*this);
    #else
    Face* last = new Face();
    #endif
    last->setId(id);
    faces[id] = last;
    return last;
}

/**
 * \~Italian
 * @brief Funzione che, data in ingresso una faccia avente dei buchi, restituisce una singola lista di vertici di una faccia avente dummy edge.
 * @param[in] f: faccia avente almeno un buco
 * @return Lista di vertice rappresentante una faccia senza buchi ma con dummy edge
 */
template <class V, class HE, class F>
std::vector<const V*> TemplatedDcel<V, HE, F>::makeSingleBorder(const Face* f) const
{
    std::vector< std::vector<const Vertex*> > visited;
    std::vector< std::vector<const Vertex*> > notVisited;
    std::map< std::pair<int, int>, std::pair<int, int> > links;
    std::vector<const Vertex*> tmp;
    for (typename Face::ConstIncidentHalfEdgeIterator heit = f->incidentHalfEdgeBegin(); heit != f->incidentHalfEdgeEnd(); ++heit){
        #ifdef DEBUG
        (*heit)->checkFromVertex();
        #endif
        tmp.push_back((*heit)->fromVertex());
    }
    visited.push_back(tmp);
    for (typename Face::ConstInnerHalfEdgeIterator iheit = f->innerHalfEdgeBegin(); iheit != f->innerHalfEdgeEnd(); ++iheit){
        tmp.clear();
        for (typename Face::ConstIncidentHalfEdgeIterator heit = f->incidentHalfEdgeBegin(*iheit); heit != f->incidentHalfEdgeEnd(); ++heit){
            #ifdef DEBUG
            (*heit)->checkFromVertex();
            #endif
            tmp.push_back((*heit)->fromVertex());
        }
        notVisited.push_back(tmp);
    }
    while (notVisited.size() > 0) {
        // trova la coppia di punti tra visited e not_visited più vicina
        double dist = FLT_MAX;
        int visIndex = -1;
        int notvisIndex = -1;
        int visI = -1;
        int visJ = -1;
        for (unsigned int i=0; i<visited.size(); ++i){
            std::vector<const Vertex*> tmpVisited = visited[i];
            for (unsigned int j=0; j<notVisited.size(); ++j){
                std::vector<const Vertex*> tmpNotVisited = notVisited[j];
                for (unsigned int vi = 0; vi<tmpVisited.size(); ++vi){
                    for (unsigned int vj = 0; vj<tmpNotVisited.size(); ++vj){
                        if (((tmpVisited[vi])->dist(tmpNotVisited[vj])) < dist){
                            visIndex = vi;
                            notvisIndex = vj;
                            visI = i;
                            visJ = j;
                            dist = (tmpVisited[vi])->dist(tmpNotVisited[vj]);
                        }
                    }
                }
            }
        }
        std::pair<int, int> p1;
        p1.first = visI;
        p1.second = visIndex;
        std::pair<int, int> p2;
        p2.first = (int)visited.size();
        p2.second = notvisIndex;
        visited.push_back(notVisited[visJ]);
        notVisited.erase(notVisited.begin() + visJ);
        links[p1] = p2;
        links[p2] = p1;
    }
    std::vector<const Vertex*> border;
    const Vertex* start = visited[0][0];
    border.push_back(start);
    const Vertex* v = nullptr;
    int i = 0;
    int j = 0;
    while (v != start){
        std::pair<int, int> p;
        p.first = i;
        p.second = j;
        if (links.find(p) != links.end()){
            p = links[p];
            i = p.first;
            j = p.second;
            border.push_back(visited[i][j]);
        }
        j = (j + 1) % (visited[i]).size();
        border.push_back(visited[i][j]);
        v = visited[i][j];
    }
    return border;
}

template <class V, class HE, class F>
void TemplatedDcel<V, HE, F>::toStdVectors(
		std::vector<double>& vertices,
		std::vector<double>& verticesNormals,
		std::vector<float>& verticesColors,
		std::vector<int>& faces,
		std::vector<double>& faceNormals,
		std::vector<unsigned int>& faceSizes,
		std::vector<float>& faceColors) const
{
    std::map<int, int> mapVertices;
    vertices.reserve(numberVertices()*3);
    verticesNormals.reserve(numberVertices()*3);
	verticesColors.reserve(numberVertices()*3);
    faces.reserve(numberFaces()*3);
	faceNormals.reserve(numberFaces()*3);
    faceSizes.reserve(numberFaces());
    faceColors.reserve(numberFaces()*3);

    int iv = 0;
    for (const Vertex* v : vertexIterator()){
        vertices.push_back(v->coordinate().x());
        vertices.push_back(v->coordinate().y());
        vertices.push_back(v->coordinate().z());
        verticesNormals.push_back(v->normal().x());
        verticesNormals.push_back(v->normal().y());
        verticesNormals.push_back(v->normal().z());
		verticesColors.push_back(v->color().redF());
		verticesColors.push_back(v->color().greenF());
		verticesColors.push_back(v->color().blueF());
        mapVertices[v->id()] = iv++;
    }
    for (const Face* f : faceIterator()){
        unsigned int size = 0;
        if (f->numberInnerHalfEdges() == 0) {
            for (const Vertex* v : f->incidentVertexIterator()){
                assert(mapVertices.find(v->id()) != mapVertices.end());
                faces.push_back(mapVertices[v->id()]);
                size++;
            }

        }
        else { // holes
            std::vector<const Vertex*> v = makeSingleBorder(f);
            for (unsigned int i = 0; i<v.size(); ++i) {
                assert(mapVertices.find(v[i]->id()) != mapVertices.end());
                faces.push_back(mapVertices[v[i]->id()]);
            }
            size = (unsigned int)v.size();
        }
		faceNormals.push_back(f->normal().x());
		faceNormals.push_back(f->normal().y());
		faceNormals.push_back(f->normal().z());
        faceSizes.push_back(size);
        faceColors.push_back(f->color().redF());
        faceColors.push_back(f->color().greenF());
        faceColors.push_back(f->color().blueF());
    }
}

template <class V, class HE, class F>
void TemplatedDcel<V, HE, F>::afterLoadFile(
        const std::list<double> &coords,
        const std::list<unsigned int> &faces,
		const io::FileMeshMode& fm,
        const std::list<double> &vnorm,
        const std::list<Color> &vcolor,
        const std::list<Color> &fcolor,
        const std::list<unsigned int> &fsizes)
{
    std::vector<Vertex*> vertices;

    std::map< std::pair<int,int>, HalfEdge* > edge;
    typename std::map< std::pair<int,int>, HalfEdge* >::iterator eiter;

    bool first = true;

    std::list<double>::const_iterator vnit = vnorm.begin();
    std::list<Color>::const_iterator vcit = vcolor.begin();
    for (std::list<double>::const_iterator it = coords.begin(); it != coords.end(); ){
        double x = *(it++), y = *(it++), z = *(it++);
        Point3d coord(x,y,z);
        if (first) {
            bBox.setMin(coord);
            bBox.setMax(coord);
            first = false;
        }
        bBox.min() = bBox.min().min(coord);
        bBox.max() = bBox.max().max(coord);

        Vertex* vid = addVertex(coord);

        vertices.push_back(vid);

		if (fm.hasVertexNormals()){
            Vec3d norm;
            norm.setX(*(vnit++));
            norm.setY(*(vnit++));
            norm.setZ(*(vnit++));
            vid->setNormal(norm);
        }
		if (fm.hasVertexColors()){
            vid->setColor(*(vcit++));
        }
    }

    std::list<unsigned int>::const_iterator fit = faces.begin();
    std::list<Color>::const_iterator fcit = fcolor.begin();
    for (std::list<unsigned int>::const_iterator fsit = fsizes.begin(); fsit != fsizes.end(); ++fsit){

        unsigned int thisSize = *fsit;
        std::vector<unsigned int> nid;
        nid.reserve(thisSize);
        for (unsigned int i = 0; i < thisSize; i++){
            nid.push_back(*(fit++));
        }
        nid.push_back(nid[0]);

        std::pair<int, int> p;
        HalfEdge* eid = nullptr;
        Face* fid = addFace();
        HalfEdge* prev = nullptr;
        HalfEdge* first = nullptr;

        for (unsigned int i=0; i<nid.size()-1; i++){
            eid = addHalfEdge();
            if (i==0) {
                first = eid;
                fid->setOuterHalfEdge(eid);
            }
            else {
                eid->setPrev(prev);
                prev->setNext(eid);
            }
            vertices[nid[i]]->setIncidentHalfEdge(eid);
            eid->setFromVertex(vertices[nid[i]]);
            vertices[nid[i]]->incrementCardinality();
            eid->setToVertex(vertices[nid[i+1]]);
            eid->setFace(fid);
            p.first = nid[i+1];
            p.second = nid[i];
            eiter = edge.find(p);
            if (eiter != edge.end()){
                HalfEdge* twin = edge[p];
                eid->setTwin(twin);
                twin->setTwin(eid);
                edge.erase(eiter);
            }
            else {
                p.first = nid[i];
                p.second = nid[i+1];
                edge[p] = eid;
            }
            prev = eid;
        }
        eid->setNext(first);
        first->setPrev(eid);

		if (fm.hasFaceColors()){
            Color c = *(fcit++);
            fid->setColor(c);
        }
        else
            fid->setColor(Color(128, 128, 128));

        fid->updateNormal();
        fid->updateArea();
    }

	if (! (fm.hasVertexNormals()))
        updateVertexNormals();
}

#ifdef  CG3_EIGENMESH_DEFINED
template <class V, class HE, class F>
void TemplatedDcel<V, HE, F>::copyFrom(const SimpleEigenMesh& eigenMesh)
{
    clear();

    std::vector<Vertex*> vertices;

    std::map< std::pair<int,int>, HalfEdge* > edge;
    typename std::map< std::pair<int,int>, HalfEdge* >::iterator eiter;

    bool first = true;


    for (unsigned int i = 0; i < eigenMesh.numberVertices(); i++) {

        Point3d coord = eigenMesh.vertex(i);

        if (first) {
            bBox.setMin(coord);
            bBox.setMax(coord);
            first = false;
        }

        if (coord.x() < bBox.minX()) bBox.setMinX(coord.x());
        if (coord.y() < bBox.minY()) bBox.setMinY(coord.y());
        if (coord.z() < bBox.minZ()) bBox.setMinZ(coord.z());

        if (coord.x() > bBox.maxX()) bBox.setMaxX(coord.x());
        if (coord.y() > bBox.maxY()) bBox.setMaxY(coord.y());
        if (coord.z() > bBox.maxZ()) bBox.setMaxZ(coord.z());

        Vertex* vid = addVertex(coord);

        vertices.push_back(vid);
    }

    for (unsigned int i = 0; i < eigenMesh.numberFaces(); i++) {

        std::vector<int> nid;
        Point3i ff = eigenMesh.face(i);
        nid.push_back(ff.x());
        nid.push_back(ff.y());
        nid.push_back(ff.z());
        nid.push_back(nid[0]);
        std::pair<int, int> p;
        HalfEdge* eid = nullptr;
        Face* fid = addFace();
        HalfEdge* prev = nullptr;
        HalfEdge* first = nullptr;

        for (unsigned int i=0; i<nid.size()-1; i++){
            eid = addHalfEdge();
            if (i==0) {
                first = eid;
                fid->setOuterHalfEdge(eid);
            }
            else {
                eid->setPrev(prev);
                prev->setNext(eid);
            }
            vertices[nid[i]]->setIncidentHalfEdge(eid);
            eid->setFromVertex(vertices[nid[i]]);
            vertices[nid[i]]->incrementCardinality();
            eid->setToVertex(vertices[nid[i+1]]);
            eid->setFace(fid);
            p.first = nid[i+1];
            p.second = nid[i];
            eiter = edge.find(p);
            if (eiter != edge.end()){
                HalfEdge* twin = edge[p];
                eid->setTwin(twin);
                twin->setTwin(eid);
                edge.erase(eiter);
            }
            else {
                p.first = nid[i];
                p.second = nid[i+1];
                edge[p] = eid;
            }
            prev = eid;
        }
        eid->setNext(first);
        first->setPrev(eid);

        fid->setColor(Color(128, 128, 128));

        fid->updateNormal();
        fid->updateArea();
    }
}

template <class V, class HE, class F>
void TemplatedDcel<V, HE, F>::copyFrom(const EigenMesh& eigenMesh)
{
    copyFrom((SimpleEigenMesh)eigenMesh);
    for (Face* f : faceIterator()){
        f->setColor(eigenMesh.faceColor(f->id()));
        f->setNormal(eigenMesh.faceNormal(f->id()));
    }
    for (Vertex* v : vertexIterator()){
        v->setNormal(eigenMesh.vertexNormal(v->id()));
        v->setColor(eigenMesh.vertexColor(v->id()));
    }
}
#endif // CG3_EIGENMESH_DEFINED

#ifdef CG3_CINOLIB_DEFINED
template <class V, class HE, class F>
void TemplatedDcel<V, HE, F>::copyFrom(const cinolib::Trimesh<> &trimesh)
{
    clear();

    std::vector<Vertex*> vertices;

    std::map< std::pair<int,int>, HalfEdge* > edge;
    typename std::map< std::pair<int,int>, HalfEdge* >::iterator eiter;

    bool first = true;


    for (unsigned int i = 0; i < (unsigned int)trimesh.num_verts(); i++) {

		Point3d coord(trimesh.vert(i));

        if (first) {
            bBox.setMin(coord);
            bBox.setMax(coord);
            first = false;
        }

        if (coord.x() < bBox.minX()) bBox.setMinX(coord.x());
        if (coord.y() < bBox.minY()) bBox.setMinY(coord.y());
        if (coord.z() < bBox.minZ()) bBox.setMinZ(coord.z());

        if (coord.x() > bBox.maxX()) bBox.setMaxX(coord.x());
        if (coord.y() > bBox.maxY()) bBox.setMaxY(coord.y());
        if (coord.z() > bBox.maxZ()) bBox.setMaxZ(coord.z());

        Vertex* vid = addVertex(coord);

        vertices.push_back(vid);
    }

    for (unsigned int i = 0; i < (unsigned int)trimesh.num_polys(); i++) {

        std::vector<int> nid;
		Point3i ff(trimesh.poly_vert_id(i, 0), trimesh.poly_vert_id(i, 1), trimesh.poly_vert_id(i, 2));
        nid.push_back(ff.x());
        nid.push_back(ff.y());
        nid.push_back(ff.z());
        nid.push_back(nid[0]);
        std::pair<int, int> p;
        HalfEdge* eid = nullptr;
        Face* fid = addFace();
        HalfEdge* prev = nullptr;
        HalfEdge* first = nullptr;

        for (unsigned int i=0; i<nid.size()-1; i++){
            eid = addHalfEdge();
            if (i==0) {
                first = eid;
                fid->setOuterHalfEdge(eid);
            }
            else {
                eid->setPrev(prev);
                prev->setNext(eid);
            }
            vertices[nid[i]]->setIncidentHalfEdge(eid);
            eid->setFromVertex(vertices[nid[i]]);
            vertices[nid[i]]->incrementCardinality();
            eid->setToVertex(vertices[nid[i+1]]);
            eid->setFace(fid);
            p.first = nid[i+1];
            p.second = nid[i];
            eiter = edge.find(p);
            if (eiter != edge.end()){
                HalfEdge* twin = edge[p];
                eid->setTwin(twin);
                twin->setTwin(eid);
                edge.erase(eiter);
            }
            else {
                p.first = nid[i];
                p.second = nid[i+1];
                edge[p] = eid;
            }
            prev = eid;
        }
        eid->setNext(first);
        first->setPrev(eid);

        fid->setColor(Color(128, 128, 128));

        fid->updateNormal();
        fid->updateArea();
    }
}
#endif //CG3_CINOLIB_DEFINED

template <class V, class HE, class F>
TemplatedDcel<V, HE, F> merge(const TemplatedDcel<V, HE, F>& d1, const TemplatedDcel<V, HE, F>& d2)
{
    TemplatedDcel<V, HE, F> res = d1;
    res.merge(d2);
    return res;
}

/**
 * @brief Swap function between Dcel
 * @param[in/out] d1: first Dcel that will contain the second one
 * @param[in/out] d2: second Dcel that will contain the first one
 */
template <class V, class HE, class F>
inline void swap(TemplatedDcel<V, HE, F>& d1, TemplatedDcel<V, HE, F>& d2)
{
    d1.swap(d2);
}



} //namespace cg3

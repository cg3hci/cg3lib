/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "dcel_struct.h"
#include "dcel_iterators.h"

namespace cg3 {

inline Dcel::Dcel(const char *filename) : nVertices(0), nHalfEdges(0), nFaces(0)
{
    loadFromFile(std::string(filename));
}

inline Dcel::Dcel(const std::string& filename) : nVertices(0), nHalfEdges(0), nFaces(0)
{
    loadFromFile(filename);
}

/**
 * @param[in] idVertex: id of the vertex that will be returned
 * @return The const pointer to the vertex if the id exists, nullptr otherwise
 * @par Complexity:
 *      \e O(1)
 */
inline const Dcel::Vertex* Dcel::vertex(unsigned int idVertex) const
{
    if (idVertex>= vertices.size()) return nullptr;
    return vertices[idVertex];
}

/**
 * @param[in] idHalfEdge: id of the half edge that will be returned
 * @return The const pointer to the half edge if the id exists, nullptr otherwise
 * @par Complexity:
 *      \e O(1)
 */
inline const Dcel::HalfEdge* Dcel::halfEdge(unsigned int idHalfEdge) const
{
    if (idHalfEdge>= halfEdges.size()) return nullptr;
    return halfEdges[idHalfEdge];
}

/**
 * @param[in] idFace: id of the face that will be returned
 * @return The const pointer to the face if the id exists, nullptr otherwise
 * @par Complexity:
 *      \e O(1)
 */
inline const Dcel::Face* Dcel::face(unsigned int idFace) const
{
    if (idFace>= faces.size()) return nullptr;
    return faces[idFace];
}

/**
 * @note Does not calculate the bounding box, it just return the last computed one.
 * @see updateBoundingBox()
 * @return The bounding box of the mesh after its last update
 * @par Complexity:
 *      \e O(1)
 */
inline BoundingBox Dcel::boundingBox() const
{
    return bBox;
}

/**
 * @return The number of vertices contained in the Dcel.
 */
inline unsigned int Dcel::numberVertices () const
{
    return nVertices;
}

/**
 * @return The number of half edges contained in the Dcel.
 */
inline unsigned int Dcel::numberHalfEdges () const
{
    return nHalfEdges;
}

/**
 * @return The number of faces contained in the Dcel.
 */
inline unsigned int Dcel::numberFaces () const
{
    return nFaces;
}

/**
 * @param[in] v: a pointer to a Vertex
 * @return true if the vertex belongs to this Dcel, false otherwise
 * @see vertexBelongsToThis
 */
inline bool Dcel::contains(const Dcel::Vertex* v) const
{
    return vertexBelongsToThis(v);
}

/**
 * @param[in] he: a pointer to a HalfEdge
 * @return true if the half edge belongs to this Dcel, false otherwise
 * @see halfEdgeBelongsToThis
 */
inline bool Dcel::contains(const Dcel::HalfEdge* he) const
{
    return halfEdgeBelongsToThis(he);
}

/**
 * @param[in] he: a pointer to a Face
 * @return true if the face belongs to this Dcel, false otherwise
 * @see faceBelongsToThis
 */
inline bool Dcel::contains(const Dcel::Face* f) const
{
    return  faceBelongsToThis(f);
}

/**
 * @return An iterator that points to the first vertex of the Dcel
 */
inline Dcel::ConstVertexIterator Dcel::vertexBegin() const
{
    unsigned int i = 0;
    while (i < vertices.size() && vertices[i] == nullptr) ++i;
    return ConstVertexIterator(i, vertices);
}

/**
 * @return An iterator that points after the last vertex of the Dcel
 */
inline Dcel::ConstVertexIterator Dcel::vertexEnd() const
{
    return ConstVertexIterator((unsigned int)vertices.size(), vertices);
}

/**
 * @return An iterator that points to the first half edge of the Dcel
 */
inline Dcel::ConstHalfEdgeIterator Dcel::halfEdgeBegin() const
{
    unsigned int i = 0;
    while (i < halfEdges.size() && halfEdges[i] == nullptr) ++i;
    return ConstHalfEdgeIterator(i, halfEdges);
}

/**
 * @return An iterator that points after the last half edge of the Dcel
 */
inline Dcel::ConstHalfEdgeIterator Dcel::halfEdgeEnd() const
{
    return ConstHalfEdgeIterator((unsigned int)halfEdges.size(), halfEdges);
}

/**
 * @return An iterator that points to the first face of the Dcel
 */
inline Dcel::ConstFaceIterator Dcel::faceBegin() const
{
    unsigned int i = 0;
    while (i < faces.size() && faces[i] == nullptr) ++i;
    return ConstFaceIterator(i, faces);
}

/**
 * @return An iterator that points after the last face of the Dcel
 */
inline Dcel::ConstFaceIterator Dcel::faceEnd() const
{
    return ConstFaceIterator((unsigned int)faces.size(), faces);
}

/**
 * @param[in] idVertex: id of the vertex that will be returned
 * @return The pointer to the vertex if the id exists, nullptr otherwise
 * @par Complexity:
 *      \e O(1)
 */
inline Dcel::Vertex* Dcel::vertex(unsigned int idVertex)
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
inline Dcel::HalfEdge* Dcel::halfEdge(unsigned int idHalfEdge)
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
inline Dcel::Face* Dcel::face(unsigned int idFace)
{
    if (idFace>= faces.size()) return nullptr;
    return faces[idFace];
}

/**
 * \~Italian
 * @brief Funzione che elimina il vertice puntato dall'iteratore passato in input.
 *
 * Una volta eliminato, il vertice passato in input non è più utilizzabile.
 *
 * Setta a nullptr tutti i seguenti campi se contengono un riferimento al vertice eliminato v:
 * per ogni half edge uscente he:
 * - he->fromVertex
 * - he->twin->toVertex
 *
 * @param[in] vit: l'iteratore che punta al vertice da eliminare
 * @return L'iteratore al vertice successivo nella lista dei vertici
 * @par Complessità:
 *      \e O(nIncidentHalfEdges) -> \e ~O(1)
 */
inline Dcel::VertexIterator Dcel::deleteVertex(const Dcel::VertexIterator& vit)
{
    Dcel::VertexIterator nv = vit;
    Dcel::Vertex* v = *vit;

    deleteVertex(v);
    return ++nv;
}

/**
 * \~Italian
 * @brief Funzione che elimina l'half edge puntato dall'iteratore passato in input.
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
 * @param[in] heit: l'iteratore che punta all'half edge da eliminare
 * @return L'iteratore all'half edge successivo nella lista degli half edge
 * @par Complessità:
 *      \e O(1)
 */
inline Dcel::HalfEdgeIterator Dcel::deleteHalfEdge(const Dcel::HalfEdgeIterator& heit)
{
    Dcel::HalfEdgeIterator nhe = heit;
    HalfEdge* he = *heit;

    deleteHalfEdge(he);

    return ++nhe;
}

/**
 * \~Italian
 * @brief Funzione che elimina la faccia puntata dall'iteratore passato in input.
 *
 * Una volta eliminata, la faccia passata in input non è più utilizzabile.
 *
 * Setta a nullptr tutti i seguenti campi se contengono un riferimento alla faccia eliminata f:
 * per ogni half edge incidente he:
 * - he->face
 *
 * @param[in] fit: l'iteratore che punta alla faccia da eliminare
 * @return L'iteratore alla faccia successiva nella lista delle facce
 * @par Complessità:
 *      \e O(nIncidentHalfEdges) -> \e ~O(1)
 */
inline Dcel::FaceIterator Dcel::deleteFace(const Dcel::FaceIterator& fit)
{
    Dcel::FaceIterator nf = fit;
    Dcel::Face* f = *fit;
    deleteFace(f);
    return ++nf;
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Dcel::VertexIterator
 * @return Un iteratore che punta al primo vertice della Dcel
 */
inline Dcel::VertexIterator Dcel::vertexBegin()
{
    unsigned int i = 0;
    while (i < vertices.size() && vertices[i] == nullptr) ++i;
    return VertexIterator(i, vertices);
}

/**
 * \~Italian
 * @brief Funzione di finalizzazione di Dcel::VertexIterator
 * @return Un iteratore che punta all'ultimo vertice della Dcel
 */
inline Dcel::VertexIterator Dcel::vertexEnd()
{
    return VertexIterator((unsigned int)vertices.size(), vertices);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Dcel::HalfEdgeIterator
 * @return Un iteratore che punta al primo half edge della Dcel
 */
inline Dcel::HalfEdgeIterator Dcel::halfEdgeBegin()
{
    unsigned int i = 0;
    while (i < halfEdges.size() && halfEdges[i] == nullptr) ++i;
    return HalfEdgeIterator(i, halfEdges);
}

/**
 * \~Italian
 * @brief Funzione di finalizzazione di Dcel::HalfEdgeIterator
 * @return Un iteratore che punta all'ultimo half edge della Dcel
 */
inline Dcel::HalfEdgeIterator Dcel::halfEdgeEnd()
{
    return HalfEdgeIterator((unsigned int)halfEdges.size(), halfEdges);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Dcel::FaceIterator
 * @return Un iteratore che punta alla prima faccia della Dcel
 */
inline Dcel::FaceIterator Dcel::faceBegin()
{
    unsigned int i = 0;
    while (i < faces.size() && faces[i] == nullptr) ++i;
    return FaceIterator(i, faces);
}

/**
 * \~Italian
 * @brief Funzione di finalizzazione di Dcel::FaceIterator
 * @return Un iteratore che punta all'ultima faccia della Dcel
 */
inline Dcel::FaceIterator Dcel::faceEnd()
{
    return FaceIterator((unsigned int)faces.size(), faces);
}

inline const Dcel::ConstVertexRangeBasedIterator Dcel::vertexIterator() const
{
    return ConstVertexRangeBasedIterator(this);
}

inline Dcel::VertexRangeBasedIterator Dcel::vertexIterator()
{
    return VertexRangeBasedIterator(this);
}

inline const Dcel::ConstHalfEdgeRangeBasedIterator Dcel::halfEdgeIterator() const
{
    return ConstHalfEdgeRangeBasedIterator(this);
}

inline Dcel::HalfEdgeRangeBasedIterator Dcel::halfEdgeIterator()
{
    return HalfEdgeRangeBasedIterator(this);
}

inline const Dcel::ConstFaceRangeBasedIterator Dcel::faceIterator() const
{
    return ConstFaceRangeBasedIterator(this);
}

inline Dcel::FaceRangeBasedIterator Dcel::faceIterator()
{
    return FaceRangeBasedIterator(this);
}

inline void swap(Dcel& d1, Dcel& d2)
{
    d1.swap(d2);
}

} //namespace cg3

//#endif // DCEL_INLINES_H

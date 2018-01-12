/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "dcel_struct.h"
#include "dcel_iterators.h"

namespace cg3 {

inline Dcel::Dcel(const char *filename) : nVertices(0), nHalfEdges(0), nFaces(0) {
    loadFromFile(std::string(filename));
}

inline Dcel::Dcel(const std::string& filename) : nVertices(0), nHalfEdges(0), nFaces(0){
    loadFromFile(filename);
}

/**
 * \~Italian
 * @brief Funzione che restituisce il puntatore al vertice avente l'id passato in input
 * @param[in] idVertex: id del vertice che verrà restituito
 * @return Il puntatore al vertice costante se l'id esiste all'interno della Dcel, nullptr altrimenti
 * @par Complessità:
 *      \e O(1)
 */
inline const Dcel::Vertex* Dcel::getVertex(unsigned int idVertex) const {
    if (idVertex>= vertices.size()) return nullptr;
    return vertices[idVertex];
}

/**
 * \~Italian
 * @brief Funzione che restituisce il puntatore all'half edge avente l'id passato in input
 * @param[in] idHalfEdge: id dell'half edge che verrà restituito
 * @return Il puntatore all'half edge costante se l'id esiste all'interno della Dcel, nullptr altrimenti
 * @par Complessità:
 *      \e O(1)
 */
inline const Dcel::HalfEdge* Dcel::getHalfEdge(unsigned int idHalfEdge) const {
    if (idHalfEdge>= halfEdges.size()) return nullptr;
    return halfEdges[idHalfEdge];
}

/**
 * \~Italian
 * @brief Funzione che restituisce il puntatore alla faccia avente l'id passato in input
 * @param[in] idFace: id della faccia che verrà restituito
 * @return Il puntatore alla faccia costante se l'id esiste all'interno della Dcel, nullptr altrimenti
 * @par Complessità:
 *      \e O(1)
 */
inline const Dcel::Face* Dcel::getFace(unsigned int idFace) const {
    if (idFace>= faces.size()) return nullptr;
    return faces[idFace];
}

/**
 * \~Italian
 * @brief Restituisce il bounding box della mesh contenuta nella Dcel
 * @note Non ricalcola il bounding box, restituisce solo l'ultimo bounding box calcolato o settato
 * @return Il bounding box della Dcel
 * @par Complessità:
 *      \e O(1)
 */
inline BoundingBox Dcel::getBoundingBox() const {
    return boundingBox;
}

/**
 * \~Italian
 * @brief Restituisce il numero di vertici presenti nella Dcel.
 * @return Numero di vertici.
 */
inline unsigned int Dcel::getNumberVertices () const {
    return nVertices;
}

/**
 * \~Italian
 * @brief Restituisce il numero di half edge presenti nella Dcel.
 * @return Numero di half edge.
 */
inline unsigned int Dcel::getNumberHalfEdges () const {
    return nHalfEdges;
}

/**
 * \~Italian
 * @brief Restituisce il numero di facce presenti nella Dcel.
 * @return Numero di facce.
 */
inline unsigned int Dcel::getNumberFaces () const {
    return nFaces;
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Dcel::ConstVertexIterator
 * @return Un iteratore che punta al primo vertice della Dcel
 */
inline Dcel::ConstVertexIterator Dcel::vertexBegin() const {
    unsigned int i = 0;
    while (i < vertices.size() && vertices[i] == nullptr) ++i;
    return ConstVertexIterator(i, vertices);
}

/**
 * \~Italian
 * @brief Funzione di finalizzazione di Dcel::ConstVertexIterator
 * @return Un iteratore che punta all'ultimo vertice della Dcel
 */
inline Dcel::ConstVertexIterator Dcel::vertexEnd() const {
    return ConstVertexIterator((unsigned int)vertices.size(), vertices);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Dcel::ConstHalfEdgeIterator
 * @return Un iteratore che punta al primo half edge della Dcel
 */
inline Dcel::ConstHalfEdgeIterator Dcel::halfEdgeBegin() const {
    unsigned int i = 0;
    while (i < halfEdges.size() && halfEdges[i] == nullptr) ++i;
    return ConstHalfEdgeIterator(i, halfEdges);
}

/**
 * \~Italian
 * @brief Funzione di finalizzazione di Dcel::ConstHalfEdgeIterator
 * @return Un iteratore che punta all'ultimo half edge della Dcel
 */
inline Dcel::ConstHalfEdgeIterator Dcel::halfEdgeEnd() const {
    return ConstHalfEdgeIterator((unsigned int)halfEdges.size(), halfEdges);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Dcel::ConstFaceIterator
 * @return Un iteratore che punta alla prima faccia della Dcel
 */
inline Dcel::ConstFaceIterator Dcel::faceBegin() const {
    unsigned int i = 0;
    while (i < faces.size() && faces[i] == nullptr) ++i;
    return ConstFaceIterator(i, faces);
}

/**
 * @brief Funzione di finalizzazione di Dcel::ConstFaceIterator
 * @return Un iteratore che punta all'ultima faccia della Dcel
 */
inline Dcel::ConstFaceIterator Dcel::faceEnd() const {
    return ConstFaceIterator((unsigned int)faces.size(), faces);
}

/**
 * \~Italian
 * @brief Funzione che restituisce il puntatore al vertice avente l'id passato in input
 * @param[in] idVertex: id del vertice che verrà restituito
 * @return Il puntatore al vertice se l'id esiste all'interno della Dcel, nullptr altrimenti
 * @par Complessità:
 *      \e O(1)
 */
inline Dcel::Vertex* Dcel::getVertex(unsigned int idVertex) {
    if (idVertex>= vertices.size()) return nullptr;
    return vertices[idVertex];
}

/**
 * \~Italian
 * @brief Funzione che restituisce il puntatore all'half edge avente l'id passato in input
 * @param[in] idHalfEdge: id dell'half edge che verrà restituito
 * @return Il puntatore all'half edge se l'id esiste all'interno della Dcel, nullptr altrimenti
 * @par Complessità:
 *      \e O(1)
 */
inline Dcel::HalfEdge* Dcel::getHalfEdge(unsigned int idHalfEdge) {
    if (idHalfEdge>= halfEdges.size()) return nullptr;
    return halfEdges[idHalfEdge];
}

/**
 * \~Italian
 * @brief Funzione che restituisce il puntatore alla faccia avente l'id passato in input
 * @param[in] idFace: id della faccia che verrà restituito
 * @return Il puntatore alla faccia se l'id esiste all'interno della Dcel, nullptr altrimenti
 * @par Complessità:
 *      \e O(1)
 */
inline Dcel::Face* Dcel::getFace(unsigned int idFace) {
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
inline Dcel::VertexIterator Dcel::deleteVertex(const Dcel::VertexIterator& vit) {
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
inline Dcel::HalfEdgeIterator Dcel::deleteHalfEdge(const Dcel::HalfEdgeIterator& heit) {
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
inline Dcel::FaceIterator Dcel::deleteFace(const Dcel::FaceIterator& fit) {
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
inline Dcel::VertexIterator Dcel::vertexBegin() {
    unsigned int i = 0;
    while (i < vertices.size() && vertices[i] == nullptr) ++i;
    return VertexIterator(i, vertices);
}

/**
 * \~Italian
 * @brief Funzione di finalizzazione di Dcel::VertexIterator
 * @return Un iteratore che punta all'ultimo vertice della Dcel
 */
inline Dcel::VertexIterator Dcel::vertexEnd() {
    return VertexIterator((unsigned int)vertices.size(), vertices);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Dcel::HalfEdgeIterator
 * @return Un iteratore che punta al primo half edge della Dcel
 */
inline Dcel::HalfEdgeIterator Dcel::halfEdgeBegin() {
    unsigned int i = 0;
    while (i < halfEdges.size() && halfEdges[i] == nullptr) ++i;
    return HalfEdgeIterator(i, halfEdges);
}

/**
 * \~Italian
 * @brief Funzione di finalizzazione di Dcel::HalfEdgeIterator
 * @return Un iteratore che punta all'ultimo half edge della Dcel
 */
inline Dcel::HalfEdgeIterator Dcel::halfEdgeEnd() {
    return HalfEdgeIterator((unsigned int)halfEdges.size(), halfEdges);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Dcel::FaceIterator
 * @return Un iteratore che punta alla prima faccia della Dcel
 */
inline Dcel::FaceIterator Dcel::faceBegin() {
    unsigned int i = 0;
    while (i < faces.size() && faces[i] == nullptr) ++i;
    return FaceIterator(i, faces);
}

/**
 * \~Italian
 * @brief Funzione di finalizzazione di Dcel::FaceIterator
 * @return Un iteratore che punta all'ultima faccia della Dcel
 */
inline Dcel::FaceIterator Dcel::faceEnd() {
    return FaceIterator((unsigned int)faces.size(), faces);
}

inline const Dcel::ConstVertexRangeBasedIterator Dcel::vertexIterator() const {
    return ConstVertexRangeBasedIterator(this);
}

inline Dcel::VertexRangeBasedIterator Dcel::vertexIterator() {
    return VertexRangeBasedIterator(this);
}

inline const Dcel::ConstHalfEdgeRangeBasedIterator Dcel::halfEdgeIterator() const {
    return ConstHalfEdgeRangeBasedIterator(this);
}

inline Dcel::HalfEdgeRangeBasedIterator Dcel::halfEdgeIterator() {
    return HalfEdgeRangeBasedIterator(this);
}

inline const Dcel::ConstFaceRangeBasedIterator Dcel::faceIterator() const {
    return ConstFaceRangeBasedIterator(this);
}

inline Dcel::FaceRangeBasedIterator Dcel::faceIterator() {
    return FaceRangeBasedIterator(this);
}

inline void swap(Dcel& d1, Dcel& d2) {
    d1.swap(d2);
}

}

//#endif // DCEL_INLINES_H

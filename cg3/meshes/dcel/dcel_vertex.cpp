/*
 * @author    Alessandro Muntoni (muntoni.alessandro@gmail.com)
 * @copyright Alessandro Muntoni 2016.
 */

#include "dcel_vertex_iterators.h"
#include "dcel_face.h"

namespace cg3 {

/****************
 * Constructors *
 ****************/

/**
 * \~Italian
 * @brief Costruttore di default.
 *
 * Crea un vertice con:
 * - posizione pari a (0, 0, 0);
 * - half edge incidente settato a nullptr;
 * - vettore normale pari a (0, 0, 0);
 * - cardinalità pari a 0;
 * - id pari a 0;
 * - flag pari a 0.
 */
Dcel::Vertex::Vertex(Dcel& parent) : parent(&parent), incidentHalfEdge(nullptr), cardinality(0), id(0), flag(0){
}

/**
 * \~Italian
 * @brief Distruttore vuoto.
 *
 * La classe Dcel dovrà occuparsi di eliminare tutti i riferimenti in essa contenuti (e quindi contenuti di conseguenza anche nella classe Dcel::Vertex).
 */
Dcel::Vertex::~Vertex(void) {
}

/******************
 * Public Methods *
 ******************/
/**
 * \~Italian
 * @brief Calcola e restituisce il numero di half edge (non di edge) incidenti sul vertice
 * @warning Utilizza Dcel::Vertex::ConstIncidentHalfEdgeIterator
 * @return Il numero di edge incidenti sul vertice
 * @par Complessità:
 *      \e O(Cardinality)
 */
int Dcel::Vertex::getNumberIncidentHalfEdges() const {
    int n = 0;
    ConstIncidentHalfEdgeIterator it;
    for (it = incidentHalfEdgeBegin(); it != incidentHalfEdgeEnd(); ++it) n++;
    return n;
}

/**
 * \~Italian
 * @brief Calcola e restituisce il numero di facce incidenti sul vertice
 * @note Se un'unica faccia incide sul vertice due volte, questa verrà contata due volte
 * @warning Utilizza Dcel::Vertex::ConstIncidentFaceIterator
 * @return Il numero di facce incidenti sul vertice
 * @par Complessità:
 *      \e O(Cardinality)
 */
int Dcel::Vertex::getNumberIncidentFaces() const {
    int n = 0;
    ConstIncidentFaceIterator it;
    for (it = incidentFaceBegin(); it != incidentFaceEnd(); ++it) n++;
    return n;
}

/**
 * \~Italian
 * @brief Calcola e restituisce il numero di vertici adiacenti al vertice
 * @warning Utilizza Dcel::Vertex::ConstAdjacentVertexIterator
 * @return Il numero di vertici adiacenti al vertice
 * @par Complessità:
 *      \e O(Cardinality)
 */
int Dcel::Vertex::getNumberAdjacentVertices() const {
    int n = 0;
    ConstAdjacentVertexIterator it;
    for (it = adjacentVertexBegin(); it != adjacentVertexEnd(); ++it) n++;
    return n;
}

/**
 * \~Italian
 * @brief Funzione che cerca e restituisce l'half edge costante condiviso dal vertice this e vertex
 *
 * Nello specifico, se viene cercato l'half edge che ha come origine il vertice this e
 * come destinazione il vertice in input vertex. Se l'half edge non viene trovato (non esiste
 * un half edge condiviso dai due vertici) viene restituito nullptr;
 *
 * @warning Utilizza Dcel::Vertex::ConstOutgoingHalfEdgeIterator
 * @param[in] vertex: vertice con cui viene cercato l'half edge condiviso
 * @return l'half edge condiviso se esiste, nullptr altrimenti
 * @par Complessità:
 *      \e O(Cardinality)
 */
const Dcel::HalfEdge* Dcel::Vertex::findSharedHalfEdge(const Dcel::Vertex* vertex) const {
    ConstOutgoingHalfEdgeIterator he;
    for (he = outgoingHalfEdgeBegin(); he != outgoingHalfEdgeEnd(); ++he){
        if ((*he)->getToVertex() == vertex) return *he;
    }
    return nullptr;
}

/**
 * \~Italian
 * @brief Funzione toString di un vertice
 * @return Una stringa rappresentativa del vertice
 * @todo Da aggiornare
 */
std::string Dcel::Vertex::toString() const {
    std::stringstream ss;

    ss << "ID: " << id << "; Position: " << /*coordinate.toString()*/ parent->vertexCoordinates[id].toString() << "; Normal: " << parent->vertexNormals[id].toString()
       << "; Half-Edge: " ;
    if (incidentHalfEdge == nullptr) ss << "nullptr";
    else ss << incidentHalfEdge->getId();
    ss << "; Card:" << cardinality << ".";

    std::string s1 = ss.str();
    return s1;
}

/**
 * \~Italian
 * @brief Ricalcola e restituisce la normale al vertice, e aggiorna la cardinalità del vertice
 * @warning Utilizza Dcel::Vertex::ConstIncidentFaceIterator
 * @return La normale al vertice appena calcolata
 * @par Complessità:
 *      \e O(Cardinality)
 */
Vec3 Dcel::Vertex::updateNormal() {
    parent->vertexNormals[id].set(0,0,0);
    unsigned int n = 0;
    ConstIncidentFaceIterator f;
    for (f = incidentFaceBegin(); f != incidentFaceEnd(); ++f) {
        parent->vertexNormals[id] += (*f)->getNormal();
        n++;
    }
    parent->vertexNormals[id] /= n;
    cardinality = n;
    return parent->vertexNormals[id];
}

/**
 * \~Italian
 * @brief Ricalcola e restituisce la cardinalità del vertice, ossia il numero di \b edge (non half edge!) incidenti
 * @warning Utilizza Dcel::Vertex::ConstOutgoingHalfEdgeIterator
 * @return La cardinalità del vertice appena calcolata
 * @par Complessità:
 *      \e O(Cardinality)
 */
unsigned int Dcel::Vertex::updateCardinality() {
    unsigned int c = 0;
    ConstOutgoingHalfEdgeIterator heit;
    for (heit = outgoingHalfEdgeBegin(); heit != outgoingHalfEdgeEnd(); ++heit)
        c++;
    return c;
}

/**
 * \~Italian
 * @brief Funzione che cerca e restituisce l'half edge condiviso dal vertice this e vertex
 *
 * Nello specifico, se viene cercato l'half edge che ha come origine il vertice this e
 * come destinazione il vertice in input vertex. Se l'half edge non viene trovato (non esiste
 * un half edge condiviso dai due vertici) viene restituito nullptr;
 *
 * @warning Utilizza Dcel::Vertex::OutgoingHalfEdgeIterator
 * @param[in] vertex: vertice con cui viene cercato l'half edge condiviso
 * @return l'half edge condiviso se esiste, nullptr altrimenti
 * @par Complessità:
 *      \e O(Cardinality)
 */
Dcel::HalfEdge* Dcel::Vertex::findSharedHalfEdge(const Vertex* vertex) {
    OutgoingHalfEdgeIterator he;
    for (he = this->outgoingHalfEdgeBegin(); he != this->outgoingHalfEdgeEnd(); ++he){
        if ((*he)->getToVertex() == vertex) return *he;
    }
    return nullptr;
}

}

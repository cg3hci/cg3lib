/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "dcel_vertex.h"
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
#ifdef NDEBUG
Vertex::Vertex(internal::DcelData& parent) :
    parent(&parent),
    _incidentHalfEdge(nullptr),
    _cardinality(0),
    _id(0),
    _flag(0)
{
}
#else
Vertex::Vertex() :
    _incidentHalfEdge(nullptr),
    _cardinality(0),
    _id(0),
    _flag(0)
{
}
#endif

/**
 * \~Italian
 * @brief Distruttore vuoto.
 *
 * La classe Dcel dovrà occuparsi di eliminare tutti i riferimenti in essa contenuti (e quindi contenuti di conseguenza anche nella classe Vertex).
 */
Vertex::~Vertex(void)
{
}

/******************
 * Public Methods *
 ******************/
/**
 * \~Italian
 * @brief Calcola e restituisce il numero di half edge (non di edge) incidenti sul vertice
 * @warning Utilizza Vertex::ConstIncidentHalfEdgeIterator
 * @return Il numero di edge incidenti sul vertice
 * @par Complessità:
 *      \e O(Cardinality)
 */
int Vertex::numberIncidentHalfEdges() const
{
    int n = 0;
    ConstIncidentHalfEdgeIterator it;
    for (it = incidentHalfEdgeBegin(); it != incidentHalfEdgeEnd(); ++it) n++;
    return n;
}

/**
 * \~Italian
 * @brief Calcola e restituisce il numero di facce incidenti sul vertice
 * @note Se un'unica faccia incide sul vertice due volte, questa verrà contata due volte
 * @warning Utilizza Vertex::ConstIncidentFaceIterator
 * @return Il numero di facce incidenti sul vertice
 * @par Complessità:
 *      \e O(Cardinality)
 */
int Vertex::numberIncidentFaces() const
{
    int n = 0;
    ConstIncidentFaceIterator it;
    for (it = incidentFaceBegin(); it != incidentFaceEnd(); ++it) n++;
    return n;
}

/**
 * \~Italian
 * @brief Calcola e restituisce il numero di vertici adiacenti al vertice
 * @warning Utilizza Vertex::ConstAdjacentVertexIterator
 * @return Il numero di vertici adiacenti al vertice
 * @par Complessità:
 *      \e O(Cardinality)
 */
int Vertex::numberAdjacentVertices() const
{
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
 * @warning Utilizza Vertex::ConstOutgoingHalfEdgeIterator
 * @param[in] vertex: vertice con cui viene cercato l'half edge condiviso
 * @return l'half edge condiviso se esiste, nullptr altrimenti
 * @par Complessità:
 *      \e O(Cardinality)
 */
const HalfEdge* Vertex::findSharedHalfEdge(const Vertex* vertex) const
{
    ConstOutgoingHalfEdgeIterator he;
    for (he = outgoingHalfEdgeBegin(); he != outgoingHalfEdgeEnd(); ++he){
        if ((*he)->toVertex() == vertex) return *he;
    }
    return nullptr;
}

/**
 * \~Italian
 * @brief Funzione toString di un vertice
 * @return Una stringa rappresentativa del vertice
 * @todo Da aggiornare
 */
std::string Vertex::toString() const
{
    std::stringstream ss;

    #ifdef NDEBUG
    ss << "ID: " << _id << "; Position: " << to_string(parent->vertexCoordinates[_id]) << "; Normal: " << to_string(parent->vertexNormals[_id])
    #else
    ss << "ID: " << _id << "; Position: " << to_string(_coordinate) << "; Normal: " << to_string(_normal)
    #endif
       << "; Half-Edge: " ;
    if (_incidentHalfEdge == nullptr) ss << "nullptr";
    else ss << _incidentHalfEdge->id();
    ss << "; Card:" << _cardinality << ".";

    std::string s1 = ss.str();
    return s1;
}

/**
 * \~Italian
 * @brief Ricalcola e restituisce la normale al vertice, e aggiorna la cardinalità del vertice
 * @warning Utilizza Vertex::ConstIncidentFaceIterator
 * @return La normale al vertice appena calcolata
 * @par Complessità:
 *      \e O(Cardinality)
 */
Vec3 Vertex::updateNormal()
{
    #ifdef NDEBUG
    parent->vertexNormals[_id].set(0,0,0);
    #else
    _normal.set(0,0,0);
    #endif
    unsigned int n = 0;
    ConstIncidentFaceIterator f;
    for (f = incidentFaceBegin(); f != incidentFaceEnd(); ++f) {
        #ifdef NDEBUG
        parent->vertexNormals[_id] += (*f)->normal();
        #else
        _normal += (*f)->normal();
        #endif
        n++;
    }
    #ifdef NDEBUG
    parent->vertexNormals[_id] /= n;
    #else
    _normal /= n;
    #endif
    _cardinality = n;
    #ifdef NDEBUG
    return parent->vertexNormals[_id];
    #else
    return _normal;
    #endif
}

/**
 * \~Italian
 * @brief Ricalcola e restituisce la cardinalità del vertice, ossia il numero di \b edge (non half edge!) incidenti
 * @warning Utilizza Vertex::ConstOutgoingHalfEdgeIterator
 * @return La cardinalità del vertice appena calcolata
 * @par Complessità:
 *      \e O(Cardinality)
 */
unsigned int Vertex::updateCardinality()
{
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
 * @warning Utilizza Vertex::OutgoingHalfEdgeIterator
 * @param[in] vertex: vertice con cui viene cercato l'half edge condiviso
 * @return l'half edge condiviso se esiste, nullptr altrimenti
 * @par Complessità:
 *      \e O(Cardinality)
 */
HalfEdge* Vertex::findSharedHalfEdge(const Vertex* vertex)
{
    OutgoingHalfEdgeIterator he;
    for (he = this->outgoingHalfEdgeBegin(); he != this->outgoingHalfEdgeEnd(); ++he){
        if ((*he)->toVertex() == vertex) return *he;
    }
    return nullptr;
}

void Vertex::serialize(std::ofstream& binaryFile) const
{
    CG3_SUPPRESS_WARNING(binaryFile);
}

void Vertex::deserialize(std::ifstream& binaryFile)
{
    CG3_SUPPRESS_WARNING(binaryFile);
}

}

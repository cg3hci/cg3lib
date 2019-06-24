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
CG3_INLINE Vertex::Vertex(internal::DcelData& parent) :
    parent(&parent),
    _incidentHalfEdge(nullptr),
    _cardinality(0),
    _id(0),
    _flag(0)
{
}
#else
CG3_INLINE Vertex::Vertex() :
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
CG3_INLINE Vertex::~Vertex(void)
{
}

/**
 * \~Italian
 * @brief Restirìtuisce l'id identificativo nella Dcel del vertice
 * @return L'id del vertice
 */
CG3_INLINE unsigned int Vertex::id() const
{
	return _id;
}

/**
 * \~Italian
 * @brief Restituisce il flag associato al vertice
 * @return Il flag del vertice
 */
CG3_INLINE int Vertex::flag() const
{
	return _flag;
}

/**
 * \~Italian
 * @brief Restituisce il vettore normale al vertice
 * @note Non ricalcola la normale, restituisce solo l'ultima normale calcolata o settata
 * @return La normale al vertice
 */
CG3_INLINE Vec3d Vertex::normal() const
{
	#ifdef NDEBUG
	return parent->vertexNormals[_id];
	#else
	return _normal;
	#endif
}

/**
 * \~Italian
 * @brief Restituisce le coordinate del vertice
 * @return Pointd rappresentante la posizione nello spazio del vertice
 */
CG3_INLINE const Point3d& Vertex::coordinate() const
{
	#ifdef NDEBUG
	return parent->vertexCoordinates[_id];
	#else
	return _coordinate;
	#endif
}

/**
 * \~Italian
 * @brief Restituisce il colore del vertice
 * @return Color rappresentante la posizione nello spazio del vertice
 */
CG3_INLINE Color Vertex::color() const
{
	#ifdef NDEBUG
	return parent->vertexColors[_id];
	#else
	return _color;
	#endif
}

/**
 * \~Italian
 * @brief Restituisce il numero di edge incidenti sul vertice
 * @note Non ricalcola la cardinalità, restituisce solo l'ultima cardinalità calcolata o settata
 * @return La cardinalità del vertice
 */
CG3_INLINE int  Vertex::cardinality() const
{
	return _cardinality;
}

/**
 * \~Italian
 * @brief Restituisce il puntatore l'half edge costante incidente sul vertice
 * @return L'HalfEdge incidente sul vertice
 */
CG3_INLINE const HalfEdge* Vertex::incidentHalfEdge() const
{
	return _incidentHalfEdge;
}

/**
 * \~Italian
 * @brief Calcola e restituisce la distanza tra il vertice this e il vertice in input
 * @param[in] otherVertex: vertice con cui verrà calcolata la distanza dal vertice this
 * @return La distanza tra il vertice this e otherVertex
 */
CG3_INLINE double Vertex::dist(const Vertex* otherVertex) const
{
	#ifdef NDEBUG
	return parent->vertexCoordinates[_id].dist(parent->vertexCoordinates[otherVertex->_id]);
	#else
	return this->_coordinate.dist(otherVertex->_coordinate);
	#endif
}

/**
 * \~Italian
 * @brief Restituisce true se l'incident half edge è diverso da nullptr
 */
CG3_INLINE bool Vertex::checkIncidentHalfEdge() const
{
	return _incidentHalfEdge != nullptr;
}

/**
 * \~Italian
 * @brief Setta il flag del vertice a 1
 */
CG3_INLINE void Vertex::setFlag()
{
	_flag = 1;
}

/**
 * \~Italian
 *
 * @brief Setta il flag del vertice
 * @param[in] newFlag: il valore del flag che verrà settato
 */
CG3_INLINE void Vertex::setFlag(int newFlag)
{
	_flag = newFlag;
}

/**
 * \~Italian
 * @brief Setta il flag della faccia a 0
 */
CG3_INLINE void Vertex::resetFlag()
{
	_flag = 0;
}

/**
 * \~Italian
 * @brief Setta il vettore normale al vertice
 * @param[in] newNormal: il vettore normale che verrà settato
 */
CG3_INLINE void Vertex::setNormal(const Vec3d& newNormal)
{
	#ifdef NDEBUG
	parent->vertexNormals[_id] = newNormal;
	#else
	_normal = newNormal;
	#endif
}

/**
 * \~Italian
 * @brief Setta le coordinate del vertice
 * @param[in] newCoordinate: il punto che verrà settato
 */
CG3_INLINE void Vertex::setCoordinate(const Point3d& newCoordinate)
{
	#ifdef NDEBUG
	parent->vertexCoordinates[_id] = newCoordinate;
	#else
	_coordinate = newCoordinate;
	#endif
}

/**
 * \~Italian
 * @brief Setta la cardinalità del vertice
 * @param[in] newCardinality: la cardinalitù che verrà settata
 */
CG3_INLINE void Vertex::setCardinality( int newCardinality )
{
	_cardinality = newCardinality;
}

CG3_INLINE void Vertex::setColor(const Color& c) {
	#ifdef NDEBUG
	parent->vertexColors[_id] = c;
	#else
	_color = c;
	#endif
}

/**
 * \~Italian
 * @brief Decrementa la cardinalità del vertice (se essa è maggiore di 0)
 * @return La cardinalità decrementata
 */
CG3_INLINE int Vertex::decrementCardinality()
{
	if (_cardinality > 0) --_cardinality;
	return _cardinality;
}

/**
 * \~Italian
 * @brief Incrementa la cardinalità del vertice
 * @return La cardinalità incrementata
 */
CG3_INLINE int Vertex::incrementCardinality()
{
	return ++_cardinality;
}

/**
 * \~Italian
 * @brief Restituisce il puntatore all'half edge incidente sul vertice
 * @return L'HalfEdge incidente sul vertice
 */
CG3_INLINE HalfEdge* Vertex::incidentHalfEdge()
{
	return _incidentHalfEdge;
}

/**
 * \~Italian
 * @brief Assegna un nuovo half edge incidente al vertice
 * @param[in] newIncidentHalfEdge: puntatore all'half edge incidente assegnato al vertice
 */
CG3_INLINE void Vertex::setIncidentHalfEdge(HalfEdge* newIncidentHalfEdge )
{
	_incidentHalfEdge = newIncidentHalfEdge;
}

/**
 * \~Italian
 * @brief Calcola e restituisce il numero di half edge (non di edge) incidenti sul vertice
 * @warning Utilizza Vertex::ConstIncidentHalfEdgeIterator
 * @return Il numero di edge incidenti sul vertice
 * @par Complessità:
 *      \e O(Cardinality)
 */
CG3_INLINE int Vertex::numberIncidentHalfEdges() const
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
CG3_INLINE int Vertex::numberIncidentFaces() const
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
CG3_INLINE int Vertex::numberAdjacentVertices() const
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
CG3_INLINE const HalfEdge* Vertex::findSharedHalfEdge(const Vertex* vertex) const
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
CG3_INLINE std::string Vertex::toString() const
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
CG3_INLINE Vec3d Vertex::updateNormal()
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
CG3_INLINE unsigned int Vertex::updateCardinality()
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
CG3_INLINE HalfEdge* Vertex::findSharedHalfEdge(const Vertex* vertex)
{
    OutgoingHalfEdgeIterator he;
    for (he = this->outgoingHalfEdgeBegin(); he != this->outgoingHalfEdgeEnd(); ++he){
        if ((*he)->toVertex() == vertex) return *he;
    }
    return nullptr;
}

/*******
 * Iterators
 ******/

/***
 * Vertex begin()/end()
 **/

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Vertex::ConstAdjacentVertexIterator.
 *
 * Permette di ciclare sui vertici adiacenti al vertice, partendo dal toVertex dell'incidentHalfEdge.
 *
 * @return Un iteratore che punta al toVertex dell'incidentHalfEdge
 */
CG3_INLINE Vertex::ConstAdjacentVertexIterator Vertex::adjacentVertexBegin() const
{
	assert(checkIncidentHalfEdge() && "Incident half edge is nullptr.");
	return ConstAdjacentVertexIterator(_incidentHalfEdge, _incidentHalfEdge, this);
}

/**
 * \~Italian
 * @brief Funzione di finalizzazione di Vertex::ConstAdjacentVertexIterator
 * @warning L'iteratore restituito non è un iteratore valido, e su di esso le operazioni di
 *          incremento e decremento sono inutili. Questa funzione è da utilizzarsi solamente per
 *          il \b confronto \b con \b un \b altro \b iteratore \b valido
 * @return Un iteratore di finalizzazione
 */
CG3_INLINE Vertex::ConstAdjacentVertexIterator Vertex::adjacentVertexEnd() const
{
	return ConstAdjacentVertexIterator(nullptr, nullptr, this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Vertex::ConstAdjacentVertexIterator.
 *
 * Permette di ciclare sui vertici adiacenti al vertice, partendo dal toVertex dell'half edge start.
 *
 * @param[in] start: half edge di partenza
 * @warning Se start non risulta avere il vertice this come fromoVertex, viene lanciata un'asserzione e il programma termina
 * @return Un iteratore che punta al toVertex dell'half edge start
 */
CG3_INLINE Vertex::ConstAdjacentVertexIterator Vertex::adjacentVertexBegin(const HalfEdge* start) const
{
	assert(start->fromVertex() == this && "Start half edge is not incident to iterated face.");
	return ConstAdjacentVertexIterator(start, start, this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Vertex::ConstAdjacentVertexIterator.
 *
 * Permette di ciclare sui vertici adiacenti al vertice, partendo dal toVertex dell'half edge start e fino al toVertex dell'half edge end.
 *
 * @param[in] start: half edge di partenza
 * @param[in] end: half edge di arrivo, il cui toVertex \b non \b è \b compreso
 * @warning Se start e end non risultano avere il vertice this come fromoVertex, viene lanciata un'asserzione e il programma termina
 * @return Un iteratore che punta al toVertex dell'half edge start
 */
CG3_INLINE Vertex::ConstAdjacentVertexIterator Vertex::adjacentVertexBegin(const HalfEdge* start, const HalfEdge* end) const
{
	assert(start->fromVertex() == this && "Start half edge is not incident to iterated face.");
	assert(end->fromVertex() == this && "End half edge is not incident to iterated face.");
	return ConstAdjacentVertexIterator(start, end, this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Vertex::ConstAdjacentVertexIterator.
 *
 * Permette di ciclare sui vertici adiacenti al vertice, partendo dal vertice start.\n
 * È meno efficiente rispetto a Vertex::constAdjacentVertexBegin(const HalfEdge* start).
 *
 * @param[in] start: vertice di partenza
 * @warning Se start non risulta essere adiacente al vertice this (ossia non esiste un half edge condiviso tra this e start),
 * viene lanciata un'asserzione e il programma termina
 * @warning Utilizza Vertex::ConstIncomingHalfEdgeIterator
 * @return Un iteratore che punta al vertice start
 * @par Complessità:
 *      \e O(Cardinality(start))
 */
CG3_INLINE Vertex::ConstAdjacentVertexIterator Vertex::adjacentVertexBegin(const Vertex* start) const
{
	Vertex::ConstIncomingHalfEdgeIterator heit;
	for (heit = start->incomingHalfEdgeBegin(); heit != start->incomingHalfEdgeEnd(); ++heit){
		if ((*heit)->fromVertex() == this) return ConstAdjacentVertexIterator(*heit, *heit, this);
	}
	assert (false && "Start vertex is not adjacent to iterated vertex.");
	return ConstAdjacentVertexIterator();
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Vertex::ConstAdjacentVertexIterator.
 *
 * Permette di ciclare sui vertici adiacenti al vertice, partendo dal vertice start e fino al vertice end.\n
 * È meno efficiente rispetto a Vertex::constAdjacentVertexBegin(const HalfEdge* start, const HalfEdge* end).
 *
 * @param[in] start: vertice di partenza
 * @param[in] end: vertice di arrivo, \b non \b compreso
 * @warning Se start e end non risultano essere adiacenti al vertice this (ossia non esiste un half edge condiviso tra this e start e tra this e end),
 * viene lanciata un'asserzione e il programma termina
 * @warning Utilizza Vertex::ConstIncomingHalfEdgeIterator
 * @return Un iteratore che punta al vertice start
 * @par Complessità:
 *      \e O(Cardinality(start)) + \e O(Cardinality(end))
 */
CG3_INLINE Vertex::ConstAdjacentVertexIterator Vertex::adjacentVertexBegin(const Vertex* start, const Vertex* end) const
{
	Vertex::ConstIncomingHalfEdgeIterator heit = start->incomingHalfEdgeBegin();
	while (heit != start->incomingHalfEdgeEnd() && ((*heit)->fromVertex() != this)) ++heit;
	assert ((*heit)->fromVertex() == this && "Start vertex is not adjacent to iterated vertex.");
	const HalfEdge* s = *heit;
	for (heit = end->incomingHalfEdgeBegin(); heit != end->incomingHalfEdgeEnd(); ++heit){
		if ((*heit)->fromVertex() == this) return ConstAdjacentVertexIterator(s, *heit, this);
	}
	assert (false && "End vertex is not adjacent to iterated vertex.");
	return ConstAdjacentVertexIterator();
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Vertex::ConstOutgoingHalfEdgeIterator.
 *
 * Permette di ciclare sugli half edge incidenti uscenti dal vertice, partendo dall'incidentHalfEdge.
 *
 * @return Un iteratore che punta all'incidentHalfEdge del vertice
 */
CG3_INLINE Vertex::ConstOutgoingHalfEdgeIterator Vertex::outgoingHalfEdgeBegin() const
{
	assert(checkIncidentHalfEdge() && "Incident half edge is nullptr.");
	return ConstOutgoingHalfEdgeIterator(_incidentHalfEdge, _incidentHalfEdge, this);
}

/**
 * \~Italian
 * @brief Funzione di finalizzazione di Vertex::ConstOutgoingHalfEdgeIterator
 * @warning L'iteratore restituito non è un iteratore valido, e su di esso le operazioni di
 *          incremento e decremento sono inutili. Questa funzione è da utilizzarsi solamente per
 *          il \b confronto \b con \b un \b altro \b iteratore \b valido
 * @return Un iteratore di finalizzazione
 */
CG3_INLINE Vertex::ConstOutgoingHalfEdgeIterator Vertex::outgoingHalfEdgeEnd() const
{
	return ConstOutgoingHalfEdgeIterator(nullptr, nullptr, this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Vertex::ConstOutgoingHalfEdgeIterator.
 *
 * Permette di ciclare sugli half edge incidenti uscenti dal vertice, partendo dall'half edge start.
 *
 * @param[in] start: half edge di partenza
 * @warning Se start non risulta avere il vertice this come fromVertex, viene lanciata un'asserzione e il programma termina
 * @return Un iteratore che punta all'half edge start
 */
CG3_INLINE Vertex::ConstOutgoingHalfEdgeIterator Vertex::outgoingHalfEdgeBegin(const HalfEdge* start) const
{
	assert(start->fromVertex() == this && "Start half edge is not incident to iterated face.");
	return ConstOutgoingHalfEdgeIterator(start, start, this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Vertex::ConstOutgoingHalfEdgeIterator.
 *
 * Permette di ciclare sugli half edge incidenti uscenti dal vertice, partendo dall'half edge start e fino all'half edge end.
 *
 * @param[in] start: half edge di partenza
 * @param[in] end: half edge di arrivo, che \b non \b è \b compreso
 * @warning Se start e end non risultano avere il vertice this come fromVertex, viene lanciata un'asserzione e il programma termina
 * @return Un iteratore che punta all'half edge start
 */
CG3_INLINE Vertex::ConstOutgoingHalfEdgeIterator Vertex::outgoingHalfEdgeBegin(const HalfEdge* start, const HalfEdge* end) const
{
	assert(start->fromVertex() == this && "Start half edge is not incident to iterated face.");
	assert(end->fromVertex() == this && "End half edge is not incident to iterated face.");
	return ConstOutgoingHalfEdgeIterator(start, end, this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Vertex::ConstIncomingHalfEdgeIterator.
 *
 * Permette di ciclare sugli half edge incidenti entranti nel vertice, partendo dal twin dell'incidentHalfEdge.
 *
 * @return Un iteratore che punta al twin dell'incidentHalfEdge del vertice
 */
CG3_INLINE Vertex::ConstIncomingHalfEdgeIterator Vertex::incomingHalfEdgeBegin() const
{
	assert(checkIncidentHalfEdge() && "Incident half edge is nullptr.");
	return ConstIncomingHalfEdgeIterator(_incidentHalfEdge, _incidentHalfEdge, this);
}

/**
 * \~Italian
 * @brief Funzione di finalizzazione di Vertex::ConstIncomingHalfEdgeIterator
 * @warning L'iteratore restituito non è un iteratore valido, e su di esso le operazioni di
 *          incremento e decremento sono inutili. Questa funzione è da utilizzarsi solamente per
 *          il \b confronto \b con \b un \b altro \b iteratore \b valido
 * @return Un iteratore di finalizzazione
 */
CG3_INLINE Vertex::ConstIncomingHalfEdgeIterator Vertex::incomingHalfEdgeEnd() const
{
	return ConstIncomingHalfEdgeIterator(nullptr, nullptr, this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Vertex::ConstIncomingHalfEdgeIterator.
 *
 * Permette di ciclare sugli half edge incidenti entranti nel vertice, partendo dall'half edge start.
 *
 * @param[in] start: half edge di partenza
 * @warning Se start non risulta avere il vertice this come toVertex, viene lanciata un'asserzione e il programma termina
 * @return Un iteratore che punta all'half edge start
 */
CG3_INLINE Vertex::ConstIncomingHalfEdgeIterator Vertex::incomingHalfEdgeBegin(const HalfEdge* start) const
{
	assert(start->toVertex() == this && "Start half edge is not incident to iterated face.");
	return ConstIncomingHalfEdgeIterator(start->twin(), start->twin(), this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Vertex::ConstIncomingHalfEdgeIterator.
 *
 * Permette di ciclare sugli half edge incidenti entranti nel vertice, partendo dall'half edge start e fino all'half edge end.
 *
 * @param[in] start: half edge di partenza
 * @param[in] end: half edge di arrivo, che \b non \b è \b compreso
 * @warning Se start e end non risultano avere il vertice this come toVertex, viene lanciata un'asserzione e il programma termina
 * @return Un iteratore che punta all'half edge start
 */
CG3_INLINE Vertex::ConstIncomingHalfEdgeIterator Vertex::incomingHalfEdgeBegin(const HalfEdge* start, const HalfEdge* end) const
{
	assert(start->toVertex() == this && "Start half edge is not incident to iterated face.");
	assert(end->toVertex() == this && "End half edge is not incident to iterated face.");
	return ConstIncomingHalfEdgeIterator(start->twin(), end->twin(), this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Vertex::ConstIncidentHalfEdgeIterator.
 *
 * Permette di ciclare sugli half edge incidenti, sia uscenti che entranti nel vertice, partendo dall'incidentHalfEdge.
 *
 * @return Un iteratore che punta all'incidentHalfEdge del vertice
 */
CG3_INLINE Vertex::ConstIncidentHalfEdgeIterator Vertex::incidentHalfEdgeBegin() const
{
	assert(checkIncidentHalfEdge() && "Incident half edge is nullptr.");
	return ConstIncidentHalfEdgeIterator(_incidentHalfEdge, _incidentHalfEdge, this);
}

/**
 * \~Italian
 * @brief Funzione di finalizzazione di Vertex::ConstIncidentHalfEdgeIterator
 * @warning L'iteratore restituito non è un iteratore valido, e su di esso le operazioni di
 *          incremento e decremento sono inutili. Questa funzione è da utilizzarsi solamente per
 *          il \b confronto \b con \b un \b altro \b iteratore \b valido
 * @return Un iteratore di finalizzazione
 */
CG3_INLINE Vertex::ConstIncidentHalfEdgeIterator Vertex::incidentHalfEdgeEnd() const
{
	return ConstIncidentHalfEdgeIterator(nullptr, nullptr, this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Vertex::ConstIncidentHalfEdgeIterator.
 *
 * Permette di ciclare sugli half edge incidenti uscenti e entranti nel vertice, partendo dall'half edge start.
 *
 * @param[in] start: half edge di partenza
 * @warning Se start non risulta avere il vertice this come toVertex o fromVertex, viene lanciata un'asserzione e il programma termina
 * @return Un iteratore che punta all'half edge start
 */
CG3_INLINE Vertex::ConstIncidentHalfEdgeIterator Vertex::incidentHalfEdgeBegin(const HalfEdge *start) const
{
	assert((start->fromVertex() == this || start->toVertex() == this) && "Start half edge is not incident to iterated face.");
	return ConstIncidentHalfEdgeIterator(start, start, this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Vertex::ConstIncidentHalfEdgeIterator.
 *
 * Permette di ciclare sugli half edge incidenti uscenti e entranti nel vertice, partendo dall'half edge start e fino all'half edge end.
 *
 * @param[in] start: half edge di partenza
 * @param[in] end: half edge di arrivo, che \b non \b è \b compreso
 * @warning Se start e end non risultano avere il vertice this come toVertex o fromVertex, viene lanciata un'asserzione e il programma termina
 * @return Un iteratore che punta all'half edge start
 */
CG3_INLINE Vertex::ConstIncidentHalfEdgeIterator Vertex::incidentHalfEdgeBegin(const HalfEdge *start, const HalfEdge *end) const
{
	assert((start->fromVertex() == this || start->toVertex() == this) && "Start half edge is not incident to iterated face.");
	assert((end->fromVertex() == this || end->toVertex() == this) && "End half edge is not incident to iterated face.");
	return ConstIncidentHalfEdgeIterator(start, end, this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Vertex::ConstIncidentFaceIterator.
 *
 * Permette di ciclare sulle facce incidenti sul vertice, partendo dalla faccia incidente sull'incidentHalfEdge.
 *
 * @return Un iteratore che punta alla faccia incidente sull'incidentHalfEdge del vertice
 */
CG3_INLINE Vertex::ConstIncidentFaceIterator Vertex::incidentFaceBegin() const
{
	assert(checkIncidentHalfEdge() && "Incident half edge is nullptr.");
	return ConstIncidentFaceIterator(_incidentHalfEdge, _incidentHalfEdge, this);
}

/**
 * \~Italian
 * @brief Funzione di finalizzazione di Vertex::ConstIncidentFaceIterator
 * @warning L'iteratore restituito non è un iteratore valido, e su di esso le operazioni di
 *          incremento e decremento sono inutili. Questa funzione è da utilizzarsi solamente per
 *          il \b confronto \b con \b un \b altro \b iteratore \b valido
 * @return Un iteratore di finalizzazione
 */
CG3_INLINE Vertex::ConstIncidentFaceIterator Vertex::incidentFaceEnd() const
{
	return ConstIncidentFaceIterator(nullptr, nullptr, this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Vertex::ConstIncidentFaceIterator.
 *
 * Permette di ciclare sulle facce incidenti sul vertice, partendo dalla faccia incidente sull'half edge start.
 *
 * @param[in] start: half edge di partenza
 * @warning Se start non risulta avere il vertice this come fromVertex, viene lanciata un'asserzione e il programma termina
 * @return Un iteratore che punta alla faccia incidente sull'half edge start
 */
CG3_INLINE Vertex::ConstIncidentFaceIterator Vertex::incidentFaceBegin(const HalfEdge* start) const
{
	assert(start->fromVertex() == this && "Start half edge is not incident to iterated face.");
	return ConstIncidentFaceIterator(start, start, this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Vertex::ConstIncidentFaceIterator.
 *
 * Permette di ciclare sulle facce incidenti sul vertice, partendo dalla faccia incidente sull'half edge start e fino alla faccia incidente sull'half edge end.
 *
 * @param[in] start: half edge di partenza
 * @param[in] end: half edge di arrivo, che \b non \b è \b compreso
 * @warning Se start e end non risultano avere il vertice this come fromVertex, viene lanciata un'asserzione e il programma termina
 * @return Un iteratore che punta alla faccia incidente sull'half edge start
 */
CG3_INLINE Vertex::ConstIncidentFaceIterator Vertex::incidentFaceBegin(const HalfEdge* start, const HalfEdge* end) const
{
	assert(start->fromVertex() == this && "Start half edge is not incident to iterated face.");
	assert(end->fromVertex() == this && "End half edge is not incident to iterated face.");
	return ConstIncidentFaceIterator(start, end, this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Vertex::AdjacentVertexIterator.
 *
 * Permette di ciclare sui vertici adiacenti al vertice, partendo dal toVertex dell'incidentHalfEdge.
 *
 * @return Un iteratore che punta al toVertex dell'incidentHalfEdge
 */
CG3_INLINE Vertex::AdjacentVertexIterator Vertex::adjacentVertexBegin()
{
	assert(checkIncidentHalfEdge() && "Incident half edge is nullptr.");
	return AdjacentVertexIterator(_incidentHalfEdge, _incidentHalfEdge, this);
}

/**
 * \~Italian
 * @brief Funzione di finalizzazione di Vertex::AdjacentVertexIterator
 * @warning L'iteratore restituito non è un iteratore valido, e su di esso le operazioni di
 *          incremento e decremento sono inutili. Questa funzione è da utilizzarsi solamente per
 *          il \b confronto \b con \b un \b altro \b iteratore \b valido
 * @return Un iteratore di finalizzazione
 */
CG3_INLINE Vertex::AdjacentVertexIterator Vertex::adjacentVertexEnd()
{
	return AdjacentVertexIterator(nullptr, nullptr, this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Vertex::AdjacentVertexIterator.
 *
 * Permette di ciclare sui vertici adiacenti al vertice, partendo dal toVertex dell'half edge start.
 *
 * @param[in] start: half edge di partenza
 * @warning Se start non risulta avere il vertice this come fromoVertex, viene lanciata un'asserzione e il programma termina
 * @return Un iteratore che punta al toVertex dell'half edge start
 */
CG3_INLINE Vertex::AdjacentVertexIterator Vertex::adjacentVertexBegin(HalfEdge* start)
{
	assert(start->fromVertex() == this && "Start half edge is not incident to iterated face.");
	return AdjacentVertexIterator(start, start, this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Vertex::AdjacentVertexIterator.
 *
 * Permette di ciclare sui vertici adiacenti al vertice, partendo dal toVertex dell'half edge start e fino al toVertex dell'half edge end.
 *
 * @param[in] start: half edge di partenza
 * @param[in] end: half edge di arrivo, il cui toVertex \b non \b è \b compreso
 * @warning Se start e end non risultano avere il vertice this come fromoVertex, viene lanciata un'asserzione e il programma termina
 * @return Un iteratore che punta al toVertex dell'half edge start
 */
CG3_INLINE Vertex::AdjacentVertexIterator Vertex::adjacentVertexBegin(HalfEdge* start, HalfEdge* end)
{
	assert(start->fromVertex() == this && "Start half edge is not incident to iterated face.");
	assert(end->fromVertex() == this && "End half edge is not incident to iterated face.");
	return AdjacentVertexIterator(start, end, this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Vertex::AdjacentVertexIterator.
 *
 * Permette di ciclare sui vertici adiacenti al vertice, partendo dal vertice start.\n
 * È meno efficiente rispetto a Vertex::constAdjacentVertexBegin(const HalfEdge* start).
 *
 * @param[in] start: vertice di partenza
 * @warning Se start non risulta essere adiacente al vertice this (ossia non esiste un half edge condiviso tra this e start),
 * viene lanciata un'asserzione e il programma termina
 * @warning Utilizza Vertex::ConstIncomingHalfEdgeIterator
 * @return Un iteratore che punta al vertice start
 * @par Complessità:
 *      \e O(Cardinality(start))
 */
CG3_INLINE Vertex::AdjacentVertexIterator Vertex::adjacentVertexBegin(Vertex* start)
{
	Vertex::IncomingHalfEdgeIterator heit;
	for (heit= start->incomingHalfEdgeBegin(); heit!= start->incomingHalfEdgeEnd(); ++heit){
		if ((*heit)->fromVertex() == this) return AdjacentVertexIterator(*heit, *heit, this);
	}
	assert (false && "Start vertex is not adjacent to iterated vertex.");
	return AdjacentVertexIterator();
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Vertex::AdjacentVertexIterator.
 *
 * Permette di ciclare sui vertici adiacenti al vertice, partendo dal vertice start e fino al vertice end.\n
 * È meno efficiente rispetto a Vertex::constAdjacentVertexBegin(const HalfEdge* start, const HalfEdge* end).
 *
 * @param[in] start: vertice di partenza
 * @param[in] end: vertice di arrivo, \b non \b compreso
 * @warning Se start e end non risultano essere adiacenti al vertice this (ossia non esiste un half edge condiviso tra this e start e tra this e end),
 * viene lanciata un'asserzione e il programma termina
 * @warning Utilizza Vertex::ConstIncomingHalfEdgeIterator
 * @return Un iteratore che punta al vertice start
 * @par Complessità:
 *      \e O(Cardinality(start)) + \e O(Cardinality(end))
 */
CG3_INLINE Vertex::AdjacentVertexIterator Vertex::adjacentVertexBegin(Vertex* start, Vertex* end)
{
	Vertex::IncomingHalfEdgeIterator heit = start->incomingHalfEdgeBegin();
	while (heit!= start->incomingHalfEdgeEnd() && ((*heit)->fromVertex() != this)) ++heit;
	assert ((*heit)->fromVertex() == this && "Start vertex is not adjacent to iterated vertex.");
	HalfEdge* s = *heit;
	for (heit= end->incomingHalfEdgeBegin(); heit!= end->incomingHalfEdgeEnd(); ++heit){
		if ((*heit)->fromVertex() == this) return AdjacentVertexIterator(s, *heit, this);
	}
	assert (false && "End vertex is not adjacent to iterated vertex.");
	return AdjacentVertexIterator();
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Vertex::OutgoingHalfEdgeIterator.
 *
 * Permette di ciclare sugli half edge incidenti uscenti dal vertice, partendo dall'incidentHalfEdge.
 *
 * @return Un iteratore che punta all'incidentHalfEdge del vertice
 */
CG3_INLINE Vertex::OutgoingHalfEdgeIterator Vertex::outgoingHalfEdgeBegin()
{
	assert(checkIncidentHalfEdge() && "Incident half edge is nullptr.");
	return OutgoingHalfEdgeIterator(_incidentHalfEdge, _incidentHalfEdge, this);
}

/**
 * \~Italian
 * @brief Funzione di finalizzazione di Vertex::OutgoingHalfEdgeIterator
 * @warning L'iteratore restituito non è un iteratore valido, e su di esso le operazioni di
 *          incremento e decremento sono inutili. Questa funzione è da utilizzarsi solamente per
 *          il \b confronto \b con \b un \b altro \b iteratore \b valido
 * @return Un iteratore di finalizzazione
 */
CG3_INLINE Vertex::OutgoingHalfEdgeIterator Vertex::outgoingHalfEdgeEnd()
{
	return OutgoingHalfEdgeIterator(nullptr, nullptr, this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Vertex::OutgoingHalfEdgeIterator.
 *
 * Permette di ciclare sugli half edge incidenti uscenti dal vertice, partendo dall'half edge start.
 *
 * @param[in] start: half edge di partenza
 * @warning Se start non risulta avere il vertice this come fromVertex, viene lanciata un'asserzione e il programma termina
 * @return Un iteratore che punta all'half edge start
 */
CG3_INLINE Vertex::OutgoingHalfEdgeIterator Vertex::outgoingHalfEdgeBegin(HalfEdge* start)
{
	assert(start->fromVertex() == this && "Start half edge is not incident to iterated face.");
	return OutgoingHalfEdgeIterator(start, start, this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Vertex::OutgoingHalfEdgeIterator.
 *
 * Permette di ciclare sugli half edge incidenti uscenti dal vertice, partendo dall'half edge start e fino all'half edge end.
 *
 * @param[in] start: half edge di partenza
 * @param[in] end: half edge di arrivo, che \b non \b è \b compreso
 * @warning Se start e end non risultano avere il vertice this come fromVertex, viene lanciata un'asserzione e il programma termina
 * @return Un iteratore che punta all'half edge start
 */
CG3_INLINE Vertex::OutgoingHalfEdgeIterator Vertex::outgoingHalfEdgeBegin(HalfEdge* start, HalfEdge* end)
{
	assert(start->fromVertex() == this && "Start half edge is not incident to iterated face.");
	assert(end->fromVertex() == this && "End half edge is not incident to iterated face.");
	return OutgoingHalfEdgeIterator(start, end, this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Vertex::IncomingHalfEdgeIterator.
 *
 * Permette di ciclare sugli half edge incidenti entranti nel vertice, partendo dal twin dell'incidentHalfEdge.
 *
 * @return Un iteratore che punta al twin dell'incidentHalfEdge del vertice
 */
CG3_INLINE Vertex::IncomingHalfEdgeIterator Vertex::incomingHalfEdgeBegin()
{
	assert(checkIncidentHalfEdge() && "Incident half edge is nullptr.");
	return IncomingHalfEdgeIterator(_incidentHalfEdge, _incidentHalfEdge, this);
}

/**
 * \~Italian
 * @brief Funzione di finalizzazione di Vertex::IncomingHalfEdgeIterator
 * @warning L'iteratore restituito non è un iteratore valido, e su di esso le operazioni di
 *          incremento e decremento sono inutili. Questa funzione è da utilizzarsi solamente per
 *          il \b confronto \b con \b un \b altro \b iteratore \b valido
 * @return Un iteratore di finalizzazione
 */
CG3_INLINE Vertex::IncomingHalfEdgeIterator Vertex::incomingHalfEdgeEnd()
{
	return IncomingHalfEdgeIterator(nullptr, nullptr, this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Vertex::IncomingHalfEdgeIterator.
 *
 * Permette di ciclare sugli half edge incidenti entranti nel vertice, partendo dall'half edge start.
 *
 * @param[in] start: half edge di partenza
 * @warning Se start non risulta avere il vertice this come toVertex, viene lanciata un'asserzione e il programma termina
 * @return Un iteratore che punta all'half edge start
 */
CG3_INLINE Vertex::IncomingHalfEdgeIterator Vertex::incomingHalfEdgeBegin(HalfEdge* start)
{
	assert(start->toVertex() == this && "Start half edge is not incident to iterated face.");
	return IncomingHalfEdgeIterator(start->twin(), start->twin(), this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Vertex::IncomingHalfEdgeIterator.
 *
 * Permette di ciclare sugli half edge incidenti entranti nel vertice, partendo dall'half edge start e fino all'half edge end.
 *
 * @param[in] start: half edge di partenza
 * @param[in] end: half edge di arrivo, che \b non \b è \b compreso
 * @warning Se start e end non risultano avere il vertice this come toVertex, viene lanciata un'asserzione e il programma termina
 * @return Un iteratore che punta all'half edge start
 */
CG3_INLINE Vertex::IncomingHalfEdgeIterator Vertex::incomingHalfEdgeBegin(HalfEdge* start, HalfEdge* end)
{
	assert(start->toVertex() == this && "Start half edge is not incident to iterated face.");
	assert(end->toVertex() == this && "End half edge is not incident to iterated face.");
	return IncomingHalfEdgeIterator(start->twin(), end->twin(), this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Vertex::IncidentHalfEdgeIterator.
 *
 * Permette di ciclare sugli half edge incidenti, sia uscenti che entranti nel vertice, partendo dall'incidentHalfEdge.
 *
 * @return Un iteratore che punta all'incidentHalfEdge del vertice
 */
CG3_INLINE Vertex::IncidentHalfEdgeIterator Vertex::incidentHalfEdgeBegin()
{
	assert(checkIncidentHalfEdge() && "Incident half edge is nullptr.");
	return IncidentHalfEdgeIterator(_incidentHalfEdge, _incidentHalfEdge, this);
}

/**
 * \~Italian
 * @brief Funzione di finalizzazione di Vertex::IncidentHalfEdgeIterator
 * @warning L'iteratore restituito non è un iteratore valido, e su di esso le operazioni di
 *          incremento e decremento sono inutili. Questa funzione è da utilizzarsi solamente per
 *          il \b confronto \b con \b un \b altro \b iteratore \b valido
 * @return Un iteratore di finalizzazione
 */
CG3_INLINE Vertex::IncidentHalfEdgeIterator Vertex::incidentHalfEdgeEnd()
{
	return IncidentHalfEdgeIterator(nullptr, nullptr, this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Vertex::IncidentHalfEdgeIterator.
 *
 * Permette di ciclare sugli half edge incidenti uscenti e entranti nel vertice, partendo dall'half edge start.
 *
 * @param[in] start: half edge di partenza
 * @warning Se start non risulta avere il vertice this come toVertex o fromVertex, viene lanciata un'asserzione e il programma termina
 * @return Un iteratore che punta all'half edge start
 */
CG3_INLINE Vertex::IncidentHalfEdgeIterator Vertex::incidentHalfEdgeBegin(HalfEdge* start)
{
	assert((start->fromVertex()==this || start->toVertex() == this) && "Start half edge is not incident to iterated face.");
	return IncidentHalfEdgeIterator(start, start, this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Vertex::IncidentHalfEdgeIterator.
 *
 * Permette di ciclare sugli half edge incidenti uscenti e entranti nel vertice, partendo dall'half edge start e fino all'half edge end.
 *
 * @param[in] start: half edge di partenza
 * @param[in] end: half edge di arrivo, che \b non \b è \b compreso
 * @warning Se start e end non risultano avere il vertice this come toVertex o fromVertex, viene lanciata un'asserzione e il programma termina
 * @return Un iteratore che punta all'half edge start
 */
CG3_INLINE Vertex::IncidentHalfEdgeIterator Vertex::incidentHalfEdgeBegin(HalfEdge* start, HalfEdge* end)
{
	assert((start->fromVertex()==this || start->toVertex() == this) && "Start half edge is not incident to iterated face.");
	assert((end->fromVertex()==this || end->toVertex() == this) && "End half edge is not incident to iterated face.");
	return IncidentHalfEdgeIterator(start, end, this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Vertex::IncidentFaceIterator.
 *
 * Permette di ciclare sulle facce incidenti sul vertice, partendo dalla faccia incidente sull'incidentHalfEdge.
 *
 * @return Un iteratore che punta alla faccia incidente sull'incidentHalfEdge del vertice
 */
CG3_INLINE Vertex::IncidentFaceIterator Vertex::incidentFaceBegin()
{
	//assert(checkIncidentHalfEdge() && "Incident half edge is nullptr.");
	return IncidentFaceIterator(_incidentHalfEdge, _incidentHalfEdge, this);
}

/**
 * \~Italian
 * @brief Funzione di finalizzazione di Vertex::IncidentFaceIterator
 * @warning L'iteratore restituito non è un iteratore valido, e su di esso le operazioni di
 *          incremento e decremento sono inutili. Questa funzione è da utilizzarsi solamente per
 *          il \b confronto \b con \b un \b altro \b iteratore \b valido
 * @return Un iteratore di finalizzazione
 */
CG3_INLINE Vertex::IncidentFaceIterator Vertex::incidentFaceEnd()
{
	return IncidentFaceIterator(nullptr, nullptr, this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Vertex::IncidentFaceIterator.
 *
 * Permette di ciclare sulle facce incidenti sul vertice, partendo dalla faccia incidente sull'half edge start.
 *
 * @param[in] start: half edge di partenza
 * @warning Se start non risulta avere il vertice this come fromVertex, viene lanciata un'asserzione e il programma termina
 * @return Un iteratore che punta alla faccia incidente sull'half edge start
 */
CG3_INLINE Vertex::IncidentFaceIterator Vertex::incidentFaceBegin(HalfEdge* start)
{
	assert(start->fromVertex() == this && "Start half edge is not incident to iterated face.");
	return IncidentFaceIterator(start, start, this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Vertex::IncidentFaceIterator.
 *
 * Permette di ciclare sulle facce incidenti sul vertice, partendo dalla faccia incidente sull'half edge start e fino alla faccia incidente sull'half edge end.
 *
 * @param[in] start: half edge di partenza
 * @param[in] end: half edge di arrivo, che \b non \b è \b compreso
 * @warning Se start e end non risultano avere il vertice this come fromVertex, viene lanciata un'asserzione e il programma termina
 * @return Un iteratore che punta alla faccia incidente sull'half edge start
 */
CG3_INLINE Vertex::IncidentFaceIterator Vertex::incidentFaceBegin(HalfEdge* start, HalfEdge* end)
{
	assert(start->fromVertex() == this && "Start half edge is not incident to iterated face.");
	assert(end->fromVertex() == this && "End half edge is not incident to iterated face.");
	return IncidentFaceIterator(start, end, this);
}

/*****
 * Range base iterators methods
 *****/

CG3_INLINE const Vertex::ConstAdjacentVertexRangeBasedIterator Vertex::adjacentVertexIterator() const
{
	return ConstAdjacentVertexRangeBasedIterator(this);
}

CG3_INLINE Vertex::AdjacentVertexRangeBasedIterator Vertex::adjacentVertexIterator()
{
	return AdjacentVertexRangeBasedIterator(this);
}

CG3_INLINE const Vertex::ConstOutgoingHalfEdgeRangeBasedIterator Vertex::outgoingHalfEdgeIterator() const
{
	return ConstOutgoingHalfEdgeRangeBasedIterator(this);
}

CG3_INLINE const Vertex::ConstIncomingHalfEdgeRangeBasedIterator Vertex::incomingHalfEdgeIterator() const
{
	return ConstIncomingHalfEdgeRangeBasedIterator(this);
}

CG3_INLINE const Vertex::ConstIncidentHalfEdgeRangeBasedIterator Vertex::incidentHalfEdgeIterator() const
{
	return ConstIncidentHalfEdgeRangeBasedIterator(this);
}

CG3_INLINE const Vertex::ConstIncidentFaceRangeBasedIterator Vertex::incidentFaceIterator() const
{
	return ConstIncidentFaceRangeBasedIterator(this);
}

CG3_INLINE Vertex::OutgoingHalfEdgeRangeBasedIterator Vertex::outgoingHalfEdgeIterator()
{
	return OutgoingHalfEdgeRangeBasedIterator(this);
}

CG3_INLINE Vertex::IncomingHalfEdgeRangeBasedIterator Vertex::incomingHalfEdgeIterator()
{
	return IncomingHalfEdgeRangeBasedIterator(this);
}

CG3_INLINE Vertex::IncidentHalfEdgeRangeBasedIterator Vertex::incidentHalfEdgeIterator()
{
	return IncidentHalfEdgeRangeBasedIterator(this);
}

CG3_INLINE Vertex::IncidentFaceRangeBasedIterator Vertex::incidentFaceIterator()
{
	return IncidentFaceRangeBasedIterator(this);
}

CG3_INLINE void Vertex::serialize(std::ofstream& binaryFile) const
{
    CG3_SUPPRESS_WARNING(binaryFile);
}

CG3_INLINE void Vertex::deserialize(std::ifstream& binaryFile)
{
    CG3_SUPPRESS_WARNING(binaryFile);
}

/**
 * \~Italian
 * @brief Setta l'id del vertice.
 *
 * Questa funzione dovrebbe essere chiamata solamente dalla classe Dcel.
 *
 * @param[in] id: nuovo id che verrà assegnato al vertice
 */
CG3_INLINE void Vertex::setId(unsigned int id)
{
	this->_id = id;
}

}

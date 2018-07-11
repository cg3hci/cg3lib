/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "dcel_vertex.h"
#include "dcel_vertex_iterators.h"

namespace cg3 {

/*************************
 * Public Inline Methods *
 *************************/

/**
 * \~Italian
 * @brief Restirìtuisce l'id identificativo nella Dcel del vertice
 * @return L'id del vertice
 */
inline unsigned int Dcel::Vertex::id() const
{
    return _id;
}

/**
 * \~Italian
 * @brief Restituisce il flag associato al vertice
 * @return Il flag del vertice
 */
inline int Dcel::Vertex::flag() const
{
    return _flag;
}

/**
 * \~Italian
 * @brief Restituisce il vettore normale al vertice
 * @note Non ricalcola la normale, restituisce solo l'ultima normale calcolata o settata
 * @return La normale al vertice
 */
inline Vec3 Dcel::Vertex::normal() const
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
inline const Pointd& Dcel::Vertex::coordinate() const
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
inline Color Dcel::Vertex::color() const
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
inline int  Dcel::Vertex::cardinality() const
{
    return _cardinality;
}

/**
 * \~Italian
 * @brief Restituisce il puntatore l'half edge costante incidente sul vertice
 * @return L'HalfEdge incidente sul vertice
 */
inline const Dcel::HalfEdge* Dcel::Vertex::incidentHalfEdge() const
{
    return _incidentHalfEdge;
}

/**
 * \~Italian
 * @brief Calcola e restituisce la distanza tra il vertice this e il vertice in input
 * @param[in] otherVertex: vertice con cui verrà calcolata la distanza dal vertice this
 * @return La distanza tra il vertice this e otherVertex
 */
inline double Dcel::Vertex::dist(const Vertex* otherVertex) const
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
inline bool Dcel::Vertex::checkIncidentHalfEdge() const
{
    return _incidentHalfEdge != nullptr;
}

/**
 * \~Italian
 * @brief Setta il flag del vertice a 1
 */
inline void Dcel::Vertex::setFlag()
{
    _flag = 1;
}

/**
 * \~Italian
 *
 * @brief Setta il flag del vertice
 * @param[in] newFlag: il valore del flag che verrà settato
 */
inline void Dcel::Vertex::setFlag(int newFlag)
{
    _flag = newFlag;
}

/**
 * \~Italian
 * @brief Setta il flag della faccia a 0
 */
inline void Dcel::Vertex::resetFlag()
{
    _flag = 0;
}

/**
 * \~Italian
 * @brief Setta il vettore normale al vertice
 * @param[in] newNormal: il vettore normale che verrà settato
 */
inline void Dcel::Vertex::setNormal(const Vec3& newNormal)
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
inline void Dcel::Vertex::setCoordinate(const Pointd& newCoordinate)
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
inline void Dcel::Vertex::setCardinality( int newCardinality )
{
    _cardinality = newCardinality;
}

inline void Dcel::Vertex::setColor(const Color& c) {
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
inline int Dcel::Vertex::decrementCardinality()
{
    if (_cardinality > 0) --_cardinality;
    return _cardinality;
}

/**
 * \~Italian
 * @brief Incrementa la cardinalità del vertice
 * @return La cardinalità incrementata
 */
inline int Dcel::Vertex::incrementCardinality()
{
    return ++_cardinality;
}

/**
 * \~Italian
 * @brief Restituisce il puntatore all'half edge incidente sul vertice
 * @return L'HalfEdge incidente sul vertice
 */
inline Dcel::HalfEdge* Dcel::Vertex::incidentHalfEdge()
{
    return _incidentHalfEdge;
}

/**
 * \~Italian
 * @brief Assegna un nuovo half edge incidente al vertice
 * @param[in] newIncidentHalfEdge: puntatore all'half edge incidente assegnato al vertice
 */
inline void Dcel::Vertex::setIncidentHalfEdge(HalfEdge* newIncidentHalfEdge )
{
    _incidentHalfEdge = newIncidentHalfEdge;
}

/****************************
 * Protected Inline Methods *
 ****************************/

/**
 * \~Italian
 * @brief Setta l'id del vertice.
 *
 * Questa funzione dovrebbe essere chiamata solamente dalla classe Dcel.
 *
 * @param[in] id: nuovo id che verrà assegnato al vertice
 */
inline void Dcel::Vertex::setId(unsigned int id)
{
    this->_id = id;
}

}

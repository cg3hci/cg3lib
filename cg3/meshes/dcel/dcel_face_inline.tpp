/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "dcel_face.h"

namespace cg3 {
namespace internal {

/*************************
 * Public Inline Methods *
 *************************/
/**
 * \~Italian
 * @brief Restituisce l'id identificativo nella Dcel della faccia
 * @return L'id della faccia
 */
inline unsigned int Face::id() const
{
    return _id;
}

inline const Vertex*Face::vertex1() const
{
    assert(_outerHalfEdge != nullptr && "Face's Outer HalfEdge is null.");
    return _outerHalfEdge->fromVertex();
}

inline const Vertex*Face::vertex2() const
{
    assert(_outerHalfEdge != nullptr && "Face's Outer HalfEdge is null.");
    return _outerHalfEdge->toVertex();
}

inline const Vertex*Face::vertex3() const
{
    assert(_outerHalfEdge != nullptr && "Face's Outer HalfEdge is null.");
    assert(_outerHalfEdge->next() != nullptr && "Outer HalfEdge's next is null.");
    return _outerHalfEdge->next()->toVertex();
}

/**
 * \~Italian
 * @brief Restituisce il flag associato alla faccia
 * @return Il flag della faccia
 */
inline int Face::flag() const
{
    return _flag;
}

/**
 * \~Italian
 * @brief Restituisce il vettore normale alla faccia
 * @note Non ricalcola la normale, restituisce solo l'ultima normale calcolata o settata
 * @return La normale della faccia
 */
inline Vec3 Face::normal() const
{
    #ifdef NDEBUG
    return parent->faceNormals[_id];
    #else
    return _normal;
    #endif
}

/**
 * \~Italian
 * @brief Restituisce la superficie della faccia
 * @note Non ricalcola l'area, restituisce solo l'ultima area calcolata o settata
 * @return L'area della faccia
 */
inline double Face::area() const
{
    return _area;
}

/**
 * \~Italian
 * @brief Restituisce il colore associato alla faccia
 * @return Il colore della faccia
 */
inline Color Face::color() const
{
    #ifdef NDEBUG
    return parent->faceColors[_id];
    #else
    return _color;
    #endif
}

/**
 * \~Italian
 * @brief Restituisce il puntatore all'half edge costante di bordo esterno della faccia
 * @return L'HalfEdge di bordo della faccia
 */
inline const HalfEdge* Face::outerHalfEdge() const
{
    return _outerHalfEdge;
}

/**
 * \~Italian
 * @brief Restituisce il numero di inner half edges contenuti nella faccia, ossia il numero di buchi
 * @return Il numero di HalfEdge interni della faccia
 */
inline unsigned int Face::numberInnerHalfEdges() const
{
    return (unsigned int)_innerHalfEdges.size();
}

/**
 * \~Italian
 * @brief Restituisce true se la faccia contiene buchi
 * @return True se la faccia contiene buchi, false altrimenti
 */
inline bool Face::hasHoles() const
{
    return (_innerHalfEdges.size() != 0);
}

/**
 * \~Italian
 * @brief Restituisce true se l'outer half edge non è null
 */
inline bool Face::checkOuterHalfEdge() const
{
    return _outerHalfEdge != nullptr;
}

inline Vertex*Face::vertex1()
{
    assert(_outerHalfEdge != nullptr && "Face's Outer HalfEdge is null.");
    return _outerHalfEdge->fromVertex();
}

inline Vertex*Face::vertex2()
{
    assert(_outerHalfEdge != nullptr && "Face's Outer HalfEdge is null.");
    return _outerHalfEdge->toVertex();
}

inline Vertex*Face::vertex3()
{
    assert(_outerHalfEdge != nullptr && "Face's Outer HalfEdge is null.");
    assert(_outerHalfEdge->next() != nullptr && "Outer HalfEdge's next is null.");
    return _outerHalfEdge->next()->toVertex();
}

/**
 * \~Italian
 * @brief Setta il flag della faccia a 1
 */
inline void Face::setFlag()
{
    _flag = 1;
}

/**
 * \~Italian
 * @brief Setta il flag della faccia
 * @param[in] newFlag: il valore del flag che verrà settato
 */
inline void Face::setFlag(int newFlag)
{
    _flag = newFlag;
}

/**
 * \~Italian
 * @brief Setta il flag della faccia a 0
 */
inline void Face::resetFlag()
{
    _flag = 0;
}

/**
 * \~Italian
 * @brief Setta il vettore normale della faccia
 * @param[in] newNormal: il vettore normale che verrà settato
 */
inline void Face::setNormal(const Vec3& newNormal)
{
    #ifdef NDEBUG
    parent->faceNormals[_id] = newNormal;
    #else
    _normal = newNormal;
    #endif
}

/**
 * \~Italian
 * @brief Setta la superficie della faccia
 * @param[in] newArea: il valore dell'area che verrà settato
 */
inline void Face::setArea(double newArea)
{
    _area = newArea;
}

/**
 * \~Italian
 * @brief Assegna un nuovo colore alla faccia
 * @param[in] newColor: il nuovo colore che verrà assegnato alla faccia
 */
inline void Face::setColor(const Color& newColor)
{
    #ifdef NDEBUG
    parent->faceColors[_id] = newColor;
    #else
    _color = newColor;
    #endif
}

/**
 * \~Italian
 * @brief Restituisce il puntatore all'half edge di bordo esterno della faccia
 * @return L'HalfEdge di bordo della faccia
 */
inline HalfEdge* Face::outerHalfEdge()
{
    return _outerHalfEdge;
}

/**
 * \~Italian
 * @brief Assegna un nuovo half edge di bordo esterno alla faccia
 * @param[in] newOuterHalfEdge: puntatore all'half edge di bordo esterno assegnato alla faccia
 */
inline void Face::setOuterHalfEdge(HalfEdge* newOuterHalfEdge)
{
    _outerHalfEdge = newOuterHalfEdge;
}

/**
 * \~Italian
 * @brief Aggiunge un nuovo half edge di bordo interno (ossia un buco) alla faccia
 * @param[in] newInnerHalfEdge: nuovo half edge di bordo interno aggiunto alla faccia
 */
inline void Face::addInnerHalfEdge(HalfEdge* newInnerHalfEdge)
{
    _innerHalfEdges.push_back(newInnerHalfEdge);
}

/**************************
 * Private Inline Methods *
 **************************/

/**
 * \~Italian
 * @brief Setta l'id della faccia.
 *
 * Questa funzione dovrebbe essere chiamata solamente dalla classe Dcel.
 *
 * @param[in] id: nuovo id che verrà assegnato alla faccia
 */
inline void Face::setId(unsigned int id)
{
    this->_id = id;
}

/*******
 * Iterators
 ******/

/****************************
 * Face begin()/end() *
 ****************************/

inline Face::ConstAdjacentFaceIterator Face::adjacentFaceBegin() const
{
    return ConstAdjacentFaceIterator(_outerHalfEdge, _outerHalfEdge, this);
}

inline Face::ConstAdjacentFaceIterator Face::adjacentFaceEnd() const
{
    return ConstAdjacentFaceIterator(nullptr, nullptr, this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Face::ConstInnerHalfEdgeIterator
 * @return Un iteratore che punta al primo inner half edge della faccia
 */
inline Face::ConstInnerHalfEdgeIterator Face::innerHalfEdgeBegin() const
{
    return _innerHalfEdges.begin();
}

/**
 * \~Italian
 * @brief Funzione di finalizzazione di Face::ConstInnerHalfEdgeIterator
 * @return Un iteratore che punta all'ultimo inner half edge della faccia
 */
inline Face::ConstInnerHalfEdgeIterator Face::innerHalfEdgeEnd() const
{
    return _innerHalfEdges.end();
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Face::ConstIncidentHalfEdgeIterator.
 *
 * Permette di ciclare sugli half edge incidenti alla faccia, partendo dall'outer half edge.
 *
 * @return Un iteratore che punta all'outer half edge della faccia
 */
inline Face::ConstIncidentHalfEdgeIterator Face::incidentHalfEdgeBegin() const
{
    return ConstIncidentHalfEdgeIterator(_outerHalfEdge, _outerHalfEdge, this);
}

/**
 * \~Italian
 * @brief Funzione di finalizzazione di Face::ConstIncidentHalfEdgeIterator
 * @warning L'iteratore restituito non è un iteratore valido, e su di esso le operazioni di
 *          incremento e decremento sono inutili. Questa funzione è da utilizzarsi solamente per
 *          il \b confronto \b con \b un \b altro \b iteratore \b valido
 * @return Un iteratore di finalizzazione
 */
inline Face::ConstIncidentHalfEdgeIterator Face::incidentHalfEdgeEnd() const
{
    return ConstIncidentHalfEdgeIterator(nullptr, nullptr, this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Face::ConstIncidentHalfEdgeIterator.
 *
 * Permette di ciclare sugli half edge incidenti alla faccia, partendo dall'half edge start.
 *
 * @param[in] start: half edge di partenza
 * @warning Se start non risulta essere incidente alla faccia, viene lanciata un'asserzione e il programma termina
 * @return Un iteratore che punta all'half edge start
 */
inline Face::ConstIncidentHalfEdgeIterator Face::incidentHalfEdgeBegin(const HalfEdge* start) const
{
    assert(start->face() == this && "Start half edge is not incident to iterated face.");
    return ConstIncidentHalfEdgeIterator(start, start, this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Face::ConstIncidentHalfEdgeIterator.
 *
 * Permette di ciclare sugli half edge incidenti alla faccia, partendo dall'half edge start e fino all'half edge end.
 *
 * @param[in] start: half edge di partenza
 * @param[in] end: half edge di arrivo, \b non \b compreso
 * @warning Se start e end non risultano essere incidenti alla faccia, viene lanciata un'asserzione e il programma termina
 * @return Un iteratore che punta all'half edge start
 */
inline Face::ConstIncidentHalfEdgeIterator Face::incidentHalfEdgeBegin(const HalfEdge* start, const HalfEdge* end) const
{
    assert(start->face() == this && "Start half edge is not incident to iterated face.");
    assert(end->face() == this && "End half edge is not incident to iterated face.");
    return ConstIncidentHalfEdgeIterator(start, end, this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Face::ConstIncidentVertexIterator.
 *
 * Permette di ciclare sui vertici incidenti alla faccia, partendo dal toVertex dell'outer half edge.
 *
 * @return Un iteratore che punta al toVertex dell'outer half edge della faccia
 */
inline Face::ConstIncidentVertexIterator Face::incidentVertexBegin() const
{
    return ConstIncidentVertexIterator(_outerHalfEdge, _outerHalfEdge, this);
}

/**
 * \~Italian
 * @brief Funzione di finalizzazione di Face::ConstIncidentVertexIterator
 * @warning L'iteratore restituito non è un iteratore valido, e su di esso le operazioni di
 *          incremento e decremento sono inutili. Questa funzione è da utilizzarsi solamente per
 *          il \b confronto \b con \b un \b altro \b iteratore \b valido
 * @return Un iteratore di finalizzazione
 */
inline Face::ConstIncidentVertexIterator Face::incidentVertexEnd() const
{
    return ConstIncidentVertexIterator(nullptr, nullptr, this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Face::ConstIncidentVertexIterator.
 *
 * Permette di ciclare sui vertici incidenti alla faccia, partendo dal toVertex dell'half edge start.
 *
 * @param[in] start: half edge di partenza
 * @warning Se start non risulta essere incidente alla faccia, viene lanciata un'asserzione e il programma termina
 * @return Un iteratore che punta al toVertex dell'half edge start
 */
inline Face::ConstIncidentVertexIterator Face::incidentVertexBegin(const HalfEdge* start) const
{
    assert(start->face() == this && "Start half edge is not incident to iterated face.");
    return ConstIncidentVertexIterator(start, start, this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Face::ConstIncidentVertexIterator.
 *
 * Permette di ciclare sui vertici incidenti alla faccia, partendo dal toVertex dell'half edge start e fino al toVertex dell'half edge end.
 *
 * @param[in] start: half edge di partenza
 * @param[in] end: half edge di arrivo, il cui toVertex \b non \b è \b compreso
 * @warning Se start e end non risultano essere incidenti alla faccia, viene lanciata un'asserzione e il programma termina
 * @return Un iteratore che punta al toVertex dell'half edge start
 */
inline Face::ConstIncidentVertexIterator Face::incidentVertexBegin(const HalfEdge* start, const HalfEdge* end) const
{
    assert(start->face() == this && "Start half edge is not incident to iterated face.");
    assert(end->face() == this && "End half edge is not incident to iterated face.");
    return ConstIncidentVertexIterator(start, end, this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Face::InnerHalfEdgeIterator
 * @return Un iteratore che punta al primo inner half edge della faccia
 */
inline Face::InnerHalfEdgeIterator Face::innerHalfEdgeBegin()
{
    return _innerHalfEdges.begin();
}

/**
 * \~Italian
 * @brief Funzione di finalizzazione di Face::InnerHalfEdgeIterator
 * @return Un iteratore che punta all'ultimo inner half edge della faccia
 */
inline Face::InnerHalfEdgeIterator Face::innerHalfEdgeEnd()
{
    return _innerHalfEdges.end();
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Face::IncidentHalfEdgeIterator.
 *
 * Permette di ciclare sugli half edge incidenti alla faccia, partendo dall'outer half edge.
 *
 * @return Un iteratore che punta all'outer half edge della faccia
 */
inline Face::IncidentHalfEdgeIterator Face::incidentHalfEdgeBegin()
{
    return IncidentHalfEdgeIterator(_outerHalfEdge, _outerHalfEdge, this);
}

/**
 * \~Italian
 * @brief Funzione di finalizzazione di Face::IncidentHalfEdgeIterator
 * @warning L'iteratore restituito non è un iteratore valido, e su di esso le operazioni di
 *          incremento e decremento sono inutili. Questa funzione è da utilizzarsi solamente per
 *          il \b confronto \b con \b un \b altro \b iteratore \b valido
 * @return Un iteratore di finalizzazione
 */
inline Face::IncidentHalfEdgeIterator Face::incidentHalfEdgeEnd()
{
    return IncidentHalfEdgeIterator(nullptr, nullptr, this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Face::IncidentHalfEdgeIterator.
 *
 * Permette di ciclare sugli half edge incidenti alla faccia, partendo dall'half edge start.
 *
 * @param[in] start: half edge di partenza
 * @warning Se start non risulta essere incidente alla faccia, viene lanciata un'asserzione e il programma termina
 * @return Un iteratore che punta all'half edge start
 */
inline Face::IncidentHalfEdgeIterator Face::incidentHalfEdgeBegin(HalfEdge* start)
{
    assert(start->face() == this && "Start half edge is not incident to iterated face.");
    return IncidentHalfEdgeIterator(start, start, this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Face::IncidentHalfEdgeIterator.
 *
 * Permette di ciclare sugli half edge incidenti alla faccia, partendo dall'half edge start e fino all'half edge end.
 *
 * @param[in] start: half edge di partenza
 * @param[in] end: half edge di arrivo, \b non \b compreso
 * @warning Se start e end non risultano essere incidenti alla faccia, viene lanciata un'asserzione e il programma termina
 * @return Un iteratore che punta all'half edge start
 */
inline Face::IncidentHalfEdgeIterator Face::incidentHalfEdgeBegin(HalfEdge* start, HalfEdge* end)
{
    assert(start->face() == this && "Start half edge is not incident to iterated face.");
    assert(end->face() == this && "End half edge is not incident to iterated face.");
    return IncidentHalfEdgeIterator(start, end, this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Face::IncidentVertexIterator.
 *
 * Permette di ciclare sui vertici incidenti alla faccia, partendo dal toVertex dell'outer half edge.
 *
 * @return Un iteratore che punta al toVertex dell'outer half edge della faccia
 */
inline Face::IncidentVertexIterator Face::incidentVertexBegin()
{
    return IncidentVertexIterator(_outerHalfEdge, _outerHalfEdge, this);
}

/**
 * \~Italian
 * @brief Funzione di finalizzazione di Face::IncidentVertexIterator
 * @warning L'iteratore restituito non è un iteratore valido, e su di esso le operazioni di
 *          incremento e decremento sono inutili. Questa funzione è da utilizzarsi solamente per
 *          il \b confronto \b con \b un \b altro \b iteratore \b valido
 * @return Un iteratore di finalizzazione
 */
inline Face::IncidentVertexIterator Face::incidentVertexEnd()
{
    return IncidentVertexIterator(nullptr, nullptr, this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Face::IncidentVertexIterator.
 *
 * Permette di ciclare sui vertici incidenti alla faccia, partendo dal toVertex dell'half edge start.
 *
 * @param[in] start: half edge di partenza
 * @warning Se start non risulta essere incidente alla faccia, viene lanciata un'asserzione e il programma termina
 * @return Un iteratore che punta al toVertex dell'half edge start
 */
inline Face::IncidentVertexIterator Face::incidentVertexBegin(HalfEdge* start)
{
    assert(start->face() == this && "Start half edge is not incident to iterated face.");
    return IncidentVertexIterator(start, start, this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Face::IncidentVertexIterator.
 *
 * Permette di ciclare sui vertici incidenti alla faccia, partendo dal toVertex dell'half edge start e fino al toVertex dell'half edge end.
 *
 * @param[in] start: half edge di partenza
 * @param[in] end: half edge di arrivo, il cui toVertex \b non \b è \b compreso
 * @warning Se start e end non risultano essere incidenti alla faccia, viene lanciata un'asserzione e il programma termina
 * @return Un iteratore che punta al toVertex dell'half edge start
 */
inline Face::IncidentVertexIterator Face::incidentVertexBegin(HalfEdge* start, HalfEdge* end)
{
    assert(start->face() == this && "Start half edge is not incident to iterated face.");
    assert(end->face() == this && "End half edge is not incident to iterated face.");
    return IncidentVertexIterator(start, end, this);
}

/*****
 * Range base iterators methods
 *****/

inline Face::ConstInnerHalfEdgeRangeBasedIterator Face::innerHalfEdgeIterator() const
{
    return ConstInnerHalfEdgeRangeBasedIterator(this);
}

inline Face::ConstAdjacentFaceRangeBasedIterator Face::adjacentFaceIterator() const
{
    return ConstAdjacentFaceRangeBasedIterator(this);
}

inline Face::ConstIncidentHalfEdgeRangeBasedIterator Face::incidentHalfEdgeIterator() const
{
    return ConstIncidentHalfEdgeRangeBasedIterator(this);
}

inline Face::ConstIncidentVertexRangeBasedIterator Face::incidentVertexIterator() const
{
    return ConstIncidentVertexRangeBasedIterator(this);
}

inline Face::AdjacentFaceIterator Face::adjacentFaceBegin()
{
    return AdjacentFaceIterator(_outerHalfEdge, _outerHalfEdge, this);
}

inline Face::AdjacentFaceIterator Face::adjacentFaceEnd()
{
    return AdjacentFaceIterator(nullptr, nullptr, this);
}

inline Face::InnerHalfEdgeRangeBasedIterator Face::innerHalfEdgeIterator()
{
    return InnerHalfEdgeRangeBasedIterator(this);
}

inline Face::AdjacentFaceRangeBasedIterator Face::adjacentFaceIterator()
{
    return AdjacentFaceRangeBasedIterator(this);
}

inline Face::IncidentHalfEdgeRangeBasedIterator Face::incidentHalfEdgeIterator()
{
    return IncidentHalfEdgeRangeBasedIterator(this);
}

inline Face::IncidentVertexRangeBasedIterator Face::incidentVertexIterator()
{
    return IncidentVertexRangeBasedIterator(this);
}

} //namespace cg3::internal
} //namespace cg3

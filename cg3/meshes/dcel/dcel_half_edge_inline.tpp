/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "dcel_half_edge.h"

namespace cg3 {
namespace internal {

/*************************
 * Public Inline Methods *
 *************************/

/**
 * \~Italian
 * @brief Restituisce l'id identificativo nella Dcel dell'half edge
 * @return L'id dell'a faccia'half edge
 */
inline unsigned int HalfEdge::id() const
{
    return _id;
}

/**
 * \~Italian
 * @brief Restituisce il flag associato all'a faccia'half edge
 * @return Il flag dell'half edge
 */
inline int HalfEdge::flag() const
{
    return _flag;
}

/**
 * \~Italian
 * @brief Restituisce il puntatore al vertice costante di origine dell'half edge
 * @return Il from vertex dell'half edge
 */
inline const Vertex* HalfEdge::fromVertex() const
{
    return _fromVertex;
}

/**
 * \~Italian
 * @brief Restituisce il puntatore al vertice costante di destinazione dell'half edge
 * @return Il to vertex dell'half edge
 */
inline const Vertex* HalfEdge::toVertex() const
{
    return _toVertex;
}

/**
 * \~Italian
 * @brief Restituisce puntatore all'half edge costante gemello dell'half edge
 * @return Il twin dell'half edge
 */
inline const HalfEdge* HalfEdge::twin() const
{
    return _twin;
}

/**
 * \~Italian
 * @brief Restituisce puntatore all'half edge costante precedente dell'half edge
 * @return Il prev dell'half edge
 */
inline const HalfEdge* HalfEdge::prev() const
{
    return _prev;
}

/**
 * \~Italian
 * @brief Restituisce puntatore all'half edge costante successivo dell'half edge
 * @return Il next dell'half edge
 */
inline const HalfEdge* HalfEdge::next() const
{
    return _next;
}

/**
 * \~Italian
 * @brief Restituisce puntatore alla faccia costante incidente all'half edge
 * @return La faccia incidente all'half edge
 */
inline const Face* HalfEdge::face() const
{
    return _face;
}

#ifdef DEBUG
/**
 * \~Italian
 * @brief Lancia un'asserzione se il vertice di origine è nullptr
 */
inline void HalfEdge::checkFromVertex() const
{
    if (_fromVertex == nullptr){
        std::cerr << "ALERT! Half Edge "<< _id << ": from_vertex is nullptr";
        assert(! (_fromVertex == nullptr));
    }
}

/**
 * \~Italian
 * @brief Lancia un'asserzione se il vertice di destinazione è nullptr
 */
inline void HalfEdge::checkToVertex() const
{
    if (_toVertex == nullptr){
        std::cerr << "ALERT! Half Edge "<< _id << ": to_vertex is nullptr";
        assert(! (_toVertex == nullptr));
    }
}

/**
 * \~Italian
 * @brief Lancia un'asserzione se l'half edge gemello è nullptr
 */
inline void HalfEdge::checkTwin() const
{
    if (_twin == nullptr){
        std::cerr << "ALERT! Half Edge "<< _id << ": twin is nullptr";
        assert(! (_twin == nullptr));
    }
}

/**
 * \~Italian
 * @brief Lancia un'asserzione se l'half edge precedente è nullptr
 */
inline void HalfEdge::checkPrev() const
{
    if (_prev == nullptr){
        std::cerr << "ALERT! Half Edge "<< _id << ": prev is nullptr";
        assert(! (_prev == nullptr));
    }
}

/**
 * \~Italian
 * @brief Lancia un'asserzione se l'half edge successivo è nullptr
 */
inline void HalfEdge::checkNext() const
{
    if (_next == nullptr){
        std::cerr << "ALERT! Half Edge "<< _id << ": next is nullptr";
        assert(! (_next == nullptr));
    }
}

/**
 * \~Italian
 * @brief Lancia un'asserzione se la faccia incidente è nullptr
 */
inline void HalfEdge::checkFace() const
{
    if (_face == nullptr){
        std::cerr << "ALERT! Half Edge "<< _id << ": face is nullptr";
        assert(! (_face == nullptr));
    }
}
#endif

/**
 * \~Italian
 * @brief Setta il flag dell'half edge a 1
 */
inline void HalfEdge::setFlag()
{
    _flag = 1;
}

/**
 * \~Italian
 * @brief Setta il flag dell'half edge
 * @param[in] new_flag: il valore del flag che verrà settato
 */
inline void HalfEdge::setFlag(int new_flag)
{
    _flag = new_flag;
}

/**
 * \~Italian
 * @brief Setta il flag dell'half edge a 0
 */
inline void HalfEdge::resetFlag()
{
    _flag = 0;
}

/**
 * \~Italian
 * @brief Restituisce il puntatore al vertice di origine dell'half edge
 * @return Il from vertex dell'half edge
 */
inline Vertex* HalfEdge::fromVertex()
{
    return _fromVertex;
}

/**
 * \~Italian
 * @brief Restituisce il puntatore al vertice di destinazione dell'half edge
 * @return Il to vertex dell'half edge
 */
inline Vertex* HalfEdge::toVertex()
{
    return _toVertex;
}

/**
 * \~Italian
 * @brief Restituisce puntatore all'half edge gemello dell'half edge
 * @return Il twin dell'half edge
 */
inline HalfEdge* HalfEdge::twin()
{
    return _twin;
}

/**
 * \~Italian
 * @brief Restituisce puntatore all'half edge precedente dell'half edge
 * @return Il prev dell'half edge
 */
inline HalfEdge* HalfEdge::prev()
{
    return _prev;
}

/**
 * \~Italian
 * @brief Restituisce puntatore all'half edge successivo dell'half edge
 * @return Il next dell'half edge
 */
inline HalfEdge* HalfEdge::next()
{
    return _next;
}

/**
 * \~Italian
 * @brief Restituisce puntatore alla faccia incidente all'half edge
 * @return La faccia incidente all'half edge
 */
inline Face* HalfEdge::face()
{
    return _face;
}

/**
 * \~Italian
 * @brief Setta il vertice di origine
 * @param[in] newFromVertex: riferimento al from vertex che verrà assegnato all'half edge
 */
inline void HalfEdge::setFromVertex(Vertex* newFromVertex)
{
    _fromVertex = newFromVertex;
}

/**
 * \~Italian
 * @brief Setta il vertice di destinazione
 * @param[in] newToVertex: riferimento al to vertex che verrà assegnato all'half edge
 */
inline void HalfEdge::setToVertex(Vertex* newToVertex)
{
    _toVertex = newToVertex;
}

/**
 * \~Italian
 * @brief Setta l'half edge gemello
 * @param[in] newTwin: riferimento al twin che verrà assegnato all'half edge
 */
inline void HalfEdge::setTwin(HalfEdge* newTwin)
{
    _twin = newTwin;
}

/**
 * \~Italian
 * @brief Setta l'half edge precedente
 * @param[in] newPrev: riferimento al prev che verrà assegnato all'half edge
 */
inline void HalfEdge::setPrev(HalfEdge* newPrev)
{
    _prev = newPrev;
}

/**
 * \~Italian
 * @brief Setta l'half edge successivo
 * @param[in] newNext: riferimento al next che verrà assegnato all'half edge
 */
inline void HalfEdge::setNext(HalfEdge* newNext)
{
    _next = newNext;
}

/**
 * \~Italian
 * @brief Setta la faccia incidente
 * @param[in] newFace:riferimento alla faccia che verrà assegnato all'half edge
 */
inline void HalfEdge::setFace(Face* newFace)
{
    _face = newFace;
}

/**************************
 * Private Inline Methods *
 **************************/

/**
 * \~Italian
 * @brief Setta l'id dell'half edge.
 *
 * Questa funzione dovrebbe essere chiamata solamente dalla classe Dcel.
 *
 * @param[in] id: nuovo id che verrà assegnato all'half edge
 */
inline void HalfEdge::setId(unsigned int id)
{
    this->_id = id;
}

} //namespace cg3::internal
} //namespace cg3

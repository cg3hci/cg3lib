/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "dcel_half_edge.h"

namespace cg3 {

/*************************
 * Public Inline Methods *
 *************************/

/**
 * \~Italian
 * @brief Restituisce l'id identificativo nella Dcel dell'half edge
 * @return L'id dell'a faccia'half edge
 */
inline unsigned int Dcel::HalfEdge::id() const
{
    return _id;
}

/**
 * \~Italian
 * @brief Restituisce il flag associato all'a faccia'half edge
 * @return Il flag dell'half edge
 */
inline int Dcel::HalfEdge::flag() const
{
    return _flag;
}

/**
 * \~Italian
 * @brief Restituisce il puntatore al vertice costante di origine dell'half edge
 * @return Il from vertex dell'half edge
 */
inline const Dcel::Vertex* Dcel::HalfEdge::fromVertex() const
{
    return _fromVertex;
}

/**
 * \~Italian
 * @brief Restituisce il puntatore al vertice costante di destinazione dell'half edge
 * @return Il to vertex dell'half edge
 */
inline const Dcel::Vertex* Dcel::HalfEdge::toVertex() const
{
    return _toVertex;
}

/**
 * \~Italian
 * @brief Restituisce puntatore all'half edge costante gemello dell'half edge
 * @return Il twin dell'half edge
 */
inline const Dcel::HalfEdge* Dcel::HalfEdge::twin() const
{
    return _twin;
}

/**
 * \~Italian
 * @brief Restituisce puntatore all'half edge costante precedente dell'half edge
 * @return Il prev dell'half edge
 */
inline const Dcel::HalfEdge* Dcel::HalfEdge::prev() const
{
    return _prev;
}

/**
 * \~Italian
 * @brief Restituisce puntatore all'half edge costante successivo dell'half edge
 * @return Il next dell'half edge
 */
inline const Dcel::HalfEdge* Dcel::HalfEdge::next() const
{
    return _next;
}

/**
 * \~Italian
 * @brief Restituisce puntatore alla faccia costante incidente all'half edge
 * @return La faccia incidente all'half edge
 */
inline const Dcel::Face* Dcel::HalfEdge::face() const
{
    return _face;
}

#ifdef DEBUG
/**
 * \~Italian
 * @brief Lancia un'asserzione se il vertice di origine è nullptr
 */
inline void Dcel::HalfEdge::checkFromVertex() const
{
    if (fromVertex == nullptr){
        std::cerr << "ALERT! Half Edge "<< id << ": from_vertex is nullptr";
        assert(! (fromVertex == nullptr));
    }
}

/**
 * \~Italian
 * @brief Lancia un'asserzione se il vertice di destinazione è nullptr
 */
inline void Dcel::HalfEdge::checkToVertex() const
{
    if (toVertex == nullptr){
        std::cerr << "ALERT! Half Edge "<< id << ": to_vertex is nullptr";
        assert(! (toVertex == nullptr));
    }
}

/**
 * \~Italian
 * @brief Lancia un'asserzione se l'half edge gemello è nullptr
 */
inline void Dcel::HalfEdge::checkTwin() const
{
    if (twin == nullptr){
        std::cerr << "ALERT! Half Edge "<< id << ": twin is nullptr";
        assert(! (twin == nullptr));
    }
}

/**
 * \~Italian
 * @brief Lancia un'asserzione se l'half edge precedente è nullptr
 */
inline void Dcel::HalfEdge::checkPrev() const
{
    if (prev == nullptr){
        std::cerr << "ALERT! Half Edge "<< id << ": prev is nullptr";
        assert(! (prev == nullptr));
    }
}

/**
 * \~Italian
 * @brief Lancia un'asserzione se l'half edge successivo è nullptr
 */
inline void Dcel::HalfEdge::checkNext() const
{
    if (next == nullptr){
        std::cerr << "ALERT! Half Edge "<< id << ": next is nullptr";
        assert(! (next == nullptr));
    }
}

/**
 * \~Italian
 * @brief Lancia un'asserzione se la faccia incidente è nullptr
 */
inline void Dcel::HalfEdge::checkFace() const
{
    if (face == nullptr){
        std::cerr << "ALERT! Half Edge "<< id << ": face is nullptr";
        assert(! (face == nullptr));
    }
}
#endif

/**
 * \~Italian
 * @brief Setta il flag dell'half edge a 1
 */
inline void Dcel::HalfEdge::setFlag()
{
    _flag = 1;
}

/**
 * \~Italian
 * @brief Setta il flag dell'half edge
 * @param[in] new_flag: il valore del flag che verrà settato
 */
inline void Dcel::HalfEdge::setFlag(int new_flag)
{
    _flag = new_flag;
}

/**
 * \~Italian
 * @brief Setta il flag dell'half edge a 0
 */
inline void Dcel::HalfEdge::resetFlag()
{
    _flag = 0;
}

/**
 * \~Italian
 * @brief Restituisce il puntatore al vertice di origine dell'half edge
 * @return Il from vertex dell'half edge
 */
inline Dcel::Vertex* Dcel::HalfEdge::fromVertex()
{
    return _fromVertex;
}

/**
 * \~Italian
 * @brief Restituisce il puntatore al vertice di destinazione dell'half edge
 * @return Il to vertex dell'half edge
 */
inline Dcel::Vertex* Dcel::HalfEdge::toVertex()
{
    return _toVertex;
}

/**
 * \~Italian
 * @brief Restituisce puntatore all'half edge gemello dell'half edge
 * @return Il twin dell'half edge
 */
inline Dcel::HalfEdge* Dcel::HalfEdge::twin()
{
    return _twin;
}

/**
 * \~Italian
 * @brief Restituisce puntatore all'half edge precedente dell'half edge
 * @return Il prev dell'half edge
 */
inline Dcel::HalfEdge* Dcel::HalfEdge::prev()
{
    return _prev;
}

/**
 * \~Italian
 * @brief Restituisce puntatore all'half edge successivo dell'half edge
 * @return Il next dell'half edge
 */
inline Dcel::HalfEdge* Dcel::HalfEdge::next()
{
    return _next;
}

/**
 * \~Italian
 * @brief Restituisce puntatore alla faccia incidente all'half edge
 * @return La faccia incidente all'half edge
 */
inline Dcel::Face* Dcel::HalfEdge::face()
{
    return _face;
}

/**
 * \~Italian
 * @brief Setta il vertice di origine
 * @param[in] newFromVertex: riferimento al from vertex che verrà assegnato all'half edge
 */
inline void Dcel::HalfEdge::setFromVertex(Dcel::Vertex* newFromVertex)
{
    _fromVertex = newFromVertex;
}

/**
 * \~Italian
 * @brief Setta il vertice di destinazione
 * @param[in] newToVertex: riferimento al to vertex che verrà assegnato all'half edge
 */
inline void Dcel::HalfEdge::setToVertex(Dcel::Vertex* newToVertex)
{
    _toVertex = newToVertex;
}

/**
 * \~Italian
 * @brief Setta l'half edge gemello
 * @param[in] newTwin: riferimento al twin che verrà assegnato all'half edge
 */
inline void Dcel::HalfEdge::setTwin(Dcel::HalfEdge* newTwin)
{
    _twin = newTwin;
}

/**
 * \~Italian
 * @brief Setta l'half edge precedente
 * @param[in] newPrev: riferimento al prev che verrà assegnato all'half edge
 */
inline void Dcel::HalfEdge::setPrev(Dcel::HalfEdge* newPrev)
{
    _prev = newPrev;
}

/**
 * \~Italian
 * @brief Setta l'half edge successivo
 * @param[in] newNext: riferimento al next che verrà assegnato all'half edge
 */
inline void Dcel::HalfEdge::setNext(Dcel::HalfEdge* newNext)
{
    _next = newNext;
}

/**
 * \~Italian
 * @brief Setta la faccia incidente
 * @param[in] newFace:riferimento alla faccia che verrà assegnato all'half edge
 */
inline void Dcel::HalfEdge::setFace(Dcel::Face* newFace)
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
inline void Dcel::HalfEdge::setId(unsigned int id)
{
    this->_id = id;
}

}

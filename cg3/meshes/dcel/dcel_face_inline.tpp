/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "dcel_face.h"
#include "dcel_face_iterators.h"
#include "dcel_half_edge.h"

namespace cg3 {

/*************************
 * Public Inline Methods *
 *************************/
/**
 * \~Italian
 * @brief Restituisce l'id identificativo nella Dcel della faccia
 * @return L'id della faccia
 */
inline unsigned int Dcel::Face::id() const
{
    return _id;
}

inline const Dcel::Vertex*Dcel::Face::vertex1() const
{
    assert(_outerHalfEdge != nullptr && "Face's Outer HalfEdge is null.");
    return _outerHalfEdge->fromVertex();
}

inline const Dcel::Vertex*Dcel::Face::vertex2() const
{
    assert(_outerHalfEdge != nullptr && "Face's Outer HalfEdge is null.");
    return _outerHalfEdge->toVertex();
}

inline const Dcel::Vertex*Dcel::Face::vertex3() const
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
inline int Dcel::Face::flag() const
{
    return _flag;
}

/**
 * \~Italian
 * @brief Restituisce il vettore normale alla faccia
 * @note Non ricalcola la normale, restituisce solo l'ultima normale calcolata o settata
 * @return La normale della faccia
 */
inline Vec3 Dcel::Face::normal() const
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
inline double Dcel::Face::area() const
{
    return _area;
}

/**
 * \~Italian
 * @brief Restituisce il colore associato alla faccia
 * @return Il colore della faccia
 */
inline Color Dcel::Face::color() const
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
inline const Dcel::HalfEdge* Dcel::Face::outerHalfEdge() const
{
    return _outerHalfEdge;
}

/**
 * \~Italian
 * @brief Restituisce il numero di inner half edges contenuti nella faccia, ossia il numero di buchi
 * @return Il numero di HalfEdge interni della faccia
 */
inline unsigned int Dcel::Face::numberInnerHalfEdges() const
{
    return (unsigned int)_innerHalfEdges.size();
}

/**
 * \~Italian
 * @brief Restituisce true se la faccia contiene buchi
 * @return True se la faccia contiene buchi, false altrimenti
 */
inline bool Dcel::Face::hasHoles() const
{
    return (_innerHalfEdges.size() != 0);
}

/**
 * \~Italian
 * @brief Restituisce true se l'outer half edge non è null
 */
inline bool Dcel::Face::checkOuterHalfEdge() const
{
    return _outerHalfEdge != nullptr;
}

inline Dcel::Vertex*Dcel::Face::vertex1()
{
    assert(_outerHalfEdge != nullptr && "Face's Outer HalfEdge is null.");
    return _outerHalfEdge->fromVertex();
}

inline Dcel::Vertex*Dcel::Face::vertex2()
{
    assert(_outerHalfEdge != nullptr && "Face's Outer HalfEdge is null.");
    return _outerHalfEdge->toVertex();
}

inline Dcel::Vertex*Dcel::Face::vertex3()
{
    assert(_outerHalfEdge != nullptr && "Face's Outer HalfEdge is null.");
    assert(_outerHalfEdge->next() != nullptr && "Outer HalfEdge's next is null.");
    return _outerHalfEdge->next()->toVertex();
}

/**
 * \~Italian
 * @brief Setta il flag della faccia a 1
 */
inline void Dcel::Face::setFlag()
{
    _flag = 1;
}

/**
 * \~Italian
 * @brief Setta il flag della faccia
 * @param[in] newFlag: il valore del flag che verrà settato
 */
inline void Dcel::Face::setFlag(int newFlag)
{
    _flag = newFlag;
}

/**
 * \~Italian
 * @brief Setta il flag della faccia a 0
 */
inline void Dcel::Face::resetFlag()
{
    _flag = 0;
}

/**
 * \~Italian
 * @brief Setta il vettore normale della faccia
 * @param[in] newNormal: il vettore normale che verrà settato
 */
inline void Dcel::Face::setNormal(const Vec3& newNormal)
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
inline void Dcel::Face::setArea(double newArea)
{
    _area = newArea;
}

/**
 * \~Italian
 * @brief Assegna un nuovo colore alla faccia
 * @param[in] newColor: il nuovo colore che verrà assegnato alla faccia
 */
inline void Dcel::Face::setColor(const Color& newColor)
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
inline Dcel::HalfEdge* Dcel::Face::outerHalfEdge()
{
    return _outerHalfEdge;
}

/**
 * \~Italian
 * @brief Assegna un nuovo half edge di bordo esterno alla faccia
 * @param[in] newOuterHalfEdge: puntatore all'half edge di bordo esterno assegnato alla faccia
 */
inline void Dcel::Face::setOuterHalfEdge(Dcel::HalfEdge* newOuterHalfEdge)
{
    _outerHalfEdge = newOuterHalfEdge;
}

/**
 * \~Italian
 * @brief Aggiunge un nuovo half edge di bordo interno (ossia un buco) alla faccia
 * @param[in] newInnerHalfEdge: nuovo half edge di bordo interno aggiunto alla faccia
 */
inline void Dcel::Face::addInnerHalfEdge(Dcel::HalfEdge* newInnerHalfEdge)
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
inline void Dcel::Face::setId(unsigned int id)
{
    this->_id = id;
}

} //namespace cg3

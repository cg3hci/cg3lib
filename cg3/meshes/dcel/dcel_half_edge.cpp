/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "dcel_face_iterators.h"
#include "dcel_vertex_iterators.h"
#include <cg3/utilities/utils.h>

namespace cg3 {

/****************
 * Constructors *
 ****************/

/**
 * \~Italian
 * @brief Costruttore di default.
 *
 * Crea un half edge con:
 * - from vertex settato a nullptr;
 * - to vertex settato a nullptr;
 * - twin settato a nullptr;
 * - prev settato a nullptr;
 * - next settato a nullptr;
 * - face settata a nullptr;
 * - id pari a 0;
 * - flag pari a 0.
 */
#ifdef NDEBUG
Dcel::HalfEdge::HalfEdge(Dcel& parent) :
    parent(&parent),
    _fromVertex(nullptr),
    _toVertex(nullptr),
    _twin(nullptr),
    _prev(nullptr),
    _next(nullptr),
    _face(nullptr),
    _id(0),
    _flag(0)
{
}
#else
Dcel::HalfEdge::HalfEdge() :
    _fromVertex(nullptr),
    _toVertex(nullptr),
    _twin(nullptr),
    _prev(nullptr),
    _next(nullptr),
    _face(nullptr),
    _id(0),
    _flag(0)
{
}
#endif

/**
 * \~Italian
 * @brief Distruttore vuoto.
 *
 * La classe Dcel dovrà occuparsi di eliminare tutti i riferimenti in essa contenuti (e quindi contenuti di conseguenza anche nella classe Dcel::HalfEdge).
 */
Dcel::HalfEdge::~HalfEdge(void)
{
}

bool Dcel::HalfEdge::isConvex() const {
    if ((face()->normal()) == (twin()->face()->normal()))
        return true;
    Vec3 dir1 = face()->normal().cross(twin()->face()->normal());
    dir1.normalize();
    Vec3 dir2 = (toVertex()->coordinate() - fromVertex()->coordinate());
    dir2.normalize();
    return (epsilonEqual(dir1, dir2));
}

/******************
 * Public Methods *
 ******************/

/**
 * \~Italian
 * @brief Funzione che permette di sapere se un half edge è outer o innter component della sua faccia incidente
 *
 * Cicla su tutti gli half edge sul bordo esterno alla faccia incidente, e se trova l'half edge this, restituisce true;
 * Se non lo trova, da per scontato che sia un inner half edge e restituisce false.
 *
 * @note Non verifica effettivamente che l'half edge sia raggiungibile ciclando sugli inner half edge della
 *       faccia incidente.
 *
 * @warning Utilizza Dcel::Face::constIncidentHalfEdgeIterator
 * @return True se l'half edge è un outer component della sua faccia incidente.
 */
bool Dcel::HalfEdge::isOuterComponent() const
{
    if (_face->numberInnerHalfEdges() == 0) return true;
    for (Dcel::Face::ConstIncidentHalfEdgeIterator heit = _face->incidentHalfEdgeBegin(); heit != _face->incidentHalfEdgeEnd(); ++heit)
        if (*heit == this) return true;
    return false;
}

/**
 * \~Italian
 * @brief Funzione che restituisce la lunghezza dell'half edge
 * @return La distanza tra il from e il to vertex dell'half edge
 */
float Dcel::HalfEdge::length() const
{
    return _fromVertex->coordinate().dist(_toVertex->coordinate());
}

/**
 * \~Italian
 * @brief Funzione toString di un half edge
 * @return Una stringa rappresentativa dell'half edge
 * @todo Da aggiornare
 */
std::string Dcel::HalfEdge::toString() const
{
    std::stringstream ss;

    ss << "ID: " << _id << "; From Vertex: ";
    if (!_fromVertex) ss << "nullptr";
    else ss << _fromVertex->id();
    ss << "; To Vertex: ";
    if (!_toVertex) ss << "nullptr";
    else ss << _toVertex->id();
    ss <<"; Twin: ";
    if (!_twin) ss << "nullptr";
    else ss << _twin->id();
    ss << "; Prev: ";
    if (!_prev) ss << "nullptr";
    else ss << _prev->id();
    ss << "; Next: ";
    if (!_next) ss << "nullptr";
    else ss << _next->id();
    ss << "; Incident Face: ";
    if (!_face) ss << "nullptr";
    else ss << _face->id();
    ss << ".";
    std::string s1 = ss.str();
    return s1;
}

} //namespace cg3

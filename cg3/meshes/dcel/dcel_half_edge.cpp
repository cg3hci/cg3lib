/*
 * @author    Alessandro Muntoni (muntoni.alessandro@gmail.com)
 * @copyright Alessandro Muntoni 2016.
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
Dcel::HalfEdge::HalfEdge(Dcel& parent) : parent(&parent), fromVertex(nullptr), toVertex(nullptr), twin(nullptr), prev(nullptr), next(nullptr), face(nullptr), id(0), flag(0) {
}

/**
 * \~Italian
 * @brief Costruttore di default.
 *
 * Crea un half edge con:
 * - from vertex pari al parametro in input from;
 * - to vertex pari al parametro in input to;
 * - twin settato a nullptr;
 * - prev settato a nullptr;
 * - next settato a nullptr;
 * - face settata a nullptr;
 * - id pari a 0;
 * - flag pari a 0.
 *
 *
 * @param[in] from: puntatore al from vertex settato nell'half edge
 * @param[in] to: puntatore al to vertex settato nell'half edge
 */
/*Dcel::HalfEdge::HalfEdge(Dcel::Vertex* from, Dcel::Vertex* to) : fromVertex(from), toVertex(to), twin(nullptr), prev(nullptr), next(nullptr), face(nullptr), id(0), flag(0) {
}*/

/**
 * \~Italian
 * @brief Costruttore di default.
 *
 * Crea un half edge con:
 * - from vertex pari al parametro in input from;
 * - to vertex pari al parametro in input to;
 * - twin pari al parametro in input twin;
 * - prev pari al parametro in input prev;
 * - next pari al parametro in input next;
 * - face pari al parametro in input face;
 * - id pari a 0;
 * - flag pari a 0.
 *
 *
 * @param[in] from: puntatore al from vertex settato nell'half edge
 * @param[in] to: puntatore al to vertex settato nell'half edge
 * @param[in] twin: puntatore al twin settato nell'half edge
 * @param[in] prev: puntatore al prev settato nell'half edge
 * @param[in] next: puntatore al next settato nell'half edge
 * @param[in] face: puntatore alla faccia incidente settata nell'half edge
 */
/*Dcel::HalfEdge::HalfEdge(Dcel::Vertex* from, Dcel::Vertex* to, Dcel::HalfEdge* twin, Dcel::HalfEdge* prev, Dcel::HalfEdge* next, Dcel::Face* face) : fromVertex(from), toVertex(to), twin(twin), prev(prev), next(next), face(face), id(0), flag(0) {
}*/

/**
 * \~Italian
 * @brief Distruttore vuoto.
 *
 * La classe Dcel dovrà occuparsi di eliminare tutti i riferimenti in essa contenuti (e quindi contenuti di conseguenza anche nella classe Dcel::HalfEdge).
 */
Dcel::HalfEdge::~HalfEdge(void) {
}

bool Dcel::HalfEdge::isConvex() const {
    if ((getFace()->getNormal()) == (getTwin()->getFace()->getNormal()))
        return true;
    Vec3 dir1 = getFace()->getNormal().cross(getTwin()->getFace()->getNormal());
    dir1.normalize();
    Vec3 dir2 = (getToVertex()->getCoordinate() - getFromVertex()->getCoordinate());
    dir2.normalize();
    return (Common::epsilonEqual(dir1, dir2));
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
bool Dcel::HalfEdge::isOuterComponent() const {
    if (face->getNumberInnerHalfEdges() == 0) return true;
    for (Dcel::Face::ConstIncidentHalfEdgeIterator heit = face->incidentHalfEdgeBegin(); heit != face->incidentHalfEdgeEnd(); ++heit)
        if (**heit == *this) return true;
    return false;
}

/**
 * \~Italian
 * @brief Funzione che restituisce la lunghezza dell'half edge
 * @return La distanza tra il from e il to vertex dell'half edge
 */
float Dcel::HalfEdge::getLength() const {
    return fromVertex->getCoordinate().dist(toVertex->getCoordinate());
}

/**
 * \~Italian
 * @brief Funzione toString di un half edge
 * @return Una stringa rappresentativa dell'half edge
 * @todo Da aggiornare
 */
std::string Dcel::HalfEdge::toString() const {
    std::stringstream ss;

    ss << "ID: " << id << "; From Vertex: ";
    if (!fromVertex) ss << "nullptr";
    else ss << fromVertex->getId();
    ss << "; To Vertex: ";
    if (!toVertex) ss << "nullptr";
    else ss << toVertex->getId();
    ss <<"; Twin: ";
    if (!twin) ss << "nullptr";
    else ss << twin->getId();
    ss << "; Prev: ";
    if (!prev) ss << "nullptr";
    else ss << prev->getId();
    ss << "; Next: ";
    if (!next) ss << "nullptr";
    else ss << next->getId();
    ss << "; Incident Face: ";
    if (!face) ss << "nullptr";
    else ss << face->getId();
    ss << ".";
    std::string s1 = ss.str();
    return s1;
}

}

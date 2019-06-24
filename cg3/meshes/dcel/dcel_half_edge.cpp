/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "dcel_half_edge.h"
#include "dcel_face.h"
#include "dcel_vertex.h"
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
CG3_INLINE HalfEdge::HalfEdge(internal::DcelData& parent) :
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
CG3_INLINE HalfEdge::HalfEdge() :
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
 * La classe Dcel dovrà occuparsi di eliminare tutti i riferimenti in essa contenuti (e quindi contenuti di conseguenza anche nella classe HalfEdge).
 */
CG3_INLINE HalfEdge::~HalfEdge(void)
{
}

/**
 * \~Italian
 * @brief Restituisce l'id identificativo nella Dcel dell'half edge
 * @return L'id dell'a faccia'half edge
 */
CG3_INLINE unsigned int HalfEdge::id() const
{
	return _id;
}

/**
 * \~Italian
 * @brief Restituisce il flag associato all'a faccia'half edge
 * @return Il flag dell'half edge
 */
CG3_INLINE int HalfEdge::flag() const
{
	return _flag;
}

/**
 * \~Italian
 * @brief Restituisce il puntatore al vertice costante di origine dell'half edge
 * @return Il from vertex dell'half edge
 */
CG3_INLINE const Vertex* HalfEdge::fromVertex() const
{
	return _fromVertex;
}

/**
 * \~Italian
 * @brief Restituisce il puntatore al vertice costante di destinazione dell'half edge
 * @return Il to vertex dell'half edge
 */
CG3_INLINE const Vertex* HalfEdge::toVertex() const
{
	return _toVertex;
}

/**
 * \~Italian
 * @brief Restituisce puntatore all'half edge costante gemello dell'half edge
 * @return Il twin dell'half edge
 */
CG3_INLINE const HalfEdge* HalfEdge::twin() const
{
	return _twin;
}

/**
 * \~Italian
 * @brief Restituisce puntatore all'half edge costante precedente dell'half edge
 * @return Il prev dell'half edge
 */
CG3_INLINE const HalfEdge* HalfEdge::prev() const
{
	return _prev;
}

/**
 * \~Italian
 * @brief Restituisce puntatore all'half edge costante successivo dell'half edge
 * @return Il next dell'half edge
 */
CG3_INLINE const HalfEdge* HalfEdge::next() const
{
	return _next;
}

/**
 * \~Italian
 * @brief Restituisce puntatore alla faccia costante incidente all'half edge
 * @return La faccia incidente all'half edge
 */
CG3_INLINE const Face* HalfEdge::face() const
{
	return _face;
}

#ifdef DEBUG
/**
 * \~Italian
 * @brief Lancia un'asserzione se il vertice di origine è nullptr
 */
CG3_INLINE void HalfEdge::checkFromVertex() const
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
CG3_INLINE void HalfEdge::checkToVertex() const
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
CG3_INLINE void HalfEdge::checkTwin() const
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
CG3_INLINE void HalfEdge::checkPrev() const
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
CG3_INLINE void HalfEdge::checkNext() const
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
CG3_INLINE void HalfEdge::checkFace() const
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
CG3_INLINE void HalfEdge::setFlag()
{
	_flag = 1;
}

/**
 * \~Italian
 * @brief Setta il flag dell'half edge
 * @param[in] new_flag: il valore del flag che verrà settato
 */
CG3_INLINE void HalfEdge::setFlag(int new_flag)
{
	_flag = new_flag;
}

/**
 * \~Italian
 * @brief Setta il flag dell'half edge a 0
 */
CG3_INLINE void HalfEdge::resetFlag()
{
	_flag = 0;
}

/**
 * \~Italian
 * @brief Restituisce il puntatore al vertice di origine dell'half edge
 * @return Il from vertex dell'half edge
 */
CG3_INLINE Vertex* HalfEdge::fromVertex()
{
	return _fromVertex;
}

/**
 * \~Italian
 * @brief Restituisce il puntatore al vertice di destinazione dell'half edge
 * @return Il to vertex dell'half edge
 */
CG3_INLINE Vertex* HalfEdge::toVertex()
{
	return _toVertex;
}

/**
 * \~Italian
 * @brief Restituisce puntatore all'half edge gemello dell'half edge
 * @return Il twin dell'half edge
 */
CG3_INLINE HalfEdge* HalfEdge::twin()
{
	return _twin;
}

/**
 * \~Italian
 * @brief Restituisce puntatore all'half edge precedente dell'half edge
 * @return Il prev dell'half edge
 */
CG3_INLINE HalfEdge* HalfEdge::prev()
{
	return _prev;
}

/**
 * \~Italian
 * @brief Restituisce puntatore all'half edge successivo dell'half edge
 * @return Il next dell'half edge
 */
CG3_INLINE HalfEdge* HalfEdge::next()
{
	return _next;
}

/**
 * \~Italian
 * @brief Restituisce puntatore alla faccia incidente all'half edge
 * @return La faccia incidente all'half edge
 */
CG3_INLINE Face* HalfEdge::face()
{
	return _face;
}

/**
 * \~Italian
 * @brief Setta il vertice di origine
 * @param[in] newFromVertex: riferimento al from vertex che verrà assegnato all'half edge
 */
CG3_INLINE void HalfEdge::setFromVertex(Vertex* newFromVertex)
{
	_fromVertex = newFromVertex;
}

/**
 * \~Italian
 * @brief Setta il vertice di destinazione
 * @param[in] newToVertex: riferimento al to vertex che verrà assegnato all'half edge
 */
CG3_INLINE void HalfEdge::setToVertex(Vertex* newToVertex)
{
	_toVertex = newToVertex;
}

/**
 * \~Italian
 * @brief Setta l'half edge gemello
 * @param[in] newTwin: riferimento al twin che verrà assegnato all'half edge
 */
CG3_INLINE void HalfEdge::setTwin(HalfEdge* newTwin)
{
	_twin = newTwin;
}

/**
 * \~Italian
 * @brief Setta l'half edge precedente
 * @param[in] newPrev: riferimento al prev che verrà assegnato all'half edge
 */
CG3_INLINE void HalfEdge::setPrev(HalfEdge* newPrev)
{
	_prev = newPrev;
}

/**
 * \~Italian
 * @brief Setta l'half edge successivo
 * @param[in] newNext: riferimento al next che verrà assegnato all'half edge
 */
CG3_INLINE void HalfEdge::setNext(HalfEdge* newNext)
{
	_next = newNext;
}

/**
 * \~Italian
 * @brief Setta la faccia incidente
 * @param[in] newFace:riferimento alla faccia che verrà assegnato all'half edge
 */
CG3_INLINE void HalfEdge::setFace(Face* newFace)
{
	_face = newFace;
}

CG3_INLINE bool HalfEdge::isConvex() const {
    if ((face()->normal()) == (twin()->face()->normal()))
        return true;
    Vec3d dir1 = face()->normal().cross(twin()->face()->normal());
    dir1.normalize();
    Vec3d dir2 = (toVertex()->coordinate() - fromVertex()->coordinate());
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
 * @warning Utilizza Face::constIncidentHalfEdgeIterator
 * @return True se l'half edge è un outer component della sua faccia incidente.
 */
CG3_INLINE bool HalfEdge::isOuterComponent() const
{
    if (_face->numberInnerHalfEdges() == 0) return true;
//    for (Face::ConstIncidentHalfEdgeIterator heit = _face->incidentHalfEdgeBegin(); heit != _face->incidentHalfEdgeEnd(); ++heit)
//        if (*heit == this) return true;
    return false;
}

/**
 * \~Italian
 * @brief Funzione che restituisce la lunghezza dell'half edge
 * @return La distanza tra il from e il to vertex dell'half edge
 */
CG3_INLINE float HalfEdge::length() const
{
    return _fromVertex->coordinate().dist(_toVertex->coordinate());
}

/**
 * \~Italian
 * @brief Funzione toString di un half edge
 * @return Una stringa rappresentativa dell'half edge
 * @todo Da aggiornare
 */
CG3_INLINE std::string HalfEdge::toString() const
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

/**
 * @brief The serialize method does nothing because everything is done by the
 * cg3::TemplatedDcel class. Must be implemented if the half edge is inherited.
 * @param binaryFile
 */
CG3_INLINE void HalfEdge::serialize(std::ofstream& binaryFile) const
{
    CG3_SUPPRESS_WARNING(binaryFile);
}

/**
 * @brief The deserialize method does nothing because everything is done by the
 * cg3::TemplatedDcel class. Must be implemented if the half edge is inherited.
 * @param binaryFile
 */
CG3_INLINE void HalfEdge::deserialize(std::ifstream& binaryFile)
{
    CG3_SUPPRESS_WARNING(binaryFile);
}

/**
 * \~Italian
 * @brief Setta l'id dell'half edge.
 *
 * Questa funzione dovrebbe essere chiamata solamente dalla classe Dcel.
 *
 * @param[in] id: nuovo id che verrà assegnato all'half edge
 */
CG3_INLINE void HalfEdge::setId(unsigned int id)
{
	this->_id = id;
}

} //namespace cg3

/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "dcel_face.h"
#include "dcel_vertex.h"
#include <cg3/geometry/transformations3.h>
#include <cg3/geometry/utils3.h>
#ifdef CG3_CGAL_DEFINED
#include <cg3/cgal/triangulation3.h>
#endif

namespace cg3 {

/****************
 * Constructors *
 ****************/
/**
 * @brief Default constructor.
 *
 * Creates a face with:
 * - outer half edge setted to nullptr;
 * - no inner half edges;
 * - normal setted to (0, 0, 0);
 * - area setted a 0;
 * - id setted to 0;
 * - flag setted to 0.
 */
#ifdef NDEBUG
CG3_INLINE Face::Face(internal::DcelData& parent) :
    parent(&parent),
    _outerHalfEdge(nullptr),
    _area(0),
    _id(0),
    _flag(0)
{
    _innerHalfEdges.clear();
}
#else
CG3_INLINE Face::Face() : _outerHalfEdge(nullptr), _area(0), _id(0), _flag(0){
    _innerHalfEdges.clear();
}
#endif

/**
 * \~Italian
 * @brief Distruttore vuoto.
 *
 * La classe Dcel dovrà occuparsi di eliminare tutti i riferimenti in essa contenuti (e quindi contenuti di conseguenza anche nella classe Face).
 */
CG3_INLINE Face::~Face(void)
{
}


/******************
 * Public Methods *
 ******************/

/**
 * \~Italian
 * @brief Restituisce l'id identificativo nella Dcel della faccia
 * @return L'id della faccia
 */
CG3_INLINE unsigned int Face::id() const
{
	return _id;
}

CG3_INLINE const Vertex*Face::vertex1() const
{
	assert(_outerHalfEdge != nullptr && "Face's Outer HalfEdge is null.");
	return _outerHalfEdge->fromVertex();
}

CG3_INLINE const Vertex*Face::vertex2() const
{
	assert(_outerHalfEdge != nullptr && "Face's Outer HalfEdge is null.");
	return _outerHalfEdge->toVertex();
}

CG3_INLINE const Vertex*Face::vertex3() const
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
CG3_INLINE int Face::flag() const
{
	return _flag;
}

/**
 * \~Italian
 * @brief Restituisce il vettore normale alla faccia
 * @note Non ricalcola la normale, restituisce solo l'ultima normale calcolata o settata
 * @return La normale della faccia
 */
CG3_INLINE Vec3d Face::normal() const
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
CG3_INLINE double Face::area() const
{
	return _area;
}

/**
 * \~Italian
 * @brief Restituisce il colore associato alla faccia
 * @return Il colore della faccia
 */
CG3_INLINE Color Face::color() const
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
CG3_INLINE const HalfEdge* Face::outerHalfEdge() const
{
	return _outerHalfEdge;
}

/**
 * \~Italian
 * @brief Restituisce il numero di inner half edges contenuti nella faccia, ossia il numero di buchi
 * @return Il numero di HalfEdge interni della faccia
 */
CG3_INLINE unsigned int Face::numberInnerHalfEdges() const
{
	return (unsigned int)_innerHalfEdges.size();
}

/**
 * \~Italian
 * @brief Restituisce true se la faccia contiene buchi
 * @return True se la faccia contiene buchi, false altrimenti
 */
CG3_INLINE bool Face::hasHoles() const
{
	return (_innerHalfEdges.size() != 0);
}

/**
 * \~Italian
 * @brief Restituisce true se l'outer half edge non è null
 */
CG3_INLINE bool Face::checkOuterHalfEdge() const
{
	return _outerHalfEdge != nullptr;
}

CG3_INLINE Vertex*Face::vertex1()
{
	assert(_outerHalfEdge != nullptr && "Face's Outer HalfEdge is null.");
	return _outerHalfEdge->fromVertex();
}

CG3_INLINE Vertex*Face::vertex2()
{
	assert(_outerHalfEdge != nullptr && "Face's Outer HalfEdge is null.");
	return _outerHalfEdge->toVertex();
}

CG3_INLINE Vertex*Face::vertex3()
{
	assert(_outerHalfEdge != nullptr && "Face's Outer HalfEdge is null.");
	assert(_outerHalfEdge->next() != nullptr && "Outer HalfEdge's next is null.");
	return _outerHalfEdge->next()->toVertex();
}

/**
 * \~Italian
 * @brief Setta il flag della faccia a 1
 */
CG3_INLINE void Face::setFlag()
{
	_flag = 1;
}

/**
 * \~Italian
 * @brief Setta il flag della faccia
 * @param[in] newFlag: il valore del flag che verrà settato
 */
CG3_INLINE void Face::setFlag(int newFlag)
{
	_flag = newFlag;
}

/**
 * \~Italian
 * @brief Setta il flag della faccia a 0
 */
CG3_INLINE void Face::resetFlag()
{
	_flag = 0;
}

/**
 * \~Italian
 * @brief Setta il vettore normale della faccia
 * @param[in] newNormal: il vettore normale che verrà settato
 */
CG3_INLINE void Face::setNormal(const Vec3d& newNormal)
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
CG3_INLINE void Face::setArea(double newArea)
{
	_area = newArea;
}

/**
 * \~Italian
 * @brief Assegna un nuovo colore alla faccia
 * @param[in] newColor: il nuovo colore che verrà assegnato alla faccia
 */
CG3_INLINE void Face::setColor(const Color& newColor)
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
CG3_INLINE HalfEdge* Face::outerHalfEdge()
{
	return _outerHalfEdge;
}

/**
 * \~Italian
 * @brief Assegna un nuovo half edge di bordo esterno alla faccia
 * @param[in] newOuterHalfEdge: puntatore all'half edge di bordo esterno assegnato alla faccia
 */
CG3_INLINE void Face::setOuterHalfEdge(HalfEdge* newOuterHalfEdge)
{
	_outerHalfEdge = newOuterHalfEdge;
}

/**
 * \~Italian
 * @brief Aggiunge un nuovo half edge di bordo interno (ossia un buco) alla faccia
 * @param[in] newInnerHalfEdge: nuovo half edge di bordo interno aggiunto alla faccia
 */
CG3_INLINE void Face::addInnerHalfEdge(HalfEdge* newInnerHalfEdge)
{
	_innerHalfEdges.push_back(newInnerHalfEdge);
}

/**
 * \~Italian
 * @brief Funzione che verifica se la faccia è un triangolo
 * @return True se la faccia è un triangolo, false altrimenti
 */
CG3_INLINE bool Face::isTriangle() const
{
    assert(_outerHalfEdge != nullptr && "Face's Outer HalfEdge is null.");
    assert(_outerHalfEdge->next() != nullptr && "HalfEdge's Next is null.");
    assert(_outerHalfEdge->next()->next() != nullptr && "HalfEdge's Next is null.");
    return (_outerHalfEdge == _outerHalfEdge->next()->next()->next());
}

CG3_INLINE bool Face::isAdjacentTo(const Face* ad) const
{
    for (const HalfEdge* he : incidentHalfEdgeIterator()){
        assert(he != nullptr && "Next component of Previous HalfEdge is null.");
        assert(he->twin() != nullptr && "HalfEdge's Twin is null.");
        if (he->twin()->face() == ad) return true;
    }
    for (ConstInnerHalfEdgeIterator ihe = innerHalfEdgeBegin(); ihe != innerHalfEdgeEnd(); ++ihe){
        for (ConstIncidentHalfEdgeIterator heit = incidentHalfEdgeBegin(*ihe), hend = incidentHalfEdgeEnd(); heit != hend; ++heit){
            assert(*(heit) != nullptr && "Next component of Previous HalfEdge is null.");
            assert((*heit)->twin() != nullptr && "HalfEdge's Twin is null.");
            if ((*heit)->twin()->face() == ad) return true;
        }
    }
    return false;
}

CG3_INLINE bool Face::isIncidentTo(const Vertex* v) const
{
    for (const HalfEdge* he : v->outgoingHalfEdgeIterator()) {
        assert(he != nullptr && "Twin component of an HalfEdge is null.");
        if (he->face() == this) return true;
    }
    return false;
}

/**
 * \~Italian
 * @brief Restituisce il numero di vertici incidenti alla faccia
 * @warning Utilizza Face::ConstIncidentVertexIterator
 * @return Il numero di vertici incidenti alla faccia
 */
CG3_INLINE int Face::numberIncidentVertices() const
{
    int n = 0;
    for (ConstIncidentVertexIterator vi = incidentVertexBegin(); vi != incidentVertexEnd(); ++vi) n++;
    return n;
}

/**
 * \~Italian
 * @brief Restituisce il numero di half edge incidenti alla faccia
 * @warning Utilizza Face::ConstIncidentHalfEdgeIterator
 * @return Il numero di half edge incidenti alla faccia
 */
CG3_INLINE int Face::numberIncidentHalfEdges() const
{
    int n = 0;
    for (ConstIncidentHalfEdgeIterator hei = incidentHalfEdgeBegin(); hei !=incidentHalfEdgeEnd(); ++hei) n++;
    return n;
}

/**
 * \~Italian
 * @brief Calcola e restituisce il baricentro della faccia.
 *
 * Il baricentro è calcolato come media dei vertici incidenti alla faccia.
 *
 * @warning Utilizza Face::ConstIncidentVertexIterator
 * @return Il baricentro della faccia.
 */
CG3_INLINE Point3d Face::barycenter() const
{
    Point3d p;
    int n = 0;
    for (const Vertex* v : incidentVertexIterator()){
        assert (v != nullptr && "HalfEdge's to vertex is null.");
        p += v->coordinate();
        n++;
    }
    p /= n;
    return p;
}

#ifdef CG3_CGAL_DEFINED
/**
 * \~Italian
 * @brief Face::getTriangulation
 * @param triangles
 */
CG3_INLINE void Face::triangulation(std::vector<std::array<const Vertex*, 3> > &triangles) const
{
    // Taking all the coordinates on vectors
    std::vector<Point3d> borderCoordinates;
    std::vector< std::vector<Point3d> > innerBorderCoordinates;
    std::map<Point3d, const Vertex*> pointsVerticesMap;
    for (const HalfEdge* he : incidentHalfEdgeIterator()){
        assert(he != nullptr && "Next component of Previous HalfEdge is null.");
        assert(he->fromVertex() != nullptr && "HalfEdge's from vertex is null.");
        borderCoordinates.push_back(he->fromVertex()->coordinate());
        std::pair<const Vertex*, const Vertex*> pp;
        pp.first = he->fromVertex();
        pp.second = he->toVertex();
        pointsVerticesMap[he->fromVertex()->coordinate()] = he->fromVertex();
    }

    if (hasHoles()){
        innerBorderCoordinates.reserve(numberInnerHalfEdges());
        int i = 0;
        for (Face::ConstInnerHalfEdgeIterator ihe = innerHalfEdgeBegin(), ihend = innerHalfEdgeEnd(); ihe != ihend; ++ihe, ++i){
            const HalfEdge* he = *ihe;
            std::vector<Point3d> inner;
            for (Face::ConstIncidentHalfEdgeIterator heit = incidentHalfEdgeBegin(he), hend = incidentHalfEdgeEnd(); heit != hend; ++heit) {
                assert(*(heit) != nullptr && "Next component of Previous HalfEdge is null.");
                assert((*heit)->fromVertex() != nullptr && "HalfEdge's from vertex is null.");
                inner.push_back((*heit)->fromVertex()->coordinate());
                std::pair<const Vertex*, const Vertex*> pp;
                pp.first = (*heit)->fromVertex();
                pp.second = (*heit)->toVertex();
                pointsVerticesMap[(*heit)->fromVertex()->coordinate()] = (*heit)->fromVertex();
            }
            innerBorderCoordinates.push_back(inner);
        }
    }

    #ifdef NDEBUG
	std::vector<std::array<Point3d, 3> > trianglesP = cgal::triangulate3(parent->faceNormals[_id], borderCoordinates, innerBorderCoordinates);
    #else
    std::vector<std::array<Point3d, 3> > trianglesP = cgal::triangulate3(_normal, borderCoordinates, innerBorderCoordinates);
    #endif

    triangles.clear();
    for (unsigned int i = 0; i < trianglesP.size(); ++i) {
            std::array<Point3d, 3> triangle = trianglesP[i];
            Point3d p1 = triangle[0];
            Point3d p2 = triangle[1];
            Point3d p3 = triangle[2];
            assert(pointsVerticesMap.find(p1) != pointsVerticesMap.end() && "Triangulation vertex not founded on original face.");
            assert(pointsVerticesMap.find(p2) != pointsVerticesMap.end() && "Triangulation vertex not founded on original face.");
            assert(pointsVerticesMap.find(p3) != pointsVerticesMap.end() && "Triangulation vertex not founded on original face.");
            const Vertex* a = pointsVerticesMap[p1];
            const Vertex* b = pointsVerticesMap[p2];
            const Vertex* c = pointsVerticesMap[p3];
            std::array<const Vertex*, 3> tuple = {a, b, c};
            triangles.push_back(tuple);
    }
}
#endif

/**
 * \~Italian
 * @brief Funzione toString di una faccia
 * @return Una stringa rappresentativa della faccia
 * @todo Da aggiornare
 */
CG3_INLINE std::string Face::toString() const
{
    std::stringstream ss;

    #ifdef NDEBUG
    ss << "ID: " << _id << "; Normal: " << parent->faceNormals[_id] << "; Outer Component: ";
    #else
    ss << "ID: " << _id << "; Normal: " << _normal << "; Outer Component: ";
    #endif
    if (_outerHalfEdge != nullptr) ss << _outerHalfEdge->id();
    else ss << "nullptr";
    ss << "; N Inner Components: " << _innerHalfEdges.size() << "; Inner Components: "
       << innerComponentsToString() << ".";
    std::string s1 = ss.str();
    return s1;
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Face::ConstIncidentVertexIterator.
 *
 * Permette di ciclare sui vertici incidenti alla faccia, partendo dal vertice start. \n
 * È meno efficiente rispetto a Face::constIncidentVertexBegin(const HalfEdge* start).
 *
 * @param[in] start: vertice di partenza
 * @warning Se start non risulta essere incidente alla faccia (ossia non possiede un half edge incidente alla faccia),
 *          viene lanciata un'asserzione e il programma termina
 * @warning Utilizza Vertex::ConstIncomingHalfEdgeIterator
 * @return Un iteratore che punta al vertice start
 */
CG3_INLINE Face::ConstIncidentVertexIterator Face::incidentVertexBegin(const Vertex* start) const
{
    for (const HalfEdge* he : start->incomingHalfEdgeIterator()) {
        assert(he != nullptr && "Half Edge is null.");
        if (he->face() == this) return ConstIncidentVertexIterator(he, he, this);
    }
    assert(0 && "Start vertex is not incident to iterated face.");
    return ConstIncidentVertexIterator();
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Face::ConstIncidentVertexIterator.
 *
 * Permette di ciclare sui vertici incidenti alla faccia, partendo dal vertice start e fino al vertice end. \n
 * È meno efficiente rispetto a Face::constIncidentVertexBegin(const HalfEdge* start, const HalfEdge* end).
 *
 * @param[in] start: vertice di partenza
 * @param[in] end: vertice di arrivo, \b non \b compreso
 * @warning Se start e end non risultano essere incidenti alla faccia (ossia non possiedono un half edge incidente alla faccia),
 *          viene lanciata un'asserzione e il programma termina
 * @warning Utilizza Vertex::ConstIncomingHalfEdgeIterator
 * @return Un iteratore che punta al vertice start
 */
CG3_INLINE Face::ConstIncidentVertexIterator Face::incidentVertexBegin(const Vertex* start, const Vertex* end) const
{
    Vertex::ConstIncomingHalfEdgeIterator heit = start->incomingHalfEdgeBegin(), hend = start->incomingHalfEdgeEnd();
    while (heit!= hend && ((*heit)->face() != this)) {
        ++heit;
        assert((heit == hend || (*heit) != nullptr) && "Half Edge is null.");
    }
    assert((*heit)->face() == this && "Start vertex is not incident to iterated face.");
    const HalfEdge* s = *heit;
    for (heit= end->incomingHalfEdgeBegin(), hend = end->incomingHalfEdgeEnd(); heit!= hend; ++heit){
        assert((*heit) != nullptr && "Half Edge is null.");
        if ((*heit)->face() == this) return ConstIncidentVertexIterator(s, *heit, this);
    }
    assert(0 && "End vertex is not incident to iterated face.");
    return ConstIncidentVertexIterator();
}

/**
 * \~Italian
 * @brief Funzione che aggiorna la normale alla faccia
 * @warning Funziona se e solo se la faccia è un triangolo
 * @warning Utilizza Face::ConstIncidentVertexIterator
 * @return La normale alla faccia aggiornata
 */
CG3_INLINE Vec3d Face::updateNormal()
{
    assert(_outerHalfEdge != nullptr && "Face's Outer HalfEdge is null.");
    Vertex* a = _outerHalfEdge->fromVertex();
    assert(a != nullptr && "HalfEdge's From Vertex is null.");
    Vertex* b = _outerHalfEdge->toVertex();
    assert(b != nullptr && "HalfEdge's To Vertex is null.");
    Vertex* c = _outerHalfEdge->next()->toVertex();
    assert(c != nullptr && "HalfEdge's To Vertex is null.");

    Vec3d normal;
    if (isTriangle()){
        normal = (b->coordinate() - a->coordinate()).cross(c->coordinate() - a->coordinate());
        if (normal != Vec3d())
            normal.normalize();
    }
    else {
        bool end = false;
        HalfEdge* edge = _outerHalfEdge->next()->next();
        Vertex* first = a;
        while (areCollinear(a->coordinate(), b->coordinate(), c->coordinate(), 1E-10) && !end){
            a = b;
            b = c;
            c = edge->toVertex();
            edge = edge->next();
            if (a == first)
                end = true;
        }
        if (end) {
            normal = Vec3d(0,0,0);
        }
        else {
            normal = (b->coordinate() - a->coordinate()).cross(c->coordinate() - a->coordinate());
            if (normal != Vec3d()){
                normal.normalize();

                std::vector<Point3d> pol;
                for (const Vertex* v : incidentVertexIterator())
                    pol.push_back(v->coordinate());
                if (! isPolygonCounterClockwise(pol, normal))
                    normal = -normal;
            }
        }
    }
    if (normal == Vec3d())
        std::cerr << "Warning: degenerate triangle/polygon; ID: " << id() << "\n";
    #ifdef NDEBUG
    parent->faceNormals[_id] = normal;
    #else
    this->_normal = normal;
    #endif
    return normal;
}

/**
 * \~Italian
 * @brief Funzione che aggiorna l'area della faccia
 * @warning Funziona se e solo se la faccia è un triangolo
 * @warning Utilizza Face::ConstIncidentVertexIterator
 * @return L'area della faccia aggiornata
 */
CG3_INLINE double Face::updateArea()
{
    updateNormal();
    if (normal() != Vec3d()) {
        if (isTriangle()) {
            assert(_outerHalfEdge != nullptr && "Face's Outer HalfEdge is null.");
            assert(_outerHalfEdge->fromVertex() != nullptr && "HalfEdge's From Vertex is null.");
            assert(_outerHalfEdge->toVertex() != nullptr && "HalfEdge's To Vertex is null.");
            assert(_outerHalfEdge->prev() != nullptr && "HalfEdge's prev is null.");
            assert(_outerHalfEdge->prev()->fromVertex() != nullptr && "HalfEdge's From Vertex is null.");
            Point3d v1 = _outerHalfEdge->fromVertex()->coordinate();
            Point3d v2 = _outerHalfEdge->toVertex()->coordinate();
            Point3d v3 = _outerHalfEdge->prev()->fromVertex()->coordinate();
            _area = (((v3 - v1).cross(v2 - v1)).length() / 2);
        }
        #ifdef CG3_CGAL_DEFINED
        else {
            _area = 0;
            std::vector<std::array<const Vertex*, 3> > t;

            triangulation(t);
            for (unsigned int i = 0; i <t.size(); ++i){
                std::array<const Vertex*, 3> tr =  t[i];
                assert(tr[0] != nullptr && "Vertex is null.");
                assert(tr[1] != nullptr && "Vertex is null.");
                assert(tr[2] != nullptr && "Vertex is null.");
                Point3d v1 = tr[0]->coordinate();
                Point3d v2 = tr[1]->coordinate();
                Point3d v3 = tr[2]->coordinate();
                _area += (((v3 - v1).cross(v2 - v1)).length() / 2);
            }
        }
        #endif
    }
    return _area;
}

/**
 * \~Italian
 * @brief Funzione che rimuove un inner half edge dalla faccia
 * @param[in] iterator: iteratore che punta all'inner half edge da eliminare
 */
CG3_INLINE void Face::removeInnerHalfEdge(const Face::InnerHalfEdgeIterator& iterator)
{
    _innerHalfEdges.erase(iterator);
}

/**
 * \~Italian
 * @brief Funzione che rimuove un inner half edge dalla faccia
 *
 * È meno efficiente rispetto a Face::removeInnerHalfEdge(const Face::innerHalfEdgeIterator &ihe).
 *
 * @param[in] halfEdge: inner half edge da eliminare
 * @return True se la rimozione è andata a buon fine, false altrimenti.
 */
CG3_INLINE bool Face::removeInnerHalfEdge(const HalfEdge* halfEdge)
{
    InnerHalfEdgeIterator i = std::find(_innerHalfEdges.begin(), _innerHalfEdges.end(), halfEdge);
    if (i != _innerHalfEdges.end()){
        _innerHalfEdges.erase(i);
        return true;
    }
    return false;
}

CG3_INLINE void Face::removeAllInnerHalfEdges() {
    _innerHalfEdges.clear();
}

CG3_INLINE void Face::invertOrientation()
{
    HalfEdge* first = _outerHalfEdge;
    HalfEdge* actual = first;
    HalfEdge* next;
    do{
        next = actual->next();

        Vertex* from = actual->fromVertex();
        if (from->incidentHalfEdge() == actual)
            from->setIncidentHalfEdge(actual->prev());
        actual->setFromVertex(actual->toVertex());
        actual->setToVertex(from);

        HalfEdge* prev = actual->prev();
        actual->setPrev(actual->next());
        actual->setNext(prev);

        actual = next;

    } while (actual != first);

    for (HalfEdge* inner : _innerHalfEdges){
        HalfEdge* first = inner;
        HalfEdge* actual = first;
        HalfEdge* next;
        do{
            next = actual->next();

            Vertex* from = actual->fromVertex();
            if (from->incidentHalfEdge() == actual)
                from->setIncidentHalfEdge(actual->prev());
            actual->setFromVertex(actual->toVertex());
            actual->setToVertex(from);

            HalfEdge* prev = actual->prev();
            actual->setPrev(actual->next());
            actual->setNext(prev);

            actual = next;

        } while (actual != first);
    }

    updateNormal();
}

/*******
 * Iterators
 ******/

/****************************
 * Face begin()/end() *
 ****************************/

CG3_INLINE Face::ConstAdjacentFaceIterator Face::adjacentFaceBegin() const
{
	return ConstAdjacentFaceIterator(_outerHalfEdge, _outerHalfEdge, this);
}

CG3_INLINE Face::ConstAdjacentFaceIterator Face::adjacentFaceEnd() const
{
	return ConstAdjacentFaceIterator(nullptr, nullptr, this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Face::ConstInnerHalfEdgeIterator
 * @return Un iteratore che punta al primo inner half edge della faccia
 */
CG3_INLINE Face::ConstInnerHalfEdgeIterator Face::innerHalfEdgeBegin() const
{
	return _innerHalfEdges.begin();
}

/**
 * \~Italian
 * @brief Funzione di finalizzazione di Face::ConstInnerHalfEdgeIterator
 * @return Un iteratore che punta all'ultimo inner half edge della faccia
 */
CG3_INLINE Face::ConstInnerHalfEdgeIterator Face::innerHalfEdgeEnd() const
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
CG3_INLINE Face::ConstIncidentHalfEdgeIterator Face::incidentHalfEdgeBegin() const
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
CG3_INLINE Face::ConstIncidentHalfEdgeIterator Face::incidentHalfEdgeEnd() const
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
CG3_INLINE Face::ConstIncidentHalfEdgeIterator Face::incidentHalfEdgeBegin(const HalfEdge* start) const
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
CG3_INLINE Face::ConstIncidentHalfEdgeIterator Face::incidentHalfEdgeBegin(const HalfEdge* start, const HalfEdge* end) const
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
CG3_INLINE Face::ConstIncidentVertexIterator Face::incidentVertexBegin() const
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
CG3_INLINE Face::ConstIncidentVertexIterator Face::incidentVertexEnd() const
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
CG3_INLINE Face::ConstIncidentVertexIterator Face::incidentVertexBegin(const HalfEdge* start) const
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
CG3_INLINE Face::ConstIncidentVertexIterator Face::incidentVertexBegin(const HalfEdge* start, const HalfEdge* end) const
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
CG3_INLINE Face::InnerHalfEdgeIterator Face::innerHalfEdgeBegin()
{
	return _innerHalfEdges.begin();
}

/**
 * \~Italian
 * @brief Funzione di finalizzazione di Face::InnerHalfEdgeIterator
 * @return Un iteratore che punta all'ultimo inner half edge della faccia
 */
CG3_INLINE Face::InnerHalfEdgeIterator Face::innerHalfEdgeEnd()
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
CG3_INLINE Face::IncidentHalfEdgeIterator Face::incidentHalfEdgeBegin()
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
CG3_INLINE Face::IncidentHalfEdgeIterator Face::incidentHalfEdgeEnd()
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
CG3_INLINE Face::IncidentHalfEdgeIterator Face::incidentHalfEdgeBegin(HalfEdge* start)
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
CG3_INLINE Face::IncidentHalfEdgeIterator Face::incidentHalfEdgeBegin(HalfEdge* start, HalfEdge* end)
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
CG3_INLINE Face::IncidentVertexIterator Face::incidentVertexBegin()
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
CG3_INLINE Face::IncidentVertexIterator Face::incidentVertexEnd()
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
CG3_INLINE Face::IncidentVertexIterator Face::incidentVertexBegin(HalfEdge* start)
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
CG3_INLINE Face::IncidentVertexIterator Face::incidentVertexBegin(HalfEdge* start, HalfEdge* end)
{
	assert(start->face() == this && "Start half edge is not incident to iterated face.");
	assert(end->face() == this && "End half edge is not incident to iterated face.");
	return IncidentVertexIterator(start, end, this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Face::IncidentVertexIterator.
 *
 * Permette di ciclare sui vertici incidenti alla faccia, partendo dal vertice start. \n
 * È meno efficiente rispetto a Face::incidentVertexBegin(const HalfEdge* start).
 *
 * @param[in] start: vertice di partenza
 * @warning Se start non risulta essere incidente alla faccia (ossia non possiede un half edge incidente alla faccia),
 *          viene lanciata un'asserzione e il programma termina
 * @warning Utilizza Vertex::ConstIncomingHalfEdgeIterator
 * @return Un iteratore che punta al vertice start
 */
CG3_INLINE Face::IncidentVertexIterator Face::incidentVertexBegin(Vertex* start)
{
    for (HalfEdge* he : start->incomingHalfEdgeIterator()) {
        assert(he != nullptr && "Half Edge is null.");
        if (he->face() == this) return IncidentVertexIterator(he, he, this);
    }
    assert(0 && "Start vertex is not incident to iterated face.");
    return IncidentVertexIterator();
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Face::IncidentVertexIterator.
 *
 * Permette di ciclare sui vertici incidenti alla faccia, partendo dal vertice start e fino al vertice end. \n
 * È meno efficiente rispetto a Face::incidentVertexBegin(const HalfEdge* start, const HalfEdge* end).
 *
 * @param[in] start: vertice di partenza
 * @param[in] end: vertice di arrivo, \b non \b compreso
 * @warning Se start e end non risultano essere incidenti alla faccia (ossia non possiedono un half edge incidente alla faccia),
 *          viene lanciata un'asserzione e il programma termina
 * @warning Utilizza Vertex::ConstIncomingHalfEdgeIterator
 * @return Un iteratore che punta al vertice start
 */
CG3_INLINE Face::IncidentVertexIterator Face::incidentVertexBegin(Vertex* start, Vertex* end)
{
    Vertex::IncomingHalfEdgeIterator heit = start->incomingHalfEdgeBegin(), hend = start->incomingHalfEdgeEnd();
    while (heit!= hend && ((*heit)->face() != this)) {
        ++heit;
        assert((heit == hend || (*heit) != nullptr) && "Half Edge is null.");
    }
    assert((*heit)->face() == this && "Start vertex is not incident to iterated face.");
    HalfEdge* s = *heit;
    for (heit= end->incomingHalfEdgeBegin(), hend = end->incomingHalfEdgeEnd(); heit!= hend; ++heit){
        assert((*heit) != nullptr && "Half Edge is null.");
        if ((*heit)->face() == this) return IncidentVertexIterator(s, *heit, this);
    }
    assert(0 && "End vertex is not incident to iterated face.");
    return IncidentVertexIterator();
}

/*****
 * Range base iterators methods
 *****/

CG3_INLINE Face::ConstInnerHalfEdgeRangeBasedIterator Face::innerHalfEdgeIterator() const
{
	return ConstInnerHalfEdgeRangeBasedIterator(this);
}

CG3_INLINE Face::ConstAdjacentFaceRangeBasedIterator Face::adjacentFaceIterator() const
{
	return ConstAdjacentFaceRangeBasedIterator(this);
}

CG3_INLINE Face::ConstIncidentHalfEdgeRangeBasedIterator Face::incidentHalfEdgeIterator() const
{
	return ConstIncidentHalfEdgeRangeBasedIterator(this);
}

CG3_INLINE Face::ConstIncidentVertexRangeBasedIterator Face::incidentVertexIterator() const
{
	return ConstIncidentVertexRangeBasedIterator(this);
}

CG3_INLINE Face::AdjacentFaceIterator Face::adjacentFaceBegin()
{
	return AdjacentFaceIterator(_outerHalfEdge, _outerHalfEdge, this);
}

CG3_INLINE Face::AdjacentFaceIterator Face::adjacentFaceEnd()
{
	return AdjacentFaceIterator(nullptr, nullptr, this);
}

CG3_INLINE Face::InnerHalfEdgeRangeBasedIterator Face::innerHalfEdgeIterator()
{
	return InnerHalfEdgeRangeBasedIterator(this);
}

CG3_INLINE Face::AdjacentFaceRangeBasedIterator Face::adjacentFaceIterator()
{
	return AdjacentFaceRangeBasedIterator(this);
}

CG3_INLINE Face::IncidentHalfEdgeRangeBasedIterator Face::incidentHalfEdgeIterator()
{
	return IncidentHalfEdgeRangeBasedIterator(this);
}

CG3_INLINE Face::IncidentVertexRangeBasedIterator Face::incidentVertexIterator()
{
	return IncidentVertexRangeBasedIterator(this);
}

CG3_INLINE void Face::serialize(std::ofstream& binaryFile) const
{
    CG3_SUPPRESS_WARNING(binaryFile);
}

CG3_INLINE void Face::deserialize(std::ifstream& binaryFile)
{
    CG3_SUPPRESS_WARNING(binaryFile);
}


/*********************
 * Protected Methods *
 *********************/

/**
 * \~Italian
 * @brief Setta l'id della faccia.
 *
 * Questa funzione dovrebbe essere chiamata solamente dalla classe Dcel.
 *
 * @param[in] id: nuovo id che verrà assegnato alla faccia
 */
CG3_INLINE void Face::setId(unsigned int id)
{
	this->_id = id;
}

/**
 * \~Italian
 * @brief Funzione che restituisce una stringa degli inner half edge
 * @return Una stringa rappresentativa degli inner half edge della faccia
 */
CG3_INLINE std::string Face::innerComponentsToString() const
{
    std::stringstream ss;
    ss << "(";
    for (unsigned int i=0; i<_innerHalfEdges.size(); i++){
        if (_innerHalfEdges[i] != nullptr) {
            if (i != 0) ss << "; ";
            ss << _innerHalfEdges[i]->id();
        }
        else ss << "nullptr";
    }
    ss << ")";
    std::string s1 = ss.str();
    return s1;
}

/**
 * @brief Computes the signed tethraedron volume composed of the tirangle and the origin. Useful for
 * the computation of the volume of the mesh
 * @link https://stackoverflow.com/questions/1406029/how-to-calculate-the-volume-of-a-3d-mesh-object-the-surface-of-which-is-made-up
 * @return signed volume of the tet between the triangle and the origin.
 *
 * @todo generalize to polygons!
 */
CG3_INLINE double Face::signedVolume() const
{
    return vertex1()->coordinate().dot(vertex2()->coordinate().cross(vertex3()->coordinate())) / 6.0f;
}


CG3_INLINE std::ostream&operator<<(std::ostream& inputStream, const Face* f)
{
    if (f == nullptr)
        inputStream << "null; ";
    else
        inputStream << f->toString() << "; ";
    return inputStream;
}

} //namespace cg3

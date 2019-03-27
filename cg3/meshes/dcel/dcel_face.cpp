/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "dcel_face.h"
#include "dcel_vertex.h"
#include <cg3/geometry/transformations.h>
#include <cg3/geometry/utils3d.h>
#ifdef CG3_CGAL_DEFINED
#include <cg3/cgal/triangulation.h>
#endif

namespace cg3 {
namespace internal {

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
Face::Face(DcelData& parent) :
    parent(&parent),
    _outerHalfEdge(nullptr),
    _area(0),
    _id(0),
    _flag(0)
{
    _innerHalfEdges.clear();
}
#else
Face::Face() : _outerHalfEdge(nullptr), _area(0), _id(0), _flag(0){
    _innerHalfEdges.clear();
}
#endif

/**
 * \~Italian
 * @brief Distruttore vuoto.
 *
 * La classe Dcel dovrà occuparsi di eliminare tutti i riferimenti in essa contenuti (e quindi contenuti di conseguenza anche nella classe Face).
 */
Face::~Face(void)
{
}


/******************
 * Public Methods *
 ******************/

/**
 * \~Italian
 * @brief Funzione che verifica se la faccia è un triangolo
 * @return True se la faccia è un triangolo, false altrimenti
 */
bool Face::isTriangle() const
{
    assert(_outerHalfEdge != nullptr && "Face's Outer HalfEdge is null.");
    assert(_outerHalfEdge->next() != nullptr && "HalfEdge's Next is null.");
    assert(_outerHalfEdge->next()->next() != nullptr && "HalfEdge's Next is null.");
    return (_outerHalfEdge == _outerHalfEdge->next()->next()->next());
}

bool Face::isAdjacentTo(const Face* ad) const
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

bool Face::isIncidentTo(const Vertex* v) const
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
int Face::numberIncidentVertices() const
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
int Face::numberIncidentHalfEdges() const
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
Pointd Face::barycenter() const
{
    Pointd p;
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
void Face::triangulation(std::vector<std::array<const Vertex*, 3> > &triangles) const
{
    // Taking all the coordinates on vectors
    std::vector<Pointd> borderCoordinates;
    std::vector< std::vector<Pointd> > innerBorderCoordinates;
    std::map<Pointd, const Vertex*> pointsVerticesMap;
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
            std::vector<Pointd> inner;
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
    std::vector<std::array<Pointd, 3> > trianglesP = cgal::triangulate(parent->faceNormals[_id], borderCoordinates, innerBorderCoordinates);
    #else
    std::vector<std::array<Pointd, 3> > trianglesP = cgal::triangulate(_normal, borderCoordinates, innerBorderCoordinates);
    #endif

    triangles.clear();
    for (unsigned int i = 0; i < trianglesP.size(); ++i) {
            std::array<Pointd, 3> triangle = trianglesP[i];
            Pointd p1 = triangle[0];
            Pointd p2 = triangle[1];
            Pointd p3 = triangle[2];
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
std::string Face::toString() const
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
Face::ConstIncidentVertexIterator Face::incidentVertexBegin(const Vertex* start) const
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
Face::ConstIncidentVertexIterator Face::incidentVertexBegin(const Vertex* start, const Vertex* end) const
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
Vec3 Face::updateNormal()
{
    assert(_outerHalfEdge != nullptr && "Face's Outer HalfEdge is null.");
    Vertex* a = _outerHalfEdge->fromVertex();
    assert(a != nullptr && "HalfEdge's From Vertex is null.");
    Vertex* b = _outerHalfEdge->toVertex();
    assert(b != nullptr && "HalfEdge's To Vertex is null.");
    Vertex* c = _outerHalfEdge->next()->toVertex();
    assert(c != nullptr && "HalfEdge's To Vertex is null.");

    Vec3 normal;
    if (isTriangle()){
        normal = (b->coordinate() - a->coordinate()).cross(c->coordinate() - a->coordinate());
        if (normal != Vec3())
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
            normal = Vec3(0,0,0);
        }
        else {
            normal = (b->coordinate() - a->coordinate()).cross(c->coordinate() - a->coordinate());
            if (normal != Vec3()){
                normal.normalize();

                std::vector<Pointd> pol;
                for (const Vertex* v : incidentVertexIterator())
                    pol.push_back(v->coordinate());
                if (! isPolygonCounterClockwise(pol, normal))
                    normal = -normal;
            }
        }
    }
    if (normal == Vec3())
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
double Face::updateArea()
{
    updateNormal();
    if (normal() != Vec3()) {
        if (isTriangle()) {
            assert(_outerHalfEdge != nullptr && "Face's Outer HalfEdge is null.");
            assert(_outerHalfEdge->fromVertex() != nullptr && "HalfEdge's From Vertex is null.");
            assert(_outerHalfEdge->toVertex() != nullptr && "HalfEdge's To Vertex is null.");
            assert(_outerHalfEdge->prev() != nullptr && "HalfEdge's prev is null.");
            assert(_outerHalfEdge->prev()->fromVertex() != nullptr && "HalfEdge's From Vertex is null.");
            Pointd v1 = _outerHalfEdge->fromVertex()->coordinate();
            Pointd v2 = _outerHalfEdge->toVertex()->coordinate();
            Pointd v3 = _outerHalfEdge->prev()->fromVertex()->coordinate();
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
                Pointd v1 = tr[0]->coordinate();
                Pointd v2 = tr[1]->coordinate();
                Pointd v3 = tr[2]->coordinate();
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
void Face::removeInnerHalfEdge(const Face::InnerHalfEdgeIterator& iterator)
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
bool Face::removeInnerHalfEdge(const HalfEdge* halfEdge)
{
    InnerHalfEdgeIterator i = std::find(_innerHalfEdges.begin(), _innerHalfEdges.end(), halfEdge);
    if (i != _innerHalfEdges.end()){
        _innerHalfEdges.erase(i);
        return true;
    }
    return false;
}

void Face::removeAllInnerHalfEdges() {
    _innerHalfEdges.clear();
}

void Face::invertOrientation()
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
Face::IncidentVertexIterator Face::incidentVertexBegin(Vertex* start)
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
Face::IncidentVertexIterator Face::incidentVertexBegin(Vertex* start, Vertex* end)
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

void Face::serialize(std::ofstream& binaryFile) const
{
    CG3_SUPPRESS_WARNING(binaryFile);
}

void Face::deserialize(std::ifstream& binaryFile)
{
    CG3_SUPPRESS_WARNING(binaryFile);
}


/*********************
 * Protected Methods *
 *********************/

/**
 * \~Italian
 * @brief Funzione che restituisce una stringa degli inner half edge
 * @return Una stringa rappresentativa degli inner half edge della faccia
 */
std::string Face::innerComponentsToString() const
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
double Face::signedVolume() const
{
    return vertex1()->coordinate().dot(vertex2()->coordinate().cross(vertex3()->coordinate())) / 6.0f;
}


std::ostream&operator<<(std::ostream& inputStream, const Face* f)
{
    if (f == nullptr)
        inputStream << "null; ";
    else
        inputStream << f->toString() << "; ";
    return inputStream;
}

}
} //namespace cg3

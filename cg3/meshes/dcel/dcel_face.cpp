/*
 * @author    Alessandro Muntoni (muntoni.alessandro@gmail.com)
 * @copyright Alessandro Muntoni 2016.
 */

#include "dcel_face_iterators.h"
#include "dcel_vertex_iterators.h"
#include <cg3/utilities/utils.h>
#ifdef CG3_CGAL_DEFINED
#include <cg3/cgal/cgalinterface.h>
#endif

namespace cg3 {

/****************
 * Constructors *
 ****************/
/**
 * \~Italian
 * @brief Costruttore di default.
 *
 * Crea una faccia con:
 * - outer half edge settato a nullptr;
 * - nessun inner half edge;
 * - normale pari a (0, 0, 0);
 * - area pari a 0;
 * - id pari a 0;
 * - flag pari a 0.
 */
Dcel::Face::Face(Dcel& parent) : parent(&parent), outerHalfEdge(nullptr), area(0), id(0), flag(0){
    innerHalfEdges.clear();
}

/**
 * \~Italian
 * @brief Distruttore vuoto.
 *
 * La classe Dcel dovrà occuparsi di eliminare tutti i riferimenti in essa contenuti (e quindi contenuti di conseguenza anche nella classe Dcel::Face).
 */
Dcel::Face::~Face(void) {
}


/******************
 * Public Methods *
 ******************/

/**
 * \~Italian
 * @brief Funzione che verifica se la faccia è un triangolo
 * @return True se la faccia è un triangolo, false altrimenti
 */
bool Dcel::Face::isTriangle() const {
    assert(outerHalfEdge != nullptr && "Face's Outer HalfEdge is null.");
    assert(outerHalfEdge->getNext() != nullptr && "HalfEdge's Next is null.");
    assert(outerHalfEdge->getNext()->getNext() != nullptr && "HalfEdge's Next is null.");
    return (outerHalfEdge == outerHalfEdge->getNext()->getNext()->getNext());
}

bool Dcel::Face::isAdjacentTo(const Dcel::Face* ad) const {
    for (const Dcel::HalfEdge* he : incidentHalfEdgeIterator()){
        assert(he != nullptr && "Next component of Previous HalfEdge is null.");
        assert(he->getTwin() != nullptr && "HalfEdge's Twin is null.");
        if (he->getTwin()->getFace() == ad) return true;
    }
    for (ConstInnerHalfEdgeIterator ihe = innerHalfEdgeBegin(); ihe != innerHalfEdgeEnd(); ++ihe){
        for (ConstIncidentHalfEdgeIterator heit = incidentHalfEdgeBegin(*ihe), hend = incidentHalfEdgeEnd(); heit != hend; ++heit){
            assert(*(heit) != nullptr && "Next component of Previous HalfEdge is null.");
            assert((*heit)->getTwin() != nullptr && "HalfEdge's Twin is null.");
            if ((*heit)->getTwin()->getFace() == ad) return true;
        }
    }
    return false;
}

bool Dcel::Face::isIncidentTo(const Dcel::Vertex* v) const {
    for (const Dcel::HalfEdge* he : v->outgoingHalfEdgeIterator()) {
        assert(he != nullptr && "Twin component of an HalfEdge is null.");
        if (he->getFace() == this) return true;
    }
    return false;
}

/**
 * \~Italian
 * @brief Restituisce il numero di vertici incidenti alla faccia
 * @warning Utilizza Dcel::Face::ConstIncidentVertexIterator
 * @return Il numero di vertici incidenti alla faccia
 */
int Dcel::Face::getNumberIncidentVertices() const {
    int n = 0;
    for (ConstIncidentVertexIterator vi = incidentVertexBegin(), vend = incidentVertexEnd(); vi != vend; ++vi) n++;
    return n;
}

/**
 * \~Italian
 * @brief Restituisce il numero di half edge incidenti alla faccia
 * @warning Utilizza Dcel::Face::ConstIncidentHalfEdgeIterator
 * @return Il numero di half edge incidenti alla faccia
 */
int Dcel::Face::getNumberIncidentHalfEdges() const {
    int n = 0;
    for (ConstIncidentHalfEdgeIterator hei = incidentHalfEdgeBegin(), hend = incidentHalfEdgeEnd(); hei != hend; ++hei) n++;
    return n;
}

/**
 * \~Italian
 * @brief Calcola e restituisce il baricentro della faccia.
 *
 * Il baricentro è calcolato come media dei vertici incidenti alla faccia.
 *
 * @warning Utilizza Dcel::Face::ConstIncidentVertexIterator
 * @return Il baricentro della faccia.
 */
Pointd Dcel::Face::getBarycentre() const {
    int n = 0;
    Pointd p;
    for (const Dcel::Vertex* v : incidentVertexIterator()){
        assert (v != nullptr && "HalfEdge's to vertex is null.");
        p += v->getCoordinate();
        n++;
    }
    p /= n;
    return p;
}

#ifdef CG3_CGAL_DEFINED
/**
 * \~Italian
 * @brief Dcel::Face::getTriangulation
 * @param triangles
 */
void Dcel::Face::getTriangulation(std::vector<std::array<const Dcel::Vertex*, 3> > &triangles) const {
    // Taking all the coordinates on vectors
    std::vector<Pointd> borderCoordinates;
    std::vector< std::vector<Pointd> > innerBorderCoordinates;
    std::map<Pointd, const Dcel::Vertex*> pointsVerticesMap;
    for (const Dcel::HalfEdge* he : incidentHalfEdgeIterator()){
        assert(he != nullptr && "Next component of Previous HalfEdge is null.");
        assert(he->getFromVertex() != nullptr && "HalfEdge's from vertex is null.");
        borderCoordinates.push_back(he->getFromVertex()->getCoordinate());
        std::pair<const Dcel::Vertex*, const Dcel::Vertex*> pp;
        pp.first = he->getFromVertex();
        pp.second = he->getToVertex();
        pointsVerticesMap[he->getFromVertex()->getCoordinate()] = he->getFromVertex();
    }

    if (hasHoles()){
        innerBorderCoordinates.reserve(getNumberInnerHalfEdges());
        int i = 0;
        for (Dcel::Face::ConstInnerHalfEdgeIterator ihe = innerHalfEdgeBegin(), ihend = innerHalfEdgeEnd(); ihe != ihend; ++ihe, ++i){
            const Dcel::HalfEdge* he = *ihe;
            std::vector<Pointd> inner;
            for (Dcel::Face::ConstIncidentHalfEdgeIterator heit = incidentHalfEdgeBegin(he), hend = incidentHalfEdgeEnd(); heit != hend; ++heit) {
                assert(*(heit) != nullptr && "Next component of Previous HalfEdge is null.");
                assert((*heit)->getFromVertex() != nullptr && "HalfEdge's from vertex is null.");
                inner.push_back((*heit)->getFromVertex()->getCoordinate());
                std::pair<const Dcel::Vertex*, const Dcel::Vertex*> pp;
                pp.first = (*heit)->getFromVertex();
                pp.second = (*heit)->getToVertex();
                pointsVerticesMap[(*heit)->getFromVertex()->getCoordinate()] = (*heit)->getFromVertex();
            }
            innerBorderCoordinates.push_back(inner);
        }
    }

    std::vector<std::array<Pointd, 3> > trianglesP = CGALInterface::Triangulation::triangulate(parent->faceNormals[id], borderCoordinates, innerBorderCoordinates);

    triangles.clear();
    for (unsigned int i = 0; i < trianglesP.size(); ++i) {
            std::array<Pointd, 3> triangle = trianglesP[i];
            Pointd p1 = triangle[0];
            Pointd p2 = triangle[1];
            Pointd p3 = triangle[2];
            assert(pointsVerticesMap.find(p1) != pointsVerticesMap.end() && "Triangulation vertex not founded on original face.");
            assert(pointsVerticesMap.find(p2) != pointsVerticesMap.end() && "Triangulation vertex not founded on original face.");
            assert(pointsVerticesMap.find(p3) != pointsVerticesMap.end() && "Triangulation vertex not founded on original face.");
            const Dcel::Vertex* a = pointsVerticesMap[p1];
            const Dcel::Vertex* b = pointsVerticesMap[p2];
            const Dcel::Vertex* c = pointsVerticesMap[p3];
            std::array<const Dcel::Vertex*, 3> tuple = {a, b, c};
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
std::string Dcel::Face::toString() const {
    std::stringstream ss;

    ss << "ID: " << id << "; Normal: " << parent->faceNormals[id] << "; Outer Component: ";
    if (outerHalfEdge != nullptr) ss << outerHalfEdge->getId();
    else ss << "nullptr";
    ss << "; N Inner Components: " << innerHalfEdges.size() << "; Inner Components: "
       << innerComponentsToString() << ".";
    std::string s1 = ss.str();
    return s1;
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Dcel::Face::ConstIncidentVertexIterator.
 *
 * Permette di ciclare sui vertici incidenti alla faccia, partendo dal vertice start. \n
 * È meno efficiente rispetto a Dcel::Face::constIncidentVertexBegin(const Dcel::HalfEdge* start).
 *
 * @param[in] start: vertice di partenza
 * @warning Se start non risulta essere incidente alla faccia (ossia non possiede un half edge incidente alla faccia),
 *          viene lanciata un'asserzione e il programma termina
 * @warning Utilizza Dcel::Vertex::ConstIncomingHalfEdgeIterator
 * @return Un iteratore che punta al vertice start
 */
Dcel::Face::ConstIncidentVertexIterator Dcel::Face::incidentVertexBegin(const Dcel::Vertex* start) const {
    for (const Dcel::HalfEdge* he : start->incomingHalfEdgeIterator()) {
    //for (Dcel::Vertex::ConstIncomingHalfEdgeIterator heit = start->incomingHalfEdgeBegin(), hend = start->incomingHalfEdgeEnd(); heit!= hend; ++heit) {
        assert(he != nullptr && "Half Edge is null.");
        if (he->getFace() == this) return ConstIncidentVertexIterator(he, he, this);
    }
    assert(0 && "Start vertex is not incident to iterated face.");
    return ConstIncidentVertexIterator();
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Dcel::Face::ConstIncidentVertexIterator.
 *
 * Permette di ciclare sui vertici incidenti alla faccia, partendo dal vertice start e fino al vertice end. \n
 * È meno efficiente rispetto a Dcel::Face::constIncidentVertexBegin(const Dcel::HalfEdge* start, const Dcel::HalfEdge* end).
 *
 * @param[in] start: vertice di partenza
 * @param[in] end: vertice di arrivo, \b non \b compreso
 * @warning Se start e end non risultano essere incidenti alla faccia (ossia non possiedono un half edge incidente alla faccia),
 *          viene lanciata un'asserzione e il programma termina
 * @warning Utilizza Dcel::Vertex::ConstIncomingHalfEdgeIterator
 * @return Un iteratore che punta al vertice start
 */
Dcel::Face::ConstIncidentVertexIterator Dcel::Face::incidentVertexBegin(const Dcel::Vertex* start, const Dcel::Vertex* end) const {
    Vertex::ConstIncomingHalfEdgeIterator heit = start->incomingHalfEdgeBegin(), hend = start->incomingHalfEdgeEnd();
    while (heit!= hend && ((*heit)->getFace() != this)) {
        ++heit;
        assert((heit == hend || (*heit) != nullptr) && "Half Edge is null.");
    }
    assert((*heit)->getFace() == this && "Start vertex is not incident to iterated face.");
    const Dcel::HalfEdge* s = *heit;
    for (heit= end->incomingHalfEdgeBegin(), hend = end->incomingHalfEdgeEnd(); heit!= hend; ++heit){
        assert((*heit) != nullptr && "Half Edge is null.");
        if ((*heit)->getFace() == this) return ConstIncidentVertexIterator(s, *heit, this);
    }
    assert(0 && "End vertex is not incident to iterated face.");
    return ConstIncidentVertexIterator();
}

/**
 * \~Italian
 * @brief Funzione che aggiorna la normale alla faccia
 * @warning Funziona se e solo se la faccia è un triangolo
 * @warning Utilizza Dcel::Face::ConstIncidentVertexIterator
 * @return La normale alla faccia aggiornata
 */
Vec3 Dcel::Face::updateNormal() {
    assert(outerHalfEdge != nullptr && "Face's Outer HalfEdge is null.");
    Vertex* a = outerHalfEdge->getFromVertex();
    assert(a != nullptr && "HalfEdge's From Vertex is null.");
    Vertex* b = outerHalfEdge->getToVertex();
    assert(b != nullptr && "HalfEdge's To Vertex is null.");
    Vertex* c = outerHalfEdge->getNext()->getToVertex();
    assert(c != nullptr && "HalfEdge's To Vertex is null.");
    Vec3 normal = (b->getCoordinate() - a->getCoordinate()).cross(c->getCoordinate() - a->getCoordinate());
    normal.normalize();
    if (outerHalfEdge->getNext()->getNext()->getToVertex() != a){
        Vec3 zAxis(0,0,1);
        Vec3 v = -(normal.cross(zAxis));
        v.normalize();
        double dot = normal.dot(zAxis);
        double angle = acos(dot);

        double r[3][3] = {0};
        if (normal != zAxis){
            if (normal == -zAxis){
                v = Vec3(1,0,0);
            }
            Common::getRotationMatrix(v, angle, r);
        }
        else {
            r[0][0] = r[1][1] = r[2][2] = 1;
        }

        std::vector<Pointd> points;
        for (const Dcel::Vertex* v : incidentVertexIterator()){
            assert(v != nullptr && "Vertex is null.");
            Pointd p = v->getCoordinate();
            Pointd pr(p.x() * r[0][0] + p.y() * r[1][0] +p.z() * r[2][0], p.x() * r[0][1] + p.y() * r[1][1] +p.z() * r[2][1], p.x() * r[0][2] + p.y() * r[1][2] +p.z() * r[2][2]);
            points.push_back(pr);
        }
        double sum = 0;
        for (unsigned int i = 0; i < points.size(); i++){
            Pointd p1 = points[i];
            Pointd p2 = points[(i+1)%points.size()];
            sum += (p2.x() - p1.x()) * (p2.y()+p1.y());
        }
        if (sum > 0)
            normal = -normal;
    }
    parent->faceNormals[id] = normal;
    return normal;
}

/**
 * \~Italian
 * @brief Funzione che aggiorna l'area della faccia
 * @warning Funziona se e solo se la faccia è un triangolo
 * @warning Utilizza Dcel::Face::ConstIncidentVertexIterator
 * @return L'area della faccia aggiornata
 */
double Dcel::Face::updateArea() {
    updateNormal();
    if (isTriangle()) {
        assert(outerHalfEdge != nullptr && "Face's Outer HalfEdge is null.");
        assert(outerHalfEdge->getFromVertex() != nullptr && "HalfEdge's From Vertex is null.");
        assert(outerHalfEdge->getToVertex() != nullptr && "HalfEdge's To Vertex is null.");
        assert(outerHalfEdge->getPrev() != nullptr && "HalfEdge's prev is null.");
        assert(outerHalfEdge->getPrev()->getFromVertex() != nullptr && "HalfEdge's From Vertex is null.");
        Pointd v1 = outerHalfEdge->getFromVertex()->getCoordinate();
        Pointd v2 = outerHalfEdge->getToVertex()->getCoordinate();
        Pointd v3 = outerHalfEdge->getPrev()->getFromVertex()->getCoordinate();
        area = (((v3 - v1).cross(v2 - v1)).getLength() / 2);
    }
    #ifdef CG3_CGAL_DEFINED
    else {
        area = 0;
        std::vector<std::array<const Dcel::Vertex*, 3> > t;

        getTriangulation(t);
        for (unsigned int i = 0; i <t.size(); ++i){
            std::array<const Dcel::Vertex*, 3> tr =  t[i];
            assert(tr[0] != nullptr && "Vertex is null.");
            assert(tr[1] != nullptr && "Vertex is null.");
            assert(tr[2] != nullptr && "Vertex is null.");
            Pointd v1 = tr[0]->getCoordinate();
            Pointd v2 = tr[1]->getCoordinate();
            Pointd v3 = tr[2]->getCoordinate();
            area += (((v3 - v1).cross(v2 - v1)).getLength() / 2);
        }
    }
    #endif
    return area;
}

/**
 * \~Italian
 * @brief Funzione che rimuove un inner half edge dalla faccia
 * @param[in] iterator: iteratore che punta all'inner half edge da eliminare
 */
void Dcel::Face::removeInnerHalfEdge(const Face::InnerHalfEdgeIterator& iterator) {
    innerHalfEdges.erase(iterator);
}

/**
 * \~Italian
 * @brief Funzione che rimuove un inner half edge dalla faccia
 *
 * È meno efficiente rispetto a Dcel::Face::removeInnerHalfEdge(const Face::innerHalfEdgeIterator &ihe).
 *
 * @param[in] halfEdge: inner half edge da eliminare
 * @return True se la rimozione è andata a buon fine, false altrimenti.
 */
bool Dcel::Face::removeInnerHalfEdge(const Dcel::HalfEdge* halfEdge) {
    InnerHalfEdgeIterator i = std::find(innerHalfEdges.begin(), innerHalfEdges.end(), halfEdge);
    if (i != innerHalfEdges.end()){
        innerHalfEdges.erase(i);
        return true;
    }
    return false;
}

void Dcel::Face::removeAllInnerHalfEdges() {
    innerHalfEdges.clear();
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Dcel::Face::IncidentVertexIterator.
 *
 * Permette di ciclare sui vertici incidenti alla faccia, partendo dal vertice start. \n
 * È meno efficiente rispetto a Dcel::Face::incidentVertexBegin(const Dcel::HalfEdge* start).
 *
 * @param[in] start: vertice di partenza
 * @warning Se start non risulta essere incidente alla faccia (ossia non possiede un half edge incidente alla faccia),
 *          viene lanciata un'asserzione e il programma termina
 * @warning Utilizza Dcel::Vertex::ConstIncomingHalfEdgeIterator
 * @return Un iteratore che punta al vertice start
 */
Dcel::Face::IncidentVertexIterator Dcel::Face::incidentVertexBegin(Dcel::Vertex* start) {
    for (Dcel::HalfEdge* he : start->incomingHalfEdgeIterator()) {
    //for (Dcel::Vertex::ConstIncomingHalfEdgeIterator heit = start->incomingHalfEdgeBegin(), hend = start->incomingHalfEdgeEnd(); heit!= hend; ++heit) {
        assert(he != nullptr && "Half Edge is null.");
        if (he->getFace() == this) return IncidentVertexIterator(he, he, this);
    }
    assert(0 && "Start vertex is not incident to iterated face.");
    return IncidentVertexIterator();
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Dcel::Face::IncidentVertexIterator.
 *
 * Permette di ciclare sui vertici incidenti alla faccia, partendo dal vertice start e fino al vertice end. \n
 * È meno efficiente rispetto a Dcel::Face::incidentVertexBegin(const Dcel::HalfEdge* start, const Dcel::HalfEdge* end).
 *
 * @param[in] start: vertice di partenza
 * @param[in] end: vertice di arrivo, \b non \b compreso
 * @warning Se start e end non risultano essere incidenti alla faccia (ossia non possiedono un half edge incidente alla faccia),
 *          viene lanciata un'asserzione e il programma termina
 * @warning Utilizza Dcel::Vertex::ConstIncomingHalfEdgeIterator
 * @return Un iteratore che punta al vertice start
 */
Dcel::Face::IncidentVertexIterator Dcel::Face::incidentVertexBegin(Dcel::Vertex* start, Dcel::Vertex* end) {
    Vertex::IncomingHalfEdgeIterator heit = start->incomingHalfEdgeBegin(), hend = start->incomingHalfEdgeEnd();
    while (heit!= hend && ((*heit)->getFace() != this)) {
        ++heit;
        assert((heit == hend || (*heit) != nullptr) && "Half Edge is null.");
    }
    assert((*heit)->getFace() == this && "Start vertex is not incident to iterated face.");
    Dcel::HalfEdge* s = *heit;
    for (heit= end->incomingHalfEdgeBegin(), hend = end->incomingHalfEdgeEnd(); heit!= hend; ++heit){
        assert((*heit) != nullptr && "Half Edge is null.");
        if ((*heit)->getFace() == this) return IncidentVertexIterator(s, *heit, this);
    }
    assert(0 && "End vertex is not incident to iterated face.");
    return IncidentVertexIterator();
}


/*********************
 * Protected Methods *
 *********************/

/**
 * \~Italian
 * @brief Funzione che restituisce una stringa degli inner half edge
 * @return Una stringa rappresentativa degli inner half edge della faccia
 */
std::string Dcel::Face::innerComponentsToString() const {
    std::stringstream ss;
    ss << "(";
    for (unsigned int i=0; i<innerHalfEdges.size(); i++){
        if (innerHalfEdges[i] != nullptr) {
            if (i != 0) ss << "; ";
            ss << innerHalfEdges[i]->getId();
        }
        else ss << "nullptr";
    }
    ss << ")";
    std::string s1 = ss.str();
    return s1;
}


std::ostream&operator<<(std::ostream& inputStream, const Dcel::Face* f) {
    if (f == nullptr)
        inputStream << "null; ";
    else
        inputStream << f->toString() << "; ";
    return inputStream;
}

}

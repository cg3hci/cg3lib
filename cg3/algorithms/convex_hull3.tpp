/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */

#include "convex_hull3.h"
#include <Eigen/Dense>

namespace cg3 {


/* ----- INTERNAL FUNCTIONS DECLARATION ----- */

namespace internal {

inline double areCoplanar(const Point3d &p0, const Point3d &p1, const Point3d &p2, const Point3d &p3);

inline bool isFaceVisible(const Dcel::Face* f, const Point3d &p);

inline void insertTet(Dcel &dcel, const Point3d &p0, const Point3d &p1, const Point3d &p2, const Point3d &p3,
                      int flag0 = 0, int flag1 = 0, int flag2 = 0, int flag3 = 0);

inline void horizonEdgeList(std::vector<Dcel::HalfEdge*> &horizon, const std::set<Dcel::Face*>& visibleFaces, std::set<Dcel::Vertex*>& horizonVertex, const Point3d &next_point);

inline void calculateP(std::vector<std::set<Point3d> >& P, const BipartiteGraph<Point3d, unsigned int>& cg, std::vector<Dcel::HalfEdge*> &horizonEdges);

inline void deleteVisibleFaces(Dcel & ch, std::set<Dcel::Vertex*>& horizonVertices, const std::set<Dcel::Face*>& visibleFaces, BipartiteGraph<Point3d, unsigned int>& cg);

inline void insertNewFaces (Dcel & ch, std::vector<Dcel::HalfEdge*>& horizonEdges, const Point3d & p, BipartiteGraph<Point3d, unsigned int>& cg, std::vector<std::set<Point3d> > & P, int flagV = 0);

} //namespace cg3::internal



/* ----- IMPLEMENTATION OF CONVEX HULL 3D ----- */

inline Dcel convexHull(const Dcel& inputDcel)
{
    std::vector<Point3d> points;
    points.reserve(inputDcel.numberVertices());
    for (const Dcel::Vertex* v : inputDcel.vertexIterator()){
        points.push_back(v->coordinate());
    }
    return convexHull(points.begin(), points.end());
}

template <class InputContainer>
Dcel convexHull(const InputContainer& container)
{
    return convexHull(container.begin(), container.end());
}


template <class InputIterator>
Dcel convexHull(InputIterator first, InputIterator end)
{
    Dcel convexHull;
    BipartiteGraph<Point3d, unsigned int> cg;

    std::vector<Point3d> points(first, end);
    std::vector<uint> ids(points.size());
    for (uint i = 0; i < points.size(); ++i)
        ids[i] = i;

    if (points.size() > 3) {

        //std::random_shuffle(points.begin(), points.end());
        std::random_shuffle(ids.begin(), ids.end());

        double determinant = 0;
        unsigned int nPoints = (unsigned int)points.size();
        uint a, b, c, d;
        do {
            a = rand()%nPoints;
            b = rand()%nPoints;
            c = rand()%nPoints;
            d = rand()%nPoints;

            determinant = internal::areCoplanar(points[ids[a]], points[ids[b]], points[ids[c]], points[ids[d]]);
        } while (determinant == 0);
        std::swap(ids[0], ids[a]);
        std::swap(ids[1], ids[b]);
        std::swap(ids[2], ids[c]);
        std::swap(ids[3], ids[d]);

        if (determinant > 0)
            internal::insertTet(convexHull, points[ids[0]], points[ids[1]], points[ids[2]], points[ids[3]],
                    ids[0], ids[1], ids[2], ids[3]);
        else
            internal::insertTet(convexHull, points[ids[1]], points[ids[0]], points[ids[2]], points[ids[3]],
                    ids[1], ids[0], ids[2], ids[3]);

        for (Dcel::Face* f : convexHull.faceIterator()){
            cg.addRightNode(f->id());
        }


        for (unsigned int i = 4; i < points.size(); i++){
            cg.addLeftNode(points[ids[i]]);
            for (Dcel::Face* f : convexHull.faceIterator()){
                if (internal::isFaceVisible(f, points[ids[i]]))
                    cg.addArc(points[ids[i]], f->id());
            }
        }

        unsigned int iterations = 0;
        for (const Point3d& p : cg.leftNodeIterator()){ //For every point that is not inserted in the convex hull yet
            /**
             * Se il punto è interno al convex hull, nel conflict graph il nodo associato al punto non
             * ha archi uscenti: si ignora il punto.
             */
            if (cg.sizeAdjacencesLeftNode(p) > 0){

                /**
                 * Calcolo l'array (ordinato per face_id!) delle facce sul convex hull viste da next_point
                 */
                std::set<Dcel::Face*> visibleFaces;
                for (const unsigned int& f : cg.adjacentLeftNodeIterator(p)){
                    visibleFaces.insert(convexHull.face(f));
                }

                std::set<Dcel::Vertex*> horizonVertex;
                std::vector<Dcel::HalfEdge*> horizonEdges;

                /**
                 * Calcolo la lista ordinata degli edge che stanno sul boundary delle facce visibili (orizzonte)
                 */
                internal::horizonEdgeList(horizonEdges, visibleFaces, horizonVertex, p);

                /**
                 * Per ogni edge sull'orizzonte, calcolo i punti non ancora inseriti sul convex hull che vedono l'edge,
                 * ossia l'unione tra gli insiemi di punti che vedono le due facce adiacenti sull'edge.
                 * Sono tutti i possibili punti che potranno vedere la nuova faccia che verrà costruita unendo l'edge
                 * sull'orizzonte con next_point.
                 * P è quindi un array di array: ogni riga i corrisponde all'i-esimo elemento di horizon.
                 */
                std::vector< std::set<Point3d> > P;
                internal::calculateP(P, cg, horizonEdges);

                /**
                 * Rimuovo next_point dal conflict graph. è fondamentale farlo subito dopo aver rimosso le facce dal
                 * convex hull: vengono ricalcolati gli indici dei nodi esattamente come vengono ricalcolati quando
                 * viene rimosso un elemento dalla DCEL.
                 */
                cg.deleteLeftNode(p);

                /**
                 * Elimino dal convex hull tutte le facce di visible_faces e tutti gli half edge ed i vece ad esse
                 * incidenti, tranne i vertici che stanno sull'orizzonte.
                 */
                internal::deleteVisibleFaces(convexHull, horizonVertex, visibleFaces, cg);


                /**
                 * Inserisco le nuove facce nel convex hull, che andranno a collegare gli edge di horizon con
                 * next_point. Sempre in questa funzione vengono anche calcolati e aggiunti i nuovi conflitti
                 * tra le nuove facce e i punti presenti nel conflict graph.
                 */
                internal::insertNewFaces(convexHull, horizonEdges, p, cg, P, ids[iterations+4]);
            }
            else
                cg.deleteLeftNode(p);

            iterations++;
        }
        convexHull.updateFaceNormals();
        convexHull.updateVertexNormals();
        convexHull.updateBoundingBox();
    }
    return convexHull;
}


/* ----- INTERNAL FUNCTIONS IMPLEMENTATION ----- */

namespace internal {

inline double areCoplanar(const Point3d& p0, const Point3d& p1, const Point3d& p2, const Point3d& p3)
{
    Eigen::Matrix4d m;
    m << p0.x(), p0.y(), p0.z(), 1,
         p1.x(), p1.y(), p1.z(), 1,
         p2.x(), p2.y(), p2.z(), 1,
         p3.x(), p3.y(), p3.z(), 1;

    return m.determinant();
}

inline bool isFaceVisible(const Dcel::Face* f, const Point3d& p)
{
    Dcel::Face::ConstIncidentVertexIterator vit = f->incidentVertexBegin();
    Point3d p1 = (*vit)->coordinate();
    vit++;
    Point3d p2 = (*vit)->coordinate();
    vit++;
    Point3d p3 = (*vit)->coordinate();
    double determinant = areCoplanar(p1, p2, p3, p);

    if (determinant > std::numeric_limits<double>::epsilon()) return false;
    else return true;

}

inline void insertTet(Dcel& dcel, const Point3d& p0, const Point3d& p1, const Point3d& p2, const Point3d& p3,
                      int flag0, int flag1, int flag2, int flag3)
{
    Dcel::Vertex* v0 = dcel.addVertex(p0);
    Dcel::Vertex* v1 = dcel.addVertex(p1);
    Dcel::Vertex* v2 = dcel.addVertex(p2);
    Dcel::Vertex* v3 = dcel.addVertex(p3);

    v0->setFlag(flag0);
    v1->setFlag(flag1);
    v2->setFlag(flag2);
    v3->setFlag(flag3);

    Dcel::HalfEdge* e01 = dcel.addHalfEdge();
    e01->setFromVertex(v0);
    e01->setToVertex(v1);

    Dcel::HalfEdge* e12 = dcel.addHalfEdge();
    e12->setFromVertex(v1);
    e12->setToVertex(v2);

    Dcel::HalfEdge* e20 = dcel.addHalfEdge();
    e20->setFromVertex(v2);
    e20->setToVertex(v0);


    Dcel::HalfEdge* e10 = dcel.addHalfEdge();
    e10->setFromVertex(v1);
    e10->setToVertex(v0);

    Dcel::HalfEdge* e03 = dcel.addHalfEdge();
    e03->setFromVertex(v0);
    e03->setToVertex(v3);

    Dcel::HalfEdge* e31 = dcel.addHalfEdge();
    e31->setFromVertex(v3);
    e31->setToVertex(v1);


    Dcel::HalfEdge* e23 = dcel.addHalfEdge();
    e23->setFromVertex(v2);
    e23->setToVertex(v3);

    Dcel::HalfEdge* e30 = dcel.addHalfEdge();
    e30->setFromVertex(v3);
    e30->setToVertex(v0);

    Dcel::HalfEdge* e02 = dcel.addHalfEdge();
    e02->setFromVertex(v0);
    e02->setToVertex(v2);


    Dcel::HalfEdge* e21 = dcel.addHalfEdge();
    e21->setFromVertex(v2);
    e21->setToVertex(v1);

    Dcel::HalfEdge* e13 = dcel.addHalfEdge();
    e13->setFromVertex(v1);
    e13->setToVertex(v3);

    Dcel::HalfEdge* e32 = dcel.addHalfEdge();
    e32->setFromVertex(v3);
    e32->setToVertex(v2);

    Dcel::Face* f0 = dcel.addFace();
    f0->setOuterHalfEdge(e01);
    f0->setColor(Color(128,128,128));

    Dcel::Face* f1 = dcel.addFace();
    f1->setOuterHalfEdge(e10);
    f1->setColor(Color(128,128,128));

    Dcel::Face* f2 = dcel.addFace();
    f2->setOuterHalfEdge(e23);
    f2->setColor(Color(128,128,128));

    Dcel::Face* f3 = dcel.addFace();
    f3->setOuterHalfEdge(e21);
    f3->setColor(Color(128,128,128));

    v0->setIncidentHalfEdge(e01);
    v1->setIncidentHalfEdge(e10);
    v2->setIncidentHalfEdge(e23);
    v3->setIncidentHalfEdge(e32);

    e01->setTwin(e10);
    e01->setFace(f0);
    e01->setNext(e12);
    e01->setPrev(e20);

    e12->setTwin(e21);
    e12->setFace(f0);
    e12->setNext(e20);
    e12->setPrev(e01);

    e20->setTwin(e02);
    e20->setFace(f0);
    e20->setNext(e01);
    e20->setPrev(e12);

    e10->setTwin(e01);
    e10->setFace(f1);
    e10->setNext(e03);
    e10->setPrev(e31);

    e03->setTwin(e30);
    e03->setFace(f1);
    e03->setNext(e31);
    e03->setPrev(e10);

    e31->setTwin(e13);
    e31->setFace(f1);
    e31->setNext(e10);
    e31->setPrev(e03);

    e23->setTwin(e32);
    e23->setFace(f2);
    e23->setNext(e30);
    e23->setPrev(e02);

    e30->setTwin(e03);
    e30->setFace(f2);
    e30->setNext(e02);
    e30->setPrev(e23);

    e02->setTwin(e20);
    e02->setFace(f2);
    e02->setNext(e23);
    e02->setPrev(e30);

    e21->setTwin(e12);
    e21->setFace(f3);
    e21->setNext(e13);
    e21->setPrev(e32);

    e13->setTwin(e31);
    e13->setFace(f3);
    e13->setNext(e32);
    e13->setPrev(e21);

    e32->setTwin(e23);
    e32->setFace(f3);
    e32->setNext(e21);
    e32->setPrev(e13);

    dcel.updateFaceNormals();
    dcel.updateVertexNormals();
}

inline void horizonEdgeList(std::vector<Dcel::HalfEdge*>& horizon, const std::set<Dcel::Face*>& visibleFaces, std::set<Dcel::Vertex*>& horizonVertex, const Point3d& next_point)
{
    Dcel::HalfEdge* e0 = nullptr ,*e1;
    Dcel::HalfEdge* first_boundary_edge;
    Dcel::Face* adiacent_face;
    bool finded = false, sees;
    std::set<Dcel::Face*>::iterator fid = visibleFaces.begin();

    /** Ciclo di ricerca della Faccia sul boundary*/
    while (!finded){
        Dcel::Face* f = *fid;

        for (Dcel::Face::IncidentHalfEdgeIterator heit = f->incidentHalfEdgeBegin(); heit != f->incidentHalfEdgeEnd() && !finded; ++heit){
            e0 = *heit;
            e1 = e0->twin();
            adiacent_face = e1->face();
            sees=isFaceVisible(adiacent_face, next_point);
            if (!sees)
                finded = true;
        }
        ++fid;
        assert (fid != visibleFaces.end() || finded);
    }

    // alla fine del ciclo:
    // - e0: half edge interno alla faccia col bordo nell'orizzonte (incidente a faccia visibile)
    // - e1: halfedge esterno alla faccia col bordo nell'orizzonte (incidente a faccia non visibile)

    horizon.push_back(e1); // e1 è il primo edge sull'orizzonte
    horizonVertex.insert(e0->fromVertex());// inserisco il from vertex di e0 in horizon_vertex

    first_boundary_edge = e0;
    e0 = e0->next(); // e0 al passo successivo: next di e0
    do { // finchè non incontro nuovamente first_boundary_edge
        e1 = e0->twin(); // e1: twin di e0
        adiacent_face = e1->face(); // f: faccia incidente a e1
        sees=isFaceVisible(adiacent_face, next_point);
        if (!sees) { // se f è una faccia non visibile
            // Allora e0/e1 sono sull'orizzonte!
            horizon.push_back(e1);
            //he = convex_hull.get_half_edge(e0);
            horizonVertex.insert(e0->fromVertex());
            e0 = e0->next(); // e0 al passo successivo: next di e0
        }
        else { // altrimenti sono sul triangolo adiacente che non sta sull'orizzonte
            // devo continuare la ricerca stando sul from vertex di e0
            e0 = e1->next(); // e0 al passo successivo: next di e1
            // in questo caso, e1 è incidente ad una faccia visibile da next_point
            // in questo modo, sto girando sul from vertex di e0
        }
    } while (e0 != first_boundary_edge);
    // finché non ho ritrovaro il primo bordo
}

inline void calculateP(std::vector< std::set<Point3d> > &P, const BipartiteGraph<Point3d, unsigned int> &cg, std::vector<Dcel::HalfEdge*> &horizonEdges)
{
    Dcel::HalfEdge* he0, *he1;
    Dcel::Face* f0, *f1;

    P.clear();
    P.resize(horizonEdges.size());
    for (unsigned int i=0; i<horizonEdges.size(); i++){
        he0 = horizonEdges[i];
        he1 = he0->twin();
        f0 = he0->face();
        f1 = he1->face();
        // viene inserito in P[i] l'array ordinato contente i punti visibili da f0 e f1
        for (const Point3d& p : cg.adjacentRightNodeIterator(f0->id()))
            P[i].insert(p);
        for (const Point3d& p : cg.adjacentRightNodeIterator(f1->id()))
            P[i].insert(p);
    }
}

inline void deleteVisibleFaces(Dcel & ch, std::set<Dcel::Vertex*>& horizonVertices, const std::set<Dcel::Face*> &visibleFaces, BipartiteGraph<Point3d, unsigned int>& cg)
{
    std::set<Dcel::Vertex*> garbage_vertex;      // array di vertici da eliminare a fine computazione

    /**
     * Scorro le facce da eliminare, e elimino gli half edge ad esse incidenti e le facce.
     * Non elimino subito i vertici in quanto potrebbero essere condivisi tra più facce,
     * ed è fondamentale che ogni vertice venga eliminato una sola volta.
     */

    for (std::set<Dcel::Face*>::const_iterator it=visibleFaces.begin(); it!=visibleFaces.end(); ++it){
        Dcel::Face* f = *it;

        Dcel::HalfEdge* e1 = f->outerHalfEdge();
        Dcel::HalfEdge* e2 = e1->next();
        Dcel::HalfEdge* e3 = e2->next();
        Dcel::Vertex* v1 = e1->fromVertex();
        Dcel::Vertex* v2 = e1->toVertex();
        Dcel::Vertex* v3 = e2->toVertex();

        /**
         * Ogni volta che viene eliminato un elemento dalla DCEL, a tutti gli elementi dello stesso
         * tipo con indice maggiore dell'elemento eliminato, viene decrementato l'indice.
         * è quindi necessario, ogni volta che si elimina un elemento, è necessario aggiornare tutti
         * gli indici che fanno riferimento ad oggetti dello stesso tipo nella DCEL, decrementandoli
         * se hanno indice maggiore dell'indice dell'elemento eliminato.
         */

        /** eliminazione degli half_edge */
        ch.deleteHalfEdge(e1);

        ch.deleteHalfEdge(e2);

        ch.deleteHalfEdge(e3);

        /** eliminazione della faccia f */
        cg.deleteRightNode(f->id());
        ch.deleteFace(f);
        /** Salvo i vertici da eliminare nell'array garbage_vertex */

        if (horizonVertices.find(v1) == horizonVertices.end())
            garbage_vertex.insert(v1);
        if (horizonVertices.find(v2) == horizonVertices.end())
            garbage_vertex.insert(v2);
        if (horizonVertices.find(v3) == horizonVertices.end())
            garbage_vertex.insert(v3);
    }

    /** Elimino i vertici */
    for (std::set<Dcel::Vertex*>::iterator it = garbage_vertex.begin(); it != garbage_vertex.end(); ++it){
        ch.deleteVertex(*it);
    }
}

inline void insertNewFaces (Dcel & ch, std::vector<Dcel::HalfEdge*> & horizonEdges, const Point3d & p, BipartiteGraph<Point3d, unsigned int>& cg, std::vector<std::set<Point3d> >& P, int flagV)
{
    Dcel::Vertex* v3, *v1, *v2;                   // id di vertici della faccia inserita: v3 è SEMPRE l'id del nuovo punto inserito nel ch.
    Dcel::HalfEdge* e1, *e2, *e3;                     // id degli half edge della faccia inserita: e1 è il twin dell'edge sull'orizzonte
                                            //                                           e2 è il next di e1
                                            //                                           e3 è il prev di e1
    Dcel::HalfEdge* old_e2, *old_e3;                 // old_e2: e2 al passo precedente; old_e3: e3 al primo passo.
    Dcel::Face* f;                              // id della faccia inserita

    /**
     * Una volta costruiti gli half edge, devono essere aggiustate le relazioni di twin.
     * L'inserimeno delle facce è fatta in senso orario, quindi ad ogni passo si può collegare
     * il prev di e1 (e3) col next di e1 al passo precedente (old_e2).
     * Fa eccezione la prima faccia in quanto non vi è una faccia al passo precedente.
     * Si salva quindi il prev di e1 della prima faccia (old_e3) e lo si collega al next di e1
     * dell'ultima faccia (e2).
     */

    /** Inserisco il nuovo punto (v3) */
    v3 = ch.addVertex(p); // inserisco il nuovo punto
    v3->setFlag(flagV);

    /** Costruisco il primo  triangolo: */
    Dcel::HalfEdge* externHalfEdge = horizonEdges[0]; // edge sull'orizzonte
    /** Half Edge */
    // e1:
    v2 = externHalfEdge->fromVertex(); // v2: from di extern_he (to di e1!)
    v1 = externHalfEdge->toVertex(); // v1: to di extern_he (from di e1!)
    e1 = ch.addHalfEdge(); // e1: id half_edge twin di extern_he
    e1->setFromVertex(v1);
    e1->setToVertex(v2);

    // e2:
    e2 = ch.addHalfEdge(); // e2: id half_edge next di e1
    e2->setFromVertex(v2);
    e2->setToVertex(v3);

    // e3:
    e3 = ch.addHalfEdge(); // e3: id half_edge prev di e1
    e3->setFromVertex(v3);
    e3->setToVertex(v1);

    old_e3=e3; // e3 sarà il twin di e2 dell'ultima faccia

    // relazioni half_edge:
    e1->setNext(e2);
    e2->setNext(e3);
    e3->setNext(e1);
    e2->setPrev(e1);
    e3->setPrev(e2);
    e1->setPrev(e3);
    horizonEdges[0]->setTwin(e1);
    e1->setTwin(horizonEdges[0]);

    // faccia
    f = ch.addFace(); // f: id faccia inserita
    f->setOuterHalfEdge(e1);
    f->setColor(Color(128,128,128));

    // half edge incident face
    e1->setFace(f);
    e2->setFace(f);
    e3->setFace(f);

    // vertex incident edge
    v1->setIncidentHalfEdge(e1);
    v2->setIncidentHalfEdge(e2);
    v3->setIncidentHalfEdge(e3);

    cg.addRightNode(f->id()); // aggiungo f al conflict_graph

    /** CHECK VISIBILITà f */
    for (const Point3d& point: P[0]){
        if (isFaceVisible(f, point)){
            cg.addArc(point, f->id());
        }
    }

    //ad ogni ciclo, il twin del nuovo e3 è il vecchio e2.
    for (unsigned int i=1; i<horizonEdges.size(); i++){ // per ogni edge  sull'orizzonte
        old_e2 = e2; // salvo e2 del passo precedente
        externHalfEdge = horizonEdges[i]; // edge sull'orizzonte
        /** Half Edge */
        // e1:
        v2 = externHalfEdge->fromVertex(); // v2: from di extern_he (to di e1!)
        v1 = externHalfEdge->toVertex(); // v1: to di extern_he (from di e1!)
        e1 = ch.addHalfEdge(); // e1: id half_edge twin di extern_he
        e1->setFromVertex(v1);
        e1->setToVertex(v2);

        // e2:
        e2 = ch.addHalfEdge(); // e2: id half_edge next di e1
        e2->setFromVertex(v2);
        e2->setToVertex(v3);

        // e3:
        e3 = ch.addHalfEdge(); // e3: id half_edge prev di e1
        e3->setFromVertex(v3);
        e3->setToVertex(v1);

        // relazioni half edge:
        // relazioni half_edge:
        e1->setNext(e2);
        e2->setNext(e3);
        e3->setNext(e1);
        e2->setPrev(e1);
        e3->setPrev(e2);
        e1->setPrev(e3);
        horizonEdges[i]->setTwin(e1);
        e1->setTwin(horizonEdges[i]);
        e3->setTwin(old_e2);
        old_e2->setTwin(e3);

        //faccia
        f = ch.addFace(); // f: id faccia inserita
        f->setColor(Color(128,128,128));
        f->setOuterHalfEdge(e1);

        //half edge incident face
        e1->setFace(f);
        e2->setFace(f);
        e3->setFace(f);

        // vertex incident edge
        v1->setIncidentHalfEdge(e1);
        v2->setIncidentHalfEdge(e2);

        cg.addRightNode(f->id());

        /** CHECK VISIBILITà f */
        for (const Point3d& point: P[i]){
            if (isFaceVisible(f, point))
                cg.addArc(point, f->id()); // se point vede f, aggiungo il conflitto nel conflict graph
        }

    }

    e2->setTwin(old_e3);
    old_e3->setTwin(e2);
}

} //namespace cg3::internal
} //namespace cg3

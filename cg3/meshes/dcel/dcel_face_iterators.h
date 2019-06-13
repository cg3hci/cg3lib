/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "dcel_face.h"

namespace cg3 {

/**
 * \~Italian
 * @class Face::ConstInnerHalfEdgeIterator
 * @brief Iteratore che permette di ciclare sul vettore degli inner half edge associati alla faccia, garantendone
 * l'immutabilità.
 * Ogni inner half edge è associato ad un buco presente all'interno della faccia.
 * Una volta che si ha a disposizione un inner half edge, è possibile ciclare sul bordo del buco
 * mediante delle semplici operazioni di next, oppure utilizzando un ConstIncidentHalfEdgeIterator opportunamente inizializzato.
 *
 * È possibile utilizzare l'iteratore esattamente come si utilizza un iteratore su un std::vector.
 * Per esempio, data una faccia Face* f:
 *
 * \code{.cpp}
 * for (Face::ConstInnerHalfEdgeIterator heit = f->innerHalfEgeBegin(); heit != f->innerHalfEdgeEnd(); ++heit){
 *     const HalfEdge* he = *heit;
 *     // operazioni const su he
 * }
 * \endcode
 *
 * Questo iteratore garantisce l'immutabilità della faccia e quindi della Dcel a cui appartiene, e quindi è possibile
 * utilizzarlo solamente su const Face. Per poter effettuare modifiche, vedere Face::InnerHalfEdgeIterator.
 *
 * @author    Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
class Face::ConstInnerHalfEdgeIterator
{
    friend class Face;

public:
    //Constructors
    ConstInnerHalfEdgeIterator() {};
    ConstInnerHalfEdgeIterator(const Face::InnerHalfEdgeIterator& it) : iterator(it){};

    //Public Operators
    const HalfEdge* operator * () const {return *iterator;};
    bool operator == (const ConstInnerHalfEdgeIterator& oit) const {return iterator == oit.iterator;};
    bool operator != (const ConstInnerHalfEdgeIterator& oit) const {return iterator != oit.iterator;};

    ConstInnerHalfEdgeIterator operator ++ () {return ++iterator;};
    ConstInnerHalfEdgeIterator operator ++ (int) {auto old = iterator; ++iterator; return old;};
    ConstInnerHalfEdgeIterator operator -- () {return --iterator;};
    ConstInnerHalfEdgeIterator operator -- (int) {auto old = iterator; --iterator; return old;};

protected:
    //Protected Attributes
    std::vector<HalfEdge*>::const_iterator iterator; /**< \~Italian @brief Iteratore vero e proprio sul vettore degli inner half edge della faccia. */

    //Protected Constructor
    ConstInnerHalfEdgeIterator(const std::vector<HalfEdge*>::const_iterator& it) : iterator(it){};
};

class Face::GenericIterator
{
    friend class Face;

public:
    //Constructor
    GenericIterator() : f(nullptr), start(nullptr), pos(nullptr), end(nullptr){};

    //Public Operators
    void* operator * () const {return nullptr;}
    bool operator == (const GenericIterator& otherIterator) const {return pos == otherIterator.pos && f == otherIterator.f;};
    bool operator != (const GenericIterator& otherIterator) const {return !(*this == otherIterator);};

    GenericIterator operator ++ () {pos = pos->next(); if (pos == end) pos = nullptr; return *this;};
    GenericIterator operator ++ (int) {GenericIterator old_value = *this; pos = pos->next(); if (pos == end) pos = nullptr; return old_value;};
    GenericIterator operator -- () {pos = pos->prev(); if (pos == end) pos = nullptr; return *this;};
    GenericIterator operator -- (int) {GenericIterator old_value = *this; pos = pos->prev(); if (pos == end) pos = nullptr; return old_value;};

protected:
    //Protected Attributes
    Face*     f;      /**< \~Italian @brief Faccia su cui vengono iterati gli half edge incidenti */
    HalfEdge* start;  /**< \~Italian @brief Half edge dal quale è partito l'iteratore */
    HalfEdge* pos;    /**< \~Italian @brief Posizione attuale dell'iteratore */
    HalfEdge* end;    /**< \~Italian @brief Half edge sul quale termina l'iteratore */

    //Protected Constructor
    GenericIterator(HalfEdge* start, HalfEdge* end, Face* f) : f(f), start(start), pos(start), end(end){};
};

class Face::ConstGenericIterator
{
    friend class Face;

public:
    //Constructors
    ConstGenericIterator() : f(nullptr), start(nullptr), pos(nullptr), end(nullptr){};
    ConstGenericIterator(const Face::GenericIterator& it) : f(it.f), start(it.start), pos(it.pos), end(it.end) {};

    //Public Operators
    const void* operator * () const {return nullptr;}
    bool operator == (const ConstGenericIterator& otherIterator) const {return pos == otherIterator.pos && f == otherIterator.f;};
    bool operator != (const ConstGenericIterator& otherIterator) const {return !(*this == otherIterator);};

    ConstGenericIterator operator ++ () {pos = pos->next(); if (pos == end) pos = nullptr; return *this;};
    ConstGenericIterator operator ++ (int) {ConstGenericIterator old_value = *this; pos = pos->next(); if (pos == end) pos = nullptr; return old_value;};
    ConstGenericIterator operator -- () {pos = pos->prev(); if (pos == end) pos = nullptr; return *this;};
    ConstGenericIterator operator -- (int) {ConstGenericIterator old_value = *this; pos = pos->prev(); if (pos == end) pos = nullptr; return old_value;};
;

protected:
    //Protected Attributes
    const Face*     f;        /**< \~Italian @brief Faccia su cui vengono iterati gli half edge incidenti */
    const HalfEdge* start;    /**< \~Italian @brief Half edge dal quale è partito l'iteratore */
    const HalfEdge* pos;      /**< \~Italian @brief Posizione attuale dell'iteratore */
    const HalfEdge* end;      /**< \~Italian @brief Half edge sul quale termina l'iteratore */

    //Protected Constructor
    ConstGenericIterator(const HalfEdge* start, const HalfEdge* end, const Face* f) : f(f), start(start), pos(start), end(end){};
};


/**
 * \~Italian
 * @class Face::AdjacentFaceIterator
 * @brief Iteratore che permette di ciclare sulle facce adiacenti ad una faccia.
 *
 * Partendo da un half edge di start e un half edge di end (non compreso), entrambi
 * incidenti alla faccia su cui è inizializzato l'iteratore, permette di
 * ciclare su tutte le facce indcidenti ai twin compresi tra start e end. \n
 *
 * Le operazioni di incremento eseguono un'operazione \c next() sull'half edge,
 * le operazioni di decremento eseguono un'operazione di \c prev() , e l'operazione di
 * dereferenziazione restituisce l'incidentFace del twin dell'half edge.
 *
 * Per questi motivi, utilizzare questo iteratore solamente quando tutti gli half edge incidenti
 * hanno settato correttamente le seguenti relazioni:
 * - next (per le operazioni di incremento)
 * - prev (per le operazioni di decremento)
 * - twin (sia per operazioni di incremento che per operazioni di decremento)
 * Inoltre, ogni twin degli half edge ciclati deve avere settata correttamente la sua faccia incidente.
 *
 * Più precisamente, è necessario che una volta effettuate diverse operazioni di next (o prev), si arrivi
 * di nuovo all'half edge di partenza (o a un eventuale halg edge finale settato all'inizializzazione).
 *
 * È possibile utilizzare l'iteratore in diversi modi. Il più semplice è ciclare in senso antiorario o orario (operatore \--)
 * su tutti gli half edge incidenti ad una data faccia \c f. In questo caso, sarà sufficiente scrivere:
 *
 * \code{.cpp}
 * for (Face::AdjacentFaceIterator fit = f->adjacentFaceBegin(); fit != f->adjacentFaceEnd(); ++fit){
 *     Face* f = *fit;
 *     // operazioni su f
 * }
 * \endcode
 *
 * È però possibile anche visitare tutte le facce adiacenti comprese tra due dati half edge. In questo caso sarà necessario
 * passare gli half edge estremi dell'intervallo all'inizializzatore Face::adjacentFaceBegin(). Per i dettagli su come funzionano queste
 * inizializzazioni si rimanda alla descrizione dei metodi stessi.
 *
 * Questo iteratore non garantisce l'immutabilità della faccia e quindi della Dcel a cui appartiene, e quindi non è possibile
 * utilizzarlo su const Face. Per const Face, vedere Face::ConstAdjacentFaceIterator.
 *
 * @author    Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
class Face::AdjacentFaceIterator : public Face::GenericIterator
{
    friend class Face;

public:
    //Constructor
    AdjacentFaceIterator() : GenericIterator(){};

    //Public Operators
    Face* operator * () const {return pos->twin()->face();};

protected:
    //Protected Constructor
    AdjacentFaceIterator(HalfEdge* start, HalfEdge* end, Face* f) : GenericIterator(start, end, f){};
};

/**
 * \~Italian
 * @class Face::ConstAdjacentFaceIterator
 * @brief Iteratore che permette di ciclare sulle facce adiacenti ad una faccia, garantendone l'immutabilità.
 *
 * Partendo da un half edge di start e un half edge di end (non compreso), entrambi
 * incidenti alla faccia su cui è inizializzato l'iteratore, permette di
 * ciclare su tutte le facce indcidenti ai twin compresi tra start e end. \n
 *
 * Le operazioni di incremento eseguono un'operazione \c next() sull'half edge,
 * le operazioni di decremento eseguono un'operazione di \c prev() , e l'operazione di
 * dereferenziazione restituisce l'incidentFace del twin dell'half edge.
 *
 * Per questi motivi, utilizzare questo iteratore solamente quando tutti gli half edge incidenti
 * hanno settato correttamente le seguenti relazioni:
 * - next (per le operazioni di incremento)
 * - prev (per le operazioni di decremento)
 * - twin (sia per operazioni di incremento che per operazioni di decremento)
 * Inoltre, ogni twin degli half edge ciclati deve avere settata correttamente la sua faccia incidente.
 *
 * Più precisamente, è necessario che una volta effettuate diverse operazioni di next (o prev), si arrivi
 * di nuovo all'half edge di partenza (o a un eventuale halg edge finale settato all'inizializzazione).
 *
 * È possibile utilizzare l'iteratore in diversi modi. Il più semplice è ciclare in senso antiorario o orario (operatore \--)
 * su tutti gli half edge incidenti ad una data faccia \c f. In questo caso, sarà sufficiente scrivere:
 *
 * \code{.cpp}
 * for (Face::AdjacentFaceIterator fit = f->adjacentFaceBegin(); fit != f->adjacentFaceEnd(); ++fit){
 *     Face* f = *fit;
 *     // operazioni su f
 * }
 * \endcode
 *
 * È però possibile anche visitare tutte le facce adiacenti comprese tra due dati half edge. In questo caso sarà necessario
 * passare gli half edge estremi dell'intervallo all'inizializzatore Face::adjacentFaceBegin(). Per i dettagli su come funzionano queste
 * inizializzazioni si rimanda alla descrizione dei metodi stessi.
 *
 * Questo iteratore garantisce l'immutabilità della faccia e quindi della Dcel a cui appartiene, e quindi si può utilizzare solo
 * su const Face. Per Face, vedere Face::AdjacentFaceIterator.
 *
 * @author    Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
class Face::ConstAdjacentFaceIterator : public Face::ConstGenericIterator
{
    friend class Face;

public:
    //Constructors
    ConstAdjacentFaceIterator() : ConstGenericIterator(){};
    ConstAdjacentFaceIterator(const Face::AdjacentFaceIterator& it) : ConstGenericIterator(it){};

    //Public Operators
    const Face* operator * () const {return pos->twin()->face();};

protected:

    //Protected Constructor
    ConstAdjacentFaceIterator(const HalfEdge* start, const HalfEdge* end, const Face* f) : ConstGenericIterator(start, end, f){};
};

/**
 * \~Italian
 * @class Face::IncidentHalfEdgeIterator
 * @brief Iteratore che permette di ciclare sugli half edge incidenti ad una faccia.
 *
 * Partendo da un half edge di start e un half edge di end (non compreso), entrambi
 * incidenti alla faccia su cui è inizializzato l'iteratore, permette di
 * ciclare su tutti gli half edge compresi tra start e end. \n
 *
 * Le operazioni di incremento eseguono un'operazione \c next() sull'half edge,
 * mentre le operazioni di decremento eseguono un'operazione di \c prev().
 *
 * Per questi motivi, utilizzare questo iteratore solamente quando tutti gli half edge incidenti
 * hanno settato correttamente le seguenti relazioni:
 * - next (per le operazioni di incremento)
 * - prev (per le operazioni di decremento)
 *
 * Più precisamente, è necessario che una volta effettuate diverse operazioni di next (o prev), si arrivi
 * di nuovo all'half edge di partenza (o a un eventuale halg edge finale settato all'inizializzazione).
 *
 * È possibile utilizzare l'iteratore in diversi modi. Il più semplice è ciclare in senso antiorario o orario (operatore \--)
 * su tutti gli half edge incidenti ad una data faccia \c f. In questo caso, sarà sufficiente scrivere:
 *
 * \code{.cpp}
 * for (Face::IncidentHalfEdgeIterator heit = f->incidentHalfEdgeBegin(); heit != f->incidentHalfEdgeEnd(); ++heit){
 *     HalfEdge* he = *heit;
 *     // operazioni su he
 * }
 * \endcode
 *
 * È però possibile anche visitare tutti gli half edge incidenti compresi tra due dati half edge. In questo caso sarà necessario
 * passare gli half edge estremi dell'intervallo all'inizializzatore Face::incidentHalfEdgeBegin(). Per i dettagli su come funzionano queste
 * inizializzazioni si rimanda alla descrizione dei metodi stessi.
 *
 * Questo iteratore non garantisce l'immutabilità della faccia e quindi della Dcel a cui appartiene, e quindi non è possibile
 * utilizzarlo su const Face. Per const Face, vedere Face::ConstIncidentHalfEdgeIterator.
 *
 * @author    Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
class Face::IncidentHalfEdgeIterator : public Face::GenericIterator
{
    friend class Face;

public:
    // Constructor
    IncidentHalfEdgeIterator() : GenericIterator(){};

    //Public Operators
    HalfEdge* operator * () const {return pos;};

protected:

    //Protected Constructor
    IncidentHalfEdgeIterator(HalfEdge* start, HalfEdge* end, Face* f) : GenericIterator(start, end, f){};
};

/**
 * \~Italian
 * @class Face::ConstIncidentHalfEdgeIterator
 * @brief Iteratore che permette di ciclare sugli half edge incidenti ad una faccia, garantendone l'immutabilità.
 *
 * Partendo da un half edge di start e un half edge di end (non compreso), entrambi
 * incidenti alla faccia su cui è inizializzato l'iteratore, permette di
 * ciclare su tutti gli half edge compresi tra start e end. \n
 *
 * Le operazioni di incremento eseguono un'operazione \c next() sull'half edge,
 * mentre le operazioni di decremento eseguono un'operazione di \c prev().
 *
 * Per questi motivi, utilizzare questo iteratore solamente quando tutti gli half edge incidenti
 * hanno settato correttamente le seguenti relazioni:
 * - next (per le operazioni di incremento)
 * - prev (per le operazioni di decremento)
 *
 * Più precisamente, è necessario che una volta effettuate diverse operazioni di next (o prev), si arrivi
 * di nuovo all'half edge di partenza (o a un eventuale halg edge finale settato all'inizializzazione).
 *
 * È possibile utilizzare l'iteratore in diversi modi. Il più semplice è ciclare in senso antiorario o orario (operatore \--)
 * su tutti gli half edge incidenti ad una data faccia \c f. In questo caso, sarà sufficiente scrivere:
 *
 * \code{.cpp}
 * for (Face::ConstIncidentHalfEdgeIterator heit = f->incidentHalfEdgeBegin(); heit != f->incidentHalfEdgeEnd(); ++heit){
 *     const HalfEdge* he = *heit;
 *     // operazioni const su he
 * }
 * \endcode
 *
 * È però possibile anche visitare tutti gli half edge incidenti compresi tra due dati half edge. In questo caso sarà necessario
 * passare gli half edge estremi dell'intervallo all'inizializzatore Face::incidentHalfEdgeBegin(). Per i dettagli su come funzionano queste
 * inizializzazioni si rimanda alla descrizione dei metodi stessi.
 *
 * Questo iteratore garantisce l'immutabilità della faccia e quindi della Dcel a cui appartiene, e quindi si può utilizzare solo
 * su const Face. Per Face, vedere Face::IncidentHalfEdgeIterator.
 *
 * @author    Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
class Face::ConstIncidentHalfEdgeIterator : public Face::ConstGenericIterator
{
        friend class Face;

    public:
        //Constructors
        ConstIncidentHalfEdgeIterator() : ConstGenericIterator(){};
        ConstIncidentHalfEdgeIterator(const Face::IncidentHalfEdgeIterator& it) :ConstGenericIterator(it){};

        //Public Operators
        const HalfEdge* operator * () const {return pos;};

    protected:

        //Protected Constructor
        ConstIncidentHalfEdgeIterator(const HalfEdge* start, const HalfEdge* end, const Face* f) : ConstGenericIterator(start, end, f){};
};

/**
 * \~Italian
 * @class Face::IncidentVertexIterator
 * @brief Iteratore che permette di ciclare sui vertici incidenti ad una faccia.
 *
 * Partendo da un half edge di start e un half edge di end (non compreso), entrambi
 * incidenti alla faccia su cui è inizializzato l'iteratore, permette di
 * ciclare su tutti i to vertex compresi tra start e end. \n
 *
 * Le operazioni di incremento eseguono un'operazione \c next() sull'half edge,
 * le operazioni di decremento eseguono un'operazione di \c prev() , e l'operazione di
 * dereferenziazione restituisce il toVertex dell'half edge.
 *
 * Per questi motivi, utilizzare questo iteratore solamente quando tutti gli half edge incidenti
 * hanno settato correttamente le seguenti relazioni:
 * - next (per le operazioni di incremento)
 * - prev (per le operazioni di decremento)
 * - to vertex (sia per operazioni di incremento che per operazioni di decremento)
 *
 * Più precisamente, è necessario che una volta effettuate diverse operazioni di next (o prev), si arrivi
 * di nuovo all'half edge di partenza (o a un eventuale halg edge finale settato all'inizializzazione).
 *
 * È possibile utilizzare l'iteratore in diversi modi. Il più semplice è ciclare in senso antiorario o orario (operatore \--)
 * su tutti gli half edge incidenti ad una data faccia \c f. In questo caso, sarà sufficiente scrivere:
 *
 * \code{.cpp}
 * for (Face::IncidentVertexIterator vit = f->incidentVertexBegin(); vit != f->incidentVertexEnd(); ++vit){
 *     Vertex* v = *vit;
 *     // operazioni su v
 * }
 * \endcode
 *
 * È però possibile anche visitare tutti i vertici incidenti compresi tra due dati half edge. In questo caso sarà necessario
 * passare gli half edge estremi dell'intervallo all'inizializzatore Face::incidentVertexBegin(). Per i dettagli su come funzionano queste
 * inizializzazioni si rimanda alla descrizione dei metodi stessi.
 *
 * Questo iteratore non garantisce l'immutabilità della faccia e quindi della Dcel a cui appartiene, e quindi non è possibile
 * utilizzarlo su const Face. Per const Face, vedere Face::ConstIncidentVertexIterator.
 *
 * @author    Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
class Face::IncidentVertexIterator : public Face::GenericIterator
{
        friend class Face;

    public:
        //Constructor
        IncidentVertexIterator() : GenericIterator() {};

        //Public Operators
        Vertex* operator * () const {return pos->toVertex();};

    protected:

        //Protected Constructor
        IncidentVertexIterator(HalfEdge* start, HalfEdge* end, Face* f) : GenericIterator(start, end, f){};
};

/**
 * \~Italian
 * @class Face::ConstIncidentVertexIterator
 * @brief Iteratore che permette di ciclare sui vertici incidenti ad una faccia, garantendone l'immutabilità.
 *
 * Partendo da un half edge di start e un half edge di end (non compreso), entrambi
 * incidenti alla faccia su cui è inizializzato l'iteratore, permette di
 * ciclare su tutti i to vertex compresi tra start e end. \n
 *
 * Le operazioni di incremento eseguono un'operazione \c next() sull'half edge,
 * le operazioni di decremento eseguono un'operazione di \c prev() , e l'operazione di
 * dereferenziazione restituisce il toVertex dell'half edge.
 *
 * Per questi motivi, utilizzare questo iteratore solamente quando tutti gli half edge incidenti
 * hanno settato correttamente le seguenti relazioni:
 * - next (per le operazioni di incremento)
 * - prev (per le operazioni di decremento)
 * - to vertex (sia per operazioni di incremento che per operazioni di decremento)
 *
 * Più precisamente, è necessario che una volta effettuate diverse operazioni di next (o prev), si arrivi
 * di nuovo all'half edge di partenza (o a un eventuale halg edge finale settato all'inizializzazione).
 *
 * È possibile utilizzare l'iteratore in diversi modi. Il più semplice è ciclare in senso antiorario o orario (operatore \--)
 * su tutti gli half edge incidenti ad una data faccia \c f. In questo caso, sarà sufficiente scrivere:
 *
 * \code{.cpp}
 * for (Face::ConstIncidentVertexIterator vit = f->incidentVertexBegin(); vit != f->incidentVertexEnd(); ++vit){
 *     const Vertex* v = *vit;
 *     // operazioni const su v
 * }
 * \endcode
 *
 * È però possibile anche visitare tutti i vertici incidenti compresi tra due dati half edge. In questo caso sarà necessario
 * passare gli half edge estremi dell'intervallo all'inizializzatore Face::incidentVertexBegin(). Per i dettagli su come funzionano queste
 * inizializzazioni si rimanda alla descrizione dei metodi stessi.
 *
 * Questo iteratore garantisce l'immutabilità della faccia e quindi della Dcel a cui appartiene, e quindi è possibile utilizzarlo solamente
 * su const Face. Per Face, vedere Face::IncidentVertexIterator.
 *
 * @author    Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
class Face::ConstIncidentVertexIterator : public Face::ConstGenericIterator
{
    friend class Face;

public:
    //Constructors
    ConstIncidentVertexIterator() : ConstGenericIterator(){};
    ConstIncidentVertexIterator(const Face::IncidentVertexIterator& it) : ConstGenericIterator(it){};

    //Public Operators
    const Vertex* operator * () const {return pos->toVertex();};

protected:

    //Protected Constructor
    ConstIncidentVertexIterator(const HalfEdge* start, const HalfEdge* end, const Face* f) : ConstGenericIterator(start, end, f){};
};

class Face::ConstInnerHalfEdgeRangeBasedIterator
{
        friend class Face;
    public:
        Face::ConstInnerHalfEdgeIterator begin() const {return f->innerHalfEdgeBegin();};
        Face::ConstInnerHalfEdgeIterator end() const {return f->innerHalfEdgeEnd();};
    private:
        ConstInnerHalfEdgeRangeBasedIterator(const Face *f) : f(f) {}
        const Face *f;
};

class Face::ConstAdjacentFaceRangeBasedIterator
{
        friend class Face;
    public:
        Face::ConstAdjacentFaceIterator begin() const {return f->adjacentFaceBegin();};
        Face::ConstAdjacentFaceIterator end() const {return f->adjacentFaceEnd();};
    private:
        ConstAdjacentFaceRangeBasedIterator(const Face *f) : f(f) {}
        const Face *f;
};

class Face::ConstIncidentHalfEdgeRangeBasedIterator
{
        friend class Face;
    public:
        Face::ConstIncidentHalfEdgeIterator begin() const {return f->incidentHalfEdgeBegin();};
        Face::ConstIncidentHalfEdgeIterator end() const {return f->incidentHalfEdgeEnd();};
    private:
        ConstIncidentHalfEdgeRangeBasedIterator(const Face *f) : f(f) {}
        const Face *f;
};

class Face::ConstIncidentVertexRangeBasedIterator
{
        friend class Face;
    public:
        Face::ConstIncidentVertexIterator begin() const {return f->incidentVertexBegin();};
        Face::ConstIncidentVertexIterator end() const {return f->incidentVertexEnd();};
    private:
        ConstIncidentVertexRangeBasedIterator(const Face *f) : f(f) {}
        const Face *f;
};

class Face::InnerHalfEdgeRangeBasedIterator
{
        friend class Face;
    public:
        Face::InnerHalfEdgeIterator begin() {return f->innerHalfEdgeBegin();};
        Face::InnerHalfEdgeIterator end() {return f->innerHalfEdgeEnd();};
    private:
        InnerHalfEdgeRangeBasedIterator(Face *f) : f(f) {}
        Face *f;
};

class Face::AdjacentFaceRangeBasedIterator
{
        friend class Face;
    public:
        Face::AdjacentFaceIterator begin() {return f->adjacentFaceBegin();};
        Face::AdjacentFaceIterator end() {return f->adjacentFaceEnd();};
    private:
        AdjacentFaceRangeBasedIterator(Face *f) : f(f) {}
        Face *f;
};

class Face::IncidentHalfEdgeRangeBasedIterator
{
        friend class Face;
    public:
        Face::IncidentHalfEdgeIterator begin() {return f->incidentHalfEdgeBegin();};
        Face::IncidentHalfEdgeIterator end() {return f->incidentHalfEdgeEnd();};
    private:
        IncidentHalfEdgeRangeBasedIterator(Face *f) : f(f) {}
        Face *f;
};

class Face::IncidentVertexRangeBasedIterator
{
        friend class Face;
    public:
        Face::IncidentVertexIterator begin() {return f->incidentVertexBegin();};
        Face::IncidentVertexIterator end() {return f->incidentVertexEnd();};
    private:
        IncidentVertexRangeBasedIterator(Face *f) : f(f) {}
        Face *f;
};

} //namespace cg3

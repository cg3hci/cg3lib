/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "dcel_vertex.h"

namespace cg3 {

class Vertex::GenericIterator
{
    friend class Vertex;

public:
    //Constructor
    GenericIterator() {};

    //Public Operators
    void* operator * () const {return nullptr;}
    bool operator == (const GenericIterator& right) const {return pos == right.pos && v == right.v;};
    bool operator != (const GenericIterator& right) const {return !(*this == right);};

	GenericIterator operator ++ () {
		if (pos->twin() == nullptr) pos = nullptr;
		else {
			pos = pos->twin()->next();
			if (pos == end) pos = nullptr;
		}
		return *this;
	};
	GenericIterator operator ++ (int) {
		GenericIterator old_value = *this;
		if (pos->twin() == nullptr) pos = nullptr;
		else {
			pos = pos->twin()->next();
			if (pos == end) pos = nullptr;
		}
		return old_value;
	};
	GenericIterator operator -- () {
		if (pos->prev() == nullptr) pos = nullptr;
		else {
			pos = pos->prev()->twin();
			if (pos == end) pos = nullptr;
		}
		return *this;
	};
	GenericIterator operator -- (int) {
		GenericIterator old_value = *this;
		if (pos->prev() == nullptr) pos = nullptr;
		else {
			pos = pos->prev()->twin();
			if (pos == end) pos = nullptr;
		}
		return old_value;
	};

protected:
    //Protected Attributes
    Vertex*   v;      /**< \~Italian @brief Vertice su cui vengono iterati i vertici adiacenti */
    HalfEdge* start;  /**< \~Italian @brief Half edge dal quale è partito l'iteratore */
    HalfEdge* pos;    /**< \~Italian @brief Posizione attuale dell'iteratore */
    HalfEdge* end;    /**< \~Italian @brief Half edge sul quale termina l'iteratore */

    //Protected Constructor
    GenericIterator(HalfEdge* start, HalfEdge* end, Vertex* v) : v(v), start(start), pos(start), end(end){};
};

class Vertex::ConstGenericIterator
{
    friend class Vertex;

public:
    //Constructors
    ConstGenericIterator() {};
    ConstGenericIterator(const Vertex::GenericIterator& it) : v(it.v), start(it.start), pos(it.pos), end(it.end) {};

    //Public Operators
    const void* operator * () const {return nullptr;}
    bool operator == (const ConstGenericIterator& right) const {return pos == right.pos && v == right.v;};
    bool operator != (const ConstGenericIterator& right) const {return !(*this == right);};

	ConstGenericIterator operator ++ () {
		if (pos->twin() == nullptr) pos = nullptr;
		else {
			pos = pos->twin()->next();
			if (pos == end) pos = nullptr;
		}
		return *this;
	};
	ConstGenericIterator operator ++ (int) {
		ConstGenericIterator old_value = *this;
		if (pos->twin() == nullptr) pos = nullptr;
		else {
			pos = pos->twin()->next();
			if (pos == end) pos = nullptr;
		}
		return old_value;
	};
	ConstGenericIterator operator -- () {
		if (pos->prev() == nullptr) pos = nullptr;
		else {
			pos = pos->prev()->twin();
			if (pos == end) pos = nullptr;
		}
		return *this;
	};
	ConstGenericIterator operator -- (int) {
		ConstGenericIterator old_value = *this;
		if (pos->prev() == nullptr) pos = nullptr;
		else {
			pos = pos->prev()->twin();
			if (pos == end) pos = nullptr;
		}
		return old_value;
	};

protected:
    //Protected Attributes
    const Vertex*   v;        /**< \~Italian @brief Vertice su cui vengono iterati i vertici adiacenti */
    const HalfEdge* start;    /**< \~Italian @brief Half edge dal quale è partito l'iteratore */
    const HalfEdge* pos;      /**< \~Italian @brief Posizione attuale dell'iteratore */
    const HalfEdge* end;      /**< \~Italian @brief Half edge sul quale termina l'iteratore */

    //Protected Constructor
    ConstGenericIterator(const HalfEdge* start, const HalfEdge* end, const Vertex* v): v(v), start(start), pos(start), end(end){};
};

/**
 * \~Italian
 * @class Vertex::AdjacentVertexIterator
 * @brief Iteratore che permette di ciclare sui vertici adiacenti ad un vertice.
 *
 * Partendo da un half edge start e un half edge end (non compreso), entrambi incidenti e uscenti
 * dal vertice su cui è inizializzaro l'iteratore, permette di ciclare su tutti i toVertex degli
 * half edge uscenti compresi tra start e end (ossia di ciclare sui vertici adiacenti). \n
 *
 * Le operazioni di incremento eseguono le due operazioni di \c prev() e \c twin() sull'half edge,
 * le operazioni di decremento eseguono le due operazioni di \c twin() e \c next() sull'half edge,
 * e l'operazione di dereferenziazione restituisce il toVertex dell'half edge puntato dall'iteratore.
 *
 * Per questi motivi, utilizzare questo iteratore solamente quando tutti gli half edge incidenti
 * (entranti e uscenti) hanno settato correttamente le seguenti relazioni di incidenza:
 * - from vertex (per gli uscenti deve essere il vertice su cui si itera)
 * - to vertex (per gli entranti deve essere il vertice su cui si itera)
 * - twin (sia per le operazioni di incremento che per quelle di decremento)
 * - next (per le operazioni di incremento)
 * - prev (per le operazioni di decremento)
 *
 * È possibile utilizzare l'iteratore in diversi modi. Il più semplice è ciclare in senso antiorario (operatore \++) o orario (operatore \--)
 * su tutti i vertici adiacenti ad un dato vertice \c v. In questo caso, sarà sufficiente scrivere:
 *
 * \code{.cpp}
 * for (Vertex::AdjacentVertexIterator vit = v->adjacentVertexBegin(); vit != v->adjacentVertexEnd(); ++vit){
 *     Vertex* av = *vit;
 *     // operazioni su av
 * }
 * \endcode
 *
 * È però possibile anche visitare tutti i vertici adiacenti compresi tra due dati vertici adiacenti. In questo caso sarà necessario
 * passare i vertici estremi dell'intervallo all'inizializzatore Vertex::adjacentVertexBegin(). Per i dettagli su come funzionano queste
 * inizializzazioni si rimanda alla descrizione dei metodi stessi.
 *
 * Questo iteratore non garantisce l'immutabilità del vertice e quindi della Dcel a cui appartiene, e quindi non è possibile
 * utilizzarlo su const Vertex. Per const Vertex, vedere Vertex::ConstAdjacentVertexIterator.
 */
class Vertex::AdjacentVertexIterator : public Vertex::GenericIterator
{
    friend class Vertex;

public:
    //Constructor
    AdjacentVertexIterator() : GenericIterator(){};

    //Public Operators
    Vertex* operator * () const {return pos->toVertex();};

protected:

    //Protected Constructor
    AdjacentVertexIterator(HalfEdge* start, HalfEdge* end, Vertex* v) : GenericIterator(start, end, v){};
};

/**
 * \~Italian
 * @class Vertex::ConstAdjacentVertexIterator
 * @brief Iteratore che permette di ciclare sui vertici adiacenti ad un vertice, garantendone l'immutabilità.
 *
 * Partendo da un half edge start e un half edge end (non compreso), entrambi incidenti e uscenti
 * dal vertice su cui è inizializzaro l'iteratore, permette di ciclare su tutti i toVertex degli
 * half edge uscenti compresi tra start e end (ossia di ciclare sui vertici adiacenti). \n
 *
 * Le operazioni di incremento eseguono le due operazioni di \c prev() e \c twin() sull'half edge,
 * le operazioni di decremento eseguono le due operazioni di \c twin() e \c next() sull'half edge,
 * e l'operazione di dereferenziazione restituisce il toVertex dell'half edge puntato dall'iteratore.
 *
 * Per questi motivi, utilizzare questo iteratore solamente quando tutti gli half edge incidenti
 * (entranti e uscenti) hanno settato correttamente le seguenti relazioni di incidenza:
 * - from vertex (per gli uscenti deve essere il vertice su cui si itera)
 * - to vertex (per gli entranti deve essere il vertice su cui si itera)
 * - twin (sia per le operazioni di incremento che per quelle di decremento)
 * - next (per le operazioni di incremento)
 * - prev (per le operazioni di decremento)
 *
 * È possibile utilizzare l'iteratore in diversi modi. Il più semplice è ciclare in senso antiorario (operatore \++) o orario (operatore \--)
 * su tutti i vertici adiacenti ad un dato vertice \c v. In questo caso, sarà sufficiente scrivere:
 *
 * \code{.cpp}
 * for (Vertex::ConstAdjacentVertexIterator vit = v->adjacentVertexBegin(); vit != v->adjacentVertexEnd(); ++vit){
 *     const Vertex* av = *vit;
 *     // operazioni const su av
 * }
 * \endcode
 *
 * È però possibile anche visitare tutti i vertici adiacenti compresi tra due dati vertici adiacenti. In questo caso sarà necessario
 * passare i vertici estremi dell'intervallo all'inizializzatore Vertex::adjacentVertexBegin(). Per i dettagli su come funzionano queste
 * inizializzazioni si rimanda alla descrizione dei metodi stessi.
 *
 * Questo iteratore garantisce l'immutabilità del vertice della Dcel a cui appartiene, e quindi è possibile utilizzarlo solo su const Vertex.
 * Se si ha necessità di modificare i vertici presenti nella Dcel, usare Vertex::AdjacentVertexIterator.
 */
class Vertex::ConstAdjacentVertexIterator : public Vertex::ConstGenericIterator
{
    friend class Vertex;

public:
    //Constructors
    ConstAdjacentVertexIterator() : ConstGenericIterator(){};
    ConstAdjacentVertexIterator(const Vertex::AdjacentVertexIterator& it) : ConstGenericIterator(it){};

    //Public Operators
    const Vertex* operator * () const {return pos->toVertex();};

protected:

    //Protected Constructor
    ConstAdjacentVertexIterator(const HalfEdge* start, const HalfEdge* end, const Vertex* v) : ConstGenericIterator(start, end, v){};
};

/**
 * \~Italian
 * @class Vertex::OutgoingHalfEdgeIterator
 * @brief Iteratore che permette di ciclare sugli half edge uscenti da un vertice.
 *
 * Partendo da un half edge start e un half edge end (non compreso), entrambi incidenti e uscenti
 * dal vertice su cui è inizializzato l'iteratore, permette di ciclare su tutti gli half edge uscenti
 * compresi tra start e end. \n
 *
 * Le operazioni di incremento eseguono le due operazioni di \c prev() e \c twin() sull'half edge,
 * le operazioni di decremento eseguono le due operazioni di \c twin() e \c next() sull'half edge,
 * e l'operazione di dereferenziazione restituisce l'half edge puntato dall'iteratore.
 *
 * Per questi motivi, utilizzare questo iteratore solamente quando tutti gli half edge incidenti
 * (entranti e uscenti) hanno settato correttamente le seguenti relazioni di incidenza:
 * - from vertex (per gli uscenti deve essere il vertice su cui si itera)
 * - to vertex (per gli entranti deve essere il vertice su cui si itera)
 * - twin (sia per le operazioni di incremento che per quelle di decremento)
 * - next (per le operazioni di incremento)
 * - prev (per le operazioni di decremento)
 *
 * È possibile utilizzare l'iteratore in diversi modi. Il più semplice è ciclare in senso antiorario (operatore \++) o orario (operatore \--)
 * su tutti i vertici adiacenti ad un dato vertice \c v. In questo caso, sarà sufficiente scrivere:
 *
 * \code{.cpp}
 * for (Vertex::OutgoingHalfEdgeIterator heit = v->outgoingHalfEdgeBegin(); heit != v->outgoingHalfEdgeEnd(); ++heit){
 *     HalfEdge* he = *heit;
 *     // operazioni su he
 * }
 * \endcode
 *
 * È però possibile anche visitare tutti gli half edge uscenti compresi tra due dati half edge incidenti. In questo caso sarà necessario
 * passare gli half edge estremi dell'intervallo all'inizializzatore Vertex::outgoingHalfEdgeBegin(). Per i dettagli su come funzionano queste
 * inizializzazioni si rimanda alla descrizione dei metodi stessi.
 *
 * Questo iteratore non garantisce l'immutabilità del vertice e quindi della Dcel a cui appartiene, e quindi non è possibile
 * utilizzarlo su const Vertex. Per const Vertex, vedere Vertex::ConstOutgoingHalfEdgeIterator.
 */
class Vertex::OutgoingHalfEdgeIterator : public Vertex::GenericIterator
{
    friend class Vertex;

public:
    //Constructor
    OutgoingHalfEdgeIterator() : GenericIterator(){};

    //Public Operators
    HalfEdge* operator * () const {return pos;};

protected:

    //Protected Constructor
    OutgoingHalfEdgeIterator(HalfEdge* start, HalfEdge* end, Vertex* v) : GenericIterator(start, end, v){};
};

/**
 * \~Italian
 * @class Vertex::ConstOutgoingHalfEdgeIterator
 * @brief Iteratore che permette di ciclare sugli half edge uscenti da un vertice, garantendone l'immutabilità.
 *
 * Partendo da un half edge start e un half edge end (non compreso), entrambi incidenti e uscenti
 * dal vertice su cui è inizializzato l'iteratore, permette di ciclare su tutti gli half edge uscenti
 * compresi tra start e end. \n
 *
 * Le operazioni di incremento eseguono le due operazioni di \c prev() e \c twin() sull'half edge,
 * le operazioni di decremento eseguono le due operazioni di \c twin() e \c next() sull'half edge,
 * e l'operazione di dereferenziazione restituisce l'half edge puntato dall'iteratore.
 *
 * Per questi motivi, utilizzare questo iteratore solamente quando tutti gli half edge incidenti
 * (entranti e uscenti) hanno settato correttamente le seguenti relazioni di incidenza:
 * - from vertex (per gli uscenti deve essere il vertice su cui si itera)
 * - to vertex (per gli entranti deve essere il vertice su cui si itera)
 * - twin (sia per le operazioni di incremento che per quelle di decremento)
 * - next (per le operazioni di incremento)
 * - prev (per le operazioni di decremento)
 *
 * È possibile utilizzare l'iteratore in diversi modi. Il più semplice è ciclare in senso antiorario (operatore \++) o orario (operatore \--)
 * su tutti i vertici adiacenti ad un dato vertice \c v. In questo caso, sarà sufficiente scrivere:
 *
 * \code{.cpp}
 * for (Vertex::ConstOutgoingHalfEdgeIterator heit = v->outgoingHalfEdgeBegin(); heit != v->outgoingHalfEdgeEnd(); ++heit){
 *     const HalfEdge* he = *heit;
 *     // operazioni const su he
 * }
 * \endcode
 *
 * È però possibile anche visitare tutti gli half edge uscenti compresi tra due dati half edge incidenti. In questo caso sarà necessario
 * passare gli half edge estremi dell'intervallo all'inizializzatore Vertex::outgoingHalfEdgeBegin(). Per i dettagli su come funzionano queste
 * inizializzazioni si rimanda alla descrizione dei metodi stessi.
 *
 * Questo iteratore garantisce l'immutabilità del vertice della Dcel a cui appartiene, e quindi è possibile utilizzarlo solo su const Vertex.
 * Se si ha necessità di modificare i vertici presenti nella Dcel, usare Vertex::OutgoingHalfEdgeIterator.
 */
class Vertex::ConstOutgoingHalfEdgeIterator : public Vertex::ConstGenericIterator
{
    friend class Vertex;

public:
    //Constructors
    ConstOutgoingHalfEdgeIterator() : ConstGenericIterator(){};
    ConstOutgoingHalfEdgeIterator(const Vertex::OutgoingHalfEdgeIterator& it) : ConstGenericIterator(it){};

    //Public Operators
    const HalfEdge* operator * () const {return pos;};

protected:

    //Protected Constructor
    ConstOutgoingHalfEdgeIterator(const HalfEdge* start, const HalfEdge* end, const Vertex* v) : ConstGenericIterator(start, end, v){};
};

/**
 * \~Italian
 * @class Vertex::IncomingHalfEdgeIterator
 * @brief Iteratore che permette di ciclare sugli half edge entranti in un vertice.
 *
 * Partendo da un half edge start e un half edge end (non compreso), entrambi incidenti e \b uscenti
 * dal vertice su cui è inizializzato l'iteratore, permette di ciclare su tutti gli half edge entranti
 * compresi tra start e end. \n
 *
 * Le operazioni di incremento eseguono le due operazioni di \c prev() e \c twin() sull'half edge,
 * le operazioni di decremento eseguono le due operazioni di \c twin() e \c next() sull'half edge,
 * e l'operazione di dereferenziazione restituisce il twin dell'half edge puntato dall'iteratore.
 *
 * Per questi motivi, utilizzare questo iteratore solamente quando tutti gli half edge incidenti
 * (entranti e uscenti) hanno settato correttamente le seguenti relazioni di incidenza:
 * - from vertex (per gli uscenti deve essere il vertice su cui si itera)
 * - to vertex (per gli entranti deve essere il vertice su cui si itera)
 * - twin (sia per le operazioni di incremento che per quelle di decremento)
 * - next (per le operazioni di incremento)
 * - prev (per le operazioni di decremento)
 *
 * È possibile utilizzare l'iteratore in diversi modi. Il più semplice è ciclare in senso antiorario (operatore \++) o orario (operatore \--)
 * su tutti i vertici adiacenti ad un dato vertice \c v. In questo caso, sarà sufficiente scrivere:
 *
 * \code{.cpp}
 * for (Vertex::IncomingHalfEdgeIterator heit = v->incomingHalfEdgeBegin(); heit != v->incomingHalfEdgeEnd(); ++heit){
 *     HalfEdge* he = *heit;
 *     // operazioni su he
 * }
 * \endcode
 *
 * È però possibile anche visitare tutti gli half edge entranti compresi tra due dati half edge incidenti. In questo caso sarà necessario
 * passare gli half edge estremi dell'intervallo all'inizializzatore Vertex::incomingHalfEdgeBegin(). Per i dettagli su come funzionano queste
 * inizializzazioni si rimanda alla descrizione dei metodi stessi.
 *
 * Questo iteratore non garantisce l'immutabilità del vertice e quindi della Dcel a cui appartiene, e quindi non è possibile
 * utilizzarlo su const Vertex. Per const Vertex, vedere Vertex::ConstIncomingHalfEdgeIterator.
 */
class Vertex::IncomingHalfEdgeIterator : public GenericIterator
{
    friend class Vertex;

public:
    //Constructor
    IncomingHalfEdgeIterator() : GenericIterator(){};

    //Public Operators
    HalfEdge* operator * () const {return pos->twin();};

protected:

    //Protected Constructor
    IncomingHalfEdgeIterator(HalfEdge* start, HalfEdge* end, Vertex* v) : GenericIterator(start, end, v){};
};

/**
 * \~Italian
 * @class Vertex::ConstIncomingHalfEdgeIterator
 * @brief Iteratore che permette di ciclare sugli half edge entranti in un vertice, garantendone l'immutabilità.
 *
 * Partendo da un half edge start e un half edge end (non compreso), entrambi incidenti e \b uscenti
 * dal vertice su cui è inizializzato l'iteratore, permette di ciclare su tutti gli half edge entranti
 * compresi tra start e end. \n
 *
 * Le operazioni di incremento eseguono le due operazioni di \c prev() e \c twin() sull'half edge,
 * le operazioni di decremento eseguono le due operazioni di \c twin() e \c next() sull'half edge,
 * e l'operazione di dereferenziazione restituisce il twin dell'half edge puntato dall'iteratore.
 *
 * Per questi motivi, utilizzare questo iteratore solamente quando tutti gli half edge incidenti
 * (entranti e uscenti) hanno settato correttamente le seguenti relazioni di incidenza:
 * - from vertex (per gli uscenti deve essere il vertice su cui si itera)
 * - to vertex (per gli entranti deve essere il vertice su cui si itera)
 * - twin (sia per le operazioni di incremento che per quelle di decremento)
 * - next (per le operazioni di incremento)
 * - prev (per le operazioni di decremento)
 *
 * È possibile utilizzare l'iteratore in diversi modi. Il più semplice è ciclare in senso antiorario (operatore \++) o orario (operatore \--)
 * su tutti i vertici adiacenti ad un dato vertice \c v. In questo caso, sarà sufficiente scrivere:
 *
 * \code{.cpp}
 * for (Vertex::ConstIncomingHalfEdgeIterator heit = v->incomingHalfEdgeBegin(); heit != v->incomingHalfEdgeEnd(); ++heit){
 *     const HalfEdge* he = *heit;
 *     // operazioni const su he
 * }
 * \endcode
 *
 * È però possibile anche visitare tutti gli half edge entranti compresi tra due dati half edge incidenti. In questo caso sarà necessario
 * passare gli half edge estremi dell'intervallo all'inizializzatore Vertex::incomingHalfEdgeBegin(). Per i dettagli su come funzionano queste
 * inizializzazioni si rimanda alla descrizione dei metodi stessi.
 *
 * Questo iteratore garantisce l'immutabilità del vertice della Dcel a cui appartiene, e quindi è possibile utilizzarlo solo su const Vertex.
 * Se si ha necessità di modificare i vertici presenti nella Dcel, usare Vertex::IncomingHalfEdgeIterator.
 */
class Vertex::ConstIncomingHalfEdgeIterator : public Vertex::ConstGenericIterator
{
    friend class Vertex;

public:
    //Constructors
    ConstIncomingHalfEdgeIterator() : ConstGenericIterator(){};
    ConstIncomingHalfEdgeIterator(const Vertex::IncomingHalfEdgeIterator& it) : ConstGenericIterator(it){};

    //Public Operators
    const HalfEdge* operator * () const {return pos->twin();};

protected:

    //Protected Constructor
    ConstIncomingHalfEdgeIterator(const HalfEdge* start, const HalfEdge* end, const Vertex* v) : ConstGenericIterator(start, end, v){};
};

/**
 * \~Italian
 * @class Vertex::IncidentHalfEdgeIterator
 * @brief Iteratore che permette di ciclare sugli half edge uscenti e entranti in un vertice.
 *
 * Partendo da un half edge start e un half edge end (non compreso), entrambi incidenti
 * sul vertice su cui è inizializzato l'iteratore, permette di ciclare su tutti gli half edge
 * compresi tra start e end. \n
 *
 * Le operazioni di incremento eseguono un'operazione di \c prev() se l'half edge è uscente e \c twin()
 * se l'half edge è entrante nel vertice, le operazioni di decremento eseguono un'operazione di \c twin()
 * se l'half edge è uscente e \c next() se l'half edge è entrante nel vertice, e l'operazione di
 * dereferenziazione restituisce l'half edge puntato dall'iteratore.
 *
 * Per questi motivi, utilizzare questo iteratore solamente quando tutti gli half edge incidenti
 * (entranti e uscenti) hanno settato correttamente le seguenti relazioni di incidenza:
 * - from vertex (per gli uscenti deve essere il vertice su cui si itera)
 * - to vertex (per gli entranti deve essere il vertice su cui si itera)
 * - twin (sia per le operazioni di incremento che per quelle di decremento)
 * - next (per le operazioni di incremento)
 * - prev (per le operazioni di decremento)
 *
 * È possibile utilizzare l'iteratore in diversi modi. Il più semplice è ciclare in senso antiorario (operatore \++) o orario (operatore \--)
 * su tutti i vertici adiacenti ad un dato vertice \c v. In questo caso, sarà sufficiente scrivere:
 *
 * \code{.cpp}
 * for (Vertex::IncidentHalfEdgeIterator heit = v->incidentHalfEdgeBegin(); heit != v->incidentHalfEdgeEnd(); ++heit){
 *     HalfEdge* he = *heit;
 *     // operazioni su he
 * }
 * \endcode
 *
 * È però possibile anche visitare tutti gli half edge incidenti compresi tra due dati half edge incidenti. In questo caso sarà necessario
 * passare gli half edge estremi dell'intervallo all'inizializzatore Vertex::incidentHalfEdgeBegin(). Per i dettagli su come funzionano queste
 * inizializzazioni si rimanda alla descrizione dei metodi stessi.
 *
 * Questo iteratore non garantisce l'immutabilità del vertice e quindi della Dcel a cui appartiene, e quindi non è possibile
 * utilizzarlo su const Vertex. Per const Vertex, vedere Vertex::ConstIncidentHalfEdgeIterator.
 */
class Vertex::IncidentHalfEdgeIterator : public Vertex::GenericIterator
{
    friend class Vertex;

public:
    //Constructor
    IncidentHalfEdgeIterator() : GenericIterator(){};

    //Public Operators
    HalfEdge* operator * () const {return pos;};

    IncidentHalfEdgeIterator operator ++ () {
        if (pos->fromVertex() == v) pos = pos->prev();
        else pos = pos->twin();
        if (pos == end) pos = nullptr;
        return *this;
    };
    IncidentHalfEdgeIterator operator ++ (int) {
        IncidentHalfEdgeIterator old_value = *this;
        if (pos->fromVertex() == v) pos = pos->prev();
        else pos = pos->twin();
        if (pos == end) pos = nullptr;
        return old_value;
    };
    IncidentHalfEdgeIterator operator -- () {
        if (pos->fromVertex() == v) pos = pos->twin();
        else pos = pos->next();
        if (pos == end) pos = nullptr;
        return *this;
    };
    IncidentHalfEdgeIterator operator -- (int) {
        IncidentHalfEdgeIterator old_value = *this;
        if (pos->fromVertex() == v) pos = pos->twin();
        else pos = pos->next();
        if (pos == end) pos = nullptr;
        return old_value;
    };

protected:

    //Protected Constructor
    IncidentHalfEdgeIterator(HalfEdge* start, HalfEdge* end, Vertex* v) : GenericIterator(start, end, v){};
};

/**
 * \~Italian
 * @class Vertex::ConstIncidentHalfEdgeIterator
 * @brief Iteratore che permette di ciclare sugli half edge uscenti e entranti in un vertice.
 *
 * Partendo da un half edge start e un half edge end (non compreso), entrambi incidenti
 * sul vertice su cui è inizializzato l'iteratore, permette di ciclare su tutti gli half edge
 * compresi tra start e end. \n
 *
 * Le operazioni di incremento eseguono un'operazione di \c prev() se l'half edge è uscente e \c twin()
 * se l'half edge è entrante nel vertice, le operazioni di decremento eseguono un'operazione di \c twin()
 * se l'half edge è uscente e \c next() se l'half edge è entrante nel vertice, e l'operazione di
 * dereferenziazione restituisce l'half edge puntato dall'iteratore.
 *
 * Per questi motivi, utilizzare questo iteratore solamente quando tutti gli half edge incidenti
 * (entranti e uscenti) hanno settato correttamente le seguenti relazioni di incidenza:
 * - from vertex (per gli uscenti deve essere il vertice su cui si itera)
 * - to vertex (per gli entranti deve essere il vertice su cui si itera)
 * - twin (sia per le operazioni di incremento che per quelle di decremento)
 * - next (per le operazioni di incremento)
 * - prev (per le operazioni di decremento)
 *
 * È possibile utilizzare l'iteratore in diversi modi. Il più semplice è ciclare in senso antiorario (operatore \++) o orario (operatore \--)
 * su tutti i vertici adiacenti ad un dato vertice \c v. In questo caso, sarà sufficiente scrivere:
 *
 * \code{.cpp}
 * for (Vertex::ConstIncidentHalfEdgeIterator heit = v->incidentHalfEdgeBegin(); heit != v->incidentHalfEdgeEnd(); ++heit){
 *     const HalfEdge* he = *heit;
 *     // operazioni const su he
 * }
 * \endcode
 *
 * È però possibile anche visitare tutti gli half edge incidenti compresi tra due dati half edge incidenti. In questo caso sarà necessario
 * passare gli half edge estremi dell'intervallo all'inizializzatore Vertex::incidentHalfEdgeBegin(). Per i dettagli su come funzionano queste
 * inizializzazioni si rimanda alla descrizione dei metodi stessi.
 *
 * Questo iteratore garantisce l'immutabilità del vertice della Dcel a cui appartiene, e quindi è possibile utilizzarlo solo su const Vertex.
 * Se si ha necessità di modificare i vertici presenti nella Dcel, usare Vertex::IncidentHalfEdgeIterator.
 */
class Vertex::ConstIncidentHalfEdgeIterator : public ConstGenericIterator
{
    friend class Vertex;

public:
    //Constructors
    ConstIncidentHalfEdgeIterator() : ConstGenericIterator(){};
    ConstIncidentHalfEdgeIterator(const Vertex::IncidentHalfEdgeIterator& it) : ConstGenericIterator(it){};

    //Public Operators
    const HalfEdge* operator * () const {return pos;};

    ConstIncidentHalfEdgeIterator operator ++ (){
        if (pos->fromVertex() == v) pos = pos->twin();
        else pos = pos->next();
        if (pos == end) pos = nullptr;
        return *this;
    }
    ConstIncidentHalfEdgeIterator operator ++ (int){
        ConstIncidentHalfEdgeIterator old_value = *this;
        if (pos->fromVertex() == v) pos = pos->twin();
        else pos = pos->next();
        if (pos == end) pos = nullptr;
        return old_value;
    }
    ConstIncidentHalfEdgeIterator operator -- (){
        if (pos->fromVertex() == v) pos = pos->prev();
        else pos = pos->twin();
        if (pos == end) pos = nullptr;
        return *this;
    }
    ConstIncidentHalfEdgeIterator operator -- (int){
        ConstIncidentHalfEdgeIterator old_value = *this;
        if (pos->fromVertex() == v) pos = pos->prev();
        else pos = pos->twin();
        if (pos == end) pos = nullptr;
        return old_value;
    }

protected:

    //Protected Constructor
    ConstIncidentHalfEdgeIterator(const HalfEdge* start, const HalfEdge* end, const Vertex* v) : ConstGenericIterator(start, end, v){};
};

/**
 * \~Italian
 * @class Vertex::IncidentFaceIterator
 * @brief Iteratore che permette di ciclare sulle facce incidenti su un vertice.
 *
 * Partendo da un half edge start e un half edge end (non compreso), entrambi incidenti
 * sul vertice su cui è inizializzato l'iteratore, permette di ciclare su tutte le facce
 * incidenti sugli half edge compresi tra start e end. \n
 *
 * Le operazioni di incremento eseguono le due operazioni di \c prev() e \c twin() sull'half edge,
 * le operazioni di decremento eseguono le due operazioni di \c twin() e \c next() sull'half edge,
 * e l'operazione di dereferenziazione restituisce la faccia incidente sull'half edge puntato
 * dall'iteratore.
 *
 * Per questi motivi, utilizzare questo iteratore solamente quando tutti gli half edge incidenti
 * (entranti e uscenti) hanno settato correttamente le seguenti relazioni di incidenza:
 * - from vertex (per gli uscenti deve essere il vertice su cui si itera)
 * - to vertex (per gli entranti deve essere il vertice su cui si itera)
 * - twin (sia per le operazioni di incremento che per quelle di decremento)
 * - next (per le operazioni di incremento)
 * - prev (per le operazioni di decremento)
 *
 * È possibile utilizzare l'iteratore in diversi modi. Il più semplice è ciclare in senso antiorario (operatore \++) o orario (operatore \--)
 * su tutti i vertici adiacenti ad un dato vertice \c v. In questo caso, sarà sufficiente scrivere:
 *
 * \code{.cpp}
 * for (Vertex::IncidentFaceIterator heit = v->incidentFaceBegin(); heit != v->incidentFaceEnd(); ++heit){
 *     Face* he = *heit;
 *     // operazioni su he
 * }
 * \endcode
 *
 * È però possibile anche visitare tutti le facce incidenti compresi tra due dati half edge incidenti. In questo caso sarà necessario
 * passare gli half edge estremi dell'intervallo all'inizializzatore Vertex::incidentFaceBegin(). Per i dettagli su come funzionano queste
 * inizializzazioni si rimanda alla descrizione dei metodi stessi.
 *
 * Questo iteratore non garantisce l'immutabilità del vertice e quindi della Dcel a cui appartiene, e quindi non è possibile
 * utilizzarlo su const Vertex. Per const Vertex, vedere Vertex::ConstFaceIterator.
 *
 * @warning Nel caso di Dcel composte da poligoni generici, è possibile che un vertice abbia la stessa faccia incidente su due punti diversi.
 */
class Vertex::IncidentFaceIterator : public Vertex::GenericIterator
{
    friend class Vertex;

public:
    //Constructor
    IncidentFaceIterator() : GenericIterator(){};

    //Public Operators
    Face* operator * () const {return pos->face();};

protected:

    //Protected Constructor
    IncidentFaceIterator(HalfEdge* start, HalfEdge* end, Vertex* v) : GenericIterator(start, end, v){};
};

/**
 * \~Italian
 * @class Vertex::ConstIncidentFaceIterator
 * @brief Iteratore che permette di ciclare sulle facce incidenti su un vertice.
 *
 * Partendo da un half edge start e un half edge end (non compreso), entrambi incidenti
 * sul vertice su cui è inizializzato l'iteratore, permette di ciclare su tutte le facce
 * incidenti sugli half edge compresi tra start e end. \n
 *
 * Le operazioni di incremento eseguono le due operazioni di \c prev() e \c twin() sull'half edge,
 * le operazioni di decremento eseguono le due operazioni di \c twin() e \c next() sull'half edge,
 * e l'operazione di dereferenziazione restituisce la faccia incidente sull'half edge puntato
 * dall'iteratore.
 *
 * Per questi motivi, utilizzare questo iteratore solamente quando tutti gli half edge incidenti
 * (entranti e uscenti) hanno settato correttamente le seguenti relazioni di incidenza:
 * - from vertex (per gli uscenti deve essere il vertice su cui si itera)
 * - to vertex (per gli entranti deve essere il vertice su cui si itera)
 * - twin (sia per le operazioni di incremento che per quelle di decremento)
 * - next (per le operazioni di incremento)
 * - prev (per le operazioni di decremento)
 *
 * È possibile utilizzare l'iteratore in diversi modi. Il più semplice è ciclare in senso antiorario (operatore \++) o orario (operatore \--)
 * su tutti i vertici adiacenti ad un dato vertice \c v. In questo caso, sarà sufficiente scrivere:
 *
 * \code{.cpp}
 * for (Vertex::ConstIncidentFaceIterator heit = v->incidentFaceBegin(); heit != v->incidentFaceEnd(); ++heit){
 *     const Face* he = *heit;
 *     // operazioni const su he
 * }
 * \endcode
 *
 * È però possibile anche visitare tutti le facce incidenti compresi tra due dati half edge incidenti. In questo caso sarà necessario
 * passare gli half edge estremi dell'intervallo all'inizializzatore Vertex::incidentFaceBegin(). Per i dettagli su come funzionano queste
 * inizializzazioni si rimanda alla descrizione dei metodi stessi.
 *
 * Questo iteratore garantisce l'immutabilità del vertice della Dcel a cui appartiene, e quindi è possibile utilizzarlo solo su const Vertex.
 * Se si ha necessità di modificare i vertici presenti nella Dcel, usare Vertex::ConstIncidentFaceIterator.
 *
 * @warning Nel caso di Dcel composte da poligoni generici, è possibile che un vertice abbia la stessa faccia incidente su due punti diversi.
 */
class Vertex::ConstIncidentFaceIterator : public Vertex::ConstGenericIterator
{
    friend class Vertex;

public:
    //Constructors
    ConstIncidentFaceIterator() : ConstGenericIterator(){};
    ConstIncidentFaceIterator(const Vertex::IncidentFaceIterator& it) : ConstGenericIterator(it){};

    //Public Operators
    const Face* operator * () const {return pos->face();};

private:

    //Protected Constructor
    ConstIncidentFaceIterator(const HalfEdge* start, const HalfEdge* end, const Vertex* v) : ConstGenericIterator(start, end, v){};
};

class Vertex::ConstAdjacentVertexRangeBasedIterator
{
    friend class Vertex;
public:
    Vertex::ConstAdjacentVertexIterator begin() const {return v->adjacentVertexBegin();};
    Vertex::ConstAdjacentVertexIterator end() const {return v->adjacentVertexEnd();};
private:
    ConstAdjacentVertexRangeBasedIterator(const Vertex *v) : v(v) {}
    const Vertex *v;
};

class Vertex::ConstOutgoingHalfEdgeRangeBasedIterator
{
    friend class Vertex;
public:
    Vertex::ConstOutgoingHalfEdgeIterator begin() const {return v->outgoingHalfEdgeBegin();};
    Vertex::ConstOutgoingHalfEdgeIterator end() const {return v->outgoingHalfEdgeEnd();};
private:
    ConstOutgoingHalfEdgeRangeBasedIterator(const Vertex *v) : v(v) {}
    const Vertex *v;
};

class Vertex::ConstIncomingHalfEdgeRangeBasedIterator
{
    friend class Vertex;
public:
    Vertex::ConstIncomingHalfEdgeIterator begin() const {return v->incomingHalfEdgeBegin();};
    Vertex::ConstIncomingHalfEdgeIterator end() const {return v->incomingHalfEdgeEnd();};
private:
    ConstIncomingHalfEdgeRangeBasedIterator(const Vertex *v) : v(v) {}
    const Vertex *v;
};

class Vertex::ConstIncidentHalfEdgeRangeBasedIterator
{
    friend class Vertex;
public:
    Vertex::ConstIncidentHalfEdgeIterator begin() const {return v->incidentHalfEdgeBegin();};
    Vertex::ConstIncidentHalfEdgeIterator end() const {return v->incidentHalfEdgeEnd();};
private:
    ConstIncidentHalfEdgeRangeBasedIterator(const Vertex *v) : v(v) {}
    const Vertex *v;
};

class Vertex::ConstIncidentFaceRangeBasedIterator
{
    friend class Vertex;
public:
    Vertex::ConstIncidentFaceIterator begin() const {return v->incidentFaceBegin();};
    Vertex::ConstIncidentFaceIterator end() const {return v->incidentFaceEnd();};
private:
    ConstIncidentFaceRangeBasedIterator(const Vertex *v) : v(v) {}
    const Vertex *v;
};

class Vertex::AdjacentVertexRangeBasedIterator
{
    friend class Vertex;
public:
    Vertex::AdjacentVertexIterator begin() {return v->adjacentVertexBegin();}
    Vertex::AdjacentVertexIterator end() {return v->adjacentVertexEnd();}
private:
    AdjacentVertexRangeBasedIterator(Vertex *v) : v(v) {}
    Vertex *v;
};

class Vertex::OutgoingHalfEdgeRangeBasedIterator
{
    friend class Vertex;
public:
    Vertex::OutgoingHalfEdgeIterator begin() {return v->outgoingHalfEdgeBegin();};
    Vertex::OutgoingHalfEdgeIterator end() {return v->outgoingHalfEdgeEnd();};
private:
    OutgoingHalfEdgeRangeBasedIterator(Vertex *v) : v(v) {}
    Vertex *v;
};

class Vertex::IncomingHalfEdgeRangeBasedIterator
{
    friend class Vertex;
public:
    Vertex::IncomingHalfEdgeIterator begin() {return v->incomingHalfEdgeBegin();};
    Vertex::IncomingHalfEdgeIterator end() {return v->incomingHalfEdgeEnd();};
private:
    IncomingHalfEdgeRangeBasedIterator(Vertex *v) : v(v) {}
    Vertex *v;
};

class Vertex::IncidentHalfEdgeRangeBasedIterator
{
    friend class Vertex;
public:
    Vertex::IncidentHalfEdgeIterator begin() {return v->incidentHalfEdgeBegin();};
    Vertex::IncidentHalfEdgeIterator end() {return v->incidentHalfEdgeEnd();};
private:
    IncidentHalfEdgeRangeBasedIterator(Vertex *v) : v(v) {}
    Vertex *v;
};

class Vertex::IncidentFaceRangeBasedIterator
{
    friend class Vertex;
public:
    Vertex::IncidentFaceIterator begin() {return v->incidentFaceBegin();};
    Vertex::IncidentFaceIterator end() {return v->incidentFaceEnd();};
private:
    IncidentFaceRangeBasedIterator(Vertex *v) : v(v) {}
    Vertex *v;
};

} //namespace cg3

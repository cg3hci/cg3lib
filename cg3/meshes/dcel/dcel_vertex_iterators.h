/*
 * @author    Alessandro Muntoni (muntoni.alessandro@gmail.com)
 * @copyright Alessandro Muntoni 2016.
 */

#ifndef CG3_DCEL_VERTEX_ITERATORS_H
#define CG3_DCEL_VERTEX_ITERATORS_H

#include "dcel_vertex.h"
#include "dcel_half_edge.h"

namespace cg3 {

class Dcel::Vertex::GenericIterator {

        friend class Dcel::Vertex;

    public:
        //Constructor
        GenericIterator();

        //Public Operators
        void* operator * () const {return nullptr;}
        bool operator == (const GenericIterator& right)  const;
        bool operator != (const GenericIterator& right)  const;

        GenericIterator operator ++ ();
        GenericIterator operator ++ (int);
        GenericIterator operator -- ();
        GenericIterator operator -- (int);

    protected:
        //Protected Attributes
        Dcel::Vertex*   v;      /**< \~Italian @brief Vertice su cui vengono iterati i vertici adiacenti */
        Dcel::HalfEdge* start;  /**< \~Italian @brief Half edge dal quale è partito l'iteratore */
        Dcel::HalfEdge* pos;    /**< \~Italian @brief Posizione attuale dell'iteratore */
        Dcel::HalfEdge* end;    /**< \~Italian @brief Half edge sul quale termina l'iteratore */

        //Protected Constructor
        GenericIterator(Dcel::HalfEdge* start, Dcel::HalfEdge* end, Dcel::Vertex* v);
};

class Dcel::Vertex::ConstGenericIterator {

        friend class Dcel::Vertex;

    public:
        //Constructors
        ConstGenericIterator();
        ConstGenericIterator(const Dcel::Vertex::GenericIterator& it);

        //Public Operators
        const void* operator * () const {return nullptr;}
        bool operator == (const ConstGenericIterator& right) const;
        bool operator != (const ConstGenericIterator& right) const;

        ConstGenericIterator operator ++ ();
        ConstGenericIterator operator ++ (int);
        ConstGenericIterator operator -- ();
        ConstGenericIterator operator -- (int);

    protected:
        //Protected Attributes
        const Dcel::Vertex*   v;        /**< \~Italian @brief Vertice su cui vengono iterati i vertici adiacenti */
        const Dcel::HalfEdge* start;    /**< \~Italian @brief Half edge dal quale è partito l'iteratore */
        const Dcel::HalfEdge* pos;      /**< \~Italian @brief Posizione attuale dell'iteratore */
        const Dcel::HalfEdge* end;      /**< \~Italian @brief Half edge sul quale termina l'iteratore */

        //Protected Constructor
        ConstGenericIterator(const Dcel::HalfEdge* start, const Dcel::HalfEdge* end, const Dcel::Vertex* v);
};

/**
 * \~Italian
 * @class Dcel::Vertex::AdjacentVertexIterator
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
 * for (Dcel::Vertex::AdjacentVertexIterator vit = v->adjacentVertexBegin(); vit != v->adjacentVertexEnd(); ++vit){
 *     Dcel::Vertex* av = *vit;
 *     // operazioni su av
 * }
 * \endcode
 *
 * È però possibile anche visitare tutti i vertici adiacenti compresi tra due dati vertici adiacenti. In questo caso sarà necessario
 * passare i vertici estremi dell'intervallo all'inizializzatore Dcel::Vertex::adjacentVertexBegin(). Per i dettagli su come funzionano queste
 * inizializzazioni si rimanda alla descrizione dei metodi stessi.
 *
 * Questo iteratore non garantisce l'immutabilità del vertice e quindi della Dcel a cui appartiene, e quindi non è possibile
 * utilizzarlo su const Dcel::Vertex. Per const Dcel::Vertex, vedere Dcel::Vertex::ConstAdjacentVertexIterator.
 */
class Dcel::Vertex::AdjacentVertexIterator : public Dcel::Vertex::GenericIterator {

        friend class Dcel::Vertex;

    public:
        //Constructor
        AdjacentVertexIterator();

        //Public Operators
        Dcel::Vertex* operator * ()                             const;

    protected:

        //Protected Constructor
        AdjacentVertexIterator(Dcel::HalfEdge* start, Dcel::HalfEdge* end, Dcel::Vertex* v);
};

/**
 * \~Italian
 * @class Dcel::Vertex::ConstAdjacentVertexIterator
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
 * for (Dcel::Vertex::ConstAdjacentVertexIterator vit = v->adjacentVertexBegin(); vit != v->adjacentVertexEnd(); ++vit){
 *     const Dcel::Vertex* av = *vit;
 *     // operazioni const su av
 * }
 * \endcode
 *
 * È però possibile anche visitare tutti i vertici adiacenti compresi tra due dati vertici adiacenti. In questo caso sarà necessario
 * passare i vertici estremi dell'intervallo all'inizializzatore Dcel::Vertex::adjacentVertexBegin(). Per i dettagli su come funzionano queste
 * inizializzazioni si rimanda alla descrizione dei metodi stessi.
 *
 * Questo iteratore garantisce l'immutabilità del vertice della Dcel a cui appartiene, e quindi è possibile utilizzarlo solo su const Dcel::Vertex.
 * Se si ha necessità di modificare i vertici presenti nella Dcel, usare Dcel::Vertex::AdjacentVertexIterator.
 */
class Dcel::Vertex::ConstAdjacentVertexIterator : public Dcel::Vertex::ConstGenericIterator {

        friend class Dcel::Vertex;

    public:
        //Constructors
        ConstAdjacentVertexIterator();
        ConstAdjacentVertexIterator(const Dcel::Vertex::AdjacentVertexIterator& it);

        //Public Operators
        const Dcel::Vertex* operator * ()                           const;

    protected:

        //Protected Constructor
        ConstAdjacentVertexIterator(const Dcel::HalfEdge* start, const Dcel::HalfEdge* end, const Dcel::Vertex* v);
};

/**
 * \~Italian
 * @class Dcel::Vertex::OutgoingHalfEdgeIterator
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
 * for (Dcel::Vertex::OutgoingHalfEdgeIterator heit = v->outgoingHalfEdgeBegin(); heit != v->outgoingHalfEdgeEnd(); ++heit){
 *     Dcel::HalfEdge* he = *heit;
 *     // operazioni su he
 * }
 * \endcode
 *
 * È però possibile anche visitare tutti gli half edge uscenti compresi tra due dati half edge incidenti. In questo caso sarà necessario
 * passare gli half edge estremi dell'intervallo all'inizializzatore Dcel::Vertex::outgoingHalfEdgeBegin(). Per i dettagli su come funzionano queste
 * inizializzazioni si rimanda alla descrizione dei metodi stessi.
 *
 * Questo iteratore non garantisce l'immutabilità del vertice e quindi della Dcel a cui appartiene, e quindi non è possibile
 * utilizzarlo su const Dcel::Vertex. Per const Dcel::Vertex, vedere Dcel::Vertex::ConstOutgoingHalfEdgeIterator.
 */
class Dcel::Vertex::OutgoingHalfEdgeIterator : public Dcel::Vertex::GenericIterator {

        friend class Dcel::Vertex;

    public:
        //Constructor
        OutgoingHalfEdgeIterator();

        //Public Operators
        Dcel::HalfEdge* operator * ()                               const;

    protected:

        //Protected Constructor
        OutgoingHalfEdgeIterator(Dcel::HalfEdge* start, Dcel::HalfEdge* end, Dcel::Vertex* v);
};

/**
 * \~Italian
 * @class Dcel::Vertex::ConstOutgoingHalfEdgeIterator
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
 * for (Dcel::Vertex::ConstOutgoingHalfEdgeIterator heit = v->outgoingHalfEdgeBegin(); heit != v->outgoingHalfEdgeEnd(); ++heit){
 *     const Dcel::HalfEdge* he = *heit;
 *     // operazioni const su he
 * }
 * \endcode
 *
 * È però possibile anche visitare tutti gli half edge uscenti compresi tra due dati half edge incidenti. In questo caso sarà necessario
 * passare gli half edge estremi dell'intervallo all'inizializzatore Dcel::Vertex::outgoingHalfEdgeBegin(). Per i dettagli su come funzionano queste
 * inizializzazioni si rimanda alla descrizione dei metodi stessi.
 *
 * Questo iteratore garantisce l'immutabilità del vertice della Dcel a cui appartiene, e quindi è possibile utilizzarlo solo su const Dcel::Vertex.
 * Se si ha necessità di modificare i vertici presenti nella Dcel, usare Dcel::Vertex::OutgoingHalfEdgeIterator.
 */
class Dcel::Vertex::ConstOutgoingHalfEdgeIterator : public Dcel::Vertex::ConstGenericIterator {

        friend class Dcel::Vertex;

    public:
        //Constructors
        ConstOutgoingHalfEdgeIterator();
        ConstOutgoingHalfEdgeIterator(const Dcel::Vertex::OutgoingHalfEdgeIterator& it);

        //Public Operators
        const Dcel::HalfEdge* operator * ()                             const;

    protected:

        //Protected Constructor
        ConstOutgoingHalfEdgeIterator(const Dcel::HalfEdge* start, const Dcel::HalfEdge* end, const Dcel::Vertex* v);
};

/**
 * \~Italian
 * @class Dcel::Vertex::IncomingHalfEdgeIterator
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
 * for (Dcel::Vertex::IncomingHalfEdgeIterator heit = v->incomingHalfEdgeBegin(); heit != v->incomingHalfEdgeEnd(); ++heit){
 *     Dcel::HalfEdge* he = *heit;
 *     // operazioni su he
 * }
 * \endcode
 *
 * È però possibile anche visitare tutti gli half edge entranti compresi tra due dati half edge incidenti. In questo caso sarà necessario
 * passare gli half edge estremi dell'intervallo all'inizializzatore Dcel::Vertex::incomingHalfEdgeBegin(). Per i dettagli su come funzionano queste
 * inizializzazioni si rimanda alla descrizione dei metodi stessi.
 *
 * Questo iteratore non garantisce l'immutabilità del vertice e quindi della Dcel a cui appartiene, e quindi non è possibile
 * utilizzarlo su const Dcel::Vertex. Per const Dcel::Vertex, vedere Dcel::Vertex::ConstIncomingHalfEdgeIterator.
 */
class Dcel::Vertex::IncomingHalfEdgeIterator : public GenericIterator {

        friend class Dcel::Vertex;

    public:
        //Constructor
        IncomingHalfEdgeIterator();

        //Public Operators
        Dcel::HalfEdge* operator * ()                               const;

    protected:

        //Protected Constructor
        IncomingHalfEdgeIterator(Dcel::HalfEdge* start, Dcel::HalfEdge* end, Dcel::Vertex* v);
};

/**
 * \~Italian
 * @class Dcel::Vertex::ConstIncomingHalfEdgeIterator
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
 * for (Dcel::Vertex::ConstIncomingHalfEdgeIterator heit = v->incomingHalfEdgeBegin(); heit != v->incomingHalfEdgeEnd(); ++heit){
 *     const Dcel::HalfEdge* he = *heit;
 *     // operazioni const su he
 * }
 * \endcode
 *
 * È però possibile anche visitare tutti gli half edge entranti compresi tra due dati half edge incidenti. In questo caso sarà necessario
 * passare gli half edge estremi dell'intervallo all'inizializzatore Dcel::Vertex::incomingHalfEdgeBegin(). Per i dettagli su come funzionano queste
 * inizializzazioni si rimanda alla descrizione dei metodi stessi.
 *
 * Questo iteratore garantisce l'immutabilità del vertice della Dcel a cui appartiene, e quindi è possibile utilizzarlo solo su const Dcel::Vertex.
 * Se si ha necessità di modificare i vertici presenti nella Dcel, usare Dcel::Vertex::IncomingHalfEdgeIterator.
 */
class Dcel::Vertex::ConstIncomingHalfEdgeIterator : public Dcel::Vertex::ConstGenericIterator {

        friend class Dcel::Vertex;

    public:
        //Constructors
        ConstIncomingHalfEdgeIterator();
        ConstIncomingHalfEdgeIterator(const Dcel::Vertex::IncomingHalfEdgeIterator& it);

        //Public Operators
        const Dcel::HalfEdge* operator * ()                             const;

    protected:

        //Protected Constructor
        ConstIncomingHalfEdgeIterator(const Dcel::HalfEdge* start, const Dcel::HalfEdge* end, const Dcel::Vertex* v);
};

/**
 * \~Italian
 * @class Dcel::Vertex::IncidentHalfEdgeIterator
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
 * for (Dcel::Vertex::IncidentHalfEdgeIterator heit = v->incidentHalfEdgeBegin(); heit != v->incidentHalfEdgeEnd(); ++heit){
 *     Dcel::HalfEdge* he = *heit;
 *     // operazioni su he
 * }
 * \endcode
 *
 * È però possibile anche visitare tutti gli half edge incidenti compresi tra due dati half edge incidenti. In questo caso sarà necessario
 * passare gli half edge estremi dell'intervallo all'inizializzatore Dcel::Vertex::incidentHalfEdgeBegin(). Per i dettagli su come funzionano queste
 * inizializzazioni si rimanda alla descrizione dei metodi stessi.
 *
 * Questo iteratore non garantisce l'immutabilità del vertice e quindi della Dcel a cui appartiene, e quindi non è possibile
 * utilizzarlo su const Dcel::Vertex. Per const Dcel::Vertex, vedere Dcel::Vertex::ConstIncidentHalfEdgeIterator.
 */
class Dcel::Vertex::IncidentHalfEdgeIterator : public Dcel::Vertex::GenericIterator {

        friend class Dcel::Vertex;

    public:
        //Constructor
        IncidentHalfEdgeIterator();

        //Public Operators
        Dcel::HalfEdge* operator * ()                               const;

        IncidentHalfEdgeIterator operator ++ ();
        IncidentHalfEdgeIterator operator ++ (int);
        IncidentHalfEdgeIterator operator -- ();
        IncidentHalfEdgeIterator operator -- (int);

    protected:

        //Protected Constructor
        IncidentHalfEdgeIterator(Dcel::HalfEdge* start, Dcel::HalfEdge* end, Dcel::Vertex* v);
};

/**
 * \~Italian
 * @class Dcel::Vertex::ConstIncidentHalfEdgeIterator
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
 * for (Dcel::Vertex::ConstIncidentHalfEdgeIterator heit = v->incidentHalfEdgeBegin(); heit != v->incidentHalfEdgeEnd(); ++heit){
 *     const Dcel::HalfEdge* he = *heit;
 *     // operazioni const su he
 * }
 * \endcode
 *
 * È però possibile anche visitare tutti gli half edge incidenti compresi tra due dati half edge incidenti. In questo caso sarà necessario
 * passare gli half edge estremi dell'intervallo all'inizializzatore Dcel::Vertex::incidentHalfEdgeBegin(). Per i dettagli su come funzionano queste
 * inizializzazioni si rimanda alla descrizione dei metodi stessi.
 *
 * Questo iteratore garantisce l'immutabilità del vertice della Dcel a cui appartiene, e quindi è possibile utilizzarlo solo su const Dcel::Vertex.
 * Se si ha necessità di modificare i vertici presenti nella Dcel, usare Dcel::Vertex::IncidentHalfEdgeIterator.
 */
class Dcel::Vertex::ConstIncidentHalfEdgeIterator : public ConstGenericIterator{

        friend class Dcel::Vertex;

    public:
        //Constructors
        ConstIncidentHalfEdgeIterator();
        ConstIncidentHalfEdgeIterator(const Dcel::Vertex::IncidentHalfEdgeIterator& it);

        //Public Operators
        const Dcel::HalfEdge* operator * ()                             const;

        ConstIncidentHalfEdgeIterator operator ++ ();
        ConstIncidentHalfEdgeIterator operator ++ (int);
        ConstIncidentHalfEdgeIterator operator -- ();
        ConstIncidentHalfEdgeIterator operator -- (int);

    protected:

        //Protected Constructor
        ConstIncidentHalfEdgeIterator(const Dcel::HalfEdge* start, const Dcel::HalfEdge* end, const Dcel::Vertex* v);
};

/**
 * \~Italian
 * @class Dcel::Vertex::IncidentFaceIterator
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
 * for (Dcel::Vertex::IncidentFaceIterator heit = v->incidentFaceBegin(); heit != v->incidentFaceEnd(); ++heit){
 *     Dcel::Face* he = *heit;
 *     // operazioni su he
 * }
 * \endcode
 *
 * È però possibile anche visitare tutti le facce incidenti compresi tra due dati half edge incidenti. In questo caso sarà necessario
 * passare gli half edge estremi dell'intervallo all'inizializzatore Dcel::Vertex::incidentFaceBegin(). Per i dettagli su come funzionano queste
 * inizializzazioni si rimanda alla descrizione dei metodi stessi.
 *
 * Questo iteratore non garantisce l'immutabilità del vertice e quindi della Dcel a cui appartiene, e quindi non è possibile
 * utilizzarlo su const Dcel::Vertex. Per const Dcel::Vertex, vedere Dcel::Vertex::ConstFaceIterator.
 *
 * @warning Nel caso di Dcel composte da poligoni generici, è possibile che un vertice abbia la stessa faccia incidente su due punti diversi.
 */
class Dcel::Vertex::IncidentFaceIterator : public Dcel::Vertex::GenericIterator{

        friend class Dcel::Vertex;

    public:
        //Constructor
        IncidentFaceIterator();

        //Public Operators
        Dcel::Face* operator * ()                               const;

    protected:

        //Protected Constructor
        IncidentFaceIterator(Dcel::HalfEdge* start, Dcel::HalfEdge* end, Dcel::Vertex* v);
};

/**
 * \~Italian
 * @class Dcel::Vertex::ConstIncidentFaceIterator
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
 * for (Dcel::Vertex::ConstIncidentFaceIterator heit = v->incidentFaceBegin(); heit != v->incidentFaceEnd(); ++heit){
 *     const Dcel::Face* he = *heit;
 *     // operazioni const su he
 * }
 * \endcode
 *
 * È però possibile anche visitare tutti le facce incidenti compresi tra due dati half edge incidenti. In questo caso sarà necessario
 * passare gli half edge estremi dell'intervallo all'inizializzatore Dcel::Vertex::incidentFaceBegin(). Per i dettagli su come funzionano queste
 * inizializzazioni si rimanda alla descrizione dei metodi stessi.
 *
 * Questo iteratore garantisce l'immutabilità del vertice della Dcel a cui appartiene, e quindi è possibile utilizzarlo solo su const Dcel::Vertex.
 * Se si ha necessità di modificare i vertici presenti nella Dcel, usare Dcel::Vertex::ConstIncidentFaceIterator.
 *
 * @warning Nel caso di Dcel composte da poligoni generici, è possibile che un vertice abbia la stessa faccia incidente su due punti diversi.
 */
class Dcel::Vertex::ConstIncidentFaceIterator : public Dcel::Vertex::ConstGenericIterator {

        friend class Dcel::Vertex;

    public:
        //Constructors
        ConstIncidentFaceIterator();
        ConstIncidentFaceIterator(const Dcel::Vertex::IncidentFaceIterator& it);

        //Public Operators
        const Dcel::Face* operator * ()                             const;

    private:

        //Protected Constructor
        ConstIncidentFaceIterator(const Dcel::HalfEdge* start, const Dcel::HalfEdge* end, const Dcel::Vertex* v);
};

class Dcel::Vertex::ConstAdjacentVertexRangeBasedIterator {
        friend class Vertex;
    public:
        Dcel::Vertex::ConstAdjacentVertexIterator begin() const;
        Dcel::Vertex::ConstAdjacentVertexIterator end() const;
    private:
        ConstAdjacentVertexRangeBasedIterator(const Vertex *v) : v(v) {}
        const Vertex *v;
};

class Dcel::Vertex::ConstOutgoingHalfEdgeRangeBasedIterator {
        friend class Vertex;
    public:
        Dcel::Vertex::ConstOutgoingHalfEdgeIterator begin() const;
        Dcel::Vertex::ConstOutgoingHalfEdgeIterator end() const;
    private:
        ConstOutgoingHalfEdgeRangeBasedIterator(const Vertex *v) : v(v) {}
        const Vertex *v;
};

class Dcel::Vertex::ConstIncomingHalfEdgeRangeBasedIterator {
        friend class Vertex;
    public:
        Dcel::Vertex::ConstIncomingHalfEdgeIterator begin() const;
        Dcel::Vertex::ConstIncomingHalfEdgeIterator end() const;
    private:
        ConstIncomingHalfEdgeRangeBasedIterator(const Vertex *v) : v(v) {}
        const Vertex *v;
};

class Dcel::Vertex::ConstIncidentHalfEdgeRangeBasedIterator {
        friend class Vertex;
    public:
        Dcel::Vertex::ConstIncidentHalfEdgeIterator begin() const;
        Dcel::Vertex::ConstIncidentHalfEdgeIterator end() const;
    private:
        ConstIncidentHalfEdgeRangeBasedIterator(const Vertex *v) : v(v) {}
        const Vertex *v;
};

class Dcel::Vertex::ConstIncidentFaceRangeBasedIterator {
        friend class Vertex;
    public:
        Dcel::Vertex::ConstIncidentFaceIterator begin() const;
        Dcel::Vertex::ConstIncidentFaceIterator end() const;
    private:
        ConstIncidentFaceRangeBasedIterator(const Vertex *v) : v(v) {}
        const Vertex *v;
};

class Dcel::Vertex::AdjacentVertexRangeBasedIterator {
        friend class Vertex;
    public:
        Dcel::Vertex::AdjacentVertexIterator begin();
        Dcel::Vertex::AdjacentVertexIterator end();
    private:
        AdjacentVertexRangeBasedIterator(Vertex *v) : v(v) {}
        Vertex *v;
};

class Dcel::Vertex::OutgoingHalfEdgeRangeBasedIterator {
        friend class Vertex;
    public:
        Dcel::Vertex::OutgoingHalfEdgeIterator begin();
        Dcel::Vertex::OutgoingHalfEdgeIterator end();
    private:
        OutgoingHalfEdgeRangeBasedIterator(Vertex *v) : v(v) {}
        Vertex *v;
};

class Dcel::Vertex::IncomingHalfEdgeRangeBasedIterator {
        friend class Vertex;
    public:
        Dcel::Vertex::IncomingHalfEdgeIterator begin();
        Dcel::Vertex::IncomingHalfEdgeIterator end();
    private:
        IncomingHalfEdgeRangeBasedIterator(Vertex *v) : v(v) {}
        Vertex *v;
};

class Dcel::Vertex::IncidentHalfEdgeRangeBasedIterator {
        friend class Vertex;
    public:
        Dcel::Vertex::IncidentHalfEdgeIterator begin();
        Dcel::Vertex::IncidentHalfEdgeIterator end();
    private:
        IncidentHalfEdgeRangeBasedIterator(Vertex *v) : v(v) {}
        Vertex *v;
};

class Dcel::Vertex::IncidentFaceRangeBasedIterator {
        friend class Vertex;
    public:
        Dcel::Vertex::IncidentFaceIterator begin();
        Dcel::Vertex::IncidentFaceIterator end();
    private:
        IncidentFaceRangeBasedIterator(Vertex *v) : v(v) {}
        Vertex *v;
};

}

#include "dcel_vertex_iterators_inline.tpp"

#endif // CG3_DCEL_VERTEX_ITERATORS_H

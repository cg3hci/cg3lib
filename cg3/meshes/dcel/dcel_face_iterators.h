/**
  * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
  * This Source Code Form is subject to the terms of the GNU GPL 3.0
  *
  * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
  */

#ifndef CG3_DCEL_FACE_ITERATORS_H
#define CG3_DCEL_FACE_ITERATORS_H

#include "dcel_face.h"
#include "dcel_half_edge.h"

namespace cg3 {

/**
 * \~Italian
 * @class Dcel::Face::ConstInnerHalfEdgeIterator
 * @brief Iteratore che permette di ciclare sul vettore degli inner half edge associati alla faccia, garantendone
 * l'immutabilità.
 * Ogni inner half edge è associato ad un buco presente all'interno della faccia.
 * Una volta che si ha a disposizione un inner half edge, è possibile ciclare sul bordo del buco
 * mediante delle semplici operazioni di next, oppure utilizzando un ConstIncidentHalfEdgeIterator opportunamente inizializzato.
 *
 * È possibile utilizzare l'iteratore esattamente come si utilizza un iteratore su un std::vector.
 * Per esempio, data una faccia Dcel::Face* f:
 *
 * \code{.cpp}
 * for (Dcel::Face::ConstInnerHalfEdgeIterator heit = f->innerHalfEgeBegin(); heit != f->innerHalfEdgeEnd(); ++heit){
 *     const Dcel::HalfEdge* he = *heit;
 *     // operazioni const su he
 * }
 * \endcode
 *
 * Questo iteratore garantisce l'immutabilità della faccia e quindi della Dcel a cui appartiene, e quindi è possibile
 * utilizzarlo solamente su const Dcel::Face. Per poter effettuare modifiche, vedere Dcel::Face::InnerHalfEdgeIterator.
 *
 * @author    Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
class Dcel::Face::ConstInnerHalfEdgeIterator {

        friend class Dcel::Face;

    public:
        //Constructors
        ConstInnerHalfEdgeIterator();
        ConstInnerHalfEdgeIterator(const Dcel::Face::InnerHalfEdgeIterator& it);

        //Public Operators
        const Dcel::HalfEdge* operator * ()                                 const;
        bool operator == (const ConstInnerHalfEdgeIterator& otherIterator)  const;
        bool operator != (const ConstInnerHalfEdgeIterator& otherIterator)  const;

        ConstInnerHalfEdgeIterator operator ++ ();
        ConstInnerHalfEdgeIterator operator ++ (int);
        ConstInnerHalfEdgeIterator operator -- ();
        ConstInnerHalfEdgeIterator operator -- (int);

    protected:
        //Protected Attributes
        std::vector<Dcel::HalfEdge*>::const_iterator iterator; /**< \~Italian @brief Iteratore vero e proprio sul vettore degli inner half edge della faccia. */

        //Protected Constructor
        ConstInnerHalfEdgeIterator(const std::vector<Dcel::HalfEdge*>::const_iterator& it);
};

class Dcel::Face::GenericIterator {

        friend class Dcel::Face;

    public:
        //Constructor
        GenericIterator();

        //Public Operators
        void* operator * () const {return nullptr;}
        bool operator == (const GenericIterator& otherIterator)  const;
        bool operator != (const GenericIterator& otherIterator)  const;

        GenericIterator operator ++ ();
        GenericIterator operator ++ (int);
        GenericIterator operator -- ();
        GenericIterator operator -- (int);

    protected:
        //Protected Attributes
        Dcel::Face*     f;      /**< \~Italian @brief Faccia su cui vengono iterati gli half edge incidenti */
        Dcel::HalfEdge* start;  /**< \~Italian @brief Half edge dal quale è partito l'iteratore */
        Dcel::HalfEdge* pos;    /**< \~Italian @brief Posizione attuale dell'iteratore */
        Dcel::HalfEdge* end;    /**< \~Italian @brief Half edge sul quale termina l'iteratore */

        //Protected Constructor
        GenericIterator(Dcel::HalfEdge* start, Dcel::HalfEdge* end, Dcel::Face* f);
};

class Dcel::Face::ConstGenericIterator {

        friend class Dcel::Face;

    public:
        //Constructors
        ConstGenericIterator();
        ConstGenericIterator(const Dcel::Face::GenericIterator& it);

        //Public Operators
        const void* operator * () const {return nullptr;}
        bool operator == (const ConstGenericIterator& otherIterator)   const;
        bool operator != (const ConstGenericIterator& otherIterator)   const;

        ConstGenericIterator operator ++ ();
        ConstGenericIterator operator ++ (int);
        ConstGenericIterator operator -- ();
        ConstGenericIterator operator -- (int);

    protected:
        //Protected Attributes
        const Dcel::Face*     f;        /**< \~Italian @brief Faccia su cui vengono iterati gli half edge incidenti */
        const Dcel::HalfEdge* start;    /**< \~Italian @brief Half edge dal quale è partito l'iteratore */
        const Dcel::HalfEdge* pos;      /**< \~Italian @brief Posizione attuale dell'iteratore */
        const Dcel::HalfEdge* end;      /**< \~Italian @brief Half edge sul quale termina l'iteratore */

        //Protected Constructor
        ConstGenericIterator(const Dcel::HalfEdge* start, const Dcel::HalfEdge* end, const Dcel::Face* f);
};


/**
 * \~Italian
 * @class Dcel::Face::AdjacentFaceIterator
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
 * for (Dcel::Face::AdjacentFaceIterator fit = f->adjacentFaceBegin(); fit != f->adjacentFaceEnd(); ++fit){
 *     Dcel::Face* f = *fit;
 *     // operazioni su f
 * }
 * \endcode
 *
 * È però possibile anche visitare tutte le facce adiacenti comprese tra due dati half edge. In questo caso sarà necessario
 * passare gli half edge estremi dell'intervallo all'inizializzatore Dcel::Face::adjacentFaceBegin(). Per i dettagli su come funzionano queste
 * inizializzazioni si rimanda alla descrizione dei metodi stessi.
 *
 * Questo iteratore non garantisce l'immutabilità della faccia e quindi della Dcel a cui appartiene, e quindi non è possibile
 * utilizzarlo su const Dcel::Face. Per const Dcel::Face, vedere Dcel::Face::ConstAdjacentFaceIterator.
 *
 * @author    Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
class Dcel::Face::AdjacentFaceIterator : public Dcel::Face::GenericIterator{

        friend class Dcel::Face;

    public:
        //Constructor
        AdjacentFaceIterator();

        //Public Operators
        Dcel::Face* operator * ()                                     const;

    protected:
        //Protected Constructor
        AdjacentFaceIterator(Dcel::HalfEdge* start, Dcel::HalfEdge* end, Dcel::Face* f);
};

/**
 * \~Italian
 * @class Dcel::Face::ConstAdjacentFaceIterator
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
 * for (Dcel::Face::AdjacentFaceIterator fit = f->adjacentFaceBegin(); fit != f->adjacentFaceEnd(); ++fit){
 *     Dcel::Face* f = *fit;
 *     // operazioni su f
 * }
 * \endcode
 *
 * È però possibile anche visitare tutte le facce adiacenti comprese tra due dati half edge. In questo caso sarà necessario
 * passare gli half edge estremi dell'intervallo all'inizializzatore Dcel::Face::adjacentFaceBegin(). Per i dettagli su come funzionano queste
 * inizializzazioni si rimanda alla descrizione dei metodi stessi.
 *
 * Questo iteratore garantisce l'immutabilità della faccia e quindi della Dcel a cui appartiene, e quindi si può utilizzare solo
 * su const Dcel::Face. Per Dcel::Face, vedere Dcel::Face::AdjacentFaceIterator.
 *
 * @author    Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
class Dcel::Face::ConstAdjacentFaceIterator : public Dcel::Face::ConstGenericIterator {

        friend class Dcel::Face;

    public:
        //Constructors
        ConstAdjacentFaceIterator();
        ConstAdjacentFaceIterator(const Dcel::Face::AdjacentFaceIterator& it);

        //Public Operators
        const Dcel::Face* operator * ()                                     const;

    protected:

        //Protected Constructor
        ConstAdjacentFaceIterator(const Dcel::HalfEdge* start, const Dcel::HalfEdge* end, const Dcel::Face* f);
};

/**
 * \~Italian
 * @class Dcel::Face::IncidentHalfEdgeIterator
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
 * for (Dcel::Face::IncidentHalfEdgeIterator heit = f->incidentHalfEdgeBegin(); heit != f->incidentHalfEdgeEnd(); ++heit){
 *     Dcel::HalfEdge* he = *heit;
 *     // operazioni su he
 * }
 * \endcode
 *
 * È però possibile anche visitare tutti gli half edge incidenti compresi tra due dati half edge. In questo caso sarà necessario
 * passare gli half edge estremi dell'intervallo all'inizializzatore Dcel::Face::incidentHalfEdgeBegin(). Per i dettagli su come funzionano queste
 * inizializzazioni si rimanda alla descrizione dei metodi stessi.
 *
 * Questo iteratore non garantisce l'immutabilità della faccia e quindi della Dcel a cui appartiene, e quindi non è possibile
 * utilizzarlo su const Dcel::Face. Per const Dcel::Face, vedere Dcel::Face::ConstIncidentHalfEdgeIterator.
 *
 * @author    Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
class Dcel::Face::IncidentHalfEdgeIterator : public Dcel::Face::GenericIterator {

        friend class Dcel::Face;

    public:
        // Constructor
        IncidentHalfEdgeIterator();

        //Public Operators
        Dcel::HalfEdge* operator * ()                                       const;

    protected:

        //Protected Constructor
        IncidentHalfEdgeIterator(Dcel::HalfEdge* start, Dcel::HalfEdge* end, Dcel::Face* f);
};

/**
 * \~Italian
 * @class Dcel::Face::ConstIncidentHalfEdgeIterator
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
 * for (Dcel::Face::ConstIncidentHalfEdgeIterator heit = f->incidentHalfEdgeBegin(); heit != f->incidentHalfEdgeEnd(); ++heit){
 *     const Dcel::HalfEdge* he = *heit;
 *     // operazioni const su he
 * }
 * \endcode
 *
 * È però possibile anche visitare tutti gli half edge incidenti compresi tra due dati half edge. In questo caso sarà necessario
 * passare gli half edge estremi dell'intervallo all'inizializzatore Dcel::Face::incidentHalfEdgeBegin(). Per i dettagli su come funzionano queste
 * inizializzazioni si rimanda alla descrizione dei metodi stessi.
 *
 * Questo iteratore garantisce l'immutabilità della faccia e quindi della Dcel a cui appartiene, e quindi si può utilizzare solo
 * su const Dcel::Face. Per Dcel::Face, vedere Dcel::Face::IncidentHalfEdgeIterator.
 *
 * @author    Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
class Dcel::Face::ConstIncidentHalfEdgeIterator : public Dcel::Face::ConstGenericIterator {

        friend class Dcel::Face;

    public:
        //Constructors
        ConstIncidentHalfEdgeIterator();
        ConstIncidentHalfEdgeIterator(const Dcel::Face::IncidentHalfEdgeIterator& it);

        //Public Operators
        const Dcel::HalfEdge* operator * ()                                     const;

    protected:

        //Protected Constructor
        ConstIncidentHalfEdgeIterator(const Dcel::HalfEdge* start, const Dcel::HalfEdge* end, const Dcel::Face* f);
};

/**
 * \~Italian
 * @class Dcel::Face::IncidentVertexIterator
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
 * for (Dcel::Face::IncidentVertexIterator vit = f->incidentVertexBegin(); vit != f->incidentVertexEnd(); ++vit){
 *     Dcel::Vertex* v = *vit;
 *     // operazioni su v
 * }
 * \endcode
 *
 * È però possibile anche visitare tutti i vertici incidenti compresi tra due dati half edge. In questo caso sarà necessario
 * passare gli half edge estremi dell'intervallo all'inizializzatore Dcel::Face::incidentVertexBegin(). Per i dettagli su come funzionano queste
 * inizializzazioni si rimanda alla descrizione dei metodi stessi.
 *
 * Questo iteratore non garantisce l'immutabilità della faccia e quindi della Dcel a cui appartiene, e quindi non è possibile
 * utilizzarlo su const Dcel::Face. Per const Dcel::Face, vedere Dcel::Face::ConstIncidentVertexIterator.
 *
 * @author    Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
class Dcel::Face::IncidentVertexIterator : public Dcel::Face::GenericIterator {

        friend class Dcel::Face;

    public:
        //Constructor
        IncidentVertexIterator();

        //Public Operators
        Dcel::Vertex* operator * ()                                     const;

    protected:

        //Protected Constructor
        IncidentVertexIterator(Dcel::HalfEdge* start, Dcel::HalfEdge* end, Dcel::Face* f);
};

/**
 * \~Italian
 * @class Dcel::Face::ConstIncidentVertexIterator
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
 * for (Dcel::Face::ConstIncidentVertexIterator vit = f->incidentVertexBegin(); vit != f->incidentVertexEnd(); ++vit){
 *     const Dcel::Vertex* v = *vit;
 *     // operazioni const su v
 * }
 * \endcode
 *
 * È però possibile anche visitare tutti i vertici incidenti compresi tra due dati half edge. In questo caso sarà necessario
 * passare gli half edge estremi dell'intervallo all'inizializzatore Dcel::Face::incidentVertexBegin(). Per i dettagli su come funzionano queste
 * inizializzazioni si rimanda alla descrizione dei metodi stessi.
 *
 * Questo iteratore garantisce l'immutabilità della faccia e quindi della Dcel a cui appartiene, e quindi è possibile utilizzarlo solamente
 * su const Dcel::Face. Per Dcel::Face, vedere Dcel::Face::IncidentVertexIterator.
 *
 * @author    Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
class Dcel::Face::ConstIncidentVertexIterator : public Dcel::Face::ConstGenericIterator {

        friend class Dcel::Face;

    public:
        //Constructors
        ConstIncidentVertexIterator();
        ConstIncidentVertexIterator(const Dcel::Face::IncidentVertexIterator& it);

        //Public Operators
        const Dcel::Vertex* operator * ()                                   const;

    protected:

        //Protected Constructor
        ConstIncidentVertexIterator(const Dcel::HalfEdge* start, const Dcel::HalfEdge* end, const Dcel::Face* f);
};

class Dcel::Face::ConstAdjacentFaceRangeBasedIterator {
        friend class Face;
    public:
        Dcel::Face::ConstAdjacentFaceIterator begin() const;
        Dcel::Face::ConstAdjacentFaceIterator end() const;
    private:
        ConstAdjacentFaceRangeBasedIterator(const Face *f) : f(f) {}
        const Face *f;
};

class Dcel::Face::ConstIncidentHalfEdgeRangeBasedIterator {
        friend class Face;
    public:
        Dcel::Face::ConstIncidentHalfEdgeIterator begin() const;
        Dcel::Face::ConstIncidentHalfEdgeIterator end() const;
    private:
        ConstIncidentHalfEdgeRangeBasedIterator(const Face *f) : f(f) {}
        const Face *f;
};

class Dcel::Face::ConstIncidentVertexRangeBasedIterator {
        friend class Face;
    public:
        Dcel::Face::ConstIncidentVertexIterator begin() const;
        Dcel::Face::ConstIncidentVertexIterator end() const;
    private:
        ConstIncidentVertexRangeBasedIterator(const Face *f) : f(f) {}
        const Face *f;
};

class Dcel::Face::AdjacentFaceRangeBasedIterator {
        friend class Face;
    public:
        Dcel::Face::AdjacentFaceIterator begin();
        Dcel::Face::AdjacentFaceIterator end();
    private:
        AdjacentFaceRangeBasedIterator(Face *f) : f(f) {}
        Face *f;
};

class Dcel::Face::IncidentHalfEdgeRangeBasedIterator {
        friend class Face;
    public:
        Dcel::Face::IncidentHalfEdgeIterator begin();
        Dcel::Face::IncidentHalfEdgeIterator end();
    private:
        IncidentHalfEdgeRangeBasedIterator(Face *f) : f(f) {}
        Face *f;
};

class Dcel::Face::IncidentVertexRangeBasedIterator {
        friend class Face;
    public:
        Dcel::Face::IncidentVertexIterator begin();
        Dcel::Face::IncidentVertexIterator end();
    private:
        IncidentVertexRangeBasedIterator(Face *f) : f(f) {}
        Face *f;
};

}

#include "dcel_face_iterators_inline.tpp"

#endif // CG3_DCEL_FACE_ITERATORS_H

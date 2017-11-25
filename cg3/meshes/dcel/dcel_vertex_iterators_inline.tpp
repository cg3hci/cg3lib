/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * @author    Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "dcel_vertex_iterators.h"

namespace cg3 {

/****************************************
 * DCEL::Vertex::GenericIterator *
 ****************************************/

//Constructor

/**
 * \~Italian
 * @brief Costruttore vuoto.
 * Un iteratore inizializzato con questo costruttore non è utilizzabile.
 */
inline Dcel::Vertex::GenericIterator::GenericIterator() {
}

//Public Operators

/**
 * \~Italian
 * @brief Operatore di uguaglianza tra iteratori.
 *
 * Due AdjacentVertexIterator sono considerati uguali se:
 * - puntano allo stesso vertice (posizione sullo stesso half edge);
 * - iterano sulla stessa faccia.
 *
 *
 * @param[in] otherIterator: iteratore con cui è verificata l'uguaglianza con this
 * @return True se gli iteratori sono uguali, false altrimenti
 */
inline bool Dcel::Vertex::GenericIterator::operator == (const GenericIterator& right) const {
    if (this->pos == right.pos && this->v == right.v) return true;
    return false;
}

/**
 * \~Italian
 * @brief Operatore di disuguaglianza tra iteratori
 * @param[in] otherIterator: iteratore con cui è verificata la disuguaglianza con this
 * @return true se gli iteratori sono diversi, false altrimenti
 */
inline bool Dcel::Vertex::GenericIterator::operator != (const GenericIterator& right) const {
    return !(*this == right);
}

/**
 * \~Italian
 * @brief Operatore di incremento prefisso dell'iteratore.
 *
 * Esegue un'operazione di \c twin() e \c next() sull'half edge. Se l'half edge ottenuto è uguale
 * all'half edge end, allora l'iteratore diventa uguale all'iteratore \c end().
 *
 * @return L'iteratore appena incrementato
 */
inline Dcel::Vertex::GenericIterator Dcel::Vertex::GenericIterator::operator ++ () {
    pos = pos->getTwin()->getNext();
    if (pos == end) pos = nullptr;
    return *this;
}

/**
 * \~Italian
 * @brief Operatore di incremento postfisso dell'iteratore.
 *
 * Esegue un'operazione di \c twin() e \c next() sull'half edge. Se l'half edge ottenuto è uguale
 * all'half edge end, allora l'iteratore diventa uguale all'iteratore \c end().
 *
 * @return L'iteratore prima di essere incrementato
 */
inline Dcel::Vertex::GenericIterator Dcel::Vertex::GenericIterator::operator ++ (int) {
    GenericIterator old_value = *this;
    pos = pos->getTwin()->getNext();
    if (pos == end) pos = nullptr;
    return old_value;
}

/**
 * \~Italian
 * @brief Operatore di decremento prefisso dell'iteratore.
 *
 * Esegue un'operazione di \c prev() e \c twin() sull'half edge. Se l'half edge ottenuto è uguale
 * all'half edge end, allora l'iteratore diventa uguale all'iteratore \c end().
 *
 * @return L'iteratore appena decrementato
 */
inline Dcel::Vertex::GenericIterator Dcel::Vertex::GenericIterator::operator -- () {
    pos = pos->getPrev()->getTwin();
    if (pos == end) pos = nullptr;
    return *this;
}

/**
 * \~Italian
 * @brief Operatore di decremento postfisso dell'iteratore.
 *
 * Esegue un'operazione di \c prev() e \c twin() sull'half edge. Se l'half edge ottenuto è uguale
 * all'half edge end, allora l'iteratore diventa uguale all'iteratore \c end().
 *
 * @return L'iteratore prima di essere decrementato
 */
inline Dcel::Vertex::GenericIterator Dcel::Vertex::GenericIterator::operator -- (int) {
    GenericIterator old_value = *this;
    pos = pos->getPrev()->getTwin();
    if (pos == end) pos = nullptr;
    return old_value;
}

//Protected Constructor

/**
 * \~Italian
 * @brief Costruttore di un iteratore.
 *
 * Setta l'half edge di partenza, l'half edge di arrivo e il vertice su cui iterare.
 * L'iteratore viene inizializzato all'half edge start.
 * Per questioni di sicurezza e di robustezza del codice questo costruttore non è direttamente richiamabile
 * dal programmatore. Tuttavia, questo costruttore viene richiamato dalla friend class Dcel::Vertex nei vari metodi
 * begin, che inizializzano correttamente l'iteratore e che possono essere utilizzati dal programmatore per
 * l'inizializzazione dell'iteratore.
 *
 * @param[in] start: half edge (uscente dal vertice) di start
 * @param[in] end: half edge (uscente dal vertice) di end
 * @param[in] v: vertice su cui vengono iterati i vertici adiacenti
 */
inline Dcel::Vertex::GenericIterator::GenericIterator(HalfEdge* start, HalfEdge* end, Vertex* v) : v(v), start(start), pos(start), end(end) {
}

/*********************************************
 * DCEL::Vertex::ConstGenericIterator *
 *********************************************/

//Constructors

/**
 * \~Italian
 * @brief Costruttore vuoto.
 * Un iteratore inizializzato con questo costruttore non è utilizzabile.
 */
inline Dcel::Vertex::ConstGenericIterator::ConstGenericIterator() {
}

/**
 * \~Italian
 * @brief Costruttore di copia da un iteratore const.
 *
 * Inizializza un ConstAdjacentVertexIterator pari all'AdjacentVertexIterator passato in input.
 * @param[in] it: iteratore di cui ne verrà fatta una copia
 */
inline Dcel::Vertex::ConstGenericIterator::ConstGenericIterator(const Dcel::Vertex::GenericIterator& it) : v(it.v), start(it.start), pos(it.pos), end(it.end) {
}

//Public Operators

/**
 * \~Italian
 * @brief Operatore di uguaglianza tra iteratori const.
 *
 * Due AdjacentVertexIterator sono considerati uguali se:
 * - puntano allo stesso vertice (posizione sullo stesso half edge);
 * - iterano sulla stessa faccia.
 *
 *
 * @param[in] otherIterator: iteratore con cui è verificata l'uguaglianza con this
 * @return True se gli iteratori sono uguali, false altrimenti
 */
inline bool Dcel::Vertex::ConstGenericIterator::operator == (const ConstGenericIterator& right) const {
    if (this->pos == right.pos && this->v == right.v) return true;
    return false;
}

/**
 * \~Italian
 * @brief Operatore di disuguaglianza tra iteratori const
 * @param[in] otherIterator: iteratore con cui è verificata la disuguaglianza con this
 * @return true se gli iteratori sono diversi, false altrimenti
 */
inline bool Dcel::Vertex::ConstGenericIterator::operator !=(const ConstGenericIterator& right) const {
    return !(*this == right);
}

/**
 * \~Italian
 * @brief Operatore di incremento prefisso dell'iteratore const.
 *
 * Esegue un'operazione di \c prev() e \c twin() sull'half edge. Se l'half edge ottenuto è uguale
 * all'half edge end, allora l'iteratore diventa uguale all'iteratore \c end().
 *
 * @return L'iteratore appena incrementato
 */
inline Dcel::Vertex::ConstGenericIterator Dcel::Vertex::ConstGenericIterator::operator ++ () {
    pos = pos->getPrev()->getTwin();
    if (pos == end) pos = nullptr;
    return *this;
}

/**
 * \~Italian
 * @brief Operatore di incremento postfisso dell'iteratore const.
 *
 * Esegue un'operazione di \c prev() e \c twin() sull'half edge. Se l'half edge ottenuto è uguale
 * all'half edge end, allora l'iteratore diventa uguale all'iteratore \c end().
 *
 * @return L'iteratore prima di essere incrementato
 */
inline Dcel::Vertex::ConstGenericIterator Dcel::Vertex::ConstGenericIterator::operator ++ (int) {
    ConstGenericIterator old_value = *this;
    pos = pos->getPrev()->getTwin();
    if (pos == end) pos = nullptr;
    return old_value;
}

/**
 * \~Italian
 * @brief Operatore di decremento prefisso dell'iteratore const.
 *
 * Esegue un'operazione di \c twin() e \c next() sull'half edge. Se l'half edge ottenuto è uguale
 * all'half edge end, allora l'iteratore diventa uguale all'iteratore \c end().
 *
 * @return L'iteratore appena decrementato
 */
inline Dcel::Vertex::ConstGenericIterator Dcel::Vertex::ConstGenericIterator::operator -- () {
    if (pos->getTwin() == nullptr)
        pos = nullptr;
    else {
        pos = pos->getTwin()->getNext();
        if (pos == end) pos = nullptr;
    }
    return *this;
}

/**
 * \~Italian
 * @brief Operatore di decremento postfisso dell'iteratore const.
 *
 * Esegue un'operazione di \c twin() e \c next() sull'half edge. Se l'half edge ottenuto è uguale
 * all'half edge end, allora l'iteratore diventa uguale all'iteratore \c end().
 *
 * @return L'iteratore prima di essere decrementato
 */
inline Dcel::Vertex::ConstGenericIterator Dcel::Vertex::ConstGenericIterator::operator -- (int) {
    ConstGenericIterator old_value = *this;
    if (pos->getTwin() == nullptr)
        pos = nullptr;
    else {
        pos = pos->getTwin()->getNext();
        if (pos == end) pos = nullptr;
    }
    return old_value;
}

//Protected Constructor

/**
 * \~Italian
 * @brief Costruttore di un iteratore const.
 *
 * Setta l'half edge di partenza, l'half edge di arrivo e il vertice su cui iterare.
 * L'iteratore viene inizializzato all'half edge start.
 * Per questioni di sicurezza e di robustezza del codice questo costruttore non è direttamente richiamabile
 * dal programmatore. Tuttavia, questo costruttore viene richiamato dalla friend class Dcel::Vertex nei vari metodi
 * begin, che inizializzano correttamente l'iteratore e che possono essere utilizzati dal programmatore per
 * l'inizializzazione dell'iteratore.
 *
 * @param[in] start: half edge (uscente dal vertice) di start
 * @param[in] end: half edge (uscente dal vertice) di end
 * @param[in] v: vertice su cui vengono iterati i vertici adiacenti
 */
inline Dcel::Vertex::ConstGenericIterator::ConstGenericIterator(const Dcel::HalfEdge* start, const Dcel::HalfEdge* end, const Dcel::Vertex* v) : v(v), start(start), pos(start), end(end) {
}

/****************************************
 * DCEL::Vertex::AdjacentVertexIterator *
 ****************************************/

//Constructor

/**
 * \~Italian
 * @brief Costruttore vuoto.
 * Un iteratore inizializzato con questo costruttore non è utilizzabile.
 */
inline Dcel::Vertex::AdjacentVertexIterator::AdjacentVertexIterator() : GenericIterator() {
}

//Public Operators

/**
 * \~Italian
 * @brief Operatore di dereferenziazione dell'AdjacentVertexIterator
 * @return Il to vertex dell'half edge puntato dall'iteratore
 */
inline Dcel::Vertex* Dcel::Vertex::AdjacentVertexIterator::operator * () const {
    return pos->getToVertex();
}

//Protected Constructor

/**
 * \~Italian
 * @brief Costruttore di un AdjacentVertexIterator.
 *
 * Setta l'half edge di partenza, l'half edge di arrivo e il vertice su cui iterare.
 * L'iteratore viene inizializzato all'half edge start.
 * Per questioni di sicurezza e di robustezza del codice questo costruttore non è direttamente richiamabile
 * dal programmatore. Tuttavia, questo costruttore viene richiamato dalla friend class Dcel::Vertex nei vari metodi
 * begin, che inizializzano correttamente l'iteratore e che possono essere utilizzati dal programmatore per
 * l'inizializzazione dell'iteratore.
 *
 * @param[in] start: half edge (uscente dal vertice) di start
 * @param[in] end: half edge (uscente dal vertice) di end
 * @param[in] v: vertice su cui vengono iterati i vertici adiacenti
 */
inline Dcel::Vertex::AdjacentVertexIterator::AdjacentVertexIterator(HalfEdge* start, HalfEdge* end, Vertex* v) : GenericIterator(start, end, v) {
}

/*********************************************
 * DCEL::Vertex::ConstAdjacentVertexIterator *
 *********************************************/

//Constructors

/**
 * \~Italian
 * @brief Costruttore vuoto.
 * Un iteratore inizializzato con questo costruttore non è utilizzabile.
 */
inline Dcel::Vertex::ConstAdjacentVertexIterator::ConstAdjacentVertexIterator() : ConstGenericIterator(){
}

/**
 * \~Italian
 * @brief Costruttore di copia da un AdjacentVertexIterator.
 *
 * Inizializza un ConstAdjacentVertexIterator pari all'AdjacentVertexIterator passato in input.
 * @param[in] it: iteratore di cui ne verrà fatta una copia
 */
inline Dcel::Vertex::ConstAdjacentVertexIterator::ConstAdjacentVertexIterator(const Dcel::Vertex::AdjacentVertexIterator& it) : ConstGenericIterator(it) {
}

//Public Operators

/**
 * \~Italian
 * @brief Operatore di dereferenziazione dell'ConstAdjacentVertexIterator
 * @return Il to vertex dell'half edge puntato dall'iteratore
 */
inline const Dcel::Vertex* Dcel::Vertex::ConstAdjacentVertexIterator::operator * () const {
    return pos->getToVertex();
}

//Protected Constructor

/**
 * \~Italian
 * @brief Costruttore di un ConstAdjacentVertexIterator.
 *
 * Setta l'half edge di partenza, l'half edge di arrivo e il vertice su cui iterare.
 * L'iteratore viene inizializzato all'half edge start.
 * Per questioni di sicurezza e di robustezza del codice questo costruttore non è direttamente richiamabile
 * dal programmatore. Tuttavia, questo costruttore viene richiamato dalla friend class Dcel::Vertex nei vari metodi
 * begin, che inizializzano correttamente l'iteratore e che possono essere utilizzati dal programmatore per
 * l'inizializzazione dell'iteratore.
 *
 * @param[in] start: half edge (uscente dal vertice) di start
 * @param[in] end: half edge (uscente dal vertice) di end
 * @param[in] v: vertice su cui vengono iterati i vertici adiacenti
 */
inline Dcel::Vertex::ConstAdjacentVertexIterator::ConstAdjacentVertexIterator(const Dcel::HalfEdge* start, const Dcel::HalfEdge* end, const Dcel::Vertex* v) : ConstGenericIterator(start, end, v) {
}

/******************************************
 * DCEL::Vertex::OutgoingHalfEdgeIterator *
 ******************************************/

//Constructor

/**
 * \~Italian
 * @brief Costruttore vuoto.
 * Un iteratore inizializzato con questo costruttore non è utilizzabile.
 */
inline Dcel::Vertex::OutgoingHalfEdgeIterator::OutgoingHalfEdgeIterator() : GenericIterator() {
}

//Public Operators

/**
 * \~Italian
 * @brief Operatore di dereferenziazione dell'OutgoingHalfEdgeIterator
 * @return L'half edge puntato dall'iteratore
 */
inline Dcel::HalfEdge* Dcel::Vertex::OutgoingHalfEdgeIterator::operator * () const {
    return pos;
}

//Protected Constructor

/**
 * \~Italian
 * @brief Costruttore di un OutgoingHalfEdgeIterator.
 *
 * Setta l'half edge di partenza, l'half edge di arrivo e il vertice su cui iterare.
 * L'iteratore viene inizializzato all'half edge start.
 * Per questioni di sicurezza e di robustezza del codice questo costruttore non è direttamente richiamabile
 * dal programmatore. Tuttavia, questo costruttore viene richiamato dalla friend class Dcel::Vertex nei vari metodi
 * begin, che inizializzano correttamente l'iteratore e che possono essere utilizzati dal programmatore per
 * l'inizializzazione dell'iteratore.
 *
 * @param[in] start: half edge (uscente dal vertice) di start
 * @param[in] end: half edge (uscente dal vertice) di end
 * @param[in] v: vertice su cui vengono iterati gli half edge uscenti
 */
inline Dcel::Vertex::OutgoingHalfEdgeIterator::OutgoingHalfEdgeIterator(HalfEdge* start, HalfEdge* end, Vertex* v) : GenericIterator(start, end, v) {
}

/***********************************************
 * DCEL::Vertex::ConstOutgoingHalfEdgeIterator *
 ***********************************************/

//Constructors

/**
 * \~Italian
 * @brief Costruttore vuoto.
 * Un iteratore inizializzato con questo costruttore non è utilizzabile.
 */
inline Dcel::Vertex::ConstOutgoingHalfEdgeIterator::ConstOutgoingHalfEdgeIterator() : ConstGenericIterator(){
}

/**
 * \~Italian
 * @brief Costruttore di copia da un OutgoingHalfEdgeIterator.
 *
 * Inizializza un ConstOutgoingHalfEdgeIterator pari all'OutgoingHalfEdgeIterator passato in input.
 * @param[in] it: iteratore di cui ne verrà fatta una copia
 */
inline Dcel::Vertex::ConstOutgoingHalfEdgeIterator::ConstOutgoingHalfEdgeIterator(const Dcel::Vertex::OutgoingHalfEdgeIterator& it) : ConstGenericIterator(it) {
}

//Public Operators

/**
 * \~Italian
 * @brief Operatore di dereferenziazione del ConstOutgoingHalfEdgeIterator
 * @return L'half edge puntato dall'iteratore
 */
inline const Dcel::HalfEdge* Dcel::Vertex::ConstOutgoingHalfEdgeIterator::operator * () const {
    return pos;
}

//Protected Constructor

/**
 * \~Italian
 * @brief Costruttore di un ConstOutgoingHalfEdgeIterator.
 *
 * Setta l'half edge di partenza, l'half edge di arrivo e il vertice su cui iterare.
 * L'iteratore viene inizializzato all'half edge start.
 * Per questioni di sicurezza e di robustezza del codice questo costruttore non è direttamente richiamabile
 * dal programmatore. Tuttavia, questo costruttore viene richiamato dalla friend class Dcel::Vertex nei vari metodi
 * begin, che inizializzano correttamente l'iteratore e che possono essere utilizzati dal programmatore per
 * l'inizializzazione dell'iteratore.
 *
 * @param[in] start: half edge (uscente dal vertice) di start
 * @param[in] end: half edge (uscente dal vertice) di end
 * @param[in] v: vertice su cui vengono iterati gli half edge uscenti
 */
inline Dcel::Vertex::ConstOutgoingHalfEdgeIterator::ConstOutgoingHalfEdgeIterator(const Dcel::HalfEdge* start, const Dcel::HalfEdge* end, const Dcel::Vertex* v) : ConstGenericIterator(start, end, v) {
}

/******************************************
 * DCEL::Vertex::IncomingHalfEdgeIterator *
 ******************************************/

//Constructor

/**
 * \~Italian
 * @brief Costruttore vuoto.
 * Un iteratore inizializzato con questo costruttore non è utilizzabile.
 */
inline Dcel::Vertex::IncomingHalfEdgeIterator::IncomingHalfEdgeIterator() : GenericIterator() {
}

//Public Operators

/**
 * \~Italian
 * @brief Operatore di dereferenziazione dell'IncomingHalfEdgeIterator
 * @return Il twin dell'half edge puntato dall'iteratore
 */
inline Dcel::HalfEdge* Dcel::Vertex::IncomingHalfEdgeIterator::operator * () const {
    return pos->getTwin();
}

//Protected Constructor

/**
 * \~Italian
 * @brief Costruttore di un IncomingHalfEdgeIterator.
 *
 * Setta l'half edge di partenza, l'half edge di arrivo e il vertice su cui iterare.
 * L'iteratore viene inizializzato all'half edge start.
 * Per questioni di sicurezza e di robustezza del codice questo costruttore non è direttamente richiamabile
 * dal programmatore. Tuttavia, questo costruttore viene richiamato dalla friend class Dcel::Vertex nei vari metodi
 * begin, che inizializzano correttamente l'iteratore e che possono essere utilizzati dal programmatore per
 * l'inizializzazione dell'iteratore.
 *
 * @param[in] start: half edge (uscente dal vertice) di start
 * @param[in] end: half edge (uscente dal vertice) di end
 * @param[in] v: vertice su cui vengono iterati gli half edge entranti
 */
inline Dcel::Vertex::IncomingHalfEdgeIterator::IncomingHalfEdgeIterator(HalfEdge* start, HalfEdge* end, Vertex* v) : GenericIterator(start, end, v) {
}

/***********************************************
 * DCEL::Vertex::ConstIncomingHalfEdgeIterator *
 ***********************************************/

//Constructors

/**
 * \~Italian
 * @brief Costruttore vuoto.
 * Un iteratore inizializzato con questo costruttore non è utilizzabile.
 */
inline Dcel::Vertex::ConstIncomingHalfEdgeIterator::ConstIncomingHalfEdgeIterator() : ConstGenericIterator(){
}

/**
 * \~Italian
 * @brief Costruttore di copia da un IncomingHalfEdgeIterator.
 *
 * Inizializza un ConstIncomingHalfEdgeIterator pari all'IncomingHalfEdgeIterator passato in input.
 * @param[in] it: iteratore di cui ne verrà fatta una copia
 */
inline Dcel::Vertex::ConstIncomingHalfEdgeIterator::ConstIncomingHalfEdgeIterator(const Dcel::Vertex::IncomingHalfEdgeIterator& it) : ConstGenericIterator(it) {
}

//Public Operators

/**
 * \~Italian
 * @brief Operatore di dereferenziazione del ConstIncomingHalfEdgeIterator
 * @return Il twin dell'half edge puntato dall'iteratore
 */
inline const Dcel::HalfEdge* Dcel::Vertex::ConstIncomingHalfEdgeIterator::operator * () const {
    return pos->getTwin();
}

//Protected Constructor

/**
 * \~Italian
 * @brief Costruttore di un ConstIncomingHalfEdgeIterator.
 *
 * Setta l'half edge di partenza, l'half edge di arrivo e il vertice su cui iterare.
 * L'iteratore viene inizializzato all'half edge start.
 * Per questioni di sicurezza e di robustezza del codice questo costruttore non è direttamente richiamabile
 * dal programmatore. Tuttavia, questo costruttore viene richiamato dalla friend class Dcel::Vertex nei vari metodi
 * begin, che inizializzano correttamente l'iteratore e che possono essere utilizzati dal programmatore per
 * l'inizializzazione dell'iteratore.
 *
 * @param[in] start: half edge (uscente dal vertice) di start
 * @param[in] end: half edge (uscente dal vertice) di end
 * @param[in] v: vertice su cui vengono iterati gli half edge entranti
 */
inline Dcel::Vertex::ConstIncomingHalfEdgeIterator::ConstIncomingHalfEdgeIterator(const Dcel::HalfEdge* start, const Dcel::HalfEdge* end, const Dcel::Vertex* v) : ConstGenericIterator(start, end, v) {
}

/******************************************
 * DCEL::Vertex::IncidentHalfEdgeIterator *
 ******************************************/

//Constructor

/**
 * \~Italian
 * @brief Costruttore vuoto.
 * Un iteratore inizializzato con questo costruttore non è utilizzabile.
 */
inline Dcel::Vertex::IncidentHalfEdgeIterator::IncidentHalfEdgeIterator() : GenericIterator(){
}

//Public Operators

/**
 * \~Italian
 * @brief Operatore di dereferenziazione dell'IncidentHalfEdgeIterator
 * @return L'half edge puntato dall'iteratore
 */
inline Dcel::HalfEdge* Dcel::Vertex::IncidentHalfEdgeIterator::operator * () const {
    return pos;
}

/**
 * \~Italian
 * @brief Operatore di incremento prefisso dell'IncidentHalfEdgeIterator.
 *
 * Esegue un'operazione di \c prev() se l'half edge attuale è uscente dal vertice su cui cicla l'iteratore,
 * mentre esegue un'operazione di \c twin() se l'half edge attuale è entrante sul vertice. Se l'half edge
 * ottenuto è uguale all'half edge end, allora l'iteratore diventa uguale all'iteratore \c end().
 *
 * @return L'iteratore appena incrementato
 */
inline Dcel::Vertex::IncidentHalfEdgeIterator Dcel::Vertex::IncidentHalfEdgeIterator::operator ++ () {
    if (pos->getFromVertex() == v) pos = pos->getPrev();
    else pos = pos->getTwin();
    if (pos == end) pos = nullptr;
    return *this;
}

/**
 * \~Italian
 * @brief Operatore di incremento postfisso dell'IncidentHalfEdgeIterator.
 *
 * Esegue un'operazione di \c prev() se l'half edge attuale è uscente dal vertice su cui cicla l'iteratore,
 * mentre esegue un'operazione di \c twin() se l'half edge attuale è entrante sul vertice. Se l'half edge
 * ottenuto è uguale all'half edge end, allora l'iteratore diventa uguale all'iteratore \c end().
 *
 * @return L'iteratore prima di essere incrementato
 */
inline Dcel::Vertex::IncidentHalfEdgeIterator Dcel::Vertex::IncidentHalfEdgeIterator::operator ++ (int) {
    IncidentHalfEdgeIterator old_value = *this;
    if (pos->getFromVertex() == v) pos = pos->getPrev();
    else pos = pos->getTwin();
    if (pos == end) pos = nullptr;
    return old_value;
}

/**
 * \~Italian
 * @brief Operatore di decremento prefisso dell'IncidentHalfEdgeIterator.
 *
 * Esegue un'operazione di \c twin() se l'half edge attuale è uscente dal vertice su cui cicla l'iteratore,
 * mentre esegue un'operazione di \c next() se l'half edge attuale è entrante sul vertice. Se l'half edge
 * ottenuto è uguale all'half edge end, allora l'iteratore diventa uguale all'iteratore \c end().
 *
 * @return L'iteratore appena decrementato
 */
inline Dcel::Vertex::IncidentHalfEdgeIterator Dcel::Vertex::IncidentHalfEdgeIterator::operator -- () {
    if (pos->getFromVertex() == v) pos = pos->getTwin();
    else pos = pos->getNext();
    if (pos == end) pos = nullptr;
    return *this;
}

/**
 * \~Italian
 * @brief Operatore di decremento postfisso dell'IncidentHalfEdgeIterator.
 *
 * Esegue un'operazione di \c twin() se l'half edge attuale è uscente dal vertice su cui cicla l'iteratore,
 * mentre esegue un'operazione di \c next() se l'half edge attuale è entrante sul vertice. Se l'half edge
 * ottenuto è uguale all'half edge end, allora l'iteratore diventa uguale all'iteratore \c end().
 *
 * @return L'iteratore prima di essere decrementato
 */
inline Dcel::Vertex::IncidentHalfEdgeIterator Dcel::Vertex::IncidentHalfEdgeIterator::operator -- (int) {
    IncidentHalfEdgeIterator old_value = *this;
    if (pos->getFromVertex() == v) pos = pos->getTwin();
    else pos = pos->getNext();
    if (pos == end) pos = nullptr;
    return old_value;
}

//Protected Constructor

/**
 * \~Italian
 * @brief Costruttore di un IncidentHalfEdgeIterator.
 *
 * Setta l'half edge di partenza, l'half edge di arrivo e il vertice su cui iterare.
 * L'iteratore viene inizializzato all'half edge start.
 * Per questioni di sicurezza e di robustezza del codice questo costruttore non è direttamente richiamabile
 * dal programmatore. Tuttavia, questo costruttore viene richiamato dalla friend class Dcel::Vertex nei vari metodi
 * begin, che inizializzano correttamente l'iteratore e che possono essere utilizzati dal programmatore per
 * l'inizializzazione dell'iteratore.
 *
 * @param[in] start: half edge (non per forza uscente dal vertice) di start
 * @param[in] end: half edge (non per forza uscente dal vertice) di end
 * @param[in] v: vertice su cui vengono iterati gli half edge incidenti
 */
inline Dcel::Vertex::IncidentHalfEdgeIterator::IncidentHalfEdgeIterator(HalfEdge* start, HalfEdge* end, Vertex* v) : GenericIterator(start, end, v) {
}

/***********************************************
 * DCEL::Vertex::ConstIncidentHalfEdgeIterator *
 ***********************************************/

//Constructors

/**
 * \~Italian
 * @brief Costruttore vuoto.
 * Un iteratore inizializzato con questo costruttore non è utilizzabile.
 */
inline Dcel::Vertex::ConstIncidentHalfEdgeIterator::ConstIncidentHalfEdgeIterator() : ConstGenericIterator(){
}

/**
 * \~Italian
 * @brief Costruttore di copia da un IncidentHalfEdgeIterator.
 *
 * Inizializza un ConstIncidentHalfEdgeIterator pari all'IncidentHalfEdgeIterator passato in input.
 * @param[in] it: iteratore di cui ne verrà fatta una copia
 */
inline Dcel::Vertex::ConstIncidentHalfEdgeIterator::ConstIncidentHalfEdgeIterator(const Dcel::Vertex::IncidentHalfEdgeIterator& it) : ConstGenericIterator(it) {
}

//Public Operators

/**
 * \~Italian
 * @brief Operatore di dereferenziazione del ConstIncidentHalfEdgeIterator
 * @return L'half edge puntato dall'iteratore
 */
inline const Dcel::HalfEdge* Dcel::Vertex::ConstIncidentHalfEdgeIterator::operator * () const {
    return pos;
}

/**
 * \~Italian
 * @brief Operatore di incremento prefisso del ConstIncidentHalfEdgeIterator.
 *
 * Esegue un'operazione di \c twin() se l'half edge attuale è uscente dal vertice su cui cicla l'iteratore,
 * mentre esegue un'operazione di \c next() se l'half edge attuale è entrante sul vertice. Se l'half edge
 * ottenuto è uguale all'half edge end, allora l'iteratore diventa uguale all'iteratore \c end().
 *
 * @return L'iteratore appena incrementato
 */
inline Dcel::Vertex::ConstIncidentHalfEdgeIterator Dcel::Vertex::ConstIncidentHalfEdgeIterator::operator ++ () {
    if (pos->getFromVertex() == v) pos = pos->getTwin();
    else pos = pos->getNext();
    if (pos == end) pos = nullptr;
    return *this;
}

/**
 * \~Italian
 * @brief Operatore di incremento postfisso del ConstIncidentHalfEdgeIterator.
 *
 * Esegue un'operazione di \c twin() se l'half edge attuale è uscente dal vertice su cui cicla l'iteratore,
 * mentre esegue un'operazione di \c next() se l'half edge attuale è entrante sul vertice. Se l'half edge
 * ottenuto è uguale all'half edge end, allora l'iteratore diventa uguale all'iteratore \c end().
 *
 * @return L'iteratore prima di essere incrementato
 */
inline Dcel::Vertex::ConstIncidentHalfEdgeIterator Dcel::Vertex::ConstIncidentHalfEdgeIterator::operator ++ (int) {
    ConstIncidentHalfEdgeIterator old_value = *this;
    if (pos->getFromVertex() == v) pos = pos->getTwin();
    else pos = pos->getNext();
    if (pos == end) pos = nullptr;
    return old_value;
}

/**
 * \~Italian
 * @brief Operatore di decremento prefisso del ConstIncidentHalfEdgeIterator.
 *
 * Esegue un'operazione di \c prev() se l'half edge attuale è uscente dal vertice su cui cicla l'iteratore,
 * mentre esegue un'operazione di \c twin() se l'half edge attuale è entrante sul vertice. Se l'half edge
 * ottenuto è uguale all'half edge end, allora l'iteratore diventa uguale all'iteratore \c end().
 *
 * @return L'iteratore appena decrementato
 */
inline Dcel::Vertex::ConstIncidentHalfEdgeIterator Dcel::Vertex::ConstIncidentHalfEdgeIterator::operator -- () {
    if (pos->getFromVertex() == v) pos = pos->getPrev();
    else pos = pos->getTwin();
    if (pos == end) pos = nullptr;
    return *this;
}

/**
 * \~Italian
 * @brief Operatore di decremento postfisso del ConstIncidentHalfEdgeIterator.
 *
 * Esegue un'operazione di \c prev() se l'half edge attuale è uscente dal vertice su cui cicla l'iteratore,
 * mentre esegue un'operazione di \c twin() se l'half edge attuale è entrante sul vertice. Se l'half edge
 * ottenuto è uguale all'half edge end, allora l'iteratore diventa uguale all'iteratore \c end().
 *
 * @return L'iteratore prima di essere incrementato
 */
inline Dcel::Vertex::ConstIncidentHalfEdgeIterator Dcel::Vertex::ConstIncidentHalfEdgeIterator::operator -- (int) {
    ConstIncidentHalfEdgeIterator old_value = *this;
    if (pos->getFromVertex() == v) pos = pos->getPrev();
    else pos = pos->getTwin();
    if (pos == end) pos = nullptr;
    return old_value;
}

//Protected Constructor

/**
 * \~Italian
 * @brief Costruttore di un ConstIncidentHalfEdgeIterator.
 *
 * Setta l'half edge di partenza, l'half edge di arrivo e il vertice su cui iterare.
 * L'iteratore viene inizializzato all'half edge start.
 * Per questioni di sicurezza e di robustezza del codice questo costruttore non è direttamente richiamabile
 * dal programmatore. Tuttavia, questo costruttore viene richiamato dalla friend class Dcel::Vertex nei vari metodi
 * begin, che inizializzano correttamente l'iteratore e che possono essere utilizzati dal programmatore per
 * l'inizializzazione dell'iteratore.
 *
 * @param[in] start: half edge (non per forza uscente dal vertice) di start
 * @param[in] end: half edge (non per forza uscente dal vertice) di end
 * @param[in] v: vertice su cui vengono iterati gli half edge incidenti
 */
inline Dcel::Vertex::ConstIncidentHalfEdgeIterator::ConstIncidentHalfEdgeIterator(const HalfEdge* start, const HalfEdge* end, const Vertex* v)  : ConstGenericIterator(start, end, v) {
}

/**************************************
 * DCEL::Vertex::IncidentFaceIterator *
 **************************************/

//Constructor

/**
 * \~Italian
 * @brief Costruttore vuoto.
 * Un iteratore inizializzato con questo costruttore non è utilizzabile.
 */
inline Dcel::Vertex::IncidentFaceIterator::IncidentFaceIterator() : GenericIterator(){
}

//Public Operators

/**
 * \~Italian
 * @brief Operatore di dereferenziazione dell'IncidentFaceIterator
 * @return La faccia incidente sull'half edge puntato dall'iteratore
 */
inline Dcel::Face* Dcel::Vertex::IncidentFaceIterator::operator * () const {
    return pos->getFace();
}

//Protected Constructor

/**
 * \~Italian
 * @brief Costruttore di un IncidentFaceIterator.
 *
 * Setta l'half edge di partenza, l'half edge di arrivo e il vertice su cui iterare.
 * L'iteratore viene inizializzato all'half edge start.
 * Per questioni di sicurezza e di robustezza del codice questo costruttore non è direttamente richiamabile
 * dal programmatore. Tuttavia, questo costruttore viene richiamato dalla friend class Dcel::Vertex nei vari metodi
 * begin, che inizializzano correttamente l'iteratore e che possono essere utilizzati dal programmatore per
 * l'inizializzazione dell'iteratore.
 *
 * @param[in] start: half edge (non per forza uscente dal vertice) di start
 * @param[in] end: half edge (non per forza uscente dal vertice) di end
 * @param[in] v: vertice su cui vengono iterate le facce incidenti
 */
inline Dcel::Vertex::IncidentFaceIterator::IncidentFaceIterator(HalfEdge* start, HalfEdge* end, Vertex* v) : GenericIterator(start, end, v) {
}

/*******************************************
 * DCEL::Vertex::ConstIncidentFaceIterator *
 *******************************************/

//Constructors

/**
 * \~Italian
 * @brief Costruttore vuoto.
 * Un iteratore inizializzato con questo costruttore non è utilizzabile.
 */
inline Dcel::Vertex::ConstIncidentFaceIterator::ConstIncidentFaceIterator() : ConstGenericIterator() {
}

/**
 * \~Italian
 * @brief Costruttore di copia da un IncidentFaceIterator.
 *
 * Inizializza un ConstIncidentFaceIterator pari all'IncidentFaceIterator passato in input.
 * @param[in] it: iteratore di cui ne verrà fatta una copia
 */
inline Dcel::Vertex::ConstIncidentFaceIterator::ConstIncidentFaceIterator(const Dcel::Vertex::IncidentFaceIterator& it) : ConstGenericIterator(it) {
}

//Public Operators

/**
 * \~Italian
 * @brief Operatore di dereferenziazione del ConstIncidentFaceIterator
 * @return La faccia incidente sull'half edge puntato dall'iteratore
 */
inline const Dcel::Face* Dcel::Vertex::ConstIncidentFaceIterator::operator * () const {
    return pos->getFace();
}

//Protected Constructor

/**
 * \~Italian
 * @brief Costruttore di un ConstIncidentFaceIterator.
 *
 * Setta l'half edge di partenza, l'half edge di arrivo e il vertice su cui iterare.
 * L'iteratore viene inizializzato all'half edge start.
 * Per questioni di sicurezza e di robustezza del codice questo costruttore non è direttamente richiamabile
 * dal programmatore. Tuttavia, questo costruttore viene richiamato dalla friend class Dcel::Vertex nei vari metodi
 * begin, che inizializzano correttamente l'iteratore e che possono essere utilizzati dal programmatore per
 * l'inizializzazione dell'iteratore.
 *
 * @param[in] start: half edge (non per forza uscente dal vertice) di start
 * @param[in] end: half edge (non per forza uscente dal vertice) di end
 * @param[in] v: vertice su cui vengono iterate le facce incidenti
 */
inline Dcel::Vertex::ConstIncidentFaceIterator::ConstIncidentFaceIterator(const HalfEdge* start, const HalfEdge* end, const Vertex* v) : ConstGenericIterator(start, end, v) {
}

inline const Dcel::Vertex::ConstAdjacentVertexRangeBasedIterator Dcel::Vertex::adjacentVertexIterator() const {
    return ConstAdjacentVertexRangeBasedIterator(this);
}

inline Dcel::Vertex::AdjacentVertexRangeBasedIterator Dcel::Vertex::adjacentVertexIterator() {
    return AdjacentVertexRangeBasedIterator(this);
}

inline Dcel::Vertex::ConstAdjacentVertexIterator Dcel::Vertex::ConstAdjacentVertexRangeBasedIterator::begin() const {
    return v->adjacentVertexBegin();
}

inline Dcel::Vertex::ConstAdjacentVertexIterator Dcel::Vertex::ConstAdjacentVertexRangeBasedIterator::end() const {
    return v->adjacentVertexEnd();
}

inline Dcel::Vertex::AdjacentVertexIterator Dcel::Vertex::AdjacentVertexRangeBasedIterator::begin() {
    return v->adjacentVertexBegin();
}

inline Dcel::Vertex::AdjacentVertexIterator Dcel::Vertex::AdjacentVertexRangeBasedIterator::end() {
    return v->adjacentVertexEnd();
}

inline Dcel::Vertex::ConstOutgoingHalfEdgeIterator Dcel::Vertex::ConstOutgoingHalfEdgeRangeBasedIterator::begin() const {
    return v->outgoingHalfEdgeBegin();
}

inline Dcel::Vertex::ConstOutgoingHalfEdgeIterator Dcel::Vertex::ConstOutgoingHalfEdgeRangeBasedIterator::end() const {
    return v->outgoingHalfEdgeEnd();
}

inline Dcel::Vertex::OutgoingHalfEdgeIterator Dcel::Vertex::OutgoingHalfEdgeRangeBasedIterator::begin() {
    return v->outgoingHalfEdgeBegin();
}

inline Dcel::Vertex::OutgoingHalfEdgeIterator Dcel::Vertex::OutgoingHalfEdgeRangeBasedIterator::end() {
    return v->outgoingHalfEdgeEnd();
}

inline Dcel::Vertex::ConstIncomingHalfEdgeIterator Dcel::Vertex::ConstIncomingHalfEdgeRangeBasedIterator::begin() const {
    return v->incomingHalfEdgeBegin();
}

inline Dcel::Vertex::ConstIncomingHalfEdgeIterator Dcel::Vertex::ConstIncomingHalfEdgeRangeBasedIterator::end() const {
    return v->incomingHalfEdgeEnd();
}

inline Dcel::Vertex::IncomingHalfEdgeIterator Dcel::Vertex::IncomingHalfEdgeRangeBasedIterator::begin() {
    return v->incomingHalfEdgeBegin();
}

inline Dcel::Vertex::IncomingHalfEdgeIterator Dcel::Vertex::IncomingHalfEdgeRangeBasedIterator::end() {
    return v->incomingHalfEdgeEnd();
}

inline Dcel::Vertex::ConstIncidentHalfEdgeIterator Dcel::Vertex::ConstIncidentHalfEdgeRangeBasedIterator::begin() const {
    return v->incidentHalfEdgeBegin();
}

inline Dcel::Vertex::ConstIncidentHalfEdgeIterator Dcel::Vertex::ConstIncidentHalfEdgeRangeBasedIterator::end() const {
    return v->incidentHalfEdgeEnd();
}

inline Dcel::Vertex::IncidentHalfEdgeIterator Dcel::Vertex::IncidentHalfEdgeRangeBasedIterator::begin() {
    return v->incidentHalfEdgeBegin();
}

inline Dcel::Vertex::IncidentHalfEdgeIterator Dcel::Vertex::IncidentHalfEdgeRangeBasedIterator::end() {
    return v->incidentHalfEdgeEnd();
}

inline Dcel::Vertex::ConstIncidentFaceIterator Dcel::Vertex::ConstIncidentFaceRangeBasedIterator::begin() const {
    return v->incidentFaceBegin();
}

inline Dcel::Vertex::ConstIncidentFaceIterator Dcel::Vertex::ConstIncidentFaceRangeBasedIterator::end() const {
    return v->incidentFaceEnd();
}

inline Dcel::Vertex::IncidentFaceIterator Dcel::Vertex::IncidentFaceRangeBasedIterator::begin() {
    return v->incidentFaceBegin();
}

inline Dcel::Vertex::IncidentFaceIterator Dcel::Vertex::IncidentFaceRangeBasedIterator::end() {
    return v->incidentFaceEnd();
}

/***
 * Dcel::Vertex begin()/end()
 **/

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Dcel::Vertex::ConstAdjacentVertexIterator.
 *
 * Permette di ciclare sui vertici adiacenti al vertice, partendo dal toVertex dell'incidentHalfEdge.
 *
 * @return Un iteratore che punta al toVertex dell'incidentHalfEdge
 */
inline Dcel::Vertex::ConstAdjacentVertexIterator Dcel::Vertex::adjacentVertexBegin() const {
    assert(checkIncidentHalfEdge() && "Incident half edge is nullptr.");
    return ConstAdjacentVertexIterator(incidentHalfEdge, incidentHalfEdge, this);
}

/**
 * \~Italian
 * @brief Funzione di finalizzazione di Dcel::Vertex::ConstAdjacentVertexIterator
 * @warning L'iteratore restituito non è un iteratore valido, e su di esso le operazioni di
 *          incremento e decremento sono inutili. Questa funzione è da utilizzarsi solamente per
 *          il \b confronto \b con \b un \b altro \b iteratore \b valido
 * @return Un iteratore di finalizzazione
 */
inline Dcel::Vertex::ConstAdjacentVertexIterator Dcel::Vertex::adjacentVertexEnd() const {
    return ConstAdjacentVertexIterator(nullptr, nullptr, this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Dcel::Vertex::ConstAdjacentVertexIterator.
 *
 * Permette di ciclare sui vertici adiacenti al vertice, partendo dal toVertex dell'half edge start.
 *
 * @param[in] start: half edge di partenza
 * @warning Se start non risulta avere il vertice this come fromoVertex, viene lanciata un'asserzione e il programma termina
 * @return Un iteratore che punta al toVertex dell'half edge start
 */
inline Dcel::Vertex::ConstAdjacentVertexIterator Dcel::Vertex::adjacentVertexBegin(const HalfEdge* start) const {
    assert(start->getFromVertex() == this && "Start half edge is not incident to iterated face.");
    return ConstAdjacentVertexIterator(start, start, this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Dcel::Vertex::ConstAdjacentVertexIterator.
 *
 * Permette di ciclare sui vertici adiacenti al vertice, partendo dal toVertex dell'half edge start e fino al toVertex dell'half edge end.
 *
 * @param[in] start: half edge di partenza
 * @param[in] end: half edge di arrivo, il cui toVertex \b non \b è \b compreso
 * @warning Se start e end non risultano avere il vertice this come fromoVertex, viene lanciata un'asserzione e il programma termina
 * @return Un iteratore che punta al toVertex dell'half edge start
 */
inline Dcel::Vertex::ConstAdjacentVertexIterator Dcel::Vertex::adjacentVertexBegin(const HalfEdge* start, const HalfEdge* end) const {
    assert(start->getFromVertex() == this && "Start half edge is not incident to iterated face.");
    assert(end->getFromVertex() == this && "End half edge is not incident to iterated face.");
    return ConstAdjacentVertexIterator(start, end, this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Dcel::Vertex::ConstAdjacentVertexIterator.
 *
 * Permette di ciclare sui vertici adiacenti al vertice, partendo dal vertice start.\n
 * È meno efficiente rispetto a Dcel::Vertex::constAdjacentVertexBegin(const Dcel::HalfEdge* start).
 *
 * @param[in] start: vertice di partenza
 * @warning Se start non risulta essere adiacente al vertice this (ossia non esiste un half edge condiviso tra this e start),
 * viene lanciata un'asserzione e il programma termina
 * @warning Utilizza Dcel::Vertex::ConstIncomingHalfEdgeIterator
 * @return Un iteratore che punta al vertice start
 * @par Complessità:
 *      \e O(Cardinality(start))
 */
inline Dcel::Vertex::ConstAdjacentVertexIterator Dcel::Vertex::adjacentVertexBegin(const Dcel::Vertex* start) const {
    Vertex::ConstIncomingHalfEdgeIterator heit;
    for (heit = start->incomingHalfEdgeBegin(); heit != start->incomingHalfEdgeEnd(); ++heit){
        if ((*heit)->getFromVertex() == this) return ConstAdjacentVertexIterator(*heit, *heit, this);
    }
    assert (false && "Start vertex is not adjacent to iterated vertex.");
    return ConstAdjacentVertexIterator();
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Dcel::Vertex::ConstAdjacentVertexIterator.
 *
 * Permette di ciclare sui vertici adiacenti al vertice, partendo dal vertice start e fino al vertice end.\n
 * È meno efficiente rispetto a Dcel::Vertex::constAdjacentVertexBegin(const Dcel::HalfEdge* start, const Dcel::HalfEdge* end).
 *
 * @param[in] start: vertice di partenza
 * @param[in] end: vertice di arrivo, \b non \b compreso
 * @warning Se start e end non risultano essere adiacenti al vertice this (ossia non esiste un half edge condiviso tra this e start e tra this e end),
 * viene lanciata un'asserzione e il programma termina
 * @warning Utilizza Dcel::Vertex::ConstIncomingHalfEdgeIterator
 * @return Un iteratore che punta al vertice start
 * @par Complessità:
 *      \e O(Cardinality(start)) + \e O(Cardinality(end))
 */
inline Dcel::Vertex::ConstAdjacentVertexIterator Dcel::Vertex::adjacentVertexBegin(const Dcel::Vertex* start, const Dcel::Vertex* end) const {
    Vertex::ConstIncomingHalfEdgeIterator heit = start->incomingHalfEdgeBegin();
    while (heit != start->incomingHalfEdgeEnd() && ((*heit)->getFromVertex() != this)) ++heit;
    assert ((*heit)->getFromVertex() == this && "Start vertex is not adjacent to iterated vertex.");
    const HalfEdge* s = *heit;
    for (heit = end->incomingHalfEdgeBegin(); heit != end->incomingHalfEdgeEnd(); ++heit){
        if ((*heit)->getFromVertex() == this) return ConstAdjacentVertexIterator(s, *heit, this);
    }
    assert (false && "End vertex is not adjacent to iterated vertex.");
    return ConstAdjacentVertexIterator();
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Dcel::Vertex::ConstOutgoingHalfEdgeIterator.
 *
 * Permette di ciclare sugli half edge incidenti uscenti dal vertice, partendo dall'incidentHalfEdge.
 *
 * @return Un iteratore che punta all'incidentHalfEdge del vertice
 */
inline Dcel::Vertex::ConstOutgoingHalfEdgeIterator Dcel::Vertex::outgoingHalfEdgeBegin() const {
    assert(checkIncidentHalfEdge() && "Incident half edge is nullptr.");
    return ConstOutgoingHalfEdgeIterator(incidentHalfEdge, incidentHalfEdge, this);
}

/**
 * \~Italian
 * @brief Funzione di finalizzazione di Dcel::Vertex::ConstOutgoingHalfEdgeIterator
 * @warning L'iteratore restituito non è un iteratore valido, e su di esso le operazioni di
 *          incremento e decremento sono inutili. Questa funzione è da utilizzarsi solamente per
 *          il \b confronto \b con \b un \b altro \b iteratore \b valido
 * @return Un iteratore di finalizzazione
 */
inline Dcel::Vertex::ConstOutgoingHalfEdgeIterator Dcel::Vertex::outgoingHalfEdgeEnd() const {
    return ConstOutgoingHalfEdgeIterator(nullptr, nullptr, this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Dcel::Vertex::ConstOutgoingHalfEdgeIterator.
 *
 * Permette di ciclare sugli half edge incidenti uscenti dal vertice, partendo dall'half edge start.
 *
 * @param[in] start: half edge di partenza
 * @warning Se start non risulta avere il vertice this come fromVertex, viene lanciata un'asserzione e il programma termina
 * @return Un iteratore che punta all'half edge start
 */
inline Dcel::Vertex::ConstOutgoingHalfEdgeIterator Dcel::Vertex::outgoingHalfEdgeBegin(const Dcel::HalfEdge* start) const {
    assert(start->getFromVertex() == this && "Start half edge is not incident to iterated face.");
    return ConstOutgoingHalfEdgeIterator(start, start, this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Dcel::Vertex::ConstOutgoingHalfEdgeIterator.
 *
 * Permette di ciclare sugli half edge incidenti uscenti dal vertice, partendo dall'half edge start e fino all'half edge end.
 *
 * @param[in] start: half edge di partenza
 * @param[in] end: half edge di arrivo, che \b non \b è \b compreso
 * @warning Se start e end non risultano avere il vertice this come fromVertex, viene lanciata un'asserzione e il programma termina
 * @return Un iteratore che punta all'half edge start
 */
inline Dcel::Vertex::ConstOutgoingHalfEdgeIterator Dcel::Vertex::outgoingHalfEdgeBegin(const HalfEdge* start, const HalfEdge* end) const {
    assert(start->getFromVertex() == this && "Start half edge is not incident to iterated face.");
    assert(end->getFromVertex() == this && "End half edge is not incident to iterated face.");
    return ConstOutgoingHalfEdgeIterator(start, end, this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Dcel::Vertex::ConstIncomingHalfEdgeIterator.
 *
 * Permette di ciclare sugli half edge incidenti entranti nel vertice, partendo dal twin dell'incidentHalfEdge.
 *
 * @return Un iteratore che punta al twin dell'incidentHalfEdge del vertice
 */
inline Dcel::Vertex::ConstIncomingHalfEdgeIterator Dcel::Vertex::incomingHalfEdgeBegin() const {
    assert(checkIncidentHalfEdge() && "Incident half edge is nullptr.");
    return ConstIncomingHalfEdgeIterator(incidentHalfEdge, incidentHalfEdge, this);
}

/**
 * \~Italian
 * @brief Funzione di finalizzazione di Dcel::Vertex::ConstIncomingHalfEdgeIterator
 * @warning L'iteratore restituito non è un iteratore valido, e su di esso le operazioni di
 *          incremento e decremento sono inutili. Questa funzione è da utilizzarsi solamente per
 *          il \b confronto \b con \b un \b altro \b iteratore \b valido
 * @return Un iteratore di finalizzazione
 */
inline Dcel::Vertex::ConstIncomingHalfEdgeIterator Dcel::Vertex::incomingHalfEdgeEnd() const {
    return ConstIncomingHalfEdgeIterator(nullptr, nullptr, this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Dcel::Vertex::ConstIncomingHalfEdgeIterator.
 *
 * Permette di ciclare sugli half edge incidenti entranti nel vertice, partendo dall'half edge start.
 *
 * @param[in] start: half edge di partenza
 * @warning Se start non risulta avere il vertice this come toVertex, viene lanciata un'asserzione e il programma termina
 * @return Un iteratore che punta all'half edge start
 */
inline Dcel::Vertex::ConstIncomingHalfEdgeIterator Dcel::Vertex::incomingHalfEdgeBegin(const HalfEdge* start) const {
    assert(start->getToVertex() == this && "Start half edge is not incident to iterated face.");
    return ConstIncomingHalfEdgeIterator(start->getTwin(), start->getTwin(), this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Dcel::Vertex::ConstIncomingHalfEdgeIterator.
 *
 * Permette di ciclare sugli half edge incidenti entranti nel vertice, partendo dall'half edge start e fino all'half edge end.
 *
 * @param[in] start: half edge di partenza
 * @param[in] end: half edge di arrivo, che \b non \b è \b compreso
 * @warning Se start e end non risultano avere il vertice this come toVertex, viene lanciata un'asserzione e il programma termina
 * @return Un iteratore che punta all'half edge start
 */
inline Dcel::Vertex::ConstIncomingHalfEdgeIterator Dcel::Vertex::incomingHalfEdgeBegin(const HalfEdge* start, const HalfEdge* end) const {
    assert(start->getToVertex() == this && "Start half edge is not incident to iterated face.");
    assert(end->getToVertex() == this && "End half edge is not incident to iterated face.");
    return ConstIncomingHalfEdgeIterator(start->getTwin(), end->getTwin(), this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Dcel::Vertex::ConstIncidentHalfEdgeIterator.
 *
 * Permette di ciclare sugli half edge incidenti, sia uscenti che entranti nel vertice, partendo dall'incidentHalfEdge.
 *
 * @return Un iteratore che punta all'incidentHalfEdge del vertice
 */
inline Dcel::Vertex::ConstIncidentHalfEdgeIterator Dcel::Vertex::incidentHalfEdgeBegin() const {
    assert(checkIncidentHalfEdge() && "Incident half edge is nullptr.");
    return ConstIncidentHalfEdgeIterator(incidentHalfEdge, incidentHalfEdge, this);
}

/**
 * \~Italian
 * @brief Funzione di finalizzazione di Dcel::Vertex::ConstIncidentHalfEdgeIterator
 * @warning L'iteratore restituito non è un iteratore valido, e su di esso le operazioni di
 *          incremento e decremento sono inutili. Questa funzione è da utilizzarsi solamente per
 *          il \b confronto \b con \b un \b altro \b iteratore \b valido
 * @return Un iteratore di finalizzazione
 */
inline Dcel::Vertex::ConstIncidentHalfEdgeIterator Dcel::Vertex::incidentHalfEdgeEnd() const {
    return ConstIncidentHalfEdgeIterator(nullptr, nullptr, this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Dcel::Vertex::ConstIncidentHalfEdgeIterator.
 *
 * Permette di ciclare sugli half edge incidenti uscenti e entranti nel vertice, partendo dall'half edge start.
 *
 * @param[in] start: half edge di partenza
 * @warning Se start non risulta avere il vertice this come toVertex o fromVertex, viene lanciata un'asserzione e il programma termina
 * @return Un iteratore che punta all'half edge start
 */
inline Dcel::Vertex::ConstIncidentHalfEdgeIterator Dcel::Vertex::incidentHalfEdgeBegin(const HalfEdge *start) const {
    assert((start->getFromVertex() == this || start->getToVertex() == this) && "Start half edge is not incident to iterated face.");
    return ConstIncidentHalfEdgeIterator(start, start, this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Dcel::Vertex::ConstIncidentHalfEdgeIterator.
 *
 * Permette di ciclare sugli half edge incidenti uscenti e entranti nel vertice, partendo dall'half edge start e fino all'half edge end.
 *
 * @param[in] start: half edge di partenza
 * @param[in] end: half edge di arrivo, che \b non \b è \b compreso
 * @warning Se start e end non risultano avere il vertice this come toVertex o fromVertex, viene lanciata un'asserzione e il programma termina
 * @return Un iteratore che punta all'half edge start
 */
inline Dcel::Vertex::ConstIncidentHalfEdgeIterator Dcel::Vertex::incidentHalfEdgeBegin(const HalfEdge *start, const HalfEdge *end) const {
    assert((start->getFromVertex() == this || start->getToVertex() == this) && "Start half edge is not incident to iterated face.");
    assert((end->getFromVertex() == this || end->getToVertex() == this) && "End half edge is not incident to iterated face.");
    return ConstIncidentHalfEdgeIterator(start, end, this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Dcel::Vertex::ConstIncidentFaceIterator.
 *
 * Permette di ciclare sulle facce incidenti sul vertice, partendo dalla faccia incidente sull'incidentHalfEdge.
 *
 * @return Un iteratore che punta alla faccia incidente sull'incidentHalfEdge del vertice
 */
inline Dcel::Vertex::ConstIncidentFaceIterator Dcel::Vertex::incidentFaceBegin() const {
    assert(checkIncidentHalfEdge() && "Incident half edge is nullptr.");
    return ConstIncidentFaceIterator(incidentHalfEdge, incidentHalfEdge, this);
}

/**
 * \~Italian
 * @brief Funzione di finalizzazione di Dcel::Vertex::ConstIncidentFaceIterator
 * @warning L'iteratore restituito non è un iteratore valido, e su di esso le operazioni di
 *          incremento e decremento sono inutili. Questa funzione è da utilizzarsi solamente per
 *          il \b confronto \b con \b un \b altro \b iteratore \b valido
 * @return Un iteratore di finalizzazione
 */
inline Dcel::Vertex::ConstIncidentFaceIterator Dcel::Vertex::incidentFaceEnd() const {
    return ConstIncidentFaceIterator(nullptr, nullptr, this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Dcel::Vertex::ConstIncidentFaceIterator.
 *
 * Permette di ciclare sulle facce incidenti sul vertice, partendo dalla faccia incidente sull'half edge start.
 *
 * @param[in] start: half edge di partenza
 * @warning Se start non risulta avere il vertice this come fromVertex, viene lanciata un'asserzione e il programma termina
 * @return Un iteratore che punta alla faccia incidente sull'half edge start
 */
inline Dcel::Vertex::ConstIncidentFaceIterator Dcel::Vertex::incidentFaceBegin(const HalfEdge* start) const {
    assert(start->getFromVertex() == this && "Start half edge is not incident to iterated face.");
    return ConstIncidentFaceIterator(start, start, this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Dcel::Vertex::ConstIncidentFaceIterator.
 *
 * Permette di ciclare sulle facce incidenti sul vertice, partendo dalla faccia incidente sull'half edge start e fino alla faccia incidente sull'half edge end.
 *
 * @param[in] start: half edge di partenza
 * @param[in] end: half edge di arrivo, che \b non \b è \b compreso
 * @warning Se start e end non risultano avere il vertice this come fromVertex, viene lanciata un'asserzione e il programma termina
 * @return Un iteratore che punta alla faccia incidente sull'half edge start
 */
inline Dcel::Vertex::ConstIncidentFaceIterator Dcel::Vertex::incidentFaceBegin(const HalfEdge* start, const HalfEdge* end) const {
    assert(start->getFromVertex() == this && "Start half edge is not incident to iterated face.");
    assert(end->getFromVertex() == this && "End half edge is not incident to iterated face.");
    return ConstIncidentFaceIterator(start, end, this);
}

inline const Dcel::Vertex::ConstOutgoingHalfEdgeRangeBasedIterator Dcel::Vertex::outgoingHalfEdgeIterator() const {
    return ConstOutgoingHalfEdgeRangeBasedIterator(this);
}

inline const Dcel::Vertex::ConstIncomingHalfEdgeRangeBasedIterator Dcel::Vertex::incomingHalfEdgeIterator() const {
    return ConstIncomingHalfEdgeRangeBasedIterator(this);
}

inline const Dcel::Vertex::ConstIncidentHalfEdgeRangeBasedIterator Dcel::Vertex::incidentHalfEdgeIterator() const {
    return ConstIncidentHalfEdgeRangeBasedIterator(this);
}

inline const Dcel::Vertex::ConstIncidentFaceRangeBasedIterator Dcel::Vertex::incidentFaceIterator() const {
    return ConstIncidentFaceRangeBasedIterator(this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Dcel::Vertex::AdjacentVertexIterator.
 *
 * Permette di ciclare sui vertici adiacenti al vertice, partendo dal toVertex dell'incidentHalfEdge.
 *
 * @return Un iteratore che punta al toVertex dell'incidentHalfEdge
 */
inline Dcel::Vertex::AdjacentVertexIterator Dcel::Vertex::adjacentVertexBegin() {
    assert(checkIncidentHalfEdge() && "Incident half edge is nullptr.");
    return AdjacentVertexIterator(incidentHalfEdge, incidentHalfEdge, this);
}

/**
 * \~Italian
 * @brief Funzione di finalizzazione di Dcel::Vertex::AdjacentVertexIterator
 * @warning L'iteratore restituito non è un iteratore valido, e su di esso le operazioni di
 *          incremento e decremento sono inutili. Questa funzione è da utilizzarsi solamente per
 *          il \b confronto \b con \b un \b altro \b iteratore \b valido
 * @return Un iteratore di finalizzazione
 */
inline Dcel::Vertex::AdjacentVertexIterator Dcel::Vertex::adjacentVertexEnd() {
    return AdjacentVertexIterator(nullptr, nullptr, this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Dcel::Vertex::AdjacentVertexIterator.
 *
 * Permette di ciclare sui vertici adiacenti al vertice, partendo dal toVertex dell'half edge start.
 *
 * @param[in] start: half edge di partenza
 * @warning Se start non risulta avere il vertice this come fromoVertex, viene lanciata un'asserzione e il programma termina
 * @return Un iteratore che punta al toVertex dell'half edge start
 */
inline Dcel::Vertex::AdjacentVertexIterator Dcel::Vertex::adjacentVertexBegin(HalfEdge* start) {
    assert(start->getFromVertex() == this && "Start half edge is not incident to iterated face.");
    return AdjacentVertexIterator(start, start, this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Dcel::Vertex::AdjacentVertexIterator.
 *
 * Permette di ciclare sui vertici adiacenti al vertice, partendo dal toVertex dell'half edge start e fino al toVertex dell'half edge end.
 *
 * @param[in] start: half edge di partenza
 * @param[in] end: half edge di arrivo, il cui toVertex \b non \b è \b compreso
 * @warning Se start e end non risultano avere il vertice this come fromoVertex, viene lanciata un'asserzione e il programma termina
 * @return Un iteratore che punta al toVertex dell'half edge start
 */
inline Dcel::Vertex::AdjacentVertexIterator Dcel::Vertex::adjacentVertexBegin(HalfEdge* start, HalfEdge* end) {
    assert(start->getFromVertex() == this && "Start half edge is not incident to iterated face.");
    assert(end->getFromVertex() == this && "End half edge is not incident to iterated face.");
    return AdjacentVertexIterator(start, end, this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Dcel::Vertex::AdjacentVertexIterator.
 *
 * Permette di ciclare sui vertici adiacenti al vertice, partendo dal vertice start.\n
 * È meno efficiente rispetto a Dcel::Vertex::constAdjacentVertexBegin(const Dcel::HalfEdge* start).
 *
 * @param[in] start: vertice di partenza
 * @warning Se start non risulta essere adiacente al vertice this (ossia non esiste un half edge condiviso tra this e start),
 * viene lanciata un'asserzione e il programma termina
 * @warning Utilizza Dcel::Vertex::ConstIncomingHalfEdgeIterator
 * @return Un iteratore che punta al vertice start
 * @par Complessità:
 *      \e O(Cardinality(start))
 */
inline Dcel::Vertex::AdjacentVertexIterator Dcel::Vertex::adjacentVertexBegin(Vertex* start) {
    Vertex::IncomingHalfEdgeIterator heit;
    for (heit= start->incomingHalfEdgeBegin(); heit!= start->incomingHalfEdgeEnd(); ++heit){
        if ((*heit)->getFromVertex() == this) return AdjacentVertexIterator(*heit, *heit, this);
    }
    assert (false && "Start vertex is not adjacent to iterated vertex.");
    return AdjacentVertexIterator();
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Dcel::Vertex::AdjacentVertexIterator.
 *
 * Permette di ciclare sui vertici adiacenti al vertice, partendo dal vertice start e fino al vertice end.\n
 * È meno efficiente rispetto a Dcel::Vertex::constAdjacentVertexBegin(const Dcel::HalfEdge* start, const Dcel::HalfEdge* end).
 *
 * @param[in] start: vertice di partenza
 * @param[in] end: vertice di arrivo, \b non \b compreso
 * @warning Se start e end non risultano essere adiacenti al vertice this (ossia non esiste un half edge condiviso tra this e start e tra this e end),
 * viene lanciata un'asserzione e il programma termina
 * @warning Utilizza Dcel::Vertex::ConstIncomingHalfEdgeIterator
 * @return Un iteratore che punta al vertice start
 * @par Complessità:
 *      \e O(Cardinality(start)) + \e O(Cardinality(end))
 */
inline Dcel::Vertex::AdjacentVertexIterator Dcel::Vertex::adjacentVertexBegin(Vertex* start, Vertex* end) {
    Vertex::IncomingHalfEdgeIterator heit = start->incomingHalfEdgeBegin();
    while (heit!= start->incomingHalfEdgeEnd() && ((*heit)->getFromVertex() != this)) ++heit;
    assert ((*heit)->getFromVertex() == this && "Start vertex is not adjacent to iterated vertex.");
    HalfEdge* s = *heit;
    for (heit= end->incomingHalfEdgeBegin(); heit!= end->incomingHalfEdgeEnd(); ++heit){
        if ((*heit)->getFromVertex() == this) return AdjacentVertexIterator(s, *heit, this);
    }
    assert (false && "End vertex is not adjacent to iterated vertex.");
    return AdjacentVertexIterator();
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Dcel::Vertex::OutgoingHalfEdgeIterator.
 *
 * Permette di ciclare sugli half edge incidenti uscenti dal vertice, partendo dall'incidentHalfEdge.
 *
 * @return Un iteratore che punta all'incidentHalfEdge del vertice
 */
inline Dcel::Vertex::OutgoingHalfEdgeIterator Dcel::Vertex::outgoingHalfEdgeBegin() {
    assert(checkIncidentHalfEdge() && "Incident half edge is nullptr.");
    return OutgoingHalfEdgeIterator(incidentHalfEdge, incidentHalfEdge, this);
}

/**
 * \~Italian
 * @brief Funzione di finalizzazione di Dcel::Vertex::OutgoingHalfEdgeIterator
 * @warning L'iteratore restituito non è un iteratore valido, e su di esso le operazioni di
 *          incremento e decremento sono inutili. Questa funzione è da utilizzarsi solamente per
 *          il \b confronto \b con \b un \b altro \b iteratore \b valido
 * @return Un iteratore di finalizzazione
 */
inline Dcel::Vertex::OutgoingHalfEdgeIterator Dcel::Vertex::outgoingHalfEdgeEnd() {
    return OutgoingHalfEdgeIterator(nullptr, nullptr, this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Dcel::Vertex::OutgoingHalfEdgeIterator.
 *
 * Permette di ciclare sugli half edge incidenti uscenti dal vertice, partendo dall'half edge start.
 *
 * @param[in] start: half edge di partenza
 * @warning Se start non risulta avere il vertice this come fromVertex, viene lanciata un'asserzione e il programma termina
 * @return Un iteratore che punta all'half edge start
 */
inline Dcel::Vertex::OutgoingHalfEdgeIterator Dcel::Vertex::outgoingHalfEdgeBegin(HalfEdge* start) {
    assert(start->getFromVertex() == this && "Start half edge is not incident to iterated face.");
    return OutgoingHalfEdgeIterator(start, start, this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Dcel::Vertex::OutgoingHalfEdgeIterator.
 *
 * Permette di ciclare sugli half edge incidenti uscenti dal vertice, partendo dall'half edge start e fino all'half edge end.
 *
 * @param[in] start: half edge di partenza
 * @param[in] end: half edge di arrivo, che \b non \b è \b compreso
 * @warning Se start e end non risultano avere il vertice this come fromVertex, viene lanciata un'asserzione e il programma termina
 * @return Un iteratore che punta all'half edge start
 */
inline Dcel::Vertex::OutgoingHalfEdgeIterator Dcel::Vertex::outgoingHalfEdgeBegin(HalfEdge* start, HalfEdge* end) {
    assert(start->getFromVertex() == this && "Start half edge is not incident to iterated face.");
    assert(end->getFromVertex() == this && "End half edge is not incident to iterated face.");
    return OutgoingHalfEdgeIterator(start, end, this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Dcel::Vertex::IncomingHalfEdgeIterator.
 *
 * Permette di ciclare sugli half edge incidenti entranti nel vertice, partendo dal twin dell'incidentHalfEdge.
 *
 * @return Un iteratore che punta al twin dell'incidentHalfEdge del vertice
 */
inline Dcel::Vertex::IncomingHalfEdgeIterator Dcel::Vertex::incomingHalfEdgeBegin() {
    assert(checkIncidentHalfEdge() && "Incident half edge is nullptr.");
    return IncomingHalfEdgeIterator(incidentHalfEdge, incidentHalfEdge, this);
}

/**
 * \~Italian
 * @brief Funzione di finalizzazione di Dcel::Vertex::IncomingHalfEdgeIterator
 * @warning L'iteratore restituito non è un iteratore valido, e su di esso le operazioni di
 *          incremento e decremento sono inutili. Questa funzione è da utilizzarsi solamente per
 *          il \b confronto \b con \b un \b altro \b iteratore \b valido
 * @return Un iteratore di finalizzazione
 */
inline Dcel::Vertex::IncomingHalfEdgeIterator Dcel::Vertex::incomingHalfEdgeEnd() {
    return IncomingHalfEdgeIterator(nullptr, nullptr, this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Dcel::Vertex::IncomingHalfEdgeIterator.
 *
 * Permette di ciclare sugli half edge incidenti entranti nel vertice, partendo dall'half edge start.
 *
 * @param[in] start: half edge di partenza
 * @warning Se start non risulta avere il vertice this come toVertex, viene lanciata un'asserzione e il programma termina
 * @return Un iteratore che punta all'half edge start
 */
inline Dcel::Vertex::IncomingHalfEdgeIterator Dcel::Vertex::incomingHalfEdgeBegin(HalfEdge* start) {
    assert(start->getToVertex() == this && "Start half edge is not incident to iterated face.");
    return IncomingHalfEdgeIterator(start->getTwin(), start->getTwin(), this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Dcel::Vertex::IncomingHalfEdgeIterator.
 *
 * Permette di ciclare sugli half edge incidenti entranti nel vertice, partendo dall'half edge start e fino all'half edge end.
 *
 * @param[in] start: half edge di partenza
 * @param[in] end: half edge di arrivo, che \b non \b è \b compreso
 * @warning Se start e end non risultano avere il vertice this come toVertex, viene lanciata un'asserzione e il programma termina
 * @return Un iteratore che punta all'half edge start
 */
inline Dcel::Vertex::IncomingHalfEdgeIterator Dcel::Vertex::incomingHalfEdgeBegin(HalfEdge* start, HalfEdge* end) {
    assert(start->getToVertex() == this && "Start half edge is not incident to iterated face.");
    assert(end->getToVertex() == this && "End half edge is not incident to iterated face.");
    return IncomingHalfEdgeIterator(start->getTwin(), end->getTwin(), this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Dcel::Vertex::IncidentHalfEdgeIterator.
 *
 * Permette di ciclare sugli half edge incidenti, sia uscenti che entranti nel vertice, partendo dall'incidentHalfEdge.
 *
 * @return Un iteratore che punta all'incidentHalfEdge del vertice
 */
inline Dcel::Vertex::IncidentHalfEdgeIterator Dcel::Vertex::incidentHalfEdgeBegin() {
    assert(checkIncidentHalfEdge() && "Incident half edge is nullptr.");
    return IncidentHalfEdgeIterator(incidentHalfEdge, incidentHalfEdge, this);
}

/**
 * \~Italian
 * @brief Funzione di finalizzazione di Dcel::Vertex::IncidentHalfEdgeIterator
 * @warning L'iteratore restituito non è un iteratore valido, e su di esso le operazioni di
 *          incremento e decremento sono inutili. Questa funzione è da utilizzarsi solamente per
 *          il \b confronto \b con \b un \b altro \b iteratore \b valido
 * @return Un iteratore di finalizzazione
 */
inline Dcel::Vertex::IncidentHalfEdgeIterator Dcel::Vertex::incidentHalfEdgeEnd() {
    return IncidentHalfEdgeIterator(nullptr, nullptr, this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Dcel::Vertex::IncidentHalfEdgeIterator.
 *
 * Permette di ciclare sugli half edge incidenti uscenti e entranti nel vertice, partendo dall'half edge start.
 *
 * @param[in] start: half edge di partenza
 * @warning Se start non risulta avere il vertice this come toVertex o fromVertex, viene lanciata un'asserzione e il programma termina
 * @return Un iteratore che punta all'half edge start
 */
inline Dcel::Vertex::IncidentHalfEdgeIterator Dcel::Vertex::incidentHalfEdgeBegin(HalfEdge* start) {
    assert((start->getFromVertex()==this || start->getToVertex() == this) && "Start half edge is not incident to iterated face.");
    return IncidentHalfEdgeIterator(start, start, this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Dcel::Vertex::IncidentHalfEdgeIterator.
 *
 * Permette di ciclare sugli half edge incidenti uscenti e entranti nel vertice, partendo dall'half edge start e fino all'half edge end.
 *
 * @param[in] start: half edge di partenza
 * @param[in] end: half edge di arrivo, che \b non \b è \b compreso
 * @warning Se start e end non risultano avere il vertice this come toVertex o fromVertex, viene lanciata un'asserzione e il programma termina
 * @return Un iteratore che punta all'half edge start
 */
inline Dcel::Vertex::IncidentHalfEdgeIterator Dcel::Vertex::incidentHalfEdgeBegin(HalfEdge* start, HalfEdge* end) {
    assert((start->getFromVertex()==this || start->getToVertex() == this) && "Start half edge is not incident to iterated face.");
    assert((end->getFromVertex()==this || end->getToVertex() == this) && "End half edge is not incident to iterated face.");
    return IncidentHalfEdgeIterator(start, end, this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Dcel::Vertex::IncidentFaceIterator.
 *
 * Permette di ciclare sulle facce incidenti sul vertice, partendo dalla faccia incidente sull'incidentHalfEdge.
 *
 * @return Un iteratore che punta alla faccia incidente sull'incidentHalfEdge del vertice
 */
inline Dcel::Vertex::IncidentFaceIterator Dcel::Vertex::incidentFaceBegin() {
    //assert(checkIncidentHalfEdge() && "Incident half edge is nullptr.");
    return IncidentFaceIterator(incidentHalfEdge, incidentHalfEdge, this);
}

/**
 * \~Italian
 * @brief Funzione di finalizzazione di Dcel::Vertex::IncidentFaceIterator
 * @warning L'iteratore restituito non è un iteratore valido, e su di esso le operazioni di
 *          incremento e decremento sono inutili. Questa funzione è da utilizzarsi solamente per
 *          il \b confronto \b con \b un \b altro \b iteratore \b valido
 * @return Un iteratore di finalizzazione
 */
inline Dcel::Vertex::IncidentFaceIterator Dcel::Vertex::incidentFaceEnd() {
    return IncidentFaceIterator(nullptr, nullptr, this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Dcel::Vertex::IncidentFaceIterator.
 *
 * Permette di ciclare sulle facce incidenti sul vertice, partendo dalla faccia incidente sull'half edge start.
 *
 * @param[in] start: half edge di partenza
 * @warning Se start non risulta avere il vertice this come fromVertex, viene lanciata un'asserzione e il programma termina
 * @return Un iteratore che punta alla faccia incidente sull'half edge start
 */
inline Dcel::Vertex::IncidentFaceIterator Dcel::Vertex::incidentFaceBegin(HalfEdge* start) {
    assert(start->getFromVertex() == this && "Start half edge is not incident to iterated face.");
    return IncidentFaceIterator(start, start, this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Dcel::Vertex::IncidentFaceIterator.
 *
 * Permette di ciclare sulle facce incidenti sul vertice, partendo dalla faccia incidente sull'half edge start e fino alla faccia incidente sull'half edge end.
 *
 * @param[in] start: half edge di partenza
 * @param[in] end: half edge di arrivo, che \b non \b è \b compreso
 * @warning Se start e end non risultano avere il vertice this come fromVertex, viene lanciata un'asserzione e il programma termina
 * @return Un iteratore che punta alla faccia incidente sull'half edge start
 */
inline Dcel::Vertex::IncidentFaceIterator Dcel::Vertex::incidentFaceBegin(HalfEdge* start, HalfEdge* end) {
    assert(start->getFromVertex() == this && "Start half edge is not incident to iterated face.");
    assert(end->getFromVertex() == this && "End half edge is not incident to iterated face.");
    return IncidentFaceIterator(start, end, this);
}

inline Dcel::Vertex::OutgoingHalfEdgeRangeBasedIterator Dcel::Vertex::outgoingHalfEdgeIterator() {
    return OutgoingHalfEdgeRangeBasedIterator(this);
}

inline Dcel::Vertex::IncomingHalfEdgeRangeBasedIterator Dcel::Vertex::incomingHalfEdgeIterator() {
    return IncomingHalfEdgeRangeBasedIterator(this);
}

inline Dcel::Vertex::IncidentHalfEdgeRangeBasedIterator Dcel::Vertex::incidentHalfEdgeIterator() {
    return IncidentHalfEdgeRangeBasedIterator(this);
}

inline Dcel::Vertex::IncidentFaceRangeBasedIterator Dcel::Vertex::incidentFaceIterator() {
    return IncidentFaceRangeBasedIterator(this);
}

}

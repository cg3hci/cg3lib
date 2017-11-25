/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * @author    Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "dcel_face_iterators.h"

namespace cg3 {

/******************************************
 * Dcel::Face::ConstInnerHalfEdgeIterator *
 ******************************************/

//Constructors

/**
 * \~Italian
 * @brief Costruttore vuoto.
 * Un iteratore inizializzato con questo costruttore non è utilizzabile.
 */
inline Dcel::Face::ConstInnerHalfEdgeIterator::ConstInnerHalfEdgeIterator() {
}

/**
 * \~Italian
 * @brief Costruttore di copia da un InnerHalfEdgeIterator.
 *
 * Inizializza un ConstInnerHalfEdgeIterator pari all'InnerHalfEdgeIterator passato in input.
 * @param[in] it: iteratore di cui ne verrà fatta una copia
 */
inline Dcel::Face::ConstInnerHalfEdgeIterator::ConstInnerHalfEdgeIterator(const Dcel::Face::InnerHalfEdgeIterator& it) : iterator(it) {
}

//Public Operators

/**
 * \~Italian
 * @brief Operatore di dereferenziazione del ConstInnerHalfEdgeIterator
 * @return L'half edge puntato dall'iteratore
 */
inline const Dcel::HalfEdge* Dcel::Face::ConstInnerHalfEdgeIterator::operator * () const {
    return *iterator;
}

/**
 * \~Italian
 * @brief Operatore di uguaglianza tra ConstInnerHalfEdgeIterator.
 *
 * Normale operatore di uguaglianza tra std::vector::iterator.
 *
 * @param[in] otherIterator: iteratore con cui è verificata l'uguaglianza con this
 * @return True se gli iteratori sono uguali, false altrimenti
 */
inline bool Dcel::Face::ConstInnerHalfEdgeIterator::operator == (const Dcel::Face::ConstInnerHalfEdgeIterator& otherIterator) const {
    return iterator == otherIterator.iterator;
}

/**
 * \~Italian
 * @brief Operatore di disuguaglianza tra ConstInnerHalfEdgeIterator
 * @param[in] otherIterator: iteratore con cui è verificata la disuguaglianza con this
 * @return True se gli iteratori sono diversi, false altrimenti
 */
inline bool Dcel::Face::ConstInnerHalfEdgeIterator::operator != (const Dcel::Face::ConstInnerHalfEdgeIterator& otherIterator) const {
    return iterator != otherIterator.iterator;
}

/**
 * \~Italian
 * @brief Operatore di incremento prefisso del ConstInnerHalfEdgeIterator.
 *
 * Normale operatore di incremento prefisso di un std::vector::iterator.
 *
 * @return L'iteratore appena incrementato
 */
inline Dcel::Face::ConstInnerHalfEdgeIterator Dcel::Face::ConstInnerHalfEdgeIterator::operator ++ () {
    return ++iterator;
}

/**
 * \~Italian
 * @brief Operatore di incremento postfisso del ConstInnerHalfEdgeIterator.
 *
 * Normale operatore di incremento prefisso di un std::vector::iterator.
 *
 * @return L'iteratore prima di essere incrementato
 */
inline Dcel::Face::ConstInnerHalfEdgeIterator Dcel::Face::ConstInnerHalfEdgeIterator::operator ++ (int) {
    Dcel::Face::ConstInnerHalfEdgeIterator old = iterator;
    ++iterator;
    return old;
}

/**
 * \~Italian
 * @brief Operatore di decremento prefisso del ConstInnerHalfEdgeIterator.
 *
 * Normale operatore di decremento prefisso di un std::vector::iterator.
 *
 * @return L'iteratore appena decrementato
 */
inline Dcel::Face::ConstInnerHalfEdgeIterator Dcel::Face::ConstInnerHalfEdgeIterator::operator -- () {
    return --iterator;
}

/**
 * \~Italian
 * @brief Operatore di decremento postfisso del ConstInnerHalfEdgeIterator.
 *
 * Normale operatore di decremento prefisso di un std::vector::iterator.
 *
 * @return L'iteratore prima di essere decrementato
 */
inline Dcel::Face::ConstInnerHalfEdgeIterator Dcel::Face::ConstInnerHalfEdgeIterator::operator -- (int) {
    Dcel::Face::ConstInnerHalfEdgeIterator old = iterator;
    --iterator;
    return old;
}

//Protected Constructor

/**
 * \~Italian
 * @brief Costruttore di un ConstInnerHalfEdgeIterator.
 *
 * Inizializza l'iteratore alla posizione di partenza del vettore di inner half edge della faccia.
 * Per questioni di sicurezza e di robustezza del codice questo costruttore non è direttamente richiamabile
 * dal programmatore. Tuttavia, questo costruttore viene richiamato dalla friend class Dcel::Face nei vari metodi
 * begin, che inizializzano correttamente l'iteratore e che possono essere utilizzati dal programmatore per
 * l'inizializzazione dell'iteratore.
 *
 * @param[in] it: iteratore sul vettore di inner half edge della faccia
 */
inline Dcel::Face::ConstInnerHalfEdgeIterator::ConstInnerHalfEdgeIterator(const std::vector<Dcel::HalfEdge*>::const_iterator& it) : iterator(it) {
}

/************************************
 * Dcel::Face::GenericIterator *
 ************************************/

//Constructor

/**
 * \~Italian
 * @brief Costruttore vuoto.
 * Un iteratore inizializzato con questo costruttore non è utilizzabile.
 */
inline Dcel::Face::GenericIterator::GenericIterator() : f(nullptr), start(nullptr), pos(nullptr), end(nullptr) {
}

//Public Operators

/**
 * \~Italian
 * @brief Operatore di uguaglianza tra iteratori.
 *
 * Due AdjacentFaceIterator sono considerati uguali se:
 * - puntano allo stesso half edge;
 * - iterano sulla stessa faccia.
 *
 *
 * @param[in] otherIterator: iteratore con cui è verificata l'uguaglianza con this
 * @return True se gli iteratori sono uguali, false altrimenti
 */
inline bool Dcel::Face::GenericIterator::operator == (const Dcel::Face::GenericIterator& otherIterator) const {
    if (this->pos == otherIterator.pos && this->f == otherIterator.f) return true;
    return false;
}

/**
 * \~Italian
 * @brief Operatore di disuguaglianza tra iteratori
 * @param[in] otherIterator: iteratore con cui è verificata la disuguaglianza con this
 * @return True se gli iteratori sono diversi, false altrimenti
 */
inline bool Dcel::Face::GenericIterator::operator != (const Dcel::Face::GenericIterator& otherIterator) const {
    return !(*this == otherIterator);
}

/**
 * \~Italian
 * @brief Operatore di incremento prefisso dell'iteratore.
 *
 * Esegue un'operazione di \c next() sull'half edge. Se l'half edge ottenuto è uguale
 * all'half edge end, allora l'iteratore diventa uguale all'iteratore \c end().
 *
 * @return L'iteratore appena incrementato
 */
inline Dcel::Face::GenericIterator Dcel::Face::GenericIterator::operator ++ () {
    pos = pos->getNext();
    if (pos == end) pos = nullptr;
    return *this;
}

/**
 * \~Italian
 * @brief Operatore di incremento postfisso dell'iteratore.
 *
 * Esegue un'operazione di \c next() sull'half edge. Se l'half edge ottenuto è uguale
 * all'half edge end, allora l'iteratore diventa uguale all'iteratore \c end().
 *
 * @return L'iteratore prima di essere incrementato
 */
inline Dcel::Face::GenericIterator Dcel::Face::GenericIterator::operator ++ (int) {
    GenericIterator old_value = *this;
    pos = pos->getNext();
    if (pos == end) pos = nullptr;
    return old_value;
}

/**
 * \~Italian
 * @brief Operatore di decremento prefisso dell'iteratore.
 *
 * Esegue un'operazione di \c prev() sull'half edge. Se l'half edge ottenuto è uguale
 * all'half edge end, allora l'iteratore diventa uguale all'iteratore \c end().
 *
 * @return L'iteratore appena decrementato
 */
inline Dcel::Face::GenericIterator Dcel::Face::GenericIterator::operator -- () {
    pos = pos->getPrev();
    if (pos == end) pos = nullptr;
    return *this;
}

/**
 * \~Italian
 * @brief Operatore di decremento postfisso dell'iteratore.
 *
 * Esegue un'operazione di \c prev() sull'half edge. Se l'half edge ottenuto è uguale
 * all'half edge end, allora l'iteratore diventa uguale all'iteratore \c end().
 *
 * @return L'iteratore prima di essere decrementato
 */
inline Dcel::Face::GenericIterator Dcel::Face::GenericIterator::operator -- (int) {
    GenericIterator old_value = *this;
    pos = pos->getPrev();
    if (pos == end) pos = nullptr;
    return old_value;
}

//Protected Constructor

/**
 * \~Italian
 * @brief Costruttore di un iteratore.
 *
 * Setta l'half edge di partenza, l'half edge di arrivo e la faccia su cui iterare.
 * L'iteratore viene inizializzato all'half edge start.
 * Per questioni di sicurezza e di robustezza del codice questo costruttore non è direttamente richiamabile
 * dal programmatore. Tuttavia, questo costruttore viene richiamato dalla friend class Dcel::Face nei vari metodi
 * begin, che inizializzano correttamente l'iteratore e che possono essere utilizzati dal programmatore per
 * l'inizializzazione dell'iteratore.
 *
 * @param[in] start: half edge di start
 * @param[in] end: half edge di end
 * @param[in] f: faccia su cui vengono iterati gli half edge incidenti
 */
inline Dcel::Face::GenericIterator::GenericIterator(HalfEdge* start, HalfEdge* end, Face* f) : f(f), start(start), pos(start), end(end) {
}

/*****************************************
 * Dcel::Face::ConstGenericIterator *
 *****************************************/

//Constructor

/**
 * \~Italian
 * @brief Costruttore vuoto.
 * Un iteratore inizializzato con questo costruttore non è utilizzabile.
 */
inline Dcel::Face::ConstGenericIterator::ConstGenericIterator() : f(nullptr), start(nullptr), pos(nullptr), end(nullptr) {
}

/**
 * \~Italian
 * @brief Costruttore di copia da un iteratore const.
 *
 * Inizializza un ConstAdjacentFaceIterator pari all'AdjacentFaceIterator passato in input.
 * @param[in] it: iteratore di cui ne verrà fatta una copia
 */
inline Dcel::Face::ConstGenericIterator::ConstGenericIterator(const Dcel::Face::GenericIterator& it) : f(it.f), start (it.start), pos(it.pos), end(it.end) {
}

//Public Operators

/**
 * \~Italian
 * @brief Operatore di uguaglianza tra iteratori const.
 *
 * Due AdjacentFaceIterator sono considerati uguali se:
 * - puntano allo stesso half edge;
 * - iterano sulla stessa faccia.
 *
 *
 * @param[in] otherIterator: iteratore con cui è verificata l'uguaglianza con this
 * @return True se gli iteratori sono uguali, false altrimenti
 */
inline bool Dcel::Face::ConstGenericIterator::operator == (const Dcel::Face::ConstGenericIterator& otherIterator) const {
    if (this->pos == otherIterator.pos && this->f == otherIterator.f) return true;
    return false;
}

/**
 * \~Italian
 * @brief Operatore di disuguaglianza tra iteratori const.
 * @param[in] otherIterator: iteratore con cui è verificata la disuguaglianza con this
 * @return True se gli iteratori sono diversi, false altrimenti
 */
inline bool Dcel::Face::ConstGenericIterator::operator != (const Dcel::Face::ConstGenericIterator& otherIterator) const {
    return !(*this == otherIterator);
}

/**
 * \~Italian
 * @brief Operatore di incremento prefisso dell'iteratore const.
 *
 * Esegue un'operazione di \c next() sull'half edge. Se l'half edge ottenuto è uguale
 * all'half edge end, allora l'iteratore diventa uguale all'iteratore \c end().
 *
 * @return L'iteratore appena incrementato
 */
inline Dcel::Face::ConstGenericIterator Dcel::Face::ConstGenericIterator::operator ++ () {
    pos = pos->getNext();
    if (pos == end) pos = nullptr;
    return *this;
}

/**
 * \~Italian
 * @brief Operatore di incremento postfisso dell'iteratore const.
 *
 * Esegue un'operazione di \c next() sull'half edge. Se l'half edge ottenuto è uguale
 * all'half edge end, allora l'iteratore diventa uguale all'iteratore \c end().
 *
 * @return L'iteratore prima di essere incrementato
 */
inline Dcel::Face::ConstGenericIterator Dcel::Face::ConstGenericIterator::operator ++ (int) {
    ConstGenericIterator old_value = *this;
    pos = pos->getNext();
    if (pos == end) pos = nullptr;
    return old_value;
}

/**
 * \~Italian
 * @brief Operatore di decremento prefisso dell'iteratore const.
 *
 * Esegue un'operazione di \c prev() sull'half edge. Se l'half edge ottenuto è uguale
 * all'half edge end, allora l'iteratore diventa uguale all'iteratore \c end().
 *
 * @return L'iteratore appena decrementato
 */
inline Dcel::Face::ConstGenericIterator Dcel::Face::ConstGenericIterator::operator -- () {
    pos = pos->getPrev();
    if (pos == end) pos = nullptr;
    return *this;
}

/**
 * \~Italian
 * @brief Operatore di decremento postfisso dell'iteratore const.
 *
 * Esegue un'operazione di \c prev() sull'half edge. Se l'half edge ottenuto è uguale
 * all'half edge end, allora l'iteratore diventa uguale all'iteratore \c end().
 *
 * @return L'iteratore prima di essere decrementato
 */
inline Dcel::Face::ConstGenericIterator Dcel::Face::ConstGenericIterator::operator -- (int) {
    ConstGenericIterator old_value = *this;
    pos = pos->getPrev();
    if (pos == end) pos = nullptr;
    return old_value;
}

//Protected Constructor

/**
 * \~Italian
 * @brief Costruttore di un iteratore const.
 *
 * Setta l'half edge di partenza, l'half edge di arrivo e la faccia su cui iterare.
 * L'iteratore viene inizializzato all'half edge start.
 * Per questioni di sicurezza e di robustezza del codice questo costruttore non è direttamente richiamabile
 * dal programmatore. Tuttavia, questo costruttore viene richiamato dalla friend class Dcel::Face nei vari metodi
 * begin, che inizializzano correttamente l'iteratore e che possono essere utilizzati dal programmatore per
 * l'inizializzazione dell'iteratore.
 *
 * @param[in] start: half edge di start
 * @param[in] end: half edge di end
 * @param[in] f: faccia su cui vengono iterati gli half edge incidenti
 */
inline Dcel::Face::ConstGenericIterator::ConstGenericIterator(const HalfEdge* start, const HalfEdge* end, const Face* f) : f(f), start(start), pos(start), end(end) {
}

/************************************
 * Dcel::Face::AdjacentFaceIterator *
 ************************************/

//Constructor

/**
 * \~Italian
 * @brief Costruttore vuoto.
 * Un iteratore inizializzato con questo costruttore non è utilizzabile.
 */
inline Dcel::Face::AdjacentFaceIterator::AdjacentFaceIterator() : GenericIterator() {
}

//Public Operators

/**
 * \~Italian
 * @brief Operatore di dereferenziazione dell'AdjacentFaceIterator
 * @return L'half edge puntato dall'iteratore
 */
inline Dcel::Face* Dcel::Face::AdjacentFaceIterator::operator * () const {
    return pos->getTwin()->getFace();
}

//Protected Constructor

/**
 * \~Italian
 * @brief Costruttore di un AdjacentFaceIterator.
 *
 * Setta l'half edge di partenza, l'half edge di arrivo e la faccia su cui iterare.
 * L'iteratore viene inizializzato all'half edge start.
 * Per questioni di sicurezza e di robustezza del codice questo costruttore non è direttamente richiamabile
 * dal programmatore. Tuttavia, questo costruttore viene richiamato dalla friend class Dcel::Face nei vari metodi
 * begin, che inizializzano correttamente l'iteratore e che possono essere utilizzati dal programmatore per
 * l'inizializzazione dell'iteratore.
 *
 * @param[in] start: half edge di start
 * @param[in] end: half edge di end
 * @param[in] f: faccia su cui vengono iterati gli half edge incidenti
 */
inline Dcel::Face::AdjacentFaceIterator::AdjacentFaceIterator(HalfEdge* start, HalfEdge* end, Face* f) : GenericIterator(start, end, f) {
}

/*****************************************
 * Dcel::Face::ConstAdjacentFaceIterator *
 *****************************************/

//Constructor

/**
 * \~Italian
 * @brief Costruttore vuoto.
 * Un iteratore inizializzato con questo costruttore non è utilizzabile.
 */
inline Dcel::Face::ConstAdjacentFaceIterator::ConstAdjacentFaceIterator() : ConstGenericIterator() {
}

/**
 * \~Italian
 * @brief Costruttore di copia da un AdjacentFaceIterator.
 *
 * Inizializza un ConstAdjacentFaceIterator pari all'AdjacentFaceIterator passato in input.
 * @param[in] it: iteratore di cui ne verrà fatta una copia
 */
inline Dcel::Face::ConstAdjacentFaceIterator::ConstAdjacentFaceIterator(const Dcel::Face::AdjacentFaceIterator& it) : ConstGenericIterator(it) {
}

//Public Operators

/**
 * \~Italian
 * @brief Operatore di dereferenziazione dell'AdjacentFaceIterator
 * @return L'half edge puntato dall'iteratore
 */
inline const Dcel::Face* Dcel::Face::ConstAdjacentFaceIterator::operator * () const {
    return pos->getTwin()->getFace();
}

//Protected Constructor

/**
 * \~Italian
 * @brief Costruttore di un ConstAdjacentFaceIterator.
 *
 * Setta l'half edge di partenza, l'half edge di arrivo e la faccia su cui iterare.
 * L'iteratore viene inizializzato all'half edge start.
 * Per questioni di sicurezza e di robustezza del codice questo costruttore non è direttamente richiamabile
 * dal programmatore. Tuttavia, questo costruttore viene richiamato dalla friend class Dcel::Face nei vari metodi
 * begin, che inizializzano correttamente l'iteratore e che possono essere utilizzati dal programmatore per
 * l'inizializzazione dell'iteratore.
 *
 * @param[in] start: half edge di start
 * @param[in] end: half edge di end
 * @param[in] f: faccia su cui vengono iterati gli half edge incidenti
 */
inline Dcel::Face::ConstAdjacentFaceIterator::ConstAdjacentFaceIterator(const HalfEdge* start, const HalfEdge* end, const Face* f) : ConstGenericIterator(start, end, f) {
}

/****************************************
 * Dcel::Face::IncidentHalfEdgeIterator *
 ****************************************/

//Constructor

/**
 * \~Italian
 * @brief Costruttore vuoto.
 * Un iteratore inizializzato con questo costruttore non è utilizzabile.
 */
inline Dcel::Face::IncidentHalfEdgeIterator::IncidentHalfEdgeIterator() : GenericIterator() {
}

//Public Operators

/**
 * \~Italian
 * @brief Operatore di dereferenziazione dell'IncidentHalfEdgeIterator
 * @return L'half edge puntato dall'iteratore
 */
inline Dcel::HalfEdge* Dcel::Face::IncidentHalfEdgeIterator::operator * () const {
    return pos;
}

//Protected Constructor

/**
 * \~Italian
 * @brief Costruttore di un IncidentHalfEdgeIterator.
 *
 * Setta l'half edge di partenza, l'half edge di arrivo e la faccia su cui iterare.
 * L'iteratore viene inizializzato all'half edge start.
 * Per questioni di sicurezza e di robustezza del codice questo costruttore non è direttamente richiamabile
 * dal programmatore. Tuttavia, questo costruttore viene richiamato dalla friend class Dcel::Face nei vari metodi
 * begin, che inizializzano correttamente l'iteratore e che possono essere utilizzati dal programmatore per
 * l'inizializzazione dell'iteratore.
 *
 * @param[in] start: half edge di start
 * @param[in] end: half edge di end
 * @param[in] f: faccia su cui vengono iterati gli half edge incidenti
 */
inline Dcel::Face::IncidentHalfEdgeIterator::IncidentHalfEdgeIterator(HalfEdge* start, HalfEdge* end, Face* f) : GenericIterator(start, end, f) {
}

/*********************************************
 * Dcel::Face::ConstIncidentHalfEdgeIterator *
 *********************************************/

//Constructors

/**
 * \~Italian
 * @brief Costruttore vuoto.
 * Un iteratore inizializzato con questo costruttore non è utilizzabile.
 */
inline Dcel::Face::ConstIncidentHalfEdgeIterator::ConstIncidentHalfEdgeIterator() : ConstGenericIterator() {
}

/**
 * \~Italian
 * @brief Costruttore di copia da un IncidentHalfEdgeIterator.
 *
 * Inizializza un ConstIncidentHalfEdgeIterator pari all'IncidentHalfEdgeIterator passato in input.
 * @param[in] it: iteratore di cui ne verrà fatta una copia
 */
inline Dcel::Face::ConstIncidentHalfEdgeIterator::ConstIncidentHalfEdgeIterator(const Dcel::Face::IncidentHalfEdgeIterator& it) : ConstGenericIterator(it) {
}

//Public Operators

/**
 * \~Italian
 * @brief Operatore di dereferenziazione del ConstIncidentHalfEdgeIterator
 * @return L'half edge puntato dall'iteratore
 */
inline const Dcel::HalfEdge *Dcel::Face::ConstIncidentHalfEdgeIterator::operator * () const {
    return pos;
}

//Protected Constructor

/**
 * \~Italian
 * @brief Costruttore di un ConstIncidentHalfEdgeIterator.
 *
 * Setta l'half edge di partenza, l'half edge di arrivo e la faccia su cui iterare.
 * L'iteratore viene inizializzato all'half edge start.
 * Per questioni di sicurezza e di robustezza del codice questo costruttore non è direttamente richiamabile
 * dal programmatore. Tuttavia, questo costruttore viene richiamato dalla friend class Dcel::Face nei vari metodi
 * begin, che inizializzano correttamente l'iteratore e che possono essere utilizzati dal programmatore per
 * l'inizializzazione dell'iteratore.
 *
 * @param[in] start: half edge di start
 * @param[in] end: half edge di end
 * @param[in] f: faccia su cui vengono iterati gli half edge incidenti
 */
inline Dcel::Face::ConstIncidentHalfEdgeIterator::ConstIncidentHalfEdgeIterator(const HalfEdge* start, const HalfEdge* end, const Face* f) : ConstGenericIterator(start, end, f) {
}

/**************************************
 * Dcel::Face::IncidentVertexIterator *
 **************************************/

//Constructor

/**
 * \~Italian
 * @brief Costruttore vuoto.
 * Un iteratore inizializzato con questo costruttore non è utilizzabile.
 */
inline Dcel::Face::IncidentVertexIterator::IncidentVertexIterator() : GenericIterator() {
}

//Public Operators

/**
 * \~Italian
 * @brief Operatore di dereferenziazione dell'IncidentVertexIterator
 * @return Il to vertex dell'half edge puntato dall'iteratore
 */
inline Dcel::Vertex* Dcel::Face::IncidentVertexIterator::operator * () const {
    return this->pos->getToVertex();
}

//Protected Constructor

/**
 * \~Italian
 * @brief Costruttore di un IncidentVertexIterator.
 *
 * Setta l'half edge di partenza, l'half edge di arrivo e la faccia su cui iterare.
 * L'iteratore viene inizializzato all'half edge start.
 * Per questioni di sicurezza e di robustezza del codice questo costruttore non è direttamente richiamabile
 * dal programmatore. Tuttavia, questo costruttore viene richiamato dalla friend class Dcel::Face nei vari metodi
 * begin, che inizializzano correttamente l'iteratore e che possono essere utilizzati dal programmatore per
 * l'inizializzazione dell'iteratore.
 *
 * @param[in] start: half edge di start
 * @param[in] end: half edge di end
 * @param[in] f: faccia su cui vengono iterati gli half edge incidenti
 */
inline Dcel::Face::IncidentVertexIterator::IncidentVertexIterator(HalfEdge* start, HalfEdge* end, Face* f) : GenericIterator(start, end, f) {
}

/*******************************************
 * Dcel::Face::ConstIncidentVertexIterator *
 *******************************************/

//Constructors

/**
 * \~Italian
 * @brief Costruttore vuoto.
 * Un iteratore inizializzato con questo costruttore non è utilizzabile.
 */
inline Dcel::Face::ConstIncidentVertexIterator::ConstIncidentVertexIterator() : ConstGenericIterator() {
}

/**
 * \~Italian
 * @brief Costruttore di copia da un IncidentVertexIterator.
 *
 * Inizializza un ConstIncidentVertexIterator pari all'IncidentVertexIterator passato in input.
 * @param[in] it: iteratore di cui ne verrà fatta una copia
 */
inline Dcel::Face::ConstIncidentVertexIterator::ConstIncidentVertexIterator(const Dcel::Face::IncidentVertexIterator& it) : ConstGenericIterator(it) {
}

//Public Operators

/**
 * \~Italian
 * @brief Operatore di dereferenziazione dell'ConstIncidentVertexIterator
 * @return Il to vertex dell'half edge puntato dall'iteratore
 */
inline const Dcel::Vertex *Dcel::Face::ConstIncidentVertexIterator::operator * () const {
    return this->pos->getToVertex();
}

//Protected Constructor

/**
 * \~Italian
 * @brief Costruttore di un ConstIncidentVertexIterator.
 *
 * Setta l'half edge di partenza, l'half edge di arrivo e la faccia su cui iterare.
 * L'iteratore viene inizializzato all'half edge start.
 * Per questioni di sicurezza e di robustezza del codice questo costruttore non è direttamente richiamabile
 * dal programmatore. Tuttavia, questo costruttore viene richiamato dalla friend class Dcel::Face nei vari metodi
 * begin, che inizializzano correttamente l'iteratore e che possono essere utilizzati dal programmatore per
 * l'inizializzazione dell'iteratore.
 *
 * @param[in] start: half edge di start
 * @param[in] end: half edge di end
 * @param[in] f: faccia su cui vengono iterati gli half edge incidenti
 */
inline Dcel::Face::ConstIncidentVertexIterator::ConstIncidentVertexIterator(const Dcel::HalfEdge* start, const Dcel::HalfEdge* end, const Dcel::Face* f) : ConstGenericIterator(start, end, f) {
}


inline Dcel::Face::ConstAdjacentFaceIterator Dcel::Face::ConstAdjacentFaceRangeBasedIterator::begin() const {
    return f->adjacentFaceBegin();
}

inline Dcel::Face::ConstAdjacentFaceIterator Dcel::Face::ConstAdjacentFaceRangeBasedIterator::end() const {
    return f->adjacentFaceEnd();
}

inline Dcel::Face::ConstIncidentHalfEdgeIterator Dcel::Face::ConstIncidentHalfEdgeRangeBasedIterator::begin() const {
    return f->incidentHalfEdgeBegin();
}

inline Dcel::Face::ConstIncidentHalfEdgeIterator Dcel::Face::ConstIncidentHalfEdgeRangeBasedIterator::end() const {
    return f->incidentHalfEdgeEnd();
}

inline Dcel::Face::ConstIncidentVertexIterator Dcel::Face::ConstIncidentVertexRangeBasedIterator::begin() const {
    return f->incidentVertexBegin();
}

inline Dcel::Face::ConstIncidentVertexIterator Dcel::Face::ConstIncidentVertexRangeBasedIterator::end() const {
    return f->incidentVertexEnd();
}

inline Dcel::Face::AdjacentFaceIterator Dcel::Face::AdjacentFaceRangeBasedIterator::begin() {
    return f->adjacentFaceBegin();
}

inline Dcel::Face::AdjacentFaceIterator Dcel::Face::AdjacentFaceRangeBasedIterator::end() {
    return f->adjacentFaceEnd();
}

inline Dcel::Face::IncidentHalfEdgeIterator Dcel::Face::IncidentHalfEdgeRangeBasedIterator::begin() {
    return f->incidentHalfEdgeBegin();
}

inline Dcel::Face::IncidentHalfEdgeIterator Dcel::Face::IncidentHalfEdgeRangeBasedIterator::end() {
    return f->incidentHalfEdgeEnd();
}

inline Dcel::Face::IncidentVertexIterator Dcel::Face::IncidentVertexRangeBasedIterator::begin() {
    return f->incidentVertexBegin();
}

inline Dcel::Face::IncidentVertexIterator Dcel::Face::IncidentVertexRangeBasedIterator::end(){
    return f->incidentVertexEnd();
}

/****************************
 * Dcel::Face begin()/end() *
 ****************************/

inline Dcel::Face::ConstAdjacentFaceIterator Dcel::Face::adjacentFaceBegin() const {
    return ConstAdjacentFaceIterator(outerHalfEdge, outerHalfEdge, this);
}

inline Dcel::Face::ConstAdjacentFaceIterator Dcel::Face::adjacentFaceEnd() const {
    return ConstAdjacentFaceIterator(nullptr, nullptr, this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Dcel::Face::ConstInnerHalfEdgeIterator
 * @return Un iteratore che punta al primo inner half edge della faccia
 */
inline Dcel::Face::ConstInnerHalfEdgeIterator Dcel::Face::innerHalfEdgeBegin() const {
    return innerHalfEdges.begin();
}

/**
 * \~Italian
 * @brief Funzione di finalizzazione di Dcel::Face::ConstInnerHalfEdgeIterator
 * @return Un iteratore che punta all'ultimo inner half edge della faccia
 */
inline Dcel::Face::ConstInnerHalfEdgeIterator Dcel::Face::innerHalfEdgeEnd() const {
    return innerHalfEdges.end();
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Dcel::Face::ConstIncidentHalfEdgeIterator.
 *
 * Permette di ciclare sugli half edge incidenti alla faccia, partendo dall'outer half edge.
 *
 * @return Un iteratore che punta all'outer half edge della faccia
 */
inline Dcel::Face::ConstIncidentHalfEdgeIterator Dcel::Face::incidentHalfEdgeBegin() const {
    return ConstIncidentHalfEdgeIterator(outerHalfEdge, outerHalfEdge, this);
}

/**
 * \~Italian
 * @brief Funzione di finalizzazione di Dcel::Face::ConstIncidentHalfEdgeIterator
 * @warning L'iteratore restituito non è un iteratore valido, e su di esso le operazioni di
 *          incremento e decremento sono inutili. Questa funzione è da utilizzarsi solamente per
 *          il \b confronto \b con \b un \b altro \b iteratore \b valido
 * @return Un iteratore di finalizzazione
 */
inline Dcel::Face::ConstIncidentHalfEdgeIterator Dcel::Face::incidentHalfEdgeEnd() const {
    return ConstIncidentHalfEdgeIterator(nullptr, nullptr, this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Dcel::Face::ConstIncidentHalfEdgeIterator.
 *
 * Permette di ciclare sugli half edge incidenti alla faccia, partendo dall'half edge start.
 *
 * @param[in] start: half edge di partenza
 * @warning Se start non risulta essere incidente alla faccia, viene lanciata un'asserzione e il programma termina
 * @return Un iteratore che punta all'half edge start
 */
inline Dcel::Face::ConstIncidentHalfEdgeIterator Dcel::Face::incidentHalfEdgeBegin(const Dcel::HalfEdge* start) const {
    assert(start->getFace() == this && "Start half edge is not incident to iterated face.");
    return ConstIncidentHalfEdgeIterator(start, start, this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Dcel::Face::ConstIncidentHalfEdgeIterator.
 *
 * Permette di ciclare sugli half edge incidenti alla faccia, partendo dall'half edge start e fino all'half edge end.
 *
 * @param[in] start: half edge di partenza
 * @param[in] end: half edge di arrivo, \b non \b compreso
 * @warning Se start e end non risultano essere incidenti alla faccia, viene lanciata un'asserzione e il programma termina
 * @return Un iteratore che punta all'half edge start
 */
inline Dcel::Face::ConstIncidentHalfEdgeIterator Dcel::Face::incidentHalfEdgeBegin(const Dcel::HalfEdge* start, const Dcel::HalfEdge* end) const {
    assert(start->getFace() == this && "Start half edge is not incident to iterated face.");
    assert(end->getFace() == this && "End half edge is not incident to iterated face.");
    return ConstIncidentHalfEdgeIterator(start, end, this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Dcel::Face::ConstIncidentVertexIterator.
 *
 * Permette di ciclare sui vertici incidenti alla faccia, partendo dal toVertex dell'outer half edge.
 *
 * @return Un iteratore che punta al toVertex dell'outer half edge della faccia
 */
inline Dcel::Face::ConstIncidentVertexIterator Dcel::Face::incidentVertexBegin() const {
    return ConstIncidentVertexIterator(outerHalfEdge, outerHalfEdge, this);
}

/**
 * \~Italian
 * @brief Funzione di finalizzazione di Dcel::Face::ConstIncidentVertexIterator
 * @warning L'iteratore restituito non è un iteratore valido, e su di esso le operazioni di
 *          incremento e decremento sono inutili. Questa funzione è da utilizzarsi solamente per
 *          il \b confronto \b con \b un \b altro \b iteratore \b valido
 * @return Un iteratore di finalizzazione
 */
inline Dcel::Face::ConstIncidentVertexIterator Dcel::Face::incidentVertexEnd() const {
    return ConstIncidentVertexIterator(nullptr, nullptr, this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Dcel::Face::ConstIncidentVertexIterator.
 *
 * Permette di ciclare sui vertici incidenti alla faccia, partendo dal toVertex dell'half edge start.
 *
 * @param[in] start: half edge di partenza
 * @warning Se start non risulta essere incidente alla faccia, viene lanciata un'asserzione e il programma termina
 * @return Un iteratore che punta al toVertex dell'half edge start
 */
inline Dcel::Face::ConstIncidentVertexIterator Dcel::Face::incidentVertexBegin(const Dcel::HalfEdge* start) const {
    assert(start->getFace() == this && "Start half edge is not incident to iterated face.");
    return ConstIncidentVertexIterator(start, start, this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Dcel::Face::ConstIncidentVertexIterator.
 *
 * Permette di ciclare sui vertici incidenti alla faccia, partendo dal toVertex dell'half edge start e fino al toVertex dell'half edge end.
 *
 * @param[in] start: half edge di partenza
 * @param[in] end: half edge di arrivo, il cui toVertex \b non \b è \b compreso
 * @warning Se start e end non risultano essere incidenti alla faccia, viene lanciata un'asserzione e il programma termina
 * @return Un iteratore che punta al toVertex dell'half edge start
 */
inline Dcel::Face::ConstIncidentVertexIterator Dcel::Face::incidentVertexBegin(const Dcel::HalfEdge* start, const Dcel::HalfEdge* end) const {
    assert(start->getFace() == this && "Start half edge is not incident to iterated face.");
    assert(end->getFace() == this && "End half edge is not incident to iterated face.");
    return ConstIncidentVertexIterator(start, end, this);
}

inline Dcel::Face::ConstAdjacentFaceRangeBasedIterator Dcel::Face::adjacentFaceIterator() const {
    return ConstAdjacentFaceRangeBasedIterator(this);
}

inline Dcel::Face::ConstIncidentHalfEdgeRangeBasedIterator Dcel::Face::incidentHalfEdgeIterator() const {
    return ConstIncidentHalfEdgeRangeBasedIterator(this);
}

inline Dcel::Face::ConstIncidentVertexRangeBasedIterator Dcel::Face::incidentVertexIterator() const {
    return ConstIncidentVertexRangeBasedIterator(this);
}

inline Dcel::Face::AdjacentFaceIterator Dcel::Face::adjacentFaceBegin() {
    return AdjacentFaceIterator(outerHalfEdge, outerHalfEdge, this);
}

inline Dcel::Face::AdjacentFaceIterator Dcel::Face::adjacentFaceEnd() {
    return AdjacentFaceIterator(nullptr, nullptr, this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Dcel::Face::InnerHalfEdgeIterator
 * @return Un iteratore che punta al primo inner half edge della faccia
 */
inline Dcel::Face::InnerHalfEdgeIterator Dcel::Face::innerHalfEdgeBegin() {
    return innerHalfEdges.begin();
}

/**
 * \~Italian
 * @brief Funzione di finalizzazione di Dcel::Face::InnerHalfEdgeIterator
 * @return Un iteratore che punta all'ultimo inner half edge della faccia
 */
inline Dcel::Face::InnerHalfEdgeIterator Dcel::Face::innerHalfEdgeEnd() {
    return innerHalfEdges.end();
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Dcel::Face::IncidentHalfEdgeIterator.
 *
 * Permette di ciclare sugli half edge incidenti alla faccia, partendo dall'outer half edge.
 *
 * @return Un iteratore che punta all'outer half edge della faccia
 */
inline Dcel::Face::IncidentHalfEdgeIterator Dcel::Face::incidentHalfEdgeBegin() {
    return IncidentHalfEdgeIterator(outerHalfEdge, outerHalfEdge, this);
}

/**
 * \~Italian
 * @brief Funzione di finalizzazione di Dcel::Face::IncidentHalfEdgeIterator
 * @warning L'iteratore restituito non è un iteratore valido, e su di esso le operazioni di
 *          incremento e decremento sono inutili. Questa funzione è da utilizzarsi solamente per
 *          il \b confronto \b con \b un \b altro \b iteratore \b valido
 * @return Un iteratore di finalizzazione
 */
inline Dcel::Face::IncidentHalfEdgeIterator Dcel::Face::incidentHalfEdgeEnd() {
    return IncidentHalfEdgeIterator(nullptr, nullptr, this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Dcel::Face::IncidentHalfEdgeIterator.
 *
 * Permette di ciclare sugli half edge incidenti alla faccia, partendo dall'half edge start.
 *
 * @param[in] start: half edge di partenza
 * @warning Se start non risulta essere incidente alla faccia, viene lanciata un'asserzione e il programma termina
 * @return Un iteratore che punta all'half edge start
 */
inline Dcel::Face::IncidentHalfEdgeIterator Dcel::Face::incidentHalfEdgeBegin(Dcel::HalfEdge* start) {
    assert(start->getFace() == this && "Start half edge is not incident to iterated face.");
    return IncidentHalfEdgeIterator(start, start, this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Dcel::Face::IncidentHalfEdgeIterator.
 *
 * Permette di ciclare sugli half edge incidenti alla faccia, partendo dall'half edge start e fino all'half edge end.
 *
 * @param[in] start: half edge di partenza
 * @param[in] end: half edge di arrivo, \b non \b compreso
 * @warning Se start e end non risultano essere incidenti alla faccia, viene lanciata un'asserzione e il programma termina
 * @return Un iteratore che punta all'half edge start
 */
inline Dcel::Face::IncidentHalfEdgeIterator Dcel::Face::incidentHalfEdgeBegin(Dcel::HalfEdge* start, Dcel::HalfEdge* end) {
    assert(start->getFace() == this && "Start half edge is not incident to iterated face.");
    assert(end->getFace() == this && "End half edge is not incident to iterated face.");
    return IncidentHalfEdgeIterator(start, end, this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Dcel::Face::IncidentVertexIterator.
 *
 * Permette di ciclare sui vertici incidenti alla faccia, partendo dal toVertex dell'outer half edge.
 *
 * @return Un iteratore che punta al toVertex dell'outer half edge della faccia
 */
inline Dcel::Face::IncidentVertexIterator Dcel::Face::incidentVertexBegin() {
    return IncidentVertexIterator(outerHalfEdge, outerHalfEdge, this);
}

/**
 * \~Italian
 * @brief Funzione di finalizzazione di Dcel::Face::IncidentVertexIterator
 * @warning L'iteratore restituito non è un iteratore valido, e su di esso le operazioni di
 *          incremento e decremento sono inutili. Questa funzione è da utilizzarsi solamente per
 *          il \b confronto \b con \b un \b altro \b iteratore \b valido
 * @return Un iteratore di finalizzazione
 */
inline Dcel::Face::IncidentVertexIterator Dcel::Face::incidentVertexEnd() {
    return IncidentVertexIterator(nullptr, nullptr, this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Dcel::Face::IncidentVertexIterator.
 *
 * Permette di ciclare sui vertici incidenti alla faccia, partendo dal toVertex dell'half edge start.
 *
 * @param[in] start: half edge di partenza
 * @warning Se start non risulta essere incidente alla faccia, viene lanciata un'asserzione e il programma termina
 * @return Un iteratore che punta al toVertex dell'half edge start
 */
inline Dcel::Face::IncidentVertexIterator Dcel::Face::incidentVertexBegin(Dcel::HalfEdge* start) {
    assert(start->getFace() == this && "Start half edge is not incident to iterated face.");
    return IncidentVertexIterator(start, start, this);
}

/**
 * \~Italian
 * @brief Funzione di inizializzazione di Dcel::Face::IncidentVertexIterator.
 *
 * Permette di ciclare sui vertici incidenti alla faccia, partendo dal toVertex dell'half edge start e fino al toVertex dell'half edge end.
 *
 * @param[in] start: half edge di partenza
 * @param[in] end: half edge di arrivo, il cui toVertex \b non \b è \b compreso
 * @warning Se start e end non risultano essere incidenti alla faccia, viene lanciata un'asserzione e il programma termina
 * @return Un iteratore che punta al toVertex dell'half edge start
 */
inline Dcel::Face::IncidentVertexIterator Dcel::Face::incidentVertexBegin(Dcel::HalfEdge* start, Dcel::HalfEdge* end) {
    assert(start->getFace() == this && "Start half edge is not incident to iterated face.");
    assert(end->getFace() == this && "End half edge is not incident to iterated face.");
    return IncidentVertexIterator(start, end, this);
}

inline Dcel::Face::AdjacentFaceRangeBasedIterator Dcel::Face::adjacentFaceIterator() {
    return AdjacentFaceRangeBasedIterator(this);
}

inline Dcel::Face::IncidentHalfEdgeRangeBasedIterator Dcel::Face::incidentHalfEdgeIterator() {
    return IncidentHalfEdgeRangeBasedIterator(this);
}

inline Dcel::Face::IncidentVertexRangeBasedIterator Dcel::Face::incidentVertexIterator() {
    return IncidentVertexRangeBasedIterator(this);
}

}

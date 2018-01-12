/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "dcel_iterators.h"

namespace cg3 {

/*****************************
 * Dcel::VertexIterator *
 *****************************/

//Constructors

/**
 * \~Italian
 * @brief Costruttore vuoto.
 * Un iteratore inizializzato con questo costruttore non è utilizzabile.
 */
inline Dcel::VertexIterator::VertexIterator() {
}

//Public Operators

/**
 * \~Italian
 * @brief Operatore di dereferenziazione del constVertexIterator
 * @return Il vertice puntato dall'iteratore
 */
inline Dcel::Vertex* Dcel::VertexIterator::operator * () const {
    return (*vector)[iterator];
}

/**
 * \~Italian
 * @brief Operatore di uguaglianza tra constVertexIterator.
 *
 * Normale operatore di uguaglianza tra std::vector::iterator.
 *
 * @param[in] otherIterator: iteratore con cui è verificata l'uguaglianza con this
 * @return True se gli iteratori sono uguali, false altrimenti
 */
inline bool Dcel::VertexIterator::operator == (const VertexIterator& otherIterator) const {
    return iterator == otherIterator.iterator;
}

/**
 * \~Italian
 * @brief Operatore di disuguaglianza tra constVertexIterator
 * @param[in] otherIterator: iteratore con cui è verificata la disuguaglianza con this
 * @return True se gli iteratori sono diversi, false altrimenti
 */
inline bool Dcel::VertexIterator::operator != (const VertexIterator& otherIterator) const {
    return iterator != otherIterator.iterator;
}

/**
 * \~Italian
 * @brief Operatore di incremento prefisso del constVertexIterator.
 *
 * Normale operatore di incremento prefisso di un std::vector::iterator.
 *
 * @return L'iteratore appena incrementato
 */
inline Dcel::VertexIterator Dcel::VertexIterator::operator ++ () {
    do {
        ++iterator;
    } while (iterator != vector->size() && (*vector)[iterator] == nullptr);
    return *this;
}

/**
 * \~Italian
 * @brief Operatore di incremento postfisso del constVertexIterator.
 *
 * Normale operatore di incremento prefisso di un std::vector::iterator.
 *
 * @return L'iteratore prima di essere incrementato
 */
inline Dcel::VertexIterator Dcel::VertexIterator::operator ++ (int) {
    Dcel::VertexIterator old = *this;
    do {
        ++iterator;
    } while (iterator != vector->size() && (*vector)[iterator] == nullptr);
    return old;
}

/**
 * \~Italian
 * @brief Operatore di decremento prefisso del constVertexIterator.
 *
 * Normale operatore di decremento prefisso di un std::vector::iterator.
 *
 * @return L'iteratore appena decrementato
 */
inline Dcel::VertexIterator Dcel::VertexIterator::operator -- () {
    do {
        --iterator;
    } while (iterator != 0 && (*vector)[iterator] == nullptr);
    return *this;
}

/**
 * \~Italian
 * @brief Operatore di decremento postfisso del constVertexIterator.
 *
 * Normale operatore di decremento prefisso di un std::vector::iterator.
 *
 * @return L'iteratore prima di essere decrementato
 */
inline Dcel::VertexIterator Dcel::VertexIterator::operator -- (int) {
    Dcel::VertexIterator old = *this;
    do {
        --iterator;
    } while (iterator != 0 && (*vector)[iterator] == nullptr);
    return old;
}

//Protected Constructor

/**
 * \~Italian
 * @brief Costruttore di un constVertexIterator.
 *
 * Inizializza l'iteratore alla posizione di partenza del vettore di vertici della Dcel.
 * Per questioni di sicurezza e di robustezza del codice questo costruttore non è direttamente richiamabile
 * dal programmatore. Tuttavia, questo costruttore viene richiamato dalla friend class Dcel nei vari metodi
 * begin, che inizializzano correttamente l'iteratore e che possono essere utilizzati dal programmatore per
 * l'inizializzazione dell'iteratore.
 *
 * @param[in] it: iteratore sul vettore di vertici della Dcel
 */
inline Dcel::VertexIterator::VertexIterator(unsigned int it, const std::vector<Vertex*>& v) : iterator(it), vector(&v) {
}

/*****************************
 * Dcel::constVertexIterator *
 *****************************/

//Constructors

/**
 * \~Italian
 * @brief Costruttore vuoto.
 * Un iteratore inizializzato con questo costruttore non è utilizzabile.
 */
inline Dcel::ConstVertexIterator::ConstVertexIterator() {
}

/**
 * \~Italian
 * @brief Costruttore di copia da un vertexIterator.
 *
 * Inizializza un constVertexIterator pari al vertexIterator passato in input.
 *
 * @param[in] it: iteratore di cui ne verrà fatta una copia
 */
inline Dcel::ConstVertexIterator::ConstVertexIterator(const Dcel::VertexIterator& it) : iterator(it.iterator), vector(it.vector) {
}

//Public Operators

/**
 * \~Italian
 * @brief Operatore di dereferenziazione del constVertexIterator
 * @return Il vertice puntato dall'iteratore
 */
inline const Dcel::Vertex* Dcel::ConstVertexIterator::operator * () const {
    return (*vector)[iterator];
}

/**
 * \~Italian
 * @brief Operatore di uguaglianza tra constVertexIterator.
 *
 * Normale operatore di uguaglianza tra std::vector::iterator.
 *
 * @param[in] otherIterator: iteratore con cui è verificata l'uguaglianza con this
 * @return True se gli iteratori sono uguali, false altrimenti
 */
inline bool Dcel::ConstVertexIterator::operator == (const ConstVertexIterator& otherIterator) const {
    return iterator == otherIterator.iterator;
}

/**
 * \~Italian
 * @brief Operatore di disuguaglianza tra constVertexIterator
 * @param[in] otherIterator: iteratore con cui è verificata la disuguaglianza con this
 * @return True se gli iteratori sono diversi, false altrimenti
 */
inline bool Dcel::ConstVertexIterator::operator != (const ConstVertexIterator& otherIterator) const {
    return iterator != otherIterator.iterator;
}

/**
 * \~Italian
 * @brief Operatore di incremento prefisso del constVertexIterator.
 *
 * Normale operatore di incremento prefisso di un std::vector::iterator.
 *
 * @return L'iteratore appena incrementato
 */
inline Dcel::ConstVertexIterator Dcel::ConstVertexIterator::operator ++ () {
    do {
        ++iterator;
    } while (iterator != vector->size() && (*vector)[iterator] == nullptr);
    return *this;
}

/**
 * \~Italian
 * @brief Operatore di incremento postfisso del constVertexIterator.
 *
 * Normale operatore di incremento prefisso di un std::vector::iterator.
 *
 * @return L'iteratore prima di essere incrementato
 */
inline Dcel::ConstVertexIterator Dcel::ConstVertexIterator::operator ++ (int) {
    Dcel::ConstVertexIterator old = *this;
    do {
        ++iterator;
    } while (iterator != vector->size() && (*vector)[iterator] == nullptr);
    return old;
}

/**
 * \~Italian
 * @brief Operatore di decremento prefisso del constVertexIterator.
 *
 * Normale operatore di decremento prefisso di un std::vector::iterator.
 *
 * @return L'iteratore appena decrementato
 */
inline Dcel::ConstVertexIterator Dcel::ConstVertexIterator::operator -- () {
    do {
        --iterator;
    } while (iterator != 0 && (*vector)[iterator] == nullptr);
    return *this;
}

/**
 * \~Italian
 * @brief Operatore di decremento postfisso del constVertexIterator.
 *
 * Normale operatore di decremento prefisso di un std::vector::iterator.
 *
 * @return L'iteratore prima di essere decrementato
 */
inline Dcel::ConstVertexIterator Dcel::ConstVertexIterator::operator -- (int) {
    Dcel::ConstVertexIterator old = *this;
    do {
        --iterator;
    } while (iterator != 0 && (*vector)[iterator] == nullptr);
    return old;
}

//Protected Constructor

/**
 * \~Italian
 * @brief Costruttore di un constVertexIterator.
 *
 * Inizializza l'iteratore alla posizione di partenza del vettore di vertici della Dcel.
 * Per questioni di sicurezza e di robustezza del codice questo costruttore non è direttamente richiamabile
 * dal programmatore. Tuttavia, questo costruttore viene richiamato dalla friend class Dcel nei vari metodi
 * begin, che inizializzano correttamente l'iteratore e che possono essere utilizzati dal programmatore per
 * l'inizializzazione dell'iteratore.
 *
 * @param[in] it: iteratore sul vettore di vertici della Dcel
 */
inline Dcel::ConstVertexIterator::ConstVertexIterator(unsigned int it, const std::vector<Vertex*>& v) : iterator(it), vector(&v) {
}

/*******************************
 * Dcel::HalfEdgeIterator *
 *******************************/

//Constructors

/**
 * \~Italian
 * @brief Costruttore vuoto.
 * Un iteratore inizializzato con questo costruttore non è utilizzabile.
 */
inline Dcel::HalfEdgeIterator::HalfEdgeIterator() {
}

//Public Operators

/**
 * \~Italian
 * @brief Operatore di dereferenziazione del constHalfEdgeIterator
 * @return L'half edge puntato dall'iteratore
 */
inline Dcel::HalfEdge* Dcel::HalfEdgeIterator::operator * () const {
    return (*vector)[iterator];
}

/**
 * \~Italian
 * @brief Operatore di uguaglianza tra constHalfEdgeIterator.
 *
 * Normale operatore di uguaglianza tra std::vector::iterator.
 *
 * @param[in] otherIterator: iteratore con cui è verificata l'uguaglianza con this
 * @return True se gli iteratori sono uguali, false altrimenti
 */
inline bool Dcel::HalfEdgeIterator::operator == (const HalfEdgeIterator& otherIterator) const {
    return iterator == otherIterator.iterator;
}

/**
 * \~Italian
 * @brief Operatore di disuguaglianza tra constHalfEdgeIterator
 * @param[in] otherIterator: iteratore con cui è verificata la disuguaglianza con this
 * @return True se gli iteratori sono diversi, false altrimenti
 */
inline bool Dcel::HalfEdgeIterator::operator != (const HalfEdgeIterator& otherIterator) const {
    return iterator != otherIterator.iterator;
}

/**
 * \~Italian
 * @brief Operatore di incremento prefisso del constHalfEdgeIterator.
 *
 * Normale operatore di incremento prefisso di un std::vector::iterator.
 *
 * @return L'iteratore appena incrementato
 */
inline Dcel::HalfEdgeIterator Dcel::HalfEdgeIterator::operator ++ () {
    do {
        ++iterator;
    } while (iterator != vector->size() && (*vector)[iterator] == nullptr);
    return *this;
}

/**
 * \~Italian
 * @brief Operatore di incremento postfisso del constHalfEdgeIterator.
 *
 * Normale operatore di incremento prefisso di un std::vector::iterator.
 *
 * @return L'iteratore prima di essere incrementato
 */
inline Dcel::HalfEdgeIterator Dcel::HalfEdgeIterator::operator ++ (int) {
    Dcel::HalfEdgeIterator old = *this;
    do {
        ++iterator;
    } while (iterator != vector->size() && (*vector)[iterator] == nullptr);
    return old;
}

/**
 * \~Italian
 * @brief Operatore di decremento prefisso del constHalfEdgeIterator.
 *
 * Normale operatore di decremento prefisso di un std::vector::iterator.
 *
 * @return L'iteratore appena decrementato
 */
inline Dcel::HalfEdgeIterator Dcel::HalfEdgeIterator::operator -- () {
    do {
        --iterator;
    } while (iterator != 0 && (*vector)[iterator] == nullptr);
    return *this;
}

/**
 * \~Italian
 * @brief Operatore di decremento postfisso del constHalfEdgeIterator.
 *
 * Normale operatore di decremento prefisso di un std::vector::iterator.
 *
 * @return L'iteratore prima di essere decrementato
 */
inline Dcel::HalfEdgeIterator Dcel::HalfEdgeIterator::operator -- (int) {
    Dcel::HalfEdgeIterator old = *this;
    do {
        --iterator;
    } while (iterator != 0 && (*vector)[iterator] == nullptr);
    return old;
}

//Protected Constructor

/**
 * \~Italian
 * @brief Costruttore di un constHalfEdgeIterator.
 *
 * Inizializza l'iteratore alla posizione di partenza del vettore di half edge della Dcel.
 * Per questioni di sicurezza e di robustezza del codice questo costruttore non è direttamente richiamabile
 * dal programmatore. Tuttavia, questo costruttore viene richiamato dalla friend class Dcel nei vari metodi
 * begin, che inizializzano correttamente l'iteratore e che possono essere utilizzati dal programmatore per
 * l'inizializzazione dell'iteratore.
 *
 * @param[in] it: iteratore sul vettore di half edge della Dcel
 */
inline Dcel::HalfEdgeIterator::HalfEdgeIterator(unsigned int it, const std::vector<HalfEdge*>& v) : iterator(it) , vector(&v){
}

/*******************************
 * Dcel::ConstHalfEdgeIterator *
 *******************************/

//Constructors

/**
 * \~Italian
 * @brief Costruttore vuoto.
 * Un iteratore inizializzato con questo costruttore non è utilizzabile.
 */
inline Dcel::ConstHalfEdgeIterator::ConstHalfEdgeIterator() {
}

/**
 * \~Italian
 * @brief Costruttore di copia da un halfEdgeIterator.
 *
 * Inizializza un constHalfEdgeIterator pari al halfEdgeIterator passato in input.
 *
 * @param[in] it: iteratore di cui ne verrà fatta una copia
 */
inline Dcel::ConstHalfEdgeIterator::ConstHalfEdgeIterator(const Dcel::HalfEdgeIterator& it) : iterator(it.iterator), vector(it.vector) {
}

//Public Operators

/**
 * \~Italian
 * @brief Operatore di dereferenziazione del constHalfEdgeIterator
 * @return L'half edge puntato dall'iteratore
 */
inline const Dcel::HalfEdge* Dcel::ConstHalfEdgeIterator::operator * () const {
    return (*vector)[iterator];
}

/**
 * \~Italian
 * @brief Operatore di uguaglianza tra constHalfEdgeIterator.
 *
 * Normale operatore di uguaglianza tra std::vector::iterator.
 *
 * @param[in] otherIterator: iteratore con cui è verificata l'uguaglianza con this
 * @return True se gli iteratori sono uguali, false altrimenti
 */
inline bool Dcel::ConstHalfEdgeIterator::operator == (const ConstHalfEdgeIterator& otherIterator) const {
    return iterator == otherIterator.iterator;
}

/**
 * \~Italian
 * @brief Operatore di disuguaglianza tra constHalfEdgeIterator
 * @param[in] otherIterator: iteratore con cui è verificata la disuguaglianza con this
 * @return True se gli iteratori sono diversi, false altrimenti
 */
inline bool Dcel::ConstHalfEdgeIterator::operator != (const ConstHalfEdgeIterator& otherIterator) const {
    return iterator != otherIterator.iterator;
}

/**
 * \~Italian
 * @brief Operatore di incremento prefisso del constHalfEdgeIterator.
 *
 * Normale operatore di incremento prefisso di un std::vector::iterator.
 *
 * @return L'iteratore appena incrementato
 */
inline Dcel::ConstHalfEdgeIterator Dcel::ConstHalfEdgeIterator::operator ++ () {
    do {
        ++iterator;
    } while (iterator != vector->size() && (*vector)[iterator] == nullptr);
    return *this;
}

/**
 * \~Italian
 * @brief Operatore di incremento postfisso del constHalfEdgeIterator.
 *
 * Normale operatore di incremento prefisso di un std::vector::iterator.
 *
 * @return L'iteratore prima di essere incrementato
 */
inline Dcel::ConstHalfEdgeIterator Dcel::ConstHalfEdgeIterator::operator ++ (int) {
    Dcel::ConstHalfEdgeIterator old = *this;
    do {
        ++iterator;
    } while (iterator != vector->size() && (*vector)[iterator] == nullptr);
    return old;
}

/**
 * \~Italian
 * @brief Operatore di decremento prefisso del constHalfEdgeIterator.
 *
 * Normale operatore di decremento prefisso di un std::vector::iterator.
 *
 * @return L'iteratore appena decrementato
 */
inline Dcel::ConstHalfEdgeIterator Dcel::ConstHalfEdgeIterator::operator -- () {
    do {
        --iterator;
    } while (iterator != 0 && (*vector)[iterator] == nullptr);
    return *this;
}

/**
 * \~Italian
 * @brief Operatore di decremento postfisso del constHalfEdgeIterator.
 *
 * Normale operatore di decremento prefisso di un std::vector::iterator.
 *
 * @return L'iteratore prima di essere decrementato
 */
inline Dcel::ConstHalfEdgeIterator Dcel::ConstHalfEdgeIterator::operator -- (int) {
    Dcel::ConstHalfEdgeIterator old = *this;
    do {
        --iterator;
    } while (iterator != 0 && (*vector)[iterator] == nullptr);
    return old;
}

//Protected Constructor

/**
 * \~Italian
 * @brief Costruttore di un constHalfEdgeIterator.
 *
 * Inizializza l'iteratore alla posizione di partenza del vettore di half edge della Dcel.
 * Per questioni di sicurezza e di robustezza del codice questo costruttore non è direttamente richiamabile
 * dal programmatore. Tuttavia, questo costruttore viene richiamato dalla friend class Dcel nei vari metodi
 * begin, che inizializzano correttamente l'iteratore e che possono essere utilizzati dal programmatore per
 * l'inizializzazione dell'iteratore.
 *
 * @param[in] it: iteratore sul vettore di half edge della Dcel
 */
inline Dcel::ConstHalfEdgeIterator::ConstHalfEdgeIterator(unsigned int it, const std::vector<HalfEdge*>& v) : iterator(it), vector(&v) {
}

/***************************
 * Dcel::FaceIterator *
 ***************************/

//Constructors

/**
 * \~Italian
 * @brief Costruttore vuoto.
 * Un iteratore inizializzato con questo costruttore non è utilizzabile.
 */
inline Dcel::FaceIterator::FaceIterator() {
}

//Public Operators

/**
 * \~Italian
 * @brief Operatore di dereferenziazione del constFaceIterator
 * @return Il vertice puntato dall'iteratore
 */
inline Dcel::Face* Dcel::FaceIterator::operator * () const {
    return (*vector)[iterator];
}

/**
 * \~Italian
 * @brief Operatore di uguaglianza tra constFaceIterator.
 *
 * Normale operatore di uguaglianza tra std::vector::iterator.
 *
 * @param[in] otherIterator: iteratore con cui è verificata l'uguaglianza con this
 * @return True se gli iteratori sono uguali, false altrimenti
 */
inline bool Dcel::FaceIterator::operator == (const FaceIterator& otherIterator) const {
    return iterator == otherIterator.iterator;
}

/**
 * \~Italian
 * @brief Operatore di disuguaglianza tra constFaceIterator
 * @param[in] otherIterator: iteratore con cui è verificata la disuguaglianza con this
 * @return True se gli iteratori sono diversi, false altrimenti
 */
inline bool Dcel::FaceIterator::operator != (const FaceIterator& otherIterator) const {
    return iterator != otherIterator.iterator;
}

/**
 * \~Italian
 * @brief Operatore di incremento prefisso del constFaceIterator.
 *
 * Normale operatore di incremento prefisso di un std::vector::iterator.
 *
 * @return L'iteratore appena incrementato
 */
inline Dcel::FaceIterator Dcel::FaceIterator::operator ++ () {
    do {
        ++iterator;
    } while (iterator != vector->size() && (*vector)[iterator] == nullptr);
    return *this;
}

/**
 * \~Italian
 * @brief Operatore di incremento postfisso del constFaceIterator.
 *
 * Normale operatore di incremento prefisso di un std::vector::iterator.
 *
 * @return L'iteratore prima di essere incrementato
 */
inline Dcel::FaceIterator Dcel::FaceIterator::operator ++ (int) {
    Dcel::FaceIterator old = *this;
    do {
        ++iterator;
    } while (iterator != vector->size() && (*vector)[iterator] == nullptr);
    return old;
}

/**
 * \~Italian
 * @brief Operatore di decremento prefisso del constFaceIterator.
 *
 * Normale operatore di decremento prefisso di un std::vector::iterator.
 *
 * @return L'iteratore appena decrementato
 */
inline Dcel::FaceIterator Dcel::FaceIterator::operator -- () {
    do {
        --iterator;
    } while (iterator != 0 && (*vector)[iterator] == nullptr);
    return *this;
}

/**
 * \~Italian
 * @brief Operatore di decremento postfisso del constFaceIterator.
 *
 * Normale operatore di decremento prefisso di un std::vector::iterator.
 *
 * @return L'iteratore prima di essere decrementato
 */
inline Dcel::FaceIterator Dcel::FaceIterator::operator -- (int) {
    Dcel::FaceIterator old = *this;
    do {
        --iterator;
    } while (iterator != 0 && (*vector)[iterator] == nullptr);
    return old;
}

//Protected Constructor

/**
 * \~Italian
 * @brief Costruttore di un constFaceIterator.
 *
 * Inizializza l'iteratore alla posizione di partenza del vettore di facce della Dcel.
 * Per questioni di sicurezza e di robustezza del codice questo costruttore non è direttamente richiamabile
 * dal programmatore. Tuttavia, questo costruttore viene richiamato dalla friend class Dcel nei vari metodi
 * begin, che inizializzano correttamente l'iteratore e che possono essere utilizzati dal programmatore per
 * l'inizializzazione dell'iteratore.
 *
 * @param[in] it: iteratore sul vettore di facce della Dcel
 */
inline Dcel::FaceIterator::FaceIterator(unsigned int it, const std::vector<Face*>& v) : iterator(it), vector(&v) {
}

/***************************
 * Dcel::constFaceIterator *
 ***************************/

//Constructors

/**
 * \~Italian
 * @brief Costruttore vuoto.
 * Un iteratore inizializzato con questo costruttore non è utilizzabile.
 */
inline Dcel::ConstFaceIterator::ConstFaceIterator() {
}

/**
 * \~Italian
 * @brief Costruttore di copia da un faceIterator.
 *
 * Inizializza un constFaceIterator pari al faceIterator passato in input.
 *
 * @param[in] it: iteratore di cui ne verrà fatta una copia
 */
inline Dcel::ConstFaceIterator::ConstFaceIterator(const Dcel::FaceIterator& it) : iterator(it.iterator), vector(it.vector) {
}

//Public Operators

/**
 * \~Italian
 * @brief Operatore di dereferenziazione del constFaceIterator
 * @return Il vertice puntato dall'iteratore
 */
inline const Dcel::Face* Dcel::ConstFaceIterator::operator * () const {
    return (*vector)[iterator];
}

/**
 * \~Italian
 * @brief Operatore di uguaglianza tra constFaceIterator.
 *
 * Normale operatore di uguaglianza tra std::vector::iterator.
 *
 * @param[in] otherIterator: iteratore con cui è verificata l'uguaglianza con this
 * @return True se gli iteratori sono uguali, false altrimenti
 */
inline bool Dcel::ConstFaceIterator::operator == (const ConstFaceIterator& otherIterator) const {
    return iterator == otherIterator.iterator;
}

/**
 * \~Italian
 * @brief Operatore di disuguaglianza tra constFaceIterator
 * @param[in] otherIterator: iteratore con cui è verificata la disuguaglianza con this
 * @return True se gli iteratori sono diversi, false altrimenti
 */
inline bool Dcel::ConstFaceIterator::operator != (const ConstFaceIterator& otherIterator) const {
    return iterator != otherIterator.iterator;
}

/**
 * \~Italian
 * @brief Operatore di incremento prefisso del constFaceIterator.
 *
 * Normale operatore di incremento prefisso di un std::vector::iterator.
 *
 * @return L'iteratore appena incrementato
 */
inline Dcel::ConstFaceIterator Dcel::ConstFaceIterator::operator ++ () {
    do {
        ++iterator;
    } while (iterator != vector->size() && (*vector)[iterator] == nullptr);
    return *this;
}

/**
 * \~Italian
 * @brief Operatore di incremento postfisso del constFaceIterator.
 *
 * Normale operatore di incremento prefisso di un std::vector::iterator.
 *
 * @return L'iteratore prima di essere incrementato
 */
inline Dcel::ConstFaceIterator Dcel::ConstFaceIterator::operator ++ (int) {
    Dcel::ConstFaceIterator old = *this;
    do {
        ++iterator;
    } while (iterator != vector->size() && (*vector)[iterator] == nullptr);
    return old;
}

/**
 * \~Italian
 * @brief Operatore di decremento prefisso del constFaceIterator.
 *
 * Normale operatore di decremento prefisso di un std::vector::iterator.
 *
 * @return L'iteratore appena decrementato
 */
inline Dcel::ConstFaceIterator Dcel::ConstFaceIterator::operator -- () {
    do {
        --iterator;
    } while (iterator != 0 && (*vector)[iterator] == nullptr);
    return *this;
}

/**
 * \~Italian
 * @brief Operatore di decremento postfisso del constFaceIterator.
 *
 * Normale operatore di decremento prefisso di un std::vector::iterator.
 *
 * @return L'iteratore prima di essere decrementato
 */
inline Dcel::ConstFaceIterator Dcel::ConstFaceIterator::operator -- (int) {
    Dcel::ConstFaceIterator old = *this;
    do {
        --iterator;
    } while (iterator != 0 && (*vector)[iterator] == nullptr);
    return old;
}

//Protected Constructor

/**
 * \~Italian
 * @brief Costruttore di un constFaceIterator.
 *
 * Inizializza l'iteratore alla posizione di partenza del vettore di facce della Dcel.
 * Per questioni di sicurezza e di robustezza del codice questo costruttore non è direttamente richiamabile
 * dal programmatore. Tuttavia, questo costruttore viene richiamato dalla friend class Dcel nei vari metodi
 * begin, che inizializzano correttamente l'iteratore e che possono essere utilizzati dal programmatore per
 * l'inizializzazione dell'iteratore.
 *
 * @param[in] it: iteratore sul vettore di facce della Dcel
 */
inline Dcel::ConstFaceIterator::ConstFaceIterator(unsigned int it, const std::vector<Dcel::Face*> &v) : iterator(it), vector(&v) {
}

/*********************************
 * ConstVertexRangeBasedIterator *
 *********************************/

inline Dcel::ConstVertexIterator Dcel::ConstVertexRangeBasedIterator::begin() const {
    return d->vertexBegin();
}

inline Dcel::ConstVertexIterator Dcel::ConstVertexRangeBasedIterator::end() const {
    return d->vertexEnd();
}

/***********************************
 * ConstHalfEdgeRangeBasedIterator *
 ***********************************/

inline Dcel::ConstHalfEdgeIterator Dcel::ConstHalfEdgeRangeBasedIterator::begin() const {
    return d->halfEdgeBegin();
}

inline Dcel::ConstHalfEdgeIterator Dcel::ConstHalfEdgeRangeBasedIterator::end() const {
    return d->halfEdgeEnd();
}

/*******************************
 * ConstFaceRangeBasedIterator *
 *******************************/

inline Dcel::ConstFaceIterator Dcel::ConstFaceRangeBasedIterator::begin() const {
    return d->faceBegin();
}

inline Dcel::ConstFaceIterator Dcel::ConstFaceRangeBasedIterator::end() const {
    return d->faceEnd();
}

/****************************
 * VertexRangeBasedIterator *
 ****************************/

inline Dcel::VertexIterator Dcel::VertexRangeBasedIterator::begin() {
    return d->vertexBegin();
}

inline Dcel::VertexIterator Dcel::VertexRangeBasedIterator::end() {
    return d->vertexEnd();
}

/******************************
 * HalfEdgeRangeBasedIterator *
 ******************************/

inline Dcel::HalfEdgeIterator Dcel::HalfEdgeRangeBasedIterator::begin() {
    return d->halfEdgeBegin();
}

inline Dcel::HalfEdgeIterator Dcel::HalfEdgeRangeBasedIterator::end() {
    return d->halfEdgeEnd();
}

/**************************
 * FaceRangeBasedIterator *
 **************************/

inline Dcel::FaceIterator Dcel::FaceRangeBasedIterator::begin() {
    return d->faceBegin();
}

inline Dcel::FaceIterator Dcel::FaceRangeBasedIterator::end() {
    return d->faceEnd();
}

}

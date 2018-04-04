/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_DCEL_ITERATORS_H
#define CG3_DCEL_ITERATORS_H

//#include "dcel_struct.h"

namespace cg3 {

class Dcel;

/**
 * \~Italian
 * @class Dcel::VertexIterator
 * @brief Iteratore che permette di ciclare sul vettore dei vertici della Dcel.
 *
 * Come utilizzare questo iteratore data una Dcel d:
 *
 * \code{.cpp}
 * for (Dcel::VertexIterator vit = d.vertexBegin(); vit != d.vertexEnd(); ++vit){
 *     Dcel::Vertex* v = *vit;
 *     // operazioni su v
 * }
 * \endcode
 *
 * L'iteratore si occupa di saltare automaticamente tutti i Dcel::Vertex precedentemente eliminati e quindi settati a nullptr.
 * Questo iteratore non garantisce l'immutabilità della Dcel e quindi non è possibile utilizzarlo su const Dcel.
 * Per const Dcel, vedere Dcel::ConstVertexIterator.
 *
 * @author    Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
class Dcel::VertexIterator
{
    friend class Dcel;

public:
    //Constructors
    VertexIterator();

    //Public Operators
    Dcel::Vertex* operator * () const;
    bool operator == (const VertexIterator& otherIterator) const;
    bool operator != (const VertexIterator& otherIterator) const;

    VertexIterator operator ++ ();
    VertexIterator operator ++ (int);
    VertexIterator operator -- ();
    VertexIterator operator -- (int);

protected:
    //Protected Attributes
    unsigned int iterator; /**< \~Italian @brief Iteratore vero e proprio sul vettore dei vertici della Dcel. */
    const std::vector<Dcel::Vertex*> *vector;
    //Protected Constructor
    VertexIterator(unsigned int it, const std::vector<Dcel::Vertex*> &v);
};

/**
 * \~Italian
 * @class Dcel::ConstVertexIterator
 * @brief Iteratore che permette di ciclare sul vettore dei vertici della Dcel,
 * garantendo l'immutabilità della Dcel stessa.
 *
 * Come utilizzare questo iteratore data una Dcel d:
 *
 * \code{.cpp}
 * for (Dcel::ConstVertexIterator vit = d.vertexBegin(); vit != d.vertexEnd(); ++vit){
 *     const Dcel::Vertex* v = *vit;
 *     // operazioni const su v
 * }
 * \endcode
 *
 * L'iteratore si occupa di saltare automaticamente tutti i Dcel::Vertex precedentemente eliminati e quindi settati a nullptr.
 * Questo iteratore garantisce l'immutabilità della Dcel e quindi è possibile utilizzarlo su const Dcel.
 * Se si ha necessità di modificare i vertici presenti nella Dcel, usare Dcel::VertexIterator.
 *
 * @author    Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
class Dcel::ConstVertexIterator
{
    friend class Dcel;

public:
    //Constructors
    ConstVertexIterator();
    ConstVertexIterator(const Dcel::VertexIterator& it);

    //Public Operators
    const Dcel::Vertex* operator * () const;
    bool operator == (const ConstVertexIterator& otherIterator) const;
    bool operator != (const ConstVertexIterator& otherIterator) const;

    ConstVertexIterator operator ++ ();
    ConstVertexIterator operator ++ (int);
    ConstVertexIterator operator -- ();
    ConstVertexIterator operator -- (int);

protected:
    //Protected Attributes
    unsigned int iterator; /**< \~Italian @brief Iteratore vero e proprio sul vettore dei vertici della Dcel. */
    const std::vector<Dcel::Vertex*> *vector;
    //Protected Constructor
    ConstVertexIterator(unsigned int it, const std::vector<Dcel::Vertex*> &v);
};

/**
 * \~Italian
 * @class Dcel::HalfEdgeIterator
 * @brief Iteratore che permette di ciclare sul vettore degli half edge della Dcel.
 *
 * Come utilizzare questo iteratore data una Dcel d:
 *
 * \code{.cpp}
 * for (Dcel::HalfEdgeIterator heit = d.halfEdgeBegin(); heit != d.halfEdgeEnd(); ++heit){
 *     Dcel::HalfEdge* he = *heit;
 *     // operazioni su he
 * }
 * \endcode
 *
 * L'iteratore si occupa di saltare automaticamente tutti i Dcel::HalfEdge precedentemente eliminati e quindi settati a nullptr.
 * Questo iteratore non garantisce l'immutabilità della Dcel e quindi non è possibile utilizzarlo su const Dcel.
 * Per const Dcel, vedere Dcel::ConstHalfEdgeIterator.
 *
 * @author    Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
class Dcel::HalfEdgeIterator
{
    friend class Dcel;

public:
    //Constructors
    HalfEdgeIterator();

    //Public Operators
    Dcel::HalfEdge* operator * () const;
    bool operator == (const HalfEdgeIterator& otherIterator) const;
    bool operator != (const HalfEdgeIterator& otherIterator) const;

    HalfEdgeIterator operator ++ ();
    HalfEdgeIterator operator ++ (int);
    HalfEdgeIterator operator -- ();
    HalfEdgeIterator operator -- (int);

protected:
    //Protected Attributes
    unsigned int iterator; /**< \~Italian @brief Iteratore vero e proprio sul vettore di half edge della Dcel. */
    const std::vector<Dcel::HalfEdge*> *vector;
    //Protected Constructor
    HalfEdgeIterator(unsigned int it, const std::vector<Dcel::HalfEdge*> &v);
};

/**
 * \~Italian
 * @class Dcel::ConstHalfEdgeIterator
 * @brief Iteratore che permette di ciclare sul vettore degli half edge della Dcel,
 * garantendo l'immutabilità della Dcel stessa.
 *
 * Come utilizzare questo iteratore data una Dcel d:
 *
 * \code{.cpp}
 * for (Dcel::ConstHalfEdgeIterator heit = d.halfEdgeBegin(); heit != d.halfEdgeEnd(); ++heit){
 *     const Dcel::HalfEdge* he = *heit;
 *     // operazioni const su he
 * }
 * \endcode
 *
 * L'iteratore si occupa di saltare automaticamente tutti i Dcel::HalfEdge precedentemente eliminati e quindi settati a nullptr.
 * Questo iteratore garantisce l'immutabilità della Dcel e quindi è possibile utilizzarlo su const Dcel.
 * Se si ha necessità di modificare gli half edge presenti nella Dcel, usare Dcel::HalfEdgeIterator.
 *
 * @author    Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
class Dcel::ConstHalfEdgeIterator
{
    friend class Dcel;

public:
    //Constructors
    ConstHalfEdgeIterator();
    ConstHalfEdgeIterator(const Dcel::HalfEdgeIterator& it);

    //Public Operators
    const Dcel::HalfEdge* operator * () const;
    bool operator == (const ConstHalfEdgeIterator& otherIterator) const;
    bool operator != (const ConstHalfEdgeIterator& otherIterator) const;

    ConstHalfEdgeIterator operator ++ ();
    ConstHalfEdgeIterator operator ++ (int);
    ConstHalfEdgeIterator operator -- ();
    ConstHalfEdgeIterator operator -- (int);

protected:
    //Protected Attributes
    unsigned int iterator; /**< \~Italian @brief Iteratore vero e proprio sul vettore di half edge della Dcel. */
    const std::vector<Dcel::HalfEdge*> *vector;
    //Protected Constructor
    ConstHalfEdgeIterator(unsigned int it, const std::vector<Dcel::HalfEdge*> &v);
};

/**
 * \~Italian
 * @class Dcel::FaceIterator
 * @brief Iteratore che permette di ciclare sul vettore delle facce della Dcel.
 *
 * Come utilizzare questo iteratore data una Dcel d:
 *
 * \code{.cpp}
 * for (Dcel::FaceIterator fit = d.faceBegin(); fit != d.faceEnd(); ++fit){
 *     Dcel::Face* f = *fit;
 *     // operazioni su f
 * }
 * \endcode
 *
 * L'iteratore si occupa di saltare automaticamente tutti i Dcel::Face precedentemente eliminati e quindi settati a nullptr.
 * Questo iteratore non garantisce l'immutabilità della Dcel e quindi non è possibile utilizzarlo su const Dcel.
 * Per const Dcel, vedere Dcel::ConstFaceIterator.
 *
 * @author    Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
class Dcel::FaceIterator
{
    friend class Dcel;

public:
    //Constructors
    FaceIterator();

    //Public Operators
    Dcel::Face* operator * () const;
    bool operator == (const FaceIterator& otherIterator) const;
    bool operator != (const FaceIterator& otherIterator) const;

    FaceIterator operator ++ ();
    FaceIterator operator ++ (int);
    FaceIterator operator -- ();
    FaceIterator operator -- (int);

protected:
    //Protected Attributes
    unsigned int iterator; /**< \~Italian @brief Iteratore vero e proprio sul vettore delle facce della Dcel. */
    const std::vector<Dcel::Face*> *vector;
    //Protected Constructor
    FaceIterator(unsigned int it, const std::vector<Dcel::Face*> &v);
};

/**
 * \~Italian
 * @class Dcel::ConstFaceIterator
 * @brief Iteratore che permette di ciclare sul vettore delle facce della Dcel,
 * garantendo l'immutabilità della Dcel stessa.
 *
 * Come utilizzare questo iteratore data una Dcel d:
 *
 * \code{.cpp}
 * for (Dcel::ConstFaceIterator fit = d.faceBegin(); fit != d.faceEnd(); ++fit){
 *     const Dcel::Face* f = *fit;
 *     // operazioni const su f
 * }
 * \endcode
 *
 * L'iteratore si occupa di saltare automaticamente tutti i Dcel::Face precedentemente eliminati e quindi settati a nullptr.
 * Questo iteratore garantisce l'immutabilità della Dcel e quindi è possibile utilizzarlo su const Dcel.
 * Se si ha necessità di modificare le facce presenti nella Dcel, usare Dcel::FaceIterator.
 *
 * @author    Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
class Dcel::ConstFaceIterator
{
    friend class Dcel;

public:
    //Constructors
    ConstFaceIterator();
    ConstFaceIterator(const Dcel::FaceIterator& it);

    //Public Operators
    const Dcel::Face* operator * () const;
    bool operator == (const ConstFaceIterator& otherIterator) const;
    bool operator != (const ConstFaceIterator& otherIterator) const;

    ConstFaceIterator operator ++ ();
    ConstFaceIterator operator ++ (int);
    ConstFaceIterator operator -- ();
    ConstFaceIterator operator -- (int);

protected:
    //Protected Attributes
    unsigned int iterator; /**< \~Italian @brief Iteratore vero e proprio sul vettore delle facce della Dcel. */
    const std::vector<Dcel::Face*> *vector;
    //Protected Constructor
    ConstFaceIterator(unsigned int it, const std::vector<Dcel::Face*> &v);
};

class Dcel::ConstVertexRangeBasedIterator
{
    friend class Dcel;
public:
    Dcel::ConstVertexIterator begin() const;
    Dcel::ConstVertexIterator end() const;
private:
    ConstVertexRangeBasedIterator(const Dcel *d) : d(d) {}
    const Dcel *d;
};

class Dcel::ConstHalfEdgeRangeBasedIterator
{
    friend class Dcel;
public:
    Dcel::ConstHalfEdgeIterator begin() const;
    Dcel::ConstHalfEdgeIterator end() const;
private:
    ConstHalfEdgeRangeBasedIterator(const Dcel *d) : d(d) {}
    const Dcel *d;
};

class Dcel::ConstFaceRangeBasedIterator
{
    friend class Dcel;
public:
    Dcel::ConstFaceIterator begin() const;
    Dcel::ConstFaceIterator end() const;
private:
    ConstFaceRangeBasedIterator(const Dcel *d) : d(d) {}
    const Dcel *d;
};

class Dcel::VertexRangeBasedIterator
{
    friend class Dcel;
public:
    Dcel::VertexIterator begin();
    Dcel::VertexIterator end();
private:
    VertexRangeBasedIterator(Dcel *d) : d(d) {}
    Dcel *d;
};

class Dcel::HalfEdgeRangeBasedIterator
{
    friend class Dcel;
public:
    Dcel::HalfEdgeIterator begin();
    Dcel::HalfEdgeIterator end();
private:
    HalfEdgeRangeBasedIterator(Dcel *d) : d(d) {}
    Dcel *d;
};

class Dcel::FaceRangeBasedIterator
{
    friend class Dcel;
public:
    Dcel::FaceIterator begin();
    Dcel::FaceIterator end();
private:
    FaceRangeBasedIterator(Dcel *d) : d(d) {}
    Dcel *d;
};

} //namespace cg3

#include "dcel_iterators_inline.tpp"

#endif // CG3_DCEL_ITERATORS_H


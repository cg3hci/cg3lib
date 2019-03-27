/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_DCEL_ITERATORS_H
#define CG3_DCEL_ITERATORS_H

#include <vector>

namespace cg3 {

template <class Vertex, class HalfEdge, class Face>
class TemplatedDcel;

namespace internal{

/**
 * @class DcelIterator
 * @brief Iterator that iterates on a vector of elements (Vertex, HalfEdge, Face) of the Dcel.
 *
 * How to use this iterator in the Dcel (example on Vertex)
 *
 * \code{.cpp}
 * for (Dcel::VertexIterator vit = d.vertexBegin(); vit != d.vertexEnd(); ++vit){
 *     Dcel::Vertex* v = *vit;
 *     // operations in v
 * }
 * \endcode
 *
 * The iterator automatically jumps all the removed elements in the Dcel (setted to nullptr).
 * This iterator cannot be used on non-const cg3::Dcel. For const Dcels, please check ConstDcelIterator.
 *
 * @author    Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
template <class Element>
class DcelIterator {
    template <class Vertex, class HalfEdge, class Face>
    friend class cg3::TemplatedDcel;

public:
    //Constructors
    DcelIterator() {};

    //Public Operators
    Element* operator * () const {return (*vector)[iterator];};
    bool operator == (const DcelIterator<Element>& otherIterator) const {return iterator == otherIterator.iterator;};
    bool operator != (const DcelIterator<Element>& otherIterator) const {return iterator != otherIterator.iterator;};

    DcelIterator<Element> operator ++ () {
        do {
            ++iterator;
        } while (iterator != vector->size() && (*vector)[iterator] == nullptr);
        return *this;
    };
    DcelIterator<Element> operator ++ (int) {
        DcelIterator<Element> old = *this;
        do {
            ++iterator;
        } while (iterator != vector->size() && (*vector)[iterator] == nullptr);
        return old;
    };
    DcelIterator<Element> operator -- () {
        do {
            --iterator;
        } while (iterator != 0 && (*vector)[iterator] == nullptr);
        return *this;
    };
    DcelIterator<Element> operator -- (int) {
        DcelIterator<Element> old = *this;
        do {
            --iterator;
        } while (iterator != 0 && (*vector)[iterator] == nullptr);
        return old;
    };

protected:
    //Protected Attributes
    unsigned int iterator; /**< \~Italian @brief Iteratore vero e proprio sul vettore dei vertici della Dcel. */
    const std::vector<Element*> *vector;
    //Protected Constructor
    DcelIterator(unsigned int it, const std::vector<Element*> &v) : iterator(it), vector(&v) {};
};

/**
 * @class DcelIterator
 * @brief Iterator that iterates on a vector of elements (Vertex, HalfEdge, Face) of the Dcel.
 *
 * How to use this iterator in the Dcel (example on Vertex)
 *
 * \code{.cpp}
 * for (Dcel::ConstVertexIterator vit = d.vertexBegin(); vit != d.vertexEnd(); ++vit){
 *     const Dcel::Vertex* v = *vit;
 *     // const operations in v
 * }
 * \endcode
 *
 * The iterator automatically jumps all the removed elements in the Dcel (setted to nullptr).
 * This iterator does not allow the modification of the iterated elements.
 * Please check DcelIterator if you need to modify iterated elements.
 *
 * @author    Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
template <class Element>
class ConstDcelIterator
{
    template <class Vertex, class HalfEdge, class Face>
    friend class cg3::TemplatedDcel;

public:
    //Constructors
    ConstDcelIterator() {};
    ConstDcelIterator(const DcelIterator<Element>& it) : iterator(it.iterator), vector(it.vector) {};

    //Public Operators
    const Element* operator * () const {return (*vector)[iterator];};
    bool operator == (const ConstDcelIterator<Element>& otherIterator) const {return iterator == otherIterator.iterator;};
    bool operator != (const ConstDcelIterator<Element>& otherIterator) const {return iterator != otherIterator.iterator;};

    ConstDcelIterator<Element> operator ++ () {
        do {
            ++iterator;
        } while (iterator != vector->size() && (*vector)[iterator] == nullptr);
        return *this;
    };
    ConstDcelIterator<Element> operator ++ (int) {
        ConstDcelIterator<Element> old = *this;
        do {
            ++iterator;
        } while (iterator != vector->size() && (*vector)[iterator] == nullptr);
        return old;
    };
    ConstDcelIterator<Element> operator -- () {
        do {
            --iterator;
        } while (iterator != 0 && (*vector)[iterator] == nullptr);
        return *this;
    };
    ConstDcelIterator<Element> operator -- (int) {
        ConstDcelIterator<Element> old = *this;
        do {
            --iterator;
        } while (iterator != 0 && (*vector)[iterator] == nullptr);
        return old;
    };

protected:
    //Protected Attributes
    unsigned int iterator; /**< \~Italian @brief Iteratore vero e proprio sul vettore dei vertici della Dcel. */
    const std::vector<Element*> *vector;
    //Protected Constructor
    ConstDcelIterator<Element>(unsigned int it, const std::vector<Element*> &v) : iterator(it), vector(&v){};
};

} //namespace cg3::internal
} //namespace cg3

#endif

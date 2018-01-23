/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */
#include "tree_reverseiterator.h"

namespace cg3 {


/* --------- REVERSE ITERATOR OPERATOR OVERLOAD --------- */


template <class B, class N, class T>
bool TreeReverseIterator<B,N,T>::operator ==(
        const TreeReverseIterator& otherIterator) const
{
    return (this->node == otherIterator.node);
}

template <class B, class N, class T>
bool TreeReverseIterator<B,N,T>::operator !=(const TreeReverseIterator& otherIterator) const
{
    return !(*this == otherIterator);
}




template <class B, class N, class T>
TreeReverseIterator<B,N,T> TreeReverseIterator<B,N,T>::operator ++()
{
    this->next();
    return *this;
}

template <class B, class N, class T>
TreeReverseIterator<B,N,T> TreeReverseIterator<B,N,T>::operator ++(int)
{
    TreeReverseIterator oldIt = *this;
    this->next();
    return oldIt;
}

template <class B, class N, class T>
TreeReverseIterator<B,N,T> TreeReverseIterator<B,N,T>::operator +(int n)
{
    TreeReverseIterator newIt = *this;
    for (int i = 0; i < n; i++) {
        newIt++;
    }
    return newIt;
}

template <class B, class N, class T>
TreeReverseIterator<B,N,T> TreeReverseIterator<B,N,T>::operator +=(int n)
{
    for (int i = 0; i < n; i++) {
        this->next();
    }
    return *this;
}





template <class B, class N, class T>
TreeReverseIterator<B,N,T> TreeReverseIterator<B,N,T>::operator --()
{
    this->prev();
    return *this;
}

template <class B, class N, class T>
TreeReverseIterator<B,N,T> TreeReverseIterator<B,N,T>::operator --(int)
{
    TreeReverseIterator oldIt = *this;
    this->prev();
    return oldIt;
}

template <class B, class N, class T>
TreeReverseIterator<B,N,T> TreeReverseIterator<B,N,T>::operator -(int n)
{
    TreeReverseIterator newIt = *this;
    for (int i = 0; i < n; i++) {
        newIt--;
    }
    return newIt;
}

template <class B, class N, class T>
TreeReverseIterator<B,N,T> TreeReverseIterator<B,N,T>::operator -=(int n)
{
    for (int i = 0; i < n; i++) {
        this->prev();
    }
    return *this;
}


template <class B, class N, class T>
T& TreeReverseIterator<B,N,T>::operator *() const
{
    return *(this->node->value);
}



/* ----- PROTECTED METHODS ----- */

template <class B, class N, class T>
void TreeReverseIterator<B,N,T>::next() {
    this->node = this->bst->getPrev(*this).node;
}

template <class B, class N, class T>
void TreeReverseIterator<B,N,T>::prev() {
    if (this->node == nullptr) {
        this->node = this->bst->getMin().node;
    }
    else {
        this->node = this->bst->getNext(*this).node;
    }
}




}

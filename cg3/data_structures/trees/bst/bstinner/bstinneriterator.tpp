/**
    @author Stefano Nuvoli
*/
#include "bstinneriterator.h"

//TODO GENERIC/CONST ITERATOR

namespace cg3 {


/* --------- CONSTRUCTORS/DESTRUCTOR --------- */

/**
 * Default constructor
 */
template <class K, class T>
BSTInner<K,T>::Iterator::Iterator(BSTInner<K,T>::Node* node)
{
    this->node = node;
}




/* --------- ITERATOR OPERATORS --------- */

template <class K, class T>
T& BSTInner<K,T>::Iterator::operator *() const
{
    return *(node->value);
}

template <class K, class T>
bool BSTInner<K,T>::Iterator::operator ==(
        const BSTInner<K,T>::Iterator& otherIterator) const
{
    return (node == otherIterator.node);
}

template <class K, class T>
bool BSTInner<K,T>::Iterator::operator !=(const BSTInner<K,T>::Iterator& otherIterator) const
{
    return !(*this == otherIterator);
}

template <class K, class T>
typename BSTInner<K,T>::Iterator BSTInner<K,T>::Iterator::operator ++()
{
    this->next();
    return *this;
}

template <class K, class T>
typename BSTInner<K,T>::Iterator BSTInner<K,T>::Iterator::operator ++(int)
{
    Iterator oldIt = *this;
    this->next();
    return oldIt;
}

template <class K, class T>
typename BSTInner<K,T>::Iterator BSTInner<K,T>::Iterator::operator --()
{
    this->prev();
    return *this;
}

template <class K, class T>
typename BSTInner<K,T>::Iterator BSTInner<K,T>::Iterator::operator --(int)
{
    Iterator oldIt = *this;
    this->prev();
    return oldIt;
}





/* --------- GETTERS/SETTERS --------- */

template <class K, class T>
typename BSTInner<K,T>::Node* BSTInner<K,T>::Iterator::getNode() const
{
    return node;
}




/* --------- PRIVATE METHODS --------- */

template <class K, class T>
void BSTInner<K,T>::Iterator::next() {
    this->node = getSuccessorHelper(this->node);
}

template <class K, class T>
void BSTInner<K,T>::Iterator::prev() {
    this->node = getPredecessorNode(this->node);
}


}

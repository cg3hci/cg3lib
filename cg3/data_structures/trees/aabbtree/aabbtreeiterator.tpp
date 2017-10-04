/**
    @author Stefano Nuvoli
*/
#include "aabbtreeiterator.h"

namespace cg3 {


/* --------- CONSTRUCTORS/DESTRUCTOR --------- */

/**
 * Default constructor
 */
template <int D, class K, class T>
AABBTree<D,K,T>::Iterator::Iterator(AABBTree<D,K,T>::Node* node)
{
    this->node = node;
}




/* --------- ITERATOR OPERATORS --------- */

template <int D, class K, class T>
T& AABBTree<D,K,T>::Iterator::operator *() const
{
    return *(node->value);
}

template <int D, class K, class T>
bool AABBTree<D,K,T>::Iterator::operator ==(
        const AABBTree<D,K,T>::Iterator& otherIterator) const
{
    return (node == otherIterator.node);
}

template <int D, class K, class T>
bool AABBTree<D,K,T>::Iterator::operator !=(const AABBTree<D,K,T>::Iterator& otherIterator) const
{
    return !(*this == otherIterator);
}

template <int D, class K, class T>
typename AABBTree<D,K,T>::Iterator AABBTree<D,K,T>::Iterator::operator ++()
{
    this->next();
    return *this;
}

template <int D, class K, class T>
typename AABBTree<D,K,T>::Iterator AABBTree<D,K,T>::Iterator::operator ++(int)
{
    Iterator oldIt = *this;
    this->next();
    return oldIt;
}

template <int D, class K, class T>
typename AABBTree<D,K,T>::Iterator AABBTree<D,K,T>::Iterator::operator --()
{
    this->prev();
    return *this;
}

template <int D, class K, class T>
typename AABBTree<D,K,T>::Iterator AABBTree<D,K,T>::Iterator::operator --(int)
{
    Iterator oldIt = *this;
    this->prev();
    return oldIt;
}





/* --------- GETTERS/SETTERS --------- */

template <int D, class K, class T>
typename AABBTree<D,K,T>::Node* AABBTree<D,K,T>::Iterator::getNode() const
{
    return node;
}




/* --------- PRIVATE METHODS --------- */

template <int D, class K, class T>
void AABBTree<D,K,T>::Iterator::next() {
    this->node = getSuccessorHelper(this->node);
}

template <int D, class K, class T>
void AABBTree<D,K,T>::Iterator::prev() {
    this->node = getPredecessorNode(this->node);
}




}

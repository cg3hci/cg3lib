/**
    @author Stefano Nuvoli
*/
#include "rangetreeiterator.h"


namespace cg3 {


/* --------- CONSTRUCTORS/DESTRUCTOR --------- */

/**
 * Default constructor
 */
template <class K, class T>
RangeTree<K,T>::Iterator::Iterator(RangeTree<K,T>::Node* node)
{
    this->node = node;
}




/* --------- ITERATOR OPERATORS --------- */

template <class K, class T>
T& RangeTree<K,T>::Iterator::operator *() const
{
    return *(node->value);
}

template <class K, class T>
bool RangeTree<K,T>::Iterator::operator ==(
        const RangeTree<K,T>::Iterator& otherIterator) const
{
    return (node == otherIterator.node);
}

template <class K, class T>
bool RangeTree<K,T>::Iterator::operator !=(const RangeTree<K,T>::Iterator& otherIterator) const
{
    return !(*this == otherIterator);
}

template <class K, class T>
typename RangeTree<K,T>::Iterator RangeTree<K,T>::Iterator::operator ++()
{
    this->next();
    return *this;
}

template <class K, class T>
typename RangeTree<K,T>::Iterator RangeTree<K,T>::Iterator::operator ++(int)
{
    Iterator oldIt = *this;
    this->next();
    return oldIt;
}

template <class K, class T>
typename RangeTree<K,T>::Iterator RangeTree<K,T>::Iterator::operator --()
{
    this->prev();
    return *this;
}

template <class K, class T>
typename RangeTree<K,T>::Iterator RangeTree<K,T>::Iterator::operator --(int)
{
    Iterator oldIt = *this;
    this->prev();
    return oldIt;
}





/* --------- GETTERS/SETTERS --------- */

template <class K, class T>
typename RangeTree<K,T>::Node* RangeTree<K,T>::Iterator::getNode() const
{
    return node;
}




/* --------- PRIVATE METHODS --------- */

template <class K, class T>
void RangeTree<K,T>::Iterator::next() {
    this->node = getSuccessorHelper(this->node);
}

template <class K, class T>
void RangeTree<K,T>::Iterator::prev() {
    this->node = getPredecessorNode(this->node);
}



}

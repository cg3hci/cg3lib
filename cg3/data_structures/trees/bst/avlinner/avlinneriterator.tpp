/**
    @author Stefano Nuvoli
*/
#include "avlinneriterator.h"


namespace cg3 {


/* --------- CONSTRUCTORS/DESTRUCTOR --------- */

/**
 * Default constructor
 */
template <class K, class T>
AVLInner<K,T>::Iterator::Iterator(AVLInner<K,T>::Node* node)
{
    this->node = node;
}




/* --------- ITERATOR OPERATORS --------- */

template <class K, class T>
T& AVLInner<K,T>::Iterator::operator *() const
{
    return *(node->value);
}

template <class K, class T>
bool AVLInner<K,T>::Iterator::operator ==(
        const AVLInner<K,T>::Iterator& otherIterator) const
{
    return (node == otherIterator.node);
}

template <class K, class T>
bool AVLInner<K,T>::Iterator::operator !=(const AVLInner<K,T>::Iterator& otherIterator) const
{
    return !(*this == otherIterator);
}

template <class K, class T>
typename AVLInner<K,T>::Iterator AVLInner<K,T>::Iterator::operator ++()
{
    this->next();
    return *this;
}

template <class K, class T>
typename AVLInner<K,T>::Iterator AVLInner<K,T>::Iterator::operator ++(int)
{
    Iterator oldIt = *this;
    this->next();
    return oldIt;
}

template <class K, class T>
typename AVLInner<K,T>::Iterator AVLInner<K,T>::Iterator::operator --()
{
    this->prev();
    return *this;
}

template <class K, class T>
typename AVLInner<K,T>::Iterator AVLInner<K,T>::Iterator::operator --(int)
{
    Iterator oldIt = *this;
    this->prev();
    return oldIt;
}





/* --------- GETTERS/SETTERS --------- */

template <class K, class T>
typename AVLInner<K,T>::Node* AVLInner<K,T>::Iterator::getNode() const
{
    return node;
}




/* --------- PRIVATE METHODS --------- */

template <class K, class T>
void AVLInner<K,T>::Iterator::next() {
    this->node = getSuccessorHelper(this->node);
}

template <class K, class T>
void AVLInner<K,T>::Iterator::prev() {
    this->node = getPredecessorNode(this->node);
}




}

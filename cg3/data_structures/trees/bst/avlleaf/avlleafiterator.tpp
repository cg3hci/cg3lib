/**
    @author Stefano Nuvoli
*/
#include "avlleafiterator.h"

namespace cg3 {

/* --------- CONSTRUCTORS/DESTRUCTOR --------- */

/**
 * Default constructor
 */
template <class K, class T>
AVLLeaf<K,T>::Iterator::Iterator(AVLLeaf<K,T>::Node* node)
{
    this->node = node;
}




/* --------- ITERATOR OPERATORS --------- */

template <class K, class T>
T& AVLLeaf<K,T>::Iterator::operator *() const
{
    return *(node->value);
}

template <class K, class T>
bool AVLLeaf<K,T>::Iterator::operator ==(
        const AVLLeaf<K,T>::Iterator& otherIterator) const
{
    return (node == otherIterator.node);
}

template <class K, class T>
bool AVLLeaf<K,T>::Iterator::operator !=(const AVLLeaf<K,T>::Iterator& otherIterator) const
{
    return !(*this == otherIterator);
}

template <class K, class T>
typename AVLLeaf<K,T>::Iterator AVLLeaf<K,T>::Iterator::operator ++()
{
    this->next();
    return *this;
}

template <class K, class T>
typename AVLLeaf<K,T>::Iterator AVLLeaf<K,T>::Iterator::operator ++(int)
{
    Iterator oldIt = *this;
    this->next();
    return oldIt;
}

template <class K, class T>
typename AVLLeaf<K,T>::Iterator AVLLeaf<K,T>::Iterator::operator --()
{
    this->prev();
    return *this;
}

template <class K, class T>
typename AVLLeaf<K,T>::Iterator AVLLeaf<K,T>::Iterator::operator --(int)
{
    Iterator oldIt = *this;
    this->prev();
    return oldIt;
}





/* --------- GETTERS/SETTERS --------- */

template <class K, class T>
typename AVLLeaf<K,T>::Node* AVLLeaf<K,T>::Iterator::getNode() const
{
    return node;
}




/* --------- PRIVATE METHODS --------- */

template <class K, class T>
void AVLLeaf<K,T>::Iterator::next() {
    this->node = getSuccessorHelper(this->node);
}

template <class K, class T>
void AVLLeaf<K,T>::Iterator::prev() {
    this->node = getPredecessorNode(this->node);
}


}

/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */
#include "graph_nodeiterator.h"

namespace cg3 {



/* ----- OPERATOR OVERLOAD ----- */


template <class T>
bool Graph<T>::NodeIterator::operator ==(
        const NodeIterator& otherIterator) const
{
    return (this->node == otherIterator.node &&
            this->graph == otherIterator.graph);
}

template <class T>
bool Graph<T>::NodeIterator::operator !=(const NodeIterator& otherIterator) const
{
    return !(*this == otherIterator);
}



template <class T>
typename Graph<T>::NodeIterator Graph<T>::NodeIterator::operator ++()
{
    this->next();
    return *this;
}

template <class T>
typename Graph<T>::NodeIterator Graph<T>::NodeIterator::operator ++(int)
{
    NodeIterator oldIt = *this;
    this->next();
    return oldIt;
}



template <class T>
const T& Graph<T>::NodeIterator::operator *() const
{
    return this->node->value;
}



/* ----- PROTECTED METHODS FOR NAVIGATION ----- */

template <class T>
void Graph<T>::NodeIterator::next() {
    typename std::vector<Node*>::iterator it = this->graph->nodes.begin();
    std::advance(it, this->node->id);

    do {
        it++;
    } while (it != this->graph->nodes.end() &&
             *it == nullptr);

    if (it == this->graph->nodes.end())
        this->node = nullptr;
    else
        this->node = *it;
}



/* --------- RANGE BASED ITERATOR --------- */

template <class T>
typename Graph<T>::NodeIterator Graph<T>::RangeBasedNodeIterator::begin() {
    return this->graph->nodeIteratorBegin();
}

template <class T>
typename Graph<T>::NodeIterator Graph<T>::RangeBasedNodeIterator::end() {
    return this->graph->nodeIteratorEnd();
}


}

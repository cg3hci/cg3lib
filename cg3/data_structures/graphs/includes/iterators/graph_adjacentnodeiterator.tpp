/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */
#include "graph_adjacentnodeiterator.h"

namespace cg3 {



/* ----- OPERATOR OVERLOAD ----- */


template <class T>
bool Graph<T>::AdjacentNodeIterator::operator ==(
        const AdjacentNodeIterator& otherIterator) const
{
    return (this->node == otherIterator.node &&
            this->targetNode == otherIterator.targetNode &&
            this->graph == otherIterator.graph);
}

template <class T>
bool Graph<T>::AdjacentNodeIterator::operator !=(const AdjacentNodeIterator& otherIterator) const
{
    return !(*this == otherIterator);
}



template <class T>
typename Graph<T>::AdjacentNodeIterator Graph<T>::AdjacentNodeIterator::operator ++()
{
    this->next();
    return *this;
}

template <class T>
typename Graph<T>::AdjacentNodeIterator Graph<T>::AdjacentNodeIterator::operator ++(int)
{
    AdjacentNodeIterator oldIt = *this;
    this->next();
    return oldIt;
}


template <class T>
const T& Graph<T>::AdjacentNodeIterator::operator *() const
{
    return this->node->value;
}



/* ----- PROTECTED METHODS FOR NAVIGATION ----- */

template <class T>
void Graph<T>::AdjacentNodeIterator::next() {
    std::unordered_map<size_t, double>& map = this->targetNode->adjacentNodes;
    std::unordered_map<size_t, double>::iterator it = map.find(this->node->id);

    do {
        it++;
    } while (it != map.end() &&
             this->graph->nodes.at(it->first) == nullptr);

    if (it == map.end())
        this->node = nullptr;
    else
        this->node = this->graph->nodes.at(it->first);
}





/* --------- RANGE BASED ITERATOR --------- */

template <class T>
typename Graph<T>::AdjacentNodeIterator Graph<T>::RangeBasedAdjacentNodeIterator::begin() {
    return this->graph->adjacentNodeIteratorBegin(node);
}

template <class T>
typename Graph<T>::AdjacentNodeIterator Graph<T>::RangeBasedAdjacentNodeIterator::end() {
    return this->graph->adjacentNodeIteratorEnd(node);
}


}

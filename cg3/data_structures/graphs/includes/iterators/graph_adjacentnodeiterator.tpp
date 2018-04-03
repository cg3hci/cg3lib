/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */
#include "graph_adjacentnodeiterator.h"

namespace cg3 {

/* ----- CONSTRUCTORS ----- */

template <class T>
Graph<T>::AdjacentNodeIterator::AdjacentNodeIterator(
        Graph<T>* graph) :
    Graph<T>::GenericNodeIterator(graph),
    targetNodeIt(this->graph->nodeIteratorEnd()),
    it(std::unordered_map<size_t, double>::iterator())
{

}

template <class T>
Graph<T>::AdjacentNodeIterator::AdjacentNodeIterator(
        Graph<T>* graph,
        const NodeIterator& targetNodeIt,
        std::unordered_map<size_t, double>::iterator it) :
    Graph<T>::GenericNodeIterator(graph),
    targetNodeIt(targetNodeIt),
    it(it)
{
    if (targetNodeIt != this->graph->nodeIteratorEnd() &&
            it != this->graph->nodes.at((size_t) targetNodeIt.id).adjacentNodes.end())
    {
        this->id = it->first;
    }
}



/* ----- OPERATOR OVERLOAD ----- */


template <class T>
bool Graph<T>::AdjacentNodeIterator::operator ==(
        const AdjacentNodeIterator& otherIterator) const
{
    return (this->graph == otherIterator.graph &&
            this->id == otherIterator.id &&
            targetNodeIt == otherIterator.targetNodeIt &&
            it == otherIterator.it);
}

template <class T>
bool Graph<T>::AdjacentNodeIterator::operator !=(const AdjacentNodeIterator& otherIterator) const
{
    return !(*this == otherIterator);
}



template <class T>
typename Graph<T>::AdjacentNodeIterator Graph<T>::AdjacentNodeIterator::operator ++()
{
    next();
    return *this;
}

template <class T>
typename Graph<T>::AdjacentNodeIterator Graph<T>::AdjacentNodeIterator::operator ++(int)
{
    AdjacentNodeIterator oldIt = *this;
    next();
    return oldIt;
}


template <class T>
const T& Graph<T>::AdjacentNodeIterator::operator *() const
{
    return this->graph->nodes.at((size_t) this->id).value;
}



/* ----- PROTECTED METHODS FOR NAVIGATION ----- */

template <class T>
void Graph<T>::AdjacentNodeIterator::next()
{
    ++it;
    it = this->graph->getFirstValidIteratorAdjacent(targetNodeIt, it);

    if (it != this->graph->nodes.at((size_t) targetNodeIt.id).adjacentNodes.end()) {
        this->id = it->first;
    }
    else {
        this->id = -1;
    }
}





/* --------- RANGE BASED ITERATOR --------- */

template <class T>
typename Graph<T>::AdjacentNodeIterator Graph<T>::RangeBasedAdjacentNodeIterator::begin()
{
    return this->graph->adjacentNodeIteratorBegin(targetNodeIt);
}

template <class T>
typename Graph<T>::AdjacentNodeIterator Graph<T>::RangeBasedAdjacentNodeIterator::end()
{
    return this->graph->adjacentNodeIteratorEnd(targetNodeIt);
}


}

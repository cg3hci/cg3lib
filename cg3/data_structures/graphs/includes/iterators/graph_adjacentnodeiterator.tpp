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
    if (targetNodeIt != this->graph->nodeIteratorEnd() && it != targetNodeIt.node->adjacentNodes.end())
    {
        this->node = this->graph->nodes.at(it->first);
    }
}



/* ----- OPERATOR OVERLOAD ----- */


template <class T>
bool Graph<T>::AdjacentNodeIterator::operator ==(
        const AdjacentNodeIterator& otherIterator) const
{
    return (this->graph == otherIterator.graph &&
            this->node == otherIterator.node &&
            this->targetNodeIt == otherIterator.targetNodeIt &&
            this->it == otherIterator.it);
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
    ++this->it;
    this->it = this->graph->getFirstValidIteratorAdjacent(this->targetNodeIt, this->it);

    if (this->it != targetNodeIt.node->adjacentNodes.end())
        this->node = this->graph->nodes.at(it->first);
    else
        this->node = nullptr;
}





/* --------- RANGE BASED ITERATOR --------- */

template <class T>
typename Graph<T>::AdjacentNodeIterator Graph<T>::RangeBasedAdjacentNodeIterator::begin() {
    return this->graph->adjacentNodeIteratorBegin(targetNodeIt);
}

template <class T>
typename Graph<T>::AdjacentNodeIterator Graph<T>::RangeBasedAdjacentNodeIterator::end() {
    return this->graph->adjacentNodeIteratorEnd(targetNodeIt);
}


}

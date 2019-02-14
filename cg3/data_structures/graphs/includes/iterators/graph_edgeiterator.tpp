/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */
#include "graph_edgeiterator.h"

namespace cg3 {


/* ----- CONSTRUCTORS ----- */

template <class T>
Graph<T>::EdgeIterator::EdgeIterator() :
    graph(nullptr),
    nodeIt(NodeIterator()),
    adjIt(AdjacentIterator())
{

}

template <class T>
Graph<T>::EdgeIterator::EdgeIterator(
        const Graph<T>* graph) :
    graph(graph),
    nodeIt(graph->nodeIteratorEnd()),
    adjIt(graph->adjacentNodeIteratorEnd(graph->nodeIteratorEnd()))
{

}

template <class T>
Graph<T>::EdgeIterator::EdgeIterator(
        const Graph<T>* graph,
        const typename Graph<T>::NodeIterator& nodeIt,
        const typename Graph<T>::AdjacentIterator& adjIt) :
    graph(graph),
    nodeIt(nodeIt),
    adjIt(adjIt)
{

}


/* ----- OPERATOR OVERLOAD ----- */


template <class T>
bool Graph<T>::EdgeIterator::operator ==(
        const EdgeIterator& otherIterator) const
{
    return (this->graph == otherIterator.graph &&
            this->nodeIt == otherIterator.nodeIt &&
            this->adjIt == otherIterator.adjIt);
}

template <class T>
bool Graph<T>::EdgeIterator::operator !=(const EdgeIterator& otherIterator) const
{
    return !(*this == otherIterator);
}



template <class T>
typename Graph<T>::EdgeIterator Graph<T>::EdgeIterator::operator ++()
{
    this->next();
    return *this;
}

template <class T>
typename Graph<T>::EdgeIterator Graph<T>::EdgeIterator::operator ++(int)
{
    EdgeIterator oldIt = *this;
    this->next();
    return oldIt;
}



template <class T>
std::pair<const T, const T> Graph<T>::EdgeIterator::operator *() const
{
    return std::make_pair(*nodeIt, *adjIt);
}



/* ----- PROTECTED METHODS FOR NAVIGATION ----- */

template <class T>
void Graph<T>::EdgeIterator::next()
{
    adjIt++;
    this->graph->getFirstValidIteratorEdge(nodeIt, adjIt, nodeIt, adjIt);
}



/* --------- RANGE BASED ITERATOR --------- */

template <class T>
typename Graph<T>::EdgeIterator Graph<T>::RangeBasedEdgeIterator::begin()
{
    return this->graph->edgeBegin();
}

template <class T>
typename Graph<T>::EdgeIterator Graph<T>::RangeBasedEdgeIterator::end()
{
    return this->graph->edgeEnd();
}


}

/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */
#include "graph_nodeiterator.h"

namespace cg3 {


/* ----- CONSTRUCTORS ----- */

template <class T>
Graph<T>::NodeIterator::NodeIterator() :
    Graph<T>::GenericNodeIterator(),
    it(typename std::vector<Node>::const_iterator())
{

}

template <class T>
Graph<T>::NodeIterator::NodeIterator(
        const Graph<T>* graph) :
    Graph<T>::GenericNodeIterator(graph),
    it(typename std::vector<Node>::const_iterator())
{

}

template <class T>
Graph<T>::NodeIterator::NodeIterator(
        const Graph<T>* graph,
        typename std::vector<Node>::const_iterator it) :
    Graph<T>::GenericNodeIterator(graph),
    it(it)
{
    if (it != this->graph->nodes.end())
        this->id = it->id;
}


/* ----- OPERATOR OVERLOAD ----- */


template <class T>
bool Graph<T>::NodeIterator::operator ==(
        const NodeIterator& otherIterator) const
{
    return (this->graph == otherIterator.graph &&
            this->id == otherIterator.id &&
            it == otherIterator.it);
}

template <class T>
bool Graph<T>::NodeIterator::operator !=(const NodeIterator& otherIterator) const
{
    return !(*this == otherIterator);
}



template <class T>
typename Graph<T>::NodeIterator Graph<T>::NodeIterator::operator ++()
{
    next();
    return *this;
}

template <class T>
typename Graph<T>::NodeIterator Graph<T>::NodeIterator::operator ++(int)
{
    NodeIterator oldIt = *this;
    next();
    return oldIt;
}



template <class T>
const T& Graph<T>::NodeIterator::operator *() const
{
    return it->value;
}



/* ----- PROTECTED METHODS FOR NAVIGATION ----- */

template <class T>
void Graph<T>::NodeIterator::next()
{
    ++it;
    it = this->graph->getFirstValidIteratorNode(it);

    if (it != this->graph->nodes.end())
        this->id = it->id;
    else
        this->id = -1;
}



/* --------- RANGE BASED ITERATOR --------- */

template <class T>
typename Graph<T>::NodeIterator Graph<T>::RangeBasedNodeIterator::begin()
{
    return this->graph->nodeBegin();
}

template <class T>
typename Graph<T>::NodeIterator Graph<T>::RangeBasedNodeIterator::end()
{
    return this->graph->nodeEnd();
}


}

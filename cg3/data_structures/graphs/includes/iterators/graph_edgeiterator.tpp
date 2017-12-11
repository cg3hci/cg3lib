/**
    @author Stefano Nuvoli
*/
#include "graph_edgeiterator.h"

namespace cg3 {



/* ----- OPERATOR OVERLOAD ----- */


template <class T>
bool Graph<T>::EdgeIterator::operator ==(
        const EdgeIterator& otherIterator) const
{
    return (this->nodeIt == otherIterator.nodeIt &&
            this->adjIt == otherIterator.adjIt &&
            this->graph == this->graph);
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
void Graph<T>::EdgeIterator::next() {
    if (nodeIt == graph->nodeIteratorEnd()) {
        adjIt = graph->adjacentNodeIteratorEnd(nullptr);
        return;
    }

    adjIt++;

    while (adjIt == graph->adjacentNodeIteratorEnd(nodeIt)) {
        nodeIt++;

        if (nodeIt == graph->nodeIteratorEnd()) {
            adjIt = graph->adjacentNodeIteratorEnd(nullptr);
            return;
        }

        adjIt = graph->adjacentNodeIteratorBegin(nodeIt);
    }

}



/* --------- RANGE BASED ITERATOR --------- */

template <class T>
typename Graph<T>::EdgeIterator Graph<T>::RangeBasedEdgeIterator::begin() {
    return this->graph->edgeIteratorBegin();
}

template <class T>
typename Graph<T>::EdgeIterator Graph<T>::RangeBasedEdgeIterator::end() {
    return this->graph->edgeIteratorEnd();
}


}

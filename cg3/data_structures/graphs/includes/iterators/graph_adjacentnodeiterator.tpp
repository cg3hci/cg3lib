/**
    @author Stefano Nuvoli
*/
#include "graph_adjacentnodeiterator.h"

namespace cg3 {



/* ----- OPERATOR OVERLOAD ----- */


template <class T>
bool Graph<T>::AdjacentNodeIterator::operator ==(
        const AdjacentNodeIterator& otherIterator) const
{
    return (this->adjacentNode == otherIterator.adjacentNode &&
            this->node == otherIterator.node &&
            this->graph == this->graph);
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
    return adjacentNode->value;
}



/* ----- PROTECTED METHODS FOR NAVIGATION ----- */

template <class T>
void Graph<T>::AdjacentNodeIterator::next() {
    std::unordered_map<unsigned int, double>& map = node->adjacentNodes;
    std::unordered_map<unsigned int, double>::iterator it = map.find(adjacentNode->id);

    do {
        it++;
    } while (it != map.end() && graph->nodes.at(it->first) == nullptr);

    if (it == map.end())
        this->adjacentNode = nullptr;
    else
        this->adjacentNode = graph->nodes.at(it->first);
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

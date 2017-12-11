/**
    @author Stefano Nuvoli
*/
#include "graph_nodeiterator.h"

namespace cg3 {



/* ----- OPERATOR OVERLOAD ----- */


template <class T>
bool Graph<T>::NodeIterator::operator ==(
        const NodeIterator& otherIterator) const
{
    return (this->node == otherIterator.node &&
            this->graph == this->graph);
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
    return node->value;
}



/* ----- PROTECTED METHODS FOR NAVIGATION ----- */

template <class T>
void Graph<T>::NodeIterator::next() {
    typename std::vector<Node*>::iterator it = graph->nodes.begin();
    std::advance(it, pos);

    do {
        it++;
        pos++;
    } while (it != graph->nodes.end() && *it == nullptr);

    if (it == graph->nodes.end())
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

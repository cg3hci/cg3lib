#ifndef CG3_GRAPH_ADJACENTITERATOR_H
#define CG3_GRAPH_ADJACENTITERATOR_H

#include "graph_genericnodeiterator.h"

namespace cg3 {

/**
 * @brief The iterator of a graph
 */
template <class T>
class Graph<T>::AdjacentIterator :
        public Graph<T>::GenericNodeIterator,
        public std::iterator<std::forward_iterator_tag, T>
{

    friend class Graph<T>;

public:

    /* Constructors */

    inline AdjacentIterator();

private:

    inline AdjacentIterator(
            const Graph<T>* graph);

    inline AdjacentIterator(
            const Graph<T>* graph,
            const NodeIterator& targetNodeIt,
            std::unordered_map<size_t, double>::const_iterator it);
public:

    /* Iterator operators */

    inline bool operator == (const AdjacentIterator& otherIterator) const;
    inline bool operator != (const AdjacentIterator& otherIterator) const;

    inline AdjacentIterator operator ++ ();
    inline AdjacentIterator operator ++ (int);

    inline const T& operator *() const;

private:

    /* Private methods */

    inline void next();


    /* Fields */

    NodeIterator targetNodeIt;
    std::unordered_map<size_t, double>::const_iterator it;

};


/**
 * @brief The range based iterator class for the graph
 */
template <class T>
class Graph<T>::RangeBasedAdjacentIterator {

public:

    inline RangeBasedAdjacentIterator(
            const Graph<T>* graph,
            const NodeIterator& targetNodeIt) :
        graph(graph), targetNodeIt(targetNodeIt) {}

    inline AdjacentIterator begin();
    inline AdjacentIterator end();

private:

    const Graph<T>* graph;
    NodeIterator targetNodeIt;

};

}


#include "graph_adjacentiterator.cpp"

#endif // CG3_GRAPH_ADJACENTITERATOR_H

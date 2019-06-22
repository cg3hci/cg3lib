#ifndef CG3_GRAPH_EDGEITERATOR_H
#define CG3_GRAPH_EDGEITERATOR_H

#include <iterator>
#include <vector>
#include <utility>

#include "../../graph.h"

namespace cg3 {

/**
 * @brief The edge iterator of a graph
 */
template <class T>
class Graph<T>::EdgeIterator :
        public std::iterator<
            std::forward_iterator_tag,
            std::pair<const T&, const T&>
        >
{

    friend class Graph<T>;

public:

    /* Constructors */

    inline EdgeIterator();

private:

    inline EdgeIterator(
            const Graph<T>* graph);

    inline EdgeIterator(
            const Graph<T>* graph,
            const typename Graph<T>::NodeIterator& nodeIt,
            const typename Graph<T>::AdjacentIterator& adjIt);

public:

    /* Iterator operators */

    inline bool operator == (const EdgeIterator& otherIterator) const;
    inline bool operator != (const EdgeIterator& otherIterator) const;

    inline EdgeIterator operator ++ ();
    inline EdgeIterator operator ++ (int);

    inline std::pair<const T, const T> operator *() const;

private:

    /* Private methods */

    inline void next();


    /* Fields */

    const Graph<T>* graph;

    typename Graph<T>::NodeIterator nodeIt;
    typename Graph<T>::AdjacentIterator adjIt;

};


/**
 * @brief The range based iterator class for the graph
 */
template <class T>
class Graph<T>::RangeBasedEdgeIterator {

public:

    inline RangeBasedEdgeIterator(const Graph<T>* graph) :
        graph(graph) {}

    inline EdgeIterator begin();
    inline EdgeIterator end();

private:

    const Graph<T>* graph;

};

}


#include "graph_edgeiterator.cpp"

#endif // CG3_GRAPH_EDGEITERATOR_H

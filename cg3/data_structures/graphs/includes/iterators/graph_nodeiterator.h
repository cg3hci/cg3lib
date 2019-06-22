#ifndef CG3_GRAPH_NODEITERATOR_H
#define CG3_GRAPH_NODEITERATOR_H

#include "graph_genericnodeiterator.h"

#include <vector>

namespace cg3 {

/**
 * @brief The node iterator of a graph
 */
template <class T>
class Graph<T>::NodeIterator :
        public Graph<T>::GenericNodeIterator,
        public std::iterator<std::forward_iterator_tag, T>
{

    friend class Graph<T>;

public:

    /* Constructors */

    inline NodeIterator();

private:

    inline NodeIterator(
            const Graph<T>* graph);

    inline NodeIterator(
            const Graph<T>* graph,
            typename std::vector<Node>::const_iterator it);

public:

    /* Iterator operators */

    inline bool operator == (const NodeIterator& otherIterator) const;
    inline bool operator != (const NodeIterator& otherIterator) const;

    inline NodeIterator operator ++ ();
    inline NodeIterator operator ++ (int);

    inline const T& operator *() const;

private:

    /* Private methods */

    inline void next();


    /* Fields */

    typename std::vector<Node>::const_iterator it;


};


/**
 * @brief The range based iterator class for the graph
 */
template <class T>
class Graph<T>::RangeBasedNodeIterator {

public:

    inline RangeBasedNodeIterator(const Graph<T>* graph) :
        graph(graph) {}

    inline NodeIterator begin();
    inline NodeIterator end();

private:

    const Graph<T>* graph;

};

}


#include "graph_nodeiterator.cpp"

#endif // CG3_GRAPH_NODEITERATOR_H

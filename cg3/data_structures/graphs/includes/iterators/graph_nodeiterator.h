#ifndef CG3_GRAPH_NODEITERATOR_H
#define CG3_GRAPH_NODEITERATOR_H

#include <iterator>
#include <vector>

#include "../../graph.h"

namespace cg3 {

/**
 * @brief The iterator of a graph
 */
template <class T>
class Graph<T>::NodeIterator :
        public std::iterator<std::bidirectional_iterator_tag, T>
{

    friend class Graph<T>;

private:

    /* Constructors */

    inline NodeIterator(Graph<T>* graph, Graph<T>::Node* node, unsigned int pos) :
        graph(graph), node(node), pos(pos) {}

public:

    /* Iterator operators */

    inline bool operator == (const NodeIterator& otherIterator) const;
    inline bool operator != (const NodeIterator& otherIterator) const;

    inline NodeIterator operator ++ ();
    inline NodeIterator operator ++ (int);
    inline NodeIterator operator -- ();
    inline NodeIterator operator -- (int);

    inline const T& operator *() const;

private:

    /* Protected methods */

    inline void next();
    inline void prev();


    /* Fields */

    Graph<T>* graph;
    Graph<T>::Node* node;
    unsigned int pos;

};


/**
 * @brief The range based iterator class for the graph
 */
template <class T>
class Graph<T>::RangeBasedNodeIterator {

public:

    inline RangeBasedNodeIterator(Graph<T>* graph);

    inline NodeIterator begin();
    inline NodeIterator end();

private:

    Graph<T>* graph;

};

}


#include "graph_nodeiterator.tpp"

#endif // CG3_GRAPH_NODEITERATOR_H

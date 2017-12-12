#ifndef CG3_GRAPH_NODEITERATOR_H
#define CG3_GRAPH_NODEITERATOR_H

#include "graph_genericnodeiterator.h"

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

private:

    /* Constructors */

    inline NodeIterator(Graph<T>* graph, Graph<T>::Node* node, unsigned int pos) :
        Graph<T>::GenericNodeIterator(graph, node),
        pos(pos) {}

public:

    /* Iterator operators */

    inline bool operator == (const NodeIterator& otherIterator) const;
    inline bool operator != (const NodeIterator& otherIterator) const;

    inline NodeIterator operator ++ ();
    inline NodeIterator operator ++ (int);

    inline const T& operator *() const;

private:

    /* Protected methods */

    inline void next();


    /* Fields */

    unsigned int pos;

};


/**
 * @brief The range based iterator class for the graph
 */
template <class T>
class Graph<T>::RangeBasedNodeIterator {

public:

    inline RangeBasedNodeIterator(Graph<T>* graph) :
        graph(graph) {}

    inline NodeIterator begin();
    inline NodeIterator end();

private:

    Graph<T>* graph;

};

}


#include "graph_nodeiterator.tpp"

#endif // CG3_GRAPH_NODEITERATOR_H

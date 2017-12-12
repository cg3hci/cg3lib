#ifndef CG3_GRAPH_ADJACENTNODEITERATOR_H
#define CG3_GRAPH_ADJACENTNODEITERATOR_H

#include "graph_genericnodeiterator.h"

namespace cg3 {

/**
 * @brief The iterator of a graph
 */
template <class T>
class Graph<T>::AdjacentNodeIterator :
        public Graph<T>::GenericNodeIterator,
        public std::iterator<std::forward_iterator_tag, T>
{

    friend class Graph<T>;

private:

    /* Constructors */

    inline AdjacentNodeIterator(Graph<T>* graph,
                                Graph<T>::Node* targetNode,
                                Graph<T>::Node* node) :
        Graph<T>::GenericNodeIterator(graph, node),
        targetNode(targetNode) {}

public:

    /* Iterator operators */

    inline bool operator == (const AdjacentNodeIterator& otherIterator) const;
    inline bool operator != (const AdjacentNodeIterator& otherIterator) const;

    inline AdjacentNodeIterator operator ++ ();
    inline AdjacentNodeIterator operator ++ (int);

    inline const T& operator *() const;

private:

    /* Protected methods */

    inline void next();


    /* Fields */

    Graph<T>::Node* targetNode;

};


/**
 * @brief The range based iterator class for the graph
 */
template <class T>
class Graph<T>::RangeBasedAdjacentNodeIterator {

public:

    inline RangeBasedAdjacentNodeIterator(
            Graph<T>* graph,
            Graph<T>::Node* node) :
        graph(graph), node(node) {}

    inline AdjacentNodeIterator begin();
    inline AdjacentNodeIterator end();

private:

    Graph<T>* graph;
    Graph<T>::Node* node;

};

}


#include "graph_adjacentnodeiterator.tpp"

#endif // CG3_GRAPH_ADJACENTNODEITERATOR_H

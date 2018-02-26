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

    inline AdjacentNodeIterator(
            Graph<T>* graph);

    inline AdjacentNodeIterator(
            Graph<T>* graph,
            Node* targetNode,
            std::unordered_map<size_t, double>::iterator it);
public:

    /* Iterator operators */

    inline bool operator == (const AdjacentNodeIterator& otherIterator) const;
    inline bool operator != (const AdjacentNodeIterator& otherIterator) const;

    inline AdjacentNodeIterator operator ++ ();
    inline AdjacentNodeIterator operator ++ (int);

    inline const T& operator *() const;

private:

    /* Private methods */

    inline void next();


    /* Fields */

    Node* targetNode;
    std::unordered_map<size_t, double>::iterator it;

};


/**
 * @brief The range based iterator class for the graph
 */
template <class T>
class Graph<T>::RangeBasedAdjacentNodeIterator {

public:

    inline RangeBasedAdjacentNodeIterator(
            Graph<T>* graph,
            typename Graph<T>::Node* node) :
        graph(graph), node(node) {}

    inline AdjacentNodeIterator begin();
    inline AdjacentNodeIterator end();

private:

    Graph<T>* graph;
    typename Graph<T>::Node* node;

};

}


#include "graph_adjacentnodeiterator.tpp"

#endif // CG3_GRAPH_ADJACENTNODEITERATOR_H

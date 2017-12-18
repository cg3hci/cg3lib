#ifndef CG3_GRAPH_NODE_H
#define CG3_GRAPH_NODE_H

#include <unordered_map>

namespace cg3 {

/**
 * @brief The node of a graph
 */
template <class T>
class Graph<T>::Node
{
    friend class Graph<T>;
    friend class Graph<T>::NodeIterator;

private:

    /* Constructors */

    inline Node(const T& value, const size_t id);


    /* Fields */

    size_t id;

    T value;

    std::unordered_map<size_t, double> adjacentNodes;

};

}

#include "graph_node.tpp"

#endif // CG3_GRAPH_NODE_H

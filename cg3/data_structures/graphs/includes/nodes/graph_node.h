#ifndef CG3_GRAPH_NODE_H
#define CG3_GRAPH_NODE_H

#include <unordered_map>

#include <cg3/io/serialize.h>

namespace cg3 {

/**
 * @brief The node of a graph
 */
template <class T>
class Graph<T>::Node : public SerializableObject
{
public:
    friend class Graph<T>;
    friend class Graph<T>::NodeIterator;

    inline Node();

    // SerializableObject interface
    void serialize(std::ofstream& binaryFile) const;
    void deserialize(std::ifstream& binaryFile);

private:

    /* Constructors */

    inline Node(const T& value, const size_t id);


    /* Fields */

    size_t id;

    T value;

    std::unordered_map<size_t, double> adjacentNodes;
};

}

#include "graph_node.cpp"

#endif // CG3_GRAPH_NODE_H

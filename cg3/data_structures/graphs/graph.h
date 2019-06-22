/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */
#ifndef CG3_GRAPH_H
#define CG3_GRAPH_H

#include <vector>
#include <set>
#include <map>
#include <unordered_map>

#include <limits>

#include <cg3/io/serialize.h>

#define NUMBER_DELETE_FOR_RECOMPACT 10000

namespace cg3 {

/**
 * @brief Class representing a weighted graph (directed or undirected)
 *
 * It can be specified if it is directed or undirected: directed is
 * the default one.
 *
 * Weights are optional: if not specified, we assume that every edge has
 * cost 0. We also assume that if there is not an edge between two nodes,
 * then the cost is MAX_WEIGHT (std::numeric_limits<double>::max()/2).
 *
 * Note that operations with iterators are usually faster, since the operations
 * that use values have to perform finding the id of the node (a map is used).
 *
 * The graph is implemented in order to have the best time complexity but it
 * is not optimal in memory if we perform delete operations. Indeed the removal
 * of the node in the graph is implemented with a lazy approach. Every time
 * we delete a node, we do not remove an entry from the node vector and from the
 * node adjacency list: we just set a flag.
 * Use recompact() method to clear the deleted node references.
 *
 * Recompact operation is automatically done after a defined number of deleted nodes
 * (to avoid memory exhaustion and optimize its usage). This number is set to 10000.
 *
 */
template <class T>
class Graph : public SerializableObject
{
protected:

    /* Node class */

    class Node;


public:

    enum GraphType { DIRECTED, UNDIRECTED };
    enum GraphMapping { MAPPED, INDEXED };

    /* Public const */

    static constexpr double MAX_WEIGHT = std::numeric_limits<double>::max()/2;


    /* Iterator classes */

    class GenericNodeIterator;

    class NodeIterator;
    friend class NodeIterator;
    class RangeBasedNodeIterator;

    class AdjacentIterator;
    friend class AdjacentIterator;
    class RangeBasedAdjacentIterator;

    class EdgeIterator;
    friend class EdgeIterator;
    class RangeBasedEdgeIterator;

    //The default iterator is the NodeIterator
    typedef NodeIterator iterator;


    /* Constructors / destructor */

    explicit Graph(const GraphType& type = GraphType::DIRECTED, const GraphMapping& mapping = GraphMapping::MAPPED);


    /* Public methods with values */

    NodeIterator addNode(const T& o);
    bool deleteNode(const T& o);

    NodeIterator findNode(const T& o) const;

    bool addEdge(const T& o1, const T& o2, const double weight = 0);
    bool deleteEdge(const T& o1, const T& o2);
    bool isAdjacent(const T& o1, const T& o2) const;

    double getWeight(const T& o1, const T& o2) const;
    void setWeight(const T& o1, const T& o2, const double weight);


    /* Public methods with iterators */

    bool deleteNode(GenericNodeIterator it);

    void addEdge(GenericNodeIterator it1, GenericNodeIterator it2, const double weight = 0);
    void deleteEdge(GenericNodeIterator it1, const GenericNodeIterator it2);
    bool isAdjacent(const GenericNodeIterator it1, const GenericNodeIterator it2) const;

    double getWeight(const GenericNodeIterator it1, const GenericNodeIterator it2) const;
    void setWeight(GenericNodeIterator it1, GenericNodeIterator it2, const double weight);


    /* Utility methods */

    size_t getId(const GenericNodeIterator iterator) const;
    NodeIterator getNode(const size_t id) const;

    size_t numNodes() const;
    size_t numEdges() const;
    void clear();
    void recompact();

    // SerializableObject interface
    void serialize(std::ofstream& binaryFile) const;
    void deserialize(std::ifstream& binaryFile);


    /* Iterators */

    NodeIterator begin() const;
    NodeIterator end() const;

    NodeIterator nodeBegin() const;
    NodeIterator nodeEnd() const;
    RangeBasedNodeIterator nodeIterator() const;

    AdjacentIterator adjacentBegin(NodeIterator nodeIt) const;
    AdjacentIterator adjacentEnd(NodeIterator nodeIt) const;
    RangeBasedAdjacentIterator adjacentIterator(NodeIterator nodeIt) const;

    AdjacentIterator adjacentBegin(AdjacentIterator nodeIt) const;
    AdjacentIterator adjacentEnd(AdjacentIterator nodeIt) const;
    RangeBasedAdjacentIterator adjacentIterator(AdjacentIterator nodeIt) const;

    AdjacentIterator adjacentBegin(const T& o) const;
    AdjacentIterator adjacentEnd(const T& o) const;
    RangeBasedAdjacentIterator adjacentIterator(const T& o) const;

    EdgeIterator edgeBegin() const;
    EdgeIterator edgeEnd() const;
    RangeBasedEdgeIterator edgeIterator() const;


protected:

    /* Protected functions for iterators */

    inline typename std::vector<Node>::const_iterator getFirstValidIteratorNode(
            typename std::vector<Node>::const_iterator it) const;

    inline std::unordered_map<size_t, double>::const_iterator getFirstValidIteratorAdjacent(
            NodeIterator nodeIt,
            std::unordered_map<size_t, double>::const_iterator it) const;

    void getFirstValidIteratorEdge(
            NodeIterator nodeIt,
            AdjacentIterator adjIt,
            NodeIterator& newNodeIt,
            AdjacentIterator& newAdjIt) const;


    /* Helpers */

    inline long long int findNodeHelper(const T& o) const;
    inline void addEdgeHelper(const size_t& id1, const size_t& id2, const double weight);
    inline void deleteEdgeHelper(const size_t& id1, const size_t& id2);
    inline bool isAdjacentHelper(const size_t& id1, const size_t& id2) const;

    inline double getWeightHelper(const size_t& id1, const size_t& id2) const;
    inline void setWeightHelper(const size_t& id1, const size_t& id2, const double weight);


    /* Protected fields */

    GraphType type; //Type of the graph (directed or undirected)
    GraphMapping mapping; //Type of mapping of the graph (mapped or indexed)

    std::vector<Node> nodes; //Vector of nodes
    std::map<T, size_t> map; //Map to find a node with a value

    std::vector<bool> isDeleted; //Delete flag
    int nDeletedNodes; //Number of deleted nodes
};


}

#include "includes/nodes/graph_node.h"

#include "includes/iterators/graph_genericnodeiterator.h"
#include "includes/iterators/graph_nodeiterator.h"
#include "includes/iterators/graph_adjacentiterator.h"
#include "includes/iterators/graph_edgeiterator.h"

#include "graph.cpp"

#endif // CG3_GRAPH_H

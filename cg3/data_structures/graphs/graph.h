/**
    @author Stefano Nuvoli
*/
#ifndef CG3_GRAPH_H
#define CG3_GRAPH_H

#include <vector>
#include <set>
#include <map>

#include <cfloat>

namespace cg3 {

enum GraphType { DIRECTED, UNDIRECTED };

/**
 * @brief Class representing a weighted graph
 *
 * It can be specified if it is directed or undirected: directed is
 * the default one.
 *
 * Weights are optional: if not specified, we assume that every edge has
 * cost 0. We also assume that if there is not an edge between two nodes,
 * then the cost is MAX_WEIGHT (DBL_MAX defined in <cfloat>).
 *
 * Note that operations with iterators are usually faster, since the
 * operation with the value has to perform a find operation in a map to get
 * the corresponding node.
 */
template <class T>
class Graph
{

private:

    /* Node class */

    class Node;


public:

    /* Public const */

    static constexpr double MAX_WEIGHT = DBL_MAX;


    /* Iterator classes */

    class GenericNodeIterator;

    class NodeIterator;
    friend class NodeIterator;
    class RangeBasedNodeIterator;

    class EdgeIterator;
    friend class EdgeIterator;
    class RangeBasedEdgeIterator;

    class AdjacentNodeIterator;
    friend class AdjacentNodeIterator;
    class RangeBasedAdjacentNodeIterator;


    /* Constructors / destructor */

    Graph(GraphType type = GraphType::DIRECTED);

    Graph(const Graph<T>& graph);
    Graph(Graph<T>&& graph);

    ~Graph();


    /* Public methods with values */

    NodeIterator addNode(const T& o);
    bool deleteNode(const T& o);
    NodeIterator findNode(const T& o);

    bool addEdge(const T& o1, const T& o2, const double weight = 0);
    bool deleteEdge(const T& o1, const T& o2);
    bool isAdjacent(const T& o1, const T& o2) const;

    double getWeight(const T& o1, const T& o2);
    void setWeight(const T& o1, const T& o2, const double weight);


    /* Public methods with iterators */

    bool deleteNode(GenericNodeIterator n);

    void addEdge(GenericNodeIterator n1, GenericNodeIterator n2, const double weight = 0);
    void deleteEdge(GenericNodeIterator n1, const GenericNodeIterator n2);
    bool isAdjacent(const GenericNodeIterator n1, const GenericNodeIterator n2) const;

    double getWeight(const GenericNodeIterator o1, const GenericNodeIterator o2);
    void setWeight(GenericNodeIterator o1, GenericNodeIterator o2, const double weight);


    /* Clear methods */

    void clear();



    /* Iterators */

    NodeIterator nodeIteratorBegin();
    NodeIterator nodeIteratorEnd();
    RangeBasedNodeIterator nodeIterator();

    EdgeIterator edgeIteratorBegin();
    EdgeIterator edgeIteratorEnd();
    RangeBasedEdgeIterator edgeIterator();

    AdjacentNodeIterator adjacentNodeIteratorBegin(const T& o);
    AdjacentNodeIterator adjacentNodeIteratorBegin(NodeIterator node);
    AdjacentNodeIterator adjacentNodeIteratorEnd(const T& o);
    AdjacentNodeIterator adjacentNodeIteratorEnd(NodeIterator node);
    RangeBasedAdjacentNodeIterator adjacentNodeIterator(const T& o);
    RangeBasedAdjacentNodeIterator adjacentNodeIterator(NodeIterator node);


    /* Swap function and assignment */

    inline Graph<T>& operator= (Graph<T> graph);
    inline void swap(Graph<T>& graph);

private:

    /* Private functions for iterators */

    inline AdjacentNodeIterator adjacentNodeIteratorBegin(Node* node);
    inline AdjacentNodeIterator adjacentNodeIteratorEnd(Node* node);


    /* Private functions */

    inline Node* findNodeHelper(const T& o) const;
    inline void addEdgeHelper(Node* n1, const Node* n2, const double weight);
    inline void deleteEdgeHelper(Node* n1, const Node* n2);
    inline bool isAdjacentHelper(const Node* n1, const Node* n2) const;

    inline double getWeightHelper(const Node* n1, const Node* n2) const;
    inline void setWeightHelper(Node* n1, const Node* n2, const double weight);


    /* Private fields */

    const GraphType type;

    std::vector<Node*> nodes;
    std::map<T, size_t> map;

};

template <class T>
void swap(Graph<T>& g1, Graph<T>& g2);

}

#include "includes/nodes/graph_node.h"

#include "includes/iterators/graph_genericnodeiterator.h"
#include "includes/iterators/graph_nodeiterator.h"
#include "includes/iterators/graph_edgeiterator.h"
#include "includes/iterators/graph_adjacentnodeiterator.h"

#include "graph.tpp"

#endif // CG3_GRAPH_H

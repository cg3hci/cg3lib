/**
    @author Stefano Nuvoli
*/
#ifndef CG3_GRAPH_H
#define CG3_GRAPH_H


#include <vector>
#include <set>
#include <map>

namespace cg3 {

enum GraphType { DIRECTED, UNDIRECTED };

/**
 * @brief Class representing a Graph
 *
 * It can be directed and undirected. Directed is the default one.
 *
 */
template <class T>
class Graph
{

private:

    /* Node class */

    class Node;

public:

    /* Iterator classes */

    class NodeIterator;
    friend class NodeIterator;
    class RangeBasedNodeIterator;

//    //TODO
//    class ArcIterator;
//    friend class ArcIterator;
//    class RangeBasedArcIterator;

//    //TODO
//    class AdjacentNodeIterator;
//    friend class AdjacentNodeIterator;
//    class RangeBasedAdjacentNodeIterator;


    /* Constructors / destructor */

    Graph(GraphType type = GraphType::DIRECTED);
    virtual ~Graph();


    /* Public methods with values */

    NodeIterator addNode(const T& o);
    bool deleteNode(const T& o);
    NodeIterator findNode(const T& o);

    bool addArc(const T& o1, const T& o2, const double weight = 0);
    bool deleteArc(const T& o1, const T& o2);
    bool isAdjacent(const T& o1, const T& o2) const;

    double getWeight(const T& o1, const T& o2);
    void setWeight(const T& o1, const T& o2, const double weight);


    /* Public methods with iterators */

    bool deleteNode(NodeIterator n);

    void addArc(NodeIterator n1, NodeIterator n2, const double weight = 0);
    void deleteArc(NodeIterator n1, NodeIterator n2);
    bool isAdjacent(const NodeIterator n1, const NodeIterator n2) const;

    double getWeight(const NodeIterator o1, const NodeIterator o2);
    void setWeight(NodeIterator o1, NodeIterator o2, const double weight);


    /* Iterators */

    NodeIterator nodeIteratorBegin();
    NodeIterator nodeIteratorEnd();

    RangeBasedNodeIterator nodeIterator();


private:

    /* Private functions */

    inline Node* findNodeHelper(const T& o) const;
    inline void addArcHelper(Node* n1, const Node* n2, const double weight);
    inline void deleteArcHelper(Node* n1, const Node* n2);
    inline bool isAdjacentHelper(const Node* n1, const Node* n2) const;

    inline double getWeightHelper(const Node* n1, const Node* n2) const;
    inline void setWeightHelper(Node* n1, const Node* n2, const double weight);


    /* Functions for iterators */

    inline Node* getNextNode(
            const unsigned int pos,
            unsigned int& newPos);

    inline Node* getPrevNode(
            const unsigned int pos,
            unsigned int& newPos);


    /* Private fields */

    const GraphType type;

    std::vector<Node*> nodes;
    std::map<T, unsigned int> map;
};

}

#include "includes/nodes/graph_node.h"
#include "includes/iterators/graph_nodeiterator.h"

#include "graph.tpp"

#endif // CG3_GRAPH_H

#ifndef CG3_BIPARTITE_GRAPH_H
#define CG3_BIPARTITE_GRAPH_H

#include <vector>
#include <map>
#include <assert.h>

#include "undirected_node.h"

namespace cg3 {

template <class T1, class T2>
class BipartiteGraph {
    public:
        BipartiteGraph();
        bool addLeftNode(const T1& info);
        bool addRightNode(const T2& info);
        bool existsLeftNode(const T1& lNode) const;
        bool existsRightNode(const T2& rNode) const;
        unsigned int sizeLeftNodes() const;
        unsigned int sizeRightNodes() const;
        unsigned int sizeAdjacencesLeftNode(const T1& lNode) const;
        unsigned int sizeAdjacencesRightNode(const T2 &rNode) const;
        bool deleteLeftNode(const T1& lNode);
        bool deleteRightNode(const T2& rNode);
        bool addArc(const T1& lNode, const T2 &rNode);
        bool deleteArc(const T1& lNode, const T2 &rNode);
        bool clearAdjacencesLeftNode(const T1 &lNode);
        bool clearAdjacencesRightNode(const T2 &rNode);
        bool modifyLeftNode(const T1 &old, const T1& newInfo);
        bool modifyRightNode(const T2 &old, const T2& newInfo);

        class AdjacentLeftNodeIterator;
        class AdjacentRightNodeIterator;

        class LeftNodeIterator;
        class RightNodeIterator;

        class AdjacentLeftNodeRangeBasedIterator;
        class AdjacentRightNodeRangeBasedIterator;

        class LeftNodeRangeBasedIterator;
        class RightNodeRangeBasedIterator;

        AdjacentLeftNodeIterator adjacentLeftNodeBegin(const T1 &lNode) const;
        AdjacentLeftNodeIterator adjacentLeftNodeEnd(const T1 &lNode) const;

        AdjacentRightNodeIterator adjacentRightNodeBegin(const T2 &rNode) const;
        AdjacentRightNodeIterator adjacentRightNodeEnd(const T2 &rNode) const;

        LeftNodeIterator leftNodeBegin() const;
        LeftNodeIterator leftNodeEnd() const;

        RightNodeIterator rightNodeBegin() const;
        RightNodeIterator rightNodeEnd() const;

        AdjacentLeftNodeRangeBasedIterator adjacentLeftNodeIterator(const T1& lNode) const;
        AdjacentRightNodeRangeBasedIterator adjacentRightNodeIterator(const T2& rNode) const;

        LeftNodeRangeBasedIterator leftNodeIterator() const;
        RightNodeRangeBasedIterator rightNodeIterator() const;

protected:
        int getIdLeftNode(const T1& uNode) const;
        int getIdRightNode(const T2& vNode) const;

        std::map<T1, unsigned int> mapL;
        std::map<T2, unsigned int> mapR;

        std::vector<graphs::UndirectedNode<T1> > nodesL;
        std::vector<graphs::UndirectedNode<T2> > nodesR;

        std::set<unsigned int> unusedLNodes;
        std::set<unsigned int> unusedRNodes;
};

}

#include "bipartite_graph_iterators.h"

#include "bipartite_graph.tpp"

#endif // BIPARTITE_GRAPH_H

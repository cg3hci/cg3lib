/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "bipartite_graph.h"

namespace cg3 {

/**
 * @brief BipartiteGraph<T1, T2>::BipartiteGraph
 * Default constructor. It creates an empty Bipartite Graph.
 */
template <class T1, class T2>
BipartiteGraph<T1, T2>::BipartiteGraph()
{
}

/**
 * @brief BipartiteGraph<T1, T2>::addLeftNode
 * Adds a new node on the left side of the graph.
 * @param[in] info: the value associated to the new node
 * @return true if the node is correctly added, false otherwise (if the node already exists)
 */
template <class T1, class T2>
bool BipartiteGraph<T1, T2>::addLeftNode(const T1& info)
{
    if (mapL.find(info) == mapL.end()){
        if (unusedLNodes.size() == 0){
            mapL[info] = (unsigned int)nodesL.size();
            nodesL.push_back(UndirectedNode<T1>(info));
        }
        else {
            unsigned int id = *(unusedLNodes.begin());
            unusedLNodes.erase(unusedLNodes.begin());
            mapL[info] = id;
            nodesL[id] = UndirectedNode<T1>(info);
        }
        return true;
    }
    else
        return false;
}

/**
 * @brief BipartiteGraph<T1, T2>::addRightNode
 * Adds a new node on the right side of the graph.
 * @param[in] info: the value associated to the new node
 * @return true if the node is correctly added, false otherwise (if the node already exists)
 */
template <class T1, class T2>
bool BipartiteGraph<T1, T2>::addRightNode(const T2& info)
{
    if (mapR.find(info) == mapR.end()){
        if (unusedRNodes.size() == 0){
            mapR[info] = (unsigned int)nodesR.size();
            nodesR.push_back(UndirectedNode<T2>(info));
        }
        else {
            unsigned int id = *(unusedRNodes.begin());
            unusedRNodes.erase(unusedRNodes.begin());
            mapR[info] = id;
            nodesR[id] = UndirectedNode<T2>(info);
        }
        return true;
    }
    else
        return false;
}

/**
 * @brief BipartiteGraph<T1, T2>::existsLeftNode
 * Checks if a node exists on the left side of the graph
 * @param lNode
 * @return true if the node exists
 */
template <class T1, class T2>
bool BipartiteGraph<T1, T2>::existsLeftNode(const T1& lNode) const
{
    return mapL.find(lNode) != mapL.end();
}

/**
 * @brief BipartiteGraph<T1, T2>::existsRightNode
 * Checks if a node exists on the right side of the graph
 * @param rNode
 * @return true if the node exists
 */
template <class T1, class T2>
bool BipartiteGraph<T1, T2>::existsRightNode(const T2& rNode) const
{
    return mapR.find(rNode) != mapR.end();
}

/**
 * @brief BipartiteGraph<T1, T2>::sizeLeftNodes
 * @return the number of nodes on the left side of the graph
 */
template <class T1, class T2>
unsigned int BipartiteGraph<T1, T2>::sizeLeftNodes() const
{
    return (unsigned int)(nodesL.size() - unusedLNodes.size());
}

/**
 * @brief BipartiteGraph<T1, T2>::sizeRightNodes
 * @return the number of nodes on the right side of the graph
 */
template <class T1, class T2>
unsigned int BipartiteGraph<T1, T2>::sizeRightNodes() const
{
    return (unsigned int)(nodesR.size() - unusedRNodes.size());
}

/**
 * @brief BipartiteGraph<T1, T2>::sizeAdjacencesLeftNode
 * @param lNode
 * @return the number of adjacent nodes to lNode
 */
template<class T1, class T2>
unsigned int BipartiteGraph<T1, T2>::sizeAdjacencesLeftNode(
        const T1& lNode) const
{
    int uid = getIdLeftNode(lNode);
    return nodesL[uid].sizeAdjacentNodes();
}

/**
 * @brief BipartiteGraph<T1, T2>::sizeAdjacencesRightNode
 * @param rNode
 * @return the number of adjacent nodes to rNode
 */
template<class T1, class T2>
unsigned int BipartiteGraph<T1, T2>::sizeAdjacencesRightNode(
        const T2& rNode) const
{
    int vid = getIdRightNode(rNode);
    return nodesR[vid].sizeAdjacentNodes();
}

/**
 * @brief BipartiteGraph<T1, T2>::deleteLeftNode
 * removes lNode and all its arcs from the graph
 * @param lNode
 * @return true if the node is successfully deleted
 */
template <class T1, class T2>
bool BipartiteGraph<T1, T2>::deleteLeftNode(const T1& lNode)
{
    if (clearAdjacencesLeftNode(lNode)){
        unusedLNodes.insert(mapL[lNode]);
        mapL.erase(lNode);
        return true;
    }
    else
        return false;

}

/**
 * @brief BipartiteGraph<T1, T2>::deleteRightNode
 * removes rNode and all its arcs from the graph
 * @param rNode
 * @return true if the node is successfully deleted
 */
template<class T1, class T2>
bool BipartiteGraph<T1, T2>::deleteRightNode(const T2& rNode)
{
    if (clearAdjacencesRightNode(rNode)){
        unusedRNodes.insert(mapR[rNode]);
        mapR.erase(rNode);
        return true;
    }
    else
        return false;
}

/**
 * @brief BipartiteGraph<T1, T2>::addArc
 * creates an arc between lNode and rNode
 * @param lNode
 * @param rNode
 * @return true if the arc is successfully created (both nodes exists in the graph)
 */
template <class T1, class T2>
bool BipartiteGraph<T1, T2>::addArc(const T1& lNode, const T2& rNode)
{
    try {
        int uid = getIdLeftNode(lNode);
        int vid = getIdRightNode(rNode);
        assert((unsigned int)uid < nodesL.size());
        assert((unsigned int)vid < nodesR.size());
        nodesL[uid].addAdjacent(vid);
        nodesR[vid].addAdjacent(uid);
        return true;
    }
    catch(...){
        return false;
    }
}

/**
 * @brief BipartiteGraph<T1, T2>::deleteArc
 * removes the arc between lNode and rNode
 * @param lNode
 * @param rNode
 * @return true if the arc is successfully deleted (both nodes and the arc exists in the graph)
 */
template<class T1, class T2>
bool BipartiteGraph<T1, T2>::deleteArc(const T1& lNode, const T2& rNode)
{
    try {
        int uid = getIdLeftNode(lNode);
        int vid = getIdRightNode(rNode);
        assert((unsigned int)uid < nodesL.size());
        assert((unsigned int)vid < nodesR.size());
        nodesL[uid].deleteAdjacent(vid);
        nodesR[vid].deleteAdjacent(uid);
        return true;
    }
    catch(...){
        return false;
    }
}

/**
 * @brief BipartiteGraph<T1, T2>::clearAdjacencesLeftNode
 * removes all the arcs connected to lNode (lNode won't have adjacent nodes)
 * @param lNode
 * @return true if all the arcs are successfully removes
 */
template<class T1, class T2>
bool BipartiteGraph<T1, T2>::clearAdjacencesLeftNode(const T1& lNode)
{
    try {
        int uid = getIdLeftNode(lNode);
        for (unsigned int adj : nodesL[uid]){
            nodesR[adj].deleteAdjacent(uid);
        }
        nodesL[uid].clearAdjacentNodes();
        return true;
    }
    catch(...){
        return false;
    }
}

/**
 * @brief BipartiteGraph<T1, T2>::clearAdjacencesLeftNode
 * removes all the arcs connected to rNode (lNode won't have adjacent nodes)
 * @param rNode
 * @return true if all the arcs are successfully removes
 */
template<class T1, class T2>
bool BipartiteGraph<T1, T2>::clearAdjacencesRightNode(const T2& rNode)
{
    try {
        int vid = getIdRightNode(rNode);
        for (unsigned int adj : nodesR[vid]){
            nodesL[adj].deleteAdjacent(vid);
        }
        nodesR[vid].clearAdjacentNodes();
        return true;
    }
    catch(...){
        return false;
    }
}

/**
 * @brief BipartiteGraph<T1, T2>::modifyLeftNode
 * modifies the key of an lNode
 * @param old
 * @param newInfo
 * @return true if the key of the node is successfully modified
 */
template<class T1, class T2>
bool BipartiteGraph<T1, T2>::modifyLeftNode(const T1& old, const T1& newInfo)
{
    try {
        int uid = getIdLeftNode(old);
        nodesL[uid] = cg3::UndirectedNode<T1>(newInfo);
        mapL.erase(old);
        mapL[newInfo] = uid;
        return true;
    }
    catch(...){
        return false;
    }
}

/**
 * @brief BipartiteGraph<T1, T2>::modifyRightNode
 * modifies the key of a rNode
 * @param old
 * @param newInfo
 * @return true if the key of the node is successfully modified
 */
template<class T1, class T2>
bool BipartiteGraph<T1, T2>::modifyRightNode(const T2& old, const T2& newInfo)
{
    try {
        int vid = getIdRightNode(old);
        nodesR[vid] = cg3::UndirectedNode<T2>(newInfo);
        mapR.erase(old);
        mapR[newInfo] = vid;
        return true;
    }
    catch(...){
        return false;
    }
}

template<class T1, class T2>
void BipartiteGraph<T1, T2>::serialize(std::ofstream &binaryFile) const
{
    cg3::serializeObjectAttributes(
                "cg3BipartiteGraph",
                binaryFile,
                mapL,
                mapR,
                nodesL,
                nodesR,
                unusedLNodes,
                unusedRNodes);
}

template<class T1, class T2>
void BipartiteGraph<T1, T2>::deserialize(std::ifstream &binaryFile)
{
    cg3::deserializeObjectAttributes(
                "cg3BipartiteGraph",
                binaryFile,
                mapL,
                mapR,
                nodesL,
                nodesR,
                unusedLNodes,
                unusedRNodes);
}

template<class T1, class T2>
typename BipartiteGraph<T1, T2>::AdjacentLeftNodeIterator BipartiteGraph<T1, T2>::adjacentLeftNodeBegin(
        const T1& lNode) const
{
    int uid = getIdLeftNode(lNode);
    return AdjacentLeftNodeIterator(nodesL[uid].begin(), *this);
}

template<class T1, class T2>
typename BipartiteGraph<T1, T2>::AdjacentLeftNodeIterator BipartiteGraph<T1, T2>::adjacentLeftNodeEnd(
        const T1& lNode) const
{
    int uid = getIdLeftNode(lNode);
    return AdjacentLeftNodeIterator(nodesL[uid].end(), *this);
}

template<class T1, class T2>
typename BipartiteGraph<T1, T2>::AdjacentRightNodeIterator BipartiteGraph<T1, T2>::adjacentRightNodeBegin(
        const T2& rNode) const
{
    int vid = getIdRightNode(rNode);
    return AdjacentRightNodeIterator(nodesR[vid].begin(), *this);

}

template<class T1, class T2>
typename BipartiteGraph<T1, T2>::AdjacentRightNodeIterator BipartiteGraph<T1, T2>::adjacentRightNodeEnd(
        const T2& rNode) const
{
    int vid = getIdRightNode(rNode);
    return AdjacentRightNodeIterator(nodesR[vid].end(), *this);
}

template<class T1, class T2>
typename BipartiteGraph<T1, T2>::LeftNodeIterator BipartiteGraph<T1, T2>::leftNodeBegin() const
{
    return LeftNodeIterator(nodesL.begin(), *this);
}

template<class T1, class T2>
typename BipartiteGraph<T1, T2>::LeftNodeIterator BipartiteGraph<T1, T2>::leftNodeEnd() const
{
    return LeftNodeIterator(nodesL.end(), *this);
}

template<class T1, class T2>
typename BipartiteGraph<T1, T2>::RightNodeIterator BipartiteGraph<T1, T2>::rightNodeBegin() const
{
    return RightNodeIterator(nodesR.begin(), *this);
}

template<class T1, class T2>
typename BipartiteGraph<T1, T2>::RightNodeIterator BipartiteGraph<T1, T2>::rightNodeEnd() const
{
    return RightNodeIterator(nodesR.end(), *this);
}

template<class T1, class T2>
typename BipartiteGraph<T1, T2>::AdjacentLeftNodeRangeBasedIterator BipartiteGraph<T1, T2>::adjacentLeftNodeIterator(const T1& lNode) const
{
    return AdjacentLeftNodeRangeBasedIterator(this, lNode);
}

template<class T1, class T2>
typename BipartiteGraph<T1, T2>::AdjacentRightNodeRangeBasedIterator BipartiteGraph<T1, T2>::adjacentRightNodeIterator(const T2& rNode) const
{
    return AdjacentRightNodeRangeBasedIterator(this, rNode);
}

template<class T1, class T2>
typename BipartiteGraph<T1, T2>::LeftNodeRangeBasedIterator BipartiteGraph<T1, T2>::leftNodeIterator() const
{
    return LeftNodeRangeBasedIterator(this);
}

template<class T1, class T2>
typename BipartiteGraph<T1, T2>::RightNodeRangeBasedIterator BipartiteGraph<T1, T2>::rightNodeIterator() const
{
    return RightNodeRangeBasedIterator(this);
}

template <class T1, class T2>
int BipartiteGraph<T1, T2>::getIdLeftNode(const T1& uNode) const
{
    return mapL.at(uNode);
}

template <class T1, class T2>
int BipartiteGraph<T1, T2>::getIdRightNode(const T2& vNode) const
{
    return mapR.at(vNode);
}

} //namespace cg3

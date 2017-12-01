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
        bool addUNode(const T1& info);
        bool addVNode(const T2& info);
        bool existsUNode(const T1& uNode) const;
        bool existsVNode(const T2& vNode) const;
        unsigned int sizeU() const;
        unsigned int sizeV() const;
        int sizeAdjacencesUNode(const T1& uNode) const;
        int sizeAdjacencesVNode(const T2 &vNode) const;
        bool deleteUNode(const T1& uNode);
        bool deleteVNode(const T2& vNode);
        bool addArc(const T1& uNode, const T2 &vNode);
        bool deleteArc(const T1& uNode, const T2 &vNode);
        bool clearAdjacencesUNode(const T1 &uNode);
        bool clearAdjacencesVNode(const T2 &vNode);
        bool modifyUNode(const T1 &old, const T1& newInfo);
        bool modifyVNode(const T2 &old, const T2& newInfo);

        class AdjacentUNodeIterator;
        class AdjacentVNodeIterator;

        class UNodeIterator;
        class VNodeIterator;

        class AdjacentUNodeRangeBasedIterator;
        class AdjacentVNodeRangeBasedIterator;

        class UNodeRangeBasedIterator;
        class VNodeRangeBasedIterator;

        AdjacentUNodeIterator adjacentUNodeBegin(const T1 &uNode) const;
        AdjacentUNodeIterator adjacentUNodeEnd(const T1 &uNode) const;

        AdjacentVNodeIterator adjacentVNodeBegin(const T2 &vNode) const;
        AdjacentVNodeIterator adjacentVNodeEnd(const T2 &vNode) const;

        UNodeIterator uNodeBegin() const;
        UNodeIterator uNodeEnd() const;

        VNodeIterator vNodeBegin() const;
        VNodeIterator vNodeEnd() const;

        AdjacentUNodeRangeBasedIterator adjacentUNodeIterator(const T1& uNode) const;
        AdjacentVNodeRangeBasedIterator adjacentVNodeIterator(const T2& vNode) const;

        UNodeRangeBasedIterator uNodeIterator() const;
        VNodeRangeBasedIterator vNodeIterator() const;

    protected:
        int getIdU(const T1& uNode) const;
        int getIdV(const T2& vNode) const;

        std::map<T1, unsigned int> mapU;
        std::map<T2, unsigned int> mapV;

        std::vector<graphs::UndirectedNode<T1> > nodesU;
        std::vector<graphs::UndirectedNode<T2> > nodesV;

        std::set<unsigned int> unusedUNodes;
        std::set<unsigned int> unusedVNodes;
};

}

#include "bipartite_graph_iterators.h"

namespace cg3 {

template <class T1, class T2>
BipartiteGraph<T1, T2>::BipartiteGraph() {
}

template <class T1, class T2>
bool BipartiteGraph<T1, T2>::addUNode(const T1& info) {
    if (mapU.find(info) == mapU.end()){
        if (unusedUNodes.size() == 0){
            mapU[info] = nodesU.size();
            nodesU.push_back(graphs::UndirectedNode<T1>(info));
        }
        else {
            unsigned int id = *(unusedUNodes.begin());
            unusedUNodes.erase(unusedUNodes.begin());
            mapU[info] = id;
            nodesU[id] = graphs::UndirectedNode<T1>(info);
        }
        return true;
    }
    else
        return false;
}

template <class T1, class T2>
bool BipartiteGraph<T1, T2>::addVNode(const T2& info) {
    if (mapV.find(info) == mapV.end()){
        if (unusedVNodes.size() == 0){
            mapV[info] = nodesV.size();
            nodesV.push_back(graphs::UndirectedNode<T2>(info));
        }
        else {
            unsigned int id = *(unusedVNodes.begin());
            unusedVNodes.erase(unusedVNodes.begin());
            mapV[info] = id;
            nodesV[id] = graphs::UndirectedNode<T2>(info);
        }
        return true;
    }
    else
        return false;
}

template <class T1, class T2>
bool BipartiteGraph<T1, T2>::existsUNode(const T1& uNode) const {
    return mapU.find(uNode) != mapU.end();
}

template <class T1, class T2>
bool BipartiteGraph<T1, T2>::existsVNode(const T2& vNode) const {
    return mapV.find(vNode) != mapV.end();
}

template <class T1, class T2>
unsigned int BipartiteGraph<T1, T2>::sizeU() const {
    return nodesU.size() - unusedUNodes.size();
}

template <class T1, class T2>
unsigned int BipartiteGraph<T1, T2>::sizeV() const {
    return nodesV.size() - unusedVNodes.size();
}

template<class T1, class T2>
int BipartiteGraph<T1, T2>::sizeAdjacencesUNode(const T1& uNode) const {
    int uid = getIdU(uNode);
    return nodesU[uid].sizeAdjacentNodes();
}

template<class T1, class T2>
int BipartiteGraph<T1, T2>::sizeAdjacencesVNode(const T2& vNode) const {
    int vid = getIdV(vNode);
    return nodesV[vid].sizeAdjacentNodes();
}

template <class T1, class T2>
bool BipartiteGraph<T1, T2>::deleteUNode(const T1& uNode) {
    if (clearAdjacencesUNode(uNode)){
        unusedUNodes.insert(mapU[uNode]);
        mapU.erase(uNode);
        return true;
    }
    else
        return false;

}

template<class T1, class T2>
bool BipartiteGraph<T1, T2>::deleteVNode(const T2& vNode) {
    if (clearAdjacencesVNode(vNode)){
        unusedVNodes.insert(mapV[vNode]);
        mapV.erase(vNode);
        return true;
    }
    else
        return false;
}

template <class T1, class T2>
bool BipartiteGraph<T1, T2>::addArc(const T1& uNode, const T2& vNode) {
    try {
        int uid = getIdU(uNode);
        int vid = getIdV(vNode);
        assert((unsigned int)uid < nodesU.size());
        assert((unsigned int)vid < nodesV.size());
        nodesU[uid].addAdjacent(vid);
        nodesV[vid].addAdjacent(uid);
        return true;
    }
    catch(...){
        return false;
    }
}

template<class T1, class T2>
bool BipartiteGraph<T1, T2>::deleteArc(const T1& uNode, const T2& vNode) {
    try {
        int uid = getIdU(uNode);
        int vid = getIdV(vNode);
        assert((unsigned int)uid < nodesU.size());
        assert((unsigned int)vid < nodesV.size());
        nodesU[uid].deleteAdjacent(vid);
        nodesV[vid].deleteAdjacent(uid);
        return true;
    }
    catch(...){
        return false;
    }
}

template<class T1, class T2>
bool BipartiteGraph<T1, T2>::clearAdjacencesUNode(const T1& uNode) {
    try {
        int uid = getIdU(uNode);
        for (unsigned int adj : nodesU[uid]){
            nodesV[adj].deleteAdjacent(uid);
        }
        nodesU[uid].clearAdjacentNodes();
        return true;
    }
    catch(...){
        return false;
    }
}

template<class T1, class T2>
bool BipartiteGraph<T1, T2>::clearAdjacencesVNode(const T2& vNode) {
    try {
        int vid = getIdV(vNode);
        for (unsigned int adj : nodesV[vid]){
            nodesU[adj].deleteAdjacent(vid);
        }
        nodesV[vid].clearAdjacentNodes();
        return true;
    }
    catch(...){
        return false;
    }
}

template<class T1, class T2>
bool BipartiteGraph<T1, T2>::modifyUNode(const T1& old, const T1& newInfo) {
    try {
        int uid = getIdU(old);
        nodesU[uid] = cg3::graphs::UndirectedNode<T1>(newInfo);
        mapU.erase(old);
        mapU[newInfo] = uid;
        return true;
    }
    catch(...){
        return false;
    }
}

template<class T1, class T2>
bool BipartiteGraph<T1, T2>::modifyVNode(const T2& old, const T2& newInfo) {
    try {
        int vid = getIdV(old);
        nodesV[vid] = cg3::graphs::UndirectedNode<T2>(newInfo);
        mapV.erase(old);
        mapV[newInfo] = vid;
        return true;
    }
    catch(...){
        return false;
    }
}

template<class T1, class T2>
typename BipartiteGraph<T1, T2>::AdjacentUNodeIterator BipartiteGraph<T1, T2>::adjacentUNodeBegin(const T1& uNode) const{
    int uid = getIdU(uNode);
    return AdjacentUNodeIterator(nodesU[uid].begin(), *this);
}

template<class T1, class T2>
typename BipartiteGraph<T1, T2>::AdjacentUNodeIterator BipartiteGraph<T1, T2>::adjacentUNodeEnd(const T1& uNode) const {
    int uid = getIdU(uNode);
    return AdjacentUNodeIterator(nodesU[uid].end(), *this);
}

template<class T1, class T2>
typename BipartiteGraph<T1, T2>::AdjacentVNodeIterator BipartiteGraph<T1, T2>::adjacentVNodeBegin(const T2& vNode) const {
    int vid = getIdV(vNode);
    return AdjacentVNodeIterator(nodesV[vid].begin(), *this);

}

template<class T1, class T2>
typename BipartiteGraph<T1, T2>::AdjacentVNodeIterator BipartiteGraph<T1, T2>::adjacentVNodeEnd(const T2& vNode) const {
    int vid = getIdV(vNode);
    return AdjacentVNodeIterator(nodesV[vid].end(), *this);
}

template<class T1, class T2>
typename BipartiteGraph<T1, T2>::UNodeIterator BipartiteGraph<T1, T2>::uNodeBegin() const {
    return UNodeIterator(nodesU.begin(), *this);
}

template<class T1, class T2>
typename BipartiteGraph<T1, T2>::UNodeIterator BipartiteGraph<T1, T2>::uNodeEnd() const {
    return UNodeIterator(nodesU.end(), *this);
}

template<class T1, class T2>
typename BipartiteGraph<T1, T2>::VNodeIterator BipartiteGraph<T1, T2>::vNodeBegin() const {
    return VNodeIterator(nodesV.begin(), *this);
}

template<class T1, class T2>
typename BipartiteGraph<T1, T2>::VNodeIterator BipartiteGraph<T1, T2>::vNodeEnd() const {
    return VNodeIterator(nodesV.end(), *this);
}

template<class T1, class T2>
typename BipartiteGraph<T1, T2>::AdjacentUNodeRangeBasedIterator BipartiteGraph<T1, T2>::adjacentUNodeIterator(const T1& uNode) const {
    return AdjacentUNodeRangeBasedIterator(this, uNode);
}

template<class T1, class T2>
typename BipartiteGraph<T1, T2>::AdjacentVNodeRangeBasedIterator BipartiteGraph<T1, T2>::adjacentVNodeIterator(const T2& vNode) const {
    return AdjacentVNodeRangeBasedIterator(this, vNode);
}

template<class T1, class T2>
typename BipartiteGraph<T1, T2>::UNodeRangeBasedIterator BipartiteGraph<T1, T2>::uNodeIterator() const {
    return UNodeRangeBasedIterator(this);
}

template<class T1, class T2>
typename BipartiteGraph<T1, T2>::VNodeRangeBasedIterator BipartiteGraph<T1, T2>::vNodeIterator() const {
    return VNodeRangeBasedIterator(this);
}

template <class T1, class T2>
int BipartiteGraph<T1, T2>::getIdU(const T1& uNode) const{
    return mapU.at(uNode);
}

template <class T1, class T2>
int BipartiteGraph<T1, T2>::getIdV(const T2& vNode) const{
    return mapV.at(vNode);
}

}
#endif // BIPARTITE_GRAPH_H

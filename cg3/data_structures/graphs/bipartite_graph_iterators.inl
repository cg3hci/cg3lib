/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "bipartite_graph_iterators.h"

namespace cg3 {

//AdjacentLeftNodeIterator

template <class T1, class T2>
inline BipartiteGraph<T1, T2>::AdjacentLeftNodeIterator::AdjacentLeftNodeIterator() : g(nullptr) {
}

template <class T1, class T2>
inline const T2& BipartiteGraph<T1, T2>::AdjacentLeftNodeIterator::operator *() const {
    return g->nodesR[*pos].getInfo();
}

template <class T1, class T2>
inline bool BipartiteGraph<T1, T2>::AdjacentLeftNodeIterator::operator ==(const AdjacentLeftNodeIterator& otherIterator) const {
    return (g == otherIterator.g && pos == otherIterator.pos);
}

template <class T1, class T2>
inline bool BipartiteGraph<T1, T2>::AdjacentLeftNodeIterator::operator !=(const AdjacentLeftNodeIterator& otherIterator) const {
    return (g != otherIterator.g || pos != otherIterator.pos);
}

template <class T1, class T2>
inline typename BipartiteGraph<T1, T2>::AdjacentLeftNodeIterator BipartiteGraph<T1, T2>::AdjacentLeftNodeIterator::operator ++() {
    ++pos;
    return *this;
}

template <class T1, class T2>
inline typename BipartiteGraph<T1, T2>::AdjacentLeftNodeIterator BipartiteGraph<T1, T2>::AdjacentLeftNodeIterator::operator ++(int) {
    AdjacentLeftNodeIterator oldIt = *this;
    ++pos;
    return oldIt;
}

template <class T1, class T2>
inline BipartiteGraph<T1, T2>::AdjacentLeftNodeIterator::AdjacentLeftNodeIterator(std::unordered_set<unsigned int>::const_iterator it, const BipartiteGraph& g): g(&g), pos(it){
}

//AdjacentRightNodeIterator

template <class T1, class T2>
inline BipartiteGraph<T1, T2>::AdjacentRightNodeIterator::AdjacentRightNodeIterator() : g(nullptr) {
}

template <class T1, class T2>
inline const T1& BipartiteGraph<T1, T2>::AdjacentRightNodeIterator::operator *() const {
    return g->nodesL[*pos].getInfo();
}

template <class T1, class T2>
inline bool BipartiteGraph<T1, T2>::AdjacentRightNodeIterator::operator ==(const AdjacentRightNodeIterator& otherIterator) const {
    return (g == otherIterator.g && pos == otherIterator.pos);
}

template <class T1, class T2>
inline bool BipartiteGraph<T1, T2>::AdjacentRightNodeIterator::operator !=(const AdjacentRightNodeIterator& otherIterator) const {
    return (g != otherIterator.g || pos != otherIterator.pos);
}

template <class T1, class T2>
inline typename BipartiteGraph<T1, T2>::AdjacentRightNodeIterator BipartiteGraph<T1, T2>::AdjacentRightNodeIterator::operator ++() {
    ++pos;
    return *this;
}

template <class T1, class T2>
inline typename BipartiteGraph<T1, T2>::AdjacentRightNodeIterator BipartiteGraph<T1, T2>::AdjacentRightNodeIterator::operator ++(int) {
    AdjacentRightNodeIterator oldIt = *this;
    ++pos;
    return oldIt;
}

template <class T1, class T2>
inline BipartiteGraph<T1, T2>::AdjacentRightNodeIterator::AdjacentRightNodeIterator(std::unordered_set<unsigned int>::const_iterator it, const BipartiteGraph& g): g(&g), pos(it){
}

//LeftNodeIterator

template <class T1, class T2>
inline BipartiteGraph<T1, T2>::LeftNodeIterator::LeftNodeIterator() : g(nullptr) {
}

template <class T1, class T2>
inline const T1& BipartiteGraph<T1, T2>::LeftNodeIterator::operator *() const {
    return (*pos).getInfo();
}

template <class T1, class T2>
inline bool BipartiteGraph<T1, T2>::LeftNodeIterator::operator ==(const LeftNodeIterator& otherIterator) const {
    return (g == otherIterator.g && pos == otherIterator.pos);
}

template <class T1, class T2>
inline bool BipartiteGraph<T1, T2>::LeftNodeIterator::operator !=(const LeftNodeIterator& otherIterator) const {
    return (g != otherIterator.g || pos != otherIterator.pos);
}

template <class T1, class T2>
inline typename BipartiteGraph<T1, T2>::LeftNodeIterator BipartiteGraph<T1, T2>::LeftNodeIterator::operator ++() {
    do {
        ++pos;
    } while (pos != g->nodesL.end() && (g->unusedLNodes.find(pos - g->nodesL.begin())) != g->unusedLNodes.end());
    return *this;
}

template <class T1, class T2>
inline typename BipartiteGraph<T1, T2>::LeftNodeIterator BipartiteGraph<T1, T2>::LeftNodeIterator::operator ++(int) {
    LeftNodeIterator oldIt = *this;
    do {
        ++pos;
    } while (pos != g->nodesL.end() && (g->unusedLNodes.find(pos - g->nodesL.begin())) != g->unusedLNodes.end());
    return oldIt;
}

template <class T1, class T2>
inline typename BipartiteGraph<T1, T2>::LeftNodeIterator BipartiteGraph<T1, T2>::LeftNodeIterator::operator --() {
    do {
        --pos;
    } while (pos != g->nodesL.begin() && (g->unusedLNodes.find(pos - g->nodesL.begin())) != g->unusedLNodes.end());
    return *this;
}

template <class T1, class T2>
inline typename BipartiteGraph<T1, T2>::LeftNodeIterator BipartiteGraph<T1, T2>::LeftNodeIterator::operator --(int) {
    LeftNodeIterator oldIt;
    do {
        --pos;
    } while (pos != g->nodesL.begin() && (g->unusedLNodes.find(pos - g->nodesL.begin())) != g->unusedLNodes.end());
    return oldIt;
}

template <class T1, class T2>
inline BipartiteGraph<T1, T2>::LeftNodeIterator::LeftNodeIterator(typename std::vector<cg3::UndirectedNode<T1> >::const_iterator it, const BipartiteGraph& g): g(&g), pos(it){
    while (pos != g.nodesL.end() && (g.unusedLNodes.find(pos - g.nodesL.begin())) != g.unusedLNodes.end())
        ++pos;
}

//RightNodeIterator

template <class T1, class T2>
inline BipartiteGraph<T1, T2>::RightNodeIterator::RightNodeIterator() : g(nullptr) {
}

template <class T1, class T2>
inline const T2& BipartiteGraph<T1, T2>::RightNodeIterator::operator *() const {
    return (*pos).getInfo();
}

template <class T1, class T2>
inline bool BipartiteGraph<T1, T2>::RightNodeIterator::operator ==(const RightNodeIterator& otherIterator) const {
    return (g == otherIterator.g && pos == otherIterator.pos);
}

template <class T1, class T2>
inline bool BipartiteGraph<T1, T2>::RightNodeIterator::operator !=(const RightNodeIterator& otherIterator) const {
    return (g != otherIterator.g || pos != otherIterator.pos);
}

template <class T1, class T2>
inline typename BipartiteGraph<T1, T2>::RightNodeIterator BipartiteGraph<T1, T2>::RightNodeIterator::operator ++() {
    do {
        ++pos;
    } while (pos != g->nodesR.end() && (g->unusedRNodes.find(pos - g->nodesR.begin())) != g->unusedRNodes.end());
    return *this;
}

template <class T1, class T2>
inline typename BipartiteGraph<T1, T2>::RightNodeIterator BipartiteGraph<T1, T2>::RightNodeIterator::operator ++(int) {
    RightNodeIterator oldIt = *this;
    do {
        ++pos;
    } while (pos != g->nodesR.end() && (g->unusedRNodes.find(pos - g->nodesR.begin())) != g->unusedRNodes.end());
    return oldIt;
}

template <class T1, class T2>
inline typename BipartiteGraph<T1, T2>::RightNodeIterator BipartiteGraph<T1, T2>::RightNodeIterator::operator --() {
    do {
        --pos;
    } while (pos != g->nodesR.begin() && (g->unusedRNodes.find(pos - g->nodesR.begin())) != g->unusedRNodes.end());
    return *this;
}

template <class T1, class T2>
inline typename BipartiteGraph<T1, T2>::RightNodeIterator BipartiteGraph<T1, T2>::RightNodeIterator::operator --(int) {
    RightNodeIterator oldIt;
    do {
        --pos;
    } while (pos != g->nodesV.begin() && (g->unusedVNodes.find(pos - g->nodesV.begin())) != g->unusedVNodes.end());
    return oldIt;
}

template <class T1, class T2>
inline BipartiteGraph<T1, T2>::RightNodeIterator::RightNodeIterator(typename std::vector<cg3::UndirectedNode<T2> >::const_iterator it, const BipartiteGraph& g): g(&g), pos(it){
    while (pos != g.nodesR.end() && (g.unusedRNodes.find(pos - g.nodesR.begin())) != g.unusedRNodes.end())
        ++pos;
}

//ConstAdjacentLeftNodeRangeBasedIterator

template<class T1, class T2>
inline typename BipartiteGraph<T1, T2>::AdjacentLeftNodeIterator BipartiteGraph<T1, T2>::AdjacentLeftNodeRangeBasedIterator::begin() const {
    return g->adjacentLeftNodeBegin(uNode);
}

template<class T1, class T2>
inline typename BipartiteGraph<T1, T2>::AdjacentLeftNodeIterator BipartiteGraph<T1, T2>::AdjacentLeftNodeRangeBasedIterator::end() const {
    return g->adjacentLeftNodeEnd(uNode);
}

template<class T1, class T2>
inline BipartiteGraph<T1, T2>::AdjacentLeftNodeRangeBasedIterator::AdjacentLeftNodeRangeBasedIterator(const BipartiteGraph* g, const T1& uNode) : g(g), uNode(uNode) {
}

//ConstAdjacentRightNodeRangeBasedIterator

template<class T1, class T2>
inline typename BipartiteGraph<T1, T2>::AdjacentRightNodeIterator BipartiteGraph<T1, T2>::AdjacentRightNodeRangeBasedIterator::begin() const {
    return g->adjacentRightNodeBegin(vNode);
}

template<class T1, class T2>
inline typename BipartiteGraph<T1, T2>::AdjacentRightNodeIterator BipartiteGraph<T1, T2>::AdjacentRightNodeRangeBasedIterator::end() const {
    return g->adjacentRightNodeEnd(vNode);
}

template<class T1, class T2>
inline BipartiteGraph<T1, T2>::AdjacentRightNodeRangeBasedIterator::AdjacentRightNodeRangeBasedIterator(const BipartiteGraph* g, const T2& vNode) : g(g), vNode(vNode) {
}

//LeftNodeRangeBasedIterator

template<class T1, class T2>
inline typename BipartiteGraph<T1, T2>::LeftNodeIterator BipartiteGraph<T1, T2>::LeftNodeRangeBasedIterator::begin() const {
    return g->leftNodeBegin();
}

template<class T1, class T2>
inline typename BipartiteGraph<T1, T2>::LeftNodeIterator BipartiteGraph<T1, T2>::LeftNodeRangeBasedIterator::end() const {
    return g->leftNodeEnd();
}

template<class T1, class T2>
inline BipartiteGraph<T1, T2>::LeftNodeRangeBasedIterator::LeftNodeRangeBasedIterator(const BipartiteGraph* g) : g(g) {
}

//RightNodeRangeBasedIterator

template<class T1, class T2>
inline typename BipartiteGraph<T1, T2>::RightNodeIterator BipartiteGraph<T1, T2>::RightNodeRangeBasedIterator::begin() const {
    return g->rightNodeBegin();
}

template<class T1, class T2>
inline typename BipartiteGraph<T1, T2>::RightNodeIterator BipartiteGraph<T1, T2>::RightNodeRangeBasedIterator::end() const {
    return g->rightNodeEnd();
}

template<class T1, class T2>
inline BipartiteGraph<T1, T2>::RightNodeRangeBasedIterator::RightNodeRangeBasedIterator(const BipartiteGraph* g) : g(g) {
}

} //namespace cg3

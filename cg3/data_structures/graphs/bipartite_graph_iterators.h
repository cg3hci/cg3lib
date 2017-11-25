#ifndef CG3_BIPARTITE_GRAPH_ITERATORS_H
#define CG3_BIPARTITE_GRAPH_ITERATORS_H

#include "bipartite_graph.h"

namespace cg3 {

template <class T1, class T2>
class BipartiteGraph<T1, T2>::AdjacentUNodeIterator{
        friend class BipartiteGraph;
    public:
        AdjacentUNodeIterator();

        const T2& operator *() const;
        bool operator == (const AdjacentUNodeIterator& otherIterator) const;
        bool operator != (const AdjacentUNodeIterator& otherIterator) const;

        AdjacentUNodeIterator operator ++ ();
        AdjacentUNodeIterator operator ++ (int);
        AdjacentUNodeIterator operator -- ();
        AdjacentUNodeIterator operator -- (int);

    protected:
        const BipartiteGraph* g;
        std::set<unsigned int>::iterator pos;
        AdjacentUNodeIterator(std::set<unsigned int>::iterator it, const BipartiteGraph &g);


};

template <class T1, class T2>
class BipartiteGraph<T1, T2>::AdjacentVNodeIterator{
        friend class BipartiteGraph;
    public:
        AdjacentVNodeIterator();

        const T1& operator *() const;
        bool operator == (const AdjacentVNodeIterator& otherIterator) const;
        bool operator != (const AdjacentVNodeIterator& otherIterator) const;

        AdjacentVNodeIterator operator ++ ();
        AdjacentVNodeIterator operator ++ (int);
        AdjacentVNodeIterator operator -- ();
        AdjacentVNodeIterator operator -- (int);

    protected:
        const BipartiteGraph* g;
        std::set<unsigned int>::iterator pos;
        AdjacentVNodeIterator(std::set<unsigned int>::iterator it, const BipartiteGraph &g);


};

template <class T1, class T2>
class BipartiteGraph<T1, T2>::UNodeIterator{
        friend class BipartiteGraph;
    public:
        UNodeIterator();

        const T1& operator *() const;
        bool operator == (const UNodeIterator& otherIterator) const;
        bool operator != (const UNodeIterator& otherIterator) const;

        UNodeIterator operator ++ ();
        UNodeIterator operator ++ (int);
        UNodeIterator operator -- ();
        UNodeIterator operator -- (int);

    protected:
        const BipartiteGraph* g;
        typename std::vector<cg3::graphs::UndirectedNode<T1> >::const_iterator pos;
        UNodeIterator(typename std::vector<cg3::graphs::UndirectedNode<T1> >::const_iterator it, const BipartiteGraph &g);


};

template <class T1, class T2>
class BipartiteGraph<T1, T2>::VNodeIterator{
        friend class BipartiteGraph;
    public:
        VNodeIterator();

        const T2& operator *() const;
        bool operator == (const VNodeIterator& otherIterator) const;
        bool operator != (const VNodeIterator& otherIterator) const;

        VNodeIterator operator ++ ();
        VNodeIterator operator ++ (int);
        VNodeIterator operator -- ();
        VNodeIterator operator -- (int);

    protected:
        const BipartiteGraph* g;
        typename std::vector<cg3::graphs::UndirectedNode<T2> >::const_iterator pos;
        VNodeIterator(typename std::vector<cg3::graphs::UndirectedNode<T2> >::const_iterator it, const BipartiteGraph &g);


};

template <class T1, class T2>
class BipartiteGraph<T1, T2>::AdjacentUNodeRangeBasedIterator {
        friend class BipartiteGraph;
    public:
        BipartiteGraph<T1, T2>::AdjacentUNodeIterator begin() const;
        BipartiteGraph<T1, T2>::AdjacentUNodeIterator end() const;
    protected:
        const BipartiteGraph* g;
        const T1& uNode;
        AdjacentUNodeRangeBasedIterator(const BipartiteGraph* g, const T1& uNode);
};

template <class T1, class T2>
class BipartiteGraph<T1, T2>::AdjacentVNodeRangeBasedIterator {
        friend class BipartiteGraph;
    public:
        BipartiteGraph<T1, T2>::AdjacentVNodeIterator begin() const;
        BipartiteGraph<T1, T2>::AdjacentVNodeIterator end() const;
    protected:
        const BipartiteGraph* g;
        const T2& vNode;
        AdjacentVNodeRangeBasedIterator(const BipartiteGraph* g, const T2& vNode);
};

template <class T1, class T2>
class BipartiteGraph<T1, T2>::UNodeRangeBasedIterator {
        friend class BipartiteGraph;
    public:
        BipartiteGraph<T1, T2>::UNodeIterator begin() const;
        BipartiteGraph<T1, T2>::UNodeIterator end() const;
    protected:
        const BipartiteGraph* g;
        UNodeRangeBasedIterator(const BipartiteGraph* g);
};

template <class T1, class T2>
class BipartiteGraph<T1, T2>::VNodeRangeBasedIterator {
        friend class BipartiteGraph;
    public:
        BipartiteGraph<T1, T2>::VNodeIterator begin() const;
        BipartiteGraph<T1, T2>::VNodeIterator end() const;
    protected:
        const BipartiteGraph* g;
        VNodeRangeBasedIterator(const BipartiteGraph* g);
};

//ConstAdjacentUNodeIterator

template <class T1, class T2>
BipartiteGraph<T1, T2>::AdjacentUNodeIterator::AdjacentUNodeIterator() : g(nullptr) {
}

template <class T1, class T2>
const T2& BipartiteGraph<T1, T2>::AdjacentUNodeIterator::operator *() const {
    return g->nodesV[*pos].getInfo();
}

template <class T1, class T2>
bool BipartiteGraph<T1, T2>::AdjacentUNodeIterator::operator ==(const BipartiteGraph<T1, T2>::AdjacentUNodeIterator& otherIterator) const {
    return (g == otherIterator.g && pos == otherIterator.pos);
}

template <class T1, class T2>
bool BipartiteGraph<T1, T2>::AdjacentUNodeIterator::operator !=(const BipartiteGraph<T1, T2>::AdjacentUNodeIterator& otherIterator) const {
    return (g != otherIterator.g || pos != otherIterator.pos);
}

template <class T1, class T2>
typename BipartiteGraph<T1, T2>::AdjacentUNodeIterator BipartiteGraph<T1, T2>::AdjacentUNodeIterator::operator ++() {
    ++pos;
    return *this;
}

template <class T1, class T2>
typename BipartiteGraph<T1, T2>::AdjacentUNodeIterator BipartiteGraph<T1, T2>::AdjacentUNodeIterator::operator ++(int) {
    AdjacentUNodeIterator oldIt = *this;
    ++pos;
    return oldIt;
}

template <class T1, class T2>
typename BipartiteGraph<T1, T2>::AdjacentUNodeIterator BipartiteGraph<T1, T2>::AdjacentUNodeIterator::operator --() {
    --pos;
    return *this;
}

template <class T1, class T2>
typename BipartiteGraph<T1, T2>::AdjacentUNodeIterator BipartiteGraph<T1, T2>::AdjacentUNodeIterator::operator --(int) {
    AdjacentUNodeIterator oldIt;
    --pos;
    return oldIt;
}

template <class T1, class T2>
BipartiteGraph<T1, T2>::AdjacentUNodeIterator::AdjacentUNodeIterator(std::set<unsigned int>::iterator it, const BipartiteGraph& g): g(&g), pos(it){
}

//ConstAdjacentUNodeIterator

template <class T1, class T2>
BipartiteGraph<T1, T2>::AdjacentVNodeIterator::AdjacentVNodeIterator() : g(nullptr) {
}

template <class T1, class T2>
const T1& BipartiteGraph<T1, T2>::AdjacentVNodeIterator::operator *() const {
    return g->nodesU[*pos].getInfo();
}

template <class T1, class T2>
bool BipartiteGraph<T1, T2>::AdjacentVNodeIterator::operator ==(const BipartiteGraph<T1, T2>::AdjacentVNodeIterator& otherIterator) const {
    return (g == otherIterator.g && pos == otherIterator.pos);
}

template <class T1, class T2>
bool BipartiteGraph<T1, T2>::AdjacentVNodeIterator::operator !=(const BipartiteGraph<T1, T2>::AdjacentVNodeIterator& otherIterator) const {
    return (g != otherIterator.g || pos != otherIterator.pos);
}

template <class T1, class T2>
typename BipartiteGraph<T1, T2>::AdjacentVNodeIterator BipartiteGraph<T1, T2>::AdjacentVNodeIterator::operator ++() {
    ++pos;
    return *this;
}

template <class T1, class T2>
typename BipartiteGraph<T1, T2>::AdjacentVNodeIterator BipartiteGraph<T1, T2>::AdjacentVNodeIterator::operator ++(int) {
    AdjacentVNodeIterator oldIt = *this;
    ++pos;
    return oldIt;
}

template <class T1, class T2>
typename BipartiteGraph<T1, T2>::AdjacentVNodeIterator BipartiteGraph<T1, T2>::AdjacentVNodeIterator::operator --() {
    --pos;
    return *this;
}

template <class T1, class T2>
typename BipartiteGraph<T1, T2>::AdjacentVNodeIterator BipartiteGraph<T1, T2>::AdjacentVNodeIterator::operator --(int) {
    AdjacentVNodeIterator oldIt;
    --pos;
    return oldIt;
}

template <class T1, class T2>
BipartiteGraph<T1, T2>::AdjacentVNodeIterator::AdjacentVNodeIterator(std::set<unsigned int>::iterator it, const BipartiteGraph& g): g(&g), pos(it){
}

//UNodeIterator

template <class T1, class T2>
BipartiteGraph<T1, T2>::UNodeIterator::UNodeIterator() : g(nullptr) {
}

template <class T1, class T2>
const T1& BipartiteGraph<T1, T2>::UNodeIterator::operator *() const {
    return (*pos).getInfo();
}

template <class T1, class T2>
bool BipartiteGraph<T1, T2>::UNodeIterator::operator ==(const BipartiteGraph<T1, T2>::UNodeIterator& otherIterator) const {
    return (g == otherIterator.g && pos == otherIterator.pos);
}

template <class T1, class T2>
bool BipartiteGraph<T1, T2>::UNodeIterator::operator !=(const BipartiteGraph<T1, T2>::UNodeIterator& otherIterator) const {
    return (g != otherIterator.g || pos != otherIterator.pos);
}

template <class T1, class T2>
typename BipartiteGraph<T1, T2>::UNodeIterator BipartiteGraph<T1, T2>::UNodeIterator::operator ++() {
    do {
        ++pos;
    } while (pos != g->nodesU.end() && (g->unusedUNodes.find(pos - g->nodesU.begin())) != g->unusedUNodes.end());
    return *this;
}

template <class T1, class T2>
typename BipartiteGraph<T1, T2>::UNodeIterator BipartiteGraph<T1, T2>::UNodeIterator::operator ++(int) {
    UNodeIterator oldIt = *this;
    do {
        ++pos;
    } while (pos != g->nodesU.end() && (g->unusedUNodes.find(pos - g->nodesU.begin())) != g->unusedUNodes.end());
    return oldIt;
}

template <class T1, class T2>
typename BipartiteGraph<T1, T2>::UNodeIterator BipartiteGraph<T1, T2>::UNodeIterator::operator --() {
    do {
        --pos;
    } while (pos != g->nodesU.begin() && (g->unusedUNodes.find(pos - g->nodesU.begin())) != g->unusedUNodes.end());
    return *this;
}

template <class T1, class T2>
typename BipartiteGraph<T1, T2>::UNodeIterator BipartiteGraph<T1, T2>::UNodeIterator::operator --(int) {
    UNodeIterator oldIt;
    do {
        --pos;
    } while (pos != g->nodesU.begin() && (g->unusedUNodes.find(pos - g->nodesU.begin())) != g->unusedUNodes.end());
    return oldIt;
}

template <class T1, class T2>
BipartiteGraph<T1, T2>::UNodeIterator::UNodeIterator(typename std::vector<cg3::graphs::UndirectedNode<T1> >::const_iterator it, const BipartiteGraph& g): g(&g), pos(it){
}

//VNodeIterator

template <class T1, class T2>
BipartiteGraph<T1, T2>::VNodeIterator::VNodeIterator() : g(nullptr) {
}

template <class T1, class T2>
const T2& BipartiteGraph<T1, T2>::VNodeIterator::operator *() const {
    return (*pos).getInfo();
}

template <class T1, class T2>
bool BipartiteGraph<T1, T2>::VNodeIterator::operator ==(const BipartiteGraph<T1, T2>::VNodeIterator& otherIterator) const {
    return (g == otherIterator.g && pos == otherIterator.pos);
}

template <class T1, class T2>
bool BipartiteGraph<T1, T2>::VNodeIterator::operator !=(const BipartiteGraph<T1, T2>::VNodeIterator& otherIterator) const {
    return (g != otherIterator.g || pos != otherIterator.pos);
}

template <class T1, class T2>
typename BipartiteGraph<T1, T2>::VNodeIterator BipartiteGraph<T1, T2>::VNodeIterator::operator ++() {
    do {
        ++pos;
    } while (pos != g->nodesV.end() && (g->unusedVNodes.find(pos - g->nodesV.begin())) != g->unusedVNodes.end());
    return *this;
}

template <class T1, class T2>
typename BipartiteGraph<T1, T2>::VNodeIterator BipartiteGraph<T1, T2>::VNodeIterator::operator ++(int) {
    UNodeIterator oldIt = *this;
    do {
        ++pos;
    } while (pos != g->nodesV.end() && (g->unusedVNodes.find(pos - g->nodesV.begin())) != g->unusedVNodes.end());
    return oldIt;
}

template <class T1, class T2>
typename BipartiteGraph<T1, T2>::VNodeIterator BipartiteGraph<T1, T2>::VNodeIterator::operator --() {
    do {
        --pos;
    } while (pos != g->nodesV.begin() && (g->unusedVNodes.find(pos - g->nodesV.begin())) != g->unusedVNodes.end());
    return *this;
}

template <class T1, class T2>
typename BipartiteGraph<T1, T2>::VNodeIterator BipartiteGraph<T1, T2>::VNodeIterator::operator --(int) {
    UNodeIterator oldIt;
    do {
        --pos;
    } while (pos != g->nodesV.begin() && (g->unusedVNodes.find(pos - g->nodesV.begin())) != g->unusedVNodes.end());
    return oldIt;
}

template <class T1, class T2>
BipartiteGraph<T1, T2>::VNodeIterator::VNodeIterator(typename std::vector<cg3::graphs::UndirectedNode<T2> >::const_iterator it, const BipartiteGraph& g): g(&g), pos(it){
}

//ConstAdjacentUNodeRangeBasedIterator

template<class T1, class T2>
typename BipartiteGraph<T1, T2>::AdjacentUNodeIterator BipartiteGraph<T1, T2>::AdjacentUNodeRangeBasedIterator::begin() const {
    return g->adjacentUNodeBegin(uNode);
}

template<class T1, class T2>
typename BipartiteGraph<T1, T2>::AdjacentUNodeIterator BipartiteGraph<T1, T2>::AdjacentUNodeRangeBasedIterator::end() const {
    return g->adjacentUNodeEnd(uNode);
}

template<class T1, class T2>
BipartiteGraph<T1, T2>::AdjacentUNodeRangeBasedIterator::AdjacentUNodeRangeBasedIterator(const BipartiteGraph* g, const T1& uNode) : g(g), uNode(uNode) {
}

//ConstAdjacentVNodeRangeBasedIterator

template<class T1, class T2>
typename BipartiteGraph<T1, T2>::AdjacentVNodeIterator BipartiteGraph<T1, T2>::AdjacentVNodeRangeBasedIterator::begin() const {
    return g->adjacentVNodeBegin(vNode);
}

template<class T1, class T2>
typename BipartiteGraph<T1, T2>::AdjacentVNodeIterator BipartiteGraph<T1, T2>::AdjacentVNodeRangeBasedIterator::end() const {
    return g->adjacentVNodeEnd(vNode);
}

template<class T1, class T2>
BipartiteGraph<T1, T2>::AdjacentVNodeRangeBasedIterator::AdjacentVNodeRangeBasedIterator(const BipartiteGraph* g, const T2& vNode) : g(g), vNode(vNode) {
}

//UNodeRangeBasedIterator

template<class T1, class T2>
typename BipartiteGraph<T1, T2>::UNodeIterator BipartiteGraph<T1, T2>::UNodeRangeBasedIterator::begin() const {
    return g->uNodeBegin();
}

template<class T1, class T2>
typename BipartiteGraph<T1, T2>::UNodeIterator BipartiteGraph<T1, T2>::UNodeRangeBasedIterator::end() const {
    return g->uNodeEnd();
}

template<class T1, class T2>
BipartiteGraph<T1, T2>::UNodeRangeBasedIterator::UNodeRangeBasedIterator(const BipartiteGraph* g) : g(g) {
}

//VNodeRangeBasedIterator

template<class T1, class T2>
typename BipartiteGraph<T1, T2>::VNodeIterator BipartiteGraph<T1, T2>::VNodeRangeBasedIterator::begin() const {
    return g->vNodeBegin();
}

template<class T1, class T2>
typename BipartiteGraph<T1, T2>::VNodeIterator BipartiteGraph<T1, T2>::VNodeRangeBasedIterator::end() const {
    return g->vNodeEnd();
}

template<class T1, class T2>
BipartiteGraph<T1, T2>::VNodeRangeBasedIterator::VNodeRangeBasedIterator(const BipartiteGraph* g) : g(g) {
}

}

#endif // CG3_BIPARTITE_GRAPH_ITERATORS_H

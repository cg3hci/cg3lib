/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_BIPARTITE_GRAPH_ITERATORS_H
#define CG3_BIPARTITE_GRAPH_ITERATORS_H

#include "bipartite_graph.h"

namespace cg3 {

template <class T1, class T2>
class BipartiteGraph<T1, T2>::AdjacentLeftNodeIterator
{
    friend class BipartiteGraph;
public:
    AdjacentLeftNodeIterator();

    const T2& operator *() const;
    bool operator == (const AdjacentLeftNodeIterator& otherIterator) const;
    bool operator != (const AdjacentLeftNodeIterator& otherIterator) const;

    AdjacentLeftNodeIterator operator ++ ();
    AdjacentLeftNodeIterator operator ++ (int);

protected:
    const BipartiteGraph* g;
    std::unordered_set<unsigned int>::const_iterator pos;
    AdjacentLeftNodeIterator(
            std::unordered_set<unsigned int>::const_iterator it,
            const BipartiteGraph &g);
};

template <class T1, class T2>
class BipartiteGraph<T1, T2>::AdjacentRightNodeIterator
{
    friend class BipartiteGraph;
public:
    AdjacentRightNodeIterator();

    const T1& operator *() const;
    bool operator == (const AdjacentRightNodeIterator& otherIterator) const;
    bool operator != (const AdjacentRightNodeIterator& otherIterator) const;

    AdjacentRightNodeIterator operator ++ ();
    AdjacentRightNodeIterator operator ++ (int);

protected:
    const BipartiteGraph* g;
    std::unordered_set<unsigned int>::const_iterator pos;
    AdjacentRightNodeIterator(
            std::unordered_set<unsigned int>::const_iterator it,
            const BipartiteGraph &g);
};

template <class T1, class T2>
class BipartiteGraph<T1, T2>::LeftNodeIterator
{
    friend class BipartiteGraph;
public:
    LeftNodeIterator();

    const T1& operator *() const;
    bool operator == (const LeftNodeIterator& otherIterator) const;
    bool operator != (const LeftNodeIterator& otherIterator) const;

    LeftNodeIterator operator ++ ();
    LeftNodeIterator operator ++ (int);
    LeftNodeIterator operator -- ();
    LeftNodeIterator operator -- (int);

protected:
    const BipartiteGraph* g;
    typename std::vector<cg3::UndirectedNode<T1> >::const_iterator pos;
    LeftNodeIterator(
            typename std::vector<cg3::UndirectedNode<T1> >::const_iterator it,
            const BipartiteGraph &g);
};

template <class T1, class T2>
class BipartiteGraph<T1, T2>::RightNodeIterator
{
    friend class BipartiteGraph;
public:
    RightNodeIterator();

    const T2& operator *() const;
    bool operator == (const RightNodeIterator& otherIterator) const;
    bool operator != (const RightNodeIterator& otherIterator) const;

    RightNodeIterator operator ++ ();
    RightNodeIterator operator ++ (int);
    RightNodeIterator operator -- ();
    RightNodeIterator operator -- (int);

protected:
    const BipartiteGraph* g;
    typename std::vector<cg3::UndirectedNode<T2> >::const_iterator pos;
    RightNodeIterator(
            typename std::vector<cg3::UndirectedNode<T2> >::const_iterator it,
            const BipartiteGraph &g);
};

template <class T1, class T2>
class BipartiteGraph<T1, T2>::AdjacentLeftNodeRangeBasedIterator
{
    friend class BipartiteGraph;
public:
    AdjacentLeftNodeIterator begin() const;
    AdjacentLeftNodeIterator end() const;
protected:
    const BipartiteGraph* g;
    T1 uNode;
    AdjacentLeftNodeRangeBasedIterator(
            const BipartiteGraph* g,
            const T1& uNode);
};

template <class T1, class T2>
class BipartiteGraph<T1, T2>::AdjacentRightNodeRangeBasedIterator
{
    friend class BipartiteGraph;
public:
    AdjacentRightNodeIterator begin() const;
    AdjacentRightNodeIterator end() const;
protected:
    const BipartiteGraph* g;
    T2 vNode;
    AdjacentRightNodeRangeBasedIterator(
            const BipartiteGraph* g,
            const T2& vNode);
};

template <class T1, class T2>
class BipartiteGraph<T1, T2>::LeftNodeRangeBasedIterator
{
    friend class BipartiteGraph;
public:
    LeftNodeIterator begin() const;
    LeftNodeIterator end() const;
protected:
    const BipartiteGraph* g;
    LeftNodeRangeBasedIterator(const BipartiteGraph* g);
};

template <class T1, class T2>
class BipartiteGraph<T1, T2>::RightNodeRangeBasedIterator
{
    friend class BipartiteGraph;
public:
    RightNodeIterator begin() const;
    RightNodeIterator end() const;
protected:
    const BipartiteGraph* g;
    RightNodeRangeBasedIterator(const BipartiteGraph* g);
};

} //namespace cg3

#include "bipartite_graph_iterators.cpp"

#endif // CG3_BIPARTITE_GRAPH_ITERATORS_H

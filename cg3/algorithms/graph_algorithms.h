/**
    @author Stefano Nuvoli
*/
#ifndef CG3_GRAPH_ALGORITHMS_H
#define CG3_GRAPH_ALGORITHMS_H

#ifdef CG3_DATA_STRUCTURES_DEFINED

#include <map>
#include <list>

#include "cg3/data_structures/graphs/graph.h"

namespace cg3 {

template <class T>
struct GraphPath {
    std::list<T> path;
    double cost;
};

template <class T>
using DijkstraResult = std::map<T, GraphPath<T>>;

template <class T>
DijkstraResult<T> dijkstra(Graph<T>& graph, const T& source);

}

#include "graph_algorithms.tpp"

#endif

#endif // CG3_GRAPH_ALGORITHMS_H

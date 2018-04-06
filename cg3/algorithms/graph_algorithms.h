/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */
#ifndef CG3_GRAPH_ALGORITHMS_H
#define CG3_GRAPH_ALGORITHMS_H

#ifdef CG3_DATA_STRUCTURES_DEFINED

#include <map>
#include <list>

#include <cg3/data_structures/graphs/graph.h>

namespace cg3 {

/* General purpouse indexed implementation */

template <class G, class I>
void dijkstra(
        const G& graph,
        const std::vector<I>& nodes,
        const std::vector<std::list<size_t>>& nodeAdjacencies,
        const size_t sourceId,
        std::vector<double>& dist,
        std::vector<long long int>& pred);




/* Implementation for cg3::Graph */

/**
 * @brief Single graph path representation
 */
template <class T>
struct GraphPath {
    std::list<T> path;
    double cost;
};

/**
 * @brief Path from a given source to each node of the graph
 */
template <class T>
using DijkstraResult = std::map<T, GraphPath<T>>;


template <class T>
DijkstraResult<T> dijkstra(
        const Graph<T>& graph,
        const typename Graph<T>::iterator& sourceIt);
template <class T>
GraphPath<T> dijkstra(
        const Graph<T>& graph,
        const typename Graph<T>::iterator& sourceIt,
        const typename Graph<T>::iterator& destinationIt);


template <class T>
DijkstraResult<T> dijkstra(const Graph<T>& graph, const T& source);
template <class T>
GraphPath<T> dijkstra(const Graph<T>& graph, const T& source, const T& destination);



} //namespace cg3

#include "graph_algorithms.tpp"

#endif

#endif // CG3_GRAPH_ALGORITHMS_H

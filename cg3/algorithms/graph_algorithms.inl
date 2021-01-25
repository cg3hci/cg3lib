/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */
#ifdef CG3_DATA_STRUCTURES_DEFINED

#include <queue>
#include <utility>
#include <unordered_map>

#include "assert.h"

#include "graph_algorithms.h"

namespace cg3 {



/** ----- GENERAL PURPOSE INDEXED IMPLEMENTATION ----- */

/**
 * @brief General porpouse indexed Dijkstra algorithm. The current implementation has
 * time complexity O(|E| + |V| log |V|).
 * @param[in] graph Input graph. It is a templated type that must implement:
 * - getNode(id) that returns the node (or an iterator) given an id;
 * - getWeight(node1, node2) that takes the return type of getNode and returns
 *   the weight of the two nodes;
 * - A constant double MAX_WEIGHT which represent the max weight in the graph.
 * @param[in] nodes List of ids of the nodes of the graph
 * @param[in] nodeAdjacencies Indexed adjacencies of each graph node (referring to the
 * indices of the vector "nodes")
 * @param[in] sourceId Id of the source (referring to the indices of the vector "nodes")
 * @param[out] dist Vector of shortest path costs from the source to each node
 * @param[out] pred Vector for predecessors to compute the path
 */
template <class G, class I>
void dijkstra(
        const G& graph,
        const std::vector<I>& nodes,
        const std::vector<std::vector<size_t>>& nodeAdjacencies,
        const size_t sourceId,
        std::vector<double>& dist,
        std::vector<long long int>& pred)
{
    typedef std::pair<double, size_t> QueueObject;

    size_t numberOfNodes = nodes.size();

    dist.resize(numberOfNodes, G::MAX_WEIGHT);
    pred.resize(numberOfNodes, -1);

    dist[sourceId] = 0;
    pred[sourceId] = (long long int) sourceId;

    //Priority queue
    std::priority_queue<QueueObject, std::vector<QueueObject>, std::greater<QueueObject>> queue;

    queue.push(std::make_pair(0, sourceId));

    while (!queue.empty()) {
        //Get iterator on the queue and pop it from it
        const QueueObject& qObject = queue.top();
        size_t uId = qObject.second;

        queue.pop();

        //For each adjacent node
        for (const size_t& vId : nodeAdjacencies[uId]) {
            //Get weight
            double weight = graph.getWeight(
                        graph.getNode(nodes[uId]),
                        graph.getNode(nodes[vId]));

            assert(dist[uId] < G::MAX_WEIGHT);

            //If there is short path to v through u.
            if (dist[vId] > dist[uId] + weight)
            {
                //Update distance of v
                dist[vId] = dist[uId] + weight;

                //Set predecessor
                pred[vId] = (long long int) uId;

                //Add to the queue
                queue.push(std::make_pair(dist[vId], vId));
            }
        }
    }
}




/* ----- IMPLEMENTATION FOR cg3::Graph ----- */


namespace internal {


template <class T>
GraphPath<T> getShortestPath(
        const Graph<T>& graph,
        const typename Graph<T>::iterator sourceIt,
        const std::vector<size_t>& nodes,
        const size_t& sourceId,
        const size_t& destinationId,
        const std::vector<double>& dist,
        const std::vector<long long int>& pred);

} //namespace internal




/**
 * @brief Execute Dijkstra algorithm given a cg3 graph and the source. It
 * computes the shortest path between the source and all the nodes of the graph.
 * @param[in] graph Input cg3 graph.
 * @param[in] source Source node value
 * @return A map that associates all the graph nodes to the shortest path from the source
 * to that node. It contains structs which contain the path (a list of nodes) and a double
 * value which represents the cost of the path. The map is implemented using the std::map,
 * hence the informations can be after retrieved in O(log |V|) complexity time.
 */
template <class T>
inline DijkstraResult<T> dijkstra(const Graph<T>& graph, const T& source)
{
    typedef typename Graph<T>::iterator NodeIterator;

    //Search source in the graph
    NodeIterator sourceIt = graph.findNode(source);
    if (sourceIt == graph.end())
        throw std::runtime_error("Source has not been found in the graph.");

    return dijkstra(graph, sourceIt);
}

/**
 * @brief Execute Dijkstra algorithm given a cg3 graph and the source. It
 * computes the shortest path between the source and all the nodes of the graph.
 * @param[in] graph Input cg3 graph.
 * @param[in] source Source node value
 * @return A map that associates all the graph nodes to the shortest path from the source
 * to that node. It contains structs which contain the path (a list of nodes) and a double
 * value which represents the cost of the path. The map is implemented using the std::map,
 * hence the informations can be after retrieved in O(log |V|) complexity time.
 */
template <class T>
DijkstraResult<T> dijkstra(
        const Graph<T>& graph,
        const T& source,
        const std::vector<size_t>& nodes,
        const std::vector<std::vector<size_t>>& nodeAdjacencies,
        const std::unordered_map<size_t, size_t>& idMap)
{
    typedef typename Graph<T>::iterator NodeIterator;

    //Search source in the graph
    NodeIterator sourceIt = graph.findNode(source);
    if (sourceIt == graph.end())
        throw std::runtime_error("Source has not been found in the graph.");

    return dijkstra(graph, sourceIt, nodes, nodeAdjacencies, idMap);
}

/**
 * @brief Execute Dijkstra algorithm given a cg3 graph and the source. It
 * computes the shortest path between the source and all the nodes of the graph.
 * @param[in] graph Input cg3 graph.
 * @param[in] sourceIt Source node iterator
 * @param[in] nodes List of ids of the nodes of the graph
 * @param[in] nodeAdjacencies Indexed adjacencies of each graph node (referring to the
 * indices of the vector "nodes")
 * @param[in] idMap Map to get the index of a node (referring to the indices of the vector
 * "nodes") given the id on the input cg3 graph
 * @return A map that associates all the graph nodes to the shortest path from the source
 * to that node. It contains structs which contain the path (a list of nodes) and a double
 * value which represents the cost of the path. The map is implemented using the std::map,
 * hence the informations can be after retrieved in O(log |V|) complexity time.
 */
template <class T>
DijkstraResult<T> dijkstra(
        const Graph<T>& graph,
        const typename Graph<T>::iterator& sourceIt)
{
    //Vector of nodes and adjacencies
    std::vector<size_t> nodes;
    std::vector<std::vector<size_t>> nodeAdjacencies;
    std::unordered_map<size_t, size_t> idMap;

    //Fill indexed data needed to execute general purpose Dijkstra algorithm
    fillIndexedData(graph, nodes, nodeAdjacencies, idMap);

    return dijkstra(graph, sourceIt, nodes, nodeAdjacencies, idMap);
}

/**
 * @brief Execute Dijkstra algorithm given a cg3 graph and the source. It
 * computes the shortest path between the source and all the nodes of the graph.
 * @param[in] graph Input cg3 graph.
 * @param[in] sourceIt Source node iterator
 * @param[in] nodes List of ids of the nodes of the graph
 * @param[in] nodeAdjacencies Indexed adjacencies of each graph node (referring to the
 * indices of the vector "nodes")
 * @param[in] idMap Map to get the index of a node (referring to the indices of the vector
 * "nodes") given the id on the input cg3 graph
 * @return A map that associates all the graph nodes to the shortest path from the source
 * to that node. It contains structs which contain the path (a list of nodes) and a double
 * value which represents the cost of the path. The map is implemented using the std::map,
 * hence the informations can be after retrieved in O(log |V|) complexity time.
 */
template <class T>
DijkstraResult<T> dijkstra(
        const Graph<T>& graph,
        const typename Graph<T>::iterator& sourceIt,
        const std::vector<size_t>& nodes,
        const std::vector<std::vector<size_t>>& nodeAdjacencies,
        const std::unordered_map<size_t, size_t>& idMap)
{
    typedef typename Graph<T>::iterator NodeIterator;

    //Vector of distances and predecessor of the shortest path from the source
    std::vector<double> dist;
    std::vector<long long int> pred;

    //Id of the source
    size_t sourceId = idMap.find(graph.getId(sourceIt))->second;


    //Execute Dijkstra
    dijkstra(graph, nodes, nodeAdjacencies, sourceId, dist, pred);



    //Result to be returned
    DijkstraResult<T> resultMap;

    //Update result map for each destination
    size_t destinationId = 0;
    for (const size_t& nodeId : nodes) {
        //If there is a path
        if (pred[destinationId] != -1) {
            //Return the resulting shortest path
            GraphPath<T> graphPath = internal::getShortestPath(graph, sourceIt, nodes, sourceId, destinationId, dist, pred);

            //Fill map            
            NodeIterator nodeIt = graph.getNode(nodeId);
            resultMap.insert(std::make_pair(*nodeIt, graphPath));
        }

        destinationId++;
    }


    return resultMap;
}






/**
 * @brief Execute Dijkstra algorithm to get the shortest path from the source
 * to the destination, given a cg3 graph.
 * @param[in] graph Input cg3 graph.
 * @param[in] source Source node value
 * @param[in] destination Destination node value
 * @return A struct which contains the shortest path and its cost.
 * If no path exists, then an empty path of MAX_WEIGHT cost is returned.
 * The data can be retrieved in constant time.
 */
template <class T>
inline GraphPath<T> dijkstra(
        const Graph<T>& graph,
        const T& source,
        const T& destination)
{
    typedef typename Graph<T>::iterator NodeIterator;

    //Search source in the graph
    NodeIterator sourceIt = graph.findNode(source);
    if (sourceIt == graph.end())
        throw std::runtime_error("Source has not been found in the graph.");

    //Search destination in the graph
    NodeIterator destinationIt = graph.findNode(destination);
    if (destinationIt == graph.end())
        throw std::runtime_error("Destination has not been found in the graph.");

    return dijkstra(graph, sourceIt, destinationIt);
}

/**
 * @brief Execute Dijkstra algorithm to get the shortest path from the source
 * to the destination, given a cg3 graph.
 * @param[in] graph Input cg3 graph.
 * @param[in] source Source node value
 * @param[in] destination Destination node value
 * @param[in] nodes List of ids of the nodes of the graph
 * @param[in] nodeAdjacencies Indexed adjacencies of each graph node (referring to the
 * indices of the vector "nodes")
 * @param[in] idMap Map to get the index of a node (referring to the indices of the vector
 * "nodes") given the id on the input cg3 graph
 * @return A struct which contains the shortest path and its cost.
 * If no path exists, then an empty path of MAX_WEIGHT cost is returned.
 * The data can be retrieved in constant time.
 */
template <class T>
GraphPath<T> dijkstra(
        const Graph<T>& graph,
        const T& source,
        const T& destination,
        const std::vector<size_t>& nodes,
        const std::vector<std::vector<size_t>>& nodeAdjacencies,
        const std::unordered_map<size_t, size_t>& idMap)
{
    typedef typename Graph<T>::iterator NodeIterator;

    //Search source in the graph
    NodeIterator sourceIt = graph.findNode(source);
    if (sourceIt == graph.end())
        throw std::runtime_error("Source has not been found in the graph.");

    //Search destination in the graph
    NodeIterator destinationIt = graph.findNode(destination);
    if (destinationIt == graph.end())
        throw std::runtime_error("Destination has not been found in the graph.");

    return dijkstra(graph, sourceIt, destinationIt, nodes, nodeAdjacencies, idMap);
}

/**
 * @brief Execute Dijkstra algorithm to get the shortest path from the source
 * to the destination, given a cg3 graph.
 * @param[in] graph Input cg3 graph.
 * @param[in] sourceIt Source node iterator
 * @param[in] destinationIt Destination node iterator
 * @return A struct which contains the shortest path and its cost.
 * If no path exists, then an empty path of MAX_WEIGHT cost is returned.
 * The data can be retrieved in constant time.
 */
template <class T>
GraphPath<T> dijkstra(
        const Graph<T>& graph,
        const typename Graph<T>::iterator& sourceIt,
        const typename Graph<T>::iterator& destinationIt)
{
    //Vector of nodes and adjacencies
    std::vector<size_t> nodes;
    std::vector<std::vector<size_t>> nodeAdjacencies;
    std::unordered_map<size_t, size_t> idMap;


    //Fill indexed data needed by general purpose Dijkstra algorithm
    fillIndexedData(graph, nodes, nodeAdjacencies, idMap);

    return dijkstra(graph, sourceIt, destinationIt, nodes, nodeAdjacencies, idMap);
}

/**
 * @brief Execute Dijkstra algorithm to get the shortest path from the source
 * to the destination, given a cg3 graph.
 * @param[in] graph Input cg3 graph.
 * @param[in] sourceIt Source node iterator
 * @param[in] destinationIt Destination node iterator
 * @param[in] nodes List of ids of the nodes of the graph
 * @param[in] nodeAdjacencies Indexed adjacencies of each graph node (referring to the
 * indices of the vector "nodes")
 * @param[in] idMap Map to get the index of a node (referring to the indices of the vector
 * "nodes") given the id on the input cg3 graph
 * @return A struct which contains the shortest path and its cost.
 * If no path exists, then an empty path of MAX_WEIGHT cost is returned.
 * The data can be retrieved in constant time.
 */
template <class T>
GraphPath<T> dijkstra(
        const Graph<T>& graph,
        const typename Graph<T>::iterator& sourceIt,
        const typename Graph<T>::iterator& destinationIt,
        const std::vector<size_t>& nodes,
        const std::vector<std::vector<size_t>>& nodeAdjacencies,
        const std::unordered_map<size_t, size_t>& idMap)
{
    //Vector of distances and predecessor of the shortest path from the source
    std::vector<double> dist;
    std::vector<long long int> pred;

    //Id of the source and destination
    size_t sourceId = idMap.find(graph.getId(sourceIt))->second;
    size_t destinationId = idMap.find(graph.getId(destinationIt))->second;

    //Execute Dijkstra
    dijkstra(graph, nodes, nodeAdjacencies, sourceId, dist, pred);

    return internal::getShortestPath(graph, sourceIt, nodes, sourceId, destinationId, dist, pred);
}



/**
 * @brief Fill indexed data structure needed by the Dijkstra algorithm for a cg3 graph.
 * @param[in] graph Input cg3 graph
 * @param[out] nodes List of ids of the nodes of the graph
 * @param[out] nodeAdjacencies Indexed adjacencies of each graph node (referring to the
 * indices of the vector "nodes")
 * @param[out] idMap Map to get the index of a node (referring to the indices of the vector
 * "nodes") given the id on the input cg3 graph
 */
template <class T>
inline void fillIndexedData(
        const Graph<T>& graph,
        std::vector<size_t>& nodes,
        std::vector<std::vector<size_t>>& nodeAdjacencies,
        std::unordered_map<size_t, size_t>& idMap)
{
    typedef typename Graph<T>::iterator NodeIterator;
    typedef typename Graph<T>::AdjacentIterator AdjacentIterator;

    size_t id;

    //Fill vector of iterators for the nodes
    id = 0;

    //Iterate on nodes of the graph
    for (NodeIterator it = graph.begin(); it != graph.end(); ++it) {
        size_t graphId = graph.getId(it);

        nodes.push_back(graphId);

        idMap.insert(std::make_pair(graphId, id));

        id++;
    }

    //Fill vector of adjacencies
    nodeAdjacencies.resize(nodes.size());

    id = 0;
    for (const size_t& graphId : nodes) {
        NodeIterator nodeIt = graph.getNode(graphId);

        std::vector<size_t>& adjList = nodeAdjacencies[id];

        //For each adjacent node
        for (AdjacentIterator adjNodeIt = graph.adjacentBegin(nodeIt); adjNodeIt != graph.adjacentEnd(nodeIt); adjNodeIt++) {
            typename std::unordered_map<size_t, size_t>::iterator findIdIt = idMap.find(graph.getId(adjNodeIt));
            size_t adjId = findIdIt->second;

            adjList.push_back(adjId);
        }

        id++;
    }
}


namespace internal {

/**
 * @brief Get the resulting shortest path in the cg3 graph, given the raw Dijkstra data,
 * given a source and a destination
 * @param[in] graph Input cg3 graph
 * @param[in] sourceIt cg3 graph iterator of the source node.
 * @param[in] nodes List of ids of the nodes of the graph
 * @param[in] sourceId Id of the source (referring to the indices of the vector "nodes")
 * @param[in] destinationId Id of the destination (referring to the indices of the vector "nodes")
 * @param[in] dist Vector of shortest path costs from the source to each node
 * @param[in] pred Vector for predecessors to compute the path
 * @return Shortest path between source and destination
 */
template <class T>
inline GraphPath<T> getShortestPath(
        const Graph<T>& graph,
        const typename Graph<T>::iterator sourceIt,
        const std::vector<size_t>& nodes,
        const size_t& sourceId,
        const size_t& destinationId,
        const std::vector<double>& dist,
        const std::vector<long long int>& pred)
{
    typedef typename Graph<T>::iterator NodeIterator;

    //Result graph path
    GraphPath<T> graphPath;

    //Get the shortest path
    if (pred[destinationId] != -1) {
        //Create path
        size_t idPred = destinationId;
        while (idPred != sourceId) {
            NodeIterator predIterator = graph.getNode(nodes[idPred]);

            graphPath.path.push_front(*predIterator);

            assert(pred[idPred] >= 0);

            idPred = (size_t) pred[idPred];
        }

        graphPath.path.push_front(*sourceIt);
    }

    graphPath.cost = dist[destinationId];

    return graphPath;
}


} //namespace internal

} //namespace cg3

#endif

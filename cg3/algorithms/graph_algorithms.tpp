/**
  * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
  * This Source Code Form is subject to the terms of the GNU GPL 3.0
  *
  * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
  */
#ifdef CG3_DATA_STRUCTURES_DEFINED

#include <queue>
#include <utility>
#include <functional>

#include "assert.h"

#include "graph_algorithms.h"

namespace cg3 {

namespace internal {
    template <class T>
    void executeDijkstra(
            Graph<T>& graph,
            const std::vector<typename Graph<T>::NodeIterator>& nodes,
            const std::vector<std::list<size_t>>& nodeAdjacencies,
            const size_t sourceId,
            std::vector<double>& dist,
            std::vector<long long int>& pred);

    template <class T>
    void fillIndexedData(
            Graph<T>& graph,
            std::vector<typename Graph<T>::NodeIterator>& nodes,
            std::vector<std::list<size_t>>& nodeAdjacencies,
            std::map<T, size_t>& idMap);
}

/**
 * @brief Execute Dijkstra algorithm given a cg3 graph and the source. It
 * compute the shortest path between the source and all the nodes of the graph.
 * The algorithm has time complexity O(|E| + |V| log |V|)
 * @param graph Input graph
 * @param source Source node
 * @return A map that associates all the graph nodes to the shortest path from the source
 * to that node. It contains structs which contain the path (a list of nodes) and a double
 * value which represents the cost of the path. The map is implemented using the std::map,
 * hence the informations can be after retrieved in O(log |V|) complexity time.
 */
template <class T>
DijkstraResult<T> dijkstra(Graph<T>& graph, const T& source)
{
    typedef typename Graph<T>::NodeIterator NIterator;


    //Search source in the graph
    NIterator sourceIt = graph.findNode(source);
    if (sourceIt == graph.nodeIteratorEnd())
        throw std::runtime_error("Source was not found in the graph.");


    //Result to be returned
    DijkstraResult<T> resultMap;

    //Vector of nodes and adjacencies
    std::vector<NIterator> nodes;
    std::vector<std::list<size_t>> nodeAdjacencies;
    std::map<T, size_t> idMap;

    //Fill indexed data needed by dijkstra algorithm
    internal::fillIndexedData(graph, nodes, nodeAdjacencies, idMap);

    //Id of the source
    size_t sourceId = idMap.find(source)->second;
    NIterator& sourceIterator = nodes[sourceId];

    //Vector of distances and predecessor of the shortest path from the source
    std::vector<double> dist;
    std::vector<long long int> pred;

    //Execute Dijkstra
    internal::executeDijkstra(graph, nodes, nodeAdjacencies, sourceId, dist, pred);

    //Update result map
    size_t id = 0;
    for (NIterator nodeIt : nodes) {
        //If there is a path
        if (pred[id] != -1) {
            std::list<T> path;

            //Get the shortest path
            size_t idPred = id;
            while (idPred != sourceId) {
                NIterator& predIterator = nodes[idPred];
                path.push_front((T) *predIterator);

                assert(pred[idPred] >= 0);

                idPred = (size_t) pred[idPred];
            }
            path.push_front((T) *sourceIterator);

            //Create resulting object
            GraphPath<T> graphPath;
            graphPath.path = path;
            graphPath.cost = dist[id];

            //Fill map
            resultMap.insert(std::make_pair(*nodeIt, graphPath));
        }

        id++;
    }

    return resultMap;
}

/**
 * @brief Execute Dijkstra algorithm to get the shortest path from the source
 * to the destination, given a cg3 graph. The algorithm has time complexity
 * O(|E| + |V| log |V|)
 * @param graph Input graph
 * @param source Source node
 * @param destination Destination node
 * @return A struct which contains the shortest path and its cost.
 * If no path exists, then an empty path of MAX_WEIGHT cost is returned.
 * The data can be retrieved in constant time.
 */
template <class T>
GraphPath<T> dijkstra(Graph<T>& graph, const T& source, const T& destination) {
    typedef typename Graph<T>::NodeIterator NIterator;


    //Search source in the graph
    NIterator sourceIt = graph.findNode(source);
    if (sourceIt == graph.nodeIteratorEnd())
        throw std::runtime_error("Source was not found in the graph.");

    //Search destination in the graph
    NIterator destinationIt = graph.findNode(destination);
    if (destinationIt == graph.nodeIteratorEnd())
        throw std::runtime_error("Destination was not found in the graph.");


    //Vector of nodes and adjacencies
    std::vector<NIterator> nodes;
    std::vector<std::list<size_t>> nodeAdjacencies;
    std::map<T, size_t> idMap;

    //Fill indexed data needed by dijkstra algorithm
    internal::fillIndexedData(graph, nodes, nodeAdjacencies, idMap);

    //Id of the source
    size_t sourceId = idMap.find(source)->second;    
    NIterator& sourceIterator = nodes[sourceId];

    //Id of the destination
    size_t destinationId = idMap.find(destination)->second;

    //Vector of distances and predecessor of the shortest path from the source
    std::vector<double> dist;
    std::vector<long long int> pred;

    //Execute Dijkstra
    internal::executeDijkstra(graph, nodes, nodeAdjacencies, sourceId, dist, pred);


    //Get the shortest path
    std::list<T> path;
    if (pred[destinationId] != -1) {
        //Create path
        size_t idPred = destinationId;
        while (idPred != sourceId) {
            NIterator& predIterator = nodes[idPred];
            path.push_front((T) *predIterator);

            assert(pred[idPred] >= 0);

            idPred = (size_t) pred[idPred];
        }
        path.push_front((T) *sourceIterator);
    }

    //Create resulting object
    GraphPath<T> graphPath;
    graphPath.path = path;
    graphPath.cost = dist[destinationId];

    return graphPath;
}


namespace internal {

/**
 * @brief Execute dijkstra algorithm
 * @param[in] graph Input graph
 * @param[in] nodes List of node iterators of the graph (indexed)
 * @param[in] nodeAdjacencies Indexed adjacencies of each graph node
 * @param[in] sourceId Id of the source
 * @param[out] dist Vector of shortest path costs from the source to each node
 * @param[out] pred Vector for predecessors to compute the path
 */
template <class T>
void executeDijkstra(
        Graph<T>& graph,
        const std::vector<typename Graph<T>::NodeIterator>& nodes,
        const std::vector<std::list<size_t>>& nodeAdjacencies,
        const size_t sourceId,
        std::vector<double>& dist,
        std::vector<long long int>& pred)
{
    typedef typename Graph<T>::NodeIterator NIterator;
    typedef std::pair<double, size_t> QueueObject;

    size_t numberOfNodes = nodes.size();

    dist.resize(numberOfNodes, Graph<T>::MAX_WEIGHT);
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

        //Getting node iterator
        const NIterator& uIterator = nodes[uId];

        for (size_t vId : nodeAdjacencies[uId]) {
            //Getting adjacent node iterator
            const NIterator& vIterator = nodes[vId];

            //Get weight
            double weight = graph.getWeight(uIterator, vIterator);

            assert(dist[uId] < Graph<T>::MAX_WEIGHT);

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

/**
 * @brief Fill dijkstra indexed data structure needed by the algorithm
 * @param[in] graph Input graph
 * @param[out] nodes List of node iterators of the graph (indexed)
 * @param[out] nodeAdjacencies Indexed adjacencies of each graph node
 * @param[out] idMap Map to get the index of a node
 */
template <class T>
void fillIndexedData(
        Graph<T>& graph,
        std::vector<typename Graph<T>::NodeIterator>& nodes,
        std::vector<std::list<size_t>>& nodeAdjacencies,
        std::map<T, size_t>& idMap)
{
    typedef typename Graph<T>::NodeIterator NIterator;

    size_t id;

    //Fill vector of iterators for the nodes
    id = 0;
    for (NIterator nodeIt = graph.nodeIteratorBegin(); nodeIt != graph.nodeIteratorEnd(); ++nodeIt) {
        idMap.insert(std::make_pair(*nodeIt, id));
        nodes.push_back(nodeIt);
        id++;
    }

    //Fill vector of adjacencies
    nodeAdjacencies.resize(nodes.size());

    id = 0;
    for (NIterator nodeIt : nodes) {
        std::list<size_t>& adjList = nodeAdjacencies[id];

        //For each adjacent node
        for (const T& adjNode : graph.adjacentNodeIterator(nodeIt)) {
            typename std::map<T, size_t>::iterator findIdIt = idMap.find(adjNode);
            size_t adjId = findIdIt->second;

            adjList.push_back(adjId);
        }

        id++;
    }
}

}

}

#endif

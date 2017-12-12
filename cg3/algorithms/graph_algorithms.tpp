/**
    @author Stefano Nuvoli
*/
#ifdef CG3_DATA_STRUCTURES_DEFINED

#include <queue>
#include <utility>

#include "assert.h"

#include "graph_algorithms.h"

namespace cg3 {

/**
 * @brief Execute Dijkstra algorithm given a cg3 graph and the source
 * @param graph Input graph
 * @param source Source of the graph
 * @return A map that associates a given node to the path starting from the source.
 * It is a
 */
template <class T>
DijkstraResult<T> dijkstra(Graph<T>& graph, const T& source)
{
    typedef typename Graph<T>::NodeIterator NIterator;
    typedef std::pair<double, unsigned int> QueueObject;
    unsigned int id;

    //Result to be returned
    DijkstraResult<T> resultMap;

    //Search source in the graph
    NIterator sourceIt = graph.findNode(source);
    if (sourceIt == graph.nodeIteratorEnd())
        throw std::runtime_error("Source was not found in the graph.");



    //Map for id of the object
    std::map<T, unsigned int> idMap;

    //Vector of iterators for the nodes
    std::vector<NIterator> nodes;
    id = 0;
    for (NIterator nodeIt = graph.nodeIteratorBegin(); nodeIt != graph.nodeIteratorEnd(); ++nodeIt) {
        idMap.insert(std::make_pair(*nodeIt, id));
        nodes.push_back(nodeIt);
        id++;
    }

    //Vector of adjacencies
    std::vector<std::list<unsigned int>> nodeAdjacencies(nodes.size());
    id = 0;
    for (NIterator nodeIt : nodes) {
        std::list<unsigned int>& adjList = nodeAdjacencies[id];

        //For each adjacent node
        for (const T& adjNode : graph.adjacentNodeIterator(nodeIt)) {
            typename std::map<T, unsigned int>::iterator findIdIt = idMap.find(adjNode);
            unsigned int adjId = findIdIt->second;

            adjList.push_back(adjId);
        }

        id++;
    }

    //Id of the source
    unsigned int sourceId = idMap.find(source)->second;

    //Vector of distances from the source
    std::vector<double> dist(nodes.size(), Graph<int>::MAX_WEIGHT);
    dist[sourceId] = 0;

    //Vector of predecessor from the source
    std::vector<double> pred(nodes.size(), -1);
    pred[sourceId] = sourceId;

    //Priority queue
    std::priority_queue<QueueObject, std::vector<QueueObject>, std::greater<QueueObject>> queue;

    queue.push(std::make_pair(0, sourceId));

    while (!queue.empty()) {
        //Get iterator on the queue and pop it from it
        const QueueObject& qObject = queue.top();
        unsigned int uId = qObject.second;

        queue.pop();

        //Getting node iterator
        NIterator& uIterator = nodes[uId];

        for (unsigned int vId : nodeAdjacencies[uId]) {
            //Getting adjacent node iterator
            NIterator& vIterator = nodes[vId];

            //Get weight
            double weight = graph.getWeight(uIterator, vIterator);

            assert(dist[uId] < Graph<int>::MAX_WEIGHT);

            //If there is short path to v through u.
            if (dist[vId] > dist[uId] + weight)
            {
                //Update distance of v
                dist[vId] = dist[uId] + weight;

                //Set predecessor
                pred[vId] = uId;

                //Add to the queue
                queue.push(std::make_pair(dist[vId], vId));
            }
        }
    }

    //Update result map
    id = 0;
    for (NIterator nodeIt : nodes) {
        //If there is a path
        if (pred[id] != -1) {
            std::list<T> path;

            //Create path
            unsigned int idPred = id;
            while (idPred != sourceId) {
                NIterator& predIterator = nodes[idPred];
                path.push_front(*predIterator);

                idPred = pred[idPred];
            }
            path.push_front(sourceId);

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

}

#endif

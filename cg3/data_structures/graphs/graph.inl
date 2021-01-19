/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */
#include "graph.h"

#include "assert.h"

namespace cg3 {

/* ----- CONST ----- */

template <class T>
constexpr double Graph<T>::MAX_WEIGHT;


/* ----- CONSTRUCTORS/DESTRUCTORS ----- */

/**
 * @brief Default constructor
 */
template <class T>
Graph<T>::Graph(const GraphType& type, const GraphMapping& mapping) :
    type(type),
    mapping(mapping),
    nDeletedNodes(0)
{

}


/* ----- PUBLIC METHODS WITH VALUES ----- */


/**
 * @brief Add a node to the graph
 * @param[in] o Object of the node
 * @return Iterator to the node if it has been inserted,
 * end iterator otherwise
 */
template <class T>
typename Graph<T>::NodeIterator Graph<T>::addNode(const T& o)
{
    //Create new node
    size_t newId = nodes.size();
    Node newNode(o, newId);

    if (this->mapping == MAPPED) {
        //If node does exists, return end of node iterator
        typename std::map<T, size_t>::iterator mapIt = map.find(o);
        if (mapIt != map.end())
            return this->nodeEnd();

        map[o] = newId;
    }

    nodes.push_back(newNode);
    isDeleted.push_back(false);

    return NodeIterator(this, --this->nodes.end());
}

/**
 * @brief Delete a node from the graph (lazy approach, it just sets a
 * flag)
 * @param[in] o Object of the node
 * @return True if the element has been deleted, false otherwise
 */
template <class T>
bool Graph<T>::deleteNode(const T& o)
{
    if (this->mapping != MAPPED)
        throw std::runtime_error("The graph is not mapped. Please use iterators or change mapping type.");

    //If node does not exists, return false
    typename std::map<T, size_t>::iterator mapIt = map.find(o);
    if (mapIt == map.end())
        return false;

    size_t nodeId = mapIt->second;

    //Setting node as deleted
    isDeleted[nodeId] = true;

    //Erase from map
    map.erase(mapIt);

    //Recompact after a defined number of delete operations
    nDeletedNodes++;
    if (nDeletedNodes >= NUMBER_DELETE_FOR_RECOMPACT) {
        this->recompact();
    }
    
    return true;
}

/**
 * @brief Find a node in the graph with a given object
 * @param[in] o Object of the node
 * @return Iterator to the node if it exists, end iterator otherwise
 */
template <class T>
typename Graph<T>::NodeIterator Graph<T>::findNode(const T& o) const
{
    if (this->mapping != MAPPED)
        throw std::runtime_error("The graph is not mapped. Please use iterators or change mapping type.");

    long long int id = findNodeHelper(o);
    if (id < 0)
        return this->nodeEnd();

    typename std::vector<Node>::const_iterator vecIt = this->nodes.begin();
    std::advance(vecIt, id);

    return NodeIterator(this, vecIt);
}

/**
 * @brief Add an edge to the graph
 * @param[in] o1 Object of the node 1
 * @param[in] o2 Object of the node 2
 * @return True if the edge has been inserted, false if it was not possible
 * to insert the edge because the corresponding objects have not been found.
 */
template <class T>
bool Graph<T>::addEdge(const T& o1, const T& o2, const double weight)
{
    if (this->mapping != MAPPED)
        throw std::runtime_error("The graph is not mapped. Please use iterators or change mapping type.");

    //If one of the nodes does not exists, return false
    long long int id1 = findNodeHelper(o1);
    if (id1 < 0)
        return false;
    long long int id2 = findNodeHelper(o2);
    if (id2 < 0)
        return false;

    addEdgeHelper(id1, id2, weight);
    if (type == GraphType::UNDIRECTED)
        addEdgeHelper(id2, id1, weight);

    return true;
}


/**
 * @brief Delete an edge from the graph
 * @param[in] o1 Object of the node 1
 * @param[in] o2 Object of the node 2
 * @return True if the edge has been deleted, false if it was not possible
 * to insert the edge because the corresponding objects have not been found.
 */
template <class T>
bool Graph<T>::deleteEdge(const T& o1, const T& o2)
{
    if (this->mapping != MAPPED)
        throw std::runtime_error("The graph is not mapped. Please use iterators or change mapping type.");

    //If one of the nodes does not exists, return false
    long long int id1 = findNodeHelper(o1);
    if (id1 < 0)
        return false;
    long long int id2 = findNodeHelper(o2);
    if (id2 < 0)
        return false;

    deleteEdgeHelper(id1, id2);
    if (type == GraphType::UNDIRECTED)
        deleteEdgeHelper(id2, id1);

    return true;
}

/**
 * @brief Check if two nodes are adjacent
 * @param[in] o1 Object of the node 1
 * @param[in] o2 Object of the node 2
 * @return True if the nodes are adjacent, false otherwise. False is returned
 * if one of the objects have not been found
 */
template <class T>
bool Graph<T>::isAdjacent(const T& o1, const T& o2) const
{
    if (this->mapping != MAPPED)
        throw std::runtime_error("The graph is not mapped. Please use iterators or change mapping type.");

    //If node does not exists, return false
    long long int id1 = findNodeHelper(o1);
    if (id1 < 0)
        return false;
    long long int id2 = findNodeHelper(o2);
    if (id2 < 0)
        return false;

    return isAdjacentHelper(id1, id2);
}


/**
 * @brief Get the weight of an edge between to nodes.
 * It returns MAX_WEIGHT if the nodes are not adjacent
 * or the nodes cannot be found.
 *
 * @param[in] o1 Object of the node 1
 * @param[in] o2 Object of the node 2
 * @return Weight of the edge, MAX_WEIGHT if nodes are not adjacent
 * or the nodes cannot be found
 */
template <class T>
double Graph<T>::getWeight(const T& o1, const T& o2) const
{
    if (this->mapping != MAPPED)
        throw std::runtime_error("The graph is not mapped. Please use iterators or change mapping type.");

    //If one of the nodes does not exists, return max weight
    long long int id1 = findNodeHelper(o1);
    if (id1 < 0)
        return MAX_WEIGHT;
    long long int id2 = findNodeHelper(o2);
    if (id2 < 0)
        return MAX_WEIGHT;

    return getWeightHelper(id1, id2);
}


/**
 * @brief Set the weight of the edge between two nodes. If the edge does not
 * exist or one of the nodes do not exist, no changes are done.
 * @param[in] o1 Object of the node 1
 * @param[in] o2 Object of the node 2
 */
template <class T>
void Graph<T>::setWeight(const T& o1, const T& o2, const double weight)
{
    if (this->mapping != MAPPED)
        throw std::runtime_error("The graph is not mapped. Please use iterators or change mapping type.");

    //If one of the nodes does not exists, return
    long long int id1 = findNodeHelper(o1);
    if (id1 < 0)
        return;
    long long int id2 = findNodeHelper(o2);
    if (id2 < 0)
        return;

    setWeightHelper(id1, id2, weight);
    if (type == GraphType::UNDIRECTED)
        setWeightHelper(id2, id1, weight);
}




/* ----- PUBLIC METHODS WITH ITERATORS ----- */


/**
 * @brief Delete node from the graph given the node iterator.
 * Note that you should use this function when you are sure
 * that the iterator is pointing to an element which is in the
 * graph.
 * @param[in] it Iterator to the node
 * @return True if the node has been deleted, false if the corresponding
 * object has not been found.
 */
template <class T>
bool Graph<T>::deleteNode(GenericNodeIterator it)
{
    size_t nodeId = it.id;
    if (this->mapping == MAPPED) {
        return deleteNode(nodes.at(nodeId).value);
    }
    else {
        if (!isDeleted[nodeId]) {
            //Setting node as deleted
            isDeleted[nodeId] = true;

            //Recompact after a defined number of delete operations
            nDeletedNodes++;
            if (nDeletedNodes >= NUMBER_DELETE_FOR_RECOMPACT) {
                this->recompact();
            }

            return true;
        }
        else {
            return false;
        }
    }
}

/**
 * @brief Add edge in the graph given the node iterators.
 * Note that you should use this function when you are sure
 * that the iteratos are pointing to an element which is in the
 * graph.
 * @param[in] it1 Iterator to node 1
 * @param[in] it2 Iterator to node 2
 */
template <class T>
void Graph<T>::addEdge(GenericNodeIterator it1, GenericNodeIterator it2, const double weight)
{
    if (isDeleted[it1.id] || isDeleted[it2.id])
        return;

    addEdgeHelper(it1.id, it2.id, weight);
    if (type == GraphType::UNDIRECTED)
        addEdgeHelper(it2.id, it1.id, weight);
}

/**
 * @brief Delete edge from the graph given the node iterators.
 * Note that you should use this function when you are sure
 * that the iteratos are pointing to an element which is in the
 * graph.
 * @param[in] it1 Iterator to node 1
 * @param[in] it2 Iterator to node 2
 */
template <class T>
void Graph<T>::deleteEdge(GenericNodeIterator it1, const GenericNodeIterator it2)
{
    if (isDeleted[it1.id] || isDeleted[it2.id])
        return;

    deleteEdgeHelper(it1.id, it2.id);
    if (type == GraphType::UNDIRECTED)
        deleteEdgeHelper(it2.id, it1.id);
}


/**
 * @brief Check if two nodes are adjacent given the iterators.
 * Note that you should use this function when you are sure
 * that the iterators are pointing to an element which is in the
 * graph.
 * @param[in] it1 Iterator to node 1
 * @param[in] it2 Iterator to node 2
 * @return True if the nodes are adjacent, false otherwise
 */
template <class T>
bool Graph<T>::isAdjacent(const GenericNodeIterator it1, const GenericNodeIterator it2) const
{
    if (isDeleted[it1.id] || isDeleted[it2.id])
        return false;

    return isAdjacentHelper(it1.id, it2.id);
}

/**
 * @brief Check if two nodes are adjacent given the iterators.
 * It returns MAX_WEIGHT if node are not adjacent.
 * Note that you should use this function when you are sure
 * that the iterators are pointing to an element which is in the
 * graph.
 * @param[in] it1 Iterator to node 1
 * @param[in] it2 Iterator to node 2
 * @return Weight of the edge, MAX_WEIGHT if nodes are not adjacent
 */
template <class T>
double Graph<T>::getWeight(const GenericNodeIterator it1, const GenericNodeIterator it2) const
{
    if (isDeleted[it1.id] || isDeleted[it2.id])
        return MAX_WEIGHT;

    return getWeightHelper(it1.id, it2.id);
}


/**
 * @brief Set the weight of an edge between two nodes.
 * Note that you should use this function when you are sure
 * that the iterators are pointing to an element which is in the
 * graph. If the edge does not exist, no changes are done
 * @param[in] it1 Iterator to node 1
 * @param[in] it2 Iterator to node 2
 * @param[in] weight New weight of the edge
 */
template <class T>
void Graph<T>::setWeight(GenericNodeIterator it1, GenericNodeIterator it2, const double weight)
{
    if (isDeleted[it1.id] || isDeleted[it2.id])
        return;

    setWeightHelper(it1.id, it2.id, weight);
    if (type == GraphType::UNDIRECTED)
        setWeightHelper(it2.id, it1.id, weight);
}




/* ----- UTILITY METHODS ----- */


/**
 * @brief Get id of the node by iterator
 * @param iterator Iterator
 * @return Id of the node
 */
template <class T>
size_t Graph<T>::getId(const GenericNodeIterator iterator) const {
    return iterator.id;
}

/**
 * @brief Get node iterator by id
 * @param id Id of the node
 * @return Iterator
 */
template <class T>
typename Graph<T>::NodeIterator Graph<T>::getNode(const size_t id) const {
    if (isDeleted[id])
        return nodeEnd();
    return NodeIterator(this, nodes.begin() + id);
}


/**
 * @brief Get the number of nodes of the graph
 * @return Number of nodes
 */
template <class T>
size_t Graph<T>::numNodes() const
{
    size_t numNodes = std::distance(this->nodeBegin(), this->nodeEnd());
    return numNodes;
}

/**
 * @brief Get the number of edges of the graph
 * @return Number of edges
 */
template <class T>
size_t Graph<T>::numEdges() const
{
    size_t numEdges = std::distance(this->edgeBegin(), this->edgeEnd());
    return numEdges;
}

/**
 * @brief Clear the graph.
 * It deletes all the nodes and clear the element map
 */
template <class T>
void Graph<T>::clear()
{
    //Clear nodes and map
    nodes.clear();
    map.clear();

    isDeleted.clear();
    nDeletedNodes = 0;
}

/**
 * @brief Recompact the graph, deleting all deleted nodes
 * and adjacencies with them.
 * It is needed in order to save memory when several nodes
 * have been deleted.
 */
template <class T>
void Graph<T>::recompact()
{
    //Vector to keep track in which index the nodes have been placed.
    std::vector<long long int> indexMap(this->nodes.size(), -1);

    //New graph data
    std::vector<Node> newNodes;
    std::map<T, size_t> newMap;
    std::vector<bool> newIsDeleted;

    //Create new vector of nodes
    size_t newIndex = 0;
    for (size_t i = 0; i < nodes.size(); i++) {
        if (!isDeleted[i]) {
            //Copy new node
            Node newNode = nodes[i];

            //Set new data
            newNode.id = newIndex;
            newNodes.push_back(newNode);
            newIsDeleted.push_back(false);

            if (this->mapping == MAPPED) {
                newMap[newNode.value] = newIndex;
            }

            //Setting references
            indexMap[i] = (long long int) newIndex;

            newIndex++;
        }
    }

    //Set edges in each node map
    for (size_t i = 0; i < nodes.size(); i++) {
        if (!isDeleted[i]) {
            const Node& node = nodes[i];

            //New adjacency data
            std::unordered_map<size_t, double> newAdjacentNodes;

            //For each adjacency entry
            const std::unordered_map<size_t, double>& adjacencyMap = node.adjacentNodes;
            for (std::unordered_map<size_t, double>::const_iterator it = adjacencyMap.begin();
                 it != adjacencyMap.end();
                 it++)
            {
                //If the target node has not been deleted
                if (!isDeleted[it->first]) {
                    //Set new adjacency
                    newAdjacentNodes[indexMap[it->first]] = it->second;
                }
            }

            //Move adjacency map in the node
            assert(indexMap[i] >= 0);
            Node& currentNode = newNodes[(size_t) indexMap[i]];
            currentNode.adjacentNodes = std::move(newAdjacentNodes);
        }

    }

    //Move new data
    this->nodes = std::move(newNodes);
    this->map = std::move(newMap);
    this->isDeleted = std::move(newIsDeleted);
    this->nDeletedNodes = 0;
}

/* ----- SERIALIZATION ----- */

/**
 * @brief Serialization of a Graph of nodes of type T (serialization of objects of type T must be provided) in
 * a binary file.
 *
 * @param binaryFile: the binary file on which the graph will be stored.
 */
template<class T>
void Graph<T>::serialize(std::ofstream& binaryFile) const
{
    cg3::serializeObjectAttributes("cg3Graph", binaryFile, type, nodes, map, isDeleted, nDeletedNodes);
    cg3::serialize(mapping, binaryFile);
}

/**
 * @brief Deerialization of a Graph of nodes of type T (serialization of objects of type T must be provided)
 * from a binary file.
 *
 * @param binaryFile: the binary file from which the graph will be loaded.
 */
template<class T>
void Graph<T>::deserialize(std::ifstream& binaryFile)
{
    cg3::deserializeObjectAttributes("cg3Graph", binaryFile, type, nodes, map, isDeleted, nDeletedNodes);
    try {
        cg3::deserialize(mapping, binaryFile);
    } catch (...) { // old version without "mapping" member, default was MAPPED
        mapping = MAPPED;
    }
}

/* ----- ITERATORS ----- */


/* Node iterators */

/**
 * @brief Begin iterator. Wrapper for node iterator
 * @return Iterator
 */
template <class T>
typename Graph<T>::NodeIterator Graph<T>::begin() const
{
    return nodeBegin();
}

/**
 * @brief End iterator. Wrapper for node iterator
 * @return Iterator
 */
template <class T>
typename Graph<T>::NodeIterator Graph<T>::end() const
{
    return nodeEnd();
}


/**
 * @brief Begin node iterator
 * @return Iterator
 */
template <class T>
typename Graph<T>::NodeIterator Graph<T>::nodeBegin() const
{
    typename std::vector<Node>::const_iterator it = nodes.begin();
    //Get first valid node iterator
    return NodeIterator(this, getFirstValidIteratorNode(it));
}

/**
 * @brief End node iterator
 * @return Iterator
 */
template <class T>
typename Graph<T>::NodeIterator Graph<T>::nodeEnd() const
{
    return NodeIterator(this, this->nodes.end());
}

/**
 * @brief Get range based node iterator of the graph
 * @return Range based node iterator
 */
template <class T>
typename Graph<T>::RangeBasedNodeIterator Graph<T>::nodeIterator() const
{
    return RangeBasedNodeIterator(this);
}



/* Adjacent node iterators */

/**
 * @brief Begin adjacent node iterator. The user should avoid to give as
 * argument a node iterator pointing to a deleted element or to the end
 * iterator.
 * @param[in] nodeIt Iterator of the node
 * @return Iterator
 */
template <class T>
typename Graph<T>::AdjacentIterator Graph<T>::adjacentBegin(
        NodeIterator nodeIt) const
{
    //Get first valid adjacent iterator
    return AdjacentIterator(
                this,
                nodeIt,
                getFirstValidIteratorAdjacent(
                    nodeIt,
                    nodes.at((size_t) nodeIt.id).adjacentNodes.begin()));
}

/**
 * @brief End adjacent node iterator. The user should avoid to give as
 * argument a node iterator pointing to a deleted element or to the end
 * iterator.
 * @param[in] nodeIt Iterator of the node
 * @return Iterator
 */
template <class T>
typename Graph<T>::AdjacentIterator Graph<T>::adjacentEnd(
        NodeIterator nodeIt) const
{
    return AdjacentIterator(
                this,
                nodeIt,
                nodes.at((size_t) nodeIt.id).adjacentNodes.end());
}


/**
 * @brief Get range based adjacent node iterator of the graph given a node.
 * The user should avoid to give as argument a node iterator pointing to a
 * deleted element or to the end iterator.
 * @param[in] nodeIt Iterator of the node
 * @return Range based node iterator
 */
template <class T>
typename Graph<T>::RangeBasedAdjacentIterator Graph<T>::adjacentIterator(
        NodeIterator nodeIt) const
{
    return RangeBasedAdjacentIterator(this, nodeIt);
}



/**
 * @brief Begin adjacent node iterator. The user should avoid to give as
 * argument a node iterator pointing to a deleted element or to the end
 * iterator.
 * @param[in] nodeIt Iterator of the node
 * @return Iterator
 */
template <class T>
typename Graph<T>::AdjacentIterator Graph<T>::adjacentBegin(
        AdjacentIterator nodeIt) const
{
    return adjacentBegin(NodeIterator(this, nodes.begin() + nodeIt.id));
}

/**
 * @brief End adjacent node iterator. The user should avoid to give as
 * argument a node iterator pointing to a deleted element or to the end
 * iterator.
 * @param[in] nodeIt Iterator of the node
 * @return Iterator
 */
template <class T>
typename Graph<T>::AdjacentIterator Graph<T>::adjacentEnd(
        AdjacentIterator nodeIt) const
{
    return adjacentEnd(NodeIterator(this, nodes.begin() + nodeIt.id));
}


/**
 * @brief Get range based adjacent node iterator of the graph given a node.
 * The user should avoid to give as argument a node iterator pointing to a
 * deleted element or to the end iterator.
 * @param[in] nodeIt Iterator of the node
 * @return Range based node iterator
 */
template <class T>
typename Graph<T>::RangeBasedAdjacentIterator Graph<T>::adjacentIterator(
        AdjacentIterator nodeIt) const
{
    return RangeBasedAdjacentIterator(this, nodes.begin() + nodeIt.id);
}



/**
 * @brief Begin adjacent node iterator
 * @param[in] o Object of the node
 * @return Iterator
 */
template <class T>
typename Graph<T>::AdjacentIterator Graph<T>::adjacentBegin(const T& o) const
{
    return this->adjacentBegin(this->findNode(o));
}

/**
 * @brief End adjacent node iterator
 * @param[in] o Object of the node
 * @return Iterator
 */
template <class T>
typename Graph<T>::AdjacentIterator Graph<T>::adjacentEnd(const T& o) const
{
    return this->adjacentEnd(this->findNode(o));
}

/**
 * @brief Get range based adjacent node iterator of the graph given a node
 * @param[in] o Object of the node
 * @return Range based node iterator
 */
template <class T>
typename Graph<T>::RangeBasedAdjacentIterator Graph<T>::adjacentIterator(const T& o) const
{
    return this->adjacentIterator(this->findNode(o));
}




/* Edge iterators */

/**
 * @brief Begin edge iterator
 * @return Iterator
 */
template <class T>
typename Graph<T>::EdgeIterator Graph<T>::edgeBegin() const
{
    //Get first candidate iterator
    NodeIterator nodeIt = this->nodeBegin();

    if (nodeIt == this->nodeEnd())
        return this->edgeEnd();

    AdjacentIterator adjIt = this->adjacentBegin(nodeIt);

    //Get first valid edge iterator
    AdjacentIterator newAdjIt(this);
    NodeIterator newNodeIt(this);
    this->getFirstValidIteratorEdge(nodeIt, adjIt, newNodeIt, newAdjIt);

    return EdgeIterator(this, newNodeIt, newAdjIt);
}

/**
 * @brief End edge iterator
 * @return Iterator
 */
template <class T>
typename Graph<T>::EdgeIterator Graph<T>::edgeEnd() const
{
    return EdgeIterator(
                this,
                NodeIterator(this), //This will point to end iterator of nodes
                AdjacentIterator(this)); //This will point to an empty iterator of the unordered_map
}

/**
 * @brief Get range based edge iterator of the graph
 * @return Range based edge iterator
 */
template <class T>
typename Graph<T>::RangeBasedEdgeIterator Graph<T>::edgeIterator() const
{
    return RangeBasedEdgeIterator(this);
}




/* ----- PRIVATE FUNCTIONS FOR ITERATORS ----- */


/**
 * @brief Get the first valid (pointing to a not deleted node)
 * node iterator starting from the input one
 * @param[in] it Input node iterator
 * @return Valid node iterator
 */
template <class T>
typename std::vector<typename Graph<T>::Node>::const_iterator Graph<T>::getFirstValidIteratorNode(
        typename std::vector<Node>::const_iterator it) const
{
    while (it != nodes.end() &&
           isDeleted[it->id])
    {
        it++;
    }

    return it;
}

/**
 * @brief Get the first valid (pointing to a not deleted node)
 * adjacent node iterator starting from the input one
 * @param[in] nodeIt Target node iterator
 * @param[in] it Input adjacent node iterator
 * @return Valid adjacent node iterator
 */
template<class T>
std::unordered_map<size_t, double>::const_iterator Graph<T>::getFirstValidIteratorAdjacent(
        NodeIterator nodeIt,
        std::unordered_map<size_t, double>::const_iterator it) const
{
    while (it != nodes.at((size_t) nodeIt.id).adjacentNodes.end() &&
           isDeleted[it->first])
    {
        it++;
    }

    return it;
}

/**
 * @brief Get the first valid (pointing to a not deleted node)
 * edge iterator starting from the input one
 * @param[in] nodeIt Input node iterator
 * @param[in] adjIt Input adjacent node iterator
 * @param[out] nodeIt Output node iterator
 * @param[out] adjIt Output adjacent node iterator
 */
template<class T>
void Graph<T>::getFirstValidIteratorEdge(
        NodeIterator nodeIt,
        AdjacentIterator adjIt,
        NodeIterator& newNodeIt,
        AdjacentIterator& newAdjIt) const
{
    while (adjIt == this->adjacentEnd(nodeIt)) {
        nodeIt++;

        if (nodeIt == this->nodeEnd()) {
            newNodeIt = NodeIterator(this);
            newAdjIt = AdjacentIterator(this);

            return;
        }

        adjIt = this->adjacentBegin(nodeIt);
    }
    newNodeIt = nodeIt;
    newAdjIt = adjIt;
}





/* ----- HELPERS ----- */

/**
 * @brief Find a node in the graph given the object
 * @param[in] o Object of the node
 * @return Index of the node in the node vector, -1 if the node
 * is not in the graph
 */
template <class T>
long long int Graph<T>::findNodeHelper(const T& o) const {
    //If node does not exists, return -1
    typename std::map<T, size_t>::const_iterator mapIt = map.find(o);
    if (mapIt == this->map.end())
        return -1;

    //Retrieve id
    const size_t& id = mapIt->second;

    return (long long int) id;
}

/**
 * @brief Add an edge in the graph given the index of the nodes
 * @param[in] id1 Index of the first node
 * @param[in] id2 Index of the second node
 */
template <class T>
void Graph<T>::addEdgeHelper(const size_t& id1, const size_t& id2, const double weight)
{
    if (!isDeleted[id2]) {
        Node& n1 = this->nodes.at(id1);

        std::unordered_map<size_t, double>::iterator it = n1.adjacentNodes.find(id2);

        if (it == n1.adjacentNodes.end()) {
            n1.adjacentNodes.insert(std::make_pair(id2, weight));
        }
        else {
            it->second = weight;
        }
    }
}

/**
 * @brief Delete an edge from the graph given the index of the nodes
 * @param[in] id1 Index of the first node
 * @param[in] id2 Index of the second node
 */
template <class T>
void Graph<T>::deleteEdgeHelper(const size_t& id1, const size_t& id2)
{
    if (!isDeleted[id2]) {
        Node& n1 = this->nodes.at(id1);
        n1.adjacentNodes.erase(id2);
    }
}


/**
 * @brief Check if two nodes are adjacent given the index of the nodes
 * @param[in] id1 Index of the first node
 * @param[in] id2 Index of the second node
 * @return True if the nodes are adjacent, false otherwise
 */
template <class T>
bool Graph<T>::isAdjacentHelper(const size_t& id1, const size_t& id2) const
{
    if (isDeleted[id1])
        return false;

    const Node& n1 = this->nodes.at(id1);
    std::unordered_map<size_t, double>::const_iterator it = n1.adjacentNodes.find(id2);

    if (it == n1.adjacentNodes.end())
        return false;

    return true;
}

/**
 * @brief Get the weight of an edge between two nodes given their indices.
 * It returns MAX_WEIGHT if the nodes are not adjacent
 *
 * @param[in] id1 Index of the first node
 * @param[in] id2 Index of the second node
 * @return Weight of the edge, MAX_WEIGHT if the nodes are not adjacent
 */
template <class T>
double Graph<T>::getWeightHelper(const size_t& id1, const size_t& id2) const
{
    const Node& n1 = this->nodes.at(id1);

    std::unordered_map<size_t, double>::const_iterator it = n1.adjacentNodes.find(id2);
    if (it == n1.adjacentNodes.end())
        return MAX_WEIGHT;
    else
        return it->second;
}

/**
 * @brief Set the weight of an edge between two nodes given their indices
 * @param[in] id1 Index of the first node
 * @param[in] id2 Index of the second node
 * @param[in] weight Weight of the edge
 */
template <class T>
void Graph<T>::setWeightHelper(const size_t& id1, const size_t& id2, const double weight)
{
    Node& n1 = this->nodes.at(id1);

    std::unordered_map<size_t, double>::iterator it = n1.adjacentNodes.find(id2);
    if (it == n1.adjacentNodes.end())
        return;

    it->second = weight;
}





}

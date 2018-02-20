/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */
#include "graph.h"

namespace cg3 {

/* ----- CONST ----- */

template <class T>
constexpr double Graph<T>::MAX_WEIGHT;


/* ----- CONSTRUCTORS/DESTRUCTORS ----- */

/**
 * @brief Default constructor
 */
template <class T>
Graph<T>::Graph(GraphType type) :
    type(type),
    nDeletedNodes(0)
{

}

/**
 * @brief Copy constructor
 * @param graph Graph
 */
template <class T>
Graph<T>::Graph(const Graph& graph) :
    type(graph.type),
    map(graph.map),
    nDeletedNodes(graph.nDeletedNodes)
{
    //Vector resizing
    this->nodes.resize(graph.nodes.size());

    #pragma omp parallel for
    for (size_t i = 0; i < graph.nodes.size(); i++) {
        Node* node = graph.nodes[i];

        //Create new node if the current one is not nullptr
        Node* copyNode = nullptr;
        if (node != nullptr) {
            copyNode = new Node(*node);
        }

        this->nodes[i] = copyNode;
    }
}

/**
 * @brief Move constructor
 * @param graph Graph
 */
template <class T>
Graph<T>::Graph(Graph<T>&& graph) {
    this->type = std::move(graph.type);
    this->nodes = std::move(graph.nodes);
    this->map = std::move(graph.map);
    this->nDeletedNodes = std::move(nDeletedNodes);
}


/**
 * @brief Destructor
 */
template <class T>
Graph<T>::~Graph() {
    this->clear();
}


/* ----- PUBLIC METHODS WITH VALUES ----- */


/**
 * @brief Add node to the graph
 * @param[in] o Object of the node
 * @return Iterator to the node if it has been inserted,
 * end iterator otherwise
 */
template <class T>
typename Graph<T>::NodeIterator Graph<T>::addNode(const T& o) {
    //If node does exists, return nullptr
    typename std::map<T, size_t>::iterator mapIt = map.find(o);
    if (mapIt != map.end())
        return this->nodeIteratorEnd();

    //Create new node
    size_t newId = nodes.size();
    Node* newNode = new Node(o, newId);

    map[o] = newId;
    nodes.push_back(newNode);

    return NodeIterator(this, newNode, newNode->id);
}

/**
 * @brief Delete node to the graph
 * @param[in] o Object of the node
 * @return True if the element has been deleted, false otherwise
 */
template <class T>
bool Graph<T>::deleteNode(const T& o) {
    //If node does not exists, return nullptr
    typename std::map<T, size_t>::iterator mapIt = map.find(o);
    if (mapIt == map.end())
        return false;

    //Delete the node
    Node*& node = nodes.at(mapIt->second);

    nodes[node->id] = nullptr;
    delete node;

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
 * @brief Find a node in the graph
 * @param[in] o Object of the node
 * @return Iterator to the node if it exists, end iterator otherwise
 */
template <class T>
typename Graph<T>::NodeIterator Graph<T>::findNode(const T& o) {
    Node* node = findNodeHelper(o);

    if (node == nullptr)
        return this->nodeIteratorEnd();

    typename std::vector<Node*>::iterator it = nodes.begin();
    std::advance(it, node->id);

    return NodeIterator(this, node, node->id);
}

/**
 * @brief Add edge in the graph
 * @param[in] o1 Object of the node 1
 * @param[in] o2 Object of the node 2
 * @return True if the edge has been inserted, false if it was not possible
 * to insert the edge because the values have not been found.
 */
template <class T>
bool Graph<T>::addEdge(const T& o1, const T& o2, const double weight) {
    //If node does not exists, return false
    Node* node1 = findNodeHelper(o1);
    if (node1 == nullptr)
        return false;

    Node* node2 = findNodeHelper(o2);
    if (node2 == nullptr)
        return false;

    addEdgeHelper(node1, node2, weight);
    if (type == GraphType::UNDIRECTED)
        addEdgeHelper(node2, node1, weight);

    return true;
}


/**
 * @brief Delete edge from the graph
 * @param[in] o1 Object of the node 1
 * @param[in] o2 Object of the node 2
 * @return True if the edge has been deleted, false if it was not possible
 * to insert the edge because the values have not been found.
 */
template <class T>
bool Graph<T>::deleteEdge(const T& o1, const T& o2) {
    //If node does not exists, return false
    Node* node1 = findNodeHelper(o1);
    if (node1 == nullptr)
        return false;

    Node* node2 = findNodeHelper(o2);
    if (node2 == nullptr)
        return false;

    deleteEdgeHelper(node1, node2);
    if (type == GraphType::UNDIRECTED)
        deleteEdgeHelper(node2, node1);

    return true;
}

/**
 * @brief Check if two nodes are adjacent
 * @param[in] o1 Object of the node 1
 * @param[in] o2 Object of the node 2
 * @return True if the nodes are adjacent, false otherwise. False is returned
 * if one of the objects have not been returned
 */
template <class T>
bool Graph<T>::isAdjacent(const T& o1, const T& o2) const {
    //If node does not exists, return false
    Node* node1 = findNodeHelper(o1);
    if (node1 == nullptr)
        return false;

    Node* node2 = findNodeHelper(o2);
    if (node2 == nullptr)
        return false;

    return isAdjacentHelper(node1, node2);
}


/**
 * @brief Get the weight of an edge between to elements.
 * It returns MAX_WEIGHT if node are not adjacent
 * or the nodes are not in the graph
 *
 * @param[in] o1 Object of the node 1
 * @param[in] o2 Object of the node 2
 * @return Weight of the edge, MAX_WEIGHT if nodes are not adjacent
 * or the nodes are not in the graph
 */
template <class T>
double Graph<T>::getWeight(const T& o1, const T& o2) {
    //If node does not exists, return false
    Node* node1 = findNodeHelper(o1);
    if (node1 == nullptr)
        return MAX_WEIGHT;

    Node* node2 = findNodeHelper(o2);
    if (node2 == nullptr)
        return MAX_WEIGHT;

    return getWeightHelper(node1, node2);
}


/**
 * @brief Set the weight of the edge between two nodes if it
 * exists.
 * @param[in] o1 Object of the node 1
 * @param[in] o2 Object of the node 2
 */
template <class T>
void Graph<T>::setWeight(const T& o1, const T& o2, const double weight) {
    //If node does not exists, return false
    Node* node1 = findNodeHelper(o1);
    if (node1 == nullptr)
        return;

    Node* node2 = findNodeHelper(o2);
    if (node2 == nullptr)
        return;

    setWeightHelper(node1, node2, weight);
    if (type == GraphType::UNDIRECTED)
        setWeightHelper(node2, node1, weight);
}




/* ----- PUBLIC METHODS WITH ITERATORS ----- */


/**
 * @brief Delete node from the graph given the node iterators.
 * Note that you should use this function when you are sure
 * that the iterator is pointing to an element which is in the
 * graph
 * @param[in] it Iterator to the node
 */
template <class T>
bool Graph<T>::deleteNode(GenericNodeIterator it) {
    return deleteNode(it.node->value);
}

/**
 * @brief Add edge in the graph given the node iterators
 * Note that you should use this function when you are sure
 * that the iteratos are pointing to an element which is in the
 * graph
 * @param[in] it1 Iterator to node 1
 * @param[in] it2 Iterator to node 2
 */
template <class T>
void Graph<T>::addEdge(GenericNodeIterator it1, GenericNodeIterator it2, const double weight) {
    addEdgeHelper(it1.node, it2.node, weight);
    if (type == GraphType::UNDIRECTED)
        addEdgeHelper(it2.node, it1.node, weight);
}

/**
 * @brief Delete edge from the graph given the node iterators
 * Note that you should use this function when you are sure
 * that the iteratos are pointing to an element which is in the
 * graph
 * @param[in] it1 Iterator to node 1
 * @param[in] it2 Iterator to node 2
 */
template <class T>
void Graph<T>::deleteEdge(GenericNodeIterator it1, const GenericNodeIterator it2) {
    deleteEdgeHelper(it1.node, it2.node);
    if (type == GraphType::UNDIRECTED)
        deleteEdgeHelper(it2.node, it1.node);
}


/**
 * @brief Check if two nodes are adjacent given the iterators
 * Note that you should use this function when you are sure
 * that the iterators are pointing to an element which is in the
 * graph
 * @param[in] it1 Iterator to node 1
 * @param[in] it2 Iterator to node 2
 * @return True if the nodes are adjacent, false otherwise
 */
template <class T>
bool Graph<T>::isAdjacent(const GenericNodeIterator it1, const GenericNodeIterator it2) const {
    return isAdjacentHelper(it1.node, it2.node);
}

/**
 * @brief Check if two nodes are adjacent given the iterators.
 * It returns MAX_WEIGHT if node are not adjacent
 * Note that you should use this function when you are sure
 * that the iterators are pointing to an element which is in the
 * graph
 * @param[in] it1 Iterator to node 1
 * @param[in] it2 Iterator to node 2
 * @return Weight of the edge, MAX_WEIGHT if nodes are not adjacent
 */
template <class T>
double Graph<T>::getWeight(const GenericNodeIterator it1, const GenericNodeIterator it2) {
    return getWeightHelper(it1.node, it2.node);
}


/**
 * @brief Set the weight of an edge between two nodes
 * Note that you should use this function when you are sure
 * that the iterators are pointing to an element which is in the
 * graph
 * @param[in] it1 Iterator to node 1
 * @param[in] it2 Iterator to node 2
 * @param[in] weight Weight of the edge
 */
template <class T>
void Graph<T>::setWeight(GenericNodeIterator it1, GenericNodeIterator it2, const double weight) {
    setWeightHelper(it1.node, it2.node, weight);
}




/* ----- UTILITY METHODS ----- */

/**
 * @brief Get number of nodes of the graph
 * @return Number of nodes
 */
template <class T>
size_t Graph<T>::numNodes() {
    size_t numNodes = std::distance(this->nodeIteratorBegin(), this->nodeIteratorEnd());
    return numNodes;
}

/**
 * @brief Get number of edges of the graph
 * @return Number of edges
 */
template <class T>
size_t Graph<T>::numEdges() {
    size_t numEdges = std::distance(this->edgeIteratorBegin(), this->edgeIteratorEnd());
    return numEdges;
}

/**
 * @brief Clear the graph.
 * It deletes all the nodes and clear the element map
 */
template <class T>
void Graph<T>::clear() {
    //Delete nodes
    for (Node* n : nodes) {
        if (n != nullptr) {
            delete n;
        }
    }
    //Clear nodes and map
    nodes.clear();
    map.clear();
}

/**
 * @brief Recompact the graph, deleting all references to nullptr.
 * It is needed after that several nodes have been deleted to save
 * memory.
 */
template <class T>
void Graph<T>::recompact() {
    //Vector to keep track in which index the nodes have been placed.
    std::vector<int> indexMap(this->nodes.size(), -1);

    //New graph data
    std::vector<Node*> newNodes;
    std::map<T, size_t> newMap;

    //Create new vector of nodes
    size_t newIndex = 0;
    for (size_t i = 0; i < nodes.size(); i++) {
        Node* n = nodes[i];

        //If node has not been deleted
        if (n != nullptr) {
            //Set new data
            newNodes.push_back(n);
            n->id = newIndex;
            newMap[n->value] = newIndex;

            indexMap[i] = newIndex;
            newIndex++;
        }
    }

    //Set edges in each node map
    for (size_t i = 0; i < nodes.size(); i++) {
        Node* n = nodes[i];

        //If node has not been deleted
        if (n != nullptr) {
            //New adjacency data
            std::unordered_map<size_t, double> newAdjacentNodes;

            //For each adjacency entry
            std::unordered_map<size_t, double>& adjacencyMap = n->adjacentNodes;
            for (std::unordered_map<size_t, double>::iterator it = adjacencyMap.begin();
                 it != adjacencyMap.end(); it++)
            {
                //If the target node has not been deleted
                if (this->nodes.at(it->first) != nullptr) {
                    //Set new adjacency
                    newAdjacentNodes[indexMap[it->first]] = it->second;
                }
            }

            //Move adjacency map in the node
            Node* currentNode = newNodes[indexMap[i]];
            currentNode->adjacentNodes = std::move(newAdjacentNodes);
        }
    }

    //Move new data
    this->nodes = std::move(newNodes);
    this->map = std::move(newMap);

    this->nDeletedNodes = 0;
}



/* ----- ITERATORS ----- */

/* Node iterators */

/**
 * @brief Begin node iterator
 * @return Iterator
 */
template <class T>
typename Graph<T>::NodeIterator Graph<T>::nodeIteratorBegin() {
    typename std::vector<typename Graph<T>::Node*>::iterator it;
    it = nodes.begin();
    while (it != nodes.end() && *it == nullptr) {
        it++;
    }

    if (it == nodes.end())
        return this->nodeIteratorEnd();

    return NodeIterator(this, *it, (*it)->id);
}

/**
 * @brief End node iterator
 * @return Iterator
 */
template <class T>
typename Graph<T>::NodeIterator Graph<T>::nodeIteratorEnd() {
    return NodeIterator(this, nullptr, nodes.size());
}

/**
 * @brief Get range based node iterator of the graph
 * @return Range based node iterator
 */
template <class T>
typename Graph<T>::RangeBasedNodeIterator Graph<T>::nodeIterator() {
    return RangeBasedNodeIterator(this);
}




/* Edge iterators */

/**
 * @brief Begin edge iterator
 * @return Iterator
 */
template <class T>
typename Graph<T>::EdgeIterator Graph<T>::edgeIteratorBegin() {
    NodeIterator nodeIt = this->nodeIteratorBegin();

    if (nodeIt == this->nodeIteratorEnd())
        return this->edgeIteratorEnd();

    AdjacentNodeIterator adjIt = this->adjacentNodeIteratorBegin(nodeIt);

    while (adjIt == this->adjacentNodeIteratorEnd(nodeIt)) {
        nodeIt++;

        if (nodeIt == this->nodeIteratorEnd()) {
            return this->edgeIteratorEnd();
        }

        adjIt = this->adjacentNodeIteratorBegin(nodeIt);
    }

    return EdgeIterator(this, nodeIt, adjIt);
}

/**
 * @brief End edge iterator
 * @return Iterator
 */
template <class T>
typename Graph<T>::EdgeIterator Graph<T>::edgeIteratorEnd() {
    return EdgeIterator(this, this->nodeIteratorEnd(), this->adjacentNodeIteratorEnd(nullptr));
}

/**
 * @brief Get range based edge iterator of the graph
 * @return Range based edge iterator
 */
template <class T>
typename Graph<T>::RangeBasedEdgeIterator Graph<T>::edgeIterator() {
    return RangeBasedEdgeIterator(this);
}




/* Adjacent node iterators */

/**
 * @brief Begin adjacent node iterator
 * @param[in] nodeIterator Iterator of the node
 * @return Iterator
 */
template <class T>
typename Graph<T>::AdjacentNodeIterator Graph<T>::adjacentNodeIteratorBegin(NodeIterator nodeIterator) {
    Node* node = nodeIterator.node;
    return this->adjacentNodeIteratorBegin(node);
}

/**
 * @brief Begin adjacent node iterator
 * @param[in] o Object of the node
 * @return Iterator
 */
template <class T>
typename Graph<T>::AdjacentNodeIterator Graph<T>::adjacentNodeIteratorBegin(const T& o) {
    return this->adjacentNodeIteratorBegin(this->findNode(o));
}

/**
 * @brief End adjacent node iterator
 * @param[in] nodeIterator Iterator of the node
 * @return Iterator
 */
template <class T>
typename Graph<T>::AdjacentNodeIterator Graph<T>::adjacentNodeIteratorEnd(NodeIterator nodeIterator) {
    Node* node = nodeIterator.node;
    return this->adjacentNodeIteratorEnd(node);
}

/**
 * @brief End adjacent node iterator
 * @param[in] o Object of the node
 * @return Iterator
 */
template <class T>
typename Graph<T>::AdjacentNodeIterator Graph<T>::adjacentNodeIteratorEnd(const T& o) {
    return this->adjacentNodeIteratorEnd(this->findNode(o));
}

/**
 * @brief Get range based adjacent node iterator of the graph given a node
 * @param[in] nodeIterator Iterator of the node
 * @return Range based node iterator
 */
template <class T>
typename Graph<T>::RangeBasedAdjacentNodeIterator Graph<T>::adjacentNodeIterator(NodeIterator nodeIterator) {
    return RangeBasedAdjacentNodeIterator(this, nodeIterator.node);
}

/**
 * @brief Get range based adjacent node iterator of the graph given a node
 * @param[in] o Object of the node
 * @return Range based node iterator
 */
template <class T>
typename Graph<T>::RangeBasedAdjacentNodeIterator Graph<T>::adjacentNodeIterator(const T& o) {
    return this->adjacentNodeIterator(this->findNode(o));
}



/* ----- SWAP FUNCTION AND ASSIGNMENT ----- */


/**
 * @brief Assignment operator
 * @param[out] graph Parameter graph
 * @return This object
 */
template <class T>
Graph<T>& Graph<T>::operator= (Graph<T> graph) {
    swap(graph);
    return *this;
}


/**
 * @brief Swap graph with another one
 * @param[out] graph Graph to be swapped with this object
 */
template <class T>
void Graph<T>::swap(Graph<T>& graph) {
    using std::swap;
    swap(this->type, graph.type);
    swap(this->nodes, graph.nodes);
    swap(this->map, graph.map);
    swap(this->nDeletedNodes, graph.nDeletedNodes);
}


/**
 * @brief Swap graph with another one
 * @param g1 First graph
 * @param g2 Second graph
 */
template <class T>
void swap(Graph<T>& g1, Graph<T>& g2) {
    g1.swap(g2);
}



/* ----- PRIVATE FUNCTIONS FOR ITERATORS ----- */


/**
 * @brief Begin adjacent node iterator
 * @param[in] node Iterator of the node
 * @return Iterator
 */
template <class T>
typename Graph<T>::AdjacentNodeIterator Graph<T>::adjacentNodeIteratorBegin(Node* node) {
    std::unordered_map<size_t, double>& map = node->adjacentNodes;
    typename std::unordered_map<size_t, double>::iterator it = map.begin();

    while (it != map.end() && nodes.at(it->first) == nullptr) {
        it++;
    }

    if (it == map.end())
        return this->adjacentNodeIteratorEnd(node);

    return AdjacentNodeIterator(this, node, nodes.at(it->first));
}

/**
 * @brief End adjacent node iterator
 * @param[in] node Iterator of the node
 * @return Iterator
 */
template <class T>
typename Graph<T>::AdjacentNodeIterator Graph<T>::adjacentNodeIteratorEnd(Node* node) {
    return AdjacentNodeIterator(this, node, nullptr);
}




/* ----- PRIVATE FUNCTIONS ----- */

/**
 * @brief Find a node in the graph
 * @param[in] o Object of the node
 * @return Pointer to the node, nullptr if the node
 * is not in the graph
 */
template <class T>
typename Graph<T>::Node* Graph<T>::findNodeHelper(const T& o) const {
    //If node does not exists, return nullptr
    typename std::map<T, size_t>::const_iterator mapIt = map.find(o);
    if (mapIt == map.end())
        return nullptr;

    //Retrieve id
    size_t id = mapIt->second;

    return nodes.at(id);
}

/**
 * @brief Add edge in the graph given the nodes
 * @param[in] node1 Node 1
 * @param[in] node2 Node 2
 */
template <class T>
void Graph<T>::addEdgeHelper(Node* n1, const Node* n2, const double weight) {
    if (n2 != nullptr) {
        std::unordered_map<size_t, double>::iterator it = n1->adjacentNodes.find(n2->id);

        if (it == n1->adjacentNodes.end()) {
            n1->adjacentNodes.insert(std::make_pair(n2->id, weight));
        }
        else {
            it->second = weight;
        }
    }
}

/**
 * @brief Delete edge from the graph given the nodes
 * @param[in] node1 Node 1
 * @param[in] node2 Node 2
 */
template <class T>
void Graph<T>::deleteEdgeHelper(Node* n1, const Node* n2) {
    if (n2 != nullptr) {
        n1->adjacentNodes.erase(n2->id);
    }
}


/**
 * @brief Check if two nodes are adjacent
 * @param[in] node1 Node 1
 * @param[in] node2 Node 2
 * @return True if the nodes are adjacent, false otherwise
 */
template <class T>
bool Graph<T>::isAdjacentHelper(const Node* n1, const Node* n2) const {
    std::unordered_map<size_t, double>::const_iterator it = n1->adjacentNodes.find(n2->id);

    if (it == n1->adjacentNodes.end())
        return false;

    return true;
}

/**
 * @brief Get the weight of an edge between two nodes
 * It returns MAX_WEIGHT if node are not adjacent
 *
 * @param[in] node1 Node 1
 * @param[in] node2 Node 2
 * @return Weight of the edge, MAX_WEIGHT if nodes are not adjacent
 */
template <class T>
double Graph<T>::getWeightHelper(const Node* n1, const Node* n2) const {
    std::unordered_map<size_t, double>::const_iterator it = n1->adjacentNodes.find(n2->id);
    if (it == n1->adjacentNodes.end())
        return MAX_WEIGHT;
    else
        return it->second;
}

/**
 * @brief Set the weight of an edge between two nodes
 * @param[in] node1 Node 1
 * @param[in] node2 Node 2
 * @param[in] weight Weight of the edge
 */
template <class T>
void Graph<T>::setWeightHelper(Node* n1, const Node* n2, const double weight) {
    std::unordered_map<size_t, double>::iterator it = n1->adjacentNodes.find(n2->id);
    if (it == n1->adjacentNodes.end())
        return;
    it->second = weight;
}




}

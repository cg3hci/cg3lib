/**
    @author Stefano Nuvoli
*/
#include "graph.h"

namespace cg3 {

/* ----- CONSTRUCTORS/DESTRUCTORS ----- */

/**
 * @brief Default constructor
 */
template <class T>
Graph<T>::Graph(GraphType type) : type(type)
{

}

/**
 * @brief Destructor
 */
template <class T>
Graph<T>::~Graph() {
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
    typename std::map<T, unsigned int>::iterator mapIt = map.find(o);
    if (mapIt != map.end())
        return this->nodeIteratorEnd();

    //Create new node
    unsigned int newId = nodes.size();
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
    typename std::map<T, unsigned int>::iterator mapIt = map.find(o);
    if (mapIt == map.end())
        return false;

    //Delete the node
    Node*& node = nodes.at(mapIt->second);

    nodes[node->id] = nullptr;
    delete node;

    //Erase from map
    map.erase(mapIt);


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
 * @param[in] n Iterator to the node
 */
template <class T>
bool Graph<T>::deleteNode(NodeIterator n) {
    return deleteNode(*n);
}

/**
 * @brief Add edge in the graph given the node iterators
 * Note that you should use this function when you are sure
 * that the iteratos are pointing to an element which is in the
 * graph
 * @param[in] n1 Iterator to node 1
 * @param[in] n2 Iterator to node 2
 */
template <class T>
void Graph<T>::addEdge(NodeIterator n1, NodeIterator n2, const double weight) {
    addEdgeHelper(n1.node, n2.node, weight);
    if (type == GraphType::UNDIRECTED)
        addEdgeHelper(n2.node, n1.node, weight);
}

/**
 * @brief Delete edge from the graph given the node iterators
 * Note that you should use this function when you are sure
 * that the iteratos are pointing to an element which is in the
 * graph
 * @param[in] n1 Iterator to node 1
 * @param[in] n2 Iterator to node 2
 */
template <class T>
void Graph<T>::deleteEdge(NodeIterator n1, const NodeIterator n2) {
    deleteEdgeHelper(n1.node, n2.node);
    if (type == GraphType::UNDIRECTED)
        deleteEdgeHelper(n2.node, n1.node);
}


/**
 * @brief Check if two nodes are adjacent given the iterators
 * Note that you should use this function when you are sure
 * that the iterators are pointing to an element which is in the
 * graph
 * @param[in] n1 Iterator to node 1
 * @param[in] n2 Iterator to node 2
 * @return True if the nodes are adjacent, false otherwise
 */
template <class T>
bool Graph<T>::isAdjacent(const NodeIterator n1, const NodeIterator n2) const {
    return isAdjacentHelper(n1.node, n2.node);
}

/**
 * @brief Check if two nodes are adjacent given the iterators.
 * It returns MAX_WEIGHT if node are not adjacent
 * Note that you should use this function when you are sure
 * that the iterators are pointing to an element which is in the
 * graph
 * @param[in] n1 Iterator to node 1
 * @param[in] n2 Iterator to node 2
 * @return Weight of the edge, MAX_WEIGHT if nodes are not adjacent
 */
template <class T>
double Graph<T>::getWeight(const NodeIterator o1, const NodeIterator o2) {
    return getWeightHelper(o1.node, o2.node);
}


/**
 * @brief Set the weight of an edge between two nodes
 * Note that you should use this function when you are sure
 * that the iterators are pointing to an element which is in the
 * graph
 * @param[in] n1 Iterator to node 1
 * @param[in] n2 Iterator to node 2
 * @param[in] weight Weight of the edge
 */
template <class T>
void Graph<T>::setWeight(NodeIterator o1, NodeIterator o2, const double weight) {
    setWeightHelper(o1.node, o2.node, weight);
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





/* ----- PRIVATE FUNCTIONS FOR ITERATORS ----- */


/**
 * @brief Begin adjacent node iterator
 * @param[in] node Iterator of the node
 * @return Iterator
 */
template <class T>
typename Graph<T>::AdjacentNodeIterator Graph<T>::adjacentNodeIteratorBegin(Node* node) {
    std::unordered_map<unsigned int, double>& map = node->adjacentNodes;
    typename std::unordered_map<unsigned int, double>::iterator it = map.begin();

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
    typename std::map<T, unsigned int>::const_iterator mapIt = map.find(o);
    if (mapIt == map.end())
        return nullptr;

    //Retrieve id
    unsigned int id = mapIt->second;

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
        std::unordered_map<unsigned int, double>::iterator it = n1->adjacentNodes.find(n2->id);

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
    std::unordered_map<unsigned int, double>::const_iterator it = n1->adjacentNodes.find(n2->id);

    if (it == n1->adjacentNodes.end())
        return false;

    if (nodes.at(it->first) == nullptr)
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
    std::unordered_map<unsigned int, double>::const_iterator it = n1->adjacentNodes.find(n2->id);
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
    std::unordered_map<unsigned int, double>::iterator it = n1->adjacentNodes.find(n2->id);
    if (it == n1->adjacentNodes.end())
        return;
    it->second = weight;
}


}

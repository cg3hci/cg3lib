/**
    @author Stefano Nuvoli
*/
#include "graph.h"

#include <cfloat>

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
 * @brief Add arc in the graph
 * @param[in] o1 Object of the node 1
 * @param[in] o2 Object of the node 2
 * @return True if the arc has been inserted, false if it was not possible
 * to insert the arc because the values have not been found.
 */
template <class T>
bool Graph<T>::addArc(const T& o1, const T& o2, const double weight) {
    //If node does not exists, return false
    Node* node1 = findNodeHelper(o1);
    if (node1 == nullptr)
        return false;

    Node* node2 = findNodeHelper(o2);
    if (node2 == nullptr)
        return false;

    addArcHelper(node1, node2, weight);
    if (type == GraphType::UNDIRECTED)
        addArcHelper(node2, node1, weight);

    return true;
}


/**
 * @brief Delete arc from the graph
 * @param[in] o1 Object of the node 1
 * @param[in] o2 Object of the node 2
 * @return True if the arc has been deleted, false if it was not possible
 * to insert the arc because the values have not been found.
 */
template <class T>
bool Graph<T>::deleteArc(const T& o1, const T& o2) {
    //If node does not exists, return false
    Node* node1 = findNodeHelper(o1);
    if (node1 == nullptr)
        return false;

    Node* node2 = findNodeHelper(o2);
    if (node2 == nullptr)
        return false;

    deleteArcHelper(node1, node2);
    if (type == GraphType::UNDIRECTED)
        deleteArcHelper(node2, node1);

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
 * @brief Get the weight of an arc between to elements.
 * It returns DBL_MAX if node are not adjacent
 * or the nodes are not in the graph
 *
 * @param[in] o1 Object of the node 1
 * @param[in] o2 Object of the node 2
 * @return Weight of the arc, DBL_MAX if nodes are not adjacent
 * or the nodes are not in the graph
 */
template <class T>
double Graph<T>::getWeight(const T& o1, const T& o2) {
    //If node does not exists, return false
    Node* node1 = findNodeHelper(o1);
    if (node1 == nullptr)
        return DBL_MAX;

    Node* node2 = findNodeHelper(o2);
    if (node2 == nullptr)
        return DBL_MAX;

    return getWeightHelper(node1, node2);
}


/**
 * @brief Set the weight of the arc between two nodes if it
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
 * @brief Add arc in the graph given the node iterators
 * Note that you should use this function when you are sure
 * that the iteratos are pointing to an element which is in the
 * graph
 * @param[in] n1 Iterator to node 1
 * @param[in] n2 Iterator to node 2
 */
template <class T>
void Graph<T>::addArc(NodeIterator n1, NodeIterator n2, const double weight) {
    addArcHelper(n1.node, n2.node, weight);
    if (type == GraphType::UNDIRECTED)
        addArcHelper(n2.node, n1.node, weight);
}

/**
 * @brief Delete arc from the graph given the node iterators
 * Note that you should use this function when you are sure
 * that the iteratos are pointing to an element which is in the
 * graph
 * @param[in] n1 Iterator to node 1
 * @param[in] n2 Iterator to node 2
 */
template <class T>
void Graph<T>::deleteArc(NodeIterator n1, const NodeIterator n2) {
    deleteArcHelper(n1.node, n2.node);
    if (type == GraphType::UNDIRECTED)
        deleteArcHelper(n2.node, n1.node);
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
 * It returns DBL_MAX if node are not adjacent
 * Note that you should use this function when you are sure
 * that the iterators are pointing to an element which is in the
 * graph
 * @param[in] n1 Iterator to node 1
 * @param[in] n2 Iterator to node 2
 * @return Weight of the arc, DBL_MAX if nodes are not adjacent
 */
template <class T>
double Graph<T>::getWeight(const NodeIterator o1, const NodeIterator o2) {
    return getWeightHelper(o1.node, o2.node);
}


/**
 * @brief Set the weight of an arc between two nodes
 * Note that you should use this function when you are sure
 * that the iterators are pointing to an element which is in the
 * graph
 * @param[in] n1 Iterator to node 1
 * @param[in] n2 Iterator to node 2
 * @param[in] weight Weight of the arc
 */
template <class T>
void Graph<T>::setWeight(NodeIterator o1, NodeIterator o2, const double weight) {
    setWeightHelper(o1.node, o2.node, weight);
}



/* ----- ITERATORS ----- */

/**
 * @brief Begin node iterator
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
 */
template <class T>
typename Graph<T>::NodeIterator Graph<T>::nodeIteratorEnd() {
    return NodeIterator(this, nullptr, nodes.size());
}

/**
 * @brief Get range based node iterator of the graph
 *
 * @return Range based node iterator
 */
template <class T>
typename Graph<T>::RangeBasedNodeIterator Graph<T>::nodeIterator() {
    return RangeBasedNodeIterator(this);
}


/* ----- FUNCTIONS FOR ITERATORS ----- */

/**
 * @brief Get next node
 *
 * @param[in] pos Current position of the input node
 * @param[out] newPos Position of the next node
 * @return Next node
 */
template<class T>
typename Graph<T>::Node* Graph<T>::getNextNode(
        const unsigned int pos,
        unsigned int& newPos)
{
    typename std::vector<Node*>::iterator it = nodes.begin();
    std::advance(it, pos);

    newPos = pos;

    do {
        it++;
        newPos++;
    } while (it != nodes.end() && *it == nullptr);

    if (it == nodes.end())
        return nullptr;

    return *it;
}

/**
 * @brief Get previous node
 *
 * @param[in] pos Current position of the input node
 * @param[out] newPos Position of the previous node
 * @return Previous node
 */
template<class T>
typename Graph<T>::Node* Graph<T>::getPrevNode(
        const unsigned int pos,
        unsigned int& newPos)
{
    typename std::vector<Node*>::iterator it = nodes.begin();
    std::advance(it, pos);

    newPos = pos;

    do {
        if (it == nodes.begin())
            return nullptr;

        it--;
        newPos--;
    } while (*it == nullptr);

    return *it;
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
 * @brief Add arc in the graph given the nodes
 * @param[in] node1 Node 1
 * @param[in] node2 Node 2
 */
template <class T>
void Graph<T>::addArcHelper(Node* n1, const Node* n2, const double weight) {

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
 * @brief Delete arc from the graph given the nodes
 * @param[in] node1 Node 1
 * @param[in] node2 Node 2
 */
template <class T>
void Graph<T>::deleteArcHelper(Node* n1, const Node* n2) {
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
 * @brief Get the weight of an arc between two nodes
 * It returns DBL_MAX if node are not adjacent
 *
 * @param[in] node1 Node 1
 * @param[in] node2 Node 2
 * @return Weight of the arc, DBL_MAX if nodes are not adjacent
 */
template <class T>
double Graph<T>::getWeightHelper(const Node* n1, const Node* n2) const {
    std::unordered_map<unsigned int, double>::const_iterator it = n1->adjacentNodes.find(n2->id);
    if (it == n1->adjacentNodes.end())
        return DBL_MAX;
    else
        return it->second;
}

/**
 * @brief Set the weight of an arc between two nodes
 * @param[in] node1 Node 1
 * @param[in] node2 Node 2
 * @param[in] weight Weight of the arc
 */
template <class T>
void Graph<T>::setWeightHelper(Node* n1, const Node* n2, const double weight) {
    std::unordered_map<unsigned int, double>::iterator it = n1->adjacentNodes.find(n2->id);
    if (it == n1->adjacentNodes.end())
        return;
    it->second = weight;
}


}

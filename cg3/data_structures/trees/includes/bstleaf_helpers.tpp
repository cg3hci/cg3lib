/**
    @author Stefano Nuvoli
*/
#include "bstleaf_helpers.h"

#include "assert.h"

namespace cg3 {

namespace internal {

/* ----- BASIC BST OPERATIONS ----- */

/**
 * @brief Insert a node in the BST
 *
 * @param[in] newNode Node to be inserted
 * @param[in] rootNode Root node of the BST
 * @param[in] lessComparator Less comparator for keys
 * @return Pointer to the node if the node has been inserted, nullptr otherwise
 */
template <class Node, class K>
inline Node* insertNodeHelperLeaf(Node*& newNode, Node*& rootNode, LessComparatorType<K> lessComparator) {
    //If the tree is empty
    if (rootNode == nullptr) {
        //Insert the node as the root
        rootNode = newNode;
        newNode->parent = nullptr;

        return newNode;
    }

    //Find the position in the BST in which
    //the new node must be inserted
    Node* node = rootNode;

    //Travel in the BST until the node is a leaf
    while (!node->isLeaf()) {
        if (isLess(newNode->key, node->key, lessComparator)) {
            node = node->left;
        }
        else {
            node = node->right;
        }
        assert(node != nullptr);
    }

    //If the value is already in the BST
    if (isEqual(node->key, newNode->key, lessComparator)) {
        delete newNode;
        newNode = nullptr;
    }

    //If the found node is a leaf
    else {
        Node* newParent = nullptr;

        if (isLess(newNode->key, node->key, lessComparator)) {
            //Create new parent for the two nodes
            newParent = new Node(node->key);

            //Set the children
            newParent->left = newNode;
            newParent->right = node;
        }
        else {
            //Create new parent for the two nodes
            newParent = new Node(newNode->key);

            //Set the children
            newParent->left = node;
            newParent->right = newNode;
        }


        //Replace the node with the new parent
        replaceSubtreeHelper(node, newParent, rootNode);

        //Update the parents for the two nodes
        newNode->parent = newParent;
        node->parent = newParent;
    }

    return newNode;
}



/**
 * @brief Erase node from BST
 *
 * @param[in] node Node to be erased
 * @param[in] rootNode Root node of the BST
 * @return Node that replaces the erased one (useful for rebalancing)
 */
template <class Node>
inline Node* eraseNodeHelperLeaf(Node*& node, Node*& rootNode)
{
    Node* replacingChild = nullptr;

    //If the node is the root node of the BST
    if (rootNode == node) {
        rootNode = nullptr;
    }
    //If the node is not the root
    else {
        Node* parent = node->parent;

        //If node is a left child
        if (parent->left == node) {
            //Replace the parent with his right child
            replacingChild = parent->right;
            parent->left = nullptr;
        }
        //If node is a right child
        else {
            //Replace the parent with his left child
            replacingChild = parent->left;
            parent->right = nullptr;
        }

        //Replace parent with the child
        replaceSubtreeHelper(parent, replacingChild, rootNode);

        delete parent;
        parent = nullptr;
    }

    //Delete the node
    delete node;
    node = nullptr;

    return replacingChild;
}



/**
 * @brief Find an entry on the BST given a key
 *
 * @param[in] key Key of the node to be found
 * @param[in] rootNode Root node of the BST
 * @param[in] lessComparator Less comparator for keys
 *
 * @return If the node with a given value is found, then its pointer
 * is returned. Otherwise a null pointer is returned.
 *
 */
template <class Node, class K>
inline Node* findNodeHelperLeaf(
        const K& key,
        Node*& rootNode,
        LessComparatorType<K> lessComparator)
{
    if (rootNode == nullptr)
        return nullptr;

    Node* node = rootNode;

    //Travel in the BST until a leaf is found
    while (!node->isLeaf()) {
        if (isLess(key, node->key, lessComparator)) {
            node = node->left;
        }
        else {
            node = node->right;
        }
        assert(node != nullptr);
    }

    //If node has the input key, then the node is found
    if (isEqual(node->key, key, lessComparator)) {
        return node;
    }

    return nullptr;
}


/**
 * @brief Find the entry of the BST which is equal/lower than a given key
 *
 * @param[in] key Input key
 * @param[in] rootNode Root node of the BST
 * @param[in] lessComparator Less comparator for keys
 *
 * @return If the node with a key equal/lower than the input key is found, then
 * its pointer is returned. Otherwise, if there is not any entry equal/lower than
 * the input key, a null pointer is returned.
 *
 */
template <class Node, class K>
inline Node* findLowerHelperLeaf(
        const K& key,
        Node*& rootNode,
        LessComparatorType<K> lessComparator
) {
    if (rootNode == nullptr)
        return nullptr;

    Node* node = rootNode;

    //Travel in the BST until a leaf is found
    while (!node->isLeaf()) {
        if (isLess(key, node->key, lessComparator)) {
            node = node->left;
        }
        else {
            node = node->right;
        }
        assert(node != nullptr);
    }

    //If the input key is lower
    if (isLess(key, node->key, lessComparator)) {
        return getPredecessorHelperLeaf(node);
    }
    //If the input key is greater or equal
    else {
        return node;
    }
}

/**
 * @brief Find the entry of the BST which is upper than a given key
 *
 * @param[in] key Input key
 * @param[in] rootNode Root node of the BST
 * @param[in] lessComparator Less comparator for keys
 *
 * @return If the node with a key upper than the input key is found, then
 * its pointer is returned. Otherwise, if there is not any entry upper
 * than the input key, a null pointer is returned.
 *
 */
template <class Node, class K>
inline Node* findUpperHelperLeaf(
        const K& key,
        Node*& rootNode,
        LessComparatorType<K> lessComparator
) {
    if (rootNode == nullptr)
        return nullptr;

    Node* node = rootNode;

    //Travel in the BST until a leaf is found
    while (!node->isLeaf()) {
        if (isLess(key, node->key, lessComparator)) {
            node = node->left;
        }
        else {
            node = node->right;
        }
        assert(node != nullptr);
    }

    //If the input key is lower
    if (isGreaterOrEqual(key, node->key, lessComparator)) {
        return getSuccessorHelperLeaf(node);
    }
    //If the input key is greater or equal
    else {
        return node;
    }
}


/* ----- CONSTRUCTION HELPERS ----- */

/**
 * Construction of the balanced BST given a vector of sorted elements
 *
 * Recursive implementation
 *
 * @param[in] sortedVec Sorted vector of nodes
 * @param[in] start Start index of the partition of the vector to be inserted
 * @param[in] end End index of the partition of the vector to be inserted
 * @param[out] rootNode Root node of the BST
 * @param[in] lessComparator Less comparator for keys
 * @return Number of entries inserted in the BST
 */
template <class Node, class K>
inline TreeSize constructionMedianHelperLeaf(
        std::vector<Node*>& sortedNodes,
        const TreeSize start, const TreeSize end,
        Node*& rootNode,
        LessComparatorType<K> lessComparator)
{
    TreeSize numberOfEntries = 0;

    if (end <= start)
        return 0;

    //Median
    TreeSize mid = start + (end-start)/2;

    //Taking median value
    Node* node = sortedNodes.at(mid);

    //Creating node and inserting it in the root node
    if (insertNodeHelperLeaf(node, rootNode, lessComparator) != nullptr) {
        numberOfEntries++;
    }    
    //If it has not been inserted
    else {
        delete node;
        node = nullptr;        
        sortedNodes[mid] = nullptr;
    }

    //Calculate next partitions of the vector
    TreeSize firstHalfEnd = mid;
    TreeSize secondHalfStart = mid + 1;

    //Recursive calls
    numberOfEntries += constructionMedianHelperLeaf(sortedNodes, start, firstHalfEnd, rootNode, lessComparator);
    numberOfEntries += constructionMedianHelperLeaf(sortedNodes, secondHalfStart, end, rootNode, lessComparator);

    return numberOfEntries;
}

/**
 * Construction of the balanced BST given a vector of sorted elements
 *
 * Bottom up construction
 *
 * @param[in] sortedVec Sorted vector of entries (pair of keys/values)
 * @param[in] rootNode Root node of the BST
 * @returns Number of entries inserted in the BST
 */
template <class Node, class K>
inline TreeSize constructionBottomUpHelperLeaf(
        std::vector<Node*>& sortedNodes,
        Node*& rootNode,
        LessComparatorType<K> lessComparator)
{
    TreeSize numberOfEntries = 0;

    std::vector<Node*>* nodes = new std::vector<Node*>();

    //Create leaves
    K lastValue;
    for (size_t i = 0; i < sortedNodes.size(); i ++) {
        Node* node = sortedNodes.at(i);

        //Avoid duplicates
        if (i == 0 || !isEqual(lastValue, node->key, lessComparator)) {
            nodes->push_back(node);

            numberOfEntries++;

            lastValue = node->key;
        }
        //If it has not been inserted
        else {
            delete node;
            node = nullptr;            
            sortedNodes[i] = nullptr;
        }
    }


    //If there is not an only remaining node
    while (nodes->size() > 1) {

        //Nodes of the new level
        std::vector<Node*>* newLevelNodes = new std::vector<Node*>();

        for (size_t i = 0; i < nodes->size(); i += 2) {
            Node* node1 = nodes->at(i);
            Node* node2 = nullptr;

            //If a second node exists
            if (i+1 < nodes->size()) {
                node2 = nodes->at(i+1);
            }

            //If a second node exists
            if (node2 != nullptr) {
                K& key = getMinimumHelperLeaf(node2)->key;
                Node* parentNode = new Node(key);

                //Setting children conditions
                parentNode->left = node1;
                parentNode->right = node2;

                //Setting parent
                node1->parent = parentNode;
                node2->parent = parentNode;

                newLevelNodes->push_back(parentNode);
            }
            else {
                newLevelNodes->push_back(node1);
            }
        }


        //Delete vector of nodes
        delete nodes;
        nodes = nullptr;

        //Replacing the nodes with the node of the new level
        nodes = newLevelNodes;
    }

    rootNode = nodes->at(0);
    rootNode->parent = nullptr;

    //Delete vector of nodes
    delete nodes;
    nodes = nullptr;

    return numberOfEntries;
}




/* ----- RANGE QUERY HELPERS ----- */


/**
 * @brief Find entries in the BST that are enclosed in a given range
 *
 * @param[in] start Starting value of the range
 * @param[in] end End value of the range
 * @param[out] out Vector of node with keys that are enclosed in the input range
 * @param[in] rootNode Root node of the BST
 * @param[in] lessComparator Less comparator for keys
 */
template <class Node, class K>
inline void rangeQueryHelperLeaf(
        const K& start, const K& end,
        std::vector<Node*> &out,
        Node* rootNode,
        LessComparatorType<K> lessComparator)
{
    //Find split node
    Node* splitNode = findSplitNodeHelperLeaf(start, end, rootNode, lessComparator);
    if (splitNode == nullptr)
        return;

    //If the split node is a leaf
    if (splitNode->isLeaf()) {
        //Report the node if it is contained in the range
        if (isGreaterOrEqual(splitNode->key, start, lessComparator) &&
                isLessOrEqual(splitNode->key, end, lessComparator))
        {
            reportSubTreeHelperLeaf(splitNode, out);
        }
    }
    //If the split node is not a leaf
    else {
        //Follow path from splitNode to start and report right subtrees
        Node* vl = splitNode->left;
        while (!vl->isLeaf()) {
            if (isLess(start, vl->key, lessComparator)) {
                reportSubTreeHelperLeaf(vl->right, out);
                vl = vl->left;
            }
            else {
                vl = vl->right;
            }
        }
        //Report the node if it is contained in the range
        if (isGreaterOrEqual(vl->key, start, lessComparator) &&
                isLessOrEqual(vl->key, end, lessComparator))
        {
            reportSubTreeHelperLeaf(vl, out);
        }

        //Follow path from splitNode to end and report left subtrees
        Node* vr = splitNode->right;
        while (!vr->isLeaf()) {
            if (isGreaterOrEqual(end, vr->key, lessComparator)) {
                reportSubTreeHelperLeaf(vr->left, out);
                vr = vr->right;
            }
            else {
                vr = vr->left;
            }
        }
        //Report the node if it is contained in the range
        if (isGreaterOrEqual(vr->key, start, lessComparator) && isLessOrEqual(vr->key, end, lessComparator)) {
            reportSubTreeHelperLeaf(vr, out);
        }
    }

}

/**
 * @brief Find split node of the BST for a given range
 *
 * @param[in] start Starting value of the range
 * @param[in] end End value of the range
 * @param[in] rootNode Root node of the BST
 * @param[in] lessComparator Less comparator for keys
 * @return Split node of the BST. Returns nullptr if the tree is empty
 */
template <class Node, class K>
inline Node* findSplitNodeHelperLeaf(
        const K& start, const K& end,
        Node* rootNode,
        LessComparatorType<K> lessComparator)
{
    if (rootNode == nullptr)
        return nullptr;

    Node* v = rootNode;
    //Follow path until a leaf is found
    while (!v->isLeaf()) {
        //If both path follow left subtree
        if (isLess(start, v->key, lessComparator)
                && isLess(end, v->key, lessComparator))
        {
            v = v->left;
        }
        //If both path follow right subtree
        else if (isGreaterOrEqual(start, v->key, lessComparator) &&
                 isGreaterOrEqual(end, v->key, lessComparator))
        {
            v = v->right;
        }
        else {
            return v;
        }
    }

    return v;
}

/**
 * @brief Add to the output vector the entire subtree
 *
 * @param[in] node Root of the subtree
 * @param[out] out Vector of output nodes
 */
template <class Node>
inline void reportSubTreeHelperLeaf(
        Node* node,
        std::vector<Node*>& out)
{
    if (node->isLeaf()) {
        out.push_back(node);
    }
    else {
        reportSubTreeHelperLeaf(node->left, out);
        reportSubTreeHelperLeaf(node->right, out);
    }
}






/* ----- SUCCESSORS/PREDECESSORS MIN/MAX ----- */

/**
 * @brief Get the successor of a node
 *
 * @param[in] node Input node
 * @return Successor of the node, nullptr if there is no successor
 */
template <class Node>
inline Node* getSuccessorHelperLeaf(Node* node) {
    Node* x = node;

    //Climb on parents
    Node* y = x->parent;
    while (y != nullptr && x == y->right) {
        x = y;
        y = y->parent;
    }

    //If it has a right child, get the minimum node of subtree
    //rooted in the right child
    if (y != nullptr && y->right != nullptr)
        return getMinimumHelperLeaf(y->right);

    return y;
}


/**
 * @brief Get predecessor of a node
 *
 * @param[in] node Input node
 * @return Predecessor of the node, nullptr if there is no predecessor
 */
template <class Node>
inline Node* getPredecessorHelperLeaf(Node* node) {
    Node* x = node;

    //Climb on parents
    Node* y = x->parent;
    while (y != nullptr && x == y->left) {
        x = y;
        y = y->parent;
    }

    // If it has a left child, get the maximum node of subtree
    // rooted in the left child
    if (y != nullptr && y->left != nullptr)
        return getMaximumHelperLeaf(y->left);

    return y;
}




/**
 * @brief Get minimum key node of the subtree
 *
 * @param[in] startingNode Root of the subtree
 * @return Minimum key node pointer
 */
template <class Node>
inline Node* getMinimumHelperLeaf(Node* rootNode) {
    Node* x = rootNode;

    while (x != nullptr && !x->isLeaf())
        x = x->left;

    return x;
}


/**
 * @brief Get maximum key node of the subtree
 *
 * @param[in] startingNode Root of the subtree
 * @return Maximum key node pointer
 */
template <class Node>
inline Node* getMaximumHelperLeaf(Node* rootNode) {
    Node* x = rootNode;

    while (x != nullptr && !x->isLeaf())
        x = x->right;

    return x;
}


}

}

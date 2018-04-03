/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */
#include "bstinner_helpers.h"

namespace cg3 {

namespace internal {


/* ----- BASIC BST OPERATIONS ----- */

/**
 * @brief Insert a node in the BST
 *
 * @param[in] newNode Node to be inserted
 * @param[in] rootNode Root node of the BST
 * @param[in] comparator Less comparator for keys
 * @return Pointer to the node if the node has been inserted, nullptr otherwise
 */
template <class Node, class K, class C>
Node* insertNodeHelperInner(Node*& newNode, Node*& rootNode, C& comparator)
{
    //Find the position in the BST in which
    //the new node must be inserted
    Node* lastVisitedNode = nullptr;
    Node* node = rootNode;

    while (node != nullptr && !isEqual(node->key, newNode->key, comparator)) {
        lastVisitedNode = node;

        if (isLess(newNode->key, node->key, comparator)) {
            node = node->left;
        }
        else {
            node = node->right;
        }
    }

    //If the value is not contained in the BST
    if (node == nullptr) {
        //If the tree is not empty
        if (rootNode != nullptr) {
            newNode->parent = lastVisitedNode;

            //Insert the node as a child of the last visited node
            if (isLess(newNode->key, lastVisitedNode->key, comparator)) {
                lastVisitedNode->left = newNode;
            }
            else {
                lastVisitedNode->right = newNode;
            }
        }
        //If the tree is empty: insert the node as the root
        else {
            newNode->parent = nullptr;
            rootNode = newNode;
        }

        return newNode;
    }

    //If the value is already in the BST
    delete newNode;
    newNode = nullptr;

    return nullptr;
}


/**
 * @brief Erase node from BST
 *
 * @param[in] node Node to be erased
 * @param[in] rootNode Root node of the BST
 * @return Node that replaces the erased one (useful for rebalancing)
 */
template <class Node>
Node* eraseNodeHelperInner(Node*& node, Node*& rootNode)
{
    //Node that will replace the node to be erased
    Node* y;

    //Child of the node that will replace the node to be erased
    Node* x;

    //If the node is a leaf
    if (node->left == nullptr || node->right == nullptr) {
        y = node;
    }
    //If the node is not a leaf, get the successor
    else {
        y = getSuccessorHelperInner(node);
    }

    //If y has a left child
    if (y->left != nullptr) {
        x = y->left;
    }
    else {
        x = y->right;
    }

    //If x is a node, set the parent
    if (x != nullptr) {
        x->parent = y->parent;
    }

    //Setting relationships between nodes
    if (y->parent == nullptr) {
        rootNode = x;
    }
    else {
        if (y == y->parent->left) {
            y->parent->left = x;
        }
        else {
            y->parent->right = x;
        }
    }

    //If the node was not a leaf, copy (replace)
    //keys and values of y in the node to be deleted
    if (y != node) {
        //Switch values (delete operation on value pointer)
        auto nodeValue = node->value;
        node->value = y->value;
        y->value = nodeValue;

        //Set new key
        node->key = y->key;
    }

    Node* replacingNode = y->parent;

    //Delete the node
    delete y;
    y = nullptr;

    return replacingNode;

}



/**
 * @brief Find an entry on the BST given a key
 *
 * @param[in] key Key of the node to be found
 * @param[in] rootNode Root node of the BST
 * @param[in] comparator Less comparator for keys
 *
 * @return If the node with a given value is found, then its pointer
 * is returned. Otherwise a null pointer is returned.
 *
 */
template <class Node, class K, class C>
Node* findNodeHelperInner(
        const K& key,
        Node*& rootNode,
        C& comparator)
{
    Node* node = rootNode;

    //Follow a path until the node is found
    while (node != nullptr && !isEqual(node->key, key, comparator)) {
        if (isLess(key, node->key, comparator)) {
            node = node->left;
        }
        else {
            node = node->right;
        }
    }

    return node;
}

/**
 * @brief Find the entry of the BST which is equal/lower than a given key
 *
 * @param[in] key Input key
 * @param[in] rootNode Root node of the BST
 * @param[in] comparator Less comparator for keys
 *
 * @return If the node with a key equal/lower than the input key is found, then
 * its pointer is returned. Otherwise, if there is not any entry equal/lower than
 * the input key, a null pointer is returned.
 *
 */
template <class Node, class K, class C>
Node* findLowerHelperInner(
        const K& key,
        Node*& rootNode,
        C& comparator)
{
    Node* node = rootNode;

    if (node == nullptr)
        return nullptr;

    Node* lastVisitedNode = nullptr;

    //Follow a path until a leaf has been reached
    while (node != nullptr) {
        //Update last visited node
        lastVisitedNode = node;

        if (isLess(key, node->key, comparator)) {
            node = node->left;
        }
        else {
            node = node->right;
        }

        //Return node if we found a node with the same key
        if (node != nullptr && isEqual(node->key, key, comparator)) {
            return node;
        }
    }

    //If the input key is lower
    if (isLess(key, lastVisitedNode->key, comparator)) {
        return getPredecessorHelperInner(lastVisitedNode);
    }
    //If the input key is greater or equal
    else {
        return lastVisitedNode;
    }
}

/**
 * @brief Find the entry of the BST which is upper than a given key
 *
 * @param[in] key Input key
 * @param[in] rootNode Root node of the BST
 * @param[in] comparator Less comparator for keys
 *
 * @return If the node with a key upper than the input key is found, then
 * its pointer is returned. Otherwise, if there is not any entry upper
 * than the input key, a null pointer is returned.
 *
 */
template <class Node, class K, class C>
Node* findUpperHelperInner(
        const K& key,
        Node*& rootNode,
        C& comparator)
{
    Node* node = rootNode;

    if (node == nullptr)
        return nullptr;

    Node* lastVisitedNode = nullptr;

    //Follow a path until a leaf has been reached
    while (node != nullptr) {
        //Update last visited node
        lastVisitedNode = node;

        if (isLess(key, node->key, comparator)) {
            node = node->left;
        }
        else {
            node = node->right;
        }

        //Return the successor of the node if we found a
        //node with the same key
        if (node != nullptr && isEqual(node->key, key, comparator)) {
            return getSuccessorHelperInner(node);
        }
    }

    //If the input key is lower
    if (isLess(key, lastVisitedNode->key, comparator)) {
        return lastVisitedNode;
    }
    //If the input key is greater or equal
    else {
        return getSuccessorHelperInner(lastVisitedNode);
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
 * @param[in] comparator Less comparator for keys
 * @return Number of entries inserted in the BST
 */
template <class Node, class K, class C>
TreeSize constructionMedianHelperInner(
        std::vector<Node*>& sortedNodes,
        const TreeSize start, const TreeSize end,
        Node*& rootNode,
        C& comparator)
{
    TreeSize numberOfEntries = 0;

    if (end <= start)
        return 0;

    //Median
    TreeSize mid = start + (end-start)/2;

    //Taking median value
    Node* node = sortedNodes.at(mid);

    //Creating node and inserting it in the root node
    Node* insertResult = insertNodeHelperInner<Node,K,C>(node, rootNode, comparator);
    if (insertResult != nullptr) {
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
    numberOfEntries += constructionMedianHelperInner<Node,K,C>(sortedNodes, start, firstHalfEnd, rootNode, comparator);
    numberOfEntries += constructionMedianHelperInner<Node,K,C>(sortedNodes, secondHalfStart, end, rootNode, comparator);

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
 * @param[in] comparator Less comparator for keys
 */
template <class Node, class K, class C>
void rangeQueryHelperInner(
        const K& start, const K& end,
        std::vector<Node*> &out,
        Node* rootNode,
        C& comparator)
{
    //Find split node
    Node* splitNode = findSplitNodeHelperInner(start, end, rootNode, comparator);
    if (splitNode == nullptr)
        return;


    //Report node if it is contained in the range
    if (isGreaterOrEqual(splitNode->key, start, comparator) &&
            isLessOrEqual(splitNode->key, end, comparator))
    {
        out.push_back(splitNode);
    }

    //Follow path from splitNode to start and report right subtrees
    Node* vl = splitNode->left;
    while (vl != nullptr) {
        //Report node if it is contained in the range
        if (isGreaterOrEqual(vl->key, start, comparator)
                && isLessOrEqual(vl->key, end, comparator))
        {
            out.push_back(vl);
        }

        //Report left child if it is contained in the range
        if (isLess(start, vl->key, comparator)) {
            reportSubTreeHelperInner(vl->right, out);
            vl = vl->left;
        }
        //Go to right child
        else {
            vl = vl->right;
        }
    }

    //Follow path from splitNode to end and report left subtrees
    Node* vr = splitNode->right;
    while (vr != nullptr) {

        //Report node if it is contained in the range
        if (isGreaterOrEqual(vr->key, start, comparator)
                && isLessOrEqual(vr->key, end, comparator))
        {
            out.push_back(vr);
        }

        //Report right child if it is contained in the range
        if (isGreaterOrEqual(end, vr->key, comparator)) {
            reportSubTreeHelperInner(vr->left, out);
            vr = vr->right;
        }
        //Go to left child
        else {
            vr = vr->left;
        }
    }

}

/**
 * @brief Find split node of the BST for a given range
 *
 * @param[in] start Starting value of the range
 * @param[in] end End value of the range
 * @param[in] rootNode Root node of the BST
 * @param[in] comparator Less comparator for keys
 * @return Split node of the BST. Returns nullptr if the tree is empty
 */
template <class Node, class K, class C>
Node* findSplitNodeHelperInner(
        const K& start, const K& end,
        Node* rootNode,
        C& comparator)
{
    if (rootNode == nullptr)
        return nullptr;

    Node* v = rootNode;
    //Follow path until a leaf is found
    while (v != nullptr) {
        //If both path follow left subtree
        if (isLess(start, v->key, comparator) && isLess(end, v->key, comparator)) {
            v = v->left;
        }
        //If both path follow right subtree
        else if (isGreater(start, v->key, comparator) && isGreater(end, v->key, comparator)) {
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
void reportSubTreeHelperInner(
        Node* node,
        std::vector<Node*>& out)
{
    if (node == nullptr)
        return;

    out.push_back(node);

    reportSubTreeHelperInner(node->left, out);
    reportSubTreeHelperInner(node->right, out);
}






/* ----- SUCCESSORS/PREDECESSORS MIN/MAX ----- */

/**
 * @brief Get the successor of a node
 *
 * @param[in] node Input node
 * @return Successor of the node, nullptr if there is no successor
 */
template <class Node>
Node* getSuccessorHelperInner(Node* node)
{
    Node* x = node;

    //If it has a right child, get the minimum node of subtree
    //rooted in the right child
    if (x->right != nullptr)
        return getMinimumHelperInner(x->right);

    //Climb on parents
    Node* y = x->parent;
    while (y != nullptr && x == y->right) {
        x = y;
        y = y->parent;
    }

    return y;
}


/**
 * @brief Get predecessor of a node
 *
 * @param[in] node Input node
 * @return Predecessor of the node, nullptr if there is no predecessor
 */
template <class Node>
Node* getPredecessorHelperInner(Node* node)
{
    Node* x = node;

    // If it has a left child, get the maximum node of subtree
    // rooted in the left child
    if (x->left != nullptr)
        return getMaximumHelperInner(x->left);

    //Climb on parents
    Node* y = x->parent;
    while (y != nullptr && x == y->left) {
        x = y;
        y = y->parent;
    }
    return y;
}




/**
 * @brief Get minimum key node of the subtree
 *
 * @param[in] startingNode Root of the subtree
 * @return Minimum key node pointer
 */
template <class Node>
Node* getMinimumHelperInner(Node* rootNode)
{
    Node* x = rootNode;

    while (x != nullptr && x->left != nullptr)
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
Node* getMaximumHelperInner(Node* rootNode)
{
    Node* x = rootNode;

    while (x != nullptr && x->right != nullptr)
        x = x->right;

    return x;
}


}

}

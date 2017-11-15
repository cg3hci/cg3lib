/**
    @author Stefano Nuvoli
*/
#include "rangetreehelpers.h"

#include "bstleafhelpers.h"

#include "assert.h"

namespace cg3 {



/* ----- MULTIDIMENSIONAL RANGE TREE HELPERS ----- */

template <class Node, class K, class Iterator>
void rangeSearchInNextDimensionHelper(
        Node* node,
        const K& start,
        const K& end,
        std::vector<Node*>& out,
        const unsigned int dim);


/**
 * @brief Find entries in the range tree that are enclosed in a given range
 *
 * @param[in] start Starting value of the range
 * @param[in] end End value of the range
 * @param[in] rootNode Root node of the BST
 * @param[out] out Vector of node with keys that are enclosed in the input range
 * @param[in] lessComparator Less comparator for keys
 * @param[in] dim Dimension of the range tree
 */
template <class Node, class K, class Iterator>
void rangeQueryRangeTreeHelper(
        const K& start, const K& end,
        Node*& rootNode,
        std::vector<Node*> &out,
        LessComparatorType<K> lessComparator,
        const unsigned int dim)
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
            rangeSearchInNextDimensionHelper<Node,K,Iterator>(splitNode, start, end, out, dim);
        }
    }
    //If the split node is not a leaf
    else {
        //Follow path from splitNode to start and report right subtrees
        Node* vl = splitNode->left;
        while (!vl->isLeaf()) {
            if (isLess(start, vl->key, lessComparator)) {
                rangeSearchInNextDimensionHelper<Node,K,Iterator>(vl->right, start, end, out, dim);
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
            rangeSearchInNextDimensionHelper<Node,K,Iterator>(vl, start, end, out, dim);
        }

        //Follow path from splitNode to end and report left subtrees
        Node* vr = splitNode->right;
        while (!vr->isLeaf()) {
            if (isGreaterOrEqual(end, vr->key, lessComparator)) {
                rangeSearchInNextDimensionHelper<Node,K,Iterator>(vr->left, start, end, out, dim);
                vr = vr->right;
            }
            else {
                vr = vr->left;
            }
        }
        //Report the node if it is contained in the range
        if (isGreaterOrEqual(vr->key, start, lessComparator) && isLessOrEqual(vr->key, end, lessComparator)) {
            rangeSearchInNextDimensionHelper<Node,K,Iterator>(vr, start, end, out, dim);
        }
    }
}


/**
 * @brief Range search in next dimension or report the subtree
 *
 * @param[in] node Root of the subtree
 * @param[in] start Starting value of the range
 * @param[in] end End value of the range
 * @param[out] out Vector of output nodes
 * @param[in] dim Dimension of the range tree
 */
template <class Node, class K, class Iterator>
void rangeSearchInNextDimensionHelper(
        Node* node,
        const K& start,
        const K& end,
        std::vector<Node*>& out,
        const unsigned int dim)
{

    if (dim > 1) {
        std::vector<Iterator> itOut;

        node->assRangeTree->rangeQuery(start, end, itOut);

        for (Iterator it : itOut) {
            out.push_back(it.node);
        }
    }
    else {
        reportSubTreeHelperLeaf(node, out);
    }
}




/* ----- HELPERS FOR ASSOCIATED RANGE TREE ----- */

/**
 * @brief Create associated tree helper for a node
 *
 * @param[in] node Node
 * @param[in] dim Dimension of the range tree
 * @param[in] customComparators Vector of comparators for each
 * dimension of the range tree
 */
template <class Node, class K, class T>
void createAssociatedTreeHelper(
        Node *node,
        const unsigned int dim,
        std::vector<LessComparatorType<K>> customComparators)
{
    if (dim > 1) {
        node->assRangeTree = new RangeTree<K,T>(dim-1, customComparators);
    }
}



/**
 * @brief Create associated tree helper for a node
 * climbing on parents (the input node is included)
 *
 * @param[in] node Node
 * @param[in] dim Dimension of the range tree
 */
template <class Node, class K, class T>
void createParentAssociatedTreeHelper(
        Node *node,
        const unsigned int dim,
        std::vector<LessComparatorType<K>> customComparators)
{
    if (dim > 1) {
        while (node != nullptr && node->assRangeTree == nullptr) {
            //Insert into associated range tree
            createAssociatedTreeHelper<Node,K,T>(node, dim, customComparators);

            //Next parent
            node = node->parent;
        }
    }
}


/**
 * @brief Insert into associated range tree key/value of the node
 *
 * @param[in] node Node for which the new node will be inserted into
 * its associated range tree
 * @param[in] key Key of new node
 * @param[in] value Value of new node
 * @param[in] dim Dimension of the range tree
 */
template <class Node, class K, class T>
void insertIntoAssociatedTreeHelper(
        Node* node,
        const K& key,
        const T& value,
        const unsigned int dim)
{
    if (dim > 1) {
        //Insert into associated range tree
        node->assRangeTree->insert(key, value);
    }
}



/**
 * @brief Insert into associated range trees the current key and value
 * climbing on parents (the input node is included)
 *
 * @param[in] node Node from which the climbing starts
 * @param[in] key Key of new node
 * @param[in] value Value of new node
 * @param[in] dim Dimension of the range tree
 */
template <class Node, class K, class T>
void insertIntoParentAssociatedTreesHelper(
        Node* node,
        const K& key,
        const T& value,
        const unsigned int dim)
{
    if (dim > 1) {
        while (node != nullptr) {
            //Insert into associated range tree
            insertIntoAssociatedTreeHelper(node, key, value, dim);

            //Next parent
            node = node->parent;
        }
    }
}


/**
 * @brief Erase from associated range tree key/value of the node
 *
 * @param[in] node Node for which the node will be erase from its
 * associated range tree
 * @param[in] key Key of the node to be deleted
 * @param[in] dim Dimension of the range tree
 */
template <class Node, class K>
void eraseFromAssociatedTreeHelper(
        Node* node,
        const K& key,
        const unsigned int dim)
{
    if (dim > 1) {
        //Erase from associated range tree
        node->assRangeTree->erase(key);
    }
}



/**
 * @brief Erase from associated range trees the current key climbing
 * on parents (the input node is included)
 *
 * @param[in] node Node from which the climbing starts
 * @param[in] key Key of new node
 * @param[in] dim Dimension of the range tree
 */
template <class Node, class K>
void eraseFromParentAssociatedTreesHelper(
        Node* node,
        const K& key,
        const unsigned int dim)
{
    if (dim > 1) {
        while (node != nullptr) {
            //Erase from associated range tree
            eraseFromAssociatedTreeHelper(node, key, dim);

            //Next parent
            node = node->parent;
        }
    }
}




/* ----- AVL HELPERS FOR RANGE TREE ----- */

/**
 * @brief Rebalance with left/right rotations to make the
 * RangeTree satisfy the AVL constraints
 *
 * @param[in] node Starting node
 * @param[in] node Root node of the BST
 */
template <class Node>
void rebalanceRangeTreeHelper(
        Node* node,
        Node*& rootNode,
        const unsigned int dim)
{
    //Null handler
    if (node == nullptr)
        return;

    //Not balanced node
    Node* n = node;
    int balanceFactor = getHeightHelper(n->right) - getHeightHelper(n->left);

    //Climb on parents to find the not balanced node
    while (n != nullptr && balanceFactor >= -1 && balanceFactor <= 1) {
        n = n->parent;

        if (n != nullptr) {
            //Compute balance factor
            balanceFactor = getHeightHelper(n->right) - getHeightHelper(n->left);

            assert(balanceFactor <= 2 && balanceFactor >= -2);
        }
    }


    if (n != nullptr) {
        assert(balanceFactor == 2 || balanceFactor == -2);
        if (balanceFactor < -1) {
            Node* leftleft = n->left->left;
            Node* leftright = n->left->right;

            //Left left case
            if (getHeightHelper(leftleft) >= getHeightHelper(leftright)) {
                n = rightRotateRangeTreeHelper(n, dim);
            }
            //Left right case
            else {
                n->left = leftRotateRangeTreeHelper(n->left, dim);
                n = rightRotateRangeTreeHelper(n, dim);
            }
        }
        else if (balanceFactor > 1) {
            Node* rightright = n->right->right;
            Node* rightleft = n->right->left;

            //Right right case
            if (getHeightHelper(rightright) >= getHeightHelper(rightleft)) {
                n = leftRotateRangeTreeHelper(n, dim);
            }
            //Left right case
            else {
                n->right = rightRotateRangeTreeHelper(n->right, dim);
                n = leftRotateRangeTreeHelper(n, dim);
            }
        }


        //Set root
        if (n->parent == nullptr) {
            rootNode = n;
        }

        //Update heights on parents and rebalance them if needed
        updateHeightAndRebalanceRangeTreeHelper(n->parent, rootNode, dim);

    }
}



/**
 * @brief Update heights climbing on the parents and then
 * rebalance them if needed
 *
 * @param[in] node Starting node
 * @param[in] node Root node of the BST
 */
template <class Node>
void updateHeightAndRebalanceRangeTreeHelper(
        Node* node,
        Node*& rootNode,
        const unsigned int dim)
{
    updateHeightHelper(node);
    rebalanceRangeTreeHelper(node, rootNode, dim);
}



/**
 * @brief Left rotation
 *
 * @param[in] a Node to be rotated
 * @return New node in the position of the original node after the rotation
 */
template <class Node>
Node* leftRotateRangeTreeHelper(Node* a, const unsigned int dim) {
    //Rotate left
    Node* b = leftRotateHelper(a);


    //Update associated trees
    if (dim > 1) {
        //Referencing subtrees
        Node* c = b->right;
        Node* aLeft = a->left;

        if (aLeft != nullptr) {
            //Insert aLeft into b associated tree
            for (auto aLeftIt = aLeft->assRangeTree->begin(); aLeftIt != aLeft->assRangeTree->end(); aLeftIt++) {
                Node* aLeftNode = aLeftIt.node;
                insertIntoAssociatedTreeHelper(b, aLeftNode->key, *(aLeftNode->value), dim);
            }
        }
        //Erase c from a associated tree
        for (auto cIt = c->assRangeTree->begin(); cIt != c->assRangeTree->end(); cIt++) {
            Node* cNode = cIt.node;
            eraseFromAssociatedTreeHelper(a, cNode->key, dim);
        }
    }

    return b;
}

/**
 * @brief Right rotation
 *
 * @param[in] a Node to be rotated
 * @return New node in the position of the original node after the rotation
 */
template <class Node>
Node* rightRotateRangeTreeHelper(Node* a, const unsigned int dim) {
    //Rotate right
    Node* b = rightRotateHelper(a);


    //Update associated trees
    if (dim > 1) {
        //Referencing subtrees
        Node* c = b->left;
        Node* aRight = a->right;

        if (aRight != nullptr) {
            //Insert aRight into b associated tree
            for (auto aRightIt = aRight->assRangeTree->begin(); aRightIt != aRight->assRangeTree->end(); aRightIt++) {
                Node* aRightNode = aRightIt.node;
                insertIntoAssociatedTreeHelper(b, aRightNode->key, *(aRightNode->value), dim);
            }
        }
        //Erase c from a associated tree
        for (auto cIt = c->assRangeTree->begin(); cIt != c->assRangeTree->end(); cIt++) {
            Node* cNode = cIt.node;
            eraseFromAssociatedTreeHelper(a, cNode->key, dim);
        }
    }

    return b;
}


}

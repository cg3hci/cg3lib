/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */
#include "bst_helpers.h"

namespace cg3 {

namespace internal {


/* ----- BASIC BST OPERATIONS ----- */

/**
 * @brief Clear a given subtree, having as root the rootNode.
 * Note that nodes referencing to the rootNode must be updated
 * manually
 *
 * @param[in] rootNode Root of the subtree
 */
template <class Node>
void clearHelper(Node*& rootNode)
{
    //If it is already empty
    if (rootNode == nullptr)
        return;

    //Clear subtrees
    clearHelper(rootNode->left);
    clearHelper(rootNode->right);

    //Delete data
    delete rootNode;
    rootNode = nullptr;
}

/**
 * @brief Create a copy of a given subtree, having as root
 * the rootNode.
 *
 * @param[in] rootNode Root of the subtree
 * @returns Copy of the subtree
 */
template <class Node, class T>
Node* copySubtreeHelper(
        const Node* rootNode,
        Node* parent)
{
    if (rootNode == nullptr)
        return nullptr;

    Node* newNode = new Node(*rootNode);

    newNode->left = copySubtreeHelper<Node,T>(rootNode->left, newNode);
    newNode->right = copySubtreeHelper<Node,T>(rootNode->right, newNode);
    newNode->parent = parent;
    if (rootNode->value != nullptr)
        newNode->value = new T(*(rootNode->value));

    return newNode;
}


/* ----- UTILITIES ----- */

/**
 * @brief Get max height of the subtree rooted in a node
 *
 * @param[in] node Root node of the subtree
 * @return Max height of the subtree
 */
template <class Node>
unsigned long long int getHeightRecursiveHelper(const Node* node)
{
    if (node == nullptr)
        return 0;

    if (node->isLeaf())
        return 1;

    return 1 + std::max(getHeightRecursiveHelper(node->left), getHeightRecursiveHelper(node->right));
}


/**
 * @brief Replace the subtree rooted at u with
 * the subtree rooted at v
 *
 * @param[in] u Root of the subtree to be replaced
 * @param[in] v Root of the subtree that replaces u
 * @param[in] node Root node of the BST
 */
template <class Node>
void replaceSubtreeHelper(const Node* u, Node* v, Node*& rootNode)
{
    //If u is the root (no parent)
    if (u->parent == nullptr) {
        rootNode = v;
    }

    //If u is the left child of the parent
    else if (u == u->parent->left) {
        u->parent->left = v;
    }
    //If u is the right child of the parent
    else {
        u->parent->right = v;
    }

    //If v is not null
    if (v != nullptr) {
        v->parent = u->parent;
    }
}

}

}

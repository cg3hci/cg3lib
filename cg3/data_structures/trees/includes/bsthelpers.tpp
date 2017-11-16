/**
    @author Stefano Nuvoli
*/
#include "bstinnerhelpers.h"

namespace cg3 {



/* ----- BASIC BST OPERATIONS ----- */

/**
 * @brief Clear a given subtree, having as root the rootNode.
 * Note that nodes referencing to the rootNode must be updated
 * manually
 *
 * @param[in] rootNode Root of the subtree
 */
template <class Node>
inline void clearHelper(Node*& rootNode) {
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



/* ----- UTILITIES ----- */

/**
 * @brief Get max height of the subtree rooted in a node
 *
 * @param[in] node Root node of the subtree
 * @return Max height of the subtree
 */
template <class Node>
inline unsigned long long int getHeightRecursiveHelper(const Node* node)
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
inline void replaceSubtreeHelper(const Node* u, Node* v, Node*& rootNode) {
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

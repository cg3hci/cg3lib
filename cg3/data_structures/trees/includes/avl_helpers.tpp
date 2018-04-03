/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */
#include "avl_helpers.h"

#include "assert.h"

namespace cg3 {

namespace internal {

/* ----- AVL HELPERS ----- */

/**
 * @brief Get max height of the subtree rooted in a node
 *
 * @param[in] node Root node
 * @return Max height of the subtree
 */
template <class Node>
TreeSize getHeightHelper(const Node* node)
{
    if (node == nullptr)
        return 0;

    return node->height;
}

/**
 * @brief Update heights climbing on the parents
 *
 * @param[in] node Starting node
 */
template <class Node>
void updateHeightHelper(Node* node)
{
    if (node != nullptr) {
        bool done;
        do {
            //Update height
            node->height = 1 + std::max(getHeightHelper(node->left),
                                        getHeightHelper(node->right));

            //Done flag
            done = (node->parent == nullptr || node->height+1 == node->parent->height);

            //Next parent
            node = node->parent;
        } while (!done);
    }
}

/**
 * @brief Rebalance with left/right rotations to make the
 * BST satisfy the AVL constraints
 *
 * @param[in] node Starting node
 * @param[in] node Root node of the BST
 */
template <class Node>
void rebalanceHelper(Node* node, Node*& rootNode)
{
    //Null handler
    if (node == nullptr)
        return;

    //Not balanced node
    Node* n = node;
    int balanceFactor = (int)(getHeightHelper(n->right) - getHeightHelper(n->left));

    //Climb on parents to find the not balanced node
    while (n != nullptr && balanceFactor >= -1 && balanceFactor <= 1) {
        n = n->parent;

        if (n != nullptr) {
            //Compute balance factor
            balanceFactor = (int)(getHeightHelper(n->right) - getHeightHelper(n->left));

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
                n = rightRotateHelper(n);
            }
            //Left right case
            else {
                n->left = leftRotateHelper(n->left);
                n = rightRotateHelper(n);
            }
        }
        else if (balanceFactor > 1) {
            Node* rightright = n->right->right;
            Node* rightleft = n->right->left;

            //Right right case
            if (getHeightHelper(rightright) >= getHeightHelper(rightleft)) {
                n = leftRotateHelper(n);
            }
            //Left right case
            else {
                n->right = rightRotateHelper(n->right);
                n = leftRotateHelper(n);
            }
        }


        //Set root
        if (n->parent == nullptr) {
            rootNode = n;
        }

        //Update heights on parents and rebalance them if needed
        updateHeightAndRebalanceHelper(n->parent, rootNode);
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
void updateHeightAndRebalanceHelper(Node* node, Node*& rootNode)
{
    updateHeightHelper(node);
    rebalanceHelper(node, rootNode);
}




/* ----- ROTATIONS ----- */

/**
 * @brief Left rotation
 *
 * @param[in] a Node to be rotated
 * @return New node in the position of the original node after the rotation
 */
template <class Node>
Node* leftRotateHelper(Node* a)
{
    Node *b = a->right;
    b->parent = a->parent;
    a->right = b->left;

    if (a->right != nullptr)
        a->right->parent = a;

    b->left = a;
    a->parent = b;

    if (b->parent != nullptr) {
        if (b->parent->right == a) {
            b->parent->right = b;
        }
        else {
            b->parent->left = b;
        }
    }

    //Update heights
    updateHeightHelper(a);

    return b;
}

/**
 * @brief Right rotation
 *
 * @param[in] a Node to be rotated
 * @return New node in the position of the original node after the rotation
 */
template <class Node>
Node* rightRotateHelper(Node* a)
{
    Node* b = a->left;
    b->parent = a->parent;
    a->left = b->right;

    if (a->left != nullptr)
        a->left->parent = a;

    b->right = a;
    a->parent = b;

    if (b->parent != nullptr) {
        if (b->parent->right == a) {
            b->parent->right = b;
        }
        else {
            b->parent->left = b;
        }
    }

    //Update heights
    updateHeightHelper(a);

    return b;
}

}

}

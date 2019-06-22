/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */
#ifndef CG3_AVLHELPERS_H
#define CG3_AVLHELPERS_H

#include "tree_common.h"

#include <vector>

namespace cg3 {

namespace internal {

/* AVL helpers */

template <class Node>
inline TreeSize getHeightHelper(const Node* node);

template <class Node>
inline void updateHeightHelper(Node* node);

template <class Node>
inline void rebalanceHelper(Node* node, Node*& rootNode);

template <class Node>
inline void updateHeightAndRebalanceHelper(Node* node, Node*& rootNode);


/* AVL Rotations helper */

template <class Node>
inline Node* leftRotateHelper(Node* a);

template <class Node>
inline Node* rightRotateHelper(Node* a);

}

}

#include "avl_helpers.cpp"

#endif // CG3_AVLHELPERS_H

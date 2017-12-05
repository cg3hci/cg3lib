/**
    @author Stefano Nuvoli
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

#include "avl_helpers.tpp"

#endif // CG3_AVLHELPERS_H

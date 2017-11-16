/**
    @author Stefano Nuvoli
*/
#ifndef CG3_AVLHELPERS_H
#define CG3_AVLHELPERS_H

#include "treecommon.h"

#include <vector>

namespace cg3 {


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

#include "avlhelpers.tpp"

#endif // CG3_AVLHELPERS_H

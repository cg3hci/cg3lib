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
TreeSize getHeightHelper(const Node* node);

template <class Node>
void updateHeightHelper(Node* node);

template <class Node>
void rebalanceHelper(Node* node, Node*& rootNode);

template <class Node>
void updateHeightAndRebalanceHelper(Node* node, Node*& rootNode);


/* AVL Rotations helper */

template <class Node>
Node* leftRotateHelper(Node* a);

template <class Node>
Node* rightRotateHelper(Node* a);

}

#include "avlhelpers.tpp"

#endif // CG3_AVLHELPERS_H

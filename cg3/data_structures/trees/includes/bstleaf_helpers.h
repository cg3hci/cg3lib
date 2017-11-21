/**
    @author Stefano Nuvoli
*/
#ifndef CG3_BSTLEAFHELPERS_H
#define CG3_BSTLEAFHELPERS_H

#include "bst_helpers.h"

#include "tree_common.h"

#include <vector>

namespace cg3 {


/* Basic BST operation helpers */

template <class Node, class K>
inline Node* insertNodeHelperLeaf(Node*& newNode, Node*& rootNode, LessComparatorType<K> lessComparator);

template <class Node, class K>
inline Node* findNodeHelperLeaf(const K& key, Node*& rootNode, LessComparatorType<K> lessComparator);

template <class Node>
inline Node* eraseNodeHelperLeaf(Node*& node, Node*& rootNode);



/* Construction helpers */

template <class Node, class K>
inline TreeSize constructionMedianHelperLeaf(
        std::vector<Node*>& sortedNodes,
        const TreeSize start, const TreeSize end,
        Node*& rootNode,
        LessComparatorType<K> lessComparator);

template <class Node, class K>
inline TreeSize constructionBottomUpHelperLeaf(
        std::vector<Node*>& sortedVec,
        Node*& rootNode,
        LessComparatorType<K> lessComparator);


/* Range query helpers */

template <class Node, class K>
inline Node* findSplitNodeHelperLeaf(
        const K& start, const K& end,
        Node* rootNode,
        LessComparatorType<K> lessComparator);

template <class Node>
inline void reportSubTreeHelperLeaf(
        Node* node,
        std::vector<Node*>& out);


template <class Node, class K>
inline void rangeQueryHelperLeaf(
        const K& start, const K& end,
        std::vector<Node*> &out,
        Node* rootNode,
        LessComparatorType<K> lessComparator);



/* Successors/Predecessors Min/Max */

template <class Node>
inline Node* getSuccessorHelperLeaf(Node* node);

template <class Node>
inline Node* getPredecessorHelperLeaf(Node* node);

template <class Node>
inline Node* getMinimumHelperLeaf(Node* node);

template <class Node>
inline Node* getMaximumHelperLeaf(Node* node);



}

#include "bstleaf_helpers.tpp"

#endif // CG3_BSTLEAFHELPERS_H

/**
    @author Stefano Nuvoli
*/
#ifndef CG3_BSTLEAFHELPERS_H
#define CG3_BSTLEAFHELPERS_H

#include "bsthelpers.h"

#include "treecommon.h"

#include <vector>

namespace cg3 {


/* Basic BST operation helpers */

template <class Node, class K>
Node* insertNodeHelperLeaf(Node*& newNode, Node*& rootNode, LessComparatorType<K> lessComparator);

template <class Node, class K>
Node* findNodeHelperLeaf(const K& key, Node*& rootNode, LessComparatorType<K> lessComparator);

template <class Node>
Node* eraseNodeHelperLeaf(Node*& node, Node*& rootNode);



/* Construction helpers */

template <class Node, class K>
TreeSize constructionMedianHelperLeaf(
        std::vector<Node*>& sortedNodes,
        const TreeSize start, const TreeSize end,
        Node*& rootNode,
        LessComparatorType<K> lessComparator);

template <class Node, class K>
TreeSize constructionBottomUpHelperLeaf(
        std::vector<Node*>& sortedVec,
        Node*& rootNode,
        LessComparatorType<K> lessComparator);


/* Range query helpers */

template <class Node, class K>
Node* findSplitNodeHelperLeaf(
        const K& start, const K& end,
        Node* rootNode,
        LessComparatorType<K> lessComparator);

template <class Node>
void reportSubTreeHelperLeaf(
        Node* node,
        std::vector<Node*>& out);


template <class Node, class K>
void rangeQueryHelperLeaf(
        const K& start, const K& end,
        std::vector<Node*> &out,
        Node* rootNode,
        LessComparatorType<K> lessComparator);



/* Successors/Predecessors Min/Max */

template <class Node>
Node* getSuccessorHelperLeaf(Node* node);

template <class Node>
Node* getPredecessorHelperLeaf(Node* node);

template <class Node>
Node* getMinimumHelperLeaf(Node* node);

template <class Node>
Node* getMaximumHelperLeaf(Node* node);



}

#include "bstleafhelpers.tpp"

#endif // CG3_BSTLEAFHELPERS_H

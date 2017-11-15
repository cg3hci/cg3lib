/**
    @author Stefano Nuvoli
*/
#ifndef CG3_BSTINNERHELPERS_H
#define CG3_BSTINNERHELPERS_H

#include "treecommon.h"

#include "bsthelpers.h"

#include <vector>

namespace cg3 {


/* Basic BST operation helpers */

template <class Node, class K>
Node* insertNodeHelperInner(Node*& newNode, Node*& rootNode, LessComparatorType<K> lessComparator);

template <class Node, class K>
Node* findNodeHelperInner(const K& key, Node*& rootNode, LessComparatorType<K> lessComparator);

template <class Node>
Node* eraseNodeHelperInner(Node*& node, Node*& rootNode);



/* Construction helpers */

template <class Node, class K>
TreeSize constructionMedianHelperInner(
        std::vector<Node*>& sortedNodes,
        const TreeSize start, const TreeSize end,
        Node*& rootNode,
        LessComparatorType<K> lessComparator);



/* Range query helpers */

template <class Node, class K>
Node* findSplitNodeHelperInner(
        const K& start, const K& end,
        Node* rootNode,
        LessComparatorType<K> lessComparator);

template <class Node>
void reportSubTreeHelperInner(
        Node* node,
        std::vector<Node*>& out);

template <class Node, class K>
void rangeQueryHelperInner(
        const K& start, const K& end,
        std::vector<Node*> &out,
        Node* rootNode,
        LessComparatorType<K> lessComparator);



/* Successors/Predecessors Min/Max */

template <class Node>
Node* getSuccessorHelperInner(Node* node);

template <class Node>
Node* getPredecessorHelperInner(Node* node);

template <class Node>
Node* getMinimumHelperInner(Node* node);

template <class Node>
Node* getMaximumHelperInner(Node* node);



}

#include "bstinnerhelpers.tpp"

#endif // CG3_BSTINNERHELPERS_H

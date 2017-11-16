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
inline Node* insertNodeHelperInner(Node*& newNode, Node*& rootNode, LessComparatorType<K> lessComparator);

template <class Node, class K>
inline Node* findNodeHelperInner(const K& key, Node*& rootNode, LessComparatorType<K> lessComparator);

template <class Node>
inline Node* eraseNodeHelperInner(Node*& node, Node*& rootNode);



/* Construction helpers */

template <class Node, class K>
inline TreeSize constructionMedianHelperInner(
        std::vector<Node*>& sortedNodes,
        const TreeSize start, const TreeSize end,
        Node*& rootNode,
        LessComparatorType<K> lessComparator);



/* Range query helpers */

template <class Node, class K>
inline Node* findSplitNodeHelperInner(
        const K& start, const K& end,
        Node* rootNode,
        LessComparatorType<K> lessComparator);

template <class Node>
inline void reportSubTreeHelperInner(
        Node* node,
        std::vector<Node*>& out);

template <class Node, class K>
inline void rangeQueryHelperInner(
        const K& start, const K& end,
        std::vector<Node*> &out,
        Node* rootNode,
        LessComparatorType<K> lessComparator);



/* Successors/Predecessors Min/Max */

template <class Node>
inline Node* getSuccessorHelperInner(Node* node);

template <class Node>
inline Node* getPredecessorHelperInner(Node* node);

template <class Node>
inline Node* getMinimumHelperInner(Node* node);

template <class Node>
inline Node* getMaximumHelperInner(Node* node);



}

#include "bstinnerhelpers.tpp"

#endif // CG3_BSTINNERHELPERS_H

/**
    @author Stefano Nuvoli
*/
#ifndef CG3_RANGETREEHELPERS_H
#define CG3_RANGETREEHELPERS_H

#include "treecommon.h"

#include <vector>

namespace cg3 {


    /* Multidimensional range tree helper */

    template <class Node, class K>
    void rangeQueryRangeTreeHelper(
            const K& start, const K& end,
            Node*& rootNode,
            std::vector<Node*> &out,
            LessComparatorType<K> lessComparator,
            const unsigned int dim);



    /* Helpers for associate range trees */

    template <class Node, class K, class T>
    void createAssociatedTreeHelper(
            Node* node, const unsigned int dim,
            std::vector<LessComparatorType<K>> customComparators);

    template <class Node, class K, class T>
    void createParentAssociatedTreeHelper(
            Node *node, const unsigned int dim,
            std::vector<LessComparatorType<K>> customComparators);


    template <class Node, class K, class T>
    void insertIntoAssociatedTreeHelper(
            Node* node,
            const K& key,
            const T& value,
            const unsigned int dim);

    template <class Node, class K, class T>
    void insertIntoParentAssociatedTreesHelper(
            Node* node,
            const K& key,
            const T& value,
            const unsigned int dim);


    template <class Node, class K>
    void eraseFromAssociatedTreeHelper(
            Node* node,
            const K& key,
            const unsigned int dim);

    template <class Node, class K>
    void eraseFromParentAssociatedTreesHelper(
            Node* node,
            const K& key,
            const unsigned int dim);



    /* AVL helpers for range tree */

    template <class Node>
    void rebalanceRangeTreeHelper(
            Node* node,
            Node*& rootNode,
            const unsigned int dim);

    template <class Node>
    void updateHeightAndRebalanceRangeTreeHelper(
            Node* node,
            Node*& rootNode,
            const unsigned int dim);

    template <class Node>
    Node* leftRotateRangeTreeHelper(Node* a, const unsigned int dim);

    template <class Node>
    Node* rightRotateRangeTreeHelper(Node* a, const unsigned int dim);
}

#include "rangetreehelpers.tpp"

#endif // CG3_RANGETREEHELPERS_H

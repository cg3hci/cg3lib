/**
    @author Stefano Nuvoli
*/
#ifndef CG3_RANGETREEHELPERS_H
#define CG3_RANGETREEHELPERS_H

#include "treecommon.h"

#include <vector>

namespace cg3 {



    /* Helpers for associate range trees */

    template <class Node, class K, class T>
    inline void createAssociatedTreeHelper(
            Node* node, const unsigned int dim,
            std::vector<LessComparatorType<K>> customComparators);

    template <class Node, class K, class T>
    inline void createParentAssociatedTreeHelper(
            Node *node, const unsigned int dim,
            std::vector<LessComparatorType<K>> customComparators);


    template <class Node, class K, class T>
    inline Node* insertIntoAssociatedTreeHelper(
            Node* node,
            const K& key,
            const T& value,
            const unsigned int dim);

    template <class Node, class K, class T>
    inline Node* insertIntoParentAssociatedTreesHelper(
            Node* node,
            const K& key,
            const T& value,
            const unsigned int dim);


    template <class Node, class K>
    inline void eraseFromAssociatedTreeHelper(
            Node* node,
            const K& key,
            const unsigned int dim);

    template <class Node, class K>
    inline void eraseFromParentAssociatedTreesHelper(
            Node* node,
            const K& key,
            const unsigned int dim);



    /* AVL helpers for range tree */

    template <class Node>
    inline void rebalanceRangeTreeHelper(
            Node* node,
            Node*& rootNode,
            const unsigned int dim);

    template <class Node>
    inline void updateHeightAndRebalanceRangeTreeHelper(
            Node* node,
            Node*& rootNode,
            const unsigned int dim);

    template <class Node>
    inline Node* leftRotateRangeTreeHelper(Node* a, const unsigned int dim);

    template <class Node>
    inline Node* rightRotateRangeTreeHelper(Node* a, const unsigned int dim);
}

#include "rangetreehelpers.tpp"

#endif // CG3_RANGETREEHELPERS_H

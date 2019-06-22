/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */
#ifndef CG3_RANGETREE_H
#define CG3_RANGETREE_H

#include <vector>
#include <algorithm>

#include "includes/tree_common.h"

#include "includes/iterators/tree_iterator.h"
#include "includes/iterators/tree_reverseiterator.h"
#include "includes/iterators/tree_insertiterator.h"
#include "includes/iterators/tree_rangebased_iterators.h"

#include "includes/nodes/rangetree_node.h"


namespace cg3 {


/**
 * @brief Auto-balancing (AVL) multi-dimensional range tree
 *
 * Values are saved only in the leaves.
 * No duplicates are allowed.
 * Keys and values are saved (and copied) in each dimension associated range tree.
 * Use pointers as template arguments if it is needed to save memory. This choice has
 * been made because we prefer to allow the user, if needed, to easily implement range
 * searches in just a subset of the dimensions of the object.
 *
 */
template <class K, class T = K, class C = DefaultComparatorType<K>>
class RangeTree
{


public:

    /* Typedefs */

    typedef internal::RangeTreeNode<K,T,C> Node;

    typedef DefaultComparatorType<K> DefaultComparator;

    typedef TreeGenericIterator<RangeTree<K,T,C>, Node> generic_iterator;

    typedef TreeIterator<RangeTree<K,T,C>, Node, T> iterator;
    typedef TreeIterator<RangeTree<K,T,C>, Node, const T> const_iterator;

    typedef TreeReverseIterator<RangeTree<K,T,C>, Node, T> reverse_iterator;
    typedef TreeReverseIterator<RangeTree<K,T,C>, Node, const T> const_reverse_iterator;

    typedef TreeInsertIterator<RangeTree<K,T,C>, K> insert_iterator;

    typedef TreeRangeBasedIterator<RangeTree<K,T,C>> RangeBasedIterator;
    typedef TreeRangeBasedConstIterator<RangeTree<K,T,C>> RangeBasedConstIterator;
    typedef TreeRangeBasedReverseIterator<RangeTree<K,T,C>> RangeBasedReverseIterator;
    typedef TreeRangeBasedConstReverseIterator<RangeTree<K,T,C>> RangeBasedConstReverseIterator;



    /* Constructors/destructor */

    explicit RangeTree(const unsigned int dim,
              const std::vector<C>& customComparators);
    explicit RangeTree(const unsigned int dim,
              const std::vector<std::pair<K,T>>& vec,
              const std::vector<C>& customComparators);
    explicit RangeTree(const unsigned int dim,
              const std::vector<K>& vec,
              const std::vector<C>& customComparators);

    RangeTree(const RangeTree<K,T,C>& bst);
    RangeTree(RangeTree<K,T,C>&& bst);

    ~RangeTree();



    /* Public methods */

    void construction(const std::vector<K>& vec);
    void construction(const std::vector<std::pair<K,T>>& vec);

    iterator insert(const K& key);
    iterator insert(const K& key, const T& value);

    bool erase(const K& key);

    iterator find(const K& key);


    size_t size();
    bool empty();

    void clear();

    size_t getHeight();



    template <class OutputIterator>
    void rangeQuery(
            const K& start, const K& end,
            OutputIterator out);



    /* Iterator Min/Max Next/Prev */

    iterator getMin();
    iterator getMax();

    generic_iterator getNext(const generic_iterator it);
    generic_iterator getPrev(const generic_iterator it);


    /* Iterators */

    iterator begin();
    iterator end();

    const_iterator cbegin();
    const_iterator cend();

    reverse_iterator rbegin();
    reverse_iterator rend();

    const_reverse_iterator crbegin();
    const_reverse_iterator crend();

    insert_iterator inserter();

    RangeBasedIterator getIterator();
    RangeBasedConstIterator getConstIterator();
    RangeBasedReverseIterator getReverseIterator();
    RangeBasedConstReverseIterator getConstReverseIterator();


    /* Swap function and assignment */

    inline RangeTree<K,T,C>& operator= (RangeTree<K,T,C> bst);
    inline void swap(RangeTree<K,T,C>& bst);

protected:

    /* Protected fields */

    Node* root;

    size_t entries;

    unsigned int dim;

    C comparator;
    std::vector<C> customComparators;


    /* Protected methods */

    void initialize();

    Node* copyRangeTreeSubtree(
            const Node* rootNode,
            Node* parent = nullptr);


    /* Range query helpers */

    inline void rangeQueryHelper(
            const K& start, const K& end,
            std::vector<Node*>& out);

    inline void rangeSearchInNextDimensionHelper(
            Node* node,
            const K& start,
            const K& end,
            std::vector<Node*>& out);




    /* Helpers for associate range trees */

    inline void createAssociatedTreeHelper(
            Node* node);

    inline void createParentAssociatedTreeHelper(
            Node *node);



    inline Node* insertIntoAssociatedTreeHelper(
            Node* node,
            const K& key,
            const T& value);

    inline Node* insertIntoParentAssociatedTreesHelper(
            Node* node,
            const K& key,
            const T& value);



    inline void eraseFromAssociatedTreeHelper(
            Node* node,
            const K& key);

    inline void eraseFromParentAssociatedTreesHelper(
            Node* node,
            const K& key);



    /* AVL helpers for range tree */

    inline void rebalanceRangeTreeHelper(Node* node);

    inline void updateHeightAndRebalanceRangeTreeHelper(Node* node);

    inline Node* leftRotateRangeTreeHelper(Node* a);

    inline Node* rightRotateRangeTreeHelper(Node* a);

};


template <class K, class T, class C>
void swap(RangeTree<K,T,C>& b1, RangeTree<K,T,C>& b2);

}


#include "rangetree.cpp"

#include "includes/rangetree_types.h"


#endif // CG3_RANGETREE_H

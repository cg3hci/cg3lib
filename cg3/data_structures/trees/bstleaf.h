/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */
#ifndef CG3_BSTLEAF_H
#define CG3_BSTLEAF_H

#include <vector>
#include <utility>

#include "includes/tree_common.h"

#include "includes/iterators/tree_iterator.h"
#include "includes/iterators/tree_reverseiterator.h"
#include "includes/iterators/tree_insertiterator.h"
#include "includes/iterators/tree_rangebased_iterators.h"

#include "includes/nodes/bst_node.h"

namespace cg3 {

/**
 * @brief A binary search tree
 *
 * Keys and values are saved only in the leaves
 * No duplicates are allowed.
 */
template <class K, class T = K>
class BSTLeaf
{

public:

    /* Typedefs */

    typedef internal::BSTNode<K,T> Node;

    typedef LessComparatorType<K> LessComparator;

    typedef TreeGenericIterator<BSTLeaf<K,T>, Node> generic_iterator;

    typedef TreeIterator<BSTLeaf<K,T>, Node, T> iterator;
    typedef TreeIterator<BSTLeaf<K,T>, Node, const T> const_iterator;

    typedef TreeReverseIterator<BSTLeaf<K,T>, Node, T> reverse_iterator;
    typedef TreeReverseIterator<BSTLeaf<K,T>, Node, const T> const_reverse_iterator;

    typedef TreeInsertIterator<BSTLeaf<K,T>, K> insert_iterator;

    typedef TreeRangeBasedIterator<BSTLeaf<K,T>> RangeBasedIterator;
    typedef TreeRangeBasedConstIterator<BSTLeaf<K,T>> RangeBasedConstIterator;
    typedef TreeRangeBasedReverseIterator<BSTLeaf<K,T>> RangeBasedReverseIterator;
    typedef TreeRangeBasedConstReverseIterator<BSTLeaf<K,T>> RangeBasedConstReverseIterator;



    /* Constructors/destructor */

    BSTLeaf(const LessComparator customComparator = &internal::defaultComparator<K>);
    BSTLeaf(const std::vector<std::pair<K,T>>& vec,
            const LessComparator customComparator = &internal::defaultComparator<K>);
    BSTLeaf(const std::vector<K>& vec,
            const LessComparator customComparator = &internal::defaultComparator<K>);

    BSTLeaf(const BSTLeaf<K,T>& bst);
    BSTLeaf(BSTLeaf<K,T>&& bst);

    ~BSTLeaf();



    /* Public methods */

    void construction(const std::vector<K>& vec);
    void construction(const std::vector<std::pair<K,T>>& vec);

    iterator insert(const K& key);
    iterator insert(const K& key, const T& value);

    bool erase(const K& key);
    void erase(generic_iterator it);

    iterator find(const K& key);

    iterator findLower(const K& key);
    iterator findUpper(const K& key);


    TreeSize size();
    bool empty();

    void clear();

    TreeSize getHeight();



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

    inline BSTLeaf<K,T>& operator= (BSTLeaf<K,T> bst);
    inline void swap(BSTLeaf<K,T>& bst);

protected:

    /* Protected fields */

    Node* root;

    TreeSize entries;

    LessComparator lessComparator;


private:

    /* Private methods */

    void initialize();

};


template <class K, class T>
void swap(BSTLeaf<K,T>& b1, BSTLeaf<K,T>& b2);


}


#include "bstleaf.tpp"

#endif // CG3_BSTLEAF_H





/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */
#ifndef CG3_AVLLEAF_H
#define CG3_AVLLEAF_H

#include <vector>
#include <utility>

#include "includes/tree_common.h"

#include "includes/iterators/tree_iterator.h"
#include "includes/iterators/tree_reverseiterator.h"
#include "includes/iterators/tree_insertiterator.h"
#include "includes/iterators/tree_rangebased_iterators.h"

#include "includes/nodes/avl_node.h"

namespace cg3 {

/**
 * @brief An autobalancing AVL binary search tree
 *
 * Keys and values are saved only in the leaves.
 * No duplicates are allowed.
 */
template <class K, class T = K, class C = DefaultComparatorType<K>>
class AVLLeaf
{

public:

    /* Typedefs */

    typedef internal::AVLNode<K,T> Node;

    typedef TreeGenericIterator<AVLLeaf<K,T,C>, Node> generic_iterator;

    typedef TreeIterator<AVLLeaf<K,T,C>, Node, T> iterator;
    typedef TreeIterator<AVLLeaf<K,T,C>, Node, const T> const_iterator;

    typedef TreeReverseIterator<AVLLeaf<K,T,C>, Node, T> reverse_iterator;
    typedef TreeReverseIterator<AVLLeaf<K,T,C>, Node, const T> const_reverse_iterator;

    typedef TreeInsertIterator<AVLLeaf<K,T,C>, K> insert_iterator;

    typedef TreeRangeBasedIterator<AVLLeaf<K,T,C>> RangeBasedIterator;
    typedef TreeRangeBasedConstIterator<AVLLeaf<K,T,C>> RangeBasedConstIterator;
    typedef TreeRangeBasedReverseIterator<AVLLeaf<K,T,C>> RangeBasedReverseIterator;
    typedef TreeRangeBasedConstReverseIterator<AVLLeaf<K,T,C>> RangeBasedConstReverseIterator;



    /* Constructors/destructor */

    explicit AVLLeaf(const C& customComparator = &internal::defaultComparator<K>);
    explicit AVLLeaf(const std::vector<std::pair<K,T>>& vec,
            const C& customComparator = &internal::defaultComparator<K>);
    explicit AVLLeaf(const std::vector<K>& vec,
            const C& customComparator = &internal::defaultComparator<K>);

    AVLLeaf(const AVLLeaf<K,T,C>& bst);
    AVLLeaf(AVLLeaf<K,T,C>&& bst);

    ~AVLLeaf();



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

    inline AVLLeaf<K,T,C>& operator= (AVLLeaf<K,T,C> bst);
    inline void swap(AVLLeaf<K,T,C>& bst);

protected:

    /* Protected fields */

    Node* root;

    TreeSize entries;

    C comparator;


    /* Protected methods */

    void initialize();

};

template <class K, class T, class C>
void swap(AVLLeaf<K,T,C>& b1, AVLLeaf<K,T,C>& b2);

}


#include "avlleaf.cpp"

#endif // CG3_AVLLEAF_H





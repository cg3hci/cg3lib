/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */
#ifndef CG3_AVLINNER_H
#define CG3_AVLINNER_H

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
 * Keys and values are saved in all nodes, not only in the leaves. The implementation
 * is performed following "Introduction to Algorithms" (Cormen, 2011).
 * No duplicates are allowed.
 */
template <class K, class T = K, class C = DefaultComparatorType<K>>
class AVLInner
{

public:

    /* Typedefs */

    typedef internal::AVLNode<K,T> Node;

    typedef TreeGenericIterator<AVLInner<K,T,C>, Node> generic_iterator;

    typedef TreeIterator<AVLInner<K,T,C>, Node, T> iterator;
    typedef TreeIterator<AVLInner<K,T,C>, Node, const T> const_iterator;

    typedef TreeReverseIterator<AVLInner<K,T,C>, Node, T> reverse_iterator;
    typedef TreeReverseIterator<AVLInner<K,T,C>, Node, const T> const_reverse_iterator;

    typedef TreeInsertIterator<AVLInner<K,T,C>, K> insert_iterator;

    typedef TreeRangeBasedIterator<AVLInner<K,T,C>> RangeBasedIterator;
    typedef TreeRangeBasedConstIterator<AVLInner<K,T,C>> RangeBasedConstIterator;
    typedef TreeRangeBasedReverseIterator<AVLInner<K,T,C>> RangeBasedReverseIterator;
    typedef TreeRangeBasedConstReverseIterator<AVLInner<K,T,C>> RangeBasedConstReverseIterator;


    /* Constructors/destructor */

    explicit AVLInner(const C& customComparator = &internal::defaultComparator<K>);
    explicit AVLInner(const std::vector<std::pair<K,T>>& vec,
             const C& customComparator = &internal::defaultComparator<K>);
    explicit AVLInner(const std::vector<K>& vec,
             const C& customComparator = &internal::defaultComparator<K>);

    AVLInner(const AVLInner<K,T,C>& bst);
    AVLInner(AVLInner<K,T,C>&& bst);

    ~AVLInner();



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

    inline AVLInner<K,T,C>& operator= (AVLInner<K,T,C> bst);
    inline void swap(AVLInner<K,T,C>& bst);

protected:

    /* Protected fields */

    Node* root;

    TreeSize entries;

    C comparator;


    /* Protected methods */

    void initialize();

};

template <class K, class T, class C>
void swap(AVLInner<K,T,C>& b1, AVLInner<K,T,C>& b2);


}


#include "avlinner.cpp"

#endif // CG3_AVLINNER_H





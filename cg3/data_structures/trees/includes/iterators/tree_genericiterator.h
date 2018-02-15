/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */
#ifndef CG3_TREEGENERICITERATOR_H
#define CG3_TREEGENERICITERATOR_H

namespace cg3 {

/**
 * @brief The generic iterator for the binary search tree
 */
template <class B, class N>
class TreeGenericIterator {

    template <class T1, class T2, class T3>
    friend class TreeIterator;
    template <class T1, class T2, class T3>
    friend class TreeReverseIterator;

    template <class T1, class T2, class T3>
    friend class BSTInner;
    template <class T1, class T2, class T3>
    friend class BSTLeaf;
    template <class T1, class T2, class T3>
    friend class AVLInner;
    template <class T1, class T2, class T3>
    friend class AVLLeaf;
    template <class T1, class T2, class T3>
    friend class RangeTree;
    template <int T1, class T2, class T3, class T4>
    friend class AABBTree;

protected:

    /* Constructors */

    inline TreeGenericIterator(B* bst, N* node) :
        bst(bst), node(node) {}


    /* Fields */

    B* bst;
    N* node;

};


}

#endif // CG3_TREEGENERICITERATOR_H

/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */
#ifndef CG3_TREEREVERSEITERATOR_H
#define CG3_TREEREVERSEITERATOR_H

#include "tree_genericiterator.h"
#include <iterator>

namespace cg3 {

/**
 * @brief The reverse iterator class for BST
 */
template <class B, class N, class T>
class TreeReverseIterator :
        public TreeGenericIterator<B,N>,
        public std::iterator<std::bidirectional_iterator_tag, T>
{

public:

    /* Constructors */

    inline TreeReverseIterator(B* bst, N* node) :
        TreeGenericIterator<B,N>(bst,node) {}


    /* Iterator operators */

    inline bool operator == (const TreeReverseIterator& otherIterator) const;
    inline bool operator != (const TreeReverseIterator& otherIterator) const;

    inline TreeReverseIterator operator ++ ();
    inline TreeReverseIterator operator ++ (int);
    inline TreeReverseIterator operator + (int);
    inline TreeReverseIterator operator += (int);

    inline TreeReverseIterator operator -- ();
    inline TreeReverseIterator operator -- (int);
    inline TreeReverseIterator operator - (int);
    inline TreeReverseIterator operator -= (int);

    inline T& operator *() const;

protected:

    /* Protected methods */

    inline void next();
    inline void prev();

};



}


#include "tree_reverseiterator.cpp"

#endif // CG3_TREEREVERSEITERATOR_H

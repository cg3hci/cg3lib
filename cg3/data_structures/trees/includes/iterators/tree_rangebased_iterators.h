/**
    @author Stefano Nuvoli
*/
#ifndef CG3_TREERANGEBASEDITERATORS_H
#define CG3_TREERANGEBASEDITERATORS_H

#include "tree_iterator.h"
#include "tree_reverseiterator.h"

namespace cg3 {

/**
 * @brief The range based iterator class for BST
 */
template <class B>
class TreeRangeBasedIterator
{

public:

    inline TreeRangeBasedIterator(B* bst);

    inline typename B::iterator begin();
    inline typename B::iterator end();

private:

    B* bst;

};

/**
 * @brief The range based const iterator class for BST
 */
template <class B>
class TreeRangeBasedConstIterator
{

public:

    inline TreeRangeBasedConstIterator(B* bst);

    inline typename B::const_iterator begin();
    inline typename B::const_iterator end();

private:

    B* bst;

};

/**
 * @brief The range based reverse iterator class for BST
 */
template <class B>
class TreeRangeBasedReverseIterator
{

public:

    inline TreeRangeBasedReverseIterator(B* bst);

    inline typename B::reverse_iterator begin();
    inline typename B::reverse_iterator end();

private:

    B* bst;

};

/**
 * @brief The range based const reverse iterator class for BST
 */
template <class B>
class TreeRangeBasedConstReverseIterator
{

public:

    inline TreeRangeBasedConstReverseIterator(B* bst);

    inline typename B::const_reverse_iterator begin();
    inline typename B::const_reverse_iterator end();

private:

    B* bst;

};


}




#include "tree_rangebased_iterators.tpp"

#endif // CG3_TREERANGEBASEDITERATORS_H

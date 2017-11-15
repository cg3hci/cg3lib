/**
    @author Stefano Nuvoli
*/
#ifndef CG3_TREEREVERSEITERATOR_H
#define CG3_TREEREVERSEITERATOR_H

#include "treegenericiterator.h"
#include <iterator>

namespace cg3 {

/**
 * @brief The reverse iteratro class for BST
 */
template <class B, class N, class T>
class TreeReverseIterator :
        public TreeGenericIterator<B,N>,
        public std::iterator<std::bidirectional_iterator_tag, T>
{

public:

    TreeReverseIterator(B* bst, N* node) : TreeGenericIterator<B,N>(bst,node) {}


    /* Iterator operators */

    bool operator == (const TreeReverseIterator& otherIterator) const;
    bool operator != (const TreeReverseIterator& otherIterator) const;

    TreeReverseIterator operator ++ ();
    TreeReverseIterator operator ++ (int);
    TreeReverseIterator operator + (int);
    TreeReverseIterator operator += (int);

    TreeReverseIterator operator -- ();
    TreeReverseIterator operator -- (int);
    TreeReverseIterator operator - (int);
    TreeReverseIterator operator -= (int);

    T& operator *() const;

protected:

    /* Protected methods */

    void next();
    void prev();

};



}


#include "treereverseiterator.tpp"

#endif // CG3_TREEREVERSEITERATOR_H

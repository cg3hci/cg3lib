/**
    @author Stefano Nuvoli
*/
#ifndef CG3_TREEITERATOR_H
#define CG3_TREEITERATOR_H

#include "treegenericiterator.h"
#include <iterator>

namespace cg3 {


/**
 * @brief The iterator class for BST
 */
template <class B, class N, class T>
class TreeIterator :
        public TreeGenericIterator<B,N>,
        public std::iterator<std::bidirectional_iterator_tag, T>
{

public:

    TreeIterator(B* bst, N* node) : TreeGenericIterator<B,N>(bst,node) {}


    /* Iterator operators */

    bool operator == (const TreeIterator& otherIterator) const;
    bool operator != (const TreeIterator& otherIterator) const;

    TreeIterator operator ++ ();
    TreeIterator operator ++ (int);
    TreeIterator operator + (int);
    TreeIterator operator += (int);

    TreeIterator operator -- ();
    TreeIterator operator -- (int);
    TreeIterator operator - (int);
    TreeIterator operator -= (int);

    T& operator *() const;

protected:

    /* Protected methods */

    void next();
    void prev();

};


}


#include "treeiterator.tpp"

#endif // CG3_TREEITERATOR_H

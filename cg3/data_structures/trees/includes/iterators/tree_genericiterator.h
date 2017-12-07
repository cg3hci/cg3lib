/**
    @author Stefano Nuvoli
*/
#ifndef CG3_TREEGENERICITERATOR_H
#define CG3_TREEGENERICITERATOR_H

namespace cg3 {

/**
 * @brief The generic iterator for the binary search tree
 */
template <class B, class N>
class TreeGenericIterator {

public:

    /* Constructors */

    inline TreeGenericIterator(B* bst, N* node);


    /* Fields */

    N* node;
    B* bst;

};


}

#include "tree_genericiterator.tpp"

#endif // CG3_TREEGENERICITERATOR_H

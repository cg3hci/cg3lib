/**
    @author Stefano Nuvoli
*/
#ifndef CG3_BSTHELPERS_H
#define CG3_BSTHELPERS_H

#include "tree_common.h"

#include <vector>

namespace cg3 {

namespace internal {

    /* Basic BST operation helpers */

    template <class Node>
    inline void clearHelperInner(Node*& rootNode);



    /* Utilities */

    template <class Node>
    inline TreeSize getHeightRecursiveHelper(const Node* node);

    template <class Node>
    inline void replaceSubtreeHelperInner(const Node* u, Node* v, Node*& rootNode);

}

}

#include "bst_helpers.tpp"

#endif // CG3_BSTHELPERS_H

/**
    @author Stefano Nuvoli
*/
#ifndef CG3_BSTHELPERS_H
#define CG3_BSTHELPERS_H

#include "treecommon.h"

#include <vector>

namespace cg3 {

    /* Basic BST operation helpers */

    template <class Node>
    inline void clearHelperInner(Node*& rootNode);



    /* Utilities */

    template <class Node>
    inline TreeSize getHeightRecursiveHelper(const Node* node);

    template <class Node>
    inline void replaceSubtreeHelperInner(const Node* u, Node* v, Node*& rootNode);

}

#include "bsthelpers.tpp"

#endif // CG3_BSTHELPERS_H

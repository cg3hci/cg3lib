/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */
#ifndef CG3_BSTHELPERS_H
#define CG3_BSTHELPERS_H

#include "tree_common.h"

#include <vector>

namespace cg3 {

namespace internal {

    /* Basic BST operation helpers */

    template <class Node>
    inline void clearHelper(Node*& rootNode);

    template <class Node, class T>
    inline Node* copySubtreeHelper(
            const Node* rootNode,
            Node* parent = nullptr);


    /* Utilities */

    template <class Node>
    inline TreeSize getHeightRecursiveHelper(const Node* node);

    template <class Node>
    inline void replaceSubtreeHelperInner(
            const Node* u,
            Node* v,
            Node*& rootNode);

}

}

#include "bst_helpers.cpp"

#endif // CG3_BSTHELPERS_H

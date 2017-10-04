/**
    @author Stefano Nuvoli
*/
#ifndef CG3BST_H
#define CG3BST_H

/** Default BST implementations */
#include "bst/avlleaf.h"

namespace cg3 {

    /*
     * AVLLeaf implementation is the default one. The BST is an auto-balancing
     * AVL tree. Values are saved only in the leaves.
     */
    template <class K, class T = K> using BST = typename cg3::AVLLeaf<K, T>;

}

#endif // CG3BST_H

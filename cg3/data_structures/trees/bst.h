/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */
#ifndef CG3BST_H
#define CG3BST_H

/** Default BST implementations */
#include "avlleaf.h"

namespace cg3 {

/*
 * AVLLeaf implementation is the default one. The BST is an auto-balancing
 * AVL tree. Values are saved only in the leaves.
 */
template <class K, class T = K, class C = DefaultComparatorType<K>>
using BST = typename cg3::AVLLeaf<K, T, C>;

}

#endif // CG3BST_H

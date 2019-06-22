/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */
#ifndef CG3_AVLNODE_H
#define CG3_AVLNODE_H

#include "../tree_common.h"

namespace cg3 {

namespace internal {


/**
 * @brief The node of the binary search tree
 *
 */
template <class K, class T>
class AVLNode {

public:

    /* Constructors/Destructor */

    AVLNode(const K& key, const T& value);
    AVLNode(const K& key);

    ~AVLNode();


    /* Fields */

    K key;
    T* value;

    AVLNode* parent;
    AVLNode* left;
    AVLNode* right;

    TreeSize height;


    /* Public methods */

    inline bool isLeaf() const;

private:

    /* Private methods */

    inline void init(const K& key, T* value);
};

}

}

#include "avl_node.cpp"

#endif // CG3_AVLNODE_H

/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */
#ifndef CG3_BSTNODE_H
#define CG3_BSTNODE_H

namespace cg3 {

namespace internal {

/**
 * @brief The node of the binary search tree
 *
 */
template <class K, class T>
class BSTNode {

public:

    /* Constructors/Destructor */

    BSTNode(const K& key, const T& value);
    BSTNode(const K& key);

    ~BSTNode();


    /* Fields */

    K key;
    T* value;

    BSTNode* parent;
    BSTNode* left;
    BSTNode* right;


    /* Public methods */

    inline bool isLeaf() const;


private:

    /* Private methods */

    inline void init(const K& key, T* value);

};

}

}

#include "bst_node.cpp"

#endif // CG3_BSTNODE_H

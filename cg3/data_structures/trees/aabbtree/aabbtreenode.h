/**
    @author Stefano Nuvoli
*/
#ifndef CG3_AABBTREENODE_H
#define CG3_AABBTREENODE_H

#include "../aabbtree.h"

namespace cg3 {

/**
 * @brief The node of the binary search tree
 *
 */
template <int D, class K, class T>
class AABBTree<D,K,T>::Node {

public:

    typedef AABBTree::AABB AABB;

    /* Constructors/Destructor */

    Node(const K& key, const T& value);
    Node(const K& key);

    ~Node();


    /* Methods */

    inline bool isLeaf() const;
    /* Fields */

    K key;
    T* value;
    AABB aabb;


    Node* parent;
    Node* left;
    Node* right;

    size_t height;
};

}

#include "aabbtreenode.tpp"

#endif // CG3_AABBTREENODE_H

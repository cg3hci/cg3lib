/**
    @author Stefano Nuvoli
*/
#ifndef CG3_AABBNODE_H
#define CG3_AABBNODE_H

#include "../tree_common.h"

#include "aabb.h"

namespace cg3 {

/**
 * @brief The node of the binary search tree
 *
 */
template <int D, class K, class T>
class AABBNode {

public:

    /* Constructors/Destructor */

    AABBNode(const K& key, const T& value);
    AABBNode(const K& key);

    ~AABBNode();


    /* Fields */

    K key;
    T* value;

    AABB<D> aabb;

    AABBNode* parent;
    AABBNode* left;
    AABBNode* right;

    TreeSize height;


    /* Public methods */

    inline bool isLeaf() const;

private:

    /* Private methods */

    inline void init(const K& key, T* value);
};


}

#include "aabb_node.tpp"

#endif // CG3_AABBNODE_H

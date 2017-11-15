/**
    @author Stefano Nuvoli
*/
#ifndef CG3_RANGETREENODE_H
#define CG3_RANGETREENODE_H



namespace cg3 {

template <class K, class T>
class RangeTree;

/**
 * @brief The node of the binary search tree
 *
 */
template <class K, class T>
class RangeTreeNode {

public:

    /* Constructors/Destructor */

    RangeTreeNode(const K& key, const T& value);
    RangeTreeNode(const K& key);

    ~RangeTreeNode();


    /* Fields */

    K key;
    T* value;

    RangeTree<K,T>* assRangeTree;

    RangeTreeNode* parent;
    RangeTreeNode* left;
    RangeTreeNode* right;

    size_t height;


    /* Private methods */

    void init(const K& key, T* value);
    inline bool isLeaf() const;

};

}

#include "../../rangetree.h"

#include "rangetreenode.tpp"

#endif // CG3_RANGETREENODE_H

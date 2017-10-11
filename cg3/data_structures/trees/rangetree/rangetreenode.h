/**
    @author Stefano Nuvoli
*/
#ifndef CG3_RANGETREENODE_H
#define CG3_RANGETREENODE_H

#include "../rangetree.h"

namespace cg3 {

/**
 * @brief The node of the binary search tree
 *
 */
template <class K, class T>
class RangeTree<K,T>::Node {

    friend class RangeTree<K,T>;

private:

    /* Constructors/Destructor */

    Node(const K& key, const T& value);
    Node(const K& key);

    ~Node();


    /* Fields */

    K key;
    T* value;

    Node* parent;
    Node* left;
    Node* right;

    size_t height;

    RangeTree<K,T>* assRangeTree;


    /* Private methods */

    void init(const K& key, T* value);
    inline bool isLeaf() const;

};

}

#include "rangetreenode.tpp"

#endif // CG3_RANGETREENODE_H

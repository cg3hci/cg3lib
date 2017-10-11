/**
    @author Stefano Nuvoli
*/
#ifndef CG3_AVLLEAFNODE_H
#define CG3_AVLLEAFNODE_H

#include "../avlleaf.h"

namespace cg3 {

/**
 * @brief The node of the AVL binary search tree
 *
 */
template <class K, class T>
class AVLLeaf<K,T>::Node {

    friend class AVLLeaf<K,T>;

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


    /* Private methods */

    void init(const K& key, T* value);
    inline bool isLeaf() const;

};

}

#include "avlleafnode.tpp"

#endif // CG3_AVLLEAFNODE_H

/**
    @author Stefano Nuvoli
*/
#ifndef CG3_BSTLEAFNODE_H
#define CG3_BSTLEAFNODE_H

#include "../bstleaf.h"

namespace cg3 {

/**
 * @brief The node of the binary search tree
 *
 */
template <class K, class T>
class BSTLeaf<K,T>::Node {

public:

    /* Constructors/Destructor */

    Node(const K& key, const T& value);
    Node(const K& key);

    ~Node();


    /* Methods */

    inline bool isLeaf() const;


    /* Fields */

    K key;
    T* value;

    Node* parent;
    Node* left;
    Node* right;
};

}

#include "bstleafnode.tpp"

#endif // CG3_BSTLEAFNODE_H

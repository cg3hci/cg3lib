/**
    @author Stefano Nuvoli
*/
#ifndef CG3_AVLLEAFNODE_H
#define CG3_AVLLEAFNODE_H

#include "../avlleaf.h"

namespace cg3 {

/**
 * @brief The node of the binary search tree
 *
 */
template <class K, class T>
class AVLLeaf<K,T>::Node {

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

    size_t height;
};

}

#include "avlleafnode.tpp"

#endif // CG3_AVLLEAFNODE_H

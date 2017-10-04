/**
    @author Stefano Nuvoli
*/
#ifndef CG3_AVLINNERNODE_H
#define CG3_AVLINNERNODE_H

#include "../avlinner.h"

namespace cg3 {

/**
 * @brief The node of the binary search tree
 *
 */
template <class K, class T>
class AVLInner<K,T>::Node {

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

#include "avlinnernode.tpp"

#endif // CG3_AVLINNERNODE_H

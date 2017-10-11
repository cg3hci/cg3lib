/**
    @author Stefano Nuvoli
*/
#ifndef CG3_AVLINNERNODE_H
#define CG3_AVLINNERNODE_H

#include "../avlinner.h"

namespace cg3 {

/**
 * @brief The node of the AVL binary search tree
 *
 */
template <class K, class T>
class AVLInner<K,T>::Node {

    friend class AVLInner<K,T>;

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

#include "avlinnernode.tpp"

#endif // CG3_AVLINNERNODE_H

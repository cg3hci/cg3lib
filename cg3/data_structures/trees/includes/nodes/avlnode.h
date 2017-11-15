/**
    @author Stefano Nuvoli
*/
#ifndef CG3_AVLNODE_H
#define CG3_AVLNODE_H

#include "../treecommon.h"

namespace cg3 {

/**
 * @brief The node of the binary search tree
 *
 */
template <class K, class T>
class AVLNode {

public:

    /* Constructors/Destructor */

    AVLNode(const K& key, const T& value);
    AVLNode(const K& key);

    ~AVLNode();


    /* Fields */

    K key;
    T* value;

    AVLNode* parent;
    AVLNode* left;
    AVLNode* right;

    TreeSize height;


    /* Public methods */

    inline bool isLeaf() const;

private:

    /* Private methods */

    inline void init(const K& key, T* value);
};

}

#include "avlnode.tpp"

#endif // CG3_AVLNODE_H

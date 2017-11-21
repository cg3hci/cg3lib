/**
    @author Stefano Nuvoli
*/
#ifndef CG3_BSTNODE_H
#define CG3_BSTNODE_H

namespace cg3 {

/**
 * @brief The node of the binary search tree
 *
 */
template <class K, class T>
class BSTNode {

public:

    /* Constructors/Destructor */

    BSTNode(const K& key, const T& value);
    BSTNode(const K& key);

    ~BSTNode();


    /* Fields */

    K key;
    T* value;

    BSTNode* parent;
    BSTNode* left;
    BSTNode* right;

    /* Public methods */

    inline bool isLeaf() const;


private:

    /* Private methods */

    inline void init(const K& key, T* value);


};

}

#include "bst_node.tpp"

#endif // CG3_BSTNODE_H

/**
    @author Stefano Nuvoli
*/
#include "rangetree_node.h"

namespace cg3 {

namespace internal {


/* --------- CONSTRUCTORS/DESTRUCTOR --------- */

/**
 * @brief Constructor with key and value
 */
template <class K, class T>
RangeTreeNode<K,T>::RangeTreeNode(
        const K& key,
        const T& value)
{
    init(key, new T(value));
}

/**
 * @brief Constructor with only key
 */
template <class K, class T>
RangeTreeNode<K,T>::RangeTreeNode(const K& key)
{
    init(key, nullptr);
}

/**
 * @brief Destructor
 */
template <class K, class T>
RangeTreeNode<K,T>::~RangeTreeNode()
{
    if (this->value != nullptr) {
        delete this->value;
        this->value = nullptr;
    }

    if (this->assRangeTree != nullptr) {
        delete this->assRangeTree;
        this->assRangeTree = nullptr;
    }
}



/* --------- PRIVATE METHODS --------- */


/**
 * @brief Initialization of the node given key and value
 */
template <class K, class T>
void RangeTreeNode<K,T>::init(const K& key, T* value) {
    this->key = key;
    this->value = value;

    this->left = nullptr;
    this->right = nullptr;

    this->parent = nullptr;

    this->height = 1;

    this->assRangeTree = nullptr;
}

/**
 * @brief Check if the node is a leaf
 *
 * @return True if the node is a leaf
 */
template <class K, class T>
bool RangeTreeNode<K,T>::isLeaf() const {
    return (left == nullptr) && (right == nullptr);
}

}

}

/**
    @author Stefano Nuvoli
*/
#include "aabbtreenode.h"

namespace cg3 {


/* --------- CONSTRUCTORS/DESTRUCTOR --------- */



/**
 * @brief Constructor with key and value
 */
template <int D, class K, class T>
AABBTree<D,K,T>::Node::Node(const K& key, const T& value) {
    this->key = key;
    this->value = new T(value);

    this->left = nullptr;
    this->right = nullptr;

    this->height = 1;
}

/**
 * @brief Constructor with only key
 */
template <int D, class K, class T>
AABBTree<D,K,T>::Node::Node(const K& key) {
    this->key = key;
    this->value = nullptr;

    this->left = nullptr;
    this->right = nullptr;

    this->height = 1;
}

/**
 * @brief Destructor
 */
template <int D, class K, class T>
AABBTree<D,K,T>::Node::~Node()
{
    if (this->value != nullptr)
        delete this->value;
}


/* --------- METHODS --------- */

/**
 * @brief Check if the node is a leaf
 *
 * @return True if the node is a leaf
 */
template <int D, class K, class T>
inline bool AABBTree<D,K,T>::Node::isLeaf() const {
    return (left == nullptr) && (right == nullptr);
}

}

/**
    @author Stefano Nuvoli
*/
#include "bstinnernode.h"

namespace cg3 {


/* --------- CONSTRUCTORS/DESTRUCTOR --------- */

/**
 * @brief Constructor with key and value
 */
template <class K, class T>
BSTInner<K,T>::Node::Node(
        const K& key,
        const T& value)
{
    this->key = key;
    this->value = new T(value);

    this->left = nullptr;
    this->right = nullptr;
}

/**
 * @brief Constructor with only key
 */
template <class K, class T>
BSTInner<K,T>::Node::Node(
        const K& key)
{
    this->key = key;
    this->value = nullptr;

    this->left = nullptr;
    this->right = nullptr;
}


/**
 * @brief Destructor
 */
template<class K, class T>
BSTInner<K, T>::Node::~Node()
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
template <class K, class T>
inline bool BSTInner<K,T>::Node::isLeaf() const {
    return (left == nullptr) && (right == nullptr);
}

}

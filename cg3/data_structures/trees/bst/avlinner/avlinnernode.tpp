/**
    @author Stefano Nuvoli
*/
#include "avlinnernode.h"

namespace cg3 {

/* --------- CONSTRUCTORS/DESTRUCTOR --------- */

/**
 * @brief Constructor with key and value
 */
template<class K, class T>
AVLInner<K,T>::Node::Node(
        const K& key,
        const T& value)
{
    init(key, new T(value));
}

/**
 * @brief Constructor with only key
 */
template<class K, class T>
AVLInner<K,T>::Node::Node(const K& key)
{
    init(key, nullptr);
}

/**
 * @brief Destructor
 */
template<class K, class T>
AVLInner<K,T>::Node::~Node()
{
    if (this->value != nullptr)
        delete this->value;
}



/* --------- PRIVATE METHODS --------- */

/**
 * @brief Initialization of the node given key and value
 */
template<class K, class T>
void AVLInner<K,T>::Node::init(const K& key, T* value) {
    this->key = key;
    this->value = value;

    this->left = nullptr;
    this->right = nullptr;

    this->parent = nullptr;

    this->height = 1;
}

/**
 * @brief Check if the node is a leaf
 *
 * @return True if the node is a leaf
 */
template<class K, class T>
inline bool AVLInner<K,T>::Node::isLeaf() const {
    return (left == nullptr) && (right == nullptr);
}



}
